#ifndef MAXHEAP_H
#define MAXHEAP_H

template<class T>
class maxHeap {
	public:
		virtual void push(const T& theKey) = 0;
		virtual T pop() = 0;
		virtual T top() const = 0;
		//virtual void heapify(T*);
		virtual int size() const = 0;
		virtual bool empty() const = 0;
		virtual void print() const = 0;
};

#endif
