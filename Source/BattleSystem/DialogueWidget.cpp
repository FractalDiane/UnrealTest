// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"

#include <Components/RichTextBlock.h>
#include <Components/TextBlock.h>
#include <Animation/WidgetAnimation.h>

void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	EventStart.BindDynamic(this, &UDialogueWidget::StartText);
	EventStart2.BindDynamic(this, &UDialogueWidget::EnableInput);
	EventEnd.BindDynamic(this, &UDialogueWidget::Destroy);
}


void UDialogueWidget::NativeDestruct()
{
	Super::NativeDestruct();

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

// ============================================================================

void UDialogueWidget::SetName(const FText& Name)
{
	NameBlock->SetText(Name);
	FText Test = Name;
}


void UDialogueWidget::SetDialogueText(const TArray<FString>& _Text)
{
	Text = _Text;
}


void UDialogueWidget::Start()
{
	Page = 0;
	CharactersVisible = 0;
	UpdateVisibleText();

	BindToAnimationFinished(AnimFadein, EventStart);
	BindToAnimationFinished(AnimFadein, EventStart2);
	PlayAnimation(AnimFadein);
}

// ============================================================================

void UDialogueWidget::EnableInput()
{
	AdvanceDelegate.BindDynamic(this, &UDialogueWidget::AdvanceText);
	ListenForInputAction(TEXT("Interact"), IE_Pressed, true, AdvanceDelegate);
}


void UDialogueWidget::IncrementCharactersVisible()
{
	if (++CharactersVisible >= Text[Page].Len()) {
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
		TextRunning = false;
	}

	UpdateVisibleText();
}


void UDialogueWidget::UpdateVisibleText()
{
	VisibleText = Text[Page].Mid(0, CharactersVisible);
	TextBlock->SetText(FText::FromString(VisibleText));
}


void UDialogueWidget::StartText()
{
	GetWorld()->GetTimerManager().SetTimer(IncrementTimerHandle, this, &UDialogueWidget::IncrementCharactersVisible, TextInterval, true);
	TextRunning = true;
}


void UDialogueWidget::AdvanceText()
{
	if (TextRunning) {
		CharactersVisible = Text[Page].Len();
		UpdateVisibleText();

		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
		TextRunning = false;
	}
	else {
		if (Page < Text.Num() - 1) {
			Page++;
			CharactersVisible = 0;
			UpdateVisibleText();
			StartText();
		}
		else {
			BindToAnimationFinished(AnimFadeout, EventEnd);
			PlayAnimation(AnimFadeout);
		}
	}
}


void UDialogueWidget::Destroy()
{
	RemoveFromParent();
	OnDialogueFinished.Execute();
}
