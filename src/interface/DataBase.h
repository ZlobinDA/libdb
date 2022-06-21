/**
	@file
	@brief ����� ��� ������ � ����� ������ sqlite.
*/
#pragma once

#include "IDataBase.h"

#include <sqlite3.h>

#include <string>
#include <memory>
#include <variant>

class DataBase : public IDataBase {
private:
	std::string _path;				/**< ������ ���� �� ����� ���� ������ */
	sqlite3* _dataBase{ nullptr };	/**< ���������� ���� ������ */

	/** ��������� ���� � ����� ������. */
	std::any connect() override;

	/** ��������� ���� � ����� ������. */
	void disconnect() override;

public:
	DataBase(const std::string& path);
	~DataBase();

	/** ����� ���������� ������ ����������. */
	bool get_connection_status() const override;

	/** ����� ���������� �������� ������, ��������� ��� ���������� ��������. */
	std::string get_error_message() const override;

	/** ����� ������� ������� ��� ������ 3-� ������� �������. */
	virtual std::any make_table_3d(const std::string& table_name);

	/** ���������� ������� � ���� ������. */
	void make_query(const std::string& query) override;
};
