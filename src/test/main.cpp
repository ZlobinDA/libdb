/**
	�������� ��� ������������ ���������� ��� ������ � ����� ������ sqlite3.
*/

#include <iostream>

extern "C" void model();

int main() {
	// �������� ���������� ������������� ��������� ������.
	model();
	// �������� ������.
	std::cout << std::endl << "Press any key for exit" << std::endl;
	std::cin.get();
}