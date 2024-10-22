#pragma once
#include"Ship&Sailor.h"
//#include"Button_manager.h"
#include"Level.h"
class Inventory:Level {
protected:
	
	Button* gold,*page1,*page2,*go_back;
	Text* crewsize_max,*crewsize_cur,*sell,*tgold,*texts;
	int previous_level;
	std::vector<std::vector<Button*>> items;
public:
	int page;
	friend class Ship;
	//ButtonManager manager;
	Inventory(SDL_Renderer* ren, Ship& ship, int prev) {
		previous_level = prev;
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
		std::vector<Button*> iw;
		std::vector<Button*> ie;
		std::vector<Button*> iq;
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
		addButtonRow(w);
		if (e.size() > 0) addButtonRow(e);
		q.push_back(gold);
		q.push_back(page1);
		q.push_back(page2);
		q.push_back(go_back);
		addButtonRow(q);
		for (int i = 0; i < ship.inventory.size(); ++i) {
			int y = 590 + i * 100;
			int x = 90;
			if (i < 6) {
				iw.push_back(new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, ship.inventory[i]->convert_to_string().c_str(), 36, {x,y,500,100}, "textures/active_fon.png"));
			}
			if (i >= 6) {
				y = 590 + (i - 6) * 100;
				x = 940;
				ie.push_back(new Button("textures/fon.png", "font/OpenSans-Light.ttf", ren, ship.inventory[i]->convert_to_string().c_str(), 36, {x,y,500,100}, "textures/active_fon.png"));
			}
		}
		iq.push_back(page1);
		iq.push_back(page2);
		iq.push_back(gold);
		items.push_back(iq);
		items.push_back(iw);
		items.push_back(ie);
	}
	void update(SDL_Renderer* ren,Ship& ship) {
		if (page == 1) {
			for (int i = 0; i < buttons.size(); ++i) {

				for (int j = 0; j < buttons[i].size(); ++j) {
					buttons[i][j]->update(ren);
				}

			}
		}
		if (page == 2) {
			for (int i = 0; i < items.size(); ++i) {

				for (int j = 0; j < items[i].size(); ++j) {
					items[i][j]->update(ren);
				}

			}
			
		}
		tgold->rename(std::to_string(ship.get_gold()).c_str(), ren);
		tgold->RenderTexture(ren);
	}
	virtual void manageButton() {
		if (page == 1) { Level::manageButton(); return; }
		currentrow = -1;
		currentbutton = -1;
		for (int i = 0; i < items.size(); i++) {
			for (int j = 0; j < items[i].size(); j++) {
				if (items[i][j]->is_active) {
					currentrow = i;
					currentbutton = j;
					break;
				}
			}
			if (currentrow != -1) break;
		}

		if (currentrow == -1) return;

	}
	void manage_buttons(size_t type,Ship&ship) {
		Inventory::manageButton();
		if (type == SDL_MOUSEBUTTONDOWN && currentrow!= -1 && currentbutton!= -1) {
			if (page == 1) {
				if (buttons[currentrow][currentbutton]->get_text() == "Go back") {
					current_level = previous_level;
					return;
				}
				if (buttons[currentrow][currentbutton]->get_text() == "2") {
					page = 2;
					return;
				}
				if (buttons[currentrow][currentbutton]->get_text() == "1") {
					page = 1;
					return;
				}
				ship.gold += 5;
				buttons[currentrow].erase(buttons[currentrow].begin() + currentbutton);
				return;
			}

			if (page == 2) {
				if (items[currentrow][currentbutton]->get_text() == "2") {
					page = 2;
					return;
				}
				if (items[currentrow][currentbutton]->get_text() == "1") {
					page = 1;
					return;
				}
				ship.gold += 10;
				items[currentrow].erase(items[currentrow].begin() + currentbutton);
				return;
			}
		}
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