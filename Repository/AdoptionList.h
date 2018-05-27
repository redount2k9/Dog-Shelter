//
// Created by razvan on 31.03.2018.
//

#ifndef LAB5_6_ADOPTIONLIST_H
#define LAB5_6_ADOPTIONLIST_H

#include <vector>
#include "../Domain/Dog.h"

class DogListSingly {
private:
    std::vector<Dog> dogList;
    int current;
public:
    // Class constructor
    DogListSingly();
    DogListSingly(const DogListSingly& dg) {
        this->current = dg.current;
        this->dogList = dg.dogList;
    }

    // Adds a dog object to the list
    int add(const Dog& dog);
    // Removes a dog from the list
    int remove(const Dog& dog);
    // Gets the current dog
    Dog getCurrentDog();
    // Starts the display of the list
    void start();
    // Increments current
    void next();
    // Decrements current
    void previous();
    // Checks end of list
    bool end();
    // Checks if the list is empty
    bool isEmpty();
    // Returns the list of dogs
    std::vector<Dog> getList() {
        return this->dogList;
    }

};

class AdoptionList {
private:
    std::vector<Dog> adoptionList;
    int current;
public:
    // Class constructor
    AdoptionList();
    AdoptionList(const AdoptionList& adList);
    // Adds a dog object to the list
    int add(const Dog& dog);
    // Removes a dog object from the list
    int remove(const Dog& dog);
    // Gets the current dog
    Dog getCurrentDog();
    // Starts the display of the list
    void start();
    // Increments current
    void next();
    // Checks end of list
    bool end();
    // Checks if the list is empty
    bool isEmpty();
    // Returns the list of dogs
    std::vector<Dog> getList() const {
        return this->adoptionList;
    }
};


#endif //LAB5_6_ADOPTIONLIST_H
