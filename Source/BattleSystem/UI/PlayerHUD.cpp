// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include <Components/TextBlock.h>
#include <Components/Image.h>

void UPlayerHUD::ShowInteractHUD(bool Show)
{
	if (Show) {
		PlayAnimation(AnimInteractFadein);
	}
	else {
		PlayAnimation(AnimInteractFadeout);
	}
}


void UPlayerHUD::SetInteractPrompt(const FText& Prompt) {
	InteractText->SetText(Prompt);
}


void UPlayerHUD::SetInteractButton(Button _Button)
{
	InteractButton->SetBrushFromTexture(ButtonImages[_Button]);
}
