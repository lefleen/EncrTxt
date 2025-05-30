#include "functions.h"

#define IS_ROW_PIXELS 1
#define IS_NO_ROW_PIXELS 2

// �������� ������� �� �������
bool change_format_pixels::is_null_pixel(const Pixel& pixel)
{
	return (pixel.r == 0 && pixel.g == 0 && pixel.b == 0);
}

// �������� �� ����� ����
bool change_format_pixels::is_end_of_row(Pixel& pixel)
{
	return (pixel.column == 0 && pixel.r == 0xff && pixel.g == 0xff && pixel.b == 0xff);
}

// ��������� ������ ��������� ����� ��������
int change_format_pixels::get_num_last_element_column(const pix_vec& pixels, int& num_last_el_column, const int index)
{
	// ����� ������� ������
	const int num_current_row = pixels[index - 1].row;
	// ����� ����������(������ ������ ��������) �������
	const int num_not_null_el = index - 1;
	// ����� ���������� (��������) �������
	int copy_num_first_el_column = index;
	// ���� �������� ������� �������(��� ���) � ������ �� ����������
	while (is_null_pixel(pixels[copy_num_first_el_column]) && num_current_row == pixels[copy_num_first_el_column].row)
	{
		// ����� ���������� �������
		copy_num_first_el_column++;
	}
	num_last_el_column = copy_num_first_el_column;
	// ��������, ���������� �� ������
	if (pixels[copy_num_first_el_column].row != num_current_row)
	{	
		// ���� ����� ������
		num_last_el_column = index;
		return IS_ROW_PIXELS;
	}
	return IS_NO_ROW_PIXELS;
}

// ��������� ���� ��������
void change_format_pixels::new_sum_pixels(const pix_vec& pixels, unsigned char& sum_r, unsigned char& sum_g, unsigned char& sum_b, const int index)
{
	sum_r += pixels[index - 1].r;
	sum_g += pixels[index - 1].g;
	sum_b += pixels[index - 1].b;
}

// ���� 
// ���������� �������
void change_format_pixels::show(const pix_vec& a)
{
	std::cout << std::endl << std::endl;
	for (int i = 0; i < a.size(); i++)
	{
		if (!is_null_pixel(a[i]))
			std::cout << "X: " << a[i].column << "\tY: " << a[i].row << "\t" << (int)a[i].r << "\t" << (int)a[i].g << "\t" << (int)a[i].b << std::endl;
	}
	std::cout << std::endl;
}
//

// ������� ��������
void change_format_pixels::change_format_column_pixels(pix_vec& new_pixels, const pix_vec& pixels, int& num_last_el_column, const int index, unsigned char& sum_r, unsigned char& sum_g, unsigned char& sum_b)
{
	// ������ ������� ������
	int num_first_el_column = index - 1;	
	!is_null_pixel(pixels[index - 2]) ? (printf("%d\t", sum_r)) : 0;

	// ������� ��� ������� � ������ ��������
	Pixel pixel = { pixels[index - 1].column,
		pixels[index - 1].row,
		pixels[index - 1].r + sum_r,
		pixels[index - 1].g + sum_g,
		pixels[index - 1].b + sum_b };

	// ������� � ������ ��������
	for (int i = num_first_el_column; i < num_last_el_column; i++)
	{
		new_pixels.push_back(pixel);
		pixel.column++;
	}
	
	new_sum_pixels(pixels, sum_r, sum_g, sum_b, index);
}

void change_format_pixels::change_format_row_pixels(pix_vec& new_pixels, const pix_vec& pixels, int& num_last_el_row, const int index, unsigned char& sum_r, unsigned char& sum_g, unsigned char& sum_b)
{
	// ����� ���������� �������� � �������
	num_last_el_row = index;

	// �����������, ���� ���� �������
	while (is_null_pixel(pixels[num_last_el_row]))
	{
		num_last_el_row++;
	}
	
	new_sum_pixels(pixels, sum_r, sum_g, sum_b, index);

	Pixel pixel = { pixels[index - 1].column,
		pixels[index - 1].row,
		pixels[index - 1].r + sum_r,
		pixels[index - 1].g + sum_g,
		pixels[index - 1].b + sum_b
	};

	for (int i = pixels[index].row; i < pixels[num_last_el_row].row; i++)
	{
		new_pixels.push_back(pixel);
		pixel.row++;
	}
}

// ������� ��� ��������� ������� ���� ��������
void change_format_pixels::change_format_all_pixels(pix_vec& pixels)
{
	// ����� ���������� �������� �� r, g, b �� X
	unsigned char column_sum_r = -1;
	unsigned char column_sum_g = -1;
	unsigned char column_sum_b = -1;

	// ����� ���������� �������� �� r, g, b �� Y
	unsigned char row_sum_r = -1;
	unsigned char row_sum_g = -1;
	unsigned char row_sum_b = -1;

	// �������� ������� ����� � ������� �����
	bool is_first_in_column = true;
	// �������� ������� ����� � ������� ��������
	bool is_first_in_row = true;
	// ������ ������ ���� �������� (����������������)
	pix_vec new_pixels = { };
	for (int index = 1; index < pixels.size(); index++)
	{
		// ���������� ����� ������ ��������
		int num_last_el_column = 0;
		// ���������� ����� ������� ��������
		int num_last_el_row = 0;
		// �������� �� ����� ������ ��������
		if (is_end_of_row(pixels[index - 1]))
		{
			continue;
		}
		if (!is_null_pixel(pixels[index - 1]))
		{
			// ��������� ������� ������ ���� ����� �����
			if (get_num_last_element_column(pixels, num_last_el_column, index) == IS_ROW_PIXELS)
			{
				change_format_row_pixels(new_pixels, pixels, num_last_el_row, index, row_sum_r, row_sum_g, row_sum_b);

				//��������� ����� ���������� �������� �� X
				column_sum_r = column_sum_g = column_sum_b = 0;
				continue;
			}
		}
		change_format_column_pixels(new_pixels, pixels, num_last_el_column, index, column_sum_r, column_sum_g, column_sum_b);

		//��������� ����� ���������� �������� �� Y
		row_sum_r = row_sum_g = row_sum_b = 0;
	}
	// ���������� ���������� ��� �����
	pixels = new_pixels;
	// 
}