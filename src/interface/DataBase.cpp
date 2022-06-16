#include "DataBase.h"

#include <sqlite3.h>

#include <iostream>

std::any DataBase::connect() {
	// ���� ����� � ����� ������ �� ����������,
	//  sqlite3_open() ������� ����� ���� ���� ������ � ���� ������ � ������� ���.
	return sqlite3_open(_path.c_str(), &_dataBase);
}

void DataBase::disconnect() {
	// ����������� ����� sqlite3_close() ����� � ����� ������,
	//  ���� ��� ������ sqlite3_open().
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
