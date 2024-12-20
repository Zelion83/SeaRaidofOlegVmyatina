#pragma once
#include"Button.h"
#include"Ship&Sailor.h"
class Quick_stats{
	Text crew, morale, gold, power, proviant;
public:
	Quick_stats(Ship& ship,SDL_Renderer* ren):
		crew(48, L"Размер экипажа: ", ren, { 30,900,500,100 }), morale(48, L"Мораль экипажа:", ren, {600,900,500,100}),
		gold(48, L"Золото: ", ren, {30,950,500,100 }), power(48, L"Сила корабля: ", ren, { 600,950,500,100 }),
		proviant(48,L"Провиант: ",ren,{1100,900,500,100})
	{
		std::wstring ws = L"Размер экипажа: " + std::to_wstring(ship.get_cursize());
		crew.rename(ws.c_str(),ren);
		ws = L"Мораль экипажа: " + std::to_wstring(ship.morale);
		morale.rename(ws.c_str(), ren);
		ws = L"Золото: " + std::to_wstring(ship.get_gold());
		gold.rename(ws.c_str(), ren);
		ws = L"Сила корабля: " + std::to_wstring(ship.power);
		//power = Text(48, L"Сила корабля: ", ren, { 600,950,500,100 }); вот так нельзя инициализировать
		power.rename(ws.c_str(), ren);
		ws = L"Провиант: " + std::to_wstring(ship.proviant);
		proviant.rename(ws.c_str(), ren);
	}
	void show(SDL_Renderer* ren){
		crew.render(ren);
		morale.render(ren);
		gold.render(ren);
		power.render(ren);
		proviant.render(ren);
	}
	void update(Ship& ship) {
		std::wstring ws = L"Размер экипажа: " + std::to_wstring(ship.get_cursize());
		crew.rename(ws.c_str(), ren);
		ws = L"Мораль экипажа: " + std::to_wstring(ship.morale);
		morale.rename(ws.c_str(), ren);
		ws = L"Золото: " + std::to_wstring(ship.get_gold());
		gold.rename(ws.c_str(), ren);
		ws = L"Сила корабля: " + std::to_wstring(ship.power);
		power.rename(ws.c_str(), ren);
	}
};