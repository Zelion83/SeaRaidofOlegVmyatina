#pragma once
#include<vector>
#include "Button.h"
class Level {
protected:
    int currentrow = -1;
    int currentbutton = -1;
    std::vector<std::vector<Button*>> buttons;
public:
    void addButtonRow(std::vector<Button*> row) {
		buttons.push_back(row);
	}
	
    
    virtual void manageButton() {
        
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
                j->update(ren);
            }
        }
    }
};