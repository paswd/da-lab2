#ifndef _BTREE_H_
#define _BTREE_H_

#include <cstdio>

typedef unsigned long long TNumber;
const size_t FILE_PREFIX_SIZE = 8;
const size_t KEY_STR_LEN = 259;

//Universal functions block
TNumber min(TNumber num1, TNumber num2);
TNumber max(TNumber num1, TNumber num2);
int StringComparison(char *str1, char *str2);
char ToLowerCase(char letter);

//Content blocks
class TNote {
public:
	char Key[KEY_STR_LEN];
	TNumber Num;

	TNote();
};


//B-Tree block
class TBTreeNode {
public:
	//Fields
	bool IsLeaf;
	TBTreeNode *Parent;

	TNote *Elements;
	size_t ElementsNum;

	TBTreeNode **Children;
	size_t ChildrenNum;

	//Methods
	TBTreeNode(TBTreeNode *parent, bool is_leaf);
	~TBTreeNode();

	void InsertElementToLeaf(TNote element);
	void DeleteElementFromLeaf(size_t pos);
	size_t GetInsertPosition(TBTreeNode *child);
	void Print(size_t lvl);
	void PrintElements();

	//Files
	void Save(FILE *out);
};
class TSearchRes {
public:
	TNote Element;
	bool IsFound;
	TBTreeNode *Node;
	size_t Pos;
};

class TBTree {
private:
//public:
	TBTreeNode *Root;
	size_t FactorT;
	char FilePrefix[FILE_PREFIX_SIZE];

	size_t Split(TBTreeNode *node);
	void Unite(TBTreeNode *node, size_t pos);
	void Balance(TBTreeNode *CurrentNode, size_t pos);

	void RotateLeft(TBTreeNode *CurrentNode);
	void RotateRight(TBTreeNode * CurrentNode);

	void TreeDestroy(TBTreeNode *node);
	TBTreeNode *LoadNodes(FILE *in, TBTreeNode *parent);

public:
	TBTree(size_t factor);
	~TBTree();

	TSearchRes Search(char *key);
	void Push(TNote element);
	TNote Pop(char *key);
	void Print();

	//Files
	bool Save(char *path);
	bool Load(char *path);
};

#endif
