// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "YKBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class YKENGINEEX_API UYKBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "YKEngine|Material")
	static bool GetStaticSwitchParameterValue(UMaterialInterface* InMaterial, FName ParameterName, bool &bFoundParam);

	UFUNCTION(BlueprintCallable, Category = "YKEngine|Material")
	static float GetScalarParameterValue(UMaterialInterface* InMaterial, FName ParameterName, bool &bFoundParam);

	UFUNCTION(BlueprintCallable, Category = "YKEngine|Material")
	static FLinearColor GetVectorParameterValue(UMaterialInterface* InMaterial, FName ParameterName, bool &bFoundParam);

	UFUNCTION(BlueprintCallable, Category = "YKEngine|Material")
	static UTexture* GetTextureParameterValue(UMaterialInterface* InMaterial, FName ParameterName, bool &bFoundParam);

	UFUNCTION(BlueprintCallable, Category = "YKEngine|Camera")
	static bool GetViewportCameraInfo(FVector& CameraLocation, FRotator& CameraRotation);
};
