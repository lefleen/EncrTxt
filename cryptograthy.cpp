#include "functions.h"
#include "classes.h"

void cryptograthy::show_plain_text(const str& plain_text)
{
	std::cout << "Plain text: " << plain_text << std::endl << std::endl;;
}

void cryptograthy::show_key(const uc_vec& key)
{
	std::cout << "key: ";
	for (int i = 0; i < key.size(); i++)
	{
		if (key[i] == '|')
		{
			continue;
		}
		std::cout << (int)key[i] << " ";
	}
	std::cout << std::endl << std::endl;
}

int cryptograthy::encryption_text(const str& plain_text, const pix_vec& pixels, uc_vec& key)
{
	if (pixels.size() < plain_text.length())
	{
		std::cout << "Not enough pixels for encryption information. Try again in next time." << std::endl << std::endl;
		return -1;
	}
	for (int i = 0; i < plain_text.length(); i++)
	{

		// Сумма пикселей
		int pix_sum = pixels[i].r + pixels[i].g + pixels[i].b;
		// Код символа исходного текста вычитаем из суммы трёх байт пикселя
		if (pix_sum < plain_text[i])
		{
			pix_sum += 1000;
		}
		key.push_back(pix_sum - plain_text[i]);
		key.push_back('|');

	}
	// Удаление символа '|' в конце
	key.pop_back();
	// Просмотр ключа
	show_key(key);
	return 0;
}

int cryptograthy::decryption_text(const str& text, const pix_vec& pixels, str& plain_text)
{
	uc_vec key;
	// Проверка на количество символов, оно должно быть больше или равно количеству пикселей
	if (pixels.size() < plain_text.length())
	{
		std::cout << "Not enough pixels for decryption information. Try again in next time." << std::endl << std::endl;
		return -1;
	}
	for (int i = 0; i < text.length(); i++)
	{
		// Часть ключа (один символ, чтение до знака разделителя - '|')
		str part_key = "";
		while (text[i] != '|' && i < text.length())
		{
			part_key += text[i];
			i++;
		}
		// stoi - str to int . Преобразование строки в число
		key.push_back(std::stoi(part_key));
	}
	for (int i = 0; i < key.size(); i++)
	{
		if (key[i] > 1000)
		{
			key[i] -= 1000;
		}
		const int pix_sum = pixels[i].r + pixels[i].g + pixels[i].b;
		plain_text += pix_sum - key[i];
	}
	// Просмотр расшифрованного текста
	show_plain_text(plain_text);
	return 0;
}
