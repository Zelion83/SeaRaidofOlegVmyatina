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
	TTF_Font* font;
	SDL_Surface* surface;
	SDL_Texture* texture;
	int size;
	SDL_Color color = {255,255,255};
	int x, y, w, h;
public:
	friend class Button;
	Text() {
		text = L"";
		path = "";
		font = nullptr;
		surface = nullptr;
		texture = nullptr;
	}
	Text(const char* nyTb, int number, const wchar_t* tx, SDL_Renderer* ren, SDL_Rect rect) { 
		x = rect.x; y = rect.y; w = rect.w; h = rect.h;
		size = number;
		text = tx;
		font = TTF_OpenFont(nyTb, size);
		surface = TTF_RenderUNICODE_Solid(font, (Uint16*)text.c_str(), color);
		texture = SDL_CreateTextureFromSurface(ren, surface);
		//TTF_SizeText(font, (const char*)text.c_str(), &w, &h);
		TTF_SizeUNICODE(font, (Uint16*)text.c_str(), &w, &h);
	}
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
		font = TTF_OpenFont((const char*)other.path.c_str(), size);
		surface = TTF_RenderUNICODE_Solid(font, (Uint16*) text.c_str(), color);
		texture = SDL_CreateTextureFromSurface(nullptr, surface);
	}

	Text& operator=(const Text& other) {
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
			font = TTF_OpenFont((const char*)other.path.c_str(), size);
			surface = TTF_RenderUNICODE_Solid(font, (Uint16*)text.c_str(), color);
			texture = SDL_CreateTextureFromSurface(nullptr, surface);
		}
		return *this;
	}
};