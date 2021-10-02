//
// Created by fer on 10/2/2021.
//

#include <Scene/Scene.h>
#include "Core/Application.h"

void ECamera::Render() const {
    if (!renderTarget)
        return;
    Vector3 camPos = {cameraRelPosition.x + position.x, cameraRelPosition.y + position.y,
                      cameraRelPosition.z + position.z};
    Vector3 camTarget = {cameraRelTarget.x + position.x, cameraRelTarget.y + position.y,
                         cameraRelTarget.z + position.z};
    Camera cam = {camPos, camTarget, cameraUp, cameraFovy, cameraProjection};
    BeginTextureMode(*renderTarget);
    BeginMode3D(cam);
    for (const auto &entity: Scene::currentScene->entities) {
        entity->Draw(cam);
    }
    EndMode3D();
    EndTextureMode();
}

ECamera::ECamera() {
    renderTarget = &Application::instance->renderTarget;
}
