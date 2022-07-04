/**
	@file
	@brief Класс для работы с базой данных sqlite.
*/
#pragma once

#include "IDataBase.h"

#include <sqlite3.h>


#include <memory>
#include <string>
#include <variant>

/** Названия колонок таблицы */
inline constexpr std::string_view id_name = "id";
inline constexpr std::string_view index1_name = "index1";
inline constexpr std::string_view index2_name = "index2";
inline constexpr std::string_view index3_name = "index3";
inline constexpr std::string_view value_name = "value";

class DataBase : public IDataBase {
private:
	std::string _path;				/**< полный путь до файла базы данных */
	sqlite3* _dataBase{ nullptr };	/**< дескриптор базы данных */
	sqlite3_stmt* _stmt{ nullptr };

	/** Открываем файл с базой данных. */
	std::any connect() override;
	/** Закрываем файл с базой данных. */
	void disconnect() override;
	/** Отключаем синхронизацию с операционной системой */
	void disable_synchronous();
	/** Включаем хранение журнала операций в оперативной памяти. */
	void enable_journalInMemory();

public:
	explicit DataBase(const std::string& path);
	~DataBase();

	/** Метод возвращает статус соединения. */
	bool get_connection_status() const override;
	/** Метод возвращает описание ошибки, возникшей при выполнении операции. */
	std::string get_error_message() const override;

	/** Метод создает таблицу для записи 3-х мерного массива. */
	QueryStatus make_table_3d(const std::string& table_name) override;
	/** Метод создает таблицу для записи 2-х мерного массива. */
	QueryStatus make_table_2d(const std::string& table_name) override;
	/** Метод создает таблицу для записи 1-о мерного массива. */
	QueryStatus make_table_1d(const std::string& table_name) override;

	/** Метод настраивает базу данных для использования шаблона для записи трехмерного массива. */
	void use_prepared_statement_3d(const std::string& table_name);
	/** Метод настраивает базу данных для использования шаблона для записи двухмерного массива. */
	void use_prepared_statement_2d(const std::string& table_name);
	/** Метод настраивает базу данных для использования шаблона для записи одномерного массива. */
	void use_prepared_statement_1d(const std::string& table_name);

	/** Метод добавляет вещественные данные в таблицу с 3-х мерным массивом. */
	void insert_table_3d(int index1, int index2, int index3, float value, const std::string& name) override;
	/** Метод добавляет вещественные данные в таблицу с 2-х мерным массивом. */
	void insert_table_2d(int index1, int index2, float value, const std::string& name) override;
	/** Метод добавляет вещественные данные в таблицу с 1-м мерным массивом. */
	void insert_table_1d(int index1, float value, const std::string& name) override;

	/** Выполнение запроса к базе данных. */
	QueryStatus make_query(const std::string& query) override;
};
