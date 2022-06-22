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

/** �������� ������� ������� */
inline constexpr std::string_view id_name = "id";
inline constexpr std::string_view index1_name = "index1";
inline constexpr std::string_view index2_name = "index2";
inline constexpr std::string_view index3_name = "index3";
inline constexpr std::string_view value_name = "value";

class DataBase : public IDataBase {
private:
	std::string _path;				/**< ������ ���� �� ����� ���� ������ */
	sqlite3* _dataBase{ nullptr };	/**< ���������� ���� ������ */

	/** ��������� ���� � ����� ������. */
	std::any connect() override;

	/** ��������� ���� � ����� ������. */
	void disconnect() override;

	/** ��������� ������������� � ������������ �������� */
	void disable_synchronous();

public:
	explicit DataBase(const std::string& path);
	~DataBase();

	/** ����� ���������� ������ ����������. */
	bool get_connection_status() const override;

	/** ����� ���������� �������� ������, ��������� ��� ���������� ��������. */
	std::string get_error_message() const override;

	/** ����� ������� ������� ��� ������ 3-� ������� �������. */
	QueryStatus make_table_3d(const std::string& table_name) override;

	/** ����� ��������� ������������ ������ � ������� � 3-� ������ ��������. */
	QueryStatus insert_table_3d(int index1, int index2, int index3, double value, const std::string& name) override;

	/** ���������� ������� � ���� ������. */
	QueryStatus make_query(const std::string& query) override;
};
