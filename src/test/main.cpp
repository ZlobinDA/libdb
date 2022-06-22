/**
	�������� ��� ������������ ���������� ��� ������ � ����� ������.
*/

#include "DataBase.h"
#include "Timer.hpp"

#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

void insertData(IDataBase*, const std::string&, int, int, int);
void insertPreparedData(IDataBase*, const std::string&, int, int, int);

int main() {

	// ������ ��������� ��� ������� �� Windows.
	// ���������� ������� ��������� �� ������� �����.
#ifdef _WIN32
	setlocale(LC_ALL, "RU");
#endif

	const std::string dbPath = "test_db.db";
	// ������� ������ ������ ��, �.�. ������� ��������� ������ ���� ������ � ����� ���� ������.
	try {
		std::filesystem::remove(dbPath);
	}
	catch (std::exception& e) {
		std::string message = e.what();
		std::cout << "Error at data base file deleting: " + message << std::endl;
		return 1;
	}

	// ������� ���� ���� ������.
	IDataBase* testDB = new DataBase(dbPath);
	if (testDB->get_connection_status()) {
		std::cout << "Successful connection with data base " << dbPath << std::endl;
	}
	else {
		std::cout << "Error in connection with data base " << dbPath << std::endl;
		return 1;
	}

	// ���� 1. ������� ������� � ����� ������� ������.
//#define TEST1
#ifdef TEST1
	{
   		std::cout << "Test 1. Small data table test" << std::endl;
		const std::string table_name = "SmallData";
		if (testDB->make_table_3d(table_name) == QueryStatus::Success) {
			std::cout << "Table is made successfully: " << table_name << std::endl;
		}
		else {
			std::cout << "Errror at creating table: " << table_name << std::endl;
			return 1;
		}
		// ��������� ������� � ������� ������� ������.
		int test_1DimensionSize = 2;
		int test_2DimensionSize = 2;
		int test_3DimensionSize = 2;
		Timer timer;

		insertData(testDB, table_name, test_1DimensionSize, test_2DimensionSize, test_3DimensionSize);
	}
#endif

	// ���� 2. ������� ������� � ������� ������� ������.
//#define TEST2
#ifdef TEST2
	{
		std::cout << std::endl;
		std::cout << "Test 2. Big data table test" << std::endl;
		const std::string table_name = "BigData";
		if (testDB->make_table_3d(table_name) == QueryStatus::Success) {
			std::cout << "Table is made successfully: " << table_name << std::endl;
		}
		else {
			std::cout << "Errror at creating table: " << table_name << std::endl;
			return 1;
		}
		// ��������� ������� � ������� ������� ������.
		int test_1DimensionSize = 37;
		int test_2DimensionSize = 163;
		int test_3DimensionSize = 50;
		Timer timer;

		insertData(testDB, table_name, test_1DimensionSize, test_2DimensionSize, test_3DimensionSize);
	}
#endif

	// ���� 3. ������� 6 ������ � ������� ������� ������.
//#define TEST3
#ifdef TEST3
	{
		std::cout << std::endl;
		std::cout << "Test 3. Six big data tables test" << std::endl;
		Timer timer;
		const int tablesNumber = 6;
		for (auto i{ 0 }; i < tablesNumber; ++i) {
			std::string table_name = "BigData" + std::to_string(i);
			if (testDB->make_table_3d(table_name) == QueryStatus::Success) {
				std::cout << "Table is made successfully: " << table_name << std::endl;
			}
			else {
				std::cout << "Errror at creating table: " << table_name << std::endl;
				return 1;
			}
			// ��������� ������� � ������� ������� ������.
			int test_1DimensionSize = 37;
			int test_2DimensionSize = 163;
			int test_3DimensionSize = 50;

			insertData(testDB, table_name, test_1DimensionSize, test_2DimensionSize, test_3DimensionSize);
		}
	}
#endif

	// ���� 4. ������� 6 ������ � ������� ������� ������.
	//  ��� ������� ������ ��������� ���������� ������.
#define TEST4
#ifdef TEST4
	{
		std::cout << std::endl;
		std::cout << "Test 4. Six big data tables test. Using prepared statement" << std::endl;
		Timer timer;
		const int tablesNumber = 6;
		for (auto i{ 0 }; i < tablesNumber; ++i) {
			std::string table_name = "BigData" + std::to_string(i);
			if (testDB->make_table_3d(table_name) == QueryStatus::Success) {
				std::cout << "Table is made successfully: " << table_name << std::endl;
			}
			else {
				std::cout << "Errror at creating table: " << table_name << std::endl;
				return 1;
			}
			// ��������� ������� � ������� ������� ������.
			int test_1DimensionSize = 37;
			int test_2DimensionSize = 163;
			int test_3DimensionSize = 50;

			insertPreparedData(testDB, table_name, test_1DimensionSize, test_2DimensionSize, test_3DimensionSize);
		}
	}
#endif

	std::cout << std::endl;
	std::cout << "Press any key for exit" << std::endl;
	std::cin.get();

	delete testDB;
}