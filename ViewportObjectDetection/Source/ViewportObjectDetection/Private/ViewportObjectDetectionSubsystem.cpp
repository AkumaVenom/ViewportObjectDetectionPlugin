
#include "ViewportObjectDetectionSubsystem.h"
#include "DetectableObjectComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"

void UViewportObjectDetectionSubsystem::RegisterDetectable(UDetectableObjectComponent* Component)
{
    if (!Component)
    {
        return;
    }

    RegisteredDetectables.RemoveAll(
        [Component](const TWeakObjectPtr<UDetectableObjectComponent>& Ptr)
        {
            return !Ptr.IsValid() || Ptr.Get() == Component;
        });

    RegisteredDetectables.Add(Component);
}

void UViewportObjectDetectionSubsystem::UnregisterDetectable(UDetectableObjectComponent* Component)
{
    if (!Component)
    {
        return;
    }

    RegisteredDetectables.RemoveAll(
        [Component](const TWeakObjectPtr<UDetectableObjectComponent>& Ptr)
        {
            return !Ptr.IsValid() || Ptr.Get() == Component;
        });
}

void UViewportObjectDetectionSubsystem::QueryDetectables(
    UWorld* World,
    const FVector& Origin,
    const FVector& Forward,
    float MaxDistance,
    float FOVDegrees,
    bool bCheckLineOfSight,
    TArray<FViewportDetectionResult>& OutResults
) const
{
    OutResults.Reset();

    if (!World || RegisteredDetectables.Num() == 0)
    {
        return;
    }

    const float MaxDistanceSq = MaxDistance * MaxDistance;
    const float HalfFOVRadians = FMath::DegreesToRadians(FOVDegrees * 0.5f);
    const float MinDot = FMath::Cos(HalfFOVRadians);

    FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(ViewportObjectDetection), false);
    QueryParams.bReturnPhysicalMaterial = false;

    for (const TWeakObjectPtr<UDetectableObjectComponent>& WeakComp : RegisteredDetectables)
    {
        UDetectableObjectComponent* Comp = WeakComp.Get();
        if (!Comp || !Comp->IsDetectable())
        {
            continue;
        }

        AActor* Owner = Comp->GetOwner();
        if (!Owner || Owner->IsActorBeingDestroyed())
        {
            continue;
        }

        const FVector TargetLocation = Owner->GetActorLocation();
        const FVector ToTarget = TargetLocation - Origin;
        const float DistSq = ToTarget.SizeSquared();

        if (DistSq > MaxDistanceSq)
        {
            continue;
        }

        const float Distance = FMath::Sqrt(DistSq);
        const FVector DirToTarget = ToTarget.GetSafeNormal();

        const float Dot = FVector::DotProduct(Forward.GetSafeNormal(), DirToTarget);
        if (Dot < MinDot)
        {
            continue;
        }

        if (bCheckLineOfSight)
        {
            FHitResult Hit;
            const bool bHit = World->LineTraceSingleByChannel(
                Hit,
                Origin,
                TargetLocation,
                ECC_Visibility,
                QueryParams
            );

            if (bHit && Hit.GetActor() != Owner)
            {
                // Something else is in the way.
                continue;
            }
        }

        const float DistanceFactor = 1.f - FMath::Clamp(Distance / MaxDistance, 0.f, 1.f);
        const float FovFactor = FMath::Clamp((Dot - MinDot) / (1.f - MinDot + KINDA_SMALL_NUMBER), 0.f, 1.f);
        const float BaseConfidence = DistanceFactor * 0.6f + FovFactor * 0.4f;

        FViewportDetectionResult Result;
        Result.SourceComponent = Comp;
        Result.Label = Comp->DetectionName;
        Result.Description = Comp->BuildFullDescription();
        Result.Distance = Distance;
        Result.ForwardDot = Dot;
        Result.Location = TargetLocation;
        Result.Confidence = FMath::Clamp(BaseConfidence, 0.f, 1.f);

        OutResults.Add(Result);
    }

    // Sort by confidence descending, then distance ascending.
    OutResults.Sort([](const FViewportDetectionResult& A, const FViewportDetectionResult& B)
    {
        if (!FMath::IsNearlyEqual(A.Confidence, B.Confidence))
        {
            return A.Confidence > B.Confidence;
        }
        return A.Distance < B.Distance;
    });
}
