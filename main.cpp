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

void main_get_pixels(work_with_files& file, pix_vec& pixels)
{
	work_with_chunks chunks;
	change_format_pixels correct_format_pixels;

	uc_vec code_file;
	uc_vec IDAT;
	uc_vec IHDR;

	int error_chunk;
	int error_pixel;

	search_pixels image;

	file.png_read(code_file);

	error_chunk = chunks.get(IDAT, IHDR, code_file);
	error_pixel = image.get_pixels(IDAT, IHDR, pixels);

	if (error_chunk == -1 || error_pixel == -1)
	{
		main_get_pixels(file, pixels);
	}

	// ОЛАДОЧНАЯ ИНФОРМАЦИЯ
	//std::cout << "show 1\n";
	//show(pixels);
	//
	
	//preprocess.delete_unnecessary_elements(pixels);

    // ОТЛАДОЧНАЯ ИНФА
	std::cout << "show 1\n";
	show(pixels);
	//

	correct_format_pixels.change_format_all_pixels(pixels);

	// ОТЛАДОЧНАЯ ИНФА
	std::cout << "show 2\n";
	show(pixels);
	//
}

void encr_final(str& input_text, uc_vec& key, work_with_files& file)
{
	// Взаимодейтсвие  с режимами шифрования и дешифрования
	cryptograthy crypto;
	pix_vec pixels;
	
	int error = 0;

	main_get_pixels(file, pixels);
	error = crypto.encryption_text(input_text, pixels, key);
	if (error == -1)
	{
		main_get_pixels(file, pixels);
		encr_final(input_text, key, file);
	}
}

void decr_final(str& input_text, str& plain_text, work_with_files& file)
{
	
	// Взаимодейтсвие с режимами шифрования и дешифрования
	cryptograthy crypto;
	pix_vec pixels;
	
	int error = 0;

	main_get_pixels(file, pixels);
	error = crypto.decryption_text(input_text, pixels, plain_text);
	if (error == -1)
	{
		main_get_pixels(file, pixels);
		decr_final(input_text, plain_text, file);
	}
}

void main(){
	system("chcp 1251 > nul");

	// Выбор для продолжения после окончания программы
	int choose_continue = 1;

	// ТЕСТ:
	//
	//
	work_with_files file;
	pix_vec pixels;
	main_get_pixels(file, pixels);
	//
	// 
	// КОНЕЦ ТЕСТА

	/*while (choose_continue == 1)
	{
		//Взаимодейтсвие с пользователем
		user_interface ui;
		// Взаимодейтсвие с файловой системой
		work_with_files file;

		str path_to_input_file;
		str input_text;

		pix_vec pixels;

		int error = 0;

		// Выбор мода - шифрование или дешифрование
		char current_mode;
		// Выбор источника - консоль или файл
		char current_source;
		ui.input_menu(current_mode, current_source);

		if (current_mode == '1')
		{
			if (current_source == '1')
			{
				ui.input_from_console(input_text);
			}
			else if (current_source == '2')
			{
				file.input(input_text);
			}
			uc_vec key;
			encr_final(input_text, key, file);
			file.output(key);
		}
		else
		{
			if (current_source == '1')
			{
				ui.input_from_console(input_text);
			}
			else if (current_source == '2')
			{
				file.input(input_text);
			}
			str plain_text;
			decr_final(input_text, plain_text, file);
			file.output(plain_text);
		}
		ui.do_you_want_continue(choose_continue);
		system("cls");
	}*/
}