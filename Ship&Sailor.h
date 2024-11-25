#pragma once
#include <string>
#include<sstream>
#include"Item.h"
#include"Sprite.h"
#include"Button.h"
#include"Text.h"
//#include"Inventory.h"

class Sailor {
	int hp = 0;
	int dmg = 0;
	int sila = (hp + dmg) / 2;
	int price = sila;
public:
	friend class Ship;
	std::wstring name;

	Sailor() {

		hp = genious_random(0, 100);
		dmg = genious_random(0, 100);
		sila = (hp + dmg) / 2;
		price = sila;
	}
	int gprice() {
		return price;
	}
	int ghp() {
		return hp;
	}
	int gdmg() {
		return dmg;
	}
	int gsila() {
		return sila;
	}
	void cprice(int n) {
		price = n;
	}
	void chp(int n) {
		hp = n;
	}
	void cdmg(int n) {
		dmg =  n;
	}
	void csila(int n) {
		sila =  n;
	}
	 Sailor operator =(Sailor& sailor) {
		hp = sailor.hp;
		dmg = sailor.hp;
		sila = sailor.sila;
		price = sailor.price;
		name = sailor.name;
		return *this;
	}

	Sailor(const Sailor& sailor) {

		hp = sailor.hp;
		dmg = sailor.dmg;
		sila = sailor.sila;
		price = sailor.price;
		name = sailor.name;
	}
	Sailor(int hp, int dmg, int price, const wchar_t* name) {
		this->hp = hp;
		this->dmg = dmg;
		sila = (hp + dmg) / 2;
		this->price = price;
		this->name = name;
	};
};
class Ship {
protected:
	std::vector<Sailor> crew;
	unsigned long long gold;
	int crewsize;

	std::vector<Item*> inventory;
public:
	friend class ButtonManager;
	friend class Inventory;
	friend class Tavern;
	int power;
	int morale;
	Ship(int size, int gold) {
		crewsize = size;
		this->gold = gold;
		morale = 100;
		power = 0;
	}
	int get_gold() {
		return gold;
	}
	void change_gold(int a) {
		gold = a;
	}
	void push_back(Sailor& sailor) {
		crew.push_back(sailor);
		for (int i = 0; i < crew.size(); i++) {
			power += crew[i].sila;
		}
	}
	void push_string(std::wstring s) {
		if (crew.size() < crewsize) {
			std::wstringstream ss(s);
			Sailor freak;
			std::wstring name;
			std::wstring musor, musor1, musor2;
			ss >> name;
			freak.name = name;
			ss >> name;
			freak.name += name;
			ss >> musor >> freak.hp >> musor1 >> freak.dmg >> musor2 >> freak.price;
			freak.price /= 2;
			gold -= freak.price;
			push_back(freak);
		}
	};
	auto decode(std::wstring s) { 
		std::wstringstream ss(s);
		std::wstring opisanie, name,musor1,musor2;
		int price = 0;

		ss >> name >> musor1 >> opisanie >> musor2 >> price;
		name.pop_back();
		for (int i = 0; i < items.size(); ++i) {
			if (items[i]->get_name() == name) {
				gold -= items[i]->price;
				return items[i];
			}
		}
		int index = 0;
		Item* none = new Item(L"None", L"None", "None", 0, ren);
		return none;

	}
	void add_item(std::wstring s) {
		inventory.push_back(decode(s));
	}
	std::wstring get_item_string(int i) {
		if (i < inventory.size()) {
			std::wstring mtext = inventory[i]->name;
			return mtext;
		}
	}
	~Ship() {
		for (auto i : items) {
			delete i;
			i = nullptr;
			
		}
	}
};