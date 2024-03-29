#pragma once

#include "CoreMinimal.h"
#include "Object.h"
#include "LinkedListNode.generated.h"

/*
 The nodes used in the CircularLinkedList.h
*/
UCLASS(Blueprintable)
class PROJECTRAGNAROK_API ULinkedListNode : public UObject
{
	GENERATED_BODY()
  
public:
	//Constructor
	ULinkedListNode();

	//Destructor
	virtual ~ULinkedListNode();

	//Pointer to the next node in the list
	UPROPERTY()
	ULinkedListNode* NextNode = NULL;
  
private:

};
