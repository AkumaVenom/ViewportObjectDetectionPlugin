
#pragma once

#include "CoreMinimal.h"
#include "ViewportDetectionTypes.generated.h"

class UDetectableObjectComponent;

/**
 * Single simulated detection result.
 */
USTRUCT(BlueprintType)
struct VIEWPORTOBJECTDETECTION_API FViewportDetectionResult
{
    GENERATED_BODY()

public:

    // The detectable component that was "seen".
    UPROPERTY(BlueprintReadOnly, Category="ViewportDetection")
    TWeakObjectPtr<UDetectableObjectComponent> SourceComponent;

    // Short label for this detection (e.g., "Enemy soldier").
    UPROPERTY(BlueprintReadOnly, Category="ViewportDetection")
    FString Label;

    // Extra descriptive text (for LLM context).
    UPROPERTY(BlueprintReadOnly, Category="ViewportDetection")
    FString Description;

    // Distance in world units.
    UPROPERTY(BlueprintReadOnly, Category="ViewportDetection")
    float Distance = 0.f;

    // Dot product between forward vector and direction to target:
    // 1 = directly ahead, 0 = 90 degrees, -1 = behind.
    UPROPERTY(BlueprintReadOnly, Category="ViewportDetection")
    float ForwardDot = 0.f;

    // Simulated confidence [0..1].
    UPROPERTY(BlueprintReadOnly, Category="ViewportDetection")
    float Confidence = 0.f;

    // World-space location of the detected actor.
    UPROPERTY(BlueprintReadOnly, Category="ViewportDetection")
    FVector Location = FVector::ZeroVector;
};
