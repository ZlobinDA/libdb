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
	// @todo Избавиться от хардкода в названии столбцов таблицы
	virtual QueryStatus make_table_3d(const std::string& table_name) = 0;
	/** Метод добавляет вещественные данные в таблицу с 3-х мерным массивом. */
	// @todo Сделать универсальную функцию для любого количества элементов.
	virtual void insert_table_3d(int index1, int index2, int index3, double value, const std::string& name) = 0;

	virtual void use_prepared_statement(const std::string& table_name) = 0;
};
