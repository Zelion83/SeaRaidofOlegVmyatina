#pragma once
#include<string>
#include"SDL_image.h"
#include"SDL.h"
class Item {
protected:
	std::wstring name;
	std::wstring opisanie;
	SDL_Texture* texture = nullptr;
	size_t price = 0;
public: 
	friend class Tavern;
	friend class Ship;
	Item(const wchar_t* name, const wchar_t* opisanie, const char* path, size_t price, SDL_Renderer* ren) {
		this->name = name;
		this->opisanie = opisanie;
		texture = IMG_LoadTexture(ren, path);
		this->price = price;
	};
	std::wstring get_name() {
		return name;
	}
	std::wstring convert_to_string() {
		std::wstring mtext = name +L":	" +opisanie + L" price: " + std::to_wstring(price);
		return mtext;
	}
};