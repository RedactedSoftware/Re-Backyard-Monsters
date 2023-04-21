#include <SDL2/SDL.h>
#include <vector>
#include "renderer.hpp"
enum {BACKGROUND = 0, BUTTON = 1, TEXT = 2};
struct MenuObject {
    bool draw;
    int type;
    int id;
    SDL_Rect renderedObject;
    SDL_Texture* renderedTexture;
};
namespace Menu {
    inline std::vector<MenuObject> menuList;

    void storeMenuObject(MenuObject mOBJ) {
        menuList.push_back(mOBJ);
    }

    void storeMenuTexture(SDL_Texture* texture, int type) {
        for (int i = 0; i < Menu::menuList.size(); i++){
            if (Menu::menuList[i].type == type) {
                Menu::menuList[i].renderedTexture = texture;
            }
        }
    }

    inline void renderMenuObjects() {
        //std::sort(Entity::entityList.begin(), Entity::entityList.end(), compareByHeight);
        //std::reverse(Entity::entityList.begin(),Entity::entityList.end());
        for (int i = 0; i < Menu::menuList.size(); i++){
            if(Menu::menuList[i].draw) {
                SDL_RenderFillRect(Renderer::renderer, &Menu::menuList[i].renderedObject);
                SDL_RenderCopy(Renderer::renderer, Menu::menuList[i].renderedTexture, NULL,
                               &Menu::menuList[i].renderedObject);

            }
        }
    }


}