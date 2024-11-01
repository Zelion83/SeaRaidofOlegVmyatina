#pragma once
#include"Sprite.h"
#include"Level.h"
#include"Button.h"
#include"Button_manager.h"
#include<vector>
class Menu:Level {
public:
	int page = 1;
	Sprite pikcha;
	//ButtonManager manager;
	Menu(SDL_Renderer* ren) {
		if (buttons.size() == 0) {
			std::vector<Button*> q;
			SDL_Rect rect = { 550,200,500,100 };

			q.push_back(new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, L"новая игра", 72, rect, "textures/active_fon.png"));
			rect.y += 150;
			q.push_back(new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, L"загрузить игру", 72, rect, "textures/active_fon.png"));
			rect.y += 150;
			q.push_back(new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, L"настройки", 72, rect, "textures/active_fon.png"));
			rect.y += 150;
			q.push_back(new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, L"про автора", 72, rect, "textures/active_fon.png"));
			rect.y += 150;
			q.push_back(new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, L"выход", 72, rect, "textures/active_fon.png"));
			addButtonRow(q);
			//manager.buttons[0][0]->is_active = true;
			//manager.active = true;
		}
	}
	void update( SDL_Renderer* ren) {
		for (int i = 0; i < buttons[0].size(); i++) {
			buttons[0][i]->update(ren);
		}
	}
	void manageButton(size_t type){
		Level::manageButton();
		if (type == SDL_MOUSEBUTTONDOWN && currentrow!=-1 && currentbutton != -1) {
			if (buttons[currentrow][currentbutton]->get_text() == L"новая игра") {
				current_level = TAVERN;
			}
		}
		
	}
};