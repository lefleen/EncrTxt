#include "functions.h"

// Проверка на стобец
bool change_format_pixels::is_row(const Pixel& pixel, const Pixel& next_pixel)
{
	if (next_pixel.row != pixel.row) 
	{
		bool is_same_column = (pixel.column == next_pixel.column);
		bool is_white = (next_pixel.column == 0 && next_pixel.r == 255 && next_pixel.g == 255 && next_pixel.b == 255);
		return (is_same_column || is_white);
	}
	return false;
}

// Вставка пикселей
void change_format_pixels::change_format_column_pixels(pix_vec& pixels, size_t num_current_pixel, size_t num_next_pixel, size_t& external_index)
{

}

// Два пикселя, разница по координатам 1 и сами пиксели разные
void change_format_pixels::change_format_row_pixels(pix_vec& pixels, size_t num_current_pixel, size_t num_next_pixel, size_t& external_index)
{
	// Стартовая и начальная позиции
	size_t start_pos = pixels[num_current_pixel].row;
	size_t end_pos = pixels[num_next_pixel].row;


	// Вычисление пикслея
	Pixel pixel = {
		pixels[num_current_pixel].column,
		pixels[num_current_pixel].row,
		static_cast<unsigned char>(pixels[num_next_pixel].r - (256 - pixels[num_current_pixel].r)),
		static_cast<unsigned char>(pixels[num_next_pixel].g - (256 - pixels[num_current_pixel].g)),
		static_cast<unsigned char>(pixels[num_next_pixel].b - (256 - pixels[num_current_pixel].b))
	};


	// Его вставка с индексированием номера строки
	for (size_t index = start_pos; index < end_pos; ++index)
	{
		pixels.insert(pixels.begin() + num_current_pixel + (index - start_pos), pixel);
		++pixel.row;
		++external_index;
	}


	// Проверка на выход за границы и удаление ненужного элемента
	if (external_index - 1 >= 0 && external_index <= pixels.size())
	{
		pixels.erase(pixels.begin() + external_index - 1);
		pixels.erase(pixels.begin() + external_index - 1);
	}
}

// Функция для изменения формата ряда пикселей
void change_format_pixels::change_format_all_pixels(pix_vec& pixels)
{
	// Номер текущего пикселя
	size_t num_current_pixel;
	// Номер следующего пикселя
	size_t num_next_pixel;

	for (size_t index = 1; index <= pixels.size(); ++index)
	{
		num_current_pixel = index - 1;
		num_next_pixel = index;
		
		// Проверка на столбец пикселей
		if (is_row(pixels[num_current_pixel], pixels[num_next_pixel]))
		{
			// Два пикселя, разница по координатам 1 и сами пиксели разные
			change_format_row_pixels(pixels, num_current_pixel, num_next_pixel, index);
		}
		else
		{
			change_format_column_pixels(pixels, num_current_pixel, num_next_pixel, index);
		}
	}
}