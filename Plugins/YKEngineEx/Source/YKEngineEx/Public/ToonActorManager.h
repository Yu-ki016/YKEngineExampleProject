// ToonActor

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Toon/ToonActorBase.h"
#include "ToonActorManager.generated.h"

class AToonActorBase;
/**
 * 维护场景中的ToonActor列表，为ToonActor设置ID
 */
UCLASS()
class YKENGINEEX_API AToonActorManager : public AInfo
{
	GENERATED_BODY()

	AToonActorManager();
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Toon)
	TArray<AToonActorBase*> ToonActorList;

public:
	static bool IsToonActorValid(AToonActorBase* ToonActor)
	{
		if (!ToonActor || !ToonActor->GetWorld()) return false;
		if (ToonActor->HasAnyFlags(RF_Transient)) return false;
		return true;
	};
	
	void UpdateToonActorList();

	void AddToonActor(AToonActorBase* ToonActor);

	void RemoveToonActor(AToonActorBase* ToonActor);

private:
	void RemoveNull();
};
