#include <filesystem>
#include <iostream>
#include <string>

extern "C" void removeDataBase(char* dataBasePath) {
	// Удаляем старую версию БД. В текущей версии тестируется только заполнение новой базы данных.
	try {
		const std::string dbPath = "test_db.db";
		std::filesystem::remove(dbPath);
	}
	catch (std::exception& e) {
		// Задаем кодировку для консоли ОС Windows.
		// Исключения выводят сообщения на русском языке.
#ifdef _WIN32
		setlocale(LC_ALL, "RU");
#endif
		std::string message = e.what();
		std::cout << "Error at data base file deleting: " + message << std::endl;
		// Задержка экрана.
		std::cout << std::endl << "Press any key for exit" << std::endl;
		std::cin.get();
		exit(0);
	}
}