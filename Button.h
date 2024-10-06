#pragma once

#include"Text.h"
#include"Sprite.h"
//#include"Button_manager.h"
class Button : protected Sprite {
protected:
	Text text;
public:
	//friend class Button_manager;
	bool is_active = false;
	bool is_clicked = false;
	SDL_Texture* newtexture = nullptr;
	std::string get_text() {
		return text.text;
	}
	Button() {
		text.x = x = 0;
		text.y = y = 0;
		text.w = w = 25;
		text.h = h = 25;
		path = "";
		text.path = "";
		text.size = 48;
		text.color = { 255,255,255 };
	}
	Button(const char* qpath, const char* mfontpath, SDL_Renderer* ren, const char* mtext, int mrazmer, SDL_Rect rect,const char* newpath) {
		path = qpath;
		if (texture != nullptr) SDL_DestroyTexture(texture);
		if (text.font != nullptr) TTF_CloseFont(text.font);
		if (text.surface != nullptr) SDL_FreeSurface(text.surface);
		if (text.texture != nullptr) SDL_DestroyTexture(text.texture);
		texture = IMG_LoadTexture(ren, qpath);
		text.size = mrazmer;
		text.text = mtext;
		
		text.color = { 255,255,255 };
		text.x = x = rect.x;
		text.y = y = rect.y;
		w = rect.w;
		h = rect.h;
		/*
		if (text.text.size() < w) {
			text.w = (text.text.size() * 40);
		}
		*/

		newtexture = IMG_LoadTexture(ren,newpath);
		text.size = mrazmer;
		text.path = mfontpath;
		text.font = TTF_OpenFont(text.path.c_str(), text.size);
		TTF_SizeText(text.font, text.text.c_str(), &text.w, &text.h);
		w = text.w;
		h = text.h;
		text.surface = TTF_RenderUTF8_Solid(text.font, text.text.c_str(), text.color);
		text.texture = SDL_CreateTextureFromSurface(ren, text.surface);
	}
	SDL_Rect* get_coord() {
		SDL_Rect dst = { x,y,w,h };
		return &dst;
	}
	void RenderTexture(SDL_Renderer* ren) {
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_Rect dst = { x,y,w,h };
		if (is_active == false) {
			SDL_RenderCopy(ren, texture, nullptr, &dst);
		}
		else {
			SDL_RenderCopy(ren, newtexture, nullptr, &dst);
		}
	}
	bool isCursorInsideRect(SDL_Rect& dst) {
		int cursorX, cursorY;
		SDL_GetMouseState(&cursorX, &cursorY);

		if (cursorX >= dst.x && cursorX <= dst.x + dst.w &&
			cursorY >= dst.y && cursorY <= dst.y + dst.h) {
			return 1;
		}
		else {
			return 0;
		}
	}
	void update(SDL_Renderer* ren) {
		SDL_Rect dst = { x,y,w,h };
		
		if (isCursorInsideRect(dst)) {
			is_active = true;
		}
		RenderTexture(ren);
		text.RenderTexture(ren);
	}
	void change_coord(size_t x, size_t y) {
		this->x += x;
		this->y += y;
		text.y += y;
		text.x += x;
	}
	
	~Button() {
		
		
		
		if (texture != nullptr) {
			SDL_DestroyTexture(texture);
		}
		if (newtexture != nullptr) {
			SDL_DestroyTexture(newtexture);
		}
		
	}
	Button& operator=(const Button& other) {
		if (this != &other) {
			operator=(other);
			TTF_CloseFont(text.font);
			text.font = other.text.font;
			SDL_FreeSurface(text.surface);
			text.surface = TTF_RenderUTF8_Solid(text.font, other.text.text.c_str(), other.text.color);
			SDL_DestroyTexture(text.texture);
			SDL_DestroyTexture(texture);
			SDL_DestroyTexture(newtexture);
			newtexture = other.texture;
			texture = other.texture;
			text.texture = other.text.texture;
			text = other.text;
			text.size = other.text.size;
			text.color = other.text.color;
			
		}
		return *this;
	}
	Button(const Button& other) : Sprite(other) {
		text.color = { 255,255,255 };
		text.font = TTF_OpenFont(other.text.path.c_str(), text.size);
		text.surface = TTF_RenderUTF8_Solid(text.font, other.text.text.c_str(), other.text.color);
		text.texture = SDL_CreateTextureFromSurface(nullptr, text.surface);
		newtexture = other.texture;
		text.text = other.text.text;
		text.size = other.text.size;

	}
};