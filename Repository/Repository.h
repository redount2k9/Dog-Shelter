//
// Created by razvan on 24.03.2018.
//

#ifndef LAB5_6_REPOSITORY_H
#define LAB5_6_REPOSITORY_H


#include "../Domain/Dog.h"
#include <vector>
#include <algorithm>

class Repository {
protected:
    std::vector<Dog> vector;
public:
    // Class constructor
    Repository() {}
    // Adds a dog object to repository
    virtual int addDog(const Dog& dog);
    // Removes a dog object from repository
    virtual int removeDog(const Dog& dog);
    // Updates a dog object from repository with another dog object
    virtual int updateDog(const Dog& oldDog, const Dog& newDog);
    // Returns the dog object containing the given breed and name, or an empty object if such a dog does not exist
    Dog findDogByBreedAndName(std::string breed, std::string name);
    // Returns the list of dogs (pointer to the first dog element)
    std::vector<Dog>& getAllDogs();
    // Returns the size of the vector
    unsigned long getVectorSize();
};


#endif //LAB5_6_REPOSITORY_H
