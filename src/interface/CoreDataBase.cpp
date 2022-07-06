
#include "DataBase.h"
#include "IDataBase.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <exception>
#include <iostream>

namespace {
	std::map<std::string, std::vector<float>> calculationData;
	std::map<std::string, std::unique_ptr<DataBase>> calculationDataBase;
}

// �������, ����������� ���� ���� ������.
void dataBase_open(const std::string& dataBasePath) {
	std::string path = dataBasePath;
	// ��� �������� �� �������� � ����������.
	calculationDataBase[path] = std::make_unique<DataBase>(path);
}

// 
bool getDataBaseConnectionStatus(const std::string& dataBasePath) {
	std::string path = dataBasePath;
	return calculationDataBase[path]->get_connection_status() ? true : false;
}

// �������, ��������� ������� � �������� ������ � ��������� ���� ������.
int dataBase_makeSingleDimensionTable(const std::string& dataBaseName, const std::string& tableName) {
	// ���� �� � ��������� ������ � ���������� ��
	auto it = calculationDataBase.find(dataBaseName);
	if (it != calculationDataBase.end()) {
		// ���� �� �������, ������� � �� ������� � ��������� ������.
		if (it->second->make_table_1d(tableName) == QueryStatus::Success) {
			return 0;
		}
	}
	return 1;
}


// �������, ������������ 1-� ������ ������ � ��������� �������.
void dataBase_insertSingleDimensionArray(const std::vector<float>& array, size_t size1, std::string& dataBaseName, std::string& tableName) {
	// ���� �� � ��������� ������ � ���������� ��
	auto it = calculationDataBase.find(dataBaseName);
	if (it != calculationDataBase.end()) {
		it->second->use_prepared_statement_1d(tableName);

		std::string query = "BEGIN TRANSACTION";
		size_t index{ 0 };
		it->second->make_query(query);
		for (size_t i{ 1 }; i <= size1; ++i) {
			if (index > size1) {
				// ����� �� ������� �������.
				break;
			}
			float value = array[index];
			++index;
			it->second->insert_table_1d(i, value, tableName);
		}

		query.clear();
		query = "END TRANSACTION";
		it->second->make_query(query);
	}
}

// �������, ����������� ���� ���� ������.
void dataBase_close(const std::string& dataBasePath) {
	// ���� �� � ��������� ������ � ���������� ��
	auto it = calculationDataBase.find(dataBasePath);
	if (it != calculationDataBase.end()) {
		calculationDataBase.erase(it);
	}
}

extern "C" void shell_sendSingleDimensionArray(float* array, size_t size, const char* name) {
	for (size_t i{ 0 }; i < size; ++i) {
		try {
			calculationData[name].push_back(array[i]);
		}
		catch (const std::exception& e) {
			std::cout << "Error: " << e.what() << std::endl;
			return;
		}
	}
}

extern "C" void dataBase_insertData(const char* dataBaseName) {
	std::string s_dataBaseName = dataBaseName;
	dataBase_open(s_dataBaseName);
	if (!getDataBaseConnectionStatus(s_dataBaseName)) {
		return;
	}

	for (auto it = calculationData.begin(); it != calculationData.end(); ++it) {
		std::string tableName = it->first;
		dataBase_makeSingleDimensionTable(dataBaseName, tableName);
		std::vector<float> dataArray = it->second;
		size_t size = it->second.size();
		dataBase_insertSingleDimensionArray(dataArray, size, s_dataBaseName, tableName);
	}
	dataBase_close(s_dataBaseName);
}