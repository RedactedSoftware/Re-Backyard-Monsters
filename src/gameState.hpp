#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include "entity.hpp"
#include "json.h"
using jsonf = nlohmann::json;

struct gamestate {
std::vector<std::vector<entity>> entityLists;
//Eventually get the stuff for money here.
};


namespace GameState {
    inline gamestate gameState;

    void storeGameState() {
        GameState::gameState.entityLists.push_back(Entity::entityList);

        //Only store the last 3 ticks.
        if(GameState::gameState.entityLists.size() > 3) {
            //reverse so we don't pop off the one we just put on.
            std::reverse(GameState::gameState.entityLists.begin(), GameState::gameState.entityLists.end());
            GameState::gameState.entityLists.pop_back();
            //put it back how it was before.
            std::reverse(GameState::gameState.entityLists.begin(), GameState::gameState.entityLists.end());
        }

    }

     std::vector<entity> getPreviousEntityList (int ticksAgo) {
        std::vector<std::vector<entity>> el = gameState.entityLists;
        if (ticksAgo <=3 && ticksAgo > 0 && Globals::tickCount != 1) {
            ticksAgo = ticksAgo -1;
            std::reverse(el.begin(), el.end());
            return el[ticksAgo];
        }
        //returns an entity list with an error entity if something bad happened.
        return std::vector<entity>{Entity::ErrorEntity};
    }

    //The save load code will eventually be on the server and the state of the entityList would be received through the network stream.
    void SaveGame() {
        std::ofstream fout("saveGame.dat", std::ios::out | std::ios::binary);
        fout.write((char*)&GameState::getPreviousEntityList(1)[0], GameState::getPreviousEntityList(1).size() * sizeof(GameState::getPreviousEntityList(1)));
        fout.close();

        }

    void LoadGame() {
        std::string saveGame = "savegame.json";
        if (!std::ifstream {saveGame}.good()) {
            //TODO write the default savegame if the file doesn't exist.
            //create empty file.
            std::ofstream output(saveGame);
        }
        //load
    }
}
