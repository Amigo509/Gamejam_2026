#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingArrows.h"
#include "DayNightCycle.generated.h"

class ADirectionalLight;

UCLASS()
class MYPROJECT_API ADayNightCycle : public AActor
{
	GENERATED_BODY()
	
public:	
	ADayNightCycle();

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = "Day/Night")
	TObjectPtr<ADirectionalLight> SunLight;

	UPROPERTY(EditAnywhere, Category = "Day/Night")
	TObjectPtr<ADirectionalLight> MoonLight;

	UPROPERTY(EditAnywhere, Category = "Day/Night")
	float DayLength = 60.f;

	UPROPERTY(EditAnywhere, Category = "Day/Night")
	TObjectPtr<AMovingArrows> ClockActor;
};
