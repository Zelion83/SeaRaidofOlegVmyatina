#pragma once
#include<sstream>
#include"Sprite.h"
#include"Text.h"
#include"Level.h"
#include"Button.h"
#include"Button_manager.h"
#include"Ship&Sailor.h"
Ship ship(10, 1000);
class Tavern:Level {
public: 
	Sprite pikcha;
	Button gtta,inv;
	Button gold;
	Text tgold,texts;
	Button page1,  page2;
	std::vector<Sailor> freaks;
	std::vector<Item> itemss;
	std::vector<Button> button_freaks;
	std::vector<std::vector<Button>> itbuttons;
	int current_button = 0;
	int page = 1;
	Tavern(SDL_Renderer* ren, Ship& ship, int page) {
			pikcha = Sprite("textures/zal.png", ren, 400, 50, 960, 540);
			gold = Button(ren, L"Золото: ", 36, { 1550,200,500,100 }, "textures/active_fon.png");
			texts = Text( 36, L"Золото:", ren, { 1550,200,500,100 });
			gtta = Button(ren, L"в приключение", 36, { 1450,100,500,100 }, "textures/active_fon.png");
			inv = Button(ren, L"ИНВЕНТАРЬ", 36, { 1450,350,500,100 }, "textures/active_fon.png");
			page1 = Button(ren, L"далее", 36, { 1650,550,500,100 }, "textures/active_fon.png");
			page2 =  Button(ren, L"назад", 36, { 1650,600,500,100 }, "textures/active_fon.png");
			std::wstringstream ss;
			ss << ship.get_gold();
			std::wstring s;
			ss >> s;
			tgold =  Text(48, (const wchar_t*)s.c_str(), ren, { 1550,250,500,100 });
			std::vector<Button> w;
			std::vector<Button> e;
			std::vector<Button> ie;
			std::vector<Button> iw;
			std::vector<Button> iq;
			int chislo = genious_random(2, 10);
			int chislo1 = genious_random(1, items.size()-1);
			for (int i = 0; i < chislo1; ++i) {
				Item item = items[genious_random(0, items.size()-1)];
				itemss.push_back(item);
			}
			for (int i = 0; i < 3;/*chislo + 1;*/ i++) {
				int mname = genious_random(0, names.size() - 1);
				int msurname = genious_random(0, surnames.size() - 1);
				Sailor freak;
				//freak.price = (freak.hp + freak.dmg) / 2;
				freak.cprice((freak.ghp() + freak.gdmg()) / 2);
				freak.name = names[mname] + L" " + surnames[msurname];
				freaks.push_back(freak);
			}
			
			for (int i = 0; i < 3; i++) {
				std::wstring mtext = freaks[i].name + L"	" + L"ОЗ: " + std::to_wstring(freaks[i].ghp()) + L"	ОД: " + std::to_wstring(freaks[i].gdmg())
					+ L" цена: " + std::to_wstring(freaks[i].gprice());
				int y = 590 + i * 100;
				int x = 90;
				if (i < 6) {
					w.push_back( Button(ren, mtext.c_str(), 36, { x,y,500,100 }, "textures/active_fon.png"));
				}
				if (i >= 6) {
					y = 590 + (i - 6) * 100;
					x = 940;
					e.push_back( Button(ren, mtext.c_str(), 36, { x,y,500,100 }, "textures/active_fon.png"));
				}


			}
			//2
			for (int i = 0; i < chislo1; ++i) {
				std::wstring mtext = itemss[i] .name + L":	" + itemss[i] .opisanie + L" цена: " + std::to_wstring(itemss[i] .price);
				int y = 590 + i * 100;
				int x = 90;
				if (i < 6) {
					iw.push_back( Button(ren, mtext.c_str(), 36, { x,y,500,100 }, "textures/active_fon.png"));
				}
				if (i >= 6) {
					y = 590 + (i - 6) * 100;
					x = 940;
					ie.push_back( Button(ren, mtext.c_str(), 36, { x,y,500,100 }, "textures/active_fon.png"));
				}
			}
			std::vector<Button> q;

			q.push_back(gtta);
			q.push_back(inv);
			q.push_back(page1);

			iq.push_back(page2);
			addButtonRow(w);
			if (e.size() > 0)addButtonRow(e);
			addButtonRow(q);
			itbuttons.push_back(iw);
			itbuttons.push_back(ie);
			itbuttons.push_back(iq);
			/*
			for (int i = 0; i < iw.size();++i) {
				delete iw[i];
			}
			for (int i = 0; i < ie.size(); ++i) {
				delete ie[i];
			}
			for (int i = 0; i < iq.size(); ++i) {
				delete iq[i];
			}
			for (int i = 0; i < q.size(); ++i) {
				delete q[i];
			}
			for (int i = 0; i < w.size(); ++i) {
				delete w[i];
			}
			for (int i = 0; i < e.size(); ++i) {
				delete e[i];
			}
			*/
	}
	virtual void manageButton() {
		currentrow = -1;
		currentbutton = -1;
		for (int i = 0; i < itbuttons.size(); i++) {
			for (int j = 0; j < itbuttons[i].size(); j++) {
				if (itbuttons[i][j].is_active) {
					currentrow = i;
					currentbutton = j;
					break;
				}
			}
			if (currentrow != -1) break;
		}

		if (currentrow == -1) return;

	}
	void tavern_update(SDL_Renderer* ren, Ship& ship) {

		if (page == 1) {
			Level::manageButton();
		
				for (int i = 0; i < buttons.size(); i++) {

					for (int j = 0; j < buttons[i].size(); j++) {
						buttons[i][j].update(ren);
					}

				}
		
			pikcha.update(ren);
			gold.update(ren);
			tgold.rename(std::to_wstring(ship.get_gold()).c_str(), ren);
			tgold.RenderTexture(ren);;
		}
		if (page == 2) {
			Tavern::manageButton();
			texts .render(ren);
			for (int i = 0; i < itbuttons.size(); i++) {

				for (int j = 0; j < itbuttons[i].size(); j++) {
					itbuttons[i][j] .update(ren);
				}

			}
			tgold .rename(std::to_wstring(ship.get_gold()).c_str(), ren);
			tgold .RenderTexture(ren);
		}
	}
	void manage_buttons(size_t type) {
		if(page == 1)Level::manageButton(); 
		if(page == 2)Tavern::manageButton();
		if (type == SDL_MOUSEBUTTONDOWN && currentrow != -1 && currentbutton != -1) {
			if (page == 1) {
				if (buttons[currentrow][currentbutton] .get_text() == L"в приключение") { 
					current_level = ADVENTURE;
					return;
				}
				if (buttons[currentrow][currentbutton] .get_text() == L"далее") {
					page = 2;
					return;
				}
				if (buttons[currentrow][currentbutton] .get_text() == L"ИНВЕНТАРЬ") {
					current_level = INVENTORY;
					return;
				}
				if (ship.crew.size() < ship.crewsize) {
					ship.push_string(buttons[currentrow][currentbutton] .get_text());
					buttons[currentrow].erase(buttons[currentrow].begin() + currentbutton);

					for (int j = currentbutton; j < buttons[currentrow].size(); j++) {
						buttons[currentrow][j] .change_coord(0, -100);
					}
				}
			}
			if (page == 2) {
				
				if (itbuttons[currentrow][currentbutton] .get_text() == L"назад") {
					page = 1;
					currentrow = -1;
					currentbutton = -1; 
					return;
				}
				if (ship.inventory.size() < 10) {
					ship.add_item(itbuttons[currentrow][currentbutton] .get_text());
					itbuttons[currentrow].erase(itbuttons[currentrow].begin() + currentbutton);
					

					for (int j = currentbutton; j < itbuttons[currentrow].size(); j++) {
						itbuttons[currentrow][j] .change_coord(0, -100);
					}
				}
			}
			
		}
	}
	/*
	~Tavern() {
		for (auto& i : buttons) {
			for (auto j : i) {
				delete j;
				j = nullptr;
			}
		}
		for (auto& i : itbuttons) {
			for (auto j : i) {
				delete j;
				j = nullptr;
			}
		}
		delete pikcha, gtta, inv, gold, tgold, texts, page1, page2;
	}
	*/
};
