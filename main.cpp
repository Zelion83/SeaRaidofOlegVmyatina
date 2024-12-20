
#include"Includes.h"
#include<clocale>
#include<ctime>
#include<memory>
SDL_Window* window = NULL;
void reset();
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
	Mix_PlayMusic(temka, 20);
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
	std::unique_ptr<Menu> menu;
	std::unique_ptr<Tavern> tavern;
	std::unique_ptr<Inventory> inventory;
	std::unique_ptr<Fight> fight;
	std::unique_ptr<End> end;
	std::unique_ptr<Chill> chill;
	std::unique_ptr<Rebellion> rebellion;
	std::unique_ptr<Forgotten_map> fmap;
	std::unique_ptr<Plague> plague;
	Sprite smegog("textures/smegog.png", ren, 100, 100, 1280, 720);
	SDL_RenderPresent(ren);
	SDL_Event ev;
	for (;;) {
		while (SDL_PollEvent(&ev)) {
			if (current_level == MAIN_MENU) {
				if (menu == nullptr) {
					menu = std::make_unique<Menu>(ren);
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
				plague.reset();
				chill.reset();
				fmap.reset();
				rebellion.reset();
				ship.reset(10, 1000);
						menu->manageButton(ev.type);
						menu->update(ren);
			}
			if (current_level == TAVERN) {
				if(menu != nullptr){
					menu.reset();
				}
				if (inventory != nullptr) {
					inventory.reset();
				}
				if (fight != nullptr) {
					fight.reset();
				}
				chill.reset();
				rebellion.reset();
				end.reset();
				fmap.reset();
				plague.reset();
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
			if (current_level == CHILL) {
				if (chill == nullptr) {
					chill = std::make_unique<Chill>(ren,ship);
				}
				menu.reset();
				tavern.reset();
				inventory.reset();
				end.reset();
				fight.reset();
				chill->update();
				chill->manage_buttons(ev.type);
			}
			if (current_level == REBELLION) {
				if (rebellion == nullptr) {
					rebellion = std::make_unique<Rebellion>(ren,ship);
				}
				menu.reset();
				tavern.reset();
				inventory.reset();
				end.reset();
				fight.reset();
				chill.reset();
				rebellion->update();
				rebellion->manage_buttons(ev.type,ship);
			}
			if (current_level == MAP) {
				if (fmap == nullptr) {
					fmap = std::make_unique<Forgotten_map>(ren);
				}
				menu.reset();
				tavern.reset();
				inventory.reset();
				end.reset();
				fight.reset();
				chill.reset();
				rebellion.reset();
				fmap->update();
				fmap->manage_buttons(ev.type, ship);
			}
			if (current_level == PLAGUE) {
				if (plague == nullptr) {
					plague = std::make_unique<Plague>(ren,ship);
				}
				menu.reset();
				tavern.reset();
				inventory.reset();
				end.reset();
				fight.reset();
				chill.reset();
				rebellion.reset();
				fmap.reset();
				plague->update();
				plague->manage_buttons(ev.type, ship);
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
	SDL_Quit();
	return 0;
}

