#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "btree.h"

using namespace std;

int main() {
	const size_t factor_t = 3;
	TBTree *tree = new TBTree(factor_t);
	char in[8];

	while (!cin.eof()) {
		cin >> in;
		char operation = in[0];
		bool out_log = false;

		TNote in_note;
		char key[257];
		TSearchRes search_res;

		switch (operation) {
			case '+':
				//TNote in_note;
				cin >> in_note.Key >> in_note.Num;
				tree->Push(in_note);
				break;
			case '-':
				//char *key;
				cin >> key;
				/*for (size_t i = 0; key[i] != '\0' && i < 255; i++) {
					cout << i << endl;
				}*/
				tree->Pop(key);
				break;
			case '!':
				/*char *param;
				char *path;
				cin >> param;*/
				break;
			case '>':
				tree->Print();
				break;
			case '~':
				out_log = true;
				break;
			default:
				TSearchRes search_res = tree->Search(in);
				if (search_res.IsFound) {
					cout << "OK: " << search_res.Element.Num << endl;
				} else {
					cout << "NoSuchWord" << endl;
				}
				break;
		}
		if (out_log) {
			cout << "Goodbye" << endl;
			break;
		}
	}
	delete tree;

	return 0;
}
