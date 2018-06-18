/**
* Author:		Dr. Spiegel
* Updated By:	Christian Carreras
* File:		BinarySearchTree..cpp
* Date:		23/4/2014
* Purpose:	Binary Tree ADT using linked structures.
*			The Binary tree uses treeNode template objects
*			to hold all data. The Binary Tree consists of one
*			data member named root which is a pointer to a
*			treeNode object. As a binary tree works, the left pointer
*			of a treeNode object will point to a node with data less
*			than the parent's data. The right pointer will also point
*			to a treeNode object but will have data greater than the
*			parent node. The Binary tree class has functions to properly
*			implement a tree structure by being able to insert, remove,
*			change and print data held within the tree.
**/

#include <iostream>
#include <string>
#include <queue>
#include "BinarySearchTree.h"

using namespace std;

/**
* Function Name:	Constructor
* Member Type:		Constructor
* Parameters:		None
* Return Value:	N/A
* Purpose:		Constructs the BinaryTree by pointing the data member
*				root at NULL
**/
template <typename treeEltType> BinaryTree<treeEltType>::BinaryTree()
{	root = NULL;
}

/**
* Function Name:	insertToTree
* Member Type:		Mutator
* Parameters:		const treeEltType& - import only
* Return Value:	int - (1) true boolean value
* Purpose:		Finds appropriate place in tree for the parameter,
*				uses a while loop to navigate through tree until
*				either it can be placed or the data is already in the
*				list, where from there, would increase the data's counter
**/
template <typename treeEltType> int BinaryTree<treeEltType>::
insertToTree(const treeEltType &data)
{	if(root == NULL)  // Empty Tree
	{	root = new TreeNode<treeEltType>(data);
		return(1);
	}
// Search for spot to put data; We only stop when we get to the bottom (NULL)
	TreeNode<treeEltType> *t = root, *parent;
	while(t != NULL) 
	{	if(t->info == data) // data already in Tree
		{	t->count++; //Increment count for multiplicity
			return(1);
		}
		//Set the trail pointer to the ancestor of where we're going
		parent = t; 
		if(data < t->info) 
			t = t->left;
		else 
			t = t->right;
	}
	// Found the spot; insert node.
	if(data < parent->info) 
		parent->left = new TreeNode<treeEltType>(data);
	else 
		parent->right = new TreeNode<treeEltType>(data);
	return(1);
}

/**
* Function Name:	treeSearch
* Member Type:		Facilitator
* Parameters:		const treeEltType& - import only
* Return Value:	Returns Ptr to Elt if Found, NULL otherwise
*				(true if found, false if not)
* Purpose:		Used while loop to navigate through tree until
*				data is found or NULL is hit
*				Assumes == is defined for treeEltType			
**/
template <typename treeEltType> bool BinaryTree<treeEltType>::
treeSearch(const treeEltType &key)
{	TreeNode<treeEltType> *t = root;
	while(t && t->info != key)
		if(key < t->info) 
			t = t->left;
		else 
			t = t->right;
	return(t);	// auto convert int to bool
}

/**
* Function Name:	retrieveFromTree
* Member Type:		Inspector
* Parameters:		const treeEltType& - import only
* Return Value:	treeEltType& - the node's info
* Purpose:		Retrieve Element from Tree (leaving Tree Intact)
*				Precondition: Item is in Tree
**/
template <typename treeEltType> treeEltType &BinaryTree<treeEltType>::
retrieveFromTree(const treeEltType &key)
{	TreeNode<treeEltType> *t;
	for(t = root; t->info != key;)
		if(key < t->info) 
			t = t->left;
		else 
			t = t->right;
	return(t->info);
}

/**
* Function Name:	deleteFromTree
* Member Type:		Mutator
* Parameters:		const treeEltType& - import only
* Return Value:	void
* Purpose:		Remove an Element from the tree
* 				Precondition: Element is in the Tree;
**/
template <typename treeEltType> void BinaryTree<treeEltType>::
deleteFromTree(const treeEltType &data)
{	TreeNode<treeEltType> *nodeWithData, *nodeToDelete, 
		*t = root,*trailT = NULL;
	// Find spot
	while(t->info != data)//safe because of precondition
	{	trailT = t;
		if(data < t->info) 
			t = t->left;
		else 
			t = t->right;
	}
	nodeWithData = t;  //Hold onto the data Node for later deletion
	
	// Case 1: Leaf?
	if(!(nodeWithData->left) && !(nodeWithData->right)) 
	{	// No Subtrees, node is leaf...Wipe it
		// Is it the root?
		if(nodeWithData == root)
			root = NULL;
		else if(trailT->right == nodeWithData) //Parent's right child
			trailT->right = NULL;
		else 
			trailT->left = NULL;
			nodeToDelete = nodeWithData; //free this at the end
	}
	else if(!(nodeWithData->left)) 
	{//If 1st condition false and this one's true, there's a right subtree
		if(!trailT) 
		{ 	// Node to delete is root and there is no left subtree
			nodeToDelete = root;
			root = root->right;
		}
		else 
	//Point parent's pointer to this node to this node's right child
		{
			if(trailT->right == nodeWithData) 
				trailT->right = nodeWithData->right;
			else 
				trailT->left = nodeWithData->right;
			nodeToDelete = nodeWithData;
		}
	}
	else if(!(nodeWithData->right)) 
// If 1st 2 conditions false and this one's true, there's a left subtree
	{
		if (!trailT) 
		{ 	// Node to delete is root and there is no left subtree
			nodeToDelete = root;
			root = root->left;
		}
		else 
		{	// Otherwise, move up the right subtree
			if(trailT->right == nodeWithData) 
				trailT->right = nodeWithData->left;
			else 
				trailT->left = nodeWithData->left;
			nodeToDelete = nodeWithData;
		}
	} 
	else 
	{ // If you make it here, node has two children
	//Go to rightmost node in left subtree; we know there's a right child
		for(trailT = nodeWithData, t = nodeWithData->left;
			t->right != NULL;trailT = t, t = t->right);
// Want to copy data from node with 0 or 1 child to node with data to delete 
// Place node data in NodeWithData
		nodeWithData->info = t->info;
		nodeWithData->count = t->count;
	// Set the parent of source node to point at source node's left child 
	//   (We know it hasn't a right child. Also ok if no left child.)
		if(trailT == nodeWithData) 
	// Need to point parent correctly. 
	// See if after the we went left there was no right child
	// If there was no right child, this is rightmost node in left subtree
			trailT->left = t->left;
		else 
	// we did go right; after going left, there was a right child
	// rightmost node has no r. child, so point its parent at its l. child
			trailT->right = t->left;
		
		nodeToDelete = t;
	}
	
	delete nodeToDelete;
}

/**
* Function Name:	change
* Member Type:		Mutator
* Parameters:		const treeEltType& - import only
*				const treeEltType& - import only
* Return Value:	void
* Purpose:		User enters a value in the tree to change, if the value
* 				is in the tree it will be removed and the new value
*				will be inserted into the tree
**/
template <typename treeEltType> void BinaryTree<treeEltType>::
change(const treeEltType &toChange, const treeEltType &data)
{		TreeNode<treeEltType> *t = root,*trailT = NULL;
	if(treeSearch(data))//If data is already in the tree
	{	while(t->info != data)
			if(data < t->info) 
				t = t->left;
			else
				t = t->right;
		if(hasMultiples(toChange))//Has multiples
		{	decCount(toChange);//Decrease count for node to change
			t->count++;//Increase count for node being changed to
		}
		else
		{	deleteFromTree(toChange);//Delete node
			t->count++; //Increment multiplicity
		}
	}
	else//Data isn't already in the tree
	{	while(t->info != toChange) //Find node
		{	trailT = t;//Parent
			if(toChange < t->info) 
				t = t->left;
			else
				t = t->right;
		}
		if(t == root)//If root
		{	if(!(t->left) && !(t->right))//Root w/ no children
			{	if(t->count > 1)
				{	t->count--;
					insertToTree(data);
				}
				else
					t->info = data;
			}
			else if(t->left && !(t->right))
			//Root w/ only left child
			{	if(data > toChange)//Data g.t. root
				{	if(t->count > 1)
					{	t->count--;
						insertToTree(data);
					}
					else
						t->info = data;
				}
				else//Data l.t. root
				{	TreeNode<treeEltType> *n = t->left;
					while(n->right != NULL)//Go to rightmost child
						n = n->right;
					if(data > n->info)
					{//Data g.t. rightmost leaf
						if(t->count > 1)
						{	t->count--;
							insertToTree(data);
						}
						else
							t->info = data;
					}
					else//Data l.t. rightmost leaf
					//Delete root and insert new data
					{	if(t->count > 1)
						{	t->count--;
							insertToTree(data);
						}
						else
						{	deleteFromTree(toChange);
							insertToTree(data);
						}
					}
				}
			}
			else if(!(t->left) && t->right)
			//Root w/ only right child
			{	if(data < toChange)//Data l.t. root
				{	if(t->count > 1)
					{	t->count--;
						insertToTree(data);
					}
					else
						t->info = data;
				}
				else//Data g.t. root
				{	TreeNode<treeEltType> *n = t->right;
					while(n->left != NULL)//Go to leftmost child
						n = n->left;
					if(data < n->info)
					//Data l.t. leftmost leaf
					{	if(t->count > 1)
						{	t->count--;
							insertToTree(data);
						}
						else	
						t->info = data;
					}
					else//Data g.t leftmost leaf
					//Delete root and insert new data
					{	if(t->count > 1)
						{	t->count--;
							insertToTree(data);
						}
						else
						{	deleteFromTree(toChange);
							insertToTree(data);
						}
					}
				}
			}
			else//Root has two children
			{	TreeNode<treeEltType> *n1 = t->left;
				TreeNode<treeEltType> *n2 = t->right;
				while(n1->right != NULL)//Go to rightmost child
					n1 = n1->right;
				while(n2->left != NULL)//Go to lefmost child
					n2 = n2->left;
				if(data > n1->info && data < n2->info)
				{//Data is g.t. rightmost & l.t. leftmost
					if(t->count > 1)
					{	t->count--;
						insertToTree(data);
					}
					else
						t->info = data;
				}
				else//Data does not fall in previous range
				{	if(t->count > 1)
					{	t->count--;
						insertToTree(data);
					}
					else
					{	deleteFromTree(toChange);
						insertToTree(data);
					}
				}
			}	
		}
		else //The node to change is a child of some sort
		{	if(!(t->left) && !(t->right))//Just a leaf
			{	if(t->count > 1)
				{	t->count--;
					insertToTree(data);
				}
				else
				{	deleteFromTree(toChange);
					insertToTree(data);
				}
			}
			else if(t->left && !(t->right))
			//Subtree w/ only left child
			{	if(toChange < trailT->info)//left node of parent
				{	TreeNode<treeEltType> *n = t->left;
					while(n->right != NULL)//Go to rightmost child
						n = n->right;
					if(data > n->info && data < trailT->info)
					//Data is g.t. left child & l.t. parent
					{	if(t->count > 1)
						{	t->count--;
							insertToTree(data);
						}
						else
							t->info = data;
					}
					else//Data does not fall in previous range
					{	if(t->count > 1)
						{	t->count--;
							insertToTree(data);
						}
						else
						{	deleteFromTree(toChange);
							insertToTree(data);
						}
					}
				}
				else//Right node of parent
				{	if(data < toChange && data > t->left->info)
					//Data is l.t. info but g.t. left child
					{	if(t->count > 1)
						{	t->count--;
							insertToTree(data);
						}
						else
							t->info = data;
					}
					else //Cannot get range
					{	deleteFromTree(toChange);
						insertToTree(data);
					}
				}
			}
			else if(!(t->left) && t->right)
			//Subtree w/ only right child
			{	if(toChange > trailT->info)//right node of parent
				{	TreeNode<treeEltType> *n = t->right;
					while(n->left != NULL)//Go to leftmost child
						n = n->left;
					if(data < n->info && data > trailT->info)
					//Data is l.t. left child & g.t. parent
					{	if(t->count > 1)
						{	t->count--;
							insertToTree(data);
						}
						else
							t->info = data;
					}
					else//Data does not fall in previous range
					{	if(t->count > 1)
						{	t->count--;
							insertToTree(data);
						}
						else
						{	deleteFromTree(toChange);
							insertToTree(data);
						}
					}
				}
				else//Left node of parent
				{	if(data > toChange && data < t->right->info)
					//Data is g.t. info but l.t. left child
					{	if(t->count > 1)
						{	t->count--;
							insertToTree(data);
						}
						else
							t->info = data;
					}
					else //Cannot get range
					{	deleteFromTree(toChange);
						insertToTree(data);
					}
				}
			}
			else//Subtree with two children
			{	TreeNode<treeEltType> *n1 = t->left;
				TreeNode<treeEltType> *n2 = t->right;
				while(n1->right != NULL)//Go to rightmost child
					n1 = n1->right;
				while(n2->left != NULL)//Go to lefmost child
					n2 = n2->left;
				if(data > n1->info && data < n2->info)
				//Data is g.t. rightmost & l.t. leftmost
				{	if(t->count > 1)
					{	t->count--;
						insertToTree(data);
					}
					else
						t->info = data;
				}
				else//Data does not fall in previous range
				{	if(t->count > 1)
					{	t->count--;
						insertToTree(data);
					}
					else
					{	deleteFromTree(toChange);
						insertToTree(data);
					}
				}
			}
		}
	}
}

/**
* Function Name:	hasMultiples
* Member Type:		Facilitator
* Parameters:		const treeEltType& - import only
* Return Value:	true if data has multiplicity
*				false if not
* Purpose:		Checks if data has multiple entries within the tree
*				Precondition: Tree has at least copy of data
**/
template <typename treeEltType> bool BinaryTree<treeEltType>::
hasMultiples(const treeEltType &data)
{	TreeNode<treeEltType> *t = root;
	while(t->info != data)//Find node
		if(data < t->info) 
			t = t->left;
		else
			t = t->right;
	if(t->count > 1)//Check for multiplicity
		return true;//There is multiples
	else
		return false;//Ther is no multiples
}

/**
* Function Name:	decCount
* Member Type:		Mutator
* Parameters:		const treeEltType& - import only
* Return Value:	void
* Purpose:		decrements the count of the data in the tree
*				Preconditions: Tree has more than one copy of data
**/
template <typename treeEltType> void BinaryTree<treeEltType>::
decCount(const treeEltType &data)
{	TreeNode<treeEltType> *t = root;
	while(t->info != data)//Find node
		if(data < t->info) 
			t = t->left;
		else
			t = t->right;
	t->count--; //Decrement count
}

/**
* Function Name:	printInorder
* Member Type:		Facilitator
* Parameters:		TreeNode<treeEltType>* - import only
* Return Value:	void
* Purpose:		Recursive helper function that prints the tree in order
*				from least to greatest while also printing the
*				multiplicity of the data (if greater than one)
**/
template <typename treeEltType> void BinaryTree<treeEltType>::
printInorder(TreeNode<treeEltType> *t) const
	//void printTheTree(TreeNode *T)
{	if(t) 
	{	printInorder(t->left);
		cout << t->info;
		if(t->count > 1) //If there is more than one
			cout << "(" << t->count << ")"; //Show multiplicity
		cout << endl;
		printInorder(t->right);
	}
}

/**
* Function Name:	inorder
* Member Type:		Facilitator
* Parameters:		None
* Return Value:	void
* Purpose:		Prints tree in order least to greatest with the help
*				of the recursive helper function printInorder
**/
template <typename treeEltType> void BinaryTree<treeEltType>::inorder()const
{	printInorder(root); }

/**
* Function Name:	printPreorder
* Member Type:		Facilitator
* Parameters:		TreeNode<treeEltType>* - import only
* Return Value:	void
* Purpose:		Recursive helper function that prints the tree in
*				preorder (NLR)
**/
template <typename treeEltType> void BinaryTree<treeEltType>::
printPreorder(TreeNode<treeEltType> *t) const
//void printTheTree(TreeNode *t)
{	if(t) 
	{	cout << t->info << endl;
		if(t->count > 1) //If there is more than one
			cout << "(" << t->count << ")"; //Show multiplicity
		printPreorder(t->left);
		printPreorder(t->right);
	}
}

/**
* Function Name:	preorder
* Member Type:		Facilitator
* Parameters:		None
* Return Value:	void
* Purpose:		Prints the tree in preorder (NLR) print node, go left
*				repeat until those options are used up then go right.
*				Uses the help of the printPreorder recursive function
**/
template <typename treeEltType> void BinaryTree<treeEltType>::preorder()const
{	printPreorder(root); }

/**
* Function Name:	printPostorder
* Member Type:		Facilitator
* Parameters:		TreeNode<treeEltType>* - import only
* Return Value:	void
* Purpose:		Recursive helper function that prints the tree in
*				preorder (LRN)
**/
template <typename treeEltType> void BinaryTree<treeEltType>::
printPostorder(TreeNode<treeEltType> *t) const
	//void printTheTree(TreeNode *t)
{	if(t) 
	{	printPostorder(t->left);
		printPostorder(t->right);
		cout << t->info << endl;
		if(t->count > 1) //If there is more than one
			cout << "(" << t->count << ")"; //Show multiplicity
	}
}

/**
* Function Name:	postorder
* Member Type:		Facilitator
* Parameters:		None
* Return Value:	void
* Purpose:		Prints the tree in postorder (LRN) go left, then go right
*				until both options are used up, then print node.
*				Uses the help of the printPostorder recursive function
**/
template <typename treeEltType> void BinaryTree<treeEltType>::postorder()const
{	printPostorder(root); }

/**
* Function Name:	treePrint
* Member Type:		Facilitator
* Parameters:		None
* Return Value:	void
* Purpose:		Prints in the tree shape (sort of)
*				With the root on top and every subtree/leaf
*				to its correct row or correct parent.
*				Calls helper function treePrintHelper
**/
template <typename treeEltType> void BinaryTree<treeEltType>::treePrint()const
{	treePrintHelper(root); }

/**
* Function Name:	treePrintHelper
* Member Type:		Facilitator
* Parameters:		None
* Return Value:	void
* Purpose:		Prints in the tree shape by using queues.
*				The output result will resemble a tree structure
**/
template <typename treeEltType> void BinaryTree<treeEltType>::
treePrintHelper(TreeNode<treeEltType> *root) const
{	queue<TreeNode<treeEltType> *> Q;
	// A dummy node to mark end of level
	TreeNode<treeEltType> *dummy = new  TreeNode<treeEltType>(-1);
	if(root) 
	{	cout << root->info << " " << endl;
		Q.push(root->left);
		Q.push(root->right);
		Q.push(dummy);
	}
	TreeNode<treeEltType> *t = root;
	while(!Q.empty()) 
	{	t = Q.front();
		Q.pop();
		if(t == dummy) 
		{	if (!Q.empty()) 
			Q.push(dummy);
			cout << endl;
		}
		else if(t) 
		{	cout << t->info << " ";
			Q.push(t->left);
			Q.push(t->right);
		} 
	}
}

template class BinaryTree<int>;
