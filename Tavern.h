#pragma once
#include<sstream>
#include"Sprite.h"
#include"Text.h"
#include"Button.h"
#include"Button_manager.h"
#include"Ship&Sailor.h"
class Tavern {
public:
	Sprite* pikcha;
	Button* gtta,*inv;
	Button* gold;
	Text* tgold;
	Button* page1, * page2;
	ButtonManager manager;
	ButtonManager item_manager;
	std::vector<Sailor> freaks;
	std::vector<Item*> itemss;
	std::vector<Button> button_freaks;
	int current_button = 0;
	int page = 1;
	Tavern(SDL_Renderer* ren, Ship& ship, int page) {
		manager.add_parent(this);
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
			int chislo1 = genious_random(0, items.size());
			for (int i = 0; i < chislo1; ++i) {
				Item* item = items[genious_random(0, items.size())];
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
			manager.addButtonRow(w);
			if (e.size() > 0)manager.addButtonRow(e);
			manager.addButtonRow(q);
			manager.buttons[0][0]->is_active = true;
			item_manager.buttons.push_back(iw);
			item_manager.buttons.push_back(iq);
	}
	void tavern_update(SDL_Renderer* ren, Ship& ship) {

		if (page == 1) {


			for (int i = 0; i < manager.buttons.size(); i++) {

				for (int j = 0; j < manager.buttons[i].size(); j++) {
					manager.buttons[i][j]->update(ren);
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
			for (int i = 0; i < item_manager.buttons.size(); i++) {

				for (int j = 0; j < item_manager.buttons[i].size(); j++) {
					item_manager.buttons[i][j]->update(ren);
				}

			}
		}
	}
	
};
