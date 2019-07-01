#pragma once

#include "CoreMinimal.h"
#include "LinkedListNode.h"
#include "Round.generated.h"

class AUnitBase;

//Round Information specific for the units
USTRUCT(BlueprintType)
struct FUnitRoundInfo
{
	GENERATED_USTRUCT_BODY()

	//Reference for the Unit
	UPROPERTY(BluePrintReadOnly, meta = (ToolTip = "Reference for the Unit"), category = "TurnSystem")
		AUnitBase* UnitRef = NULL;

	//Adjusted initiative for this Round
	UPROPERTY(BluePrintReadWrite, meta = (ToolTip = "Adjusted initiative for this Round"), category = "TurnSystem")
		int RoundInitiative = 0;

	//Whether the Unit had a turn
	UPROPERTY(BluePrintReadWrite, meta = (ToolTip = "Whether the Unit had a turn"), category = "TurnSystem")
		bool HadTurn = false;


	//Default constructor
	FUnitRoundInfo() {};

	//Constructor
	FUnitRoundInfo(AUnitBase* a_UnitRef, int a_BaseInitiative, bool a_HadTurn = false)
	{
		UnitRef = a_UnitRef;
		RoundInitiative = a_BaseInitiative;
    HadTurn = a_HadTurn;
	}
};


/*
 The Round class is a child of node, used to keep track of turn order and potential other modifiers for the Round
 A Round ends when all units have had their turn and then next Round starts
 */
UCLASS(Blueprintable)
class PROJECTRAGNAROK_API URound : public ULinkedListNode
{
	GENERATED_BODY()
  
public:

	//Constructor
	URound();

	//Destructor
	virtual ~URound();

	//Sorts the round based on RoundInitiative
	void SortRound();

	//Removes the unit from the turn order
	//@param[in] a_Unit : The unit that will be removed
	void RemoveUnitFromTurnOrder(AUnitBase* a_Unit);

public:

	//Turn order of this round
	TArray<FUnitRoundInfo> TurnOrder;
};
