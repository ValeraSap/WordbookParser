#pragma once
#include <regex>
#include <utility>
#include <string>

using namespace std;


class Parser
{
public: 
	pair<string, string> parseLine(string str);

	string replaceExcess(string input);

private:
	 const regex ENDINGS=regex("-([а-я]{1,6})[,.;:][ ]*"); ////regex("[:space:]-([а-я]*)[[:punct:]][[:space:]]*"));
	 const regex GENDER = regex("[[:space:]]{1,}([мж]\\.|ср\\.)+");
	 const regex BRACKETS = regex("\\(([^)]*)\\)|\\[(.*)\\]");
	 const regex ADJECTIVE = regex("II [а-я]*[., ]([^.^<]*)|11 прил[., ]([^.^<]*)"); //II прил 
	
	 const regex SPELL_MEAN_DIVITION = regex("[ ]*([А-ЯЁA-Zbl123]*)[ ]*[,\\.](.*)");
	 const regex MEAN_START = regex("([^А-Я^1]*)(.*)");
	 
	 string replaceLatin(string spell);
};

