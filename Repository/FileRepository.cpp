//
// Created by razvan on 08.04.2018.
//

#include <iostream>
#include "FileRepository.h"
#include "../Validators/AppError.h"


FileRepository::FileRepository(std::string _filename) : Repository(), filename(_filename) {
    this->read();
}

FileRepository::~FileRepository() {
    this->write();
}

int FileRepository::addDog(const Dog &dog) {
    return Repository::addDog(dog);
}

int FileRepository::removeDog(const Dog &dog) {
    return Repository::removeDog(dog);
}

int FileRepository::updateDog(const Dog &oldDog, const Dog &newDog) {
    return Repository::updateDog(oldDog, newDog);
}



void FileRepository::read() {
    std::ifstream fin(this->filename, std::ios::in);
    if (!fin.is_open())
        throw FileError(1);
    this->vector.clear();

    //std::string params, breed, name, age, link;

    /*while(getline(fin, params)) {
        int p1, p2, p3;
        p1 = params.find(',', 0);
        p2 = params.find(',', p1 + 1);
        p3 = params.find(',', p2 + 1);

        breed = params.substr(0, p1);

        name = params.substr(p1 + 1, p2 - p1 - 1);

        age = params.substr(p2 + 1, p3 - p2 - 1);

        link = params.substr(p3 + 1, params.size() - p3 - 1);

        addDog(Dog{breed, name, std::stoi(age), link});
    }*/

    Dog d{};
    while(fin >> d) {
        addDog(d);
    }

    fin.close();

}

void FileRepository::write() {
    std::ofstream fout(this->filename, std::ios::out | std::ios::trunc);

    std::for_each(this->vector.begin(), this->vector.end(), [&fout](const Dog& dog) {
        fout << dog << '\n';
    });

    fout.close();
}
