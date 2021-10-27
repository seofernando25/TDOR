//
// Created by fer on 10/12/2021.
//

#ifndef TDOR_APP_H
#define TDOR_APP_H


class App {
public:
    App();
    int Run();

    virtual bool StartUp() {return true;}
    virtual bool Shutdown() {return true;}
};


#endif //TDOR_APP_H
