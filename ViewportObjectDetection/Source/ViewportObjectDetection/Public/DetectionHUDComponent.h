#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ViewportDetectionTypes.h"
#include "DetectionHUDComponent.generated.h"

class UObjectDetectorComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHUDDetectionsUpdated, const TArray<FViewportDetectionResult>&, Results);

UCLASS(ClassGroup=(SimDetection), meta=(BlueprintSpawnableComponent))
class VIEWPORTOBJECTDETECTION_API UDetectionHUDComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UDetectionHUDComponent();

protected:
    virtual void BeginPlay() override;

public:
    /** Master toggle: if false, this component will not forward detections for HUD usage. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HUD")
    bool bEnableDetectionHUD = true;

    /** If true, only broadcasts when there is at least one detection. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HUD")
    bool bOnlyWhenHasDetections = true;

    /** Event fired whenever the owning detector updates its detections.
        Bind to this in Blueprints (e.g. in a UMG widget) to drive YOLO-style boxes. */
    UPROPERTY(BlueprintAssignable, Category="HUD")
    FOnHUDDetectionsUpdated OnHUDDetectionsUpdated;

    /** Internal binding from the detector. */
    UFUNCTION()
    void HandleDetections(const TArray<FViewportDetectionResult>& Results);

private:
    /** Cached pointer to the detector on the same actor, if any. */
    UObjectDetectorComponent* DetectorRef = nullptr;
};
