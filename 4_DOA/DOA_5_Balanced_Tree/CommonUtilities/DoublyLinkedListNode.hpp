#pragma once

namespace CommonUtilities
{
	template <class T>
	class DoublyLinkedList;

	template <class T>
	class DoublyLinkedListNode
	{
	public:
		// Copy-konstruktorn och assignment-operatorn är borttagna, så att det enda
		// sättet att skapa en nod är genom att stoppa in ett värde i en lista.
		DoublyLinkedListNode<T>(const DoublyLinkedListNode<T>&) = delete;
		DoublyLinkedListNode<T>& operator=(const DoublyLinkedListNode<T>&) = delete;

		// Returnerar nodens värde
		const T& GetValue() const
		{
			return myValue;
		}

		T& GetValue()
		{
			return myValue;
		}

		// Returnerar nästa nod i listan, eller nullptr om noden är sist i listan
		DoublyLinkedListNode<T>* GetNext() const
		{
			return myNext;
		}

		// Returnerar föregående nod i listan, eller nullptr om noden är först i
		// listan
		DoublyLinkedListNode<T>* GetPrevious() const
		{
			return myPrevious;
		}

	private:
		// Konstruktorn och destruktorn är privat, så att man inte kan skapa eller
		// ta bort noder utifrån. List-klassen är friend, så att den kan skapa
		// eller ta bort noder.
		friend class DoublyLinkedList<T>;

		DoublyLinkedListNode(const T& aValue)
		{
			myValue = aValue;
		}

		~DoublyLinkedListNode()
		{
			myNext = nullptr;
			myPrevious = nullptr;
		}

		T myValue;
		DoublyLinkedListNode<T>* myNext = nullptr;
		DoublyLinkedListNode<T>* myPrevious = nullptr;
	};
}
