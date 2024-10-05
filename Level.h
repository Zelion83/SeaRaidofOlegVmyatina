#pragma once
#include<vector>
#include "Button.h"
class Level {
	std::vector<std::vector<Button*>> buttons;
	void addButtonRow(std::vector<Button*> row) {
		buttons.push_back(row);
	}
	
    bool isCursorInsideRect(SDL_Rect &dst) {
        int cursorX, cursorY;
        SDL_GetMouseState(&cursorX, &cursorY);

        if (cursorX >= dst.x && cursorX <= dst.x + dst.w &&
            cursorY >= dst.y && cursorY <= dst.y + dst.h) {
            return 1;
        }
        else {
            return 0; 
        }
    }
    void switchButton() {
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
    }
    virtual void update() {
        for (auto i : buttons) {
            for (auto j : i) {
                
                if (isCursorInsideRect(*(j->get_coord()))) {
                    j->is_active = true;
                    
                }
                else {
                    j->is_active = false;
                }
                j->update(ren);
            }
        }
    }
};