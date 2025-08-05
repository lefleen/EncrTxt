#include "functions.h"

// Проверка на конкец столбца пикселей
bool change_format_pixels::is_end_or_start_column(const Pixel& pixel)
{
	return (pixel.r == 255 && pixel.g == 255 && pixel.b == 255);
}

bool is_id_start_or_end_column(const Pixel& pixel)
{
	return (pixel.column == 0 && pixel.r == 255 && pixel.g == 255 && pixel.b == 255);
}

// Проверка на стобец
bool change_format_pixels::is_row(const Pixel& pixel, const Pixel& next_pixel)
{
	if (next_pixel.row != pixel.row) 
	{
		bool is_same_column = (pixel.column == next_pixel.column);
		return (is_same_column);
	}
	return false;
}

// Вставка пикселей
void change_format_pixels::change_format_column_pixels(pix_vec& pixels, size_t num_current_pixel, size_t num_next_pixel, size_t& external_index)
{
	// Пропуск заполнения, если r, g, b равны 255
	if (is_end_or_start_column(pixels[num_next_pixel]))
	{
		return;
	}

	// Непрерывная строка пикселей
	static_cast<unsigned char>(pixels[num_next_pixel].r += pixels[num_current_pixel].r);
	static_cast<unsigned char>(pixels[num_next_pixel].g += pixels[num_current_pixel].g);
	static_cast<unsigned char>(pixels[num_next_pixel].b += pixels[num_current_pixel].b);
	//std::cout << pixels[num_next_pixel].row << "\t" << pixels[num_next_pixel].column << "\t" << (int)pixels[num_next_pixel].r << "\t" << (int)pixels[num_next_pixel].g << "\t" << (int)pixels[num_next_pixel].b << std::endl;

}

// Два пикселя, разница по координатам 1 и сами пиксели разные
void change_format_pixels::change_format_row_pixels(pix_vec& pixels, size_t num_current_pixel, size_t num_next_pixel, size_t& external_index)
{
	// Стартовая и конечная позиции
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

	--external_index;
}

// Функция для изменения формата ряда пикселей
void change_format_pixels::change_format_all_pixels(pix_vec& pixels)
{
	// Номер текущего пикселя
	size_t num_current_pixel = 0;
	// Номер следующего пикселя
	size_t num_next_pixel = 0;

	size_t copy_num_rows = num_rows;
	bool is_start = false;

	for (size_t index_column = 0; index_column < num_columns; ++index_column)
	{
		for (size_t index_row = 1; index_row < copy_num_rows; ++index_row)
		{
			num_current_pixel = (index_row - 1) * num_columns + index_column;
			num_next_pixel = index_row * num_columns + index_column;

			if (is_id_start_or_end_column(pixels[num_next_pixel]))
			{
				if (is_start)
				{
					copy_num_rows = pixels[num_next_pixel].row - 1;
					is_start = false;
					continue;
				}
				else
				{
					copy_num_rows = num_rows;
					is_start = true;
				}
			}

			//std::cout << index_column << " " << index_row << std::endl;

			change_format_column_pixels(pixels, num_current_pixel, num_next_pixel, index_row);

			//std::cout << pixels[num_next_pixel].row << " " << pixels[num_next_pixel].column << "\t" << pixels[num_current_pixel].row << " " << pixels[num_current_pixel].column << "\t" 
			//std::cout << num_next_pixel << std::endl;
		}
		change_format_column_pixels(pixels, num_next_pixel, num_columns + index_column + 1, index_column);
		//std::cout << num_next_pixel << "\t" << num_columns + index_column << std::endl;
		//std::cout << num_next_pixel << std::endl << std::endl << std::endl;
	}

	/*for (size_t index = 1; index <= pixels.size(); ++index)
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
	}*/
}