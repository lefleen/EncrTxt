#include "functions.h"
#include "classes.h"

#define SHOW_PIXEL(pixel) std::cout << pixel.column << "\t" << pixel.row << "\t" << (int)pixel.r << "\t" << (int)pixel.g << "\t" << (int)pixel.b << std::endl;

// Нахождение размеров изображения, X и Y
int search_pixels::extract_dimension_from_ihdr(unsigned long& dimension, const uc_vec & IHDR, const bool is_y)
{
	int offset_IHDR_on_row_or_column = is_y ? 4 : 0;
	// Проверка чанка на корректность
	if (IHDR.size() < 8)
	{
		std::cout << "Uncorrect size IHDR. Try again in next time." << std::endl << std::endl;
		return -1;
	}
	// Преобразование в правильный формат бвайт из Big endian и нахождение размера измерения
	for (int i = 0; i < 4; i++)
	{
		dimension = (dimension << 8) | (IHDR[i + offset_IHDR_on_row_or_column]);
	}
	return 0;
}

// Проверка пикселя на пустоту
bool search_pixels::is_null_pixel(const uc_vec &IDAT, const int index)
{
	return !(index + 2 < IDAT.size()  && IDAT[index] != 0 || IDAT[index + 1] != 0 || IDAT[index + 2] != 0);
}

// Проверка на конец ряда
bool is_end_of_row(const uc_vec &IDAT, const int index, const int column) 
{
	return (index + 2 < IDAT.size() && IDAT[index] == 0xff && IDAT[index + 1] == 0xff && IDAT[index + 2] == 0xff && column == 0);
}

// Поиск не нулевых пикселей
int search_pixels::get_pixels(const uc_vec& IDAT, const uc_vec& IHDR, pix_vec& pixels)
{
	int error;
	// Количество байт в одном пикселе
	const int bytes_per_pixel = 4;
	// Количество строк и столбцов
	unsigned long num_rows = 0, num_columns = 0;
	// Нахождение строк и столбцов
	error = extract_dimension_from_ihdr(num_rows, IHDR, true);
	error = extract_dimension_from_ihdr(num_columns, IHDR, false);
	// Индекс для IDAT - чанка
	int index = 0;
	// Переменная для определения наличия пикселей перед идентификатором конца строки (column = 0, r | g | b = 0xff)
	bool is_first_end_of_row = true;
	// Проверка на размер изображения
	if (num_rows <= 0 || num_columns <= 0)
	{
		std::cout << "Num rows or(and) columns is empty, or(and) null. Try again in next time." << std::endl << std::endl;
		return -1;
	}
	for (int row = 0; row < num_rows; row++)
	{
		// Пропуск фильтра строки пикселей (первый байт строки)
		index++;
		for (int column = 0; column < num_columns; column++)
		{
			pixels.push_back({ column, row });
			// Проверка пикселя на пустоту
			if (!is_null_pixel(IDAT, index))
			{
				// Заполнение вектора не нулевыми пикселями
				Pixel pixel = { column, row, IDAT[index], IDAT[index + 1], IDAT[index + 2] };
				pixels.back() = pixel;
				// Проверка на идентификатор конца ряда
				if (is_first_end_of_row && is_end_of_row(IDAT, index, column))
				{
					// Удаление идентификатора конца ряда
					pixels.pop_back();
				}
				else if (is_first_end_of_row)
				{
					is_first_end_of_row = false;
				}
			}
			// Следующий пиксель
			index += bytes_per_pixel;
		}
	}
	// Проверка на наличия пикселей
	if (pixels.empty())
	{
		std::cout << "Pixels doestn't found or num pixel is NULL. Try again in next time." << std::endl << std::endl;
		return -1;
	}
	//pixels.pop_back();
	return 0;
}