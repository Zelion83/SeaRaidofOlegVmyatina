#pragma once
#include"Level.h"
#include"Ship&Sailor.h"
class Forgotten_map:Level {
	//Sprite pikcha;
	Text text,text2;
	Button da, net;
public:
	Forgotten_map(SDL_Renderer* ren):
		text{ 36,L"во время уборки в каюте вы находите необычную карту, на которой отмечен неизвестный вам остров.",ren,{100,676,500,100} },
		text2{ 36,L"Последовать этому маршруту?",ren,{100,776,500,100} }, da{ ren,L"Да",36,{100,850,500,100} },
		net{ ren,L"Нет",36,{600,850,500,100} }
	{
		std::vector<Button> q;
		pikcha = { "textures/karta1.png",ren,1920 / 4,100,1024,576 },
		q.push_back(da);
		q.push_back(net);
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
		text2.render(ren);
	}
	void manage_buttons(size_t type,Ship& ship) {
		Level::manageButton();

		if (type == SDL_MOUSEBUTTONDOWN && currentrow != -1 && currentbutton != -1) {
			if (buttons[currentrow][currentbutton].get_text() == L"Да") {
				pikcha.replace_texture("textures/island.png", ren);
				text.rename(L"Вы прибыли на остров", ren);
				text2.rename(L"", ren); 
				da.settext(L"Дальше",ren);
				buttons[0].clear();
				buttons[0].push_back(da);
				return;

			}
			if (buttons[currentrow][currentbutton].get_text() == L"Нет") {
				ship.morale -= 20;
				current_level = TAVERN;
				return;
			}
			if (buttons[currentrow][currentbutton].get_text() == L"Дальше") {
				int test = 1;// genious_random(1, 2);
				if (test == 1) {
					pikcha.replace_texture("textures/negros.png", ren);
					text.rename(L"На пути в глубь острова вам повстречалась группа негров-аборигенов. Они настроены агрессивно.", ren);
					text2.rename(L"Что вы собираетесь делать?", ren);
					buttons[0].clear();
					da.settext(L"Сразиться с ними.",ren);
					net.settext(L"Попытаться задобрить провиантом.", ren);
					buttons[0].clear();
					buttons[0].push_back(da);
					buttons[0].push_back(net);
					return;
				}
			}
			
			if (buttons[currentrow][currentbutton].get_text() == L"Сразиться с ними.") {
				int test = genious_random(100, 1500);
				if (ship.power >= test) {
					pikcha.replace_texture("textures/mogila.png",ren);
					text.rename(L"пройдя дальше вглубь острова, вы видите перед собой могилу.", ren);
					text2.rename(L"Отметка на карте указывает прямо на неё.",ren);
					da.settext(L"Копать", ren);
					net.settext(L"Уйти с острова", ren);
					buttons[0].clear();
					buttons[0].push_back(da);
					buttons[0].push_back(net);
					return;
				}
				else {
					current_level = END;
					return;
				}
			}
			if (buttons[currentrow][currentbutton].get_text() == L"Попытаться задобрить провиантом.") {
				int test = genious_random(100, 200);
				if (ship.proviant >= test) {
					pikcha.replace_texture("textures/mogila.png", ren);
					text.rename(L"пройдя дальше вглубь острова, вы видите перед собой могилу.", ren);
					text2.rename(L"Отметка на карте указывает прямо на неё.", ren);
					da.settext(L"Копать", ren);
					net.settext(L"Уйти с острова", ren);
					buttons[0].clear();
					buttons[0].push_back(da);
					buttons[0].push_back(net);
					return;
				}
				else {
					current_level = END;
					return;
				}
			}
			if (buttons[currentrow][currentbutton].get_text() == L"Копать") {
				pikcha.replace_texture("textures/klad.png", ren);
				text.rename(L"Помимо человеческих останков, вы откопали сундук, полный сокровищ!", ren);
				text2.rename(L"Предметы из сундука и золото были добавлены в ваш инвентарь.", ren);
				ship.change_gold(ship.get_gold() + genious_random(1, 400));
				buttons[0].clear();
				da.settext(L"Уйти с острова",ren);
				buttons[0].push_back(da);
				ship.morale -= genious_random(1, 10);
				ship.add_item(genious_random(0, items.size()-1));
				return;
			}
			if (buttons[currentrow][currentbutton].get_text() == L"Уйти с острова") {
				current_level = TAVERN;
				return;
			}
			
		}
	}
};