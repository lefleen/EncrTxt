 #include "functions.h"

void main()
{
	// Установка русской локали
	system("chcp 1251 > nul");

	// Чтение пнг
	handler_read_png PngRead;
	PngRead.png_read_pixels();

	// Запись пнг
	handler_write_png PngWrite(PngRead);
	PngWrite.write_png();
}