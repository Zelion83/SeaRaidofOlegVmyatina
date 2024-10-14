#pragma once
#include<string>
#include"SDL_image.h"
#include"SDL.h"
class Item {
protected:
	std::string name;
	std::string opisanie;
	SDL_Texture* texture = nullptr;
	size_t price;
public:
	friend class Tavern;
	Item(const char* name, const char* opisanie, const char* path, size_t price, SDL_Renderer* ren) {
		this->name = name;
		this->opisanie = opisanie;
		texture = IMG_LoadTexture(ren, path);
		this->price = price;
	};
	std::string get_name() {
		return name;
	}
};