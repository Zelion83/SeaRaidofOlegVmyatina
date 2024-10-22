
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
#include<clocale>
#include<ctime>
SDL_Window* window = NULL;

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
	setlocale(LC_ALL, "Russian");
	if (TTF_Init() < 0) {
		printf("error %s", TTF_GetError());
		exit(-4);
	}
	
	window = SDL_CreateWindow("SEROV3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);
	Sprite pikcha;
	Menu* menu = nullptr;
	Tavern* tavern = nullptr;
	Inventory* inventory = nullptr;
	Sprite smegog("textures/smegog.png", ren, 100, 100, 1280, 720);
	SDL_RenderPresent(ren);
	SDL_Event ev;
	for (;;) {
		while (SDL_PollEvent(&ev)) {
			if (current_level == MAIN_MENU) {
				if (menu == nullptr) {
					menu = new Menu(ren);
					
				}
				
				
					

						menu->manageButton(ev.type);
					
				

					menu->update(ren);
					
				
				
			}
			
			if (current_level == TAVERN) {
				//printf("%s", typeid(tavern).name());
				if(menu != nullptr){
					delete menu; menu = nullptr;
				}
				if (inventory != nullptr) {
					//delete inventory; inventory = nullptr;
				}
				if(tavern == nullptr) tavern = new Tavern(ren,ship,1);
				tavern->tavern_update(ren, ship);
				tavern->manage_buttons(ev.type);
			}
			if (current_level == ADVENTURE) {
				if (tavern != nullptr) {
					delete tavern; tavern = nullptr;
				}
				smegog.update(ren);
			}
			if (current_level == INVENTORY) {
				if (inventory == nullptr) {
					inventory = new Inventory(ren, ship,TAVERN);
				}
				inventory->update(ren, ship);
				inventory->manage_buttons(ev.type,ship);
			}
			if (ev.type == SDL_QUIT) {
				goto mark1;
				exit(0);

			}
			SDL_RenderPresent(ren);
			SDL_RenderClear(ren);
		}
	}
mark1:
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(ren);
	delete menu;
	delete tavern;
	SDL_Quit();
	return 0;
}


