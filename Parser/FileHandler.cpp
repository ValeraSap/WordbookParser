#include "FileHandler.h"
#include <future>

void FileHandler::run()
{
	if (ifile->is_open() && ofile->is_open()) {

		/**********–јЅќ“јёўјя „ј—“№********
	while (!ifile->eof()) {

		
		getline(*ifile, str);
		auto out = parser.parseLine(str);		
		if (!out.first.empty() && !out.second.empty())
		{
			dbHandler.insertLine(out.first, out.second); //пишем в файл
			cout << "Inserting spell = " << out.first << ", mean = " << out.second << endl;
			cout << "reading: ";
			dbHandler.readLine(out.first);
		}
		
		}*/
		
		auto future1=std::async(std::launch::async, [&] {
			while (!ifile->eof()) {

				while (words.size() > 250) //пока размер списка больше 250 - отдыхаем
					this_thread::sleep_for(chrono::milliseconds(50));

				getline(*ifile, str);
				auto out = parser.parseLine(str);
				if (!out.first.empty() && !out.second.empty()) {
					cout << "words.push_back spell = " << out.first << ", mean = " << out.second << endl;
					//то что выше убрать бы куда-то
					listMutex.lock();
					words.push_back(out); //вставить в конец
					listMutex.unlock();
				}
			}
		});
		auto future2 = std::async(std::launch::async, [&] {
			while (!ifile->eof() || !words.empty()) {
				while (words.empty())
					this_thread::sleep_for(chrono::milliseconds(10)); //может секунда это много

				listMutex.lock();
				auto out = words.front();  //вз€ть первый элемент 
				words.pop_front();	//удалить первый элем
				listMutex.unlock();

				cout << "dbHandler.insertLine spell = " << out.first << ", mean = " << out.second << endl;
				//то что ниже тоже бы куда-то убрать
				dbHandler.insertLine(out.first, out.second); //пишем в файл
			//fromList();
			}
		});

	
	}	else cerr << "error while opening files";
}

FileHandler::FileHandler(string inputFileName, string outputFileName)
{
	ifile = new ifstream(inputFileName);
	ofile = new ofstream(outputFileName);
}

FileHandler::~FileHandler()
{
	ifile->close();
	ofile->close();
}

void FileHandler::toList() //переименовать бы
{
	getline(*ifile, str);
	auto out = parser.parseLine(str);
	//то что выше убрать бы куда-то
	listMutex.lock();
	words.push_back(out); //вставить в конец
	listMutex.unlock();
}

void FileHandler::fromList()
{	
	listMutex.lock();
	auto out = words.front();  //вз€ть первый элемент 
	words.pop_front();	//удалить первый элем
	listMutex.unlock();

	//то что ниже тоже бы куда-то убрать
	dbHandler.insertLine(out.first, out.second); //пишем в файл

}
