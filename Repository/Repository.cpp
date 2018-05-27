//
// Created by razvan on 24.03.2018.
//

#include "Repository.h"

int Repository::addDog(const Dog &dog) {
    this->vector.push_back(dog);
}

Dog Repository::findDogByBreedAndName(std::string breed, std::string name) {
    std::vector<Dog> dogs = this->vector;

    if (dogs.empty())
        return Dog{};

    for (auto dog : dogs) {
        if (dog.getName() == name and dog.getBreed() == breed)
            return dog;
    }

    return Dog{};
}

int Repository::removeDog(const Dog &dog) {
    std::vector<Dog> &dogs = this->vector;
    int initialSz = dogs.size();

    if (dogs.empty())
        return 1;

    auto it = dogs.erase(std::remove(dogs.begin(), dogs.end(), dog), dogs.end());

    if ( initialSz == dogs.size() )
        return 1;

    return 0;
}

int Repository::updateDog(const Dog &oldDog, const Dog &newDog) {
    std::vector<Dog>& dogs = this->vector;

    if ( dogs.empty() )
        return 1;

    auto it = std::find(dogs.begin(), dogs.end(), oldDog);

    if ( it == dogs.end() )
        return 1;

    removeDog(oldDog);

    this->vector.insert(it, newDog);

    return 0;
}

std::vector<Dog>& Repository::getAllDogs() {
    return this->vector;
}

unsigned long Repository::getVectorSize() {
    return this->vector.size();
}


