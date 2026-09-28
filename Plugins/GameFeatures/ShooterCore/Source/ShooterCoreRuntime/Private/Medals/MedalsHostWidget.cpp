// Fill out your copyright notice in the Description page of Project Settings.

#include "Medals/MedalsHostWidget.h"

#include "GameFramework/PlayerState.h"
#include "Messages/LyraNotificationMessage.h"
#include "Messages/LyraVerbMessage.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(MedalsHostWidget)

namespace MedalsWidget
{
	UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_Lyra_Elimination_Message, "Lyra.Elimination.Message");
	UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_Lyra_Elimination_Context_OneShot, "Lyra.Elimination.Context.OneShot");
}

void UMedalsHostWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	MessageSubsystem.RegisterListener(MedalsWidget::TAG_Lyra_Elimination_Message, this, &ThisClass::OnEliminationMessage);
}

void UMedalsHostWidget::OnEliminationMessage(FGameplayTag Channel, const FLyraVerbMessage& Payload)
{
	const APlayerController* PC = GetOwningPlayer();
	const APlayerState* InstigatorPS = Cast<APlayerState>(Payload.Instigator);
	const bool bIsSuicide = Payload.Instigator == Payload.Target;
	if (!PC || !InstigatorPS || PC->PlayerState != InstigatorPS || bIsSuicide)
	{
		return;
	}

	if (Payload.ContextTags.HasTagExact(MedalsWidget::TAG_Lyra_Elimination_Context_OneShot))
	{
		AddMedal(EMedalType::OneShot);
	}
	else if(Payload.InstigatorTags.HasTagExact(FGameplayTag::RequestGameplayTag("Movement.Mode.Falling")))
	{
		AddMedal(EMedalType::JumpKill);
	}
	else
	{
		AddMedal(EMedalType::Kill);
	}
}
