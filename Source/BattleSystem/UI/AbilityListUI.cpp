// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityListUI.h"

#include "../Data/Ability.h"

#include <Engine/Texture2D.h>
#include <Components/Button.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Components/HorizontalBox.h>
#include <Components/Spacer.h>
#include <Components/ButtonSlot.h>
#include <Components/HorizontalBoxSlot.h>
#include <Components/ScrollBoxSlot.h>


void UAbilityListUI::AddAbility(UAbility* Ability, UTexture2D* ButtonTexture)
{
	UButton* BaseButton = NewObject<UButton>(this, UButton::StaticClass());
	FButtonStyle Style;
	Style.Normal.SetResourceObject(ButtonTexture);
	Style.Hovered.SetResourceObject(ButtonTexture);
	Style.Pressed.SetResourceObject(ButtonTexture);
	Style.Normal.TintColor = FSlateColor(FLinearColor{ 1.f, 1.f, 1.f, 0.f });
	Style.Hovered.TintColor = FSlateColor(FLinearColor{ 1.f, 1.f, 1.f, 0.4f });
	Style.Pressed.TintColor = FSlateColor(FLinearColor{ 1.f, 1.f, 1.f, 0.4f });
	BaseButton->SetStyle(Style);
	AddChild(BaseButton);
	Cast<UScrollBoxSlot>(BaseButton->Slot)->SetPadding(FMargin(24, 24));

	UHorizontalBox* ButtonBox = NewObject<UHorizontalBox>(this, UHorizontalBox::StaticClass());
	
	BaseButton->AddChild(ButtonBox);

	UTextBlock* Name = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
	UImage* Icon = NewObject<UImage>(this, UImage::StaticClass());
	Name->SetText(Ability->GetAbilityName());
	Name->Font.Size = 36;
	Icon->SetBrushFromTexture(Ability->GetAbilityIcon());
	Icon->SetBrushSize(FVector2D(64, 64));

	USpacer* Spacer = NewObject<USpacer>(this, USpacer::StaticClass());
	Spacer->SetSize(FVector2D(24, 0));
	USpacer* Spacer2 = NewObject<USpacer>(this, USpacer::StaticClass());
	
	UTextBlock* AbilityCost = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
	AbilityCost->SetText(FText::Format(FTextFormat::FromString("{Cost} EP"), Ability->GetEPCost()));
	AbilityCost->Font.Size = 36;

	ButtonBox->AddChild(Icon);
	ButtonBox->AddChild(Spacer);
	ButtonBox->AddChild(Name);
	ButtonBox->AddChild(Spacer2);
	ButtonBox->AddChild(AbilityCost);

	Cast<UButtonSlot>(BaseButton->GetSlots()[0])->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	Cast<UHorizontalBoxSlot>(Spacer2->Slot)->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	Cast<UHorizontalBoxSlot>(AbilityCost->Slot)->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Right);
}


void UAbilityListUI::ClearList()
{
	ClearChildren();
}
