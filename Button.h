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
	std::string newpath;
	SDL_Texture* newtexture = nullptr;
	std::wstring get_text() {
		return text.text;
	}
	/*
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
	*/
	Button() {  };
	Button( SDL_Renderer* ren, const wchar_t* mtext, int mrazmer, SDL_Rect rect,const char* newpath = "textures/active_fon.png", const char* qpath = "textures/fon.png", const char* mfontpath = "font/OpenSans-Light.ttf") {
		path = qpath;
		if (texture != nullptr) SDL_DestroyTexture(texture);
		if (text.font != nullptr) TTF_CloseFont(text.font);
		if (text.surface != nullptr) SDL_FreeSurface(text.surface);
		if (text.texture != nullptr) SDL_DestroyTexture(text.texture);
		texture = IMG_LoadTexture(ren, qpath);
		text = { mrazmer,mtext,ren,rect };
		x = rect.x;
		y = rect.y;
		/*
		text.size = mrazmer;
		text.text = mtext;
		
		text.color = { 255,255,255 };
		text.x = x = rect.x;
		text.y = y = rect.y;
		w = rect.w;
		h = rect.h;

		
		text.size = mrazmer;
		text.path = mfontpath;
		text.font = TTF_OpenFont(text.path.c_str(), text.size);
		
		text.surface = TTF_RenderUNICODE_Solid(text.font, (Uint16*)text.text.c_str(), text.color);
		text.texture = SDL_CreateTextureFromSurface(ren, text.surface);
		if (text.texture == NULL) {
			printf("%s", SDL_GetError());
			exit(231);
		}
		*/
		
		TTF_SizeUNICODE(text.font, (Uint16*)text.text.c_str(), &text.w, &text.h);
		w = text.w;
		h = text.h;
		this->newpath = newpath;
		newtexture = IMG_LoadTexture(ren, this->newpath.c_str());
		if (newtexture == NULL) {
			printf("Error!! %s", SDL_GetError());
			exit(123);
		}
		
		int i = 5 + 10;
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
		else {
			is_active = false;
		}
		RenderTexture(ren);
		text.render(ren);
	}
	void change_coord(size_t x, size_t y) {
		this->x += x;
		this->y += y;
		text.y += y;
		text.x += x;
	}
	void settext(const wchar_t* newtext,SDL_Renderer* ren) {
		this->text.rename(newtext, ren);
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
			Sprite::operator=(other);
			/*
			TTF_CloseFont(text.font);
			text.font = other.text.font;
			SDL_FreeSurface(text.surface);
			text.surface = TTF_RenderUNICODE_Solid(text.font, (Uint16*)other.text.text.c_str(), other.text.color);
			SDL_DestroyTexture(text.texture);
			SDL_DestroyTexture(texture);
			SDL_DestroyTexture(newtexture);
			newtexture = other.texture;
			texture = other.texture;
			text.texture = other.text.texture;
			text = other.text;
			text.size = other.text.size;
			text.color = other.text.color;
			*/
			text = other.text;
			if (newtexture != nullptr) {
				SDL_DestroyTexture(newtexture);
			}
			newpath = other.newpath;
			newtexture = IMG_LoadTexture(ren, other.newpath.c_str());
		}
		return *this;
	}
	Button(const Button& other) : Sprite(other) {
		text = other.text;
		newtexture = IMG_LoadTexture(ren, other.newpath.c_str());
		newpath = other.newpath;
		/*
		text.color = { 255,255,255 };
		text.font = TTF_OpenFont(other.text.path.c_str(), text.size);
		
		text.surface = TTF_RenderUNICODE_Solid(text.font, (Uint16*)other.text.text.c_str(), other.text.color);
		text.texture = SDL_CreateTextureFromSurface(nullptr, text.surface);
		newtexture = other.texture;
		text.text = other.text.text;
		text.size = other.text.size;
		*/
	}
};