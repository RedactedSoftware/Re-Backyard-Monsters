#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <algorithm>

#include <globals.hpp>
#include <renderer.hpp>
#include <inputHandler.hpp>
#include <texture.hpp>
#include <Vector2.hpp>

//entity types.
enum { PLAYER = 0, TOWNHALL = 1, TWIGSNAPPER = 2, PEBBLESHINER = 3, ERRORENTITY = -247, YARD = 4};
struct entity {
    int type;
    bool isLocalPlayer;
    int entityID;
    bool draw;
    bool doAnim;
    int animState;
    int posX, posY, width, height;
    SDL_Rect renderedEntity;
    SDL_Texture* renderedTexture;
};

typedef uint64_t UUID;

namespace ReBackyardMonsters {

    class Entity {
        Vector2 Position;
        Vector2 PrevPosition;
        Vector2 NextPosition;
        Vector2 Velocity;
        Vector2 BoundingBox;
        UUID EntityID;
    public:
        virtual void Draw();
    public:
        UUID GetUUID();
    };
    class PlayerEntity : public virtual Entity { };
    class LocalPlayerEntity : public virtual PlayerEntity { };
    class TownHall : public virtual Entity { };
    class PebbleShiner : public virtual Entity { };
    class YardEntity : public virtual Entity { };
    class ErrorEntity : public virtual Entity {

    };

    //inline std::vector<entity> entityList;
    inline entity ErrorEntity = {ERRORENTITY,0,-247,false};

    /*inline void storeEntity(entity e) {
        entityList.push_back(e);
    }*/

    /*inline entity* getEntityByID(int id) {
        for (int i = 0; i < entityList.size(); i++) {
            if (entityList[i].entityID == id)
                return &entityList[i];
        }
    }*/
    /*inline entity* getLocalPlayer() {
        for (int i = 0; i < entityList.size(); i++){
            if (entityList[i].type == PLAYER && entityList[i].type == PLAYER)
                return &entityList[i];
        }
    }*/
    /*inline bool compareByHeight(const entity &x, const entity &y)
    {
        return x.posY < y.posY;
    }*/

    //TODO This is the biggest hack I've ever made.
    //Return the entity the player is intersecting with which has the lowest Y coordinate.
    /*inline entity* getEntityByIntersection() {
        std::vector<entity> intersectionVector;
        for (int i = 0; i < entityList.size(); i++){
            if (SDL_HasIntersection(&Entity::getLocalPlayer()->renderedEntity, &entityList[i].renderedEntity) == SDL_TRUE) {
                if(!Entity::entityList[i].isLocalPlayer) {
                    intersectionVector.push_back(Entity::entityList[i]);
                    std::sort(intersectionVector.begin(), intersectionVector.end(), compareByHeight);
                }
            }
        }
        if (intersectionVector.size() == 0)
            return &Entity::ErrorEntity;
        std::reverse(intersectionVector.begin(),intersectionVector.end());
        return Entity::getEntityByID(intersectionVector[0].entityID);
    }*/

    inline entity* getEntityByClick() {
        if (InputHandler::isMouse1Down) {
            return getEntityByIntersection();
        }
        return &Entity::ErrorEntity;
    }

    inline void setLocalPlayer(entity e) {
        for (int i = 0; i < entityList.size(); i++){
            if (entityList[i].type == PLAYER && entityList[i].type == PLAYER)
                entityList[i] = e;
        }
    }

    //TODO this won't work right until I check if tick-count is the same as it was last frame.
    inline void storeEntityTextures() {
        for (int i = 0; i < Entity::entityList.size(); i++){
            if (Entity::entityList[i].type == PEBBLESHINER) {
                if (entityList[i].doAnim) {
                    entityList[i].animState++;
                    if (entityList[i].animState > 25)
                        entityList[i].animState = 0;
                    Entity::entityList[i].renderedTexture = Texture::pebbleShiner[entityList[i].animState];
                }
                if (!entityList[i].doAnim)
                    entityList[i].animState = 0;
            }
            if(Entity::entityList[i].type == YARD)
                Entity::entityList[i].renderedTexture = Texture::grassTexture;
        }
    }

    //Render entities in order Y position.
    inline void renderEntities() {

        //Savant genius render the boxes used for collision *under* the grass LOL.
        std::sort(Entity::entityList.begin(), Entity::entityList.end(), compareByHeight);
        for (int i = 0; i < Entity::entityList.size(); i++){
            if(Entity::entityList[i].draw && Entity::entityList[i].type != PLAYER && Entity::entityList[i].type != YARD) {
                SDL_RenderFillRect(Renderer::renderer, &Entity::entityList[i].renderedEntity);
            }
        }

        //Render the grass.
        for (int i = 0; i < Entity::entityList.size(); i++){
            if (Entity::entityList[i].type == YARD) {
                SDL_RenderFillRect(Renderer::renderer, &Entity::entityList[i].renderedEntity);
                SDL_RenderCopy(Renderer::renderer, Entity::entityList[i].renderedTexture, NULL,
                               &Entity::entityList[i].renderedEntity);
            }
        }
        //Generic
        for (int i = 0; i < Entity::entityList.size(); i++){
            if(Entity::entityList[i].draw && !Entity::entityList[i].type == PLAYER && Entity::entityList[i].type != YARD) {
                    SDL_RenderCopy(Renderer::renderer, Entity::entityList[i].renderedTexture, NULL,
                                   &Entity::entityList[i].renderedEntity);

            }
            //Always render the localPlayer last for now.
            SDL_RenderFillRect(Renderer::renderer,&Entity::getLocalPlayer()->renderedEntity);
        }
    }
}
