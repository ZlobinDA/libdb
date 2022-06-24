
#include "DataBase.h"
#include "IDataBase.h"

#include <iostream>
#include <map>
#include <memory>

static std::map<std::string, std::unique_ptr<DataBase>> dataBases;

// �������, ����������� ���� ���� ������.
extern "C" void openDataBase(char* dataBasePath) {
	std::string path = dataBasePath;
	// ��� �������� �� �������� � ����������.
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
extern "C" int makeTableInDataBase(char* dataBaseName, char* tableName) {
	// ���� �� � ��������� ������ � ���������� ��
	auto it = dataBases.find(dataBaseName);
	if (it != dataBases.end()) {
		// ���� �� �������, ������� � �� ������� � ��������� ������.
		if (it->second->make_table_3d(tableName) == QueryStatus::Success) {
			return 0;
		}
	}
	return 1;
}

// �������, ������������ 3-� ������ ������ � ��������� �������.
extern "C" void insertArrayInDataBase(float* array, size_t size1, size_t size2, size_t size3, char * dataBaseName, char* tableName) {
	// ���� �� � ��������� ������ � ���������� ��
	auto it = dataBases.find(dataBaseName);
	if (it != dataBases.end()) {
		it->second->use_prepared_statement(tableName);

		std::string query = "BEGIN TRANSACTION";
		size_t index{ 0 };
		it->second->make_query(query);
		for (size_t i{ 1 }; i <= size1; ++i) {
			for (size_t j{ 1 }; j <= size2; ++j) {
				for (size_t k{ 1 }; k <= size3; ++k) {
					if (index > size1 * size2 * size3) {
						// ����� �� ������� �������.
						break;
					}
					float value = array[index];
					++index;
					it->second->insert_table_3d(i, j, k, value, tableName);
				}
			}
		}

		query.clear();
		query = "END TRANSACTION";
		it->second->make_query(query);
	}
}

// �������, ����������� ���� ���� ������.
extern "C" void closeDataBase(char* dataBasePath) {
	// ���� �� � ��������� ������ � ���������� ��
	auto it = dataBases.find(dataBasePath);
	if (it != dataBases.end()) {
		dataBases.erase(it);
	}
}