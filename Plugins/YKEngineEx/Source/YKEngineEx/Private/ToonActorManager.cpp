// ToonActor


#include "ToonActorManager.h"

#include "Kismet/GameplayStatics.h"

AToonActorManager::AToonActorManager()
{
	this->UpdateToonActorList();
}

void AToonActorManager::UpdateToonActorList()
{
	const UWorld* World = GetWorld();
	
	if (!World) return;
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(World, AToonActorBase::StaticClass(), Actors);

	for (AActor* Actor : Actors)
	{
		if (AToonActorBase* ToonActor = Cast<AToonActorBase>(Actor); ToonActor->IsValidLowLevel())
		{
			AddToonActor(ToonActor);
		}
	}
}

void AToonActorManager::AddToonActor(AToonActorBase* ToonActor)
{
	if (!IsToonActorValid(ToonActor)) return;
	
	if (const int Index = ToonActorList.Find(ToonActor) != INDEX_NONE)
	{
		UE_LOG(LogTemp, Log, TEXT("Have Same Actor, Same Actor Index:%i"), Index)
		return;
	}
	
	const int32 ActorIndex = ToonActorList.Add(ToonActor);
	ToonActor->SetToonID(ActorIndex);

	UE_LOG(LogTemp, Log, TEXT("AddActor:%1s,Actor Name:%1s, ID%i"), *ToonActor->GetActorLabel(), *ToonActor->GetFName().ToString(), ActorIndex)
}

// 清除空指针
void AToonActorManager::RemoveNull()
{
	ToonActorList.RemoveAll([](const AToonActorBase* Actor){ return Actor == nullptr; });
};

void AToonActorManager::RemoveToonActor(AToonActorBase* ToonActor)
{
	if (!IsToonActorValid(ToonActor) || ToonActorList.Num() == 0)
	{
		return;
	}

	RemoveNull();
	const int32 Index = ToonActorList.Find(ToonActor);
	if (Index != INDEX_NONE)
	{
		ToonActorList.RemoveAt(Index);
		// 去掉列表中的一个ToonActor之后，列表后面的Actor的ID重新更新
		for (int i = Index; i < ToonActorList.Num(); i++)
		{
			checkf(ToonActorList[i], TEXT("ToonActorList Index %d Is null Pointer"), i)
			ToonActorList[i]->SetToonID(i);
		}
	}
}
