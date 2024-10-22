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
	ADVENTURE,
	INVENTORY
};
enum events {
	PIRATES,
	ISLAND,
	PLAGUE,
	MAP,
	REBELLION
};
/*
std:: vector<std::string>items {
	"CAT",
	"MONKEY",
	"GREAT_CANNONS",
	"SLAVES",
	"MEGA_SABRE",
	"SUPPLY",
	"BOOK_OF_LEGENDS",
	"MEDECINE_CHEST"
};
*/
std::vector<Item*> items{
	new Item("Cat","Gain a +10 crewmorale","textures/cat1.png",10,ren),
	new Item("Monkey","Gain a +20 crewmorale","textures/cat1.png",10,ren),
	new Item("BigCannons","Gain a +15 ship power","textures/cat1.png",10,ren)
};
short current_level = MAIN_MENU; 

std::vector<std::string> names{ //= new std::vector<std::string>{
	"Oliver",
	 "Jack",
	 "Harry",
	 "Jacob",
	 "Charley",
	 "Thomas",
	 "George",
	 "Oscar",
	 "James",
	 "William" 
};
std::vector<std::string> surnames{ //= new std::vector<std::string>{
	"Williams",
	"Peters",
	"Gibson",
	"Martin",
	"Jordan",
	"Jackson",
	"Grant",
	"Davis",
	"Collins",
	"Bradley",
	"Barlow"
}; 
 int genious_random(int first,int last);

 //goooool
 class Sprite {
 protected:
	 SDL_Texture* texture = nullptr;
	 std::string path;
	 int x, y, w, h;
 public:
	 virtual void RenderTexture(SDL_Renderer* ren) {
		 SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		 SDL_Rect dst = { x,y,w,h };
		 SDL_RenderCopy(ren, texture, nullptr, &dst);
	 }
	 Sprite() {
		x = 0;
		y = 0;
		w = 25;
		h = 25;
		path = "";
	 };
	 Sprite(const char* qpath, SDL_Renderer* ren,int mx, int my, int mw, int mh) {
		 path = qpath;
		 texture = IMG_LoadTexture(ren, qpath);
		 x = mx;
		 y = my;
		 w = mw;
		 h = mh;
		 //RenderTexture(ren, texture, x, y, w, h);
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
		 texture = other.texture;
		 path = other.path;
		 x = other.x;
		 y = other.y;
		 w = other.w;
		 h = other.h;
	 }

	 Sprite& operator=(const Sprite& other) {
		 if (this != &other) {
			 SDL_DestroyTexture(texture);
			 texture = other.texture;
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