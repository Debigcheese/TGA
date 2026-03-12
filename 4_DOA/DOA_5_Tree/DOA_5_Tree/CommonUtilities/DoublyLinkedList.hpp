#pragma once
#include "DoublyLinkedListNode.hpp"

namespace CommonUtilities
{
	template <class T>
	class DoublyLinkedList
	{
	public:
		// Skapar en tom lista
		DoublyLinkedList() : myFirst(nullptr), myLast(nullptr), mySize(0)
		{
		}

		// Frigör allt minne som listan allokerat
		~DoublyLinkedList()
		{
			auto node = myFirst;
			auto nextNode = node->GetNext();

			for (int i = 0; i < mySize; ++i)
			{
				nextNode = node->GetNext();
				Remove(node);
				node = nextNode;
			}

			mySize = 0;
		}

		// Returnerar antalet element i listan
		int GetSize() const
		{
			return mySize;
		}

		// Returnerar första noden i listan, eller nullptr om listan är tom
		DoublyLinkedListNode<T>* GetFirst()
		{
			return myFirst;
		}

		// Returnerar sista noden i listan, eller nullptr om listan är tom
		DoublyLinkedListNode<T>* GetLast()
		{
			return myLast;
		}

		// Skjuter in ett nytt element först i listan
		void InsertFirst(const T& aValue)
		{
			auto newNode = new DoublyLinkedListNode<T>(aValue);
			if (myFirst)
			{
				newNode->myNext = myFirst;
				myFirst->myPrevious = newNode;
			}
			if (!myLast)
			{
				myLast = newNode;
			}

			myFirst = newNode;
			mySize++;
		}

		// Skjuter in ett nytt element sist i listan
		void InsertLast(const T& aValue)
		{
			auto newNode = new DoublyLinkedListNode<T>(aValue);
			if (myLast)
			{
				newNode->myPrevious = myLast;
				myLast->myNext = newNode;
			}
			if (myFirst)
			{
				myFirst = newNode;
			}

			myLast = newNode;
			mySize++;
		}

		// Skjuter in ett nytt element innan aNode
		void InsertBefore(DoublyLinkedListNode<T>* aNode, const T& aValue)
		{
			auto node = new DoublyLinkedListNode<T>(aValue);
			node->myNext = aNode;

			auto oldPrevious = aNode->GetPrevious();

			if (aNode->GetPrevious())
			{
				oldPrevious->myNext = node;
			}
			aNode->myPrevious = node;
			node->myPrevious = oldPrevious;

			if (aNode == myFirst)
			{
				myFirst = node;
			}

			mySize++;
		}

		// Skjuter in ett nytt element efter aNode
		void InsertAfter(DoublyLinkedListNode<T>* aNode, const T& aValue)
		{
			auto newNode = new DoublyLinkedListNode<T>(aValue);
			newNode->myPrevious = aNode;

			auto oldNext = aNode->myNext;

			if (aNode->GetNext())
			{
				oldNext->myPrevious = newNode;
			}
			aNode->myNext = newNode;
			newNode->myNext = oldNext;

			if (aNode == myLast)
			{
				myLast = newNode;
			}
			mySize++;
		}

		// Plockar bort noden ur listan och frigör minne. (Det är ok att anta att
		// aNode är en nod i listan, och inte från en annan lista)
		void Remove(DoublyLinkedListNode<T>* aNode)
		{
			auto previous = aNode->GetPrevious();
			auto next = aNode->GetNext();

			if (next)
			{
				next->myPrevious = previous;
			}
			if (previous)
			{
				previous->myNext = next;
			}
			if (aNode == myLast)
			{
				myLast = previous;
			}
			if (aNode == myFirst)
			{
				myFirst = next;
			}

			delete aNode;
			mySize--;
		}

		// Hittar första elementet i listan som har ett visst värde. Jämförelsen
		// görs med operator==. Om inget element hittas returneras nullptr.
		DoublyLinkedListNode<T>* FindFirst(const T& aValue)
		{
			auto node = myFirst;
			for (int i = 0; i < mySize; ++i)
			{
				if (node->GetValue() == aValue)
				{
					return node;
				}
				node = node->GetNext();
			}
			return nullptr;
		}

		// Hittar sista elementet i listan som har ett visst värde. Jämförelsen
		// görs med operator==. Om inget element hittas returneras nullptr.
		DoublyLinkedListNode<T>* FindLast(const T& aValue)
		{
			auto node = myLast;
			for (int i = 0; i < mySize; ++i)
			{
				if (node->GetValue() == aValue)
				{
					return node;
				}
				node = node->GetPrevious();
			}
			return nullptr;
		}

		// Plockar bort första elementet i listan som har ett visst värde. 
		// Jämförelsen görs med operator==. Om inget element hittas görs ingenting.
		// Returnerar true om ett element plockades bort, och false annars.
		bool RemoveFirst(const T& aValue)
		{
			auto node = myFirst;
			for (int i = 0; i < mySize; ++i)
			{
				if (node->GetValue() == aValue)
				{
					Remove(node);
					return true;
				}
				node = node->GetNext();
			}
			return false;
		}

		// Plockar bort sista elementet i listan som har ett visst värde.
		// Jämförelsen görs med operator==. Om inget element hittas görs ingenting.
		// Returnerar true om ett element plockades bort, och false annars.
		bool RemoveLast(const T& aValue)
		{
			auto node = myLast;
			for (int i = 0; i < mySize; ++i)
			{
				if (node->GetValue() == aValue)
				{
					Remove(node);
					return true;
				}
				node = node->GetPrevious();
			}
			return false;
		}

	private:
		DoublyLinkedListNode<T>* myFirst = nullptr;
		DoublyLinkedListNode<T>* myLast = nullptr;
		int mySize{};
	};
}
