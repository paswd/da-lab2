#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <memory>
#include "btree.h"

using namespace std;

int main() {
	const size_t factor_t = 80;
	TBTree *tree = new TBTree(factor_t);
	char in[KEY_STR_LEN];

	while (!cin.eof()) {
		cin >> in;
		if (cin.eof()) {
			break;
		}
		char operation = in[0];
		bool out_log = false;

		TNote in_note;
		char str[KEY_STR_LEN];
		TSearchRes search_res;
		char file_path[MAX_FILE_PATH_LEN];

		char save[] = "Save";
		char load[] = "Load";

		if (operation == '\n') {
			continue;
		}

		char str_tmp[KEY_STR_LEN];

		switch (operation) {
			case '+':
				cin >> str_tmp;
				in_note.KeyLen = 1;
				for (size_t i = 0; str_tmp[i] != '\0' && i < KEY_STR_LEN - 1; i++) {
					in_note.KeyLen++;
				}

				in_note.Key = new char[in_note.KeyLen];
				in_note.Key[in_note.KeyLen - 1] = '\0';
				for (size_t i = 0; i < in_note.KeyLen; i++) {
					in_note.Key[i] = str_tmp[i];
				}

				cin >> in_note.Num;

				tree->Push(in_note);
				break;
			case '-':
				cin >> str;
				in_note = tree->Pop(str);
				delete [] in_note.Key;
				break;
			case '!':
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
