#include "functions.h"

void change_format_pixels::get_average(const pix_vec& pixels, size_t current_pixel, uc& average_r, uc& average_g, uc& average_b)
{
	size_t current_up_pixel = current_pixel - num_columns;
	size_t previous_pixel = current_pixel - 1;

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

	average_r = pixels[current_pixel].r + (pixels[previous_pixel].r + pixels[current_up_pixel].r) / 2;
	average_g = pixels[current_pixel].g + (pixels[previous_pixel].g + pixels[current_up_pixel].g) / 2;
	average_b = pixels[current_pixel].b + (pixels[previous_pixel].b + pixels[current_up_pixel].b) / 2;
}

// Вставка пикселей
void change_format_pixels::change_format_sub_filter(pix_vec& pixels, size_t num_current_pixel)
{
	size_t start_pos = num_current_pixel - 1;
	size_t next_pos = num_current_pixel;

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
	size_t start_up_pos = index_row - num_columns;
	size_t start_pos = index_row;

	if (pixels[start_pos].row == 0) return;

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
	for (size_t index = 0; index < num_columns; ++index)
	{
		size_t current_pixel = index_row + index;
		uc average_r, average_g, average_b;
		get_average(pixels, current_pixel, average_r, average_g, average_b);

		pixels[current_pixel].r = average_r;
		pixels[current_pixel].g = average_g;
		pixels[current_pixel].b = average_b;
	}
}

// Функция для изменения формата ряда пикселей
void change_format_pixels::change_format_all_pixels(pix_vec& pixels)
{
	// Флаг для поочередного заполнения то столбца, то строки
	bool is_start_column = true;
	size_t index_filter_row = 0;

	// Заполнение
	for (size_t index_row = 0; index_row < num_pixels; index_row += num_columns, ++index_filter_row)
	{
		if (row_filter[index_filter_row] == 0) continue;
		else if (row_filter[index_filter_row] == 1) change_format_sub_filter(pixels, index_row);
		else if (row_filter[index_filter_row] == 2) change_format_up_filter(pixels, index_row);
		else if (row_filter[index_filter_row] == 3) change_format_average_filter(pixels, index_row);
		//else if (row_filter[index_filter_row] == 4) change_format_paeth_filter(pixels, index_row);
	}
}