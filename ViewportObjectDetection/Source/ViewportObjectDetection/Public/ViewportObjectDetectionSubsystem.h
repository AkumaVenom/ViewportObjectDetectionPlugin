
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ViewportDetectionTypes.h"
#include "ViewportObjectDetectionSubsystem.generated.h"

class UDetectableObjectComponent;

/**
 * GameInstance subsystem that tracks all detectable components and
 * performs fast cone-based detection queries.
 */
UCLASS()
class VIEWPORTOBJECTDETECTION_API UViewportObjectDetectionSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // Registry management
    void RegisterDetectable(UDetectableObjectComponent* Component);
    void UnregisterDetectable(UDetectableObjectComponent* Component);

    // Main query: find detectables in a vision cone + optional line-of-sight test.
    void QueryDetectables(
        UWorld* World,
        const FVector& Origin,
        const FVector& Forward,
        float MaxDistance,
        float FOVDegrees,
        bool bCheckLineOfSight,
        TArray<FViewportDetectionResult>& OutResults
    ) const;

protected:
    UPROPERTY()
    TArray<TWeakObjectPtr<UDetectableObjectComponent>> RegisteredDetectables;
};
