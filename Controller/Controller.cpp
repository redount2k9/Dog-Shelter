//
// Created by razvan on 24.03.2018.
//

#include <algorithm>
#include "Controller.h"

void Controller::addDogToRepository(std::string breed, std::string name, int age, std::string url_photo, bool undo) {
    validator.validateDog(breed, name, age, url_photo);
    Dog dog {breed, name, age, url_photo};
    if (this->repository.findDogByBreedAndName(breed, name).getName().empty())
        this->repository.addDog(dog);
    else
        throw ControllerError(1);
    this->history2.clear();
    if (undo) {
        this->history.push_back(std::make_shared<UndoAdd>(this->repository, dog));
    }
}

void Controller::removeDogFromRepository(std::string breed, std::string name, bool undo) {
    auto dog = this->repository.findDogByBreedAndName(breed, name);
    this->history2.clear();
    if (undo) {
        this->history.push_back(std::make_shared<UndoDelete>(this->repository, dog));
    }
    if (this->repository.removeDog(dog))
        throw ControllerError(2);

}

void Controller::updateDogFromRepository(std::string oldBreed, std::string oldName, std::string newBreed,
                                         std::string newName, int age, std::string url_photo, bool undo) {
    auto oldDog = this->repository.findDogByBreedAndName(oldBreed, oldName);
    // If any of the new fields are empty, we assign the old properties to the new object we create
    if (newBreed.empty())
        newBreed = oldBreed;
    if (newName.empty())
        newName = oldName;
    if (age < 1)
        age = oldDog.getAge();
    if (url_photo.empty())
        url_photo = oldDog.getPhoto();
    validator.validateDog(newBreed, newName, age, url_photo);
    Dog newDog{newBreed, newName, age, url_photo};
    if (oldBreed != newBreed && oldName != newName)
        if (!this->repository.findDogByBreedAndName(newBreed, newName).getName().empty() )
            throw ControllerError(3);
    this->history2.clear();
    if (undo) {
        this->history.push_back(std::make_shared<UndoUpdate>(this->repository, oldDog, newDog));
    }
    if (this->repository.updateDog(oldDog, newDog))
        throw ControllerError(3);


}

std::vector<Dog> Controller::getDogsFromRepository() {
    return repository.getAllDogs();
}

int Controller::getVectorSize() {
    return repository.getVectorSize();
}

int Controller::addDogToAdoptionList(const Dog &dog) {
    return this->adoptionList.add(dog);
}

int Controller::deleteDogFromAdoptionList(const Dog &dog) {
    return this->adoptionList.remove(dog);
}

void Controller::filterAdoptedDogs(std::vector<Dog> &dogs) {

    int noDogs = static_cast<int>(std::count_if(dogs.begin(), dogs.end(), [this](Dog d) {
        return isAdopted(d);
    }));

    std::vector<Dog> resultedDogs(noDogs);

    std::copy_if(dogs.begin(), dogs.end(), resultedDogs.begin(), [this](Dog d) {
        return isAdopted(d);
    });

    dogs = resultedDogs;

}

void Controller::deleteFromList(DogListSingly &list, Dog& dog) {
    list.remove(dog);
}

DogListSingly Controller::getDogsByBreedAndAge(std::string breed, int age) {
    std::vector<Dog> dogs = this->repository.getAllDogs();
    //filterAdoptedDogs(dogs);
    DogListSingly currentList;
    for ( const auto &currentDog : dogs ) {
        if ( breed.empty() ) {
            if (age == -1 or age == 0 or currentDog.getAge() < age)
                currentList.add(currentDog);
        }
        else {
            if (currentDog.getBreed() == breed and currentDog.getAge() < age)
                currentList.add(currentDog);
        }
    }
    return currentList;

}

bool Controller::isAdopted(const Dog &dog) const {
    /*for ( int i = 0; i < this->adoptionList.getList().getSize(); ++i )
        if ( this->adoptionList.getList().getElement(i) == dog )
            return true;
    return false;
     */
    for ( const auto &currentDog : adoptionList.getList() )
        if (currentDog == dog)
            return true;
    return false;
}

void Controller::setAdoptionListFormat(const std::string &format) {
    if ( format == "CSV" )
        listSaver = std::make_shared<CSVListSaver>(adoptionList);
    else if ( format == "HTML" )
        listSaver = std::make_shared<HTMLListSaver>(adoptionList);
}

Dog Controller::createDog(std::vector<std::__cxx11::string> vec)
{
    std::string breed = vec[0];
    std::string name = vec[1];
    int age = std::stoi(vec[2]);
    std::string url_photo = vec[3];
    validator.validateDog(breed, name, age, url_photo);
    return Dog{breed, name, age, url_photo};

}

void Controller::openPhoto(std::__cxx11::string url)
{
    std::string command = "xdg-open " + url;
    system(command.c_str());
}

void Controller::undo()
{
    if (this->history.empty())
        return;
    this->history.back()->undo(this->history2);
    this->history.pop_back();
}

void Controller::redo()
{
    if (this->history2.empty())
        return;
    this->history2.back()->undo(this->history);
    this->history2.pop_back();
}



