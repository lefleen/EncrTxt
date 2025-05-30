#include "functions.h"

// Является ли чанк верным
bool work_with_chunks::is_true_chunk(int index, const uc_vec& code_file, const str& name_chunk)
{
    return (index + 3 < code_file.size() &&
        code_file[index] == name_chunk[0] &&
        code_file[index + 1] == name_chunk[1] &&
        code_file[index + 2] == name_chunk[2] &&
        code_file[index + 3] == name_chunk[3]);
}

// Перенесение чанка из файла в отдельный вектор
int work_with_chunks::from_file_to_chunk(uc_vec& chunk, const uc_vec& code_file, int position_chunk_in_flle)
{
    // Полный размера чанка в формате Big Endian
    size_t size_chunk;
    // Получение длины чанка 
    size_chunk = get_length_chunk(position_chunk_in_flle, code_file);
    chunk.resize(size_chunk);
    // Пропуск длины(4 байта) и названия(4 байта)
    position_chunk_in_flle += 8;
    // Проверка границ чанка
    if (position_chunk_in_flle + size_chunk > code_file.size())
    {
        std::cout << "Invalid chunk size. Try again in next time." << std::endl << std::endl;
        return -1;
    }
    if (size_chunk == -1)
    {
        return -1;
    }
    for (int i = 0; i < size_chunk; i++)
    {
        chunk[i] = code_file[position_chunk_in_flle + i];
    }
    return 0;
}

long work_with_chunks::get_length_chunk(int chunk_offset_size, const uc_vec& code_chunk)
{
    // Длина размера (количество байт в размере)
    const int bytes_size = 4;
    // Полный размера чанка в формате Big Endian
    size_t size_chunk;
    // Сложение с изменением порядка байт в Little Endian
    for (int i = 0; i < bytes_size; i++)
    {
        size_chunk = (size_chunk << 8) | code_chunk[chunk_offset_size + i];
    }
    // Проверка чанка на пустоту
    if (code_chunk.empty() || size_chunk == 0)
    {
        std::cout << "Chunk is empty or size chunk is NULL. Try again in next time." << std::endl << std::endl;
        return -1;
    }
    return size_chunk;
}

uc_vec work_with_chunks::uncompress_chunk(const uc_vec& compress_chunk)
{
    // Предполагаемый размер декомпресованного чанка
    uLong size_uncompress_chunk = compress_chunk.size() * 1000;
    // Размер сжатого чанка
    uLong size_compress_chunk = compress_chunk.size();
    // Вектор для хранения декомпрессованного чанка
    uc_vec uncompress_chunk(size_uncompress_chunk);
    // Проверка чанка на пустоту
    if (compress_chunk.empty())
    {
        std::cout << "Chunk is empty. Try again in next time." << std::endl << std::endl;
        return uncompress_chunk;
    }
    int error = 0;
    // Распаковка чанка
    error = uncompress(uncompress_chunk.data(), &size_uncompress_chunk, compress_chunk.data(), compress_chunk.size());
    // Проверка успешности декомпрессии
    if (error != Z_OK)
    {
        std::cout << "Chunk not been uncompress. Try again in next time." << std::endl << std::endl;
        uncompress_chunk.clear();
        return uncompress_chunk;
    }
    // Изменение предполагаемого размера чанка на фактический
    uncompress_chunk.resize(size_uncompress_chunk);
    return uncompress_chunk;
}

uc_vec work_with_chunks::search_chunk(const uc_vec& code_file, const str& name_chunk)
{
    // Переменная для хранения чанка
    uc_vec chunk;
    // Позиция чанка в файла
    int position_chunk_in_file = -1;
    //Поиск чанка
    for (int index = 0; index < code_file.size(); index++)
    {
        if (code_file[index] != 'I')
        {
            continue;
        }
        //Проверка чанка 
        if (is_true_chunk(index, code_file, name_chunk) && position_chunk_in_file == -1)
        {
            // Позиция чанка в файле
            position_chunk_in_file = index - 4;
            break;
        }
    }
    // Проверка наличия чанка в файле
    if (position_chunk_in_file == -1)
    {
        std::cout << name_chunk << " wasn't be seek. Try again in next time." << std::endl << std::endl;
        return chunk;
    }
    // Перенос чанка из файла в отдельную переменную
    int error = from_file_to_chunk(chunk, code_file, position_chunk_in_file);
    if(error == -1)
    {
        chunk.clear();
    }
    return chunk;
}

int work_with_chunks::get(uc_vec& IDAT, uc_vec& IHDR, const uc_vec& code_file)
{
    uc_vec compress_IDAT = search_chunk(code_file, "IDAT");
    IHDR = search_chunk(code_file, "IHDR");
    IDAT = uncompress_chunk(compress_IDAT);
    if (compress_IDAT.empty() || IDAT.empty() || IHDR.empty())
    {
        return -1;
    }
    return 0;
}
