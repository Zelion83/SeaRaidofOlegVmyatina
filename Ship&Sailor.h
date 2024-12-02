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
	/*
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
	
	bool operator ==(Sailor& sailor) {
		if (hp == sailor.hp &&
			dmg == sailor.hp &&
			sila == sailor.sila &&
			price == sailor.price &&
			name == sailor.name) {
			return true;
		}
		else {
			return false;
		}
		
		hp == sailor.hp;
		dmg == sailor.hp;
		sila == sailor.sila;
		price == sailor.price;
		name == sailor.name;
		return *this;
		*/
	
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

	std::vector<Item> inventory;
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
	int get_cursize() {
		return crew.size();
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
			freak.name += L" ";
			freak.name += name;
			ss >> musor >> freak.hp >> musor1 >> freak.dmg >> musor2 >> freak.price;
			freak.price /= 2;
			gold -= freak.price;
			push_back(freak);
		}
	};
	Sailor decode_sailor(std::wstring s) {
		std::wstringstream ss(s);
		Sailor freak;
		std::wstring name;
		std::wstring musor, musor1, musor2;
		ss >> name;
		freak.name = name;
		ss >> name;
		freak.name += L" ";
		freak.name += name;
		ss >> musor >> freak.hp >> musor1 >> freak.dmg >> musor2 >> freak.price;
		
		return freak;
		
	}
	void delete_sailor(Sailor freak) {
		gold += freak.price;
		power -= ((freak.hp + freak.dmg) / 2);
		for (int i = 0; i < crew.size();++i) {
			if (crew[i].name == freak.name) {
				crew.erase(crew.begin() + i);
			}
		}
		//auto it = std::find(std::begin(crew), std::end(crew), freak);
		//crew.erase(crew.begin());
	}
	auto decode_item(std::wstring s) {
		std::wstringstream ss(s);
		std::wstring opisanie, name, musor1, musor2;
		int price = 0;

		ss >> name >> musor1 >> opisanie >> musor2 >> price;
		name.pop_back();
		for (int i = 0; i < items.size(); ++i) {
			if (items[i].get_name() == name) {
				
				return items[i];
			}
		}
		

		int index = 0;
		Item none = Item(L"None", L"None", "None", 0, ren);
		return none;

	}
	void add_item(std::wstring s) {
		auto item = decode_item(s);
		if (item.name == L"Кот") {
			morale += 10;
		}
		if (item.name == L"Обезьяна") {
			morale += 15;
		}
		if (item.name == L"Пушки") {
			power += 20;
		}
		gold -= item.price;
		inventory.push_back(item);
	}
	void delete_item(std::wstring s) {
		auto item = decode_item(s);
		for (int i = 0; i < inventory.size(); ++i) {
			if (inventory[i].name == item.get_name()) {
				if (inventory[i].name == L"Кот") {
					morale -= 10;
				}
				if (inventory[i].name == L"Обезьяна") {
					morale -= 15;
				}
				if (inventory[i].name == L"Пушки") {
					power -= 20;
				}
				gold += item.price;
				inventory.erase(inventory.begin() + i);
			}
		}
	}
	std::wstring get_item_string(int i) {
		if (i < inventory.size()) {
			std::wstring mtext = inventory[i].name;
			return mtext;
		}
	}
	/*
	~Ship() {
		for (auto i : items) {
			delete i;
			i = nullptr;
			
		}
	}
	*/
};