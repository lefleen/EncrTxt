#include "functions.h"

// Проверка на стобец
bool change_format_pixels::is_row(const Pixel& pixel, const Pixel& next_pixel) 
{
	return pixel.column == next_pixel.column && pixel.row != next_pixel.row
		|| pixel.column == 0 && pixel.r == 255 && pixel.g == 255 && pixel.b == 255;
}

bool change_format_pixels::is_row_same_pixels(const Pixel& pixel, const Pixel& next_pixel)
{
	return (next_pixel.row - pixel.row > 1);
}

// Проверка на строку
bool change_format_pixels::is_column(const Pixel& pixel, const Pixel& next_pixel)
{
	return pixel.row == next_pixel.row && pixel.column != next_pixel.column;
}

// Получение номера элемената конца пикселей
int change_format_pixels::get_num_last_element_column()
{

}

// Изменение сумм пикселей
void change_format_pixels::new_sum_pixels()
{

}

// Вставка пикселей
void change_format_pixels::change_format_column_pixels()
{

}

// Два пикселя, разница по координатам 1 и сами пиксели разные
void change_format_pixels::change_format_row_different_pixels(pix_vec& pixels, size_t num_current_pixel, size_t num_next_pixel, size_t& external_index)
{
	pixels[num_next_pixel] = {
		pixels[num_next_pixel].column,
		pixels[num_next_pixel].row,
		static_cast<unsigned char>(pixels[num_next_pixel].r - (256 - pixels[num_current_pixel].r)),
		static_cast<unsigned char>(pixels[num_next_pixel].g - (256 - pixels[num_current_pixel].g)),
		static_cast<unsigned char>(pixels[num_next_pixel].b - (256 - pixels[num_current_pixel].b))
	};
}

// Непрерывный ряд одинаковыъ пикселей
void change_format_pixels::change_format_row_same_pixels(pix_vec& pixels, size_t num_current_pixel, size_t num_next_pixel, size_t& external_index)
{
	size_t start_pos = pixels[num_next_pixel].row;
	size_t end_pos = pixels[num_next_pixel + 1].row;
	Pixel pixel = {
			   pixels[num_next_pixel].column,
			   pixels[num_next_pixel].row,
			   static_cast<unsigned char>(pixels[num_next_pixel].r - (256 - pixels[num_current_pixel].r)),
			   static_cast<unsigned char>(pixels[num_next_pixel].g - (256 - pixels[num_current_pixel].g)),
			   static_cast<unsigned char>(pixels[num_next_pixel].b - (256 - pixels[num_current_pixel].b))
	};
	for (size_t index = start_pos; index < end_pos; ++index)
	{
		pixels.insert(pixels.begin() + external_index, pixel);
		++pixel.row;
		++external_index;
	}
	// Удаление (первого элемента столбца)
	pixels.erase(pixels.begin() + external_index);
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
		// Проверка на строку пикселей
		if (is_column(pixels[num_current_pixel], pixels[num_next_pixel]))
		{
			change_format_column_pixels();
		}
		// Проверка на столбец пикселей
		else if (is_row(pixels[num_current_pixel], pixels[num_next_pixel]))
		{
			// Одинаковые пиксели в столбце
			if (is_row_same_pixels(pixels[num_current_pixel], pixels[num_next_pixel]))
			{
				// Непрерывный ряд одинаковыъ пикселей
				change_format_row_same_pixels(pixels, num_current_pixel, num_next_pixel, index);
			}
			// Разные пиксли в столбце
			else
			{
				// Два пикселя, разница по координатам 1 и сами пиксели разные
				change_format_row_different_pixels(pixels, num_current_pixel, num_next_pixel, index);
			}
		}
	}
}