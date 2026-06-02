/*
 * This file is part of CnCn (mynovel).
 * Copyright (C) 2026 Iaroslav Bobylev
 * CnCn (mynovel) is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * CnCn (mynovel) is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with CnCn (mynovel). If not, see <https://www.gnu.org/licenses/>.
 */



#pragma once
#include "utils.hpp"

class Button{
    SDL_Rect cords;
    std::function<void()> event;
    public:

    Button(SDL_Rect c, std::function<void()> e){
        event = e;
        cords = c;
    }

    void draw(SDL_Renderer *rend, int xx, int yy, bool is_hovered=0){

    }

    void action(){
        event();
    }

};


class Menu{
    std::vector<std::variant<Button>>things;
    int x, y, w, h;

    void draw(SDL_Renderer *rend){
        for(int i=0; i<things.size(); i++){
            std::visit([&](auto& thing) {
                thing.draw(rend, x, y);
            }, things[i]);
        }
    }
};