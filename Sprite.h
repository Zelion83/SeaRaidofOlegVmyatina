#pragma once
#include"SDL.h"
#include"SDL_image.h"
#include"SDL_ttf.h"
#include"Item.h"
#include<string>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<random>
SDL_Renderer* ren = NULL;
enum levels {
	MAIN_MENU,
	SETTINGS,
	TAVERN,
	INVENTORY,
	END,
	CHILL,
	ADVENTURE,
	REBELLION,
	PLAGUE,
	MAP
};
/*
enum events {
	PIRATES,
	ISLAND,
	PLAGUE,
	MAP,
	REBELLION, //делаю первым
	CHILL
};
*/
/*
std:: vector<std::string>items {
	"CAT",
	"MONKEY",
	"GREAT_CANNONS",
	"SLAVES",
	"MEGA_SABRE",
	"SUPPLY",
	"BOOK_OF_LEGENDS",
	"MEDICINE_CHEST"
};
*/
std::vector<Item> items{
	 Item(L"Кот",L"+10 к боевому духу","textures/cat1.png",10,ren),
	 Item(L"Обезьяна",L"+20 к боевому духу","textures/cat1.png",10,ren),
	 Item(L"Пушки",L"+15 к мощи корабля","textures/cat1.png",10,ren),
	 Item(L"Апетчка",L"повышает шансы выжить в мор", "textures/cat1.png",10,ren),
	 Item(L"Капитанский мундир",L"Вы неотразимы. +10 к боевому духу","textures/cat1.png",10,ren)
};
short current_level = MAIN_MENU; 

std::vector<std::wstring> names{
	 L"Оливер",
	 L"Джек",
	 L"Гарри",
	 L"Иаков",
	 L"Чарли",
	 L"Томас",
	 L"Георг",
	 L"Оскар",
	 L"Джеймс",
	 L"Вильям" 
};
std::vector<std::wstring> surnames{
	L"Вильямс",
	L"Питерс",
	L"Гибсон",
	L"Мартин",
	L"Джордан",
	L"Джексон",
	L"Грант",
	L"Дэвис",
	L"Коллинс",
	L"Брэдли",
	L"Барлоу"
}; 
 int genious_random(int first,int last);
 class Sprite {
 protected:
	 SDL_Texture* texture = nullptr;
 public:
	 std::string path;
	 int x = 0, y = 0, w = 25, h = 25;
	 virtual void RenderTexture(SDL_Renderer* ren) {
		 SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		 SDL_Rect dst = { x,y,w,h };
		 SDL_RenderCopy(ren, texture, nullptr, &dst);
	 }
	 /*
	Sprite() {
		x = 0;
		y = 0;
		w = 25;
		h = 25;
		path = "";
	 };
	 */
	 Sprite() {}
	 /*
	 Sprite(const char* qpath, SDL_Renderer* ren,int mx, int my, int mw, int mh) {
		 path = qpath;
		 texture = IMG_LoadTexture(ren, qpath);
		 x = mx;
		 y = my;
		 w = mw;
		 h = mh;
	 }
	 */
	 Sprite(const char* qpath, SDL_Renderer* ren, int mx, int my, int mw, int mh):
		 path(qpath), x{mx},y{my},w{mw},h{mh}
	 {
		 texture = IMG_LoadTexture(ren, qpath);
	 }
	 virtual void update(SDL_Renderer* ren) {
		 RenderTexture(ren);
	 }
	 virtual void replace_texture(const char* newpath, SDL_Renderer* ren) {
		 if (path.c_str() != newpath) {
			 SDL_DestroyTexture(texture);
			 path = newpath;
			 texture = IMG_LoadTexture(ren, path.c_str());
		 }
	 }
	 Sprite(const Sprite& other) {
		 //texture = other.texture;
		 texture = IMG_LoadTexture(ren, other.path.c_str());
		 path = other.path;
		 x = other.x;
		 y = other.y;
		 w = other.w;
		 h = other.h;
	 }

	 Sprite& operator=(const Sprite& other) {
		 if (this != &other) {
			 SDL_DestroyTexture(texture);
			 texture = IMG_LoadTexture(ren, other.path.c_str());
			 //texture = other.texture;
			 path = other.path;
			 x = other.x;
			 y = other.y;
			 w = other.w;
			 h = other.h;
		 }
		 return *this;
	 }

	 ~Sprite() {
		 if (texture != nullptr) {
			 SDL_DestroyTexture(texture);
		 }
	 }
};

 
 


int genious_random(int first, int last) {
	
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(first, last);
	int random_number = dist(mt);
	return random_number;
}