//
// Created by fer on 9/30/2021.
//



#include "Scene.h"

Scene *Scene::currentScene = nullptr;

Scene::Scene() {
//    L = luaL_newstate();
//    luaL_openlibs(L); // Very dangerous on the wrong hands :)
}

Scene::~Scene() {
//    lua_close(L);
}

void Scene::Update(float dt) {
    currentScene = this;

    for (const auto &entity: entities) {
        entity->Update(dt);
    }
}

void Scene::Draw() {
    currentScene = this;
    for (const auto &camera: cameras) {
        camera->Render();
    }

    // TODO Probably do something about static geometry
}
