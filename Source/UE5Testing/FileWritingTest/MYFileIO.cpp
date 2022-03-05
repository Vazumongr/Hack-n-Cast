// Troy Records Jr. 2021


#include "MYFileIO.h"

#include "Serialization/BufferArchive.h"


void UMYFileIO::SaveGame()
{
	const FString& ProjectSavedDirectory = FPaths::ProjectSavedDir();
	const FString GameSavesDirectory = ProjectSavedDirectory + "GameSaves/";
	const FString SaveName = "testsave.save";
	const FString FullPath = GameSavesDirectory + SaveName;
	SaveToFile(FullPath);
	LoadFromFile(FullPath);
}

void UMYFileIO::SaveLoadData(FArchive& Ar, FString& Name, FVector& Vector, TArray<FRotator>& RotatorArray)
{
	Ar << Name;
	Ar << Vector;
	Ar << RotatorArray;
}

bool UMYFileIO::SaveToFile(const FString& FullFilePath)
{
	FBufferArchive Ar;
	SaveLoadData(Ar, str,vec,rot);
	if(Ar.Num() <= 0) return false;
	if(FFileHelper::SaveArrayToFile(Ar,*FullFilePath))
	{
		Ar.FlushCache();
		Ar.Empty();
		UE_LOG(LogTemp, Warning, TEXT("SAVE SUCCESS"));
		return true;
	}
	
	Ar.FlushCache();
	Ar.Empty();
	return false;
}

bool UMYFileIO::LoadFromFile(const FString& FullFilePath)
{
	TArray<uint8> bytes;
	if(!FFileHelper::LoadFileToArray(bytes,*FullFilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("LOADING FILE FAILED"));
		return false;
	}

	if(bytes.Num() <= 0) return false; // Nothing laoded
	
	FMemoryReader Ar(bytes,true);
	Ar.Seek(0);
	FString fs;
	FVector fv;
	TArray<FRotator> tfr;
	SaveLoadData(Ar,fs,fv,tfr);

	Ar.FlushCache();

	bytes.Empty();
	Ar.Close();

	return true;
}
