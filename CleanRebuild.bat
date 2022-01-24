@rd /s /q %cd%\Intermediate
@rd /s /q %cd%\Binaries
@rd /s /q %cd%\.vs
@rd /s /q %cd%\DerivedDataCache
@del /q %cd%\*.sln

set MyUVS="C:\Program Files (x86)\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe"
set MyUBT="C:/UnrealSourceBuilds/UE5Source/Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.exe"

set MyFullPath="%cd%\UE5Testing"

%MyUVS% /projectfiles %MyFullPath%.uproject