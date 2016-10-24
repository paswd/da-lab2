#include <iostream>

using namespace std;

typedef unsigned long long Number;

class TBTreeNode {
public:
	Number *Keys;
	TBTreeNode **Children;
	
	size_t KeysNum;
};

class TBTree {
private:
	TBTreeNode *Root;
	size_t FactorT;

public:
	TBTree(size_t factor);
	~TBTree();


};
