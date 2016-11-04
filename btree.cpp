#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include "btree.h"

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
	//cout << str1 << endl << str2 << endl;
	for (size_t i = 0; true; i++) {
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


TNote::TNote() {
	this->Num = 0;
}



TBTreeNode::TBTreeNode(TBTreeNode *parent, bool is_leaf) {
	this->Parent = parent;

	this->Elements = NULL;
	this->ElementsNum = 0;

	this->Children = NULL;
	this->ChildrenNum = 0;

	this->IsLeaf = is_leaf;
}

TBTreeNode::~TBTreeNode() {
	free(this->Elements);
	free(this->Children);
}

void TBTreeNode::InsertElementToLeaf(TNote element) {
	if (!this->IsLeaf) {
		cout << "Node is not a leaf" << endl;
		return;
	}

	//Binnary search
	size_t left = 0;
	size_t right = this->ElementsNum - 1;
	if (this->ElementsNum == 0) {
		right = 0;
	}
	while (right > left) {
		size_t tmp_size = right - left + 1;
		size_t middle = tmp_size / 2 + left;
		if (StringComparison(element.Key, this->Elements[middle].Key) == -1) {
			right = middle - 1;
		} else {
			left = middle;
		}
	}

	//Insert element
	size_t insert_pos = left;
	if (this->ElementsNum != 0) {
		int cmp = StringComparison(element.Key, this->Elements[insert_pos].Key);
		if (insert_pos != 0 || cmp != -1) {
			insert_pos++;
		}
	}
	this->ElementsNum++;
	this->Elements = (TNote *) realloc(this->Elements, this->ElementsNum * sizeof(TNote));
	for (size_t i = this->ElementsNum - 1; i > insert_pos; i--) {
		this->Elements[i] = this->Elements[i - 1];
	}
	this->Elements[insert_pos] = element;
}

void TBTreeNode::DeleteElementFromLeaf(size_t pos) {
	this->ElementsNum--;
	for (size_t i = pos; i < this->ElementsNum; i++) {
		this->Elements[i] = this->Elements[i + 1];
	}
	this->Elements = (TNote *) realloc(this->Elements, this->ElementsNum * sizeof(TNote));
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

void TBTreeNode::PrintElements() {
	cout << "NodeContent::";
	for (size_t i = 0; i < this->ElementsNum; i++) {
		cout << this->Elements[i].Key << " ";
	}
	cout << endl;
}



TBTree::TBTree(size_t factor) {
	this->Root = NULL;
	this->FactorT = factor;

	//Creating file prefix
	this->FilePrefix[0] = 'P';
	this->FilePrefix[1] = 'a';
	this->FilePrefix[2] = 's';
	this->FilePrefix[3] = 'W';
	this->FilePrefix[4] = 'D';
	this->FilePrefix[5] = 'd';
	this->FilePrefix[6] = 'a';
	this->FilePrefix[7] = '\0';
}

TBTree::~TBTree() {
	if (this->Root != NULL) {
		this->TreeDestroy(this->Root);
	}
}

void TBTree::TreeDestroy(TBTreeNode *node) {
	for (size_t i = 0; i < node->ChildrenNum; i++) {
		if (i != node->ChildrenNum - 1) {
			delete [] node->Elements[i].Key;
		}
		this->TreeDestroy(node->Children[i]);
	}
	delete node;
}

size_t TBTree::Split(TBTreeNode *node) {
	//Separate arrays
	size_t middle = node->ElementsNum / 2;
	TNote middle_element = node->Elements[middle];

	size_t arr1_elements_len = middle;
	size_t arr2_elements_len = node->ElementsNum - middle - 1;

	TNote *arr2_elements = (TNote *) calloc(arr2_elements_len, sizeof(TNote));
	for (size_t i = middle + 1; i < node->ElementsNum; i++) {
		arr2_elements[i - middle - 1] = node->Elements[i];
	}
	TNote *arr1_elements = (TNote *) realloc(node->Elements, arr1_elements_len * sizeof(TNote));
	size_t arr1_children_len = 0;
	size_t arr2_children_len = 0;

	TBTreeNode **arr1_children = NULL;
	TBTreeNode **arr2_children = NULL;
	if (!node->IsLeaf) {
		arr1_children_len = arr1_elements_len + 1;
		arr2_children_len = arr2_elements_len + 1;

		arr2_children = (TBTreeNode **) calloc(arr2_children_len, sizeof(TBTreeNode *));
		for (size_t i = middle + 1; i < node->ChildrenNum; i++) {
			arr2_children[i - middle - 1] = node->Children[i];
		}
		arr1_children = (TBTreeNode **) realloc(node->Children, arr1_children_len * sizeof(TBTreeNode *));
	}

	if (node->Parent == NULL) {
		node->Parent = new TBTreeNode(NULL, false);
		node->Parent->ChildrenNum = 1;
		node->Parent->Children = (TBTreeNode **) calloc(node->Parent->ChildrenNum, sizeof(TBTreeNode *));
		node->Parent->Children[node->Parent->ChildrenNum - 1] = node;
		this->Root = node->Parent;
	}

	if (node->Parent->ElementsNum >= this->FactorT * 2 - 1) {
		this->Split(node->Parent);
	}

	size_t insert_pos_element = node->Parent->GetInsertPosition(node);
	size_t insert_pos_children = insert_pos_element + 1;

	//Space
	node->Parent->ElementsNum++;
	node->Parent->Elements = (TNote *) realloc(node->Parent->Elements, node->Parent->ElementsNum * sizeof(TNote));
	for (size_t i = node->Parent->ElementsNum - 1; i > insert_pos_element; i--) {
		node->Parent->Elements[i] = node->Parent->Elements[i - 1];
	}

	node->Parent->ChildrenNum++;
	node->Parent->Children = (TBTreeNode **) realloc(node->Parent->Children, node->Parent->ChildrenNum * sizeof(TBTreeNode *));
	for (size_t i = node->Parent->ChildrenNum - 1; i > insert_pos_element; i--) {
		node->Parent->Children[i] = node->Parent->Children[i - 1];
	}

	//Inserting
	node->Parent->Elements[insert_pos_element] = middle_element;

	node->Parent->Children[insert_pos_children] = new TBTreeNode(node->Parent, node->IsLeaf);
	node->Parent->Children[insert_pos_children]->IsLeaf = node->IsLeaf;

	node->Parent->Children[insert_pos_children]->Elements = arr2_elements;
	node->Parent->Children[insert_pos_children]->ElementsNum = arr2_elements_len;

	if (!node->IsLeaf) {
		TBTreeNode *ths_tmp = node->Parent->Children[insert_pos_children];
		ths_tmp->Children = arr2_children;
		ths_tmp->ChildrenNum = arr2_children_len;
		for (size_t i = 0; i < ths_tmp->ChildrenNum; i++) {
			ths_tmp->Children[i]->Parent = ths_tmp;
		}
	}

	node->Elements = arr1_elements;
	node->ElementsNum = arr1_elements_len;

	if (!node->IsLeaf) {
		node->Children = arr1_children;
		node->ChildrenNum = arr1_children_len;
	}

	return insert_pos_element;
}

void TBTree::Unite(TBTreeNode *node, size_t pos) {
	if (node->IsLeaf) {
		cout << "Unite error: Node is leaf" << endl;
		return;
	}
	if (pos >= node->ElementsNum) {
		cout << "Unite error: Unable position" << endl;
		return;
	}

	//Creating united arrays
	size_t new_arr_elements_len = 1;
	new_arr_elements_len += node->Children[pos]->ElementsNum;
	new_arr_elements_len += node->Children[pos + 1]->ElementsNum;

	TNote *new_arr_elements = (TNote *) realloc(node->Children[pos]->Elements, new_arr_elements_len * sizeof(TNote));
	new_arr_elements[node->Children[pos]->ElementsNum] = node->Elements[pos];
	for (size_t i = node->Children[pos]->ElementsNum + 1; i < new_arr_elements_len; i++) {
		size_t tmp_pos = i - node->Children[pos]->ElementsNum - 1;
		new_arr_elements[i] = node->Children[pos + 1]->Elements[tmp_pos];
	}

	size_t new_arr_children_len = 0;
	TBTreeNode **new_arr_children = NULL;
	if (!node->Children[pos]->IsLeaf) {
		new_arr_children_len = node->Children[pos]->ChildrenNum;
		new_arr_children_len += node->Children[pos + 1]->ChildrenNum;
		new_arr_children = (TBTreeNode **) realloc(node->Children[pos]->Children, new_arr_children_len * sizeof(TBTreeNode *));

		for (size_t i = node->Children[pos]->ChildrenNum; i < new_arr_children_len; i++) {
			size_t tmp_pos = i - node->Children[pos]->ChildrenNum;
			new_arr_children[i] = node->Children[pos + 1]->Children[tmp_pos];
		}
	}

	//Deleting second branch and creating united child in first branch
	delete node->Children[pos + 1];

	node->Children[pos]->Elements = new_arr_elements;
	node->Children[pos]->ElementsNum = new_arr_elements_len;
	node->Children[pos]->Children = new_arr_children;
	node->Children[pos]->ChildrenNum = new_arr_children_len;

	//Creating new parent arrays
	size_t new_parent_arr_elements_len = node->ElementsNum - 1;
	size_t new_parent_arr_children_len = node->ChildrenNum - 1;

	for (size_t i = pos + 1; i < node->ElementsNum; i++) {
		node->Elements[i - 1] = node->Elements[i];
	}
	for (size_t i = pos + 2; i < node->ChildrenNum; i++) {
		node->Children[i - 1] = node->Children[i];
	}

	node->Elements = (TNote *) realloc(node->Elements, new_parent_arr_elements_len * sizeof(TNote));
	node->Children = (TBTreeNode **) realloc(node->Children, new_parent_arr_children_len * sizeof(TBTreeNode *));

	//Refreshing arrays
	node->ElementsNum = new_parent_arr_elements_len;
	node->ChildrenNum = new_parent_arr_children_len;
	for (size_t i = 0; i < node->Children[pos]->ChildrenNum; i++) {

		node->Children[pos]->Children[i]->Parent = node->Children[pos];
	}

	size_t tmp_pos = 0;
	if (node->Parent != NULL) {
		for (size_t i = 0; i < node->Parent->ChildrenNum; i++) {
			if (node == node->Parent->Children[i]) {
				tmp_pos = i;
				break;
			}
		}
	}

	this->Balance(node, tmp_pos);
}

void TBTree::Balance(TBTreeNode *CurrentNode, size_t pos) {
	if (CurrentNode == NULL) {
		return;
	}
	if (CurrentNode->ElementsNum == 0 && CurrentNode->Parent == NULL) {
		CurrentNode = CurrentNode->Children[0];
		delete this->Root;
		this->Root = CurrentNode;
		this->Root->Parent = NULL;
		return;
	}
	if (CurrentNode->ElementsNum >= this->FactorT - 1 || CurrentNode->Parent == NULL) {
		return;
	}

	bool is_left_larger = false;
	bool is_right_larger = false;

	if (pos > 0) {
		if (CurrentNode->Parent->Children[pos - 1]->ElementsNum > this->FactorT - 1) {
			is_left_larger = true;
		}
	}
	if (pos < CurrentNode->Parent->ChildrenNum - 1) {
		if (CurrentNode->Parent->Children[pos + 1]->ElementsNum > this->FactorT - 1) {
			is_right_larger = true;
		}
	}

	if (!is_left_larger && !is_right_larger) {
		if (pos > 0) {
			this->Unite(CurrentNode->Parent, pos - 1);
		} else {
			this->Unite(CurrentNode->Parent, pos);
		}
		return;
	}
	if (is_left_larger) {
		this->RotateRight(CurrentNode);
	} else {
		this->RotateLeft(CurrentNode);
	}
}

void TBTree::RotateLeft(TBTreeNode *CurrentNode) {
	size_t pos = 0;
	for (size_t i = 0; i < CurrentNode->Parent->ChildrenNum; i++) {
		if (CurrentNode == CurrentNode->Parent->Children[i]) {
			pos = i;
			break;
		}
	}

	size_t right_first = 0;
	TNote k1 = CurrentNode->Parent->Children[pos + 1]->Elements[right_first];
	TNote k2 = CurrentNode->Parent->Elements[pos];
	CurrentNode->Parent->Children[pos + 1]->DeleteElementFromLeaf(right_first);
	CurrentNode->Parent->Elements[pos] = k1;

	CurrentNode->ElementsNum++;
	CurrentNode->Elements = (TNote *) realloc(CurrentNode->Elements, CurrentNode->ElementsNum * sizeof(TNote));
	CurrentNode->Elements[CurrentNode->ElementsNum - 1] = k2;

	if (!CurrentNode->IsLeaf) {
		TBTreeNode *t_right = CurrentNode->Parent->Children[pos + 1];
		TBTreeNode *tmp = t_right->Children[right_first];

		for (size_t i = 1; i < t_right->ChildrenNum; i++) {
			t_right->Children[i - 1] = t_right->Children[i];
		}
		t_right->ChildrenNum--;
		t_right->Children = (TBTreeNode **) realloc(t_right->Children, t_right->ChildrenNum * sizeof(TBTreeNode *));

		tmp->Parent = CurrentNode;
		CurrentNode->ChildrenNum++;
		CurrentNode->Children = (TBTreeNode **) realloc(CurrentNode->Children, CurrentNode->ChildrenNum * sizeof(TBTreeNode *));
		CurrentNode->Children[CurrentNode->ChildrenNum - 1] = tmp;
	}
}

void TBTree::RotateRight(TBTreeNode *CurrentNode) {
	size_t pos = 0;
	for (size_t i = 0; i < CurrentNode->Parent->ChildrenNum; i++) {
		if (CurrentNode == CurrentNode->Parent->Children[i]) {
			pos = i;
			break;
		}
	}
	//cout << "Rotate::Point1" << endl;
	size_t left_last = CurrentNode->Parent->Children[pos - 1]->ElementsNum - 1;
	TNote k1 = CurrentNode->Parent->Children[pos - 1]->Elements[left_last];
	TNote k2 = CurrentNode->Parent->Elements[pos - 1];
	CurrentNode->Parent->Children[pos - 1]->DeleteElementFromLeaf(left_last);
	CurrentNode->Parent->Elements[pos - 1] = k1;

	CurrentNode->ElementsNum++;
	CurrentNode->Elements = (TNote *) realloc(CurrentNode->Elements, CurrentNode->ElementsNum * sizeof(TNote));
	for (size_t i = CurrentNode->ElementsNum - 1; i > 0; i--) {
		CurrentNode->Elements[i] = CurrentNode->Elements[i - 1];
	}
	CurrentNode->Elements[0] = k2;

	if (!CurrentNode->IsLeaf) {
		TBTreeNode *t_left = CurrentNode->Parent->Children[pos - 1];
		TBTreeNode *tmp = t_left->Children[left_last + 1];

		t_left->ChildrenNum--;
		t_left->Children = (TBTreeNode **) realloc(t_left->Children, t_left->ChildrenNum * sizeof(TBTreeNode *));

		tmp->Parent = CurrentNode;
		CurrentNode->ChildrenNum++;
		CurrentNode->Children = (TBTreeNode **) realloc(CurrentNode->Children, CurrentNode->ChildrenNum * sizeof(TBTreeNode *));
		for (size_t i = CurrentNode->ChildrenNum - 1; i > 0; i--) {
			CurrentNode->Children[i] = CurrentNode->Children[i - 1];
		}
		CurrentNode->Children[0] = tmp;
	}
}

TSearchRes TBTree::Search(char *key) {
	TSearchRes res;
	TBTreeNode *node = this->Root;
	res.Node = node;
	res.Pos = 0;
	res.IsFound = false;

	while (node != NULL) {

		//Binnary search
		size_t left = 0;
		size_t right = node->ElementsNum - 1;
		if (node->ElementsNum == 0) {
			right = 0;
		}
		while (right > left) {
			size_t tmp_size = right - left + 1;
			size_t middle = tmp_size / 2 + left;
			int cmp = StringComparison(key, node->Elements[middle].Key);
			if (cmp == 0) {
				res.Element = node->Elements[middle];
				res.Pos = middle;
				res.IsFound = true;
				res.Node = node;
				return res;
			}
			if (cmp == -1) {
				right = middle - 1;
			} else {
				left = middle;
			}
		}
		int cmp = StringComparison(key, node->Elements[left].Key);
		if (cmp == 0) {
			res.Element = node->Elements[left];
			res.Pos = left;
			res.IsFound = true;
			return res;
		}
		if (!node->IsLeaf) {
			if (cmp < 0) {
				node = node->Children[left];
			} else {
				node = node->Children[left + 1];
			}
		} else {
			res.Node = node;
			break;
		}
		if (node != NULL) {
			res.Node = node;
		}
	}
	res.IsFound = false;
	return res;
}

void TBTree::Push(TNote element) {
	
	TSearchRes search_res = this->Search(element.Key);
	TBTreeNode *CurrentNode = search_res.Node;

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
	cout << "OK" << endl;
}

TNote TBTree::Pop(char *key) {
	TNote res;
	res.Num = 0;
	res.Key = NULL;
	TSearchRes search_res = this->Search(key);
	if (!search_res.IsFound) {
		cout << "NoSuchWord" << endl;
		return res;
	}
	TBTreeNode *CurrentNode = search_res.Node;
	size_t pos = search_res.Pos;

	res = CurrentNode->Elements[pos];
	while (!CurrentNode->IsLeaf) {
		TBTreeNode *left = CurrentNode->Children[pos];
		TBTreeNode *right = CurrentNode->Children[pos + 1];

		bool is_left_larger = false;
		bool is_right_larger = false;

		if (left->ElementsNum > this->FactorT - 1) {
			is_left_larger = true;
		}

		if (right->ElementsNum > this->FactorT - 1) {
			is_right_larger = true;
		}

		if (!is_left_larger && !is_right_larger) {
			this->Unite(CurrentNode, pos);
			CurrentNode = left;
			pos = CurrentNode->ElementsNum / 2;
			continue;
		}

		if (is_left_larger) {
			this->RotateRight(right);
			CurrentNode = right;
			pos = 0;
		} else {
			this->RotateLeft(left);
			CurrentNode = left;
			pos = CurrentNode->ElementsNum - 1;

		}
	}

	if (CurrentNode == this->Root && CurrentNode->ElementsNum == 1) {
		TreeDestroy(this->Root);
		this->Root = NULL;
		cout << "OK" << endl;
		return res;
	}
	
	CurrentNode->DeleteElementFromLeaf(pos);
	
	size_t parent_pos = 0;
	if (CurrentNode->Parent != NULL) {
		for (size_t i = 0; i < CurrentNode->Parent->ChildrenNum; i++) {
			if (CurrentNode == CurrentNode->Parent->Children[i]) {
				parent_pos = i;
				break;
			}
		}
	}

	this->Balance(CurrentNode, parent_pos);

	cout << "OK" << endl;
	return res;
}

void TBTree::Print() {
	if (this->Root != NULL) {
		this->Root->Print(0);
	} else {
		cout << "Tree is empty" << endl;
	}
}


//FILES

bool TBTree::Save(char *path) {
	FILE *out = fopen(path, "wb");
	if (out == NULL) {
		cout << "ERROR: Couldn't create file" << endl;
		return false;
	}

	//Writing prefix
	fwrite(this->FilePrefix, sizeof(char), FILE_PREFIX_SIZE, out);
	char is_empty = (char) false;
	if (this->Root == NULL) {
		is_empty = (char) true;
		fwrite(&is_empty, 1, 1, out);
		fclose(out);
		cout << "OK" << endl;
		return true;
	}
	fwrite(&is_empty, 1, 1, out);
	this->Root->Save(out);
	fclose(out);
	cout << "OK" << endl;
	return true;
}
bool TBTree::Load(char *path) {
	FILE *in = fopen(path, "rb");

	if (in == NULL) {
		cout << "ERROR: Couldn't open file" << endl;
		return false;
	}

	char out_prefix[FILE_PREFIX_SIZE];

	fread(out_prefix, sizeof(char), FILE_PREFIX_SIZE, in);

	if (StringComparison(this->FilePrefix, out_prefix) != 0) {
		cout << "ERROR: Incorrect file" << endl;
		return false;
	}

	if (this->Root != NULL) {
		this->TreeDestroy(this->Root);
	}
	this->Root = NULL;

	char is_empty;
	fread(&is_empty, 1, 1, in);
	if ((bool) is_empty) {
		this->Root = NULL;
		fclose(in);
		cout << "OK" << endl;
		return true;
	}
	this->Root = this->LoadNodes(in, NULL);
	fclose(in);

	cout << "OK" << endl;
	return true;
}

void TBTreeNode::Save(FILE *out) {
	if (out == NULL) {
		return;
	}
	char is_leaf = (char) this->IsLeaf;
	fwrite(&is_leaf, 1, 1, out);
	fwrite(&this->ElementsNum, sizeof(size_t), 1, out);
	for (size_t i = 0; i < this->ElementsNum; i++) {
		fwrite(&this->Elements[i].KeyLen, sizeof(size_t), 1, out);
		for (size_t j = 0; j < this->Elements[i].KeyLen; j++) {
			fwrite(this->Elements[i].Key + j, sizeof(char), 1, out);
		}
		fwrite(&this->Elements[i].Num, sizeof(TNumber), 1, out);
	}
	for (size_t i = 0; i < this->ChildrenNum; i++) {
		this->Children[i]->Save(out);
	}
}
TBTreeNode *TBTree::LoadNodes(FILE *in, TBTreeNode *parent) {
	if (feof(in)) {
		return NULL;
	}
	char is_leaf;
	fread(&is_leaf, 1, 1, in);
	TBTreeNode *node = new TBTreeNode(parent, (bool) is_leaf);

	fread(&node->ElementsNum, sizeof(size_t), 1, in);
	node->Elements = (TNote *) calloc(node->ElementsNum, sizeof(TNote));
	for (size_t i = 0; i < node->ElementsNum; i++) {
		fread(&node->Elements[i].KeyLen, sizeof(size_t), 1, in);
		node->Elements[i].Key = new char[node->Elements[i].KeyLen];
		for (size_t j = 0; j < node->Elements[i].KeyLen; j++) {
			fread(node->Elements[i].Key + j, sizeof(char), 1, in);
		}
		fread(&node->Elements[i].Num, sizeof(TNumber), 1, in);
	}
	if (!node->IsLeaf) {
		node->ChildrenNum = node->ElementsNum + 1;
		node->Children = (TBTreeNode **) calloc(node->ChildrenNum, sizeof(TBTreeNode *));
		for (size_t i = 0; i < node->ChildrenNum; i++) {
			node->Children[i] = this->LoadNodes(in, node);
		}
	}
	return node;
}
