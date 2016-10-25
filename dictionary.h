#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

typedef unsigned long long TNumber;

//Universal functions block
TNumber min(TNumber num1, TNumber num2);
TNumber max(TNumber num1, TNumber num2);

//Content blocks
class TNote {
public:
	char key[257];
	TNumber num;
};


//B-Tree block
class TBTreeNode {
public:
	//Fields
	//bool IsLeaf;
	TNote *Elements;
	size_t ElementsNum;

	TBTreeNode **Children;
	size_t ChilrenNum;
	
	TBTreeNode *Parent;

	//Methods
	TBTreeNode(TBTreeNode *parent);
	~TBTreeNode();

	//void InsertElementToArray(TNode element);
	size_t GetInsertPosition(TBTreeNode *child);
};

class TBTree {
private:
	TBTreeNode *Root;
	size_t FactorT;

	void SplitChild(TBTreeNode *node);

public:
	TBTree(size_t factor);
	~TBTree();

	TBTreeNode *Search(TNumber key);
	void Push(TNote element);
	TNote Pop(TNumber key);
};


//Dictionary block

#endif
