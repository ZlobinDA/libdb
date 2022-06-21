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
	bool _isOpen{ false };	/**< ������ ����������� � ���� ������ */
	std::string _message;	/**< ���������� ��������� */

	virtual ~IDataBase() = default;

	/** ����� ��������� ���������� � ����� ������. */
	virtual std::any connect() = 0;

	/** ����� ��������� ���������� � ����� ������. */
	virtual void disconnect() = 0;

	/** ����� ���������� ������ ����������. */
	virtual bool get_connection_status() const = 0;

	/** ����� ���������� �������� ������, ��������� ��� ���������� ��������. */
	virtual std::string get_error_message() const = 0;

	/** ����� ��������� ������� � ���� ������. */
	virtual QueryStatus make_query(const std::string& query) = 0;
};
