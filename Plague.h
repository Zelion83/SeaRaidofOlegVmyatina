#pragma once
#include"Level.h"
#include"Ship&Sailor.h"
#include<set>
class Plague :Level {
	Text text, text2;
	Button da, net;
	int pogibli;
	std::set<int> uvy;
public:
	Plague(SDL_Renderer* ren, Ship& ship) : 
	text{ 36,L"Среди команды возникла вспышка чумы. Члены экипажа заболевают один за другим.",ren,{100,676,500,100} },
	text2{ 36,L"Что вы собираетесь делать?",ren,{100,776,500,100} }, da{ ren,L"Попытаться вылечить чуму",36,{100,850,500,100} },
	net{ ren,L"Выкинуть за борт всех заболевших и ввести жёсткий карантин",36,{600,850,500,100} }
	{
		std::vector<Button> q;
		q.push_back(da);
		q.push_back(net);
		addButtonRow(q);
		pikcha = { "textures/cherepok.png",ren,1920 / 4,100,1024,576 };
		for (int i = 0; i < genious_random(1, ship.get_cursize() - 1); ++i) {
			uvy.insert(genious_random(0, ship.get_cursize() - 1));
		}
		pogibli = uvy.size();
	}
	void update() {
		for (auto& i : buttons) {
			for (auto& j : i) {
				j.update(ren);
			}
		}
		pikcha.update(ren);
		text.render(ren);
		text2.render(ren);
	}
	void manage_buttons(size_t type, Ship& ship) {
		Level::manageButton();

		if (type == SDL_MOUSEBUTTONDOWN && currentrow != -1 && currentbutton != -1) {
			if (buttons[currentrow][currentbutton].get_text() == L"Попытаться вылечить чуму") {
				int test = ship.get_cursize() * genious_random(1, 100);
				
				
				bool uspeh = (test >= 500);
				for (int i = 0; i < ship.get_cursize(); ++i) {
					
					if (ship.get_item_string(i) == L"Апетчка") {
						uspeh = true;
						return;
					}
				}
				if (uspeh) {
					pikcha.replace_texture("textures/pirat_cap.png", ren);
					text.rename(L"Успех! Экипаж пережил мор, но без жертв не обошлось.", ren);
					std::wstring ws = L"Умерло членов экипажа: " + std::to_wstring(pogibli);
					text2.rename(ws.c_str(), ren);
					buttons[0].clear();
					da.settext(L"Дальше", ren);
					buttons[0].push_back(da);
					for (auto it = uvy.begin(); it!= uvy.end(); ++it) {
						ship.delete_sailor(ship.decode_sailor((*it)));
					}
					return;
				}
				else {
					current_level = END;
					return;
				}
			}
			if (buttons[currentrow][currentbutton].get_text() == L"Дальше") {
				current_level = TAVERN;
				return;
			}
			if (buttons[currentrow][currentbutton].get_text() == L"Выкинуть за борт всех заболевших и ввести жёсткий карантин") {
				int test = pogibli * genious_random(1, 100);
				if (test <= 800) {
					current_level = END;
					return;
				}
				else {
					pikcha.replace_texture("textures/pirat_cap.png", ren);
					text.rename(L"Успех! Экипаж пережил мор, но без жертв не обошлось.", ren);
					std::wstring ws = L"Умерло членов экипажа: " + std::to_wstring(pogibli);
					text2.rename(ws.c_str(), ren);
					buttons[0].clear();
					da.settext(L"Дальше", ren);
					buttons[0].push_back(da);
					for (auto it = uvy.begin(); it != uvy.end(); ++it) {
						ship.delete_sailor(ship.decode_sailor((*it)));
					}
					return;
				}
			}
		}
	}
};