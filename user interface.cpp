#include "functions.h"

// Проверка границ выбора
/*bool user_interface::is_coorect_input(const char value, const char min_val_arg, const char max_val_arg)
{
	return (value >= min_val_arg && value <= max_val_arg);
}

// Выбор источника ввода, файл или консоль
char user_interface::func_choose_source()
{
	std::cout << "Please choose source:\n1 - from console\n2 - from file" << std::endl;
	char choose = _getch();
	if (!is_coorect_input(choose, '1', '2'))
	{
		std::cout << "Incorrecr input. Please choose source:\n1 - from console\n2 - from file" << std::endl;
		choose = _getch();
	}
	return choose;
}

// Выбор мода, шифрование или дешифрование
char user_interface::func_choose_mode()
{
	std::cout << "Please choose mode:\n1 - encryption\n2 - decryption" << std::endl;
	char choose = _getch();
	while (!is_coorect_input(choose, '1', '2'))
	{
		std::cout << "Incorrecr input. Please choose source:\n1 - from console\n2 - from file" << std::endl;
		choose = _getch();
	}
	return choose;
}

// Чтение текста из консоли
void user_interface::input_from_console(str& text_from_console)
{
	std::cout << "Input text: ";
	std::cin >> text_from_console;
	std::cout << std::endl << std::endl;
}

// Запрос на продолжение
void user_interface::do_you_want_continue(int &get_choose)
{
	std::cout << "Do you want continue?\nYES \t- \t1\nNO \t- \t2" << std::endl << std::endl;
	char choose = _getch();
	while (!is_coorect_input(choose, '1', '2'))
	{
		std::cout << "Incorrecr input. Try again. Do you want continue?\nYES \t- \t1\nNO \t- \t2" << std::endl << std::endl;
		choose = _getch();
	}
	choose == '1' ? get_choose = 1 : get_choose = 0;
}

// Меню ввода
void user_interface::input_menu(char &current_mode, char &current_source) 
{
	current_mode = func_choose_mode();
	current_source = func_choose_source();
	std::cout << std::endl;
}*/