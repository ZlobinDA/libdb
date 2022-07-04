/**
	@file
	@brief ����� ��� ������ � ����� ������ sqlite.
*/
#pragma once

#include "IDataBase.h"

#include <sqlite3.h>


#include <memory>
#include <string>
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
	sqlite3_stmt* _stmt{ nullptr };

	/** ��������� ���� � ����� ������. */
	std::any connect() override;
	/** ��������� ���� � ����� ������. */
	void disconnect() override;
	/** ��������� ������������� � ������������ �������� */
	void disable_synchronous();
	/** �������� �������� ������� �������� � ����������� ������. */
	void enable_journalInMemory();

public:
	explicit DataBase(const std::string& path);
	~DataBase();

	/** ����� ���������� ������ ����������. */
	bool get_connection_status() const override;
	/** ����� ���������� �������� ������, ��������� ��� ���������� ��������. */
	std::string get_error_message() const override;

	/** ����� ������� ������� ��� ������ 3-� ������� �������. */
	QueryStatus make_table_3d(const std::string& table_name) override;
	/** ����� ������� ������� ��� ������ 2-� ������� �������. */
	QueryStatus make_table_2d(const std::string& table_name) override;
	/** ����� ������� ������� ��� ������ 1-� ������� �������. */
	QueryStatus make_table_1d(const std::string& table_name) override;

	/** ����� ����������� ���� ������ ��� ������������� ������� ��� ������ ����������� �������. */
	void use_prepared_statement_3d(const std::string& table_name);
	/** ����� ����������� ���� ������ ��� ������������� ������� ��� ������ ����������� �������. */
	void use_prepared_statement_2d(const std::string& table_name);
	/** ����� ����������� ���� ������ ��� ������������� ������� ��� ������ ����������� �������. */
	void use_prepared_statement_1d(const std::string& table_name);

	/** ����� ��������� ������������ ������ � ������� � 3-� ������ ��������. */
	void insert_table_3d(int index1, int index2, int index3, float value, const std::string& name) override;
	/** ����� ��������� ������������ ������ � ������� � 2-� ������ ��������. */
	void insert_table_2d(int index1, int index2, float value, const std::string& name) override;
	/** ����� ��������� ������������ ������ � ������� � 1-� ������ ��������. */
	void insert_table_1d(int index1, float value, const std::string& name) override;

	/** ���������� ������� � ���� ������. */
	QueryStatus make_query(const std::string& query) override;
};
