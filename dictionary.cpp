#include <iostream>
#include <cstdlib>
#include "dictionary.h"

using namespace std;

TNumber min(TNumber num1, TNumber num2) {
	if (num1 < num2) {
		return num1;
	} else {
		return num2;
	}
}
TNumber max(TNumber num1, TNumber num2) {
	if (num1 > num2) {
		return num1;
	} else {
		return num2;
	}
}



TBTreeNode::TBTreeNode(TBTreeNode *parent) {
	/*this->ElementsNum = size;
	this->Elements = new TNote[this->ElementsNum];
	for (size_t i = 0; i < this->ElementsNum; i++) {
		this->Elements[i] = values[i];
	}
	this->ChildrenNum = 0;
	this->Children = NULL;*/
	this->Parent = parent;
}

TBTreeNode::~TBTreeNode() {
	delete [] this->Elements;
	for (size_t i = 0; i < this->ChildrenNum; i++) {
		delete this->Children[i];
	}
	delete [] this->Children;
}

/*TBTreeNode::void InsertElementToArray(TNode element, TBTreeNode *right_branch) {
	//Binnary search
	/*size_t left = 0;
	size_t right = this->ElementsNum - 1;

	while (right > left) {
		size_t tmp_size = right - left + 1;
		size_t middle = tmp_size / 2 + left;
		if (element.num < this->Elements[middle]) {
			right = middle - 1;
		} else {
			left = middle;
		}
	}
	size_t insert_pos = left;

	for (size_t i = 0; i < )

	//Insert element

}*/

size_t TBTreeNode::GetInsertPosition(TBTreeNode *child) {
	for (size_t i = 0; i < this->ChildrenNum; i++) {
		if (this->Children[i] == child) {
			return i;
		}
	}
	return 0;
}



TBTree::TBTree(size_t factor) {
	this->Root = NULL;
	this->FactorT = factor;
}

TBTree::~TBTree() {
	delete this->Root;
}

void TBTree::Split(TBTreeNode *node) {
	//Separate arrays
	size_t middle = node->ElementsNum / 2;
	TNode middle_element = node->Elements[middle];

	size_t arr1_elements_len = middle;
	size_t arr2_elements_len = this->ElementsNum - middle - 1;

	TNote *arr1_elements = new TNote[arr1_len];
	TNote *arr2_elements = new TNote[arr2_len];

	size_t arr1_children_len = arr1_elements_len + 1;
	size_t arr2_children_len = arr2_elements_len + 1;

	TBTreeNode **arr1_children = new TBTreeNode *[arr1_children_len];
	TBTreeNode **arr2_children = new TBTreeNode *[arr2_children_len];

	for (size_t i = 0; i < node->ElementsNum; i++) {
		if (i == middle) {
			continue;
		}
		if (i < middle) {
			arr1_elements[i] = node->Elements[i];
		} else {
			arr2_elements[i - middle - 1] = node->Elements[i];
		}
	}
	for (size_t i = 0; i < node->ChildrenNum; i++) {
		if (i <= middle) {
			arr1_children[i] = node->Children[i];
		} else {
			arr2_children[i - middle - 1] = node->Children[i];
		}
	}

	size_t insert_pos_children = node->Parent->GetInsertPosition(node);
	size_t insert_pos_element = insert_pos_children - 1;

	//Space
	TNote *parent_elements_new = new TNote[node->Parent->ElementsNum + 1];
	size_t pos = 0;
	for (size_t i = 0; i < node->Parent->ElementsNum; i++) {
		if (pos == insert_pos_element) {
			pos++;
		}
		parent_elements_new[pos] = node->Parent->Elements[i];
		pos++;
	}
	node->Parent->ElementsNum++;
	delete [] node->Patent->Elements;
	node->Parent->Elements = parent_elements_nenode->Parent->Children[insert_pos_children]w;

	TBTreeNode **parent_children_new = new TBTreeNode *[node->Parent->ChildrenNum + 1];
	pos = 0;
	for (size_t i = 0; i < node->Patent->ChildrenNum; i++) {
		if (pos == insert_pos_children) {
			pos++;
		}
		parent_children_new[pos] = node->Parent->Children[i];
		pos++;
	}
	node->Parent->ChildrenNum++;
	delete [] node->Parent->Children;
	node->Parent->Children = parent_children_new;


	//Inserting
	node->Parent->Elements[insert_pos_element] = middle_element;

	node->Parent->Children[insert_pos_children] = new TBTreeNode(node->Parent);
	node->Parent->Children[insert_pos_children]->Elements = arr2_elements;
	node->Parent->Children[insert_pos_children]->ElementsNum = arr2_elements_len;
	node->Parent->Children[insert_pos_children]->Children = arr2_children;
	node->Parent->Children[insert_pos_children]->ChildrenNum = arr2_children_len;

	delete [] node->Elements;
	node->Elements = arr1_elements;
	node->ElementsNum = arr1_elements_len;
	delete [] node->Children;
	node->Children = arr1_children;
	node->ChildrenNum = arr1_children_len;
}

TBTreeNode *TBTree::Search(TNumber key) {

}

void TBTree::Push(TNote element) {

}

TNote TBTree::Pop(TNumber key) {

}
