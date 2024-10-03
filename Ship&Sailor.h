#pragma once
#include <string>
#include<sstream>
#include"Item.h"
#include"Sprite.h"
#include"Button.h"
#include"Text.h"
//#include"Inventory.h"
class Sailor {
public:
	int hp = 0;
	int dmg = 0;
	int sila = (hp + dmg) / 2;
	int price = sila;
	std::string name;
	Sailor() {

		hp = genious_random(0, 100);
		dmg = genious_random(0, 100);
		sila = (hp + dmg) / 2;
		price = sila;
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
	Sailor(int hp, int dmg, int price, const char* name) {
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
	int power;
	int morale;
	std::vector<Item*> inventory;
public:
	friend class ButtonManager;
	friend class Inventory;
	Ship(int size, int gold) {
		crewsize = size;
		this->gold = gold;
		morale = 100;
	}
	int get_gold() {
		return gold;
	}
	void change_gold(int a) {
		gold += a;
	}
	void push_back(Sailor& sailor) {
		crew.push_back(sailor);
		for (int i = 0; i < crew.size(); i++) {
			power += crew[i].sila;
		}
	}
	void push_string(std::string s) {
		if (crew.size() < crewsize) {
			std::stringstream ss(s);
			Sailor freak;
			std::string name;
			std::string musor, musor1, musor2;
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
	void add_item(Item* item) {
		inventory.push_back(item);
	}

	/*
	Ship operator+(Sailor& sailor) {
		crew.push_back(sailor);
	}
	*/
};