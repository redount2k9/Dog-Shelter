//
// Created by razvan on 24.03.2018.
//

#ifndef LAB5_6_UI_H
#define LAB5_6_UI_H


#include "../Controller/Controller.h"

class UI {
private:
    Controller controller;
public:
    explicit UI(const Controller& c) : controller(c) {};
    void start();
private:
    static void printUserMenu();
    static void printRepositoryMenu();
    static void printUserModeMenu();

    void printFormatSaver();
    void printAddDogMenu();
    void printDeleteDogMenu();
    void printUpdateDogMenu();
    void printAllDogsMenu();
    void printDogsIndividually(std::string, int age);
    void printAdoptionMenu();
    void printAdoptionList();


};


#endif //LAB5_6_UI_H
