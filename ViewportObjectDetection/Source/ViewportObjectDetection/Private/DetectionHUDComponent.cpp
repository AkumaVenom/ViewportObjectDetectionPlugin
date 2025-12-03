#include "DetectionHUDComponent.h"
#include "ObjectDetectorComponent.h"

UDetectionHUDComponent::UDetectionHUDComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UDetectionHUDComponent::BeginPlay()
{
    Super::BeginPlay();

    // Auto-attach to the same actor's detector component (if present)
    DetectorRef = GetOwner() ? GetOwner()->FindComponentByClass<UObjectDetectorComponent>() : nullptr;
    if (DetectorRef)
    {
        DetectorRef->OnDetectionsUpdated.AddDynamic(this, &UDetectionHUDComponent::HandleDetections);
    }
}

void UDetectionHUDComponent::HandleDetections(const TArray<FViewportDetectionResult>& Results)
{
    if (!bEnableDetectionHUD)
    {
        return;
    }

    if (bOnlyWhenHasDetections && Results.Num() == 0)
    {
        return;
    }

    OnHUDDetectionsUpdated.Broadcast(Results);
}
