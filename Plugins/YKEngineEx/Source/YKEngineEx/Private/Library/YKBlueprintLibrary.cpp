// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/YKBlueprintLibrary.h"
#include "Editor/UnrealEd/Classes/Editor/EditorEngine.h"
#include "LevelEditorViewport.h"

bool UYKBlueprintLibrary::GetStaticSwitchParameterValue( UMaterialInterface* InMaterial, FName ParameterName , bool &bFoundParam)
{
	FGuid ParamGUID;
	bool OutValue = false;
	bFoundParam = false;
	
	if (!InMaterial)
	{
		return OutValue;
	}

	if (UMaterial* Material = Cast<UMaterial>(InMaterial))
	{
		bFoundParam = Material->GetStaticSwitchParameterDefaultValue(ParameterName, OutValue, ParamGUID);
	}
	if (UMaterialInstance* MaterialInstance = Cast<UMaterialInstance>(InMaterial))
	{
		bFoundParam = MaterialInstance->GetStaticSwitchParameterDefaultValue(ParameterName, OutValue, ParamGUID);
	}
	
	return OutValue;
}

float UYKBlueprintLibrary::GetScalarParameterValue( UMaterialInterface* InMaterial, FName ParameterName,
	bool& bFoundParam )
{
	float OutValue = 0;
	bFoundParam = false;
	
	if (!InMaterial)
	{
		return OutValue;
	}

	if (UMaterial* Material = Cast<UMaterial>(InMaterial))
	{
		bFoundParam = Material->GetScalarParameterDefaultValue(ParameterName, OutValue);
	}
	if (UMaterialInstance* MaterialInstance = Cast<UMaterialInstance>(InMaterial))
	{
		bFoundParam = MaterialInstance->GetScalarParameterValue(ParameterName, OutValue);
	}
	
	return OutValue;
}

FLinearColor UYKBlueprintLibrary::GetVectorParameterValue( UMaterialInterface* InMaterial, FName ParameterName,
	bool& bFoundParam )
{
	FLinearColor OutValue = FLinearColor::Black;
	bFoundParam = false;
	
	if (!InMaterial)
	{
		return OutValue;
	}

	if (UMaterial* Material = Cast<UMaterial>(InMaterial))
	{
		bFoundParam = Material->GetVectorParameterDefaultValue(ParameterName, OutValue);
	}
	if (UMaterialInstance* MaterialInstance = Cast<UMaterialInstance>(InMaterial))
	{
		bFoundParam = MaterialInstance->GetVectorParameterValue(ParameterName, OutValue);
	}
	
	return OutValue;
}
UTexture* UYKBlueprintLibrary::GetTextureParameterValue( UMaterialInterface* InMaterial, FName ParameterName,
	bool& bFoundParam )
{
	UTexture* OutValue = nullptr;
	bFoundParam = false;
	
	if (!InMaterial)
	{
		return OutValue;
	}

	if (UMaterial* Material = Cast<UMaterial>(InMaterial))
	{
		bFoundParam = Material->GetTextureParameterDefaultValue(ParameterName, OutValue);
	}
	if (UMaterialInstance* MaterialInstance = Cast<UMaterialInstance>(InMaterial))
	{
		bFoundParam = MaterialInstance->GetTextureParameterValue(ParameterName, OutValue);
	}
	
	return OutValue;
}

bool UYKBlueprintLibrary::GetViewportCameraInfo( FVector& CameraLocation, FRotator& CameraRotation )
{
	bool RetVal = false;
	CameraLocation = FVector::ZeroVector;
	CameraRotation = FRotator::ZeroRotator;

#if WITH_EDITOR
	if (GEditor)
	{
		for (FLevelEditorViewportClient* LevelVC : GEditor->GetLevelViewportClients())
		{
			if (LevelVC && LevelVC->IsPerspective())
			{
				CameraLocation = LevelVC->GetViewLocation();
				CameraRotation = LevelVC->GetViewRotation();
				RetVal = true;
				break;
			}
		}
	}
#endif

	return RetVal;
}
