
#include "ViewportDetectionBPLibrary.h"

FString UViewportDetectionBPLibrary::BuildLLMContextFromDetections(
    const TArray<FViewportDetectionResult>& Detections,
    int32 MaxLines,
    bool bIncludeDistance,
    bool bIncludeConfidence
)
{
    FString Out;

    const int32 Count = FMath::Min(MaxLines, Detections.Num());
    if (Count <= 0)
    {
        return Out;
    }

    Out += TEXT("You see:\n");

    for (int32 i = 0; i < Count; ++i)
    {
        const FViewportDetectionResult& D = Detections[i];

        FString Line;
        Line += FString::Printf(TEXT("%d) %s"), i + 1, *D.Label);

        if (!D.Description.IsEmpty())
        {
            Line += TEXT(" - ");
            Line += D.Description;
        }

        if (bIncludeDistance)
        {
            Line += FString::Printf(TEXT(" [distance: %.0f]"), D.Distance);
        }

        if (bIncludeConfidence)
        {
            Line += FString::Printf(TEXT(" [confidence: %.2f]"), D.Confidence);
        }

        Out += Line;
        Out += TEXT("\n");
    }

    return Out;
}
