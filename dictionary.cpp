#include <iostream>
#include <cstdlib>

using namespace std;

TBTreeNode::TBTreeNode(TNote *values, size_t size, TBTreeNode *parent) {
	this->ElementsNum = size;
	this->Elements = new TNote[this->ElementsNum];
	for (size_t i = 0; i < this->ElementsNum; i++) {
		this->Elements[i] = values[i];
	}
	this->ChildrenNum = 0;
	this->Children = NULL;
	this->Parent = parent;
}

TBTreeNode::~TBTreeNode() {
	delete [] this->Elements;
	for (size_t i = 0; i < this->ChildrenNum; i++) {
		delete this->Children[i];
	}
	delete [] this->Children;
}



TBTree::TBTree(size_t factor) {
	this->Root = NULL;
	this->FactorT = factor;
}

TBTree::~TBTree() {
	delete this->Root;
}

void TBTree::Split(TBTreeNode *node) {
	
}

TBTreeNode *TBTree::Search(TNumber key) {

}

void TBTree::Push(TNote element) {

}

TNote TBTree::Pop(TNumber key) {

}
