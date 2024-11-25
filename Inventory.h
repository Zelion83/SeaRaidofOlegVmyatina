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
		gold = new Button(ren, L"золото: ", 36, { 1550,200,500,100 }, "textures/active_fon.png");
		page1 = new Button( ren, L"1", 72, { 980,940,500,100 }, "textures/active_fon.png");
		page2 = new Button(ren, L"2", 72, { 1080,940,500,100 }, "textures/active_fon.png");
		
		go_back = new Button(ren, L"назад:", 72, { 1280,740,500,100 }, "textures/active_fon.png");
		std::wstring crewtext = L"размер экипажа:	/";
		std::wstringstream ss2;
		ss2 << ship.crewsize;
		std::wstring s2;
		ss2 >> s2;
		crewtext += s2;
		std::wstringstream ss1;
		ss1 << ship.crew.size();
		std::wstring s1;
		ss1 >> s1;
		crewsize_max = new Text(48, crewtext.c_str(), ren, { 100,900,500,100 });
		crewsize_cur = new Text(48, s1.c_str(), ren, { 110,900,500,100 });

		std::wstringstream ss;
		ss << ship.get_gold();
		std::wstring s;
		ss >> s;
		tgold = new Text(48, s.c_str(), ren, { 1550,250,500,100 });
		page = 1;
		std::vector<Button*> w;
		std::vector<Button*> e;
		std::vector<Button*> q;
		std::vector<Button*> iw;
		std::vector<Button*> ie;
		std::vector<Button*> iq;
		for (int i = 0; i < ship.crew.size(); i++) {
			std::wstring mtext = ship.crew[i].name + L"	" + L"ОЗ: " + std::to_wstring(ship.crew[i].ghp()) + L"	ОУ: " + std::to_wstring(ship.crew[i].gdmg())
				+ L" цена: " + std::to_wstring(ship.crew[i].gprice());
			int y = 590 + i * 100;
			int x = 90;
			if (i < 6) {
				w.push_back(new Button(ren, mtext.c_str(), 36, { x,y,500,100 }, "textures/active_fon.png"));
			}
			if (i >= 6) {
				y = 590 + (i - 6) * 100;
				x = 940;
				e.push_back(new Button(ren, mtext.c_str(), 36, { x,y,500,100 }, "textures/active_fon.png"));
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
				iw.push_back(new Button(ren, ship.inventory[i]->convert_to_string().c_str(), 36, {x,y,500,100}, "textures/active_fon.png"));
			}
			if (i >= 6) {
				y = 590 + (i - 6) * 100;
				x = 940;
				ie.push_back(new Button(ren, ship.inventory[i]->convert_to_string().c_str(), 36, {x,y,500,100}, "textures/active_fon.png"));
			}
		}
		iq.push_back(page1);
		iq.push_back(page2);
		iq.push_back(gold);
		items.push_back(iq);
		items.push_back(iw);
		items.push_back(ie);
		/*
		for (int i = 0; i < iw.size(); ++i) {
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
		tgold->rename(std::to_wstring(ship.get_gold()).c_str(), ren);
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
				if (buttons[currentrow][currentbutton]->get_text() == L"назад:") {
					current_level = previous_level;
					return;
				}
				if (buttons[currentrow][currentbutton]->get_text() == L"2") {
					page = 2;
					return;
				}
				if (buttons[currentrow][currentbutton]->get_text() == L"1") {
					page = 1;
					return;
				}
				ship.gold += 5;
				buttons[currentrow].erase(buttons[currentrow].begin() + currentbutton);
				return;
			}

			if (page == 2) {
				if (items[currentrow][currentbutton]->get_text() == L"2") {
					page = 2;
					return;
				}
				if (items[currentrow][currentbutton]->get_text() == L"1") {
					page = 1;
					return;
				}
				ship.gold += 10;
				items[currentrow].erase(items[currentrow].begin() + currentbutton);
				return;
			}
		}
	}
	~Inventory() {
		for (auto& i : buttons) {
			for (auto j : i) {
				delete j;
				j = nullptr;
			}
		}
		for (auto& i : items) {
			for (auto j : i) {
				delete j;
				j = nullptr;
			}
		}
		delete gold, page1, page2, crewsize_cur, crewsize_max, tgold, go_back,sell,texts;

	}
};
