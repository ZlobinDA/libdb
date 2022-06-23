/**
	@file
	@brief ��������� ������ ��� ������ � ����� ������.
*/
#pragma once

#include <any>
#include <string>

enum class QueryStatus { Success, Error };

class IDataBase {
protected:
	bool _isOpen{ false };		/**< ������ ����������� � ���� ������ */
	std::string _errorMessage;	/**< ��������� � ��������� ������, ��������� ��� ���������� �������� */

	/** ����� ��������� ���������� � ����� ������. */
	virtual std::any connect() = 0;
	/** ����� ��������� ���������� � ����� ������. */
	virtual void disconnect() = 0;

public:
	virtual ~IDataBase() = default;

	/** ����� ���������� ������ ����������. */
	virtual bool get_connection_status() const = 0;
	/** ����� ���������� �������� ������, ��������� ��� ���������� ��������. */
	virtual std::string get_error_message() const = 0;
	/** ����� ��������� ������� � ���� ������. */
	virtual QueryStatus make_query(const std::string& query) = 0;
	/** ����� ������� ������� ��� ������ 3-� ������� �������. */
	// @todo ���������� �� �������� � �������� �������� �������
	virtual QueryStatus make_table_3d(const std::string& table_name) = 0;
	/** ����� ��������� ������������ ������ � ������� � 3-� ������ ��������. */
	// @todo ������� ������������� ������� ��� ������ ���������� ���������.
	virtual void insert_table_3d(int index1, int index2, int index3, double value, const std::string& name) = 0;

	virtual void use_prepared_statement(const std::string& table_name) = 0;
};
