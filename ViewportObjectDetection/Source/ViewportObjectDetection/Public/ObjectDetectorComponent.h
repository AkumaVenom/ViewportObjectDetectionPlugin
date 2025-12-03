
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ViewportDetectionTypes.h"
#include "ObjectDetectorComponent.generated.h"

class UViewportObjectDetectionSubsystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDetectionsUpdated, const TArray<FViewportDetectionResult>&, Detections);

/**
 * Component you put on NPCs / Pawns / Actors to simulate YOLO-style object detection.
 * It does a cone check + optional line trace and keeps a list of current detections,
 * plus exposes a ready-to-send LLM context string.
 */
UCLASS(ClassGroup=(ViewportDetection), meta=(BlueprintSpawnableComponent))
class VIEWPORTOBJECTDETECTION_API UObjectDetectorComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UObjectDetectorComponent();

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
    float TimeSinceLastScan = 0.f;

public:
    // Should this component automatically scan every UpdateInterval seconds?
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ViewportDetection")
    bool bAutoScan = true;

    // Interval in seconds for auto scan when bAutoScan is true.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ViewportDetection", meta=(ClampMin="0.01"))
    float UpdateInterval = 0.25f;

    // Maximum distance for detection.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ViewportDetection", meta=(ClampMin="10.0"))
    float MaxDistance = 3000.f;

    // Field of view in degrees (centered around forward vector).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ViewportDetection", meta=(ClampMin="1.0", ClampMax="180.0"))
    float FOVDegrees = 90.0f;

    // If true, perform a visibility line trace to ensure nothing blocks the target.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ViewportDetection")
    bool bCheckLineOfSight = true;

    // If true, draw debug lines/cones each scan (runtime only, works in PIE and packaged).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ViewportDetection")
    bool bDebugDraw = false;

    // How long debug draw should persist (seconds).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ViewportDetection", meta=(ClampMin="0.0"))
    float DebugDrawTime = 0.05f;

    // Optional custom view origin (if not set, owner's actor location is used).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ViewportDetection")
    USceneComponent* ViewOrigin = nullptr;

    // Optional custom view direction (if not set, owner's forward vector is used).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ViewportDetection")
    USceneComponent* ViewDirection = nullptr;

    // Latest detections (read-only, but can be accessed from Blueprints).
    UPROPERTY(BlueprintReadOnly, Category="ViewportDetection")
    TArray<FViewportDetectionResult> LastDetections;

    // Fired whenever a scan completes.
    UPROPERTY(BlueprintAssignable, Category="ViewportDetection")
    FOnDetectionsUpdated OnDetectionsUpdated;

public:
    // Forces a scan immediately.
    UFUNCTION(BlueprintCallable, Category="ViewportDetection")
    void ScanNow();

    // Returns latest LLM-friendly context text built from LastDetections.
    UFUNCTION(BlueprintCallable, Category="ViewportDetection")
    FString GetLLMContextText(int32 MaxLines = 16, bool bIncludeDistance = true, bool bIncludeConfidence = true) const;

protected:
    UViewportObjectDetectionSubsystem* GetDetectionSubsystem() const;
    void PerformScan();
    void DebugDrawDetections(const FVector& Origin, const FVector& Forward);
};
