#ifndef BSTREE_H
#define BSTREE_H

template <class T>
struct treeNode {
	T data;
	treeNode<T> *left, *right;
	
	treeNode() {};
	treeNode(const T& info)
	{	data = info; }	
};

class bsTree {
	public:
		virtual bool find(int) const = 0;
		virtual void insert(int) = 0;
		virtual void erase(int) = 0;
		
		virtual void inOrder(std::ostream&) const = 0;
		virtual void preOrder(std::ostream&) const = 0;
		virtual void postOrder(std::ostream&) const = 0;
		virtual void lvlOrder(std::ostream&) const = 0;
};

#endif		
	