#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingArrows.generated.h"

UCLASS()
class MYPROJECT_API AMovingArrows : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovingArrows();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clock")
	TObjectPtr<UStaticMeshComponent> MinuteArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clock")
	TObjectPtr<UStaticMeshComponent> SecondArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock")
	float StopAfter = 60.f;


private:
	float CurrentSeconds = 0.f;
	float CurrentMinutes = 0.f;

	FRotator InitialMinuteRotation;
	FRotator InitialSecondRotation;

	float ElapsedTime = 0.f;
	bool bClockStopped = false;
};
