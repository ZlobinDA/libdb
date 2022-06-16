/**
	@file
	@brief Класс для работы с базой данных sqlite.
*/
#pragma once

#include "IDataBase.h"

#include <sqlite3.h>

#include <string>
#include <memory>
#include <variant>

class DataBase : public IDataBase {
private:
	std::string _path;				/**< полный путь до файла базы данных */
	sqlite3* _dataBase{ nullptr };	/**< дескриптор базы данных */

	/** Открываем файл с базой данных. */
	std::any connect() override;

	/** Закрываем файл с базой данных. */
	void disconnect() override;

public:
	DataBase(const std::string& path);
	~DataBase();

	/** Метод возвращает статус соединения. */
	bool get_connection_status() const override;

	/** Метод возвращает описание ошибки, возникшей при выполнении операции. */
	std::string get_error_message() const override;

	/** Выполнение запроса к базе данных. */
	void make_query() override;
};
