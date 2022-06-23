#include "IDataBase.h"

#include <iostream>
#include <memory>

// Запись а базу данных малого объема данных. Дядюшка Боб в шоке.
void insertPreparedData(IDataBase* testDB, const std::string& table_name, int test_1DimensionSize, int test_2DimensionSize, int test_3DimensionSize) {

	testDB->use_prepared_statement(table_name);

	std::string query = "BEGIN TRANSACTION";
	testDB->make_query(query);

	for (auto i{ 1 }; i <= test_1DimensionSize; ++i) {
		for (auto j{ 1 }; j <= test_2DimensionSize; ++j) {
			for (auto k{ 1 }; k <= test_3DimensionSize; ++k) {
				double test_value = rand();
				testDB->insert_table_3d(i, j, k, test_value, table_name);
			}
		}
	}

	query.clear();
	query = "END TRANSACTION";
	testDB->make_query(query);
}