 #include "functions.h"

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

	// ��������� ����������
	correct_format_pixels.show(pixels);
	//

	correct_format_pixels.change_format_all_pixels(pixels);

	// ���������� ����
	correct_format_pixels.show(pixels);
	//

	if (error_chunk == -1 || error_pixel == -1)
	{
		main_get_pixels(file, pixels);
	}
}

void encr_final(str& input_text, uc_vec& key, work_with_files& file)
{
	// ��������������  � �������� ���������� � ������������
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
	
	// �������������� � �������� ���������� � ������������
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

	// ����� ��� ����������� ����� ��������� ���������
	int choose_continue = 1;

	// ����:
	//
	//
	work_with_files file;
	pix_vec pixels;
	main_get_pixels(file, pixels);
	//
	// 
	// ����� �����

	/*while (choose_continue == 1)
	{
		//�������������� � �������������
		user_interface ui;
		// �������������� � �������� ��������
		work_with_files file;

		str path_to_input_file;
		str input_text;

		pix_vec pixels;

		int error = 0;

		// ����� ���� - ���������� ��� ������������
		char current_mode;
		// ����� ��������� - ������� ��� ����
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