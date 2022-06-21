/**
	@file
	@brief ��������� ������ ��� ������ � ����� ������.
*/
#pragma once

#include <any>
#include <string>

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
	virtual void make_query(const std::string& query) = 0;
};
