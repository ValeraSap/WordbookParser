#pragma once
#include <regex>
#include <utility>
#include <string>

using namespace std;


class Parser
{
public: 
	pair<string, string> parseLine(string str);

private:
	 const regex ENDINGS=regex("-([�-�]{1,6})[,.;:][ ]*"); ////regex("[:space:]-([�-�]*)[[:punct:]][[:space:]]*"));
	 const regex GENDER = regex("[[:space:]]{1,}([��]\\.|��\\.)+");
	 const regex BRACKETS = regex("\\(([^)]*)\\)|\\[(.*)\\]");
	 const regex ADJECTIVE = regex("II [�-�]*[., ]([^.^<]*)|11 ����[., ]([^.^<]*)"); //II ���� 
	//regex hang_points("([:space:]{1,}\\.)+");

	 const regex SPELL_MEAN_DIVITION = regex("[ ]*([�-ߨA-Zbl123]*)[ ]*[,\\.](.*)");
	 const regex MEAN_START = regex("([^�-�^1]*)(.*)");

	 void replaceLatin(string& spell);
};

