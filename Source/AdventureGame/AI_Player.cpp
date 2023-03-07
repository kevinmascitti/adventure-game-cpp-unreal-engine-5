// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Player.h"

void UAI_Player::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	Actor=GetOwningActor();
	if(Actor)
	{
		PlayerBase=Cast<APlayerBase>(Actor);
		if(PlayerBase)
		{
			Speed = PlayerBase->VSpeed;
			Crouch = PlayerBase->VCrouch;
			IsInAir = PlayerBase->VIsInAir;
		}
	}
}