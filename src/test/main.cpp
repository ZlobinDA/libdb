/**
	Оболочка для тестирования библиотеки для работы с базой данных.
*/

#include "DataBase.h"

#include <iostream>
#include <memory>
#include <string>


int main() {

	// Создаем файл базы данных.
	const std::string dbPath = "test_db.db";
	auto testDB = std::make_unique<DataBase>(dbPath);
	if (testDB->get_connection_status()) {
		std::cout << "Successful connection with data base " << dbPath << std::endl;
	}
	else {
		std::cout << "Error in connection with data base " << dbPath << std::endl;
		return 1;
	}

	// Создаем таблицу.
	const std::string table_name = "TestTable";
	if (testDB->make_table_3d(table_name) == QueryStatus::Success) {
		std::cout << "Table is made successfully: " << table_name << std::endl;
	}
	else {
		std::cout << "Errror at creating table: " << table_name << std::endl;
		return 1;
	}

	// Заполняем таблицу.
	const int test_1DimensionValue = 2;
	const int test_2DimensionValue = 2;
	const int test_3DimensionValue = 2;
	const double test_value = 7.0;
	for (auto i{ 0 }; i < test_1DimensionValue; ++i) {
		for (auto j{ 0 }; j < test_1DimensionValue; ++j) {
			for (auto k{ 0 }; k < test_1DimensionValue; ++k) {
				if (testDB->insert_table_3d(i, j, k, test_value, table_name) == QueryStatus::Success) {
					std::string message = "Data is added successfully : (" + std::to_string(i) + ", " + std::to_string(j) + ", " + std::to_string(k) + ", "
						+ std::to_string(test_value) + ")";
					std::cout << message << std::endl;
				}
				else {
					std::string message = "Error at adding data: (" + std::to_string(i) + ", " + std::to_string(j) + ", " + std::to_string(k) + ", "
						+ std::to_string(test_value) + ")";
					std::cout << message << std::endl;
				}
			}
		}
	}
}