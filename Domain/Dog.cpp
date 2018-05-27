//
// Created by razvan on 24.03.2018.
//

#include "Dog.h"
#include <fstream>
#include <iostream>
Dog::Dog() : breed(""), name(""), age(0), url_photo("") {};

Dog::Dog(const std::string &breed, const std::string &name, int age, const std::string &url_photo) {
    this->breed = breed;
    this->name = name;
    this->age = age;
    this->url_photo = url_photo;
}


std::string Dog::getName() const{
    return this->name;
}

std::string Dog::getBreed() const{
    return this->breed;
}

int Dog::getAge() const{
    return this->age;
}

std::string Dog::getPhoto() const{
    return this->url_photo;
}

std::string Dog::toString() const
{
    return this->breed + ',' + this->name + ',' + std::to_string(this->age) + ',' + this->url_photo;
}

std::__cxx11::string Dog::toShortString() const
{
    return this->breed + ',' + this->name;
}

bool Dog::operator==(const Dog &a) const{
    return ( this->name == a.getName() and this->breed == a.getBreed() );
}

void Dog::display() {
    std::string command = "xdg-open " + url_photo;
    system(command.c_str());
}


std::ostream &operator<<(std::ostream &stream, const Dog &dog) {
    stream << dog.getBreed() << ',' << dog.getName() << ',' << dog.getAge() << ',' << dog.getPhoto();
    return stream;
}

std::istream &operator>>(std::istream &stream, Dog &dog) {
    getline(stream, dog.breed, ',');
    getline(stream, dog.name, ',');
    stream >> dog.age;
    stream.get();
    getline(stream, dog.url_photo);
    return stream;
}
