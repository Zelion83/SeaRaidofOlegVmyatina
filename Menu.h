#pragma once
#include"Sprite.h"
#include"Button.h"
#include"Button_manager.h"
#include<vector>
class Menu {
public:
	int page = 1;
	Sprite pikcha;
	ButtonManager manager;
	Menu(SDL_Renderer* ren) {
		if (manager.buttons.size() == 0) {
			std::vector<Button*> q;
			SDL_Rect rect = { 550,200,500,100 };

			q.push_back(new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, "new game", 72, rect, "textures/active_fon.png"));
			rect.y += 150;
			q.push_back(new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, "load game", 72, rect, "textures/active_fon.png"));
			rect.y += 150;
			q.push_back(new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, "settings", 72, rect, "textures/active_fon.png"));
			rect.y += 150;
			q.push_back(new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, "about author", 72, rect, "textures/active_fon.png"));
			rect.y += 150;
			q.push_back(new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, "exit", 72, rect, "textures/active_fon.png"));
			manager.addButtonRow(q);
			manager.buttons[0][0]->is_active = true;
			manager.active = true;
		}
	}
	void update( SDL_Renderer* ren) {
		for (int i = 0; i < manager.buttons[0].size(); i++) {
			manager.buttons[0][i]->update(ren);
		}
	}
};