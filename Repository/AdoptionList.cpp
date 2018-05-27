//
// Created by razvan on 31.03.2018.
//

#include "AdoptionList.h"
#include <algorithm>

DogListSingly::DogListSingly() {
    this->current = 0;
}

int DogListSingly::add(const Dog &dog) {
    this->dogList.push_back(dog);
    return 0;
}

Dog DogListSingly::getCurrentDog() {
    return this->dogList[this->current];
}

void DogListSingly::start() {
    if (this->isEmpty())
        return;
    this->current = 0;
}

void DogListSingly::next() {
    if (this->isEmpty())
        return;
    this->current = (this->current + 1) % this->dogList.size();
}

bool DogListSingly::end() {
    return this->dogList.size() == this->current;
}

bool DogListSingly::isEmpty() {
    return this->dogList.size() == 0;
}

int DogListSingly::remove(const Dog &dog) {
    dogList.erase(std::remove(dogList.begin(), dogList.end(), dog), dogList.end());
}

void DogListSingly::previous() {
    if(this->isEmpty())
        return;
    this->current = (this->current - 1) % this->dogList.size();
}

AdoptionList::AdoptionList() {
    this->current = 0;
}

AdoptionList::AdoptionList(const AdoptionList &adList)
{
    adoptionList = adList.adoptionList;
    current = adList.current;
}

int AdoptionList::add(const Dog &dog) {
    this->adoptionList.push_back(dog);
    return 0;
}

Dog AdoptionList::getCurrentDog() {
    return this->adoptionList[this->current];
}

void AdoptionList::start() {
    if (this->isEmpty())
        return;
    this->current = 0;
    Dog currentDog = this->getCurrentDog();
}

int AdoptionList::remove(const Dog &dog) {
    adoptionList.erase(std::remove(adoptionList.begin(), adoptionList.end(), dog), adoptionList.end());
}

void AdoptionList::next() {
    if (this->isEmpty())
        return;
    this->current++;
}

bool AdoptionList::end() {
    return this->adoptionList.size() == this->current;
}

bool AdoptionList::isEmpty() {
    return this->adoptionList.size() == 0;
}
