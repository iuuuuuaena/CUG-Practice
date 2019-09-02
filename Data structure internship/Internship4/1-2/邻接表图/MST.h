#pragma once
#include "MyGraph.h"
const int maxValue = INT_MAX;
template<class T,class E>
struct MSTEdgeNode
{
	int tail, head; E key;
	MSTEdgeNode():tail(-1),head(-1),key(0){}
	bool operator<=(MSTEdgeNode<T, E>& R) { return key <= R.key; }
	bool operator>(MSTEdgeNode<T, E>& R) { return key > R.key; }
};

template<class T, class E>
class MinSpanTree
{
public:
	MinSpanTree(int sz = DefaultVertices - 1) :maxSize(sz), n(0) {
		edgevalue = new MSTEdgeNode<T, E>[sz];
	}
	bool Insert(MSTEdgeNode<T, E>& item) {
		if (n == maxSize) {
			return false;
		}
		edgevalue[n] = item;
		n++;
		return true;
	}
	void output() {
		for (int i = 0; i < n; i++) {
			//cout << "Edge " << i << " : " << "head = " << edgevalue[i - 1].head << " ; tail = " << edgevalue[i - 1].tail << " ; key = " << edgevalue[i - 1].key << endl;
			cout << "(" << edgevalue[i].head + 1 << "," << edgevalue[i].tail + 1 << "," << edgevalue[i].key << ")" << endl;
		}
	}
protected:
	MSTEdgeNode<T, E> *edgevalue;
	int maxSize, n;
};
