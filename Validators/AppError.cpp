//
// Created by razvan on 09.04.2018.
//

#include "AppError.h"

const std::string AppError::getMessage() const {
    return this->message;
}

AppError::AppError() : message("") {}


FileError::FileError(int error) {
    switch(error) {
        case 1:
            message = "File could not be opened\n";
        default:
            break;
    }

}

ControllerError::ControllerError(int error) {
    switch (error) {
        case 1:
            message = "Could not add dog\n";
            break;
        case 2:
            message = "Could not remove dog\n";
            break;
        case 3:
            message = "Could not update dog\n";
            break;
        case 4:
            message = "No dogs exist\n";
            break;
        case 5:
            message = "Error!\n";
            break;
        default:
            break;
    }
}

void Validator::validateDog(const std::string& breed, const std::string& name, int age, const std::string& link) const {
    int status = 0;
    if ( breed.empty() )
        status += 1;
    if ( name.empty() )
        status += 2;
    if ( age < 0 or age > 20 )
        status += 4;
    if ( link.empty() )
        status += 8;
    else if ( link.find("www", 0) == std::string::npos && link.find("http", 0) == std::string::npos )
        status += 16;
    if ( status > 0 )
        throw ValidatonError(status);
}

void Validator::validateDogObject(const Dog &dog) {
    int status = 0;
    if ( dog.getBreed().empty() )
        status += 1;
    if ( dog.getName().empty() )
        status += 2;
    if ( dog.getAge() < 0 or dog.getAge() > 20 )
        status += 4;
    if ( dog.getPhoto().empty() )
        status += 8;
    else if ( dog.getPhoto().find("www", 0) == std::string::npos && dog.getPhoto().find("http", 0) == std::string::npos )
        status += 16;
    if ( status > 0 )
        throw ValidatonError(status);
}

ValidatonError::ValidatonError(int status) {
    if ( status & 1 )
        message += "Breed cannot be empty\n";
    if ( status & 2 )
        message += "Name cannot be empty\n";
    if ( status & 4 )
        message += "Age is not in a valid range\n";
    if ( status & 8 )
        message += "Link cannot be empty\n";
    if ( status & 16 )
        message += "Invalid link\n";
}
