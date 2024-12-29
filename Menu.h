#pragma once
#include"Sprite.h"
#include"Level.h"
#include"Button.h"
#include"Button_manager.h"
#include<vector>
class Menu:Level {
public: 
	int page = 1;

	std::vector<std::vector<Button*>> alt;
	Menu(SDL_Renderer* ren) {
		if (buttons.size() == 0) {
			std::vector<Button> q;
			SDL_Rect rect = { 1280,200,500,100 };
			pikcha = { "textures/korablik_menu.png", ren, 0, 200, (int)(1280 * 0.9), (int)(720 * 0.9) }; //А ЭТО ТОГДА ПОЧЕМУ РАБОТАЕТ?????????
			q.push_back(  Button(ren, L"новая игра", 48, rect, "textures/active_fon.png"));
			rect.y += 150;
			q.push_back(Button( ren, L"загрузить игру", 48, rect, "textures/active_fon.png"));
			rect.y += 150;
			q.push_back( Button( ren, L"настройки", 48, rect, "textures/active_fon.png"));
			rect.y += 150;
			q.push_back( Button( ren, L"про автора", 48, rect, "textures/active_fon.png"));
			rect.y += 150;
			q.push_back( Button( ren, L"выход", 48, rect, "textures/active_fon.png"));
			//q.push_back(button);
			
			addButtonRow(q);
			//alt.push_back(q);
		}
		//button = Button(ren, L"Тест", 72, { 1000,900,500,100 }, "textures/active_fon.png");
		
	}
	void update( SDL_Renderer* ren) {
		pikcha.update(ren);
		
		for (int i = 0; i < buttons[0].size(); i++) {
			
				buttons[0][i].update(ren);
			
		}
		
		
	}
	void manageButton(size_t type){
		Level::manageButton();
		if (type == SDL_MOUSEBUTTONDOWN && currentrow!=-1 && currentbutton != -1) {
			if (buttons[currentrow][currentbutton].get_text() == L"новая игра") {
				current_level = TAVERN;
			}
		}
		
	}
	
};