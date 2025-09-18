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

void get_pixels(pix_vec& pixels)
{
	uc_vec code_file;
	uc_vec IDAT;
	uc_vec IHDR;

	int error_chunk;
	int error_pixel;

	work_with_files::get(code_file);

	error_chunk = work_with_chunks::get(IDAT, IHDR, code_file);
	error_pixel = search_pixels::get(IDAT, IHDR, pixels);

	if (error_chunk == -1 || error_pixel == -1)
	{
		get_pixels(pixels);
	}
}

void main()
{
	system("chcp 1251 > nul");

	int choose_continue = 1;

	pix_vec pixels;
	get_pixels(pixels);
}