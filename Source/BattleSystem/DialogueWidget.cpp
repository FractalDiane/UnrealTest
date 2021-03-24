// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"

#include <Components/RichTextBlock.h>
#include <Components/TextBlock.h>


void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TextBlock->SetText(FText::FromString("Default text"));
}


bool UDialogueWidget::Initialize()
{
	Super::Initialize();

	//GetWorld()->GetTimerManager().SetTimer(IncrementTimerHandle, this, &UDialogueWidget::IncrementCharactersVisible, 0.3f, true);
	return true;
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
	GetWorld()->GetTimerManager().SetTimer(IncrementTimerHandle, this, &UDialogueWidget::IncrementCharactersVisible, TextInterval, true);
}

// ============================================================================

void UDialogueWidget::IncrementCharactersVisible()
{
	CharactersVisible++;
	UpdateVisibleText();
}


void UDialogueWidget::UpdateVisibleText()
{
	VisibleText = Text[Page].Mid(0, CharactersVisible);
	TextBlock->SetText(FText::FromString(VisibleText));
}
