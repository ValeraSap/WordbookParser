#include "parser.h"
#include <iostream>

pair<string, string> Parser::parseLine(string str) {


	smatch m;
	bool isWord = regex_search(str, m, regex("<p>(.{2,})</p>")); //обрабатываем только то, что в теге <p> и больше 2-х букв
	if (isWord) {

		smatch m2;
		try {
			string start = m.str(1);
			//string delGend = regex_replace(start, GENDER, "");
			string delEnd = regex_replace(start, ENDINGS, "");
			string delBacket = regex_replace(delEnd, BRACKETS, "");
			string delAdj = regex_replace(delBacket, ADJECTIVE, "");

			bool found = regex_search(delAdj, m2, SPELL_MEAN_DIVITION);

			if (found) {

				string spell = m2.str(1);
				string mean = m2.str(2);

				//делаем красивым значение слова
				smatch m3;
				bool found2 = regex_search(mean, m3, MEAN_START);
				if (found2) {
					mean = m3.str(2);
				}

				if (spell.size() > 0 && mean.size() > 0) {
					//починим английские буквы в слове
					replaceLatin(spell);					
					return make_pair(spell, mean);					
				}

			}
		}
		catch (exception e) {
			cout << e.what() << endl;
		}
	}
	else {
		str += "\n";
		return make_pair("", "");
		
	}

	//ofile.write(str.c_str(), str.size());  //просто записали неподходящую строку


}

void Parser::replaceLatin(string& spell) {
	for (int i = 0; i < spell.size(); i++) {
		switch (spell[i]) {
		case 'b':
			if (spell[i - 1] == 'I' || spell[i - 1] == 'l') {
				spell[i - 1] = 'Ы';
				spell.erase(i, 1);
				--i; //уменьшаем индекс, потому что размер строки изменился
			}
			else spell[i] = 'Ь';
			break;
		case 'K':
			spell[i] = 'К';
			break;
		case 'O':
			spell[i] = 'О';
			break;
		case 'A':
			spell[i] = 'А';
			break;
		case 'C':
			spell[i] = 'С';
			break;
		case '3':
			spell[i] = 'З';
			break;
		case 'P':
			spell[i] = 'Р';
			break;
		case 'H':
			spell[i] = 'Н';
			break;
		case 'M':
			spell[i] = 'М';
			break;
		default:
			break;
		}
	}

}
