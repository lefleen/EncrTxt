#include "functions.h"

void show(const pix_vec& pixels)
{
	for (int i = 0; i < pixels.size(); i++)
	{
		if ((pixels[i].r == 0 && pixels[i].g == 0 && pixels[i].b == 0) || (pixels[i].r == 255 && pixels[i].g == 255 && pixels[i].b == 255))
		{
			continue;
		}
		std::cout << pixels[i].row << "\t" << pixels[i].column << "\t" << (int)pixels[i].r << "\t" << (int)pixels[i].g << "\t" << (int)pixels[i].b << std::endl;
	}
	std::cout << std::endl;
}


void handler_read_png::get_code_file(uc_vec& code_file)
{
	work_with_files::get(code_file);
}

void handler_read_png::get_chunks(uc_vec& code_file)
{
	// Флаг для ошибки и поддсчет количества попыток, если она найдена. Получение пикселей
	for (size_t num_attempts = 0; num_attempts < 3; ++num_attempts)
	{
		if (work_with_chunks::get(IDAT, IHDR, code_file) == 0) break;
	}
}
	
void handler_read_png::get_pixels()
{
	// Флаг для ошибки и поддсчет количества попыток, если она найдена. Получение пикселей
	for (size_t num_attempts = 0; num_attempts < 3; ++num_attempts)
	{
		if (search_pixels::get(IDAT, IHDR, pixels) == 0) break;
	}
}

void handler_read_png::change_format_pixels() 
{
	change_format_pixels::get(pixels);
}

void handler_read_png::png_read_pixels()
{
	uc_vec code_file;

	get_code_file(code_file);
	get_chunks(code_file);
	get_pixels();
	change_format_pixels();

	show(pixels);
}