#include "functions.h"

// Ввод пути до пнг файла
void work_with_files::get_path_to_png(str& path_to_png_file)
{
	// Ввод пути до файла с помощью диалогового окна
	std::cout << "Input path to .png file. ";
	open_file_dialog(path_to_png_file);

	// Пока не будет кооректного название, будет вызываеться диалоговое окно
	while (!is_correct_file_format(path_to_png_file, "png"))
	{
		std::cout << "File format must be \".png\". Try again. " << std::endl << std::endl;
		open_file_dialog(path_to_png_file);
	}
}

// Проверка типа файла
bool work_with_files::is_correct_file_format(const str& file_name, const str& file_format)
{
	// Смещение на формат файла(последние три символа)
	const int number_identificator_type_file = file_name.length() - 3;

	// Получение подстроки с форматом
	str type_file = file_name.substr(number_identificator_type_file, 3);

	// Проверка
	return (type_file == file_format);
}
	
// Преобразование пути к файлу
void work_with_files::change_format_path_file(str& path_to_file)
{
	for (int i = 0; i < path_to_file.length(); i++)
	{
		if (path_to_file[i] == '/')
		{
			path_to_file += '/';
		}
		else if (path_to_file[i] == '"')
		{
			path_to_file.erase(path_to_file.begin() + i);
		}
	}
}
    
// Чтение текста из файла
void work_with_files::input(str& text_from_file)
{
	// Переменная для хранения пути
	str path_to_file;
	std::ifstream file;
	std::cout << "Input path to input file. ";

	// Диалоговыое меню проводника
	open_file_dialog(path_to_file);

	// Вызывается, пока не будеи корректным путь
	while (!is_correct_file_format(path_to_file, "txt"))
	{
		std::cout << "File format must be \".txt\". Try again. " << std::endl << std::endl;
		open_file_dialog(path_to_file);
	}

	// Открытие файла
	file.open(path_to_file);

	// Вызовы, пока файл не откроется (смена файлов)
	while (!file.is_open())
	{
		std::cout << "Error while opening file. Try again. " << std::endl << std::endl;
		open_file_dialog(path_to_file);
	}

	// Пока не конец файла, считывает построчно 
	while (!file.eof())
	{
		str line;
		std::getline(file, line);
		text_from_file += line;
		text_from_file += '\n';
	}

	text_from_file.pop_back();
	file.close();
}

// Вывод в файл тектовой переменной
void work_with_files::output(const bytes& text)
{
	// Переменная для хранения пути
	str path_to_file;
	std::ofstream file;

	std::cout << "Input path to output file.";

	// Диалоговыое меню проводника
	open_file_dialog(path_to_file);

	// Вызывается, пока не будеи корректным путь
	while (!is_correct_file_format(path_to_file, "png"))
	{
		std::cout << "File format must be \".txt\". Try again. " << std::endl << std::endl;
		open_file_dialog(path_to_file);
	}

	// Открытие файла в двоичном виде
	file.open(path_to_file, std::ios::binary);

	// Пока не конец файла, считывает построчно 
	while (!file.is_open())
	{
		std::cout << "Error while opening file. Try again. " << std::endl << std::endl;
		open_file_dialog(path_to_file);
	}

	// Вывод в файл текста
	for (size_t index = 0; index < text.size(); ++index) file << text[index];

	file.close();
}

void work_with_files::open_file_dialog(str& path_to_file)
{
	std::cout << "Press any key to continue. ";
	system("pause > nul");

	// Буфер для размера имени
	const int size_buffer = 1024;
	char buffer[size_buffer] = { 0 };

	// Объект класса
	OPENFILENAMEA open_file_name = { 0 };
	// Получение размера структуры
	open_file_name.lStructSize = sizeof(open_file_name);
	// Получение размепа файла
	open_file_name.lpstrFile = buffer;
	// Максимальный размер
	open_file_name.nMaxFile = size_buffer;

	// Окрытие файла 
	GetOpenFileNameA(&open_file_name);
	buffer[1023] = '\0';

	// Преобразование char* в std::string
	path_to_file = static_cast<str>(buffer);

	// Проверка на пустоту
	if (path_to_file.empty())
	{
		std::cout << "Incorrect path to file. Try again. " << std::endl << std::endl;
		open_file_dialog(path_to_file);
		return;
	}

	// Вывод пути и его изменение
	std::cout << "Path: " << path_to_file;
	change_format_path_file(path_to_file);

	std::cout << std::endl << std::endl;
}

void work_with_files::get(uc_vec &code_file)
{
	str path_to_file;

	// ТЕСТ
	get_path_to_png(path_to_file);	
	// 
	
	// Размер файла
	int size_file = 0;
	std::ifstream file(path_to_file, std::ios::binary);

	// Проверка файла на открытие
	while (!file.is_open())
	{
		std::cout << "Error while opening .png file. Choose another file. " << std::endl << std::endl;
		get_path_to_png(path_to_file);
		file.open(path_to_file, std::ios::binary);
	}

	// Перемещение указателя файла на конец файла
	file.seekg(0, std::ios::end);

	// Получение позиции указателя (количество элементов)
	size_file = file.tellg();

	// Уменьшение размера (количество символов в файле без сигнатуры)
	size_file -= 8;

	// Перемещение указателя на 8 символ, т.е пропуск сигнатуры
	file.seekg(8, std::ios::beg);

	// Изменение размера файла
	code_file.resize(size_file);

	// Чтение файла с записью в переменные
	file.read(reinterpret_cast<char*>(code_file.data()), size_file);
	file.close();
}