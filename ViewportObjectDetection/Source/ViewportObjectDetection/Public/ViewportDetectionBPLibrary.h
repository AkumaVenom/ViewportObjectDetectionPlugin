
#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ViewportDetectionTypes.h"
#include "ViewportDetectionBPLibrary.generated.h"

/**
 * Helper Blueprint functions for turning detection results into nice text blocks
 * for LLM prompts, logging, etc.
 */
UCLASS()
class VIEWPORTOBJECTDETECTION_API UViewportDetectionBPLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /**
     * Builds a context string from a list of detections.
     * Example output:
     *   "You see: 1) Enemy soldier - holding a rifle [distance: 1200] [confidence: 0.92]\n2) Health potion..."
     */
    UFUNCTION(BlueprintCallable, Category="ViewportDetection", meta=(AutoCreateRefTerm="Detections"))
    static FString BuildLLMContextFromDetections(
        const TArray<FViewportDetectionResult>& Detections,
        int32 MaxLines,
        bool bIncludeDistance,
        bool bIncludeConfidence
    );
};
