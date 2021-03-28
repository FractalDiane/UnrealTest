// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimation.h"

bool UCharacterAnimation::GetBool(FName Name)
{
	FBoolProperty* Prop = FindFProperty<FBoolProperty>(Parent->GetClass(), Name);
	return Prop->GetPropertyValue_InContainer(Parent);
}


void UCharacterAnimation::SetBool(FName Name, bool Value)
{
	FBoolProperty* Prop = FindFProperty<FBoolProperty>(Parent->GetClass(), Name);
	Prop->SetPropertyValue_InContainer(Parent, Value);
}


int UCharacterAnimation::GetInt(FName Name)
{
	FIntProperty* Prop = FindFProperty<FIntProperty>(Parent->GetClass(), Name);
	return Prop->GetPropertyValue_InContainer(Parent);
}


void UCharacterAnimation::SetInt(FName Name, int Value)
{
	FIntProperty* Prop = FindFProperty<FIntProperty>(Parent->GetClass(), Name);
	Prop->SetPropertyValue_InContainer(Parent, Value);
}


float UCharacterAnimation::GetFloat(FName Name)
{
	FFloatProperty* Prop = FindFProperty<FFloatProperty>(Parent->GetClass(), Name);
	return Prop->GetPropertyValue_InContainer(Parent);
}


void UCharacterAnimation::SetFloat(FName Name, float Value)
{
	FFloatProperty* Prop = FindFProperty<FFloatProperty>(Parent->GetClass(), Name);
	Prop->SetPropertyValue_InContainer(Parent, Value);
}
