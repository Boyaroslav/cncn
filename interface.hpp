
#pragma once
#include "utils.hpp"

class Button{
    SDL_Rect cords;
    void (*event)();
    public:

    Button(SDL_Rect c, void (*e)()){
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