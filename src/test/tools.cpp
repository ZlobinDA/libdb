#include <filesystem>
#include <iostream>
#include <string>

extern "C" void removeDataBase(char* dataBasePath) {
	// ������� ������ ������ ��. � ������� ������ ����������� ������ ���������� ����� ���� ������.
	try {
		const std::string dbPath = "test_db.db";
		std::filesystem::remove(dbPath);
	}
	catch (std::exception& e) {
		// ������ ��������� ��� ������� �� Windows.
		// ���������� ������� ��������� �� ������� �����.
#ifdef _WIN32
		setlocale(LC_ALL, "RU");
#endif
		std::string message = e.what();
		std::cout << "Error at data base file deleting: " + message << std::endl;
		// �������� ������.
		std::cout << std::endl << "Press any key for exit" << std::endl;
		std::cin.get();
		exit(0);
	}
}