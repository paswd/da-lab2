#include <iostream>
#include <cstdlib>
#include "dictionary.h"

using namespace std;

int main() {
	const size_t size = 26;
	TNote arr[size];
	for (int i = 0; i < size; i++) {
		//int j = size - i - 1;
		arr[i].num = (TNumber) i;
		arr[i].key[0] = 'a' + i;
		arr[i].key[1] = 'a' + i;
		arr[i].key[2] = 'a' + i;
		arr[i].key[3] = 'a' + i;
		arr[i].key[4] = '\0';
	}

	TBTree *tree = new TBTree(4);
	for (size_t i = 0; i < size; i++) {
		cout << "Num: " << i << endl;
		tree->Push(arr[i]);
		tree->Print();
		cout << endl;
	}
	TNote res;
	res.num = 102;
	res.key[0] = 'd';
	res.key[1] = 'f';
	res.key[2] = 'g';
	res.key[3] = 'a';
	res.key[4] = '\0';
	tree->Push(res);
	tree->Print();
	delete tree;
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
