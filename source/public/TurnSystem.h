// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Round.h"
#include "Engine/World.h"
#include "TurnSystem.generated.h"


class AUnitBase;
class UCircularLinkedList;

/*
The TurnSystem keeps track of the turn order with use of nodes called rounds
A round ends when all units have had their turn ones
*/
UCLASS()
class PROJECTRAGNAROK_API ATurnSystem : public AActor
{
	GENERATED_BODY()

public:


	//Sets up the rounds to start the turn order
	//@Param[in] a_UnitBase : List of the units that needs to be in the turn order
	UFUNCTION(BlueprintCallable, Category = "TurnSystem")
		void SetUpRounds(TArray<AUnitBase*> a_UnitBase);

	//Starts turn of the next unit in the turn order
	void StartTurn();

	//Ends turn of the current unit and then calls start turn
	UFUNCTION(BlueprintCallable, Category = "TurnSystem")
		void EndTurn();

	//Moves the CurrentRound pointer to the next round
	void NextRound();

	//Starts the CurrentRound and starts the first unit in the turn order
	UFUNCTION(BlueprintCallable, Category = "TurnSystem")
		void StartRound();

	//Resets the CurrentRound to its default values and then ends the CurrentRound
	void EndRound();


	//Gets the round order of any round
	//@Param[in] a_Round : What round you want to get, round 0 is current round, round 1 is the round after the current round,
	//round 2 is 2 rounds after the current round, etc...
	//@Param[out] RoundOrder : Sorted list containing the UnitRoundInfo
	UFUNCTION(BlueprintCallable, Category = "TurnSystem")
		void GetRoundOrder(int a_Round, TArray<FUnitRoundInfo>&RoundOrder);

	//Updates the turn order UI
	UFUNCTION(BlueprintImplementableEvent, Category = "TurnSystem")
		void UpdateTurnOrderUI();

	//Called at the start of each round
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Start Round"), Category = "TurnSystem")
		void ReceiveStartRound();

	//Called at the end of each round
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "End Round"), Category = "TurnSystem")
		void ReceiveEndRound();

	//Called at the start of a new unit's turn
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Next Turn"), Category = "TurnSystem")
		void ReceiveNextTurn(AUnitBase* NextUnit);

	//Adds initiative to the given unit on the given round and sorts the turn order
	//@Param[in] a_Roundptr : Pointer to the round you want to add initiative to
	//@Param[in] a_AddedInitiative : How much initiative will be added
	//@Param[in] a_Unit : Pointer to the unit that will have the initiative added
	void AddIntiative(URound* a_Roundptr, int a_AddedInitiative, AUnitBase* a_Unit);

	//Sorts the turn order of all the rounds
	void SortAllRounds();

	//Removes a unit form all the rounds
	//@Param[in] a_Unit : Pointer to the unit that will be removed
	UFUNCTION(BlueprintCallable, Category = "TurnSystem")
		void RemoveUnitFromAllRounds(AUnitBase* a_Unit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

//Pointer to unit that has its turn
	UPROPERTY(BluePrintReadOnly, category = "TurnSystem")
		AUnitBase* CurrentUnit;


private:

//The Current Round pointer
	UPROPERTY(BluePrintReadOnly, meta = (AllowPrivateAccess = "true"), category = "TurnSystem")
		URound* CurrentRound;

	//Pointer to the Round list that is created at the start
	UPROPERTY()
		UCircularLinkedList* RoundList;

	UPROPERTY(EditAnywhere, meta = (ToolTip = "How many rounds will be created, useful for how many rounds you want initiative debuffs to be applied", AllowPrivateAccess = "true"), category = "TurnSystem")
		int RoundsCreated = 5;

	//Creates the URound objects
	void CreateRounds();



};
