/**
	Оболочка для тестирования библиотеки для работы с базой данных.
*/

#include "DataBase.h"
#include "Timer.hpp"

#include <filesystem>
#include <iostream>
#include <memory>
#include <string>


void insertData(IDataBase* testDB, const std::string& table_name, int test_1DimensionSize, int test_2DimensionSize, int test_3DimensionSize);

int main() {

	const std::string dbPath = "test_db.db";
	// Удаляем старую версию БД, т.к. функция выполняет только тест записи в новую базу данных.
	std::filesystem::remove(dbPath);

	// Создаем файл базы данных.
	IDataBase* testDB = new DataBase(dbPath);
	if (testDB->get_connection_status()) {
		std::cout << "Successful connection with data base " << dbPath << std::endl;
	}
	else {
		std::cout << "Error in connection with data base " << dbPath << std::endl;
		return 1;
	}

	// Создаем таблицу с малым объемом данных.
	{
		const std::string table_name = "SmallData";
		if (testDB->make_table_3d(table_name) == QueryStatus::Success) {
			std::cout << "Table is made successfully: " << table_name << std::endl;
		}
		else {
			std::cout << "Errror at creating table: " << table_name << std::endl;
			return 1;
		}
		// Заполняем таблицу с большим объемом данных.
		int test_1DimensionSize = 2;
		int test_2DimensionSize = 2;
		int test_3DimensionSize = 2;
		Timer timer;

		insertData(testDB, table_name, test_1DimensionSize, test_2DimensionSize, test_3DimensionSize);
	}


	// Создаем таблицу с большим объемом данных.
	{
		const std::string table_name = "BigData";
		if (testDB->make_table_3d(table_name) == QueryStatus::Success) {
			std::cout << "Table is made successfully: " << table_name << std::endl;
		}
		else {
			std::cout << "Errror at creating table: " << table_name << std::endl;
			return 1;
		}
		// Заполняем таблицу с большим объемом данных.
		int test_1DimensionSize = 37;
		int test_2DimensionSize = 163;
		int test_3DimensionSize = 50;
		Timer timer;

		insertData(testDB, table_name, test_1DimensionSize, test_2DimensionSize, test_3DimensionSize);
	}

	delete testDB;
}