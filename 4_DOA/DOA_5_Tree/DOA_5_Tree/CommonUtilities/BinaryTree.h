#pragma once

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
		Node* current = nodes.front();
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
	}
}

template <class T>
bool BinaryTree<T>::HasElement(const T& value) const
{
	auto currentNode = myRoot;

	while (currentNode && currentNode->myValue != value)
	{
		if (value < currentNode->myValue)
		{
			currentNode = currentNode->myLeft;
		}
		else if (value > currentNode->myValue)
		{
			currentNode = currentNode->myRight;
		}
	}

	return (currentNode && currentNode->myValue == value);
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

	while (currentNode && currentNode->myValue != value)
	{
		previousNode = currentNode;

		if (value < currentNode->myValue)
		{
			currentNode = currentNode->myLeft;
		}
		else if (value > currentNode->myValue)
		{
			currentNode = currentNode->myRight;
		}
	}
	if (currentNode && currentNode->myValue == value)
	{
		return;
	}

	Node* newNode = new Node;
	if (previousNode && value < previousNode->myValue)
	{
		newNode->myValue = value;
		previousNode->myLeft = newNode;
	}
	if (previousNode && value > previousNode->myValue)
	{
		newNode->myValue = value;
		previousNode->myRight = newNode;
	}
}

template <class T>
void BinaryTree<T>::Remove(const T& value)
{
	auto currentNode = myRoot;
	auto previousNode = currentNode;
	previousNode = nullptr;

	while (currentNode && currentNode->myValue != value)
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

	if (!currentNode)
	{
		return; // value not found
	}

	// Node has two children — replace with in-order successor
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

		// Now delete the successor (has at most a right child)
		if (successorParent == currentNode)
		{
			successorParent->myRight = successor->myRight;
		}
		else
		{
			successorParent->myLeft = successor->myRight;
		}

		delete successor;
		return;
	}

	// Node has zero or one child
	Node<T> * child = currentNode->myLeft ? currentNode->myLeft : currentNode->myRight;

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
