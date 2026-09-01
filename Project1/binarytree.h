//vector<int> res;
//TreeNode* current = root;
//stack<TreeNode*> stack;

//while(current && !stack.empty()){
//while(current){
//    stack.push(current);
//    current = current->left;
//}
//current = stack.top();
//stack.pop();
//res.push_back(current->val);
//current = current->right;

//}

///**
// * Definition for a binary tree node.
// * struct TreeNode {
// *     int val;
// *     TreeNode *left;
// *     TreeNode *right;
// *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
// *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
// *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
// * };
// */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;

	TreeNode() : val(0), left(nullptr), right(nullptr)
	{
	}

	TreeNode(int x) : val(x), left(nullptr), right(nullptr)
	{
	}

	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right)
	{
	}
};

class binarytree
{
public:
	bool isSameTree(TreeNode* p, TreeNode* q)
	{
		stack<TreeNode*> stackP;
		stack<TreeNode*> stackQ;

		stackP.push(p);
		stackQ.push(q);

		while (!stackP.empty())
		{
			auto a = stackP.top();
			stackP.pop();
			auto b = stackQ.top();
			stackQ.pop();

			if (!a && !b) continue;
			if (!a || !b) return false;
			if (a->val != b->val) return false;

			stackP.push(a->right);
			stackP.push(a->left);
			stackQ.push(b->right);
			stackQ.push(b->left);
		}
		return true;
	}
};


class Solution
{
public:
	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int> res;
		TreeNode* current = root;
		stack<TreeNode*> stack;
		stack.push(current);

		while (current && !stack.empty())
		{
			while (current)
			{
				stack.push(current);
				current = current->left;
			}
			current = stack.top();
			stack.pop();
			res.push_back(current->val);
			current = current->right;
		}
		return res;
	}
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution
{
public:
	bool isSymmetric(TreeNode* root)
	{
		stack<TreeNode*> leftStack;
		stack<TreeNode*> rightStack;

		leftStack.push(root);
		rightStack.push(root);

		if (root->left && root->right)
		{
			if (!root->left && root->right)
			{
				return false;
			}
			if (root->left->val != root->right->val)
			{
				return false;
			}
		}

		while (!leftStack.empty() && !rightStack.empty())
		{
			auto a = leftStack.top();
			auto b = rightStack.top();
			leftStack.pop();
			rightStack.pop();

			if (!a && !b) continue;
			if (!a || !b) return false;
			if (!a->left && b->left) return false;
			if (!a->right && b->right) return false;

			leftStack.push(a->right);
			leftStack.push(a->left);
			rightStack.push(b->left);
			rightStack.push(b->right);
		}

		return true;
	}
};


class Solution
{
public:
	bool isSymmetric(TreeNode* root)
	{
		stack<TreeNode*> leftStack;
		stack<TreeNode*> rightStack;

		leftStack.push(root);
		rightStack.push(root);

		if (root->left)
		{
			leftStack.push(root->left);
		}
		if (root->right)
		{
			rightStack.push(root->right);
		}

		while (!leftStack.empty() && !rightStack.empty())
		{
			auto a = leftStack.top();
			auto b = rightStack.top();
			leftStack.pop();
			rightStack.pop();

			if (!a && !b) continue;
			if (!a->left && !b->left) return false;
			if (!a->right && !b->right) return false;
			if (a->val != b->val) return false;

			leftStack.push(a->right);
			leftStack.push(a->left);
			rightStack.push(b->left);
			rightStack.push(b->right);
		}
		return true;
	}
};
