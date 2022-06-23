
#include "DataBase.h"
#include "IDataBase.h"

#include <iostream>
#include <map>
#include <memory>

static std::map<std::string, std::unique_ptr<DataBase>> dataBases;

// �������, ����������� ���� ���� ������.
extern "C" void openDataBase(char* dataBasePath) {
	std::string path = dataBasePath;
	dataBases[path] = std::make_unique<DataBase>(path);
}

// 
extern "C" int getDataBaseConnectionStatus(char* dataBasePath) {
	std::string path = dataBasePath;
	if (dataBases[path]->get_connection_status()) {
		std::cout << "Successful connection with data base " << path << std::endl;
	}
	else {
		std::cout << "Error in connection with data base " << path << std::endl;;
	}
	return 0;
}

// �������, ��������� ������� � �������� ������ � ��������� ���� ������.
extern "C" void makeTableInDataBase(char* dataBaseName, char* tableName) {

}

// �������, ������������ 3-� ������ ������ � ��������� �������.
extern "C" void insertArrayInDataBase(size_t index1, size_t index2, size_t index3, float value, char* tableName) {


	//testDB->use_prepared_statement(table_name);

	//std::string query = "BEGIN TRANSACTION";
	//testDB->make_query(query);

	//testDB->insert_table_3d(index1, index2, index3, test_value, table_name);

	//query.clear();
	//query = "END TRANSACTION";
	//testDB->make_query(query);
}

// �������, ����������� ���� ���� ������.
extern "C" void closeDataBase(char* dataBasePath) {


}