#include "functions.h"

// ���� ���� �� ��� �����
void work_with_files::get_path_to_png(str& path_to_png_file)
{
	std::cout << "Input path to .png file. ";
	open_file_dialog(path_to_png_file);
	while (!is_correct_file_format(path_to_png_file, "png"))
	{
		std::cout << "File format must be \".png\". Try again. " << std::endl << std::endl;
		open_file_dialog(path_to_png_file);
	}
}

// �������� ���� �����
bool work_with_files::is_correct_file_format(const str& file_name, const str& file_format)
{
	const int number_identificator_type_file = file_name.length() - 3;
	str type_file = file_name.substr(number_identificator_type_file, 3);
	return (type_file == file_format);
}
	
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
    
// ������ ������ �� �����
void work_with_files::input(str& text_from_file)
{
	str path_to_file;
	std::ifstream file;
	std::cout << "Input path to input file. ";
	open_file_dialog(path_to_file);
	while (!is_correct_file_format(path_to_file, "txt"))
	{
		std::cout << "File format must be \".txt\". Try again. " << std::endl << std::endl;
		open_file_dialog(path_to_file);
	}
	file.open(path_to_file);
	while (!file.is_open())
	{
		std::cout << "Error while opening file. Try again. " << std::endl << std::endl;
		open_file_dialog(path_to_file);
	}
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

// ����� � ���� �������� ����������
void work_with_files::output(const str& text)
{
	str path_to_file;
	std::ofstream file;
	std::cout << "Input path to output file.";
	open_file_dialog(path_to_file);
	while (!is_correct_file_format(path_to_file, "txt"))
	{
		std::cout << "File format must be \".txt\". Try again. " << std::endl << std::endl;
		open_file_dialog(path_to_file);
	}
	file.open(path_to_file);
	while (!file.is_open())
	{
		std::cout << "Error while opening file. Try again. " << std::endl << std::endl;
		open_file_dialog(path_to_file);
	}
	file << text;
	file.close();
}

// ����� � ���� �����
void work_with_files::output(const uc_vec& key)
{
	str key_in_format_text;
	str path_to_file;
	std::ofstream file;
	std::cout << "Input path to output file. ";
	open_file_dialog(path_to_file);
	while (!is_correct_file_format(path_to_file, "txt"))
	{
		std::cout << "File format must be \".txt\". Try again." << std::endl << std::endl;
		open_file_dialog(path_to_file);
	}
	file.open(path_to_file);
	if (!file.is_open())
	{
		std::cout << "Error while opening file. Try again.";
		open_file_dialog(path_to_file);
	}
	file << static_cast<int>(key[0]);
	for (int i = 2; i < key.size(); i++)
	{
		file << '|';
		while (key[i] != '|')
		{
			file << static_cast<int>(key[i]);
			i++;
		}
	}
	file.close();
}

void work_with_files::open_file_dialog(str& path_to_file)
{
	std::cout << "Press any key to continue. ";
	system("pause > nul");
	const int size_buffer = 1024;
	char buffer[size_buffer] = { 0 };
	OPENFILENAMEA open_file_name = { 0 };
	open_file_name.lStructSize = sizeof(open_file_name);
	open_file_name.lpstrFile = buffer;
	open_file_name.nMaxFile = size_buffer;
	GetOpenFileNameA(&open_file_name);
	buffer[1023] = '\0';
	path_to_file = static_cast<str>(buffer);
	if (path_to_file.empty())
	{
		std::cout << "Incorrect path to file. Try again. " << std::endl << std::endl;
		open_file_dialog(path_to_file);
	}
	std::cout << "Path: " << path_to_file;
	change_format_path_file(path_to_file);
	std::cout << std::endl << std::endl;
}

void work_with_files::png_read(uc_vec &code_file)
{
	str path_to_file = "C:\\Users\\1\\Downloads\\browser.png";

	// ����
	// get_path_to_png(path_to_file);	
	// 
	
	// ������ �����
	int size_file = 0;
	std::ifstream file(path_to_file, std::ios::binary);
	// �������� ����� �� ��������
	while (!file.is_open())
	{
		std::cout << "Error while opening .png file. Choose another file. " << std::endl << std::endl;
		get_path_to_png(path_to_file);
		file.open(path_to_file, std::ios::binary);
	}
	// ����������� ��������� ����� �� ����� �����
	file.seekg(0, std::ios::end);
	// ��������� ������� ��������� (���������� ���������)
	size_file = file.tellg();
	// ���������� ������� (���������� �������� � ����� ��� ���������)
	size_file -= 8;
	// ����������� ��������� �� 8 ������, �.� ������� ���������
	file.seekg(8, std::ios::beg);
	// ��������� ������� �����
	code_file.resize(size_file);
	// ������ ����� � ������� � ����������
	file.read(reinterpret_cast<char*>(code_file.data()), size_file);
	file.close();
}