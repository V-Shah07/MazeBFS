#pragma once
#include <stdlib.h>
#include <stdio.h>
struct node
{
	node* next, * prev;
	int value;
};
struct LinkedList
{

private:
	int curNode;
public:
	node* head, * tail;

	node* addToTail(int val)
	{
		node* new_node = (node*)malloc(sizeof(node));

		new_node->value = val;
		new_node->next = NULL;
		new_node->prev = tail;

		if (tail != NULL)
		{
			tail->next = new_node;
		}

		if (head == NULL) //head being NULL means that the list is empty, and this is the first node getting pushed on. 
									 //Therefore, must make head AND tail point to it.
		{
			head = new_node;
		}

		tail = new_node;
		++curNode;
		return new_node;
	}
	node* removeFromTail()
	{
		node* returnNode = tail;

		tail = tail->prev;

		if (tail != NULL)
		{
			tail->next = NULL;
		}
		else //tail is NULL. That means that when setting tail to previous, it became NULL, meaning that the one we are trying to pop is the last element. 
			  //Therefore, we have to set both the head to NULL as well to make sure the list is represented as empty!
		{
			head = NULL;
		}
		--curNode;
		return returnNode;
	}
	node* removeFromHead()
	{
		node* returnNode = head;

		head = head->next;

		if (head != NULL)
		{
			head->prev = NULL;
		}
		else //head is null, this means when setting the head to the next element, it became NULL, meaning the one we are trying to dequeue is the last element.
			 //Therefore, we have to set the Tail to NULL as well to make sure the list is represented as empty!
		{
			tail = NULL;
		}
		--curNode;
		return returnNode;
	}
	void printList()
	{
		for (node* mover = head; mover != NULL; mover = mover->next)
		{
			if (mover->next == NULL)
			{
				printf("%d.", mover->value);
			}
			else
			{
				printf("%d, ", mover->value);
			}
		}
	}
	int valueAt(int index)
	{
		node* returnNode = head;
		for (int i = 0; i < index; ++i)
		{
			returnNode = returnNode->next;
		}
		return returnNode->value;
	}
	LinkedList()
	{
		curNode = 0;
		head = NULL;
		tail = NULL;
	}

	LinkedList(int val)
	{
		curNode = 1;
		node* element = (node*)malloc(sizeof(node));

		element->next = element->prev = NULL;
		element->value = val;

		head = tail = element;
	}

	int getCurNodeCt()
	{
		return curNode;
	}

	bool sequential(bool reverse)
	{
		for (node* curElement = (head->next); curElement != NULL; curElement = curElement->next)
		{
			if (!reverse) //ascending
			{
				if (curElement->value != ((curElement->prev->value) + 1))
				{
					return false;
				}
			}
			else
			{
				if (curElement->value != ((curElement->prev->value) - 1))
				{
					return false;
				}
			}


		}
		return true;
	}
};

struct stack
{
private:
	LinkedList model;

public:

	node* push(int val)
	{
		return model.addToTail(val);

	}
	node* pop()
	{
		return model.removeFromTail();
	}
	int getNumNodes()
	{
		return model.getCurNodeCt();
	}

	void print()
	{
		model.printList();
	}

	int getValue(int index)
	{
		return model.valueAt(index);
	}

	bool sequential(bool reversed)
	{
		return model.sequential(reversed);
	}
	node* getHead()
	{
		return model.head;
	}
	node* getTail()
	{
		return model.tail;
	}
};

struct queue
{
private:
	LinkedList model;
public:
	node* enqueue(int val)
	{
		return model.addToTail(val);
	}
	node* dequeue()
	{
		return model.removeFromHead();
	}
	int getNumNodes()
	{
		return model.getCurNodeCt();
	}
	void print()
	{
		model.printList();
	}
	int getValue(int index)
	{
		return model.valueAt(index);
	}
	bool sequential(bool reversed)
	{
		return model.sequential(reversed);
	}
	node* getHead()
	{
		return model.head;
	}
	node* getTail()
	{
		return model.tail;
	}
};