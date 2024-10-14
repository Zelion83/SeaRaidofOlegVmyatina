#pragma once
#include<sstream>
#include"Sprite.h"
#include"Text.h"
#include"Level.h"
#include"Button.h"
#include"Button_manager.h"
#include"Ship&Sailor.h"
class Tavern:Level {
public:
	Sprite* pikcha;
	Button* gtta,*inv;
	Button* gold;
	Text* tgold;
	Button* page1, * page2;
	std::vector<Sailor> freaks;
	std::vector<Item*> itemss;
	std::vector<Button> button_freaks;
	std::vector<std::vector<Button*>> itbuttons;
	int current_button = 0;
	int page = 1;
	Tavern(SDL_Renderer* ren, Ship& ship, int page) {
			pikcha = new Sprite("textures/zal.png", ren, 400, 50, 960, 540);
			gold = new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, "Gold: ", 36, { 1550,200,500,100 }, "textures/active_fon.png");
			gtta = new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, "go to the adventure", 36, { 1450,100,500,100 }, "textures/active_fon.png");
			inv = new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, "INVENTORY", 36, { 1450,350,500,100 }, "textures/active_fon.png");
			page1 = new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, "next", 36, { 1650,550,500,100 }, "textures/active_fon.png");
			page2 = new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, "back", 36, { 1650,600,500,100 }, "textures/active_fon.png");
			std::stringstream ss;
			ss << ship.get_gold();
			std::string s;
			ss >> s;
			tgold = new Text("font/OpenSans-Light.ttf", 48, s.c_str(), ren, { 1550,250,500,100 });
			std::vector<Button*> w;
			std::vector<Button*> e;
			std::vector<Button*> ie;
			std::vector<Button*> iw;
			std::vector<Button*> iq;
			int chislo = genious_random(2, 10);
			int chislo1 = genious_random(1, items.size()-1);
			for (int i = 0; i < chislo1; ++i) {
				Item* item = items[genious_random(0, items.size()-1)];
				itemss.push_back(item);
			}
			for (int i = 0; i < chislo + 1; i++) {
				int mname = genious_random(0, names.size() - 1);
				int msurname = genious_random(0, surnames.size() - 1);
				Sailor freak;
				freak.price = (freak.hp + freak.dmg) / 2;
				freak.name = names[mname] + " " + surnames[msurname];
				freaks.push_back(freak);
			}
			
			for (int i = 0; i < chislo + 1; i++) {
				std::string mtext = freaks[i].name + "	" + "hp: " + std::to_string(freaks[i].hp) + "	dmg: " + std::to_string(freaks[i].dmg)
					+ " price: " + std::to_string(freaks[i].price);
				int y = 590 + i * 100;
				int x = 90;
				if (i < 6) {
					w.push_back(new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, mtext.c_str(), 36, { x,y,500,100 }, "textures/active_fon.png"));
				}
				if (i >= 6) {
					y = 590 + (i - 6) * 100;
					x = 940;
					e.push_back(new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, mtext.c_str(), 36, { x,y,500,100 }, "textures/active_fon.png"));
				}


			}
			//2
			for (int i = 0; i < chislo1; ++i) {
				std::string mtext = itemss[i]->name + ":	" + itemss[i]->opisanie + " price: " + std::to_string(itemss[i]->price);
				int y = 590 + i * 100;
				int x = 90;
				if (i < 6) {
					iw.push_back(new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, mtext.c_str(), 36, { x,y,500,100 }, "textures/active_fon.png"));
				}
				if (i >= 6) {
					y = 590 + (i - 6) * 100;
					x = 940;
					ie.push_back(new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, mtext.c_str(), 36, { x,y,500,100 }, "textures/active_fon.png"));
				}
			}
			std::vector<Button*> q;
			q.push_back(gtta);
			q.push_back(inv);
			q.push_back(page1);
			//q.push_back(page2);
			iq.push_back(page2);
			addButtonRow(w);
			if (e.size() > 0)addButtonRow(e);
			addButtonRow(q);
			//buttons[0][0]->is_active = true;
			itbuttons.push_back(iw);
			itbuttons.push_back(iq);
	}
	virtual void manageButton() {
		currentrow = -1;
		currentbutton = -1;
		for (int i = 0; i < itbuttons.size(); i++) {
			for (int j = 0; j < itbuttons[i].size(); j++) {
				if (itbuttons[i][j]->is_active) {
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

		
				for (int i = 0; i < buttons.size(); i++) {

					for (int j = 0; j < buttons[i].size(); j++) {
						buttons[i][j]->update(ren);
					}

				}
		
			pikcha->update(ren);
			gold->update(ren);
			std::stringstream ss;
			ss << ship.get_gold();
			std::string s;
			ss >> s;
			tgold->rename(s.c_str(), ren);
			tgold->RenderTexture(ren);
		}
		if (page == 2) {
			Tavern::manageButton();
			/*
			std::vector<Button*> it;
			for (int i = 0; i < item_manager.buttons.size(); ++i) {
				std::stringstream ss;
				ss << items[i]->price;
				std::string s = items[i]->name + items[i]->opisanie;
				ss >> s;
				it.push_back(new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, s.c_str(), 36, { 100,100,500,100 }, "textures/active_fon.png"));
			}
			*/
			
			for (int i = 0; i < itbuttons.size(); i++) {

				for (int j = 0; j < itbuttons[i].size(); j++) {
					itbuttons[i][j]->update(ren);
				}

			}
		}
	}
	void manage_buttons(size_t type) {
		if(page == 1)Level::manageButton();
		if(page == 2)Tavern::manageButton();
		if (type == SDL_MOUSEBUTTONDOWN && currentrow != -1 && currentbutton != -1) {
			if (buttons[currentrow][currentbutton]->get_text() == "go to the adventure") {
				current_level = ADVENTURE;
			}
			if (buttons[currentrow][currentbutton]->get_text() == "next") {
				page = 2;
				return;
			}
			if (page == 2) {
				if (itbuttons[currentrow][currentbutton]->get_text() == "back") {
					page = 1;
					return;
				}
				if (ship.crew.size() < ship.crewsize) {
					ship.add_item(itbuttons[currentrow][currentbutton]->get_text());
					itbuttons[currentrow].erase(itbuttons[currentrow].begin() + currentbutton);

					for (int j = currentbutton; j < itbuttons[currentrow].size(); j++) {
						itbuttons[currentrow][j]->change_coord(0, -100);
					}
				}
			}
			if (ship.crew.size() < ship.crewsize) {
				ship.push_string(buttons[currentrow][currentbutton]->get_text());
				buttons[currentrow].erase(buttons[currentrow].begin() + currentbutton);

				for (int j = currentbutton; j < buttons[currentrow].size(); j++) {
					buttons[currentrow][j]->change_coord(0, -100);
				}
			}
		}
	}
};
