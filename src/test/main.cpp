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


}