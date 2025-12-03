
#include "DetectableObjectComponent.h"
#include "ViewportObjectDetectionSubsystem.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"

UDetectableObjectComponent::UDetectableObjectComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UDetectableObjectComponent::OnRegister()
{
    Super::OnRegister();

    if (UViewportObjectDetectionSubsystem* Subsystem = GetDetectionSubsystem())
    {
        Subsystem->RegisterDetectable(this);
    }
}

void UDetectableObjectComponent::OnUnregister()
{
    if (UViewportObjectDetectionSubsystem* Subsystem = GetDetectionSubsystem())
    {
        Subsystem->UnregisterDetectable(this);
    }

    Super::OnUnregister();
}

void UDetectableObjectComponent::BeginPlay()
{
    Super::BeginPlay();

    if (UViewportObjectDetectionSubsystem* Subsystem = GetDetectionSubsystem())
    {
        Subsystem->RegisterDetectable(this);
    }
}

UViewportObjectDetectionSubsystem* UDetectableObjectComponent::GetDetectionSubsystem() const
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

FString UDetectableObjectComponent::BuildFullDescription() const
{
    FString Result = DetectionName;
    if (!DetectionDescription.IsEmpty())
    {
        if (!Result.IsEmpty())
        {
            Result += TEXT(" - ");
        }
        Result += DetectionDescription;
    }

    if (Tags.Num() > 0)
    {
        Result += TEXT(" [Tags: ");
        for (int32 i = 0; i < Tags.Num(); ++i)
        {
            if (i > 0)
            {
                Result += TEXT(", ");
            }
            Result += Tags[i];
        }
        Result += TEXT("]");
    }

    return Result;
}
