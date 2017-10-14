#include <iostream>

using namespace std;

template <class T>

class Queue {
private:
	int length;
	struct Node
	{
		T Value;
		struct Node *nextNode;
	};
	Node *firstNode;
	Node *tailNode;
public:
	Queue()
	{
		length = 0;
		firstNode = nullptr;
		tailNode = nullptr;
	}
	~Queue()
	{
		Node *tempNode = firstNode;
		Node *prevNode = nullptr;
		while (tempNode != nullptr)
		{
			prevNode = tempNode;
			tempNode = tempNode->nextNode;
			delete prevNode;
		}
	}
	void Enqueue(T newItem)
	{
		Node *newNode = new Node;
		newNode->Value = newItem;
		newNode->nextNode = nullptr;
		if (length == 0)
		{
			firstNode = newNode;
			tailNode = newNode;
		}
		else
		{
			tailNode->nextNode = newNode;
			tailNode = newNode;
		}
		length++;
	}
	void Dequeue()
	{
		if (length == 0)
		{
			length++;
		}
		if (length == 1)
		{
			firstNode = nullptr;
			tailNode = nullptr;
		}
		else
		{
			Node *tempNode = firstNode;
			firstNode = firstNode->nextNode;
			delete tempNode;
		}
		length--;
	}
	T Front()
	{
		return firstNode->Value;
	}
	int getLength()
	{
		return length;
	}

};
