#include "classes.h"
#include "functions.h"

// Проверка на конец ряда
bool preprocessing_pixels::is_null_pixel(const Pixel& pixel)
{
	return (pixel.r == 0 && pixel.g == 0 && pixel.b == 0);
}

// Проверка на белый цвет
bool preprocessing_pixels::is_white_color(const Pixel& pixel)
{
	return (pixel.r == 255 && pixel.g == 255 && pixel.b == 255);
}

void preprocessing_pixels::delete_unnecessary_elements(pix_vec& pixels)
{
	// Вектор для пикселей после обработки
	pix_vec ready_to_processing;

	for (int index = 0; index < pixels.size(); index++)
	{
		// Если конец строки (роли не играет в дальнейшем, поэтому убираем)
		if (is_null_pixel(pixels[index]))
		{
			continue;
		}
		// После всех проверок вставляем пиксель
		ready_to_processing.push_back(pixels[index]);
	}
	pixels = ready_to_processing;
}