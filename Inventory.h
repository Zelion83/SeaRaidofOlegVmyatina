#pragma once
#include"Ship&Sailor.h"
#include"Button_manager.h"
class Inventory {
protected:
	
	Button* gold,*page1,*page2,*go_back;
	Text* crewsize_max,*crewsize_cur,*sell,*tgold;
	int previous_level;
public:
	int page;
	friend class Ship;
	ButtonManager manager;
	Inventory(SDL_Renderer* ren, Ship& ship) {
		gold = new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, "Gold: ", 36, { 1550,200,500,100 }, "textures/active_fon.png");
		page1 = new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, "1", 72, { 980,940,500,100 }, "textures/active_fon.png");
		page2 = new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, "2", 72, { 1080,940,500,100 }, "textures/active_fon.png");
		go_back = new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, "Go back", 72, { 1280,740,500,100 }, "textures/active_fon.png");
		std::string crewtext = "crewsize:	/";
		std::stringstream ss2;
		ss2 << ship.crewsize;
		std::string s2;
		ss2 >> s2;
		crewtext += s2;
		std::stringstream ss1;
		ss1 << ship.crew.size();
		std::string s1;
		ss1 >> s1;
		crewsize_max = new Text("textures/fon.png", 48, crewtext.c_str(), ren, { 100,900,500,100 });
		crewsize_cur = new Text("textures/fon.png", 48, s1.c_str(), ren, { 110,900,500,100 });

		std::stringstream ss;
		ss << ship.get_gold();
		std::string s;
		ss >> s;
		tgold = new Text("font/OpenSans-Light.ttf", 48, s.c_str(), ren, { 1550,250,500,100 });
		page = 1;
		std::vector<Button*> w;
		std::vector<Button*> e;
		std::vector<Button*> q;
		for (int i = 0; i < ship.crew.size(); i++) {
			std::string mtext = ship.crew[i].name + "	" + "hp: " + std::to_string(ship.crew[i].hp) + "	dmg: " + std::to_string(ship.crew[i].dmg)
				+ " price: " + std::to_string(ship.crew[i].price);
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
		manager.addButtonRow(w);
		if (e.size() > 0) manager.addButtonRow(e);
		q.push_back(gold);
		q.push_back(page1);
		q.push_back(page2);
		q.push_back(go_back);
		manager.addButtonRow(q);
		manager.buttons[0][0]->is_active = true;
	}
	void update(SDL_Renderer* ren,Ship& ship) {
		for (int i = 0; i < manager.buttons.size(); i++) {

			for (int j = 0; j < manager.buttons[i].size(); j++) {
				manager.buttons[i][j]->update(ren);
			}

		}
		tgold->RenderTexture(ren);
	}
};
/*
Tavern(SDL_Renderer* ren, Ship& ship) {
		pikcha = new Sprite("textures/zal.png", ren, 400, 50, 960, 540);
		gold = new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, "Gold: ", 36, { 1550,200,500,100 }, "textures/active_fon.png");
		gtta = new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, "go to the adventure", 36, { 1450,100,500,100 }, "textures/active_fon.png");
		inv = new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, "INVENTORY", 36, { 1450,350,500,100 }, "textures/active_fon.png");
		std::stringstream ss;
		ss << ship.get_gold();
		std::string s;
		ss >> s;
		tgold = new Text("font/OpenSans-Light.ttf", 48, s.c_str(), ren, {1550,250,500,100});
		std::vector<Button*> w;
		std::vector<Button*> e;
		int chislo = 10;// genious_random(2, 10);
		for (int i = 0; i < chislo+1; i++) {
			int mname = genious_random(0, names.size() - 1);
			int msurname = genious_random(0, surnames.size() - 1);
			Sailor freak;
			freak.price = (freak.hp + freak.dmg) / 2;
			freak.name = names[mname] + " " + surnames[msurname];

			freaks.push_back(freak);
		}

		//for (int i = 0; i < chislo; i++) {
		//	Button button;

		//	button_freaks.push_back(button);
		//}
		for (int i = 0; i < chislo+1; i++) {
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
		std::vector<Button*> q;
		q.push_back(gtta);
		q.push_back(inv);
		manager.addButtonRow(w);
		if(e.size() > 0)manager.addButtonRow(e);
		manager.addButtonRow(q);
		manager.buttons[0][0]->is_active = true;

	}
*/