#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include "btree.h"

using namespace std;

int main() {
	const size_t factor_t = 20;
	TBTree *tree = new TBTree(factor_t);
	char in[8];

	while (!cin.eof()) {
		cin >> in;
		if (cin.eof()) {
			break;
		}
		char operation = in[0];
		bool out_log = false;

		TNote in_note;
		char *str;
		TSearchRes search_res;
		char *file_path;

		char save[] = "Save";
		char load[] = "Load";

		if (operation == '\n') {
			continue;
		}

		switch (operation) {
			case '+':
				//TNote in_note;
				cin >> in_note.Key >> in_note.Num;
				tree->Push(in_note);
				break;
			case '-':
				//char *key;
				cin >> str;
				/*for (size_t i = 0; key[i] != '\0' && i < 255; i++) {
					cout << i << endl;
				}*/
				tree->Pop(str);
				break;
			case '!':
				/*char *param;
				char *path;
				cin >> param;*/
				cin >> str;
				cin >> file_path;
				if (StringComparison(str, save) == 0) {
					tree->Save(file_path);
					break;
				}
				if (StringComparison(str, load) == 0) {
					tree->Load(file_path);
					break;
				}
				/*if (str == "Load" || str == "load" || str == "LOAD") {
					tree->Load(file_path);
					break;
				}
				if (str == "Save" || str == "save" || str == "SAVE") {
					tree->Save(file_path);
					break;
				}*/
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
