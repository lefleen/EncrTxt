#include "functions.h"

handler_write_png::handler_write_png(const handler_read_png& Png)
{
	IDAT = Png.IDAT;
	IHDR = Png.IHDR;
	PLTE = Png.PLTE;
	pixels = Png.pixels;
}

void handler_write_png::write_png()
{
	bytes code_file;
	write_png_in_value(code_file);
	write_png_in_file(code_file);
}

void handler_write_png::write_png_in_value(bytes& code_file)
{
	// Переменные для ошибок
	int num_attempts = 0;

	// Запись всех чанков и получение кода ошибки, а также подсчет количества ошибок
	for(size_t num_attempts = 0; num_attempts < 3; ++num_attempts)
	{
		if(create_png::set(code_file, IDAT, IHDR, PLTE, pixels) == 0) break;
	}
}

void handler_write_png::write_png_in_file(const bytes& code_file)
{
	// Запись в файл
	work_with_files::output(code_file);
}