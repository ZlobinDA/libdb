/**
	@file
	@brief Интерфейс класса для работы с базой данных.
*/
#pragma once

#include <any>
#include <string>

enum class QueryStatus { Success, Error };

class IDataBase {
protected:
	bool _isOpen{ false };		/**< статус подключения к базе данных */
	std::string _errorMessage;	/**< сообщение с описанием ошибки, возникшей при выполнении операции */

	/** Метод открывает соединение с базой данных. */
	virtual std::any connect() = 0;
	/** Метод закрывает соединение с базой данных. */
	virtual void disconnect() = 0;

public:
	virtual ~IDataBase() = default;

	/** Метод возвращает статус соединения. */
	virtual bool get_connection_status() const = 0;
	/** Метод возвращает описание ошибки, возникшей при выполнении операции. */
	virtual std::string get_error_message() const = 0;
	/** Метод выполняет запроса к базе данных. */
	virtual QueryStatus make_query(const std::string& query) = 0;
	/** Метод создает таблицу для записи 3-х мерного массива. */

	virtual QueryStatus make_table_3d(const std::string& table_name) = 0;
	/** Метод создает таблицу для записи 2-х мерного массива. */
	virtual QueryStatus make_table_2d(const std::string& table_name) = 0;
	/** Метод создает таблицу для записи 1-о мерного массива. */
	virtual QueryStatus make_table_1d(const std::string& table_name) = 0;

	/** Метод добавляет вещественные данные в таблицу с 3-х мерным массивом. */
	virtual void insert_table_3d(int index1, int index2, int index3, float value, const std::string& name) = 0;
	/** Метод добавляет вещественные данные в таблицу с 2-х мерным массивом. */
	virtual void insert_table_2d(int index1, int index2, float value, const std::string& name) = 0;
	/** Метод добавляет вещественные данные в таблицу с 1-о мерным массивом. */
	virtual void insert_table_1d(int index1, float value, const std::string& name) = 0;
};
