// Copyright Troy Records Jr. 2022
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "MYWeaponSMADA.generated.h"

class UStaticMesh;

/**
 * DataAsset for storing static mesh and weapon rotation data for weapons.
 */
UCLASS(BlueprintType)
class UE5TESTING_API UMYWeaponSMADA : public UDataAsset
{
public:
	FRotator GetPrimaryMeshSpawnRotation() const
	{
		return PrimaryMeshSpawnRotation;
	}

	UStaticMesh* GetPrimaryStaticMesh() const
	{
		return PrimaryStaticMesh;
	}

	FRotator GetSecondaryMeshSpawnRotation() const
	{
		return SecondaryMeshSpawnRotation;
	}

	UStaticMesh* GetSecondaryStaticMesh() const
	{
		return SecondaryStaticMesh;
	}

private:
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FRotator PrimaryMeshSpawnRotation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UStaticMesh* PrimaryStaticMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FRotator SecondaryMeshSpawnRotation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UStaticMesh* SecondaryStaticMesh;
};