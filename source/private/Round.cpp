// Fill out your copyright notice in the Description page of Project Settings.

#include "Round.h"
#include "UnitBase.h"

//Constructor
URound::URound()
{
}

//Destructor
URound::~URound()
{
}

//Sorts the round based on RoundInitiative in descending order
void URound::SortRound()
{
	//Sorts the array on the key values in descending order
	TurnOrder.Sort([](FUnitRoundInfo A, FUnitRoundInfo B) 
	{
		return A.RoundInitiative > B.RoundInitiative;
	});
}

//Removes the unit from the map
//@param[in] a_Unit : The unit that will be removed
void URound::RemoveUnitFromTurnOrder(AUnitBase* a_Unit)
{
	for (auto &iter : TurnOrder)
	{
		//Checks if the map value is equal to the unit reference given
		if (iter.UnitRef == a_Unit)
		{
			TurnOrder.(*iter);
			SortRound();
			return;
		}
	}
}
