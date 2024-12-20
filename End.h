#pragma once
#include"Level.h"
class End :Level {
protected:
	Sprite pikcha;
	Text text;
public:
	End(SDL_Renderer* ren) {
		std::vector<Button> q;
		text =  Text(36, L"Морская пучина поглотила ваш корабль. Игра окончена.", ren, { 100,576,500,100 });
		pikcha =  Sprite("textures/cherepok2.png", ren, 300, 0, 1024, 576);
		SDL_Rect rect = { 100,676,500,100 };
		q.push_back( Button(ren, L"•В меню", 48, rect, "textures/active_fon.png"));
		addButtonRow(q);
	}
	void update() {
		for (auto& i : buttons) {
			for (auto& j : i) {
				j.update(ren);
			}
		}
		pikcha.update(ren);
		text.render(ren);
	}
	void manageButton(size_t type) {
		Level::manageButton();
		if (type == SDL_MOUSEBUTTONDOWN && currentrow != -1 && currentbutton != -1) {
			if (buttons[currentrow][currentbutton].get_text() == L"•В меню" ) {
				current_level = MAIN_MENU;
				
			}
		}
	}
	
};