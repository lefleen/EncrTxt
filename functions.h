#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include "Windows.h"
#include "classes.h"
#include "zlib.h"

using str = std::string;
using pix_vec = std::vector<Pixel>;
using uc_vec = std::vector<unsigned char>;

class png 
{
public:
	static unsigned long num_rows;
	static unsigned long num_columns;
};

class user_interface : public png
{
	bool is_coorect_input(const char value, const char min_val_arg, const char max_val_arg);
	char func_choose_source();
	char func_choose_mode();
public:
	void input_from_console(str& text_from_console);
	void do_you_want_continue(int& choose);
	void input_menu(char &current_mode, char &current_source);
};

class work_with_files : public png
{
	bool is_correct_file_format(const str& file_name, const str& file_format);
	void change_format_path_file(str& path_to_file);
	void open_file_dialog(str& path_to_file);
	void get_path_to_png(str& path_to_png_file);
public:
	void png_read(uc_vec &code_file);
	void input(str& text_from_file);
	void output(const uc_vec& text);
	void output(const str& text);
};

class work_with_chunks : public png
{
	bool is_true_chunk(int index, const uc_vec& code_file, const str& name_chunk);
	int from_file_to_chunk(uc_vec& chunk, const uc_vec& code_file, int position_chunk_in_flle);
	long get_length_chunk(int chunk_offset_size, const uc_vec& code_chunk);
	uc_vec uncompress_chunk(const uc_vec& compress_chunk);
	uc_vec search_chunk(const uc_vec& code_file, const str& name_chunk);
public:
	int get(uc_vec& IDAT, uc_vec& IHDR, const uc_vec& code_file);
};

class cryptograthy : public png
{
	void show_plain_text(const str& plain_text);
	void show_key(const uc_vec& key);
public:
	int encryption_text(const str& text, const pix_vec& pixels, uc_vec& key);
	int decryption_text(const str& text, const pix_vec& pixels, str& plain_text);
};

class search_pixels : public png
{
private:
	int extract_dimension_from_ihdr(unsigned long& dimension, const uc_vec& IHDR, const bool is_y);
public:
	int get_pixels(const uc_vec& IDAT, const uc_vec& IHDR, pix_vec& pixels);
};

class change_format_pixels : public png
{
private:
	bool is_row(const Pixel& pixel, const Pixel& next_pixel);
	bool is_end_or_start_column(const Pixel& pixel);
	void change_format_row_pixels(pix_vec& pixels, size_t num_current_pixel, size_t num_next_pixel, size_t& external_index);
	void change_format_column_pixels(pix_vec& pixels, size_t num_current_pixel, size_t num_next_pixel, size_t& external_index);
public:
	void change_format_all_pixels(pix_vec& pixels);
};

class preprocessing_pixels : public png
{
private:
	bool is_white_color(const Pixel& pixel);
	bool is_null_pixel(const Pixel& pixel);
public:
	void delete_unnecessary_elements(pix_vec& pixels);
};
