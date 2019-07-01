#include "CircularLinkedList.h"
#include "LinkedListNode.h"

//Constructor
UCircularLinkedList::UCircularLinkedList()
{
	Head = NULL;
}

//Destructor
UCircularLinkedList::~UCircularLinkedList()
{

}

//Gets Head of the list
//@Return : returns the Head of the list, returns NULL if the list is empty
ULinkedListNode* UCircularLinkedList::GetHead()
{
	return Head;
}

//Whether the list is empty
//@Return : true if it is empty, false if it is not empty
bool UCircularLinkedList::IsEmpty()
{
	if (Head == NULL)
	{
		return true;
	}
	return false;
}

//Gets last node in the list
//@Return : returns last node in the list, returns NULL if the list is empty
ULinkedListNode* UCircularLinkedList::GetLast()
{
	if (!IsEmpty())
	{
		ULinkedListNode* tempptr = Head;

		while (tempptr->NextNode != Head)
		{
			tempptr = tempptr->NextNode;
		}
		return tempptr;
	}
	else
	{
		return NULL;
	}
}

//Adds node at the front of the list making it the new Head
//@Param[in] a_Node : Node that will be added
void UCircularLinkedList::AddAtFront(ULinkedListNode * a_Node)
{
	if (IsEmpty())
	{
		Head = a_Node;
		a_Node->NextNode = Head;
	}
	else
	{
		a_Node->NextNode = Head;
		Head = a_Node;
		GetLast()->NextNode = Head;
	}
}

//Adds node at the end of the list making it point to the Head
//@Param[in] a_Node : Node that will be added
void UCircularLinkedList::AddAtEnd(ULinkedListNode * a_Node)
{
	if (IsEmpty())
	{
		Head = a_Node;
		a_Node->NextNode = Head;
	}
	else
	{
		GetLast()->NextNode = a_Node;
		a_Node->NextNode = Head;
	}
}
