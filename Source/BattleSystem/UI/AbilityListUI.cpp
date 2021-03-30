// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityListUI.h"

#include <Engine/Texture2D.h>
#include <Components/Button.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Components/HorizontalBox.h>
#include <Components/Spacer.h>
#include <Components/HorizontalBoxSlot.h>


void UAbilityListUI::AddAbility(FText AbilityName, UTexture2D* AbilityIcon, UTexture2D* ButtonTexture)
{
	UTextBlock* Name = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
	UImage* Icon = NewObject<UImage>(this, UImage::StaticClass());
	Name->SetText(AbilityName);
	Name->Font.Size = 36;

	Icon->SetBrushFromTexture(AbilityIcon);
	Icon->SetBrushSize(FVector2D(64, 64));

	UButton* BaseButton = NewObject<UButton>(this, UButton::StaticClass());
	FButtonStyle Style;
	Style.Normal.SetResourceObject(ButtonTexture);
	Style.Hovered.SetResourceObject(ButtonTexture);
	Style.Pressed.SetResourceObject(ButtonTexture);
	Style.Normal.TintColor = FSlateColor({ 255, 255, 255, 0 });
	Style.Hovered.TintColor = FSlateColor({ 255, 255, 255, 200 });
	Style.Pressed.TintColor = FSlateColor({ 255, 255, 255, 200 });
	BaseButton->SetStyle(Style);
	AddChild(BaseButton);

	UHorizontalBox* Entry = NewObject<UHorizontalBox>(this, UHorizontalBox::StaticClass());
	BaseButton->AddChild(Entry);

	USpacer* Spacer = NewObject<USpacer>(this, USpacer::StaticClass());
	Spacer->SetSize(FVector2D(25, 0));

	Entry->AddChild(Icon);
	Entry->AddChild(Spacer);
	Entry->AddChild(Name);

	Cast<UHorizontalBoxSlot>(Entry->GetSlots()[0])->SetPadding(FMargin(24, 24));
	Cast<UHorizontalBoxSlot>(Entry->GetSlots().Last())->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
}


void UAbilityListUI::ClearList()
{
	ClearChildren();
}
