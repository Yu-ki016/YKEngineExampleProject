// ToonActor

#include "ToonActor.h"

#include "ToonActorManager.h"
#include "Kismet/GameplayStatics.h"
#include "Toon/ToonActorBase.h"

AToonActor::AToonActor()
{
	if ( !AToonActorManager::IsToonActorValid(this) ) return;
	
	UWorld* World = GetWorld();
	ULevel* Level = GetLevel();
	if (!World || !Level) return;

	TArray<AActor*> ManagersInWorld;
	UGameplayStatics::GetAllActorsOfClass(World, AToonActorManager::StaticClass(), ManagersInWorld);
	if (!ToonActorManager)
	{
		if (ManagersInWorld.IsEmpty())
		{
			ToonActorManager = World->SpawnActor<AToonActorManager>(AToonActorManager::StaticClass());
		}
		else
		{
			ToonActorManager = Cast<AToonActorManager>(ManagersInWorld[0]);
		}
	}
	
	// 删除多余的Manager
	if (ManagersInWorld.Num() > 1)
	{
		for(int i = 0; i < ManagersInWorld.Num(); i++)
		{
			if (AActor* Manger = ManagersInWorld[i]; Manger->IsValidLowLevel())
			{
				if (ToonActorManager != Manger)	Manger->Destroy();
			}
		}
	}
}

void AToonActor::UpdateID()
{
	if (ToonActorManager && ToonActorManager->ToonActorList.Num())
	{
		SetToonID(ToonActorManager->ToonActorList.Find(this));
	}
}

// 保证有被ToonActorManager管理到的ToonActor最小ID为1
void AToonActor::SetToonID(int NewValue)
{
	Super::SetToonID(NewValue + 1);
}

void AToonActor::AddToManager()
{
	if (ToonActorManager)
	{
		ToonActorManager->AddToonActor(this);
	}
}

void AToonActor::PostInitProperties()
{
	Super::PostInitProperties();
	if (ToonActorManager)
	{
		ToonActorManager->AddToonActor(this);
	}
}

void AToonActor::Destroyed()
{
	UE_LOG(LogTemp, Log, TEXT("BeginToonActorDestoryed:%1s"), *this->GetName())
	if (ToonActorManager)
	{
		ToonActorManager->RemoveToonActor(this);
	}
	Super::Destroyed();
}
