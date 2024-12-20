#pragma once
#include"Level.h"
#include "Ship&Sailor.h"
class Rebellion:Level
{
	Sprite rezultat;
	Text text,text2,text3,textrezulat;
	Button podavit, uspokoit,dalshe;
	std::vector<Sailor> myatezhniki;
	int pogibli;
public:
	Rebellion(SDL_Renderer* ren,Ship& ship) :
		text{ 36,L"Ближайший к вам советник сообщает о том, что среди команды созрел мятеж.",ren,{100,600,500,100} },
		text2{ 36,L"Матросы собрались на палубе, громко бьют в дверь капитанской каюты и требуют, что бы вы вышли.",ren,{100,650,500,100} },
		text3{ 36,L"Вам остались верны несколько членов команды. Что вы будете делать?",ren,{100,700,500,100} },
		podavit{ ren,L"вооружиться и подавить мятеж силой",36,{100,800,500,100} },
		uspokoit{ ren,L"попытаться успокоить мятежников",36,{100,850,500,100} },
		pogibli{ genious_random(0,ship.get_cursize()-1)}
	{
		std::vector<Button> q;
		pikcha = { "textures/rebellion.png",ren,1920 / 4,0,1024,576 };
		q.push_back(podavit);
		q.push_back(uspokoit);
		addButtonRow(q);
		for (int i = ship.get_cursize() - pogibli; i < ship.get_cursize(); ++i) {
			int freak = genious_random(1, ship.get_cursize()-1);
			myatezhniki.push_back(ship.get_sailor(freak));
			
		}
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
	void manage_buttons(size_t type, Ship& ship) {
		Level::manageButton();
		if (type == SDL_MOUSEBUTTONDOWN && currentrow != -1 && currentbutton != -1) {
			if (buttons[currentrow][currentbutton].get_text() == L"вооружиться и подавить мятеж силой") {
				int test = genious_random(1,10);
				if (4 <= test <= 10) {
					for (int i = 0; i < myatezhniki.size(); ++i) {
						ship.delete_sailor(ship.decode_sailor(myatezhniki[i].name));
					}
					pikcha.replace_texture("textures/pirat_cap.png",ren);
					text.rename(L"Вам удалось подавить мятеж, но без жертв не обошлось",ren);
					std::wstring a = L"В ходе боя умерло членов экипажа: " + std::to_wstring(pogibli);
					text2.rename(a.c_str(), ren);
					text3.rename(L"", ren);
					podavit.settext(L"Дальше",ren);
					buttons[0].clear();
					buttons[0].push_back(podavit);
					return;
				}
				else {
					current_level = END;
					return;
				}
			}
			if (buttons[currentrow][currentbutton].get_text() == L"попытаться успокоить мятежников") {
				int test = genious_random(1, 10) * ship.morale;
				if (test < 500) {
					current_level = END;
					return;
				}
				else {
					pikcha.replace_texture("textures/pirat_cap.png", ren);
					text.rename(L"Вы успешно успокоили бунтовщиков силой харизмы.",ren);
					text2.rename(L"", ren);
					text3.rename(L"", ren);
					podavit.settext(L"Дальше", ren);
					buttons[0].clear();
					buttons[0].push_back(podavit);
					return;
				}
			}
			if (buttons[currentrow][currentbutton].get_text() == L"Дальше") {
				current_level = TAVERN;
				return;
			}
		}
	}
};