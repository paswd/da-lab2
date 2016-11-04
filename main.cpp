#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <memory>
#include "btree.h"

using namespace std;

int main() {
	const size_t factor_t = 20;
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

		//size_t cnt;
		//size_t i;
		char str_tmp[KEY_STR_LEN];

		switch (operation) {
			case '+':
				//TNote in_note;
				//char sym;
				//i = 0;
				//cin >> str_tmp;
				//in_note.KeyLen = (size_t) scanf("%s", str_tmp);
				cin >> str_tmp;
				in_note.KeyLen = 1;
				for (size_t i = 0; str_tmp[i] != '\0' && i < KEY_STR_LEN - 1; i++) {
					in_note.KeyLen++;
				}
				//in_note.Key(new char[cnt]);
				in_note.Key = new char[in_note.KeyLen];
				in_note.Key[in_note.KeyLen - 1] = '\0';
				for (size_t i = 0; i < in_note.KeyLen; i++) {
					in_note.Key[i] = str_tmp[i];
				}
				//in_note.KeyLen = cnt;
				cin >> in_note.Num;
				//cout << "InCase::" << in_note.Key << ":" << in_note.KeyLen << endl;
				tree->Push(in_note);
				break;
			case '-':
				//char *key;
				cin >> str;
				/*for (size_t i = 0; key[i] != '\0' && i < 255; i++) {
					cout << i << endl;
				}*/
				in_note = tree->Pop(str);
				delete [] in_note.Key;
				break;
			case '!':
				/*char *param;
				char *path;
				cin >> param;*/
				cin >> str;
				cin >> file_path;
				//cout << "In::Point1" << endl;
				if (StringComparison(str, save) == 0) {
					//cout << "In::Point2" << endl;
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
