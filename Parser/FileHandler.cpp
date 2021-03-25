#include "FileHandler.h"
#include <future>

void FileHandler::run()
{
	if (ifile->is_open() && ofile->is_open()) {

				
		auto future1=std::async(std::launch::async, [&] {
			while (!ifile->eof()) {

				while (words.size() > 250) //���� ������ ������ ������ 250 - ��������
					this_thread::sleep_for(chrono::milliseconds(50));

				getline(*ifile, str);
				
				auto out = parser.parseLine(str);
				if (!out.first.empty() && !out.second.empty()) {
					//�� ��� ���� ������ �� ����-��
					listMutex.lock();
					words.push_back(out); //�������� � �����
					listMutex.unlock();
				}
			}
		});
		auto future2 = std::async(std::launch::async, [&] {
			while (!ifile->eof() || !words.empty()) {
				while (words.empty())
					this_thread::sleep_for(chrono::milliseconds(10)); //����� ������� ��� �����

				listMutex.lock();
				auto out = words.front();  //����� ������ ������� 
				words.pop_front();	//������� ������ ����
				listMutex.unlock();

				//cout << "dbHandler.insertLine spell = " << out.first << ", mean = " << out.second << endl;
				//�� ��� ���� ���� �� ����-�� ������
				dbHandler.insertLine(out.first, out.second); //����� � ����
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

void FileHandler::toList() //������������� ��
{
	getline(*ifile, str);
	auto out = parser.parseLine(str);
	//�� ��� ���� ������ �� ����-��
	listMutex.lock();
	words.push_back(out); //�������� � �����
	listMutex.unlock();
}

void FileHandler::fromList()
{	
	listMutex.lock();
	auto out = words.front();  //����� ������ ������� 
	words.pop_front();	//������� ������ ����
	listMutex.unlock();

	//�� ��� ���� ���� �� ����-�� ������
	dbHandler.insertLine(out.first, out.second); //����� � ����

}
