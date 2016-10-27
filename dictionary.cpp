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

char ToLowerCase(char letter) {
	if (letter >= 'A' && letter <= 'Z') {
		letter += 'a' - 'A';
	}
	return letter;
}

int StringComparison(char *str1, char *str2) {
	for (size_t i = 0; true; i++) {
		//cout << str1 << endl;
		//cout << str2 << endl;
		if (str1[i] == '\0' && str2[i] != '\0') {
			return -1;
		}
		if (str1[i] != '\0' && str2[i] == '\0') {
			return 1;
		}
		if (str1[i] == '\0' && str2[i] == '\0') {
			return 0;
		}
		if (ToLowerCase(str1[i]) == ToLowerCase(str2[i])) {
			continue;
		}
		if (ToLowerCase(str1[i]) > ToLowerCase(str2[i])) {
			return 1;
		} else {
			return -1;
		}
	}
}



TBTreeNode::TBTreeNode(TBTreeNode *parent, bool is_leaf) {
	/*this->ElementsNum = size;
	this->Elements = new TNote[this->ElementsNum];
	for (size_t i = 0; i < this->ElementsNum; i++) {
		this->Elements[i] = values[i];
	}
	this->ChildrenNum = 0;
	this->Children = NULL;*/
	this->Parent = parent;

	this->Elements = NULL;
	this->ElementsNum = 0;

	this->Children = NULL;
	this->ChildrenNum = 0;

	this->IsLeaf = is_leaf;
}

TBTreeNode::~TBTreeNode() {
	delete [] this->Elements;
	for (size_t i = 0; i < this->ChildrenNum; i++) {
		delete this->Children[i];
	}
	delete [] this->Children;
}

void TBTreeNode::InsertElementToLeaf(TNote element) {
	//cout << "Insert::Element " << element.Key << ":" << element.Num << endl;
	//cout << "Insert::Point1" << endl;
	if (!this->IsLeaf) {
		cout << "Node is not a leaf" << endl;
		//this->Print(0);
		return;
	}
	//cout << "Insert::Point2" << endl;
	//Binnary search
	size_t left = 0;
	size_t right = this->ElementsNum - 1;
	if (this->ElementsNum == 0) {
		right = 0;
	}
	//cout << "Insert::Point3" << endl;
	//cout << left << endl << right << endl;
	while (right > left) {
		size_t tmp_size = right - left + 1;
		size_t middle = tmp_size / 2 + left;
		//cout << "Insert::InPoint1" << endl;
		//if (element.num < this->Elements[middle]) {
		if (StringComparison(element.Key, this->Elements[middle].Key) == -1) {
			right = middle - 1;
		} else {
			left = middle;
		}
	}
	//cout << "Insert::Point4" << endl;
	//Insert element
	size_t insert_pos = left;
	if (this->ElementsNum != 0) {
		int cmp = StringComparison(element.Key, this->Elements[insert_pos].Key);
		if (insert_pos != 0 || cmp != -1) {
			insert_pos++;
		}
	}

	TNote *new_elements = new TNote[this->ElementsNum + 1];
	size_t pos = 0;
	//cout << "Insert::Point5" << endl;
	for (size_t i = 0; i < this->ElementsNum; i++) {
		if (i == insert_pos) {
			pos++;
		}
		new_elements[pos] = this->Elements[i];
		pos++;
	}
	new_elements[insert_pos] = element;
	//cout << "Insert::Point6" << endl;
	delete [] this->Elements;
	this->Elements = new_elements;
	this->ElementsNum++;
}

size_t TBTreeNode::GetInsertPosition(TBTreeNode *child) {
	for (size_t i = 0; i < this->ChildrenNum; i++) {
		if (this->Children[i] == child) {
			return i;
		}
	}
	return 0;
}

void TBTreeNode::Print(size_t lvl) {
	for (size_t i = 0; i < this->ElementsNum; i++) {
		for (size_t j = 0; j < lvl; j++) {
			cout << "  ";
		}
		cout << this->Elements[i].Key << ":" << this->Elements[i].Num << endl;
	}
	cout << "----------" << endl;
	for (size_t i = 0; i < this->ChildrenNum; i++) {
		this->Children[i]->Print(lvl + 1);
	}
}

/*TBTreeNode *TBTreeNode::Search(char *key) {
	for (size_t i = 0; )
}*/



TBTree::TBTree(size_t factor) {
	this->Root = NULL;
	this->FactorT = factor;
}

TBTree::~TBTree() {
	delete this->Root;
}

size_t TBTree::Split(TBTreeNode *node) {
	//Separate arrays
	size_t middle = node->ElementsNum / 2;
	TNote middle_element = node->Elements[middle];

	size_t arr1_elements_len = middle;
	size_t arr2_elements_len = node->ElementsNum - middle - 1;

	TNote *arr1_elements = new TNote[arr1_elements_len];
	TNote *arr2_elements = new TNote[arr2_elements_len];
	size_t arr1_children_len = 0;
	size_t arr2_children_len = 0;

	TBTreeNode **arr1_children = NULL;
	TBTreeNode **arr2_children = NULL;
	if (!node->IsLeaf) {
		arr1_children_len = arr1_elements_len + 1;
		arr2_children_len = arr2_elements_len + 1;

		arr1_children = new TBTreeNode *[arr1_children_len];
		arr2_children = new TBTreeNode *[arr2_children_len];
	}

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
	if (!node->IsLeaf) {
		for (size_t i = 0; i < node->ChildrenNum; i++) {
			if (i <= middle) {
				arr1_children[i] = node->Children[i];
			} else {
				arr2_children[i - middle - 1] = node->Children[i];
			}
		}
	}

	if (node->Parent == NULL) {
		node->Parent = new TBTreeNode(NULL, false);
		node->Parent->ChildrenNum = 1;
		node->Parent->Children = new TBTreeNode *[node->Parent->ChildrenNum];
		node->Parent->Children[node->Parent->ChildrenNum - 1] = node;
		this->Root = node->Parent;
	}

	size_t insert_pos_element = node->Parent->GetInsertPosition(node);
	size_t insert_pos_children = insert_pos_element + 1;

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
	delete [] node->Parent->Elements;
	node->Parent->Elements = parent_elements_new;

	TBTreeNode **parent_children_new = new TBTreeNode *[node->Parent->ChildrenNum + 1];
	pos = 0;
	for (size_t i = 0; i < node->Parent->ChildrenNum; i++) {
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

	node->Parent->Children[insert_pos_children] = new TBTreeNode(node->Parent, node->IsLeaf);
	node->Parent->Children[insert_pos_children]->IsLeaf = node->IsLeaf;

	node->Parent->Children[insert_pos_children]->Elements = arr2_elements;
	node->Parent->Children[insert_pos_children]->ElementsNum = arr2_elements_len;
	if (!node->IsLeaf) {
		node->Parent->Children[insert_pos_children]->Children = arr2_children;
		node->Parent->Children[insert_pos_children]->ChildrenNum = arr2_children_len;
	}

	delete [] node->Elements;
	node->Elements = arr1_elements;
	node->ElementsNum = arr1_elements_len;

	if (!node->IsLeaf) {
		delete [] node->Children;
		node->Children = arr1_children;
		node->ChildrenNum = arr1_children_len;
	}

	if (node->Parent->ElementsNum > this->FactorT * 2 - 1) {
		this->Split(node->Parent);
	}

	return insert_pos_element;
}

TSearchRes TBTree::Search(char *key) {
	TSearchRes result;
	TBTreeNode *node = this->Root;
	result.Node = node;
	result.Pos = 0;
	result.IsFound = false;
	//*node_res = node;

	while (node != NULL) {
		//cout << "Search::Point1" << endl;
		bool is_maximal = true;
		for (size_t i = 0; i < node->ElementsNum; i++) {
			int cmp = StringComparison(key, node->Elements[i].Key);
			//cout << "Str::Comp " << cmp << endl;
			if (cmp == 0) {
				//cout << "Strings are equal" << endl;
				//*pos = i;
				result.Pos = i;
				result.IsFound = true;
				return result;
				//return true;
			}
			
			if (cmp < 0) {
				is_maximal = false;
				if (!node->IsLeaf) {
					node = node->Children[i];
				}
				break;
			}
		}
		//cout << "Search::Point2" << endl;
		if (node->IsLeaf) {
			//*node_res = node;
			result.Node = node;
			result.IsFound = false;
			//return false;
			return result;
		}
		if (is_maximal) {
			node = node->Children[node->ChildrenNum - 1];
		}
		//cout << "Search::Point3" << endl;
		if (node != NULL) {
			//*node_res = node;
			result.Node = node;
			//cout << "Node::true" << endl;
		}
	}
	result.IsFound = false;
	//return false;
	return result;
}

void TBTree::Push(TNote element) {
	cout << "Push::Element " << element.Key << ":" << element.Num << endl;
	//cout << "In" << endl;
	
	TSearchRes search_res = this->Search(element.Key);
	TBTreeNode *CurrentNode = search_res.Node;
	//cout << "Push::Searched" << endl;

	if (search_res.IsFound) {
		cout << "Exist" << endl;
		return;
	}

	if (CurrentNode == NULL) {
		CurrentNode = new TBTreeNode(NULL, true);
		this->Root = CurrentNode;
	}

	if (CurrentNode->ElementsNum >= this->FactorT * 2 - 1) {
		size_t insert_pos = this->Split(CurrentNode);
		if (StringComparison(element.Key, CurrentNode->Parent->Elements[insert_pos].Key) != -1) {
			CurrentNode = CurrentNode->Parent->Children[insert_pos + 1];
		}
	}

	CurrentNode->InsertElementToLeaf(element);
	//cout << "Push::Point" << endl;
}

/*TNote TBTree::Pop(TNumber key) {
	
}*/

void TBTree::Print() {
	cout << "Tree printing..." << endl;
	this->Root->Print(0);
	cout << "Finish printing" << endl;
}
