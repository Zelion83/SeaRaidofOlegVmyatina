
#include "SDL.h"
#include"SDL_mixer.h"
#include"SDL_image.h"
#include <stdio.h>
#include"SDL_ttf.h"
#include"chrono"
#include<string>
#include"Sprite.h"
#include<thread>
#include"Button.h"
#include"Inventory.h"
#include"Menu.h"
#include"Ship&Sailor.h"
#include"Tavern.h"
#include"Button_manager.h"
#include"Fight.h"
#include"End.h"
#include"quick_stats.h"
#include<clocale>
#include<ctime>
#include<memory>
SDL_Window* window = NULL;
//Если класс содержит указатель, он должен быть дополнен согласно правилу трёх - деструктором, конструктором копий и оператором присваивания
// бля короче темка лютая ебейшая, надо сделать UI статов корабля постоянным, внизу куда-нибудь поставить, что бы игрок мог более обдуманно принимать решения
int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("error %s", SDL_GetError());
		exit(-5);
	}
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		printf("error %s", SDL_GetError());
		exit(-2);
	}
	if (SDL_Init(IMG_INIT_PNG) < 0) {
		printf("error %s", SDL_GetError());
		exit(-3);
	}


	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_VolumeMusic(10);
	Mix_Music* temka = Mix_LoadMUS("music/call_of_the_sea.mp3");
	//Mix_Chunk* temka2 = Mix_LoadWAV("call_of_the_sea.mp3");
	Mix_PlayMusic(temka, 0);
	//Mix_PlayChannel(-1, temka2, 1);
	setlocale(LC_ALL, "Russian");
	if (TTF_Init() < 0) {
		printf("error %s", TTF_GetError());
		exit(-4);
	}
	
	window = SDL_CreateWindow("SEROV3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);
	Sprite pikcha();
	Quick_stats qs(ship, ren);
	//Menu* menu = nullptr;
	std::unique_ptr<Menu> menu;
	//menu.reset();
	std::unique_ptr<Tavern> tavern;
	std::unique_ptr<Inventory> inventory;
	std::unique_ptr<Fight> fight;
	std::unique_ptr<End> end;
	//Menu* menu = nullptr;
	//Tavern* tavern = nullptr;
	//Inventory* inventory = nullptr;
	//Fight* fight = nullptr;
	//End* end = nullptr;
	Sprite smegog("textures/smegog.png", ren, 100, 100, 1280, 720);
	SDL_RenderPresent(ren);
	SDL_Event ev;
	for (;;) {
		while (SDL_PollEvent(&ev)) {
			if (current_level == MAIN_MENU) {
				if (menu == nullptr) {
					menu = std::make_unique<Menu>(ren);
					//menu = new Menu(ren);
				}
				if (tavern != nullptr) {
					tavern.reset();
				}
				if (inventory != nullptr) {
					inventory.reset();
				}
				if (fight != nullptr) {
					fight.reset();
				}
						menu->manageButton(ev.type);
						menu->update(ren);
			}
			if (current_level == TAVERN) {
				if(menu != nullptr){
					menu.reset();
					//delete menu; menu = nullptr;
				}
				if (inventory != nullptr) {
					inventory.reset();
				}
				if (fight != nullptr) {
					fight.reset();
				}
				if(tavern == nullptr) tavern = std::make_unique< Tavern>(ren,ship,1);
				tavern->tavern_update(ren, ship);
				tavern->manage_buttons(ev.type);
				qs.update(ship);
			}
			if (current_level == ADVENTURE) {
				if (tavern != nullptr) {
					tavern.reset();
				}
				if (inventory != nullptr) {
					inventory.reset();
				}
				if(fight == nullptr) fight = std::make_unique< Fight>(ren);
				fight->update();
				fight->manageButton(ev.type,ship);
			}
			if (current_level == INVENTORY) {
				if (inventory == nullptr) {
					inventory = std::make_unique< Inventory>(ren, ship,TAVERN);
				}
				inventory->update(ren, ship);
				inventory->manage_buttons(ev.type,ship);
				qs.update(ship);
			}
			if(current_level == END){
				if (end == nullptr) {
					end = std::make_unique< End>(ren);
				}
				menu.reset();
				tavern.reset();
				inventory.reset();
				end->update();
				end->manageButton(ev.type);
			}
			if (ev.type == SDL_QUIT) {
				goto mark1;
				exit(0);

			}
			qs.show(ren);
			SDL_RenderPresent(ren);
			SDL_RenderClear(ren);
		}
	}
mark1:
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(ren);
	Mix_CloseAudio();
	//delete menu;
	//delete tavern;
	//delete inventory;
	SDL_Quit();
	return 0;
}


