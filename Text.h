#pragma once
#include"Sprite.h"
#include"SDL_ttf.h"
#include"SDL.h"
#include"SDL_image.h"
#include<string>
#include"Button.h"
//класс текст : строка, шрифт, поверхность->текстура, размер, цвет, рендер, координаты, изменение этого всего, в конструкторе инициализация
class Text {
protected:
	std::string path;
	std::wstring text;
	TTF_Font* font = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;
	
public:
	friend class Button;
	int size = 25;
	SDL_Color color = { 255,255,255 };
	int x = 0, y = 0, w = 25, h = 25;
	/*
	Text() {
		text = L"";
		path = "";
		font = nullptr;
		surface = nullptr;
		texture = nullptr;
	}
	*/
	Text() {}
	
	Text(int number, const wchar_t* tx, SDL_Renderer* ren, SDL_Rect rect, const char* nyTb = "font/OpenSans-Light.ttf") {
		x = rect.x; y = rect.y; w = rect.w; h = rect.h;
		size = number;
		text = tx;
		path = nyTb;
		font = TTF_OpenFont(nyTb, size);
		TTF_SizeUNICODE(font, (Uint16*)text.c_str(), &w, &h);
		surface = TTF_RenderUNICODE_Solid(font, (Uint16*)text.c_str(), color);
		texture = SDL_CreateTextureFromSurface(ren, surface);
		
		if (surface == NULL) {
			printf("Surface == NULL \n");
			exit(22);
		}

		texture = SDL_CreateTextureFromSurface(ren, surface);
		if (texture == NULL) {
			printf("Error: %s", SDL_GetError());
			exit(3);
		}
	}
	
	/*
	Text(const char* nyTb, int number, const wchar_t* tx, SDL_Renderer* ren, SDL_Rect rect) :
		x{ rect.x }, y{ rect.y }, w{ rect.w }, h{ rect.h }, size{ number }, text{ tx }, font{TTF_OpenFont(nyTb,size)},
		surface{ TTF_RenderUNICODE_Solid(font,(Uint16*)text.c_str(),color) }, texture{SDL_CreateTextureFromSurface(ren,surface)}
	{ 
		TTF_SizeUNICODE(font,(Uint16*)text.c_str(),&w,&h); 
	}
	*/
	void rename(const wchar_t* newname, SDL_Renderer* ren) {
		text = newname;
		SDL_FreeSurface(surface);
		surface = TTF_RenderUNICODE_Solid(font, (Uint16*)text.c_str(), color);
		SDL_DestroyTexture(texture);
		texture = SDL_CreateTextureFromSurface(ren, surface);
	}
	void change_coord(SDL_Rect rect) {
		x = rect.x; y = rect.y; w = rect.w; h = rect.h;
	}
	void render(SDL_Renderer* ren){
		RenderTexture(ren);
	}
	void RenderTexture(SDL_Renderer* ren) {
		/*if (texture == NULL) {
			printf("Error!!!! %s", SDL_GetError());
			exit(221);
		}
		*/
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_Rect dst = { x,y,w,h };
		SDL_RenderCopy(ren, texture, nullptr, &dst);
	}
	~Text() {
		TTF_CloseFont(font);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}

	Text(const Text& other) {
		text = other.text;
		path = other.path;
		size = other.size;
		color = other.color;
		x = other.x;
		y = other.y;
		w = other.w;
		h = other.h;
		font = TTF_OpenFont(other.path.c_str(), size);
		surface = TTF_RenderUNICODE_Solid(font, (Uint16*) text.c_str(), color);
		texture = SDL_CreateTextureFromSurface(ren, surface);
	}

	Text& operator=(const Text& other) {
		if (&other != nullptr) {
			if (this != &other) {
				TTF_CloseFont(font);
				SDL_FreeSurface(surface);
				SDL_DestroyTexture(texture);
				text = other.text;
				path = other.path;
				size = other.size;
				color = other.color;
				x = other.x;
				y = other.y;
				w = other.w;
				h = other.h;
				font = TTF_OpenFont(path.c_str(), size);
				surface = TTF_RenderUNICODE_Solid(font, (Uint16*)text.c_str(), color);
				texture = SDL_CreateTextureFromSurface(ren, surface);

				
			}
			return *this;
		}
	}
};