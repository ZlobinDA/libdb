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

	const std::string table_name = "TestTable";
	testDB->make_table_3d(table_name);

	const std::string id_name = "id";
	const std::string index1_name = "index1";
	const std::string index2_name = "index2";
	const std::string index3_name = "index3";
	const std::string value_name = "value";

	int id = 1;
	int index1 = 1;
	int index2 = 1;
	int index3 = 1;
	double value = 0.0;

	std::string query = "INSERT INTO " + table_name
		+ " (" + id_name
		+ ", " + index1_name
		+ ", " + index2_name
		+ ", " + index3_name
		+ ", " + value_name + ") "  \
		"VALUES ("
		+ std::to_string(id)
		+ ", " + std::to_string(index1)
		+ ", " + std::to_string(index2)
		+ ", " + std::to_string(index3)
		+ ", " + std::to_string(value)
		+ "); ";

	testDB->make_query(query);
}