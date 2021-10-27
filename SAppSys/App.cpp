//
// Created by fer on 10/12/2021.
//

#include "App.h"


void App::AddSubsystem(const std::string& id, SubSystem *subSystem) {
    if(subsystems.count(id)){
        return; // Subsystem already exist
    }

    subsystems[id] = subSystem;

    subSystem->Init();

    // Create running thread
    subsystemThreads[id] = std::thread(&SubSystem::Run, subSystem);
}

void App::RemoveSubsystem(const std::string& id) {
    if(!subsystems.count(id)){
        return; // Subsystem not found
    }
    // Call shutdown function
    subsystems[id]->Shutdown();

    // Remove subsystem
    subsystems.erase(subsystems.find(id));

    // Remove thread (and hope it cleaned itself on shutdown)
    subsystemThreads.erase(subsystemThreads.find(id));
}

SubSystem *App::GetSubsystem(const std::string& id) {
    if(!subsystems.count(id))
        return nullptr;
    return subsystems[id];
}

void App::JoinSubsystems() {
    for(auto it = subsystemThreads.begin(); it != subsystemThreads.end(); ++it)
        it->second.join();
}

