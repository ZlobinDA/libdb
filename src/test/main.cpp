/**
	Оболочка для тестирования библиотеки для работы с базой данных sqlite3.
*/

#include <iostream>

extern "C" void model();

int main() {
	// Передаем управление тестированием расчетной модели.
	model();
	// Задержка экрана.
	std::cout << std::endl << "Press any key for exit" << std::endl;
	std::cin.get();
}