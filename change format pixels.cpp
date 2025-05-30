#include "functions.h"

namespace 
{
	constexpr int IS_ROW_PIXELS = 1;
	constexpr int IS_NO_ROW_PIXELS = 2;
}

// Проверка пикселя на пустоту
bool change_format_pixels::is_null_pixel(const Pixel& pixel)
{
	return (pixel.r == 0 && pixel.g == 0 && pixel.b == 0);
}

// Проверка на конец ряда
bool change_format_pixels::is_end_of_row(Pixel& pixel)
{
	return (pixel.column == 0 && pixel.r == 0xff && pixel.g == 0xff && pixel.b == 0xff);
}

// Получение номера элемената конца пикселей
int change_format_pixels::get_num_last_element_column(const pix_vec& pixels, int& num_last_el_column, const int index)
{
	// Номер текущей строки
	const int num_current_row = pixels[index - 1].row;
	// Номер ненулевого(начало строки пикселей) пикселя
	const int num_not_null_el = index - 1;
	// Номер следующего (нулевого) пикселя
	int copy_num_first_el_column = index;
	// Пока значенич пикселя нулевые(идёт ряд) и строка не изменяется
	while (is_null_pixel(pixels[copy_num_first_el_column]) && num_current_row == pixels[copy_num_first_el_column].row)
	{
		// Номер Следующего пиксель
		copy_num_first_el_column++;
	}
	num_last_el_column = copy_num_first_el_column;
	// Проверка, изменилась ли строка
	if (pixels[copy_num_first_el_column].row != num_current_row)
	{	
		// Если новая строка
		num_last_el_column = index;
		return IS_ROW_PIXELS;
	}
	return IS_NO_ROW_PIXELS;
}

// Изменение сумм пикселей
void change_format_pixels::new_sum_pixels(const pix_vec& pixels, unsigned char& sum_r, unsigned char& sum_g, unsigned char& sum_b, const int index)
{
	sum_r += pixels[index - 1].r;
	sum_g += pixels[index - 1].g;
	sum_b += pixels[index - 1].b;
}

// ТЕСТ 
// ОТЛАДОЧНАЯ ФУНКЦИЯ
void change_format_pixels::show(const pix_vec& a)
{
	std::cout << std::endl << std::endl;
	for (int i = 0; i < a.size(); i++)
	{
		if (!is_null_pixel(a[i]))
			std::cout << "X: " << a[i].column << "\tY: " << a[i].row << "\t" << (int)a[i].r << "\t" << (int)a[i].g << "\t" << (int)a[i].b << std::endl;
	}
	std::cout << std::endl;
}
//

// Вставка пикселей
void change_format_pixels::change_format_column_pixels(pix_vec& new_pixels, const pix_vec& pixels, int& num_last_el_column, const int index, unsigned char& sum_r, unsigned char& sum_g, unsigned char& sum_b)
{
	// Первый элемент строки
	int num_first_el_column = index - 1;	
	!is_null_pixel(pixels[index - 2]) ? (printf("%d\t", sum_r)) : 0;

	// Пиксель для вставки в вектор пикселей
	Pixel pixel = { pixels[index - 1].column,
		pixels[index - 1].row,
		pixels[index - 1].r + sum_r,
		pixels[index - 1].g + sum_g,
		pixels[index - 1].b + sum_b };

	// Вставка в вектор пикселей
	for (int i = num_first_el_column; i < num_last_el_column; i++)
	{
		new_pixels.push_back(pixel);
		pixel.column++;
	}
	
	new_sum_pixels(pixels, sum_r, sum_g, sum_b, index);
}

void change_format_pixels::change_format_row_pixels(pix_vec& new_pixels, const pix_vec& pixels, int& num_last_el_row, const int index, unsigned char& sum_r, unsigned char& sum_g, unsigned char& sum_b)
{
	// Номер последнего элемента в столбца
	num_last_el_row = index;

	// Выполняется, пока идет столбец
	while (is_null_pixel(pixels[num_last_el_row]))
	{
		num_last_el_row++;
	}
	
	new_sum_pixels(pixels, sum_r, sum_g, sum_b, index);

	Pixel pixel = { pixels[index - 1].column,
		pixels[index - 1].row,
		pixels[index - 1].r + sum_r,
		pixels[index - 1].g + sum_g,
		pixels[index - 1].b + sum_b
	};

	for (int i = pixels[index].row; i < pixels[num_last_el_row].row; i++)
	{
		new_pixels.push_back(pixel);
		pixel.row++;
	}
}

// Функция для изменения формата ряда пикселей
void change_format_pixels::change_format_all_pixels(pix_vec& pixels)
{
	// Сумма предыдущих пикселей по r, g, b по X
	unsigned char column_sum_r = -1;
	unsigned char column_sum_g = -1;
	unsigned char column_sum_b = -1;

	// Сумма предыдущих пикселей по r, g, b по Y
	unsigned char row_sum_r = -1;
	unsigned char row_sum_g = -1;
	unsigned char row_sum_b = -1;

	// Проверка первого входа в функцию строк
	bool is_first_in_column = true;
	// Проверка первого входа в функцию столбцов
	bool is_first_in_row = true;
	// Вектор нового ряда пикселей (преобразованного)
	pix_vec new_pixels = { };
	for (int index = 1; index < pixels.size(); index++)
	{
		// Координаты конца строки пикселей
		int num_last_el_column = 0;
		// Координаты конца столбца пикселей
		int num_last_el_row = 0;
		// Проверка на конец строки пикселей
		if (is_end_of_row(pixels[index - 1]))
		{
			continue;
		}
		if (!is_null_pixel(pixels[index - 1]))
		{
			// Следующий элемент должен быть равен нулям
			if (get_num_last_element_column(pixels, num_last_el_column, index) == IS_ROW_PIXELS)
			{
				change_format_row_pixels(new_pixels, pixels, num_last_el_row, index, row_sum_r, row_sum_g, row_sum_b);

				//Обнуление суммы предыдущих пикселей по X
				column_sum_r = column_sum_g = column_sum_b = 0;
				continue;
			}
		}
		change_format_column_pixels(new_pixels, pixels, num_last_el_column, index, column_sum_r, column_sum_g, column_sum_b);

		//Обнуление суммы предыдущих пикселей по Y
		row_sum_r = row_sum_g = row_sum_b = 0;
	}
	// ОТЛАДОЧНОЕ ПРИСВОЕНИЕ ДЛЯ ТЕСТА
	pixels = new_pixels;
	// 
}