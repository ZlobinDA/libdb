#include "IDataBase.h"

#include <iostream>
#include <memory>

// ������ � ���� ������ ������ ������ ������. ������� ��� � ����.
void insertData(IDataBase* testDB, const std::string& table_name, int test_1DimensionSize, int test_2DimensionSize, int test_3DimensionSize) {

	std::string query = "BEGIN TRANSACTION";
	testDB->make_query(query);

	for (auto i{ 1 }; i <= test_1DimensionSize; ++i) {
		for (auto j{ 1 }; j <= test_2DimensionSize; ++j) {
			for (auto k{ 1 }; k <= test_3DimensionSize; ++k) {
				double test_value = rand();
				if (testDB->insert_table_3d(i, j, k, test_value, table_name) == QueryStatus::Error) {
					std::string message = "Error at adding data: ("
						+ std::to_string(i) + ", "
						+ std::to_string(j) + ", "
						+ std::to_string(k) + ", "
						+ std::to_string(test_value) + ")";
					std::cout << message << std::endl;
				}
			}
		}
	}

	query.clear();
	query = "END TRANSACTION";
	testDB->make_query(query);
}