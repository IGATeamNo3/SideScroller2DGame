// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScroller2DGame.h"
#include "AutoAdjustmentCameraActor.h"




AAutoAdjustmentCameraActor::AAutoAdjustmentCameraActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAutoAdjustmentCameraActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdatePlayersLocation();
	UpdateCameraTransform();
}

void AAutoAdjustmentCameraActor::BeginPlay()
{
	Super::BeginPlay();

}

void AAutoAdjustmentCameraActor::UpdateCameraTransform()
{
	FVector  Center= FVector((GetMaxXPoint()+GetMinXPoint()).X*0.5f, 
		(GetMaxYPoint() + GetMinYPoint()).Y*0.5f,
		(GetMaxZPoint() + GetMinZPoint()).Z*0.5f);
	SetActorLocation(Center);
}

int32 AAutoAdjustmentCameraActor::GetLocalGamePlayerNumber()
{
	TArray<ULocalPlayer*> LocalPlayers = GetLocalGamePlayers();
	return LocalPlayers.Num();
}

void AAutoAdjustmentCameraActor::SetViewTargetToThisCamera()
{
	TArray<ULocalPlayer*> LocalPlayers = GetLocalGamePlayers();
	for (int8 i = 0; i < LocalPlayers.Num(); i++)
	{
		LocalPlayers[i]->PlayerController->SetViewTargetWithBlend(this);
	}

}

void AAutoAdjustmentCameraActor::SetViewTargetToThisCamera(APlayerController* PlayerController)
{
	if (PlayerController)
	{
		PlayerController->SetViewTargetWithBlend(this);
	}
}

FVector AAutoAdjustmentCameraActor::GetMaxXPoint()
{
	FVector ret;
	for (auto vector:PlayersLocation)
	{
		if (vector.X > ret.X)
		{
			ret = vector;
		}
		
	}
	return ret;
}

FVector AAutoAdjustmentCameraActor::GetMinXPoint()
{
	FVector ret;
	for (auto vector : PlayersLocation)
	{
		if (vector.X < ret.X)
		{
			ret = vector;
		}

	}
	return ret;
}

FVector AAutoAdjustmentCameraActor::GetMaxYPoint()
{
	FVector ret;
	for (auto vector : PlayersLocation)
	{
		if (vector.Y > ret.Y)
		{
			ret = vector;
		}

	}
	return ret;
}

FVector AAutoAdjustmentCameraActor::GetMinYPoint()
{
	FVector ret;
	for (auto vector : PlayersLocation)
	{
		if (vector.Y < ret.Y)
		{
			ret = vector;
		}

	}
	return ret;
}

FVector AAutoAdjustmentCameraActor::GetMaxZPoint()
{
	FVector ret;
	for (auto vector : PlayersLocation)
	{
		if (vector.Z > ret.Z)
		{
			ret = vector;
		}

	}
	return ret;
}

FVector AAutoAdjustmentCameraActor::GetMinZPoint()
{
	FVector ret;
	for (auto vector : PlayersLocation)
	{
		if (vector.Z < ret.Z)
		{
			ret = vector;
		}

	}
	return ret;
}

void AAutoAdjustmentCameraActor::UpdatePlayersLocation()
{
	PlayersLocation.Reset();
	TArray<ULocalPlayer*> LocalPlayers = GetLocalGamePlayers();
	for (int8 i = 0; i < LocalPlayers.Num(); i++)
	{	
		if (LocalPlayers[i] && LocalPlayers[i]->PlayerController)
		{
			APawn* pPawn = LocalPlayers[i]->PlayerController->GetPawn();
			if (pPawn)
			{
				PlayersLocation.Add(pPawn->GetActorLocation());
			}
		}
		
	}
}

const TArray<ULocalPlayer*> AAutoAdjustmentCameraActor::AAutoAdjustmentCameraActor::GetLocalGamePlayers() const
{
	return GEngine->GetGamePlayers(GetWorld());
}
