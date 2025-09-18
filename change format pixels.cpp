#include "functions.h"

void change_format_pixels::get_average(const pix_vec& pixels, size_t current_pixel, uc& average_r, uc& average_g, uc& average_b)
{
	size_t current_up_pixel = current_pixel - num_columns;
	size_t previous_pixel = current_pixel - 1;


	if (current_pixel >= 0)
	{
		if (pixels[current_pixel].column == 0 && pixels[current_pixel].row == 0)
		{
			average_r = 0;
			average_g = 0;
			average_b = 0;
		}
		else if (pixels[current_pixel].column == 0)
		{
			average_r = pixels[current_pixel].r + pixels[current_up_pixel].r / 2;
			average_g = pixels[current_pixel].g + pixels[current_up_pixel].g / 2;
			average_b = pixels[current_pixel].b + pixels[current_up_pixel].b / 2;
		}
		else if (pixels[current_pixel].row == 0)
		{
			average_r = pixels[current_pixel].r + pixels[previous_pixel].r / 2;
			average_g = pixels[current_pixel].g + pixels[previous_pixel].g / 2;
			average_b = pixels[current_pixel].b + pixels[previous_pixel].b / 2;
		}
		else
		{
			average_r = pixels[current_pixel].r + (pixels[previous_pixel].r + pixels[current_up_pixel].r) / 2;
			average_g = pixels[current_pixel].g + (pixels[previous_pixel].g + pixels[current_up_pixel].g) / 2;
			average_b = pixels[current_pixel].b + (pixels[previous_pixel].b + pixels[current_up_pixel].b) / 2;
		}
	}
}

uc change_format_pixels::get_paeth(const pix_vec& pixels, size_t current_pixel, uc code_color_pixel)
{
	// Позиции: верхнего, предыдущего и верхнего левого пикселя
	size_t current_up_pixel = current_pixel - num_columns;
	size_t previous_pixel = current_pixel - 1;
	size_t current_up_left_pixel = current_up_pixel - 1;

	// Сами пиксели
	int a = 0;
	int b = 0;
	int c = 0;

	if (previous_pixel >= 0) a = pixels[previous_pixel].r;
	if (current_up_pixel >= 0) b = pixels[current_up_pixel].r;
	if (current_up_left_pixel >= 0) c = pixels[current_up_left_pixel].r;

	// Вычисление расстояний

	int p = 0;
	size_t p_a = 0;
	size_t p_b = 0;
	size_t p_c = 0;

	// Проверка на границы
	if (pixels[current_pixel].column == 0 && pixels[current_pixel].row == 0)
	{
		a = 0;
		b = 0;
		c = 0;
	}
	else if (pixels[current_pixel].column == 0)
	{
		a = 0;
		c = 0;
	}
	else if (pixels[current_pixel].row == 0)
	{
		b = 0;
		c = 0;
	}
	else if (pixels[current_up_pixel].row == 0)
	{
		c = 0;
	}

	// Вычисление локальной функции
	p = a + b - c;
	p_a = abs(p - a);
	p_b = abs(p - b);
	p_c = abs(p - c);

	// Возврат верного значения
	if (p_a <= p_b && p_a <= p_c) return a;
	else if (p_b <= p_c) return b;
	else return c;
}

// Вставка пикселей
void change_format_pixels::change_format_sub_filter(pix_vec& pixels, size_t num_current_pixel)
{
	// Старотовый и следующий пиксель
	size_t start_pos = num_current_pixel - 1;
	size_t next_pos = num_current_pixel;

	// Изменение всех фильтро строки
	for(size_t index = 1; index < num_columns; ++index)
	{
		size_t current_pixel = start_pos + index;
		size_t next_pixel = next_pos + index;

		pixels[next_pos + index].r += pixels[start_pos + index].r;
		pixels[next_pos + index].g += pixels[start_pos + index].g;
		pixels[next_pos + index].b += pixels[start_pos + index].b;
	}
}

// Изменение формата столбцов пикселей
void change_format_pixels::change_format_up_filter(pix_vec& pixels, size_t index_row)
{
	// Стартовая верхняя и стартовая текущая координата
	size_t start_up_pos = index_row - num_columns;
	size_t start_pos = index_row;

	// Проверка на выход за границы
	if (pixels[start_pos].row == 0) return;

	// Преобразование столбца пикселей
	for (size_t index = 0; index < num_columns; ++index)
	{
		size_t current_up_pixel = start_up_pos + index;
		size_t current_pixel = start_pos + index;

		pixels[current_pixel].r += pixels[current_up_pixel].r;
		pixels[current_pixel].b += pixels[current_up_pixel].b;
		pixels[current_pixel].g += pixels[current_up_pixel].g;
	}
}

void change_format_pixels::change_format_average_filter(pix_vec& pixels, size_t index_row)
{
	// Работа с фильтром 3 , average для всей текущей строки
	for (size_t index = 0; index < num_columns; ++index)
	{
		// Текущий пиксель
		size_t current_pixel = index_row + index;

		// Разницы для r, g, b
		uc average_r, average_g, average_b;

		// Получение разниц
		get_average(pixels, current_pixel, average_r, average_g, average_b);

		// Сохранение значнеий
		pixels[current_pixel].r = average_r;
		pixels[current_pixel].g = average_g;
		pixels[current_pixel].b = average_b;
	}
}

void change_format_pixels::change_format_paeth_filter(pix_vec& pixels, size_t index_row)
{
	// Работа с фильтром 3 , paeth для всей текущей строки
	for (size_t index = 0; index < num_columns; ++index)
	{
		// Координаты текущего пикселя
		size_t current_pixel = index_row + index;

		// Сохранение значений
		pixels[current_pixel].r = get_paeth(pixels, current_pixel, pixels[current_pixel].r);
		pixels[current_pixel].g = get_paeth(pixels, current_pixel, pixels[current_pixel].g);
		pixels[current_pixel].b = get_paeth(pixels, current_pixel, pixels[current_pixel].b);
	}
}

// Функция для изменения формата ряда пикселей
void change_format_pixels::get(pix_vec& pixels)
{
	// Флаг для поочередного заполнения то столбца, то строки
	bool is_start_column = true;
	size_t index_filter_row = 0;

	// Заполнение
	for (size_t index_row = 0; index_row < num_pixels; index_row += num_columns, ++index_filter_row)
	{
		// Метод фильтрации для фильтра 0
		if (row_filter[index_filter_row] == 0) continue;
		// Метод фильтрации для фильра 1
		else if (row_filter[index_filter_row] == 1) change_format_sub_filter(pixels, index_row);
		// Для 2
		else if (row_filter[index_filter_row] == 2) change_format_up_filter(pixels, index_row);
		// ...
		else if (row_filter[index_filter_row] == 3) change_format_average_filter(pixels, index_row);
		else if (row_filter[index_filter_row] == 4) change_format_paeth_filter(pixels, index_row);

	}
}