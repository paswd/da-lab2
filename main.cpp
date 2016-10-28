#include <iostream>
#include <cstdlib>
#include "btree.h"

using namespace std;

int main() {
	const size_t size = 26;
	const size_t tree_param = 3;

	TNote arr[size];
	for (int i = 0; i < size; i++) {
		int j = i;
		//int j = size - i - 1;

		arr[j].Num = (TNumber) i;
		arr[j].Key[0] = 'a' + i;
		arr[j].Key[1] = 'a' + i;
		arr[j].Key[2] = 'a' + i;
		arr[j].Key[3] = 'a' + i;
		arr[j].Key[4] = '\0';
	}

	TBTree *tree = new TBTree(tree_param);
	for (size_t i = 0; i < size; i++) {
		cout << "Num: " << i << endl;
		tree->Push(arr[i]);
		tree->Print();
		cout << endl;
	}
	TNote res;
	res.Num = 102;
	res.Key[0] = 'u';
	res.Key[1] = 'u';
	res.Key[2] = 'u';
	res.Key[3] = 'u';
	res.Key[4] = '\0';
	TSearchRes search = tree->Search(res.Key);
	tree->Unite(search.Node, search.Pos);
	tree->Print();
	//cout << "<<SPLITTING>>" << endl;
	//search.Node->PrintElements();
	//tree->Split(search.Node);
	//tree->Print();
	/*TNote res;
	res.Num = 102;
	res.Key[0] = 'd';
	res.Key[1] = 'f';
	res.Key[2] = 'g';
	res.Key[3] = 'a';
	res.Key[4] = '\0';
	tree->Push(res);
	tree->Print();*/

	/*TNote del;
	del.Num = 99;
	del.Key[0] = 'n';
	del.Key[1] = 'n';
	del.Key[2] = 'n';
	del.Key[3] = 'n';
	del.Key[4] = '\0';
	cout << "Input: " << del.Key << endl;
	TNote p_res = tree->Pop(del.Key);
	cout << "Popped value: " << p_res.Key << endl;
	tree->Print();*/


	/*cout << "Uniting... ";
	tree->Unite(tree->Root, 2);
	cout << "OK" << endl;
	tree->Print();*/
	cout << "Deleting... ";
	delete tree;
	cout << "OK" << endl;
	/*arr[0].key = "xsca\0";
	arr[1].key = "acsc\0";
	arr[2].key = "acseece\0";
	arr[3].key = "acesec\0";
	arr[4].key = "scesc\0";
	arr[5].key = "secse\0";
	arr[6].key = "secse\0";
	arr[7].key = "secsea\0";
	arr[8].key = "aewcaew\0";
	arr[9].key = "aecasaw\0";*/
	return 0;
}
