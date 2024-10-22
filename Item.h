#pragma once
#include<string>
#include"SDL_image.h"
#include"SDL.h"
class Item {
protected:
	std::string name;
	std::string opisanie;
	SDL_Texture* texture = nullptr;
	size_t price = 0;
public: 
	friend class Tavern;
	friend class Ship;
	Item(const char* name, const char* opisanie, const char* path, size_t price, SDL_Renderer* ren) {
		this->name = name;
		this->opisanie = opisanie;
		texture = IMG_LoadTexture(ren, path);
		this->price = price;
	};
	std::string get_name() {
		return name;
	}
	std::string convert_to_string() {
		std::string mtext = name +":	" +opisanie + " price: " + std::to_string(price);
		return mtext;
	}
	int five() { //вызывает исключение 
		return price;
	}
};
//ship.inventory[i]->get_name().c_str()