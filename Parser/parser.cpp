#include "parser.h"
#include <iostream>

pair<string, string> Parser::parseLine(string str) {

	const regex SPELL_MEAN_DIVITION = regex("[ ]*([А-ЯЁA-Zbl123]*)[ ]*[,\\.](.*)");
	const regex MEAN_START = regex("([^А-Я^1]*)(.*)");

	smatch m;
	bool isWord = regex_search(str, m, regex("<p>(.{2,})</p>")); 
	if (isWord) {

		smatch m2;
		try {
			string s = m.str(1);
			bool found = regex_search(s, m2, SPELL_MEAN_DIVITION);

			if (found) {

				string spell = m2.str(1);
				string mean = m2.str(2);

				
				smatch m3;
				bool found2 = regex_search(mean, m3, MEAN_START);
				if (found2) {
					mean = m3.str(2);
				}

				if (spell.size() > 0 && mean.size() > 0) {
					
					return make_pair(replaceLatin(spell), mean);
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

 
}

string Parser::replaceExcess(string input)
{
	string delGend = regex_replace(input, GENDER, "");
	string delEnd = regex_replace(delGend, ENDINGS, "");
	string delBacket = regex_replace(delEnd, BRACKETS, "");
	string delAdj = regex_replace(delBacket, ADJECTIVE, "");

	return delAdj;
}

string Parser::replaceLatin(string spell) {
	string out;
	for (int i = 0; i < spell.size(); i++) {
		switch (spell[i]) {
		case 'b':
			if (spell[i - 1] == 'I' || spell[i - 1] == 'l') {
				out += "Ы";
			}
			else
				out += "Ь";				
			break;
		case 'K':
			out += "К";			
			break;
		case 'O':
			out += "О";
			break;
		case 'A':
			out += "А";
		case 'C':
			out += "С";
			break;
		case '3':
			out += "З";
			break;
		case 'P':
			out += "Р";
			break;
		case 'H':
			out += "Н";
			break;
		case 'M':
			out += "М";
			break;
		default:
			out += spell[i];
			break;
		}
	}
	return out;

}
