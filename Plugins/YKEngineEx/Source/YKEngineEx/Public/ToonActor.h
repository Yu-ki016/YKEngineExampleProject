// ToonActor

#pragma once

#include "CoreMinimal.h"
#include "Toon/ToonActorBase.h"
#include "ToonActor.generated.h"

class AToonActorManager;

UCLASS(Blueprintable)
class YKENGINEEX_API AToonActor : public AToonActorBase
{
	GENERATED_BODY()

public:
	AToonActor();
	
protected:
	// Called when the game starts or when spawned
	virtual void PostInitProperties() override;

public:
	virtual void Destroyed() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Toon)
	AToonActorManager* ToonActorManager;

	UFUNCTION(BlueprintCallable, Category="Rendering|Toon")
	void UpdateID();

	UFUNCTION(BlueprintCallable, Category="Rendering|Toon")
	void AddToManager();

	UFUNCTION(BlueprintCallable, Category="Rendering|Toon")
	virtual void SetToonID(int NewValue) override;
};
