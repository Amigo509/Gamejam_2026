#include "DayNightCycle.h"
#include "Engine/DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"

ADayNightCycle::ADayNightCycle()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADayNightCycle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!SunLight)
    {
        return;
    }

    CurrentTime += DeltaTime;

    const float Alpha = FMath::Fmod(CurrentTime / DayLength, 1.f);

    const float SunPitch = Alpha * 360.f - 90.f;

    FRotator SunRotation = SunLight->GetActorRotation();
    SunRotation.Pitch = SunPitch;
    SunLight->SetActorRotation(SunRotation);

    if (MoonLight)
    {
        FRotator MoonRotation = SunRotation;
        MoonRotation.Pitch = FMath::UnwindDegrees(SunPitch + 180.f);

        MoonLight->SetActorRotation(MoonRotation);
    }

    /*const float SunHeight = SunLight->GetActorForwardVector().Z;

    const float SunIntensity = FMath::Max(0.f, SunHeight) * MaxSunIntensity;
    SunLight->GetLightComponent()->SetIntensity(SunIntensity);

    if (MoonLight)
    {
        const float MoonIntensity = FMath::Max(0.f, -SunHeight) * MaxMoonIntensity;
        MoonLight->GetLightComponent()->SetIntensity(MoonIntensity);
    }*/
}

