//
// Created by fer on 9/30/2021.
//



#include <Core/Application.h>
#include "LevelGeometry.h"
//
//void LevelGeometry::UpdateUI(RenderTexture target){
//    // TODO Check if click and assign last clicked
//    // maybe on mouse enter and stuff?
//
//    RelativeRect renderRect{(float)target.texture.width, (float)target.texture.height, 0,0,1,1};
//    for (const auto &uiElement : uiEntities){
//        uiElement->Draw(renderRect);
//    }
//}
//
//void LevelGeometry::Update(float dt) {
//    int i = 0;
//    for (auto &thinker : thinkers){
//        thinker->Tick(this);
//        if(thinker->wantsToBeRemoved){
//            thinker->OnRemoved(this);
//            thinkers.erase(thinkers.begin() + i);
//        }
//        i++;
//    }
//
//
//    for (const auto &uiElement : uiEntities){
//        uiElement->Update(dt);
//    }
//}
//
//void LevelGeometry::Render(RenderTexture target) {
//    if(!mainCamera)
//        return;
//
//
//    BeginTextureMode(target);
//    BeginMode3D(*mainCamera);
//    DrawGrid(10, 1);
//    for (const auto &entity: entities) {
//        // TODO How do we know what to draw?
//        DrawCube({entity->position.x, 0.5, -entity->position.y}, 0.5, 0.5, 0.5, WHITE);
//    }
//    EndMode3D();
//    UpdateUI(target);
//    EndTextureMode();
//}

