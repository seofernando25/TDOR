//
// Created by fer on 10/12/2021.
//

#ifndef TDOR_SUBSYSTEM_H
#define TDOR_SUBSYSTEM_H


class SubSystem {
public:
    virtual void Init() {}
    virtual void Run() {}
    virtual void Shutdown() {}
};


#endif //TDOR_SUBSYSTEM_H
