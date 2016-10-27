#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

typedef unsigned long long TNumber;

//Universal functions block
TNumber min(TNumber num1, TNumber num2);
TNumber max(TNumber num1, TNumber num2);
int StringComparison(char *str1, char *str2);
char ToLowerCase(char letter);

//Content blocks
class TNote {
public:
	char Key[257];
	TNumber Num;
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
	size_t GetInsertPosition(TBTreeNode *child);
	void Print(size_t lvl);
	//void SetRoot();

	//TBTreeNode *Search(char *key);
};
class TSearchRes {
public:
	bool IsFound;
	TBTreeNode *Node;
	size_t Pos;
};

class TBTree {
private:
	TBTreeNode *Root;
	size_t FactorT;

	size_t Split(TBTreeNode *node);
	void Unite(TBTreeNode *node, size_t pos);

	void TreeDestroy(TBTreeNode *node);

public:
	TBTree(size_t factor);
	~TBTree();

	TSearchRes Search(char *key);
	void Push(TNote element);
	TNote Pop(char *key);
	void Print();
};


//Dictionary block

#endif
