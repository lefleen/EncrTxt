#include "functions.h"
#include "classes.h"

// Нахождение размеров изображения, X и Y
int search_pixels::extract_dimension_from_ihdr(unsigned long& dimension, const uc_vec& IHDR, const bool is_y)
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

// Поиск не нулевых пикселей
int search_pixels::get_pixels(const uc_vec& IDAT, const uc_vec& IHDR, pix_vec& pixels)
{
	int error;
	// Количество байт в одном пикселе
	const int bytes_per_pixel = 4;

	// Нахождение строк и столбцов
	error = extract_dimension_from_ihdr(num_rows, IHDR, true);
	error = extract_dimension_from_ihdr(num_columns, IHDR, false);
	// Индекс для IDAT - чанка
	int index = 1;

	// Подготовака места для будущих вставок
	pixels.reserve(num_columns * num_rows);

	// Проверка на размер изображения
	if (num_rows <= 0 || num_columns <= 0)
	{
		std::cout << "Num rows or(and) columns is empty, or(and) null. Try again in next time." << std::endl << std::endl;
		return -1;
	}

	for (int row = 0; row < num_rows; ++row, ++index)
	{
		for (int column = 0; column < num_columns; ++column, index += bytes_per_pixel)
		{
			Pixel pixel = { column, row, IDAT[index], IDAT[index + 1], IDAT[index + 2] };
			pixels.push_back(pixel);
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