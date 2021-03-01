#include <iostream>
#include <regex>
#include <fstream>
#include <string>

using namespace std;

const char* INPUT_FILENAME = "input_file.xml";
//const char* OUTPUT_FILENAME = "output_file.xml";
//const char* INPUT_FILENAME = "file.txt";
const char* OUTPUT_FILENAME = "o.txt";

int main() {

	setlocale(LC_ALL,"rus");
	//system("chcp 1251");
	//std::locale::global(std::locale(""));
	//setlocale(LC_ALL, "");
	//#include <Windows.h>
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);


	ifstream file(INPUT_FILENAME);
	ofstream ofile(OUTPUT_FILENAME);

	if (file.is_open() && ofile.is_open()) {

		string str;
		regex r("<p>$1, (.*)</p>");

		while (!file.eof()) {

			getline(file, str);   //считали строку

			smatch m;
			bool isWord = regex_search(str, m, regex("<p>(.{2,})</p>"));
			if (isWord) {

				regex reg1("-([а-я]{1,6})[,.;:][ ]*"); ////regex("[:space:]-([а-я]*)[[:punct:]][[:space:]]*"));  //убрали -ая -ие
				regex reg2("[[:space:]]{1,}([мж]\\.|ср\\.)+"); //убрали //м. ж. ср.
				regex reg3("\\(([^)]*)\\)|\\[(.*)\\]");  //убрали () []
				regex reg4("II [а-я]*[., ]([^.^<]*)|11 прил[., ]([^.^<]*)"); //убрать II прил 
				//regex reg5("([:space:]{1,}\\.)+");


				smatch m2;
				try {
					string str2 = regex_replace(str, reg1, ""); //вместо str передать m.str(1) //или (2)
					string str3 = regex_replace(str2, reg2, "");
					string str4 = regex_replace(str3, reg3, "");
					string str5 = regex_replace(str4, reg4, "");
					//string str6 = regex_replace(str5, reg5, ".");
					bool found = regex_search(str5, m2,
						//regex("<(.*)>(.*)</(\\1)>"));					
						regex("<(.*)>[ ]*([А-ЯA-Z]*),(.*)</(\\1)>")); //m.str(2) = АББАТ		 OK! 


					if (found) {

						smatch m3;
						string spell = m2.str(2);
						string mean = m2.str(3);
						//cout << mean << endl;
						bool found2 = regex_search(mean, m3,
							regex("([^А-Я^1]*)(.*)"));
						if (found2) {
							mean = m3.str(2);
						}

						string outStr = "<spell>" + spell + "</spell><mean>" + mean + "</mean>\n";
						
						ofile.write(outStr.c_str(), outStr.size());

					}
				}
				catch (exception e) {
					cout << e.what() << endl;
				}
			}
			else {
				str += "\n";
				ofile.write(str.c_str(), str.size());  //просто записали неподходящую строку
			}

		}

	}
	else cerr << "error while opening files";


	system("pause");
	return 0;
}
