
#include "ObjectDetectorComponent.h"
#include "ViewportObjectDetectionSubsystem.h"
#include "DetectableObjectComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Engine/GameInstance.h"
#include "DrawDebugHelpers.h"

UObjectDetectorComponent::UObjectDetectorComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UObjectDetectorComponent::BeginPlay()
{
    Super::BeginPlay();
    TimeSinceLastScan = 0.f;
}

void UObjectDetectorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}

void UObjectDetectorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!bAutoScan)
    {
        return;
    }

    TimeSinceLastScan += DeltaTime;
    if (TimeSinceLastScan >= UpdateInterval)
    {
        TimeSinceLastScan = 0.f;
        PerformScan();
    }
}

UViewportObjectDetectionSubsystem* UObjectDetectorComponent::GetDetectionSubsystem() const
{
    if (UWorld* World = GetWorld())
    {
        if (UGameInstance* GI = World->GetGameInstance())
        {
            return GI->GetSubsystem<UViewportObjectDetectionSubsystem>();
        }
    }
    return nullptr;
}

void UObjectDetectorComponent::ScanNow()
{
    PerformScan();
}

void UObjectDetectorComponent::PerformScan()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    AActor* Owner = GetOwner();
    if (!Owner)
    {
        return;
    }

    FVector Origin = Owner->GetActorLocation();
    FVector Forward = Owner->GetActorForwardVector();

    if (ViewOrigin)
    {
        Origin = ViewOrigin->GetComponentLocation();
    }
    if (ViewDirection)
    {
        Forward = ViewDirection->GetForwardVector();
    }

    if (UViewportObjectDetectionSubsystem* Subsystem = GetDetectionSubsystem())
    {
        TArray<FViewportDetectionResult> Results;
        Subsystem->QueryDetectables(
            World,
            Origin,
            Forward,
            MaxDistance,
            FOVDegrees,
            bCheckLineOfSight,
            Results
        );

        LastDetections = Results;
        OnDetectionsUpdated.Broadcast(LastDetections);

        if (bDebugDraw)
        {
            DebugDrawDetections(Origin, Forward);
        }
    }
}

void UObjectDetectorComponent::DebugDrawDetections(const FVector& Origin, const FVector& Forward)
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    // Draw central forward line
    const FVector End = Origin + Forward.GetSafeNormal() * MaxDistance;
    DrawDebugLine(World, Origin, End, FColor::Cyan, false, DebugDrawTime, 0, 1.5f);

    // Draw lines to each detected target
    for (const FViewportDetectionResult& Result : LastDetections)
    {
        DrawDebugLine(World, Origin, Result.Location, FColor::Green, false, DebugDrawTime, 0, 1.2f);
        DrawDebugSphere(World, Result.Location, 12.f, 8, FColor::Yellow, false, DebugDrawTime, 0, 1.0f);
    }
}

FString UObjectDetectorComponent::GetLLMContextText(int32 MaxLines, bool bIncludeDistance, bool bIncludeConfidence) const
{
    FString Out;
    const int32 Count = FMath::Min(MaxLines, LastDetections.Num());

    for (int32 i = 0; i < Count; ++i)
    {
        const FViewportDetectionResult& D = LastDetections[i];

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
