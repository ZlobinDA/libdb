#include "DataBase.h"

#include <sqlite3.h>

#include <iostream>

std::any DataBase::connect() {
	// Если файла с таким именем не существует,
	//  sqlite3_open() создаст новый файл базы данных с этим именем и откроет его.
	return sqlite3_open(_path.c_str(), &_dataBase);
}

void DataBase::disconnect() {
	// Закрывающий вызов sqlite3_close() нужен в любом случае,
	//  даже при ошибке sqlite3_open().
	sqlite3_close(_dataBase);
}

DataBase::DataBase(const std::string& path) : _path{ path } {
	if (std::any_cast<int>(connect())) {
#ifdef _DEBUG
		std::cout << "Error! Make connection with data base: " << get_error_message() << std::endl;
#endif // _DEBUG
		disconnect();
	}
	else {
		_isOpen = true;
	}
}

DataBase::~DataBase() {
	disconnect();
}

bool DataBase::get_connection_status() const {
	return _isOpen;
}

std::string DataBase::get_error_message() const {
	return sqlite3_errmsg(_dataBase);
}

std::any DataBase::make_table_3d(const std::string& table_name) {
	const std::string id_name = "id";
	const std::string index1_name = "index1";
	const std::string index2_name = "index2";
	const std::string index3_name = "index3";
	const std::string value_name = "value";
	std::string query = "CREATE TABLE IF NOT EXISTS " + table_name + " ( \
		" + id_name + " INT PRIMARY KEY NOT NULL, \
		" + index1_name + " INT NOT NULL, \
		" + index2_name + " INT NOT NULL, \
		" + index3_name + " INT NOT NULL, \
		" + value_name + " REAL NOT NULL \
		);";

	make_query(query);

	return std::any();
}

void DataBase::make_query(const std::string& query) {
	char* error = 0;
	if (sqlite3_exec(_dataBase, query.c_str(), nullptr, nullptr, &error)) {
		_message.clear();
		_message = error;
		sqlite3_free(error);
	}
}
