#include "MovingArrows.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

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

    PlayerController = UGameplayStatics::GetPlayerController(this, 0);

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

    if (IsPlayerLookingAtClock())
    {
        return;
    }

    ElapsedTime += DeltaTime;

    if (ElapsedTime >= StopAfter)
    {
        bTimeExpired = true;
        bClockStopped = true;

        //SetActorTickEnabled(false);

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

bool AMovingArrows::IsPlayerLookingAtClock() const
{
    if (!ensure(PlayerController))
    {
        return false;
    }

    FVector CameraLocation;
    FRotator CameraRotation;
    PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

    const FVector ToClock = (GetActorLocation() - CameraLocation).GetSafeNormal();

    const float Dot = FVector::DotProduct(CameraRotation.Vector(), ToClock);

    if (Dot < LookDotThreshold)
    {
        return false;
    }

    FHitResult Hit;

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(PlayerController->GetPawn());

    const bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, GetActorLocation(), ECC_Visibility, Params);

    //DrawDebugLine(GetWorld(),CameraLocation,GetActorLocation(), bHit ? FColor::Green : FColor::Red, false, 0.0f, 0, 0.5f);

    if (!bHit)
    {
        return false;
    }

    return Hit.GetActor() == this;
}