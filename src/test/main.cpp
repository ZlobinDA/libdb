/**
	�������� ��� ������������ ���������� ��� ������ � ����� ������.
*/

#include "DataBase.h"

#include <iostream>
#include <memory>
#include <string>


int main() {

	// ������� ���� ���� ������.
	const std::string dbPath = "test_db.db";
	auto testDB = std::make_unique<DataBase>(dbPath);


}