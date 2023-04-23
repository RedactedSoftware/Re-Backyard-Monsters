#pragma once

#include <entity.hpp>

namespace ReBackyardMonsters {
    class GameScene
    {
        std::vector<Entity> Entities;
    public:
        void AddEntity(Entity& e);
        Entity GetEntityByUUID(UUID id);
        LocalPlayerEntity GetLocalPlayer();
        void Render();
        void Update();
    };

    Entity GameScene::GetEntityByUUID(UUID id) {
        for(auto& e : Entities)
            if (e.GetUUID() == id)
                return e;
    }

}

