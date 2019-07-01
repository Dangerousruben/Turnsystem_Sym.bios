#pragma once

#include "CoreMinimal.h"
#include "Object.h"
#include "CircularLinkedList.generated.h"

//Forward Declaration
class ULinkedListNode;

UCLASS(Blueprintable)
class PROJECTRAGNAROK_API UCircularLinkedList : public UObject
{
	GENERATED_BODY()

public:
	//Constructor
	UCircularLinkedList();

	//Destructor
	virtual ~UCircularLinkedList();

	//Gets Head of the list
	//@Return : returns the Head of the list, returns NULL if the list is empty
	ULinkedListNode* GetHead();

	//Whether the list is empty
	//@Return : true if it is empty, false if it is not empty
	bool IsEmpty();

	//Adds node at the front of the list making it the new Head
	//@Param[in] a_Node : Node that will be added
	void AddAtFront(ULinkedListNode* a_Node);

	//Adds node at the end of the list making it point to the Head
	//@Param[in] a_Node : Node that will be added
	void AddAtEnd(ULinkedListNode* a_Node);


	//Gets last node in the list
	//@Return : returns last node in the list, returns NULL if the list is empty
	ULinkedListNode* GetLast();

private:
	UPROPERTY()
	ULinkedListNode* Head;

};
