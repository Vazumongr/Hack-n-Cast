// Copyright Troy Records Jr. 2022

#pragma once

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	OneHanded,
	TwoHanded,
	DualWield
};

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Common,
	Rare,
	Epic,
	Legendary
};