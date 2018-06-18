/**
* Author:		Dr. Spiegel
* Updated By:	Christian Carreras
* File:		BinarySearchTree.h
* Date:		23/4/2014
* Purpose:	Binary Tree ADT using linked structures.
*			A binary tree is comprised of a root, and subtrees.
*			Subtrees are called children and can be a parent by
*			having its own children. If the subtree has no children
*			it is called a leaf. Entries less than the subtree will go
*			left, with entries greater than the subtree will go right.
*			Any entry added that's already in the tree will increment
*			the counter. This adds multiplicity to the tree.
**/

#ifndef TREE_H
#define TREE_H

template <typename treeEltType> class BinaryTree;

/**
* Class:		TreeNode
* Purpose:	A template class that holds later to be specified data.
*			Consists of a pointer to be used to point at a treeNode
*			with lesser data, a right pointer to point at a treeNode 
*			with greater data, and a counter for multiplicity.
**/
template <typename eltType> class TreeNode {
private:
	eltType info;
	TreeNode<eltType> *left, *right;
	int count; //Multiplicity counter, initially 1
	TreeNode(const eltType &data, TreeNode<eltType> *lChild = NULL, 
	TreeNode *rChild = NULL, int num = 1)
	{	info = data; 
		left = lChild; 
		right = rChild; 
		count = num; //Assign one, or user assigned value to count
	}
  
	friend class BinaryTree<eltType>;
};

template <typename treeEltType> class BinaryTree {

public:

	/**
	* The constructor constructs an instance of a BinaryTree by pointing
	*	the data member root at NULL
	**/
	BinaryTree();
	
	/**
	* Places an element into the tree by following the rules of a tree.
	*	Returns 1 if inserted (true)
	**/
	int insertToTree(const treeEltType &data);

	/**
	* Searches the tree for a specific element. Returns true if the element
	*	resides in the tree, false if not. 
	*	Assumes == is defined for treeEltType
	**/
	bool treeSearch(const treeEltType &data);

	/**
	* Retrieves an element from the tree while leaving the tree intact
	*	Precondition: The element has to be located in the tree
	**/
	treeEltType &retrieveFromTree(const treeEltType &data);
	
	/**
	* Removes an element from the tree or decrements counter based
	*	on the element's multiplicity.
	*	Precondition: The element has to be located in the tree
	**/
	void deleteFromTree(const treeEltType &data);
	
	/**
	* Changes an element to a new specified data, if the multiplicity of
	*	the element to be changed is greater than one, the element's counter
	*	will be decremented and the new data will be inserted. Otherwise,
	*	the element will be changed/deleted according to the new data
	**/
	void change(const treeEltType &toChange, const treeEltType &data);
	
	/**
	* Checks if the given element has multiple copies (multiplicity g.t. one)
	* 	Returns true if multiple copies, false if not
	*	Precondition: At least one copy is in the tree
	**/
	bool hasMultiples(const treeEltType &data);
	
	/**
	* Decrements the count of the given element
	* 	Preconditions: Element has to be in the list w/ more than one copy
	**/
	void decCount(const treeEltType &data);

	/**
	* Displays the tree in order, least to greatest (Left, Node, Right)
	**/
	void inorder() const;

	/**
	* Displays the tree in preorder (Node, Left, Right)
	**/
	void preorder() const;

	/**
	* Displays tree in postorder (Left, Right, Node)
	**/
	void postorder() const;
 
	/**
	* Prints the tree according the its actual shape
	**/
	void treePrint() const;
 
private:

	TreeNode<treeEltType> *root;

	/**
	* Recursive helper function to printorder
	**/
	void printInorder(TreeNode<treeEltType> *) const;

	/**
	* Recursive helper function to preorder
	**/
	void printPreorder(TreeNode<treeEltType> *) const;

	/**
	* Recursive helper function to postorder
	**/
	void printPostorder(TreeNode<treeEltType> *) const;
 
	/**
	* Helper function to treePrint
	**/
	void treePrintHelper(TreeNode<treeEltType> *) const;

};

#endif
