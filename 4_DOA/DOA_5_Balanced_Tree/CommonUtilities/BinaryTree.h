#pragma once

namespace CommonUtilities
{
	template <class T>
	class BinaryTree
	{
	public:
		struct Node
		{
			T myValue{};
			Node* myLeft = nullptr;
			Node* myRight = nullptr;
		};

		BinaryTree();
		~BinaryTree();

		//Returnerar true om elementet finns i mängden, och false annars.
		bool HasElement(const T& value) const;

		//Stoppar in elementet i mängden, om det inte redan finns där. Gör 
		//ingenting annars.
		void Insert(const T& value);

		//Plockar bort elementet ur mängden, om det finns. Gör ingenting annars.
		void Remove(const T& value);

		bool Equals(const T& valueOne, const T& valueTwo) const
		{
			return !(valueOne < valueTwo) && !(valueTwo < valueOne);
		}

	private:
		Node* myRoot = nullptr;
	};

	template <class T>
	BinaryTree<T>::BinaryTree()
	{
	}

	template <class T>
	BinaryTree<T>::~BinaryTree()
	{
		std::vector<Node*> nodes;

		if (myRoot)
		{
			nodes.push_back(myRoot);
		}
		while (!nodes.empty())
		{
			Node* current = nodes.back();
			nodes.pop_back();
			if (current->myLeft)
			{
				nodes.push_back(current->myLeft);
			}
			if (current->myRight)
			{
				nodes.push_back(current->myRight);
			}
			delete current;
			current = nullptr;
		}
		myRoot = nullptr;
	}

	template <class T>
	bool BinaryTree<T>::HasElement(const T& value) const
	{
		auto currentNode = myRoot;

		while (currentNode && !Equals(currentNode->myValue, value))
		{
			if (value < currentNode->myValue)
			{
				currentNode = currentNode->myLeft;
			}
			else if (currentNode->myValue < value)
			{
				currentNode = currentNode->myRight;
			}
		}

		return (currentNode && Equals(currentNode->myValue, value));
	}

	template <class T>
	void BinaryTree<T>::Insert(const T& value)
	{
		auto currentNode = myRoot;
		auto previousNode = currentNode;

		if (!myRoot)
		{
			Node* newNode = new Node;
			newNode->myValue = value;
			myRoot = newNode;
			return;
		}

		while (currentNode && !Equals(currentNode->myValue, value))
		{
			previousNode = currentNode;

			if (value < currentNode->myValue)
			{
				currentNode = currentNode->myLeft;
			}
			else if (currentNode->myValue < value)
			{
				currentNode = currentNode->myRight;
			}
		}
		if (currentNode && Equals(currentNode->myValue, value))
		{
			return;
		}

		Node* newNode = new Node;
		if (previousNode && value < previousNode->myValue)
		{
			newNode->myValue = value;
			previousNode->myLeft = newNode;
		}
		if (previousNode && previousNode->myValue < value)
		{
			newNode->myValue = value;
			previousNode->myRight = newNode;
		}
	}

	template <class T>
	void BinaryTree<T>::Remove(const T& value)
	{
		auto currentNode = myRoot;
		auto previousNode = static_cast<Node*>(nullptr);

		while (currentNode && !Equals(currentNode->myValue, value))
		{
			previousNode = currentNode;

			if (value < currentNode->myValue)
			{
				currentNode = currentNode->myLeft;
			}
			else
			{
				currentNode = currentNode->myRight;
			}
		}

		if (!currentNode) return;
		if (currentNode->myLeft && currentNode->myRight)
		{
			auto successorParent = currentNode;
			auto successor = currentNode->myRight;

			while (successor->myLeft)
			{
				successorParent = successor;
				successor = successor->myLeft;
			}

			currentNode->myValue = successor->myValue;

			currentNode = successor;
			previousNode = successorParent;
		}

		Node* child = currentNode->myLeft ? currentNode->myLeft : currentNode->myRight;

		if (!previousNode)
		{
			myRoot = child;
		}
		else if (previousNode->myLeft == currentNode)
		{
			previousNode->myLeft = child;
		}
		else
		{
			previousNode->myRight = child;
		}

		delete currentNode;
	}

	// input: 60
	//              20
	//       10            40
	//     5   15        30  50
	//    1 8 11 17
}
