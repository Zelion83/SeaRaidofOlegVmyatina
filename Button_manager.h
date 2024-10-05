#pragma once
#include"Button.h"
#include"Ship&Sailor.h"
Ship ship(7, 1000);
class ButtonManager {
protected:
    std::vector<std::vector<Button*>> buttons;
    void* parent = nullptr;
public:
    bool active = true;
    friend class Menu;
    friend class Tavern;
    friend class Inventory;
    void addButtonRow(std::vector<Button*> row) {
        buttons.push_back(row);
    }
    template <typename T> void add_parent(T* parent) {
        //this->parent = parent;
        this->parent = static_cast<T*> (parent);
    }
    template <typename T>void switchButton(SDL_Keycode direction, T* par) {
        
            int currentrow = -1;
            int currentbutton = -1;
            for (int i = 0; i < buttons.size(); i++) {
                for (int j = 0; j < buttons[i].size(); j++) {
                    if (buttons[i][j]->is_active) {
                        currentrow = i;
                        currentbutton = j;
                        break;
                    }
                }
                if (currentrow != -1) break;
            }

            if (currentrow == -1) return; // no active button

            int newrow = currentrow;
            int newbutton = currentbutton;
            switch (direction) {
            case SDLK_LEFT:
                newrow = (currentrow - 1 + buttons.size()) % buttons.size();
                if (currentbutton > buttons[newrow].size() - 1) {
                    newbutton = 0;
                }
                else newbutton = currentbutton;
                break;
            case SDLK_RIGHT:
                newrow = (currentrow + 1) % buttons.size();
                //if(buttons.size() > 1)newbutton = (buttons.size() % (newrow+1))-1;
                if (currentbutton > buttons[newrow].size() - 1) {
                    newbutton = 0;
                }
                else newbutton = currentbutton;
                break;
            case SDLK_UP:
                newbutton = (currentbutton - 1 + buttons[currentrow].size()) % buttons[currentrow].size();
                break;
            case SDLK_DOWN:
                newbutton = (currentbutton + 1) % buttons[currentrow].size();
                break;

            case SDLK_SPACE:
                if (buttons[currentrow][currentbutton]->get_text() == "exit") {
                    exit(0);
                }
                if (buttons[currentrow][currentbutton]->get_text() == "new game") {
                    current_level = TAVERN;
                    active = false;
                    break;
                }
                if (current_level == TAVERN) {

                    if (buttons[currentrow][currentbutton]->get_text() == "go to the adventure") {
                        current_level = ADVENTURE;
                        break;
                    }
                    //if (typeid(T).name() == "class Tavern * __ptr64") {
                        if (buttons[currentrow][currentbutton]->get_text() == "next") {
                            par->page = 2;
                            //par->item_manager.buttons[0][0]->is_active = true;
                            break;
                        }
                        if (buttons[currentrow][currentbutton]->get_text() == "back") {
                            par->page = 1;
                            break;
                        }
                   // }
                    if (buttons[currentrow][currentbutton]->get_text() == "INVENTORY") {
                        current_level = INVENTORY;
                        break;
                    }

                    if (ship.crew.size() < ship.crewsize) {
                        ship.push_string(buttons[currentrow][currentbutton]->get_text());
                        buttons[currentrow].erase(buttons[currentrow].begin() + currentbutton);


                        if (buttons[currentrow].size()) {
                            newbutton = currentbutton % buttons[currentrow].size();
                        }
                        if (buttons[currentrow].size() == 0) {
                            buttons.erase(buttons.begin() + currentrow);
                            break;
                        }


                        for (int j = currentbutton; j < buttons[currentrow].size(); j++) {
                            buttons[currentrow][j]->change_coord(0, -100);
                        }
                        if (buttons[currentrow].size() == 0) {
                            newrow = currentrow + 1;
                            newbutton = 0;
                        }
                    }
                }
                if (current_level == INVENTORY) {
                    if (buttons[currentrow][currentbutton]->get_text() == "Go back") {
                        current_level = TAVERN;
                        break;
                    }

                }
                break;
            }
            if (buttons[currentrow].size() > currentbutton) {
                buttons[currentrow][currentbutton]->is_active = false;
            }
            buttons[newrow][newbutton]->is_active = true;
        }

    
};