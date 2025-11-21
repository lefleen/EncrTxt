#include "functions.h"

// Перевод pix_vec в bytef
std::vector<Bytef> create_png::pv_to_bytef(const pix_vec& pixels) 
{
	// С uc_vec не робит, хотя и bytef и uc - unsigned char...
	std::vector<Bytef> byte_pix;

	for (size_t index_row = 0; index_row < num_rows; ++index_row)
	{	
		// Фильтр строки
		byte_pix.push_back(0x00);

		for (size_t index_column = 0; index_column < num_columns; ++index_column)
		{
			// Вставка пикселей
			byte_pix.push_back(pixels[index_column + index_row * num_columns].r);
			byte_pix.push_back(pixels[index_column + index_row * num_columns].g);
			byte_pix.push_back(pixels[index_column + index_row * num_columns].b);
		}
	}

	return byte_pix;
}

// Функция вставки контрольной суммы в чанк
void create_png::insert_crc_in_chunk(bytes& chunk)
{
	// Контрольная сумма
	uLongf crc = crc32(0, chunk.data(), chunk.size());
	bytes crc_bytes;

	// Вставка в чанк контрольной суммы и одновременное преобразование в Big Endian
	chunk.push_back(crc >> 24 & 0xFF);
	chunk.push_back(crc >> 16 & 0xFF);
	chunk.push_back(crc >> 8 & 0xFF);
	chunk.push_back(crc & 0xFF);
}

// Запись сигнатуры
void create_png::set_signature(bytes& code_file)
{
	uc_vec png_signature = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
	code_file.insert(code_file.end(), png_signature.begin(), png_signature.end());	
}

// Запись IHDR
void create_png::set_IHDR(bytes& code_file, uc_vec& IHDR)
{
	// Название и размера чанка
	uc_vec name_IHDR = {'I', 'H', 'D', 'R'};
	uc_vec size_IHDR = { 0x00, 0x00, 0x00, 0x0D };
	
	// Установка RGB, отсутствие альфа-канала
	IHDR[9] = 0x02;

	// Вставка имени, crc, размера в чанк
	IHDR.insert(IHDR.begin(), name_IHDR.begin(), name_IHDR.end());
	insert_crc_in_chunk(IHDR);
	IHDR.insert(IHDR.begin(), size_IHDR.begin(), size_IHDR.end());

	// Вставка чанка в массив чанка 
	code_file.insert(code_file.end(), IHDR.begin(), IHDR.end());
}

// Уствновка пнг
int create_png::set_IDAT(bytes& code_file, pix_vec& pixels)
{
	// Имя чанка, вектора для сжатого чанка, хранеия данных чанка
	uc_vec name_IDAT = { 'I', 'D', 'A', 'T' };
	bytes compress_data;
	uc_vec IDAT;

	// Преобразование pix_vec в bytef, размер и вектор для сжатого чанка
	bytes byte_pix = pv_to_bytef(pixels);

	// Размервы сжатого и не сжатого чанка, а также изменение емкости вектора для сжатого чанка
	uLongf compress_size = byte_pix.size();
	uLongf full_size = byte_pix.size();
	compress_data.resize(compress_size);

	// Сжатие и проверка на успешность выполнения
	int error = compress(compress_data.data(), &compress_size, byte_pix.data(), compress_size);
	if (error != Z_OK)
	{
		std::cout << "Error compressing chunk " << error << std::endl;
		return -1;
	}

	// Вставкеа размеров в IDAT и одновременное преобразование в Big Endian
	bytes size_bytes;
	size_bytes.push_back(full_size >> 24 & 0xFF);
	size_bytes.push_back(full_size >> 16 & 0xFF);
	size_bytes.push_back(full_size >> 8 & 0xFF);
	size_bytes.push_back(full_size & 0xFF);

	// Вставка имени, сжатых данных, crc
	IDAT.insert(IDAT.end(), name_IDAT.begin(), name_IDAT.end());
	IDAT.insert(IDAT.end(), compress_data.begin(), compress_data.end());
	insert_crc_in_chunk(IDAT);
	IDAT.insert(IDAT.begin(), size_bytes.begin(), size_bytes.end());

	// Вставка в массив чанка
	code_file.insert(code_file.end(), IDAT.begin(), IDAT.end());

	return 0;
}

void create_png::set_IEND(bytes& code_file)
{
	// Вектора для имени, длины и самого чанка
	uc_vec name_IEND = { 'I', 'E', 'N', 'D' };
    uc_vec size_IEND = { 0, 0, 0, 0 };
	uc_vec IEND;

	// Вставка этих переменных
	IEND.insert(IEND.end(), name_IEND.begin(), name_IEND.end());
	insert_crc_in_chunk(IEND);
	IEND.insert(IEND.begin(), size_IEND.begin(), size_IEND.end());

	code_file.insert(code_file.end(), IEND.begin(), IEND.end());
}

int create_png::set(bytes& code_file, uc_vec& IDAT, uc_vec& IHDR, uc_vec& PLTE, pix_vec& pixels)
{
	// Переменная для хранения кода ошибки
	int error = 0;

	// Установка всех чанков в code_file
	set_signature(code_file);
	set_IHDR(code_file, IHDR);
	error = set_IDAT(code_file, pixels);
	set_IEND(code_file);


	// Проверка на наличие ошибки
	if (error == -1)
	{
		return -1;
	}

	return 0;
}
