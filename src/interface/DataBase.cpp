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

void DataBase::disable_synchronous() {
	const std::string query = "PRAGMA synchronous = OFF";
	make_query(query);
}

void DataBase::enable_journalInMemory() {
	const std::string query = "PRAGMA journal_mode = MEMORY";
	make_query(query);
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
		disable_synchronous();
		enable_journalInMemory();
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

QueryStatus DataBase::make_table_3d(const std::string& table_name) {
	// Внимание! Номер строки (id) будет добавлен автоматически.
	std::string query = "CREATE TABLE IF NOT EXISTS " + table_name + " ( \
		" + index1_name.data() + " INT, \
		" + index2_name.data() + " INT, \
		" + index3_name.data() + " INT, \
		" + value_name.data() + " REAL \
		);";

	return make_query(query);
}

QueryStatus DataBase::insert_table_3d(int index1, int index2, int index3, double value, const std::string& name) {
	// Внимание! Увеличение номера строки (id) происходит автоматически.
	std::string query = "INSERT INTO " + name
		+ "("  + index1_name.data()
		+ ", " + index2_name.data()
		+ ", " + index3_name.data()
		+ ", " + value_name.data() + ") "  \
		"VALUES ("
		+ std::to_string(index1)
		+ ", " + std::to_string(index2)
		+ ", " + std::to_string(index3)
		+ ", " + std::to_string(value)
		+ "); ";

	return make_query(query);
}

QueryStatus DataBase::make_query(const std::string& query) {
	char* error = 0;
	if (sqlite3_exec(_dataBase, query.c_str(), nullptr, nullptr, &error)) {
		_message.clear();
		_message = error;
		sqlite3_free(error);
		return QueryStatus::Error;
	}
	return QueryStatus::Success;
}
