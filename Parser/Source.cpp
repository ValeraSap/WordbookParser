#include <time.h> 
#include <iostream>
#include <chrono>
#include "FileHandler.h"
#include <future>

const char* INPUT_FILENAME = "fu8.txt";
const char* OUTPUT_FILENAME = "o.xml";

int main() {

	auto begin = std::chrono::steady_clock::now();
	
	try {

		FileHandler fileHandler(INPUT_FILENAME, OUTPUT_FILENAME);
		fileHandler.run();

		
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << "The time: " << elapsed_ms.count() << " ms\n";
	
	}
	catch (exception e) {
		cout << e.what();
	}
	

	system("pause");
	return 0;
}




