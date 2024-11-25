#pragma once
#include"Level.h"
class Fight:Level {
protected:
	Sprite* pikcha;
	int stage;
	int otkup;
	int slozhnost;
	Text* text;
public:
	Fight(SDL_Renderer* ren) {
		std::vector<Button*> q;
		text = new Text(36, L"К вам приближается корабль с чёрным флагом. До вас доносится крик с требованием откупа.", ren, { 100,576,500,100 });
		pikcha = new Sprite("textures/cherepok.png", ren, 300, 0, 1024, 576);
		SDL_Rect rect = { 100,676,500,100 };
		otkup = genious_random(100, 1000);
		slozhnost = genious_random(1, 10);
		std::wstring s = L"•откупиться: " + std::to_wstring(otkup) + L"g";
		q.push_back(new Button(ren, s.c_str(), 48, rect, "textures/active_fon.png"));
		rect.x += 1000;
		q.push_back(new Button(ren, L"•сражаться!", 48, rect, "textures/active_fon.png"));
		//rect.y += 100;
		addButtonRow(q);
	}
	void update() {
		for (auto& i : buttons) {
			for (auto j : i) {
				j->update(ren);
			}
		}
		pikcha->update(ren);
		text->render(ren);
	}
	void manageButton(size_t type,Ship& ship) {
		Level::manageButton();
		if (type == SDL_MOUSEBUTTONDOWN && currentrow != -1 && currentbutton != -1) {
			if (buttons[currentrow][currentbutton]->get_text().find(L"•откупиться: ") != std::string::npos && ship.get_gold() >= otkup) {
				ship.change_gold(ship.get_gold() - otkup);
				current_level = TAVERN;
			}

			if (buttons[currentrow][currentbutton]->get_text().find(L"•сражаться!") != std::string::npos && ship.power >= slozhnost) {
				current_level = TAVERN;
			}
			else if(buttons[currentrow][currentbutton]->get_text().find(L"•сражаться!") != std::string::npos && ship.power < slozhnost) {
				current_level = END;
			}
		}
	}
	~Fight() {
		for (auto& i : buttons) {
			for (auto j : i) {
				delete j;
				j = nullptr;
			}
		}
		delete pikcha;
		delete text;
	}
};