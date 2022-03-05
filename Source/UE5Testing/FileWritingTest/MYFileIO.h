// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "Serialization/BufferArchive.h"
#include "UObject/Object.h"
#include "MYFileIO.generated.h"

/**
 * 
 */
UCLASS()
class UE5TESTING_API UMYFileIO : public UObject
{
	GENERATED_BODY()
public:
	static void SaveGame();
private:
	static void SaveLoadData(FArchive& Ar, FString& Name, FVector& Vector, TArray<FRotator>& RotatorArray);
	static bool SaveToFile(const FString& FullFilePath);
	static bool LoadFromFile(const FString& FullFilePath);
	inline static FString str{"John Wilcock"};
	inline static FVector vec{1,2,3};
	inline static TArray<FRotator> rot{FRotator(1,1,1),FRotator(2,2,2)};
};
