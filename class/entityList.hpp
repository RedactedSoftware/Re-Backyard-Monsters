#pragma once
#include <vector>
inline std::vector<entity> entityList;

void storeEntity(entity e) {
    entityList.push_back(e);
}
entity getLocalPlayer() {
    for (int i = 0; i < entityList.size(); i++){
        if (entityList[i].type == LOCALPLAYER)
            return entityList[i];
    }
}

void setLocalPlayer(entity e) {
    for (int i = 0; i < entityList.size(); i++){
        if (entityList[i].type == LOCALPLAYER)
            entityList[i] = e;
    }
}
