#pragma once
#include <vector>

namespace CommonUtilities
{
	template <class T>
	class BinaryTreeNode;

	template <class T>
	class BSTSet
	{
	public:
		BSTSet() : myRoot(nullptr)
		{
		}

		~BinaryTree()
		{
			std::vector<BinaryTreeNode<T>*> nodes;
			if (myRoot)
				nodes.push_back(myRoot);

			while (!nodes.empty())
			{
				BinaryTreeNode<T>* current = nodes.back();
				nodes.pop_back();
				if (current->myLeftChild)
					nodes.push_back(current->myLeftChild);
				if (current->myRightChild)
					nodes.push_back(current->myRightChild);
				delete current;
			}
		}

		const BinaryTreeNode<T>* get_root() const { return myRoot; }
		bool has_element(const T& data) const;
		void insert(const T& data);
		void remove(const T& data);
		void DSWBalance();

	private:
		bool equals(const T& a, const T& b) const { return !(a < b) && !(b < a); }
		// Left-rotate count times down the vine starting from root
		void compress(BinaryTreeNode<T>* root, int count);

		BinaryTreeNode<T>* myRoot;
	};

	template <class T>
	bool BSTSet<T>::has_element(const T& data) const
	{
		BinaryTreeNode<T>* current = myRoot;
		while (current)
		{
			if (data < current->myValue)
				current = current->myLeftChild;
			else if (current->myValue < data)
				current = current->myRightChild;
			else
				return true;
		}
		return false;
	}

	template <class T>
	void BSTSet<T>::insert(const T& data)
	{
		if (!myRoot)
		{
			myRoot = new BinaryTreeNode<T>(data);
			return;
		}

		BinaryTreeNode<T>* current = myRoot;
		while (true)
		{
			if (data < current->myValue)
			{
				if (!current->myLeftChild)
				{
					current->myLeftChild = new BinaryTreeNode<T>(data);
					return;
				}
				current = current->myLeftChild;
			}
			else if (current->myValue < data)
			{
				if (!current->myRightChild)
				{
					current->myRightChild = new BinaryTreeNode<T>(data);
					return;
				}
				current = current->myRightChild;
			}
			else
			{
				return;
			}
		}
	}

	template <class T>
	void BSTSet<T>::remove(const T& data)
	{
		BinaryTreeNode<T>* parent = nullptr;
		BinaryTreeNode<T>* current = myRoot;

		// Find the node
		while (current)
		{
			if (data < current->myValue)
			{
				parent = current;
				current = current->myLeftChild;
			}
			else if (current->myValue < data)
			{
				parent = current;
				current = current->myRightChild;
			}
			else
				break;
		}

		if (!current) return;

		if (current->myLeftChild && current->myRightChild)
		{
			BinaryTreeNode<T>* successorParent = current;
			BinaryTreeNode<T>* successor = current->myRightChild;
			while (successor->myLeftChild)
			{
				successorParent = successor;
				successor = successor->myLeftChild;
			}
			current->myValue = successor->myValue;

			parent = successorParent;
			current = successor;
		}


		BinaryTreeNode<T>* child = current->myLeftChild
			                           ? current->myLeftChild
			                           : current->myRightChild;

		if (!parent)
		{
			myRoot = child;
		}
		else if (parent->myLeftChild == current)
		{
			parent->myLeftChild = child;
		}
		else
		{
			parent->myRightChild = child;
		}

		delete current;
	}

	template <class T>
	void BSTSet<T>::DSWBalance()
	{
		if (!myRoot)
			return;

		BinaryTreeNode<T>* pseudoRoot = new BinaryTreeNode<T>(myRoot->myValue);
		pseudoRoot->myRightChild = myRoot;
		pseudoRoot->myLeftChild = nullptr;

		BinaryTreeNode<T>* tail = pseudoRoot;
		BinaryTreeNode<T>* rest = tail->myRightChild;

		while (rest)
		{
			if (!rest->myLeftChild)
			{
				tail = rest;
				rest = rest->myRightChild;
			}
			else
			{
				// Right rotate around left child
				BinaryTreeNode<T>* temp = rest->myLeftChild;
				rest->myLeftChild = temp->myRightChild;
				temp->myRightChild = rest;
				tail->myRightChild = temp;
				rest = temp;
			}
		}

		int nodeCount = 0;
		BinaryTreeNode<T>* counter = pseudoRoot->myRightChild;
		while (counter)
		{
			nodeCount++;
			counter = counter->myRightChild;
		}

		int idealSize = 1;
		while (idealSize <= nodeCount)
		{
			idealSize = idealSize * 2;
		}
		idealSize = idealSize / 2 - 1;

		compress(pseudoRoot, nodeCount - idealSize);

		for (idealSize = idealSize / 2; idealSize > 0; idealSize /= 2)
		{
			compress(pseudoRoot, idealSize);
		}

		myRoot = pseudoRoot->myRightChild;
		pseudoRoot->myRightChild = nullptr;
		delete pseudoRoot;
	}

	template <class T>
	void BSTSet<T>::compress(BinaryTreeNode<T>* root, int count)
	{
		BinaryTreeNode<T>* scanner = root;
		for (int i = 0; i < count; i++)
		{
			BinaryTreeNode<T>* child = scanner->myRightChild;
			scanner->myRightChild = child->myRightChild;
			scanner = scanner->myRightChild;
			child->myRightChild = scanner->myLeftChild;
			scanner->myLeftChild = child;
		}
	}

	template <class T>
	class BinaryTreeNode
	{
	public:
		BinaryTreeNode<T>(const BinaryTreeNode<T>&) = delete;
		BinaryTreeNode<T>& operator=(const BinaryTreeNode<T>&) = delete;

		const T& GetValue() const { return myValue; }
		T& GetValue() { return myValue; }

		BinaryTreeNode<T>* GetLeftChild() const { return myLeftChild; }
		BinaryTreeNode<T>* GetRightChild() const { return myRightChild; }

	private:
		friend class BinaryTree<T>;

		BinaryTreeNode(const T& aValue)
			: myLeftChild(nullptr), myRightChild(nullptr), myValue(aValue)
		{
		}

		~BinaryTreeNode() = default;

		BinaryTreeNode<T>* myLeftChild;
		BinaryTreeNode<T>* myRightChild;
		T myValue;
	};
}
