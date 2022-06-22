#include "IDataBase.h"

#include <iostream>
#include <memory>

// Запись а базу данных малого объема данных. Дядюшка Боб в шоке.
void insertData(IDataBase* testDB, const std::string& table_name, int test_1DimensionSize, int test_2DimensionSize, int test_3DimensionSize) {
	const double test_value = 7.0;
	for (auto i{ 0 }; i < test_1DimensionSize; ++i) {
		for (auto j{ 0 }; j < test_1DimensionSize; ++j) {
			for (auto k{ 0 }; k < test_1DimensionSize; ++k) {
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
}