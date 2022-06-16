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
		_status = true;
	}
}

DataBase::~DataBase() {
	disconnect();
}

bool DataBase::get_connection_status() const {
	return _status;
}

std::string DataBase::get_error_message() const {
	return sqlite3_errmsg(_dataBase);
}

void DataBase::make_query() {

}
