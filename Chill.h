#pragma once
#include"Level.h"
class Chill:Level {
	//Sprite pikcha;
	Text text;
	Text text2,text3;
	Button into_tavern;
public:
	Chill(SDL_Renderer* ren, Ship& ship) {
		std::vector<Button> q;
		into_tavern = { ren,L"� �������",48, {100,800,500,100},"textures/active_fon.png" };
		pikcha = { "textures/korablik6.png",ren,300,0,1024,576 };
		std::wstring wtext = L"������� ���� ���������� ���! �� ���� ���� �� ���������� ������� ������� ����������� �������";
		std::wstring wtext2 = L"� ������, ��� ����� �������� ��������� ������������� ������ � �������!";
		std::wstring wtext3 = L"�� ��������: ";
		int gold = genious_random(100, 1000);
		wtext3+= std::to_wstring(gold);
		wtext3 += L"g";
		text = { 36, wtext.c_str(),ren,{100,576,500,100}};
		text2 = { 36, wtext2.c_str(),ren,{100,676,500,100} };
		text3 = { 36, wtext3.c_str(),ren,{100,776,500,100} };
		ship.change_gold(ship.get_gold() + gold);
		q.push_back(into_tavern);
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
		text3.render(ren);
	}
	void manage_buttons(size_t type) {
		Level::manageButton();
		
		if (type == SDL_MOUSEBUTTONDOWN && currentrow != -1 && currentbutton != -1) {
			if (buttons[currentrow][currentbutton].get_text() == L"� �������") {
				current_level = TAVERN;
			}
		}
	}
};