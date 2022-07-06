#include "DataBase.h"

#include <sqlite3.h>
#include <iostream>

std::any DataBase::connect() {
	// Если файла с таким именем не существует,
	//  sqlite3_open() создаст новый файл базы данных с этим именем и откроет его.
	return sqlite3_open(_path.c_str(), &_dataBase);
}

void DataBase::disconnect() {
	//
	sqlite3_finalize(_stmt);
	// Закрывающий вызов sqlite3_close() нужен в любом случае, даже при ошибке sqlite3_open().
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

void DataBase::use_prepared_statement_1d(const std::string& table_name) {
	std::string query = "INSERT INTO " + table_name
		+ "(" + index1_name.data()
		+ ", " + value_name.data() + ") "  \
		"VALUES (@" + index1_name.data()
		+ ", @" + value_name.data()
		+ "); ";
	const int nBytes = 256;
	const char* tail = 0;
	sqlite3_prepare_v2(_dataBase, query.c_str(), nBytes, &_stmt, &tail);
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

QueryStatus DataBase::make_table_1d(const std::string& table_name) {
	std::string query = "CREATE TABLE IF NOT EXISTS " + table_name + " ( \
		" + index1_name.data() + " INT, \
		" + value_name.data() + " FLOAT \
		);";

	return make_query(query);
}

void DataBase::insert_table_1d(int index1, float value, const std::string& name) {
	sqlite3_bind_text(_stmt, 1, std::to_string(index1).c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(_stmt, 2, std::to_string(value).c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_step(_stmt);
	sqlite3_clear_bindings(_stmt);
	sqlite3_reset(_stmt);
}

QueryStatus DataBase::make_query(const std::string& query) {
	char* error = 0;
	if (sqlite3_exec(_dataBase, query.c_str(), nullptr, nullptr, &error)) {
		_errorMessage.clear();
		_errorMessage = error;
		sqlite3_free(error);
		return QueryStatus::Error;
	}
	return QueryStatus::Success;
}
