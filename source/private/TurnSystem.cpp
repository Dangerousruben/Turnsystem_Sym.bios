#include "TurnSystem.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

#include "CircularLinkedList.h"
#include "Round.h"
#include "UnitBase.h"


//Called when the game starts or when spawned
void ATurnSystem::BeginPlay()
{
	CreateRounds();
	Super::BeginPlay();
}

//Creates the URound objects
void ATurnSystem::CreateRounds()
{
	RoundList = NewObject<UCircularLinkedList>();

	for (int i = 0; i < RoundsCreated; i++)
	{
		RoundList->AddAtEnd(NewObject<URound>());
	}

	CurrentRound = Cast<URound>(RoundList->GetHead());
}

//Starts turn of the next unit in the turn order
void ATurnSystem::StartTurn()
{
	if (CurrentRound)
	{
		for (auto &iterator : CurrentRound->TurnOrder)
		{
			if (IsValid(iterator.UnitRef))
			{
				if (iterator.HadTurn == false && iterator.UnitRef->GetState() != EMechStateEnum::Dying)
				{
					iterator.UnitRef->StartTurn();

					CurrentUnit = iterator.UnitRef;

					UpdateTurnOrderUI();

					ReceiveNextTurn(CurrentUnit);

					return;
				}
			}
		}

		//Since every has had their turn we end the round
		EndRound();
	}
}

//Ends turn of the current unit and then calls start turn
void ATurnSystem::EndTurn()
{
	if (CurrentRound)
	{
		for (auto &iter : CurrentRound->TurnOrder)
		{
			if (iter.UnitRef == CurrentUnit)
			{
				iter.HadTurn = true;
			}
		}

		CurrentUnit->EndTurn();
    
		StartTurn();
	}
}

//Moves the CurrentRound pointer to the next round
void ATurnSystem::NextRound()
{
	CurrentRound = Cast<URound>(CurrentRound->NextNode);

	if (CurrentRound)
	{
		StartRound();
	}
}

//Starts the CurrentRound and starts the first unit in the turn order
void ATurnSystem::StartRound()
{
	ReceiveStartRound();
	StartTurn();
}

//Resets the CurrentRound to its default values and then ends the CurrentRound
void ATurnSystem::EndRound()
{
	if (CurrentRound)
	{
    //Reset the round
		for (auto &iter : CurrentRound->TurnOrder)
		{
			iter.RoundInitiative = iter.UnitRef->MechStats.Initiative;

			iter.HadTurn = false;
		}

		CurrentRound->SortRound();

		ReceiveEndRound();

		NextRound();
	}
}

//Sets up the rounds to start the turn order
//@Param[in] a_UnitBase : List of the units that needs to be in the turn order
void ATurnSystem::SetUpRounds(TArray<AUnitBase*> a_UnitBase)
{
	ULinkedListNode* round = RoundList->GetHead();
	if (round)
	{
		for (uint8 i = 0; i < a_UnitBase.Num(); i++)
		{
			do
			{
				round->TurnOrder.Add(FUnitRoundInfo(a_UnitBase[i], a_UnitBase[i]->MechStats.Initiative));
				round = round->NextNode;
			} while (round != RoundList->GetHead());

		}
		SortAllRounds();
	}
}

//Gets the round order of any round
//@Param[in] Round : What round you want, round 0 is the current round, round 1 is the round after the current round,
//round 2 is 2 rounds after the current round, etc...
//@Param[out] RoundOrder : Sorted list containing the UnitRoundInfo
void ATurnSystem::GetRoundOrder(int a_Round, TArray<FUnitRoundInfo>&RoundOrder)
{
	if (CurrentRound)
	{
		URound* temproundptr = CurrentRound;

		for (int i = a_Round; i > 0; i--)
		{
			temproundptr = Cast<URound>(temproundptr->NextNode);
		}

		for (auto &iter : temproundptr->TurnOrder)
		{
			RoundOrder.Add(iter);
		}
	}
}

//Sorts the turn order of all the rounds
void ATurnSystem::SortAllRounds()
{
	ULinkedListNode* round = RoundList->GetHead();
	if (round)
	{
		do
		{
			round->SortRound();
			round = Cast<URound>(round->NextNode);
		} while (round != RoundList->GetHead());
	}
}

//Removes a unit form all the rounds
//@Param[in] a_Unit : Pointer to the unit that will be removed
void ATurnSystem::RemoveUnitFromAllRounds(AUnitBase* a_Unit)
{
	if (CurrentRound && a_Unit)
	{
		//If the Unit has its turn, end it
		if (a_Unit == CurrentUnit)
		{
			EndTurn();
		}

		URound* round = CurrentRound;
		do
		{
			round->RemoveUnitFromTurnOrder(a_Unit);

			round->SortRound();
			round = Cast<URound>(round->NextNode);
		} while (round != CurrentRound);

		UpdateTurnOrderUI();
	}
}

//Adds initiative to the given unit on the given round and sorts the turn order
//@Param[in] a_Roundptr : Pointer to the round you want to add initiative to
//@Param[in] a_AddedInitiative : How much initiative will be added
//@Param[in] a_Unit : Pointer to the unit that will have the initiative added
void ATurnSystem::AddIntiative(URound* a_Roundptr, int a_AddedInitiative, AUnitBase* a_Unit)
{
	for (auto &iter : a_Roundptr->TurnOrder)
	{
		if (iter.UnitRef == a_Unit)
		{
			iter.RoundInitiative += a_AddedInitiative;

			return;
		}
	}
}
