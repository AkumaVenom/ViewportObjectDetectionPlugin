
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DetectableObjectComponent.generated.h"

class UViewportObjectDetectionSubsystem;

UENUM(BlueprintType)
enum class EViewportDetectionCategory : uint8
{
    Generic         UMETA(DisplayName="Generic"),
    Character       UMETA(DisplayName="Character"),
    Item            UMETA(DisplayName="Item"),
    Obstacle        UMETA(DisplayName="Obstacle"),
    PointOfInterest UMETA(DisplayName="Point Of Interest")
};

/**
 * Attach this to any Actor/Pawn to mark it as detectable by viewport object detectors.
 * You define a Name, Description and Tags that are used to generate LLM-friendly text.
 */
UCLASS(ClassGroup=(ViewportDetection), meta=(BlueprintSpawnableComponent))
class VIEWPORTOBJECTDETECTION_API UDetectableObjectComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDetectableObjectComponent();

protected:
    virtual void OnRegister() override;
    virtual void OnUnregister() override;
    virtual void BeginPlay() override;

public:
    // Short name used in detection output, e.g. "Enemy soldier", "Health potion".
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ViewportDetection")
    FString DetectionName;

    // Optional detailed text for LLM context (multi-line allowed).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ViewportDetection", meta=(MultiLine="true"))
    FString DetectionDescription;

    // Optional category for filtering and organization.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ViewportDetection")
    EViewportDetectionCategory Category = EViewportDetectionCategory::Generic;

    // If false, this object will be ignored by detection queries.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ViewportDetection")
    bool bDetectable = true;

    // Optional per-object max detection distance (0 = use observer's range).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ViewportDetection")
    float MaxDetectionDistanceOverride = 0.f;

    // Importance for LLM sorting (higher = more important).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ViewportDetection")
    float Importance = 1.f;

    // Extra text tags / keywords for the LLM. (e.g. "enemy", "robot", "dangerous").
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ViewportDetection")
    TArray<FString> Tags;

public:
    UFUNCTION(BlueprintCallable, Category="ViewportDetection")
    float GetMaxDetectionDistanceOverride() const { return MaxDetectionDistanceOverride; }

    UFUNCTION(BlueprintCallable, Category="ViewportDetection")
    bool IsDetectable() const { return bDetectable; }

    // Builds a full description string combining name, description, and tags.
    UFUNCTION(BlueprintCallable, Category="ViewportDetection")
    FString BuildFullDescription() const;

private:
    UViewportObjectDetectionSubsystem* GetDetectionSubsystem() const;
};
