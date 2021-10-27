//
// Created by fer on 10/12/2021.
//

#ifndef TDOR_APP_H
#define TDOR_APP_H


#include "SubSystem.h"
#include "spch.h"

class App {
public:
    void JoinSubsystems();

    void AddSubsystem(const std::string& id, SubSystem* subSystem);
    void RemoveSubsystem(const std::string& id);
    SubSystem* GetSubsystem(const std::string& id);

    virtual bool StartUp() {return true;}
    virtual bool Shutdown() {return true;}
private:
    std::map<std::string, std::thread> subsystemThreads;
    std::map<std::string, SubSystem*> subsystems;

};

#endif //TDOR_APP_H
