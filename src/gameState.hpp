#include <vector>
#include <string>
#include "entity.hpp"

struct gamestate {
std::vector<std::vector<entity>> entityLists;
//Eventually get the stuff for money here.
};


namespace GameState {
    inline gamestate gameState;

    void storeGameState() {
        GameState::gameState.entityLists.push_back(Entity::entityList);

        //Only store the last 3 ticks.
        if(GameState::gameState.entityLists.size() > 2) {
            //reverse so we don't pop off the one we just put on.
            std::reverse(GameState::gameState.entityLists.begin(), GameState::gameState.entityLists.end());
            GameState::gameState.entityLists.pop_back();
            //put it back how it was before.
            std::reverse(GameState::gameState.entityLists.begin(), GameState::gameState.entityLists.end());
        }

    }

     std::vector<entity> getPreviousEntityList (int ticksAgo) {
        std::vector<std::vector<entity>> el = gameState.entityLists;
        if (ticksAgo <=2 && ticksAgo > 0 && Globals::tickCount != 1) {
            ticksAgo = ticksAgo -1;
            std::reverse(el.begin(), el.end());
            return el[ticksAgo];
        }
        //returns an empty entityList if something bad happened.
        return std::vector<entity>{};
    }
}
