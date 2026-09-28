// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonUserWidget.h"
#include "GameFramework/GameplayMessageSubsystem.h"

#include "MedalsHostWidget.generated.h"

struct FGameplayTag;
struct FLyraVerbMessage;

UENUM(BlueprintType)
enum class EMedalType : uint8
{
	Kill,
	OneShot,
	JumpKill,

	MAX	UMETA(Hidden)
};

UCLASS()
class SHOOTERCORERUNTIME_API UMedalsHostWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	//~UUserWidget interface
	virtual void NativeOnInitialized() override;
	//~End of UUserWidget interface

	UFUNCTION(BlueprintImplementableEvent)
	void AddMedal(EMedalType MedalType);

private:	
	void OnEliminationMessage(FGameplayTag Channel, const FLyraVerbMessage& Payload);
};
