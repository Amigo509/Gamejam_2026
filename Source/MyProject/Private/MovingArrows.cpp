#include "MovingArrows.h"

AMovingArrows::AMovingArrows()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	MinuteArrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MinuteHand"));
	MinuteArrow->SetupAttachment(RootComponent);

	SecondArrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondHand"));
	SecondArrow->SetupAttachment(RootComponent);

}

void AMovingArrows::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentSeconds = 0.f;
	CurrentMinutes = 0.f;

    if (!ensure(MinuteArrow))
    {
        return;
    }
    InitialMinuteRotation = MinuteArrow->GetRelativeRotation();

    if (!ensure(SecondArrow))
    {
        return;
    }
    InitialSecondRotation = SecondArrow->GetRelativeRotation();
}

void AMovingArrows::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    ElapsedTime += DeltaTime;

    if (ElapsedTime >= StopAfter)
    {
        bClockStopped = true;

        SetActorTickEnabled(false);

        return;
    }

    if (bClockStopped)
    {
        return;
    }

    CurrentSeconds += DeltaTime;

    if (CurrentSeconds >= 60.f)
    {
        CurrentSeconds -= 60.f;
        CurrentMinutes += 1.f;
    }

    if (CurrentMinutes >= 60.f)
    {
        CurrentMinutes -= 60.f;
    }

    const float SecondAngle = CurrentSeconds * 6.f;
    const float MinuteAngle = (CurrentMinutes + CurrentSeconds / 60.f) * 6.f;

    SecondArrow->SetRelativeRotation(InitialSecondRotation + FRotator(SecondAngle, 0.f, 0.f));

    MinuteArrow->SetRelativeRotation(InitialMinuteRotation + FRotator(MinuteAngle, 0.f, 0.f));
}