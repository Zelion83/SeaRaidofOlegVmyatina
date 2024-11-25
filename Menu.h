#pragma once
#include"Sprite.h"
#include"Level.h"
#include"Button.h"
#include"Button_manager.h"
#include<vector>
class Menu:Level {
public:
	int page = 1;
	Sprite* pikcha;
	//ButtonManager manager;
	Menu(SDL_Renderer* ren) {
		if (buttons.size() == 0) {
			std::vector<Button*> q;
			SDL_Rect rect = { 1280,200,500,100 };
			pikcha = new Sprite("textures/korablik_menu.png", ren, 0, 200, 1280*0.9, 720*0.9);
			q.push_back(new Button( ren, L"новая игра", 72, rect, "textures/active_fon.png"));
			rect.y += 150;
			q.push_back(new Button( ren, L"загрузить игру", 72, rect, "textures/active_fon.png"));
			rect.y += 150;
			q.push_back(new Button( ren, L"настройки", 72, rect, "textures/active_fon.png"));
			rect.y += 150;
			q.push_back(new Button( ren, L"про автора", 72, rect, "textures/active_fon.png"));
			rect.y += 150;
			q.push_back(new Button( ren, L"выход", 72, rect, "textures/active_fon.png"));
			addButtonRow(q);
		}
		
	}
	void update( SDL_Renderer* ren) {
		pikcha->update(ren);
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

	~Menu() {
		
		for (auto& i : buttons) {
			for (auto j : i) {
				delete j;
				j = nullptr;
			}
		}
		
		delete pikcha;
	}
};