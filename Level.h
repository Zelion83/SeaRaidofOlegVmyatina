#pragma once
#include<vector>
#include "Button.h"
class Level {
protected:
    Sprite pikcha;
    int currentrow = -1;
    int currentbutton = -1;
    std::vector<std::vector<Button>> buttons;
public:
    void addButtonRow(std::vector<Button> row) {
		buttons.push_back(row);
	}
	
    
    virtual void manageButton() {
        currentrow = -1;
        currentbutton = -1;
        for (int i = 0; i < buttons.size(); i++) {
            for (int j = 0; j < buttons[i].size(); j++) {
                if (buttons[i][j].is_active) {
                    currentrow = i;
                    currentbutton = j;
                    break;
                }
            }
            if (currentrow != -1) break;
        }
        
        if (currentrow == -1) return; 
        
        int newrow = currentrow;
        int newbutton = currentbutton;
    }
    virtual void update() {
        for (auto& i : buttons) {
            for (auto& j : i) {
                j.update(ren);
            }
        }
    }
};