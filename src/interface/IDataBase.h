/**
	@file
	@brief Интерфейс класса для работы с базой данных.
*/
#pragma once

#include <any>
#include <string>

class IDataBase {
protected:
	bool _status{ false };	/**< статус подключения к базе данных */

	virtual ~IDataBase() = default;

	/** Метод открывает соединение с базой данных. */
	virtual std::any connect() = 0;

	/** Метод закрывает соединение с базой данных. */
	virtual void disconnect() = 0;

	/** Метод возвращает статус соединения. */
	virtual bool get_connection_status() const = 0;

	/** Метод возвращает описание ошибки, возникшей при выполнении операции. */
	virtual std::string get_error_message() const = 0;

	/** Метод выполняет запроса к базе данных. */
	virtual void make_query() = 0;
};
