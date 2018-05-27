//
// Created by razvan on 09.04.2018.
//

#ifndef LAB5_6_APPERROR_H
#define LAB5_6_APPERROR_H
#include <string>
#include "../Domain/Dog.h"

class AppError {
public:
    // Class constructor
    AppError();
    // Getter for the error message
    const std::string getMessage() const;
protected:
    std::string message;
};

class FileError : public AppError {
public:
    // Class constructor
    FileError(int);
};

class ControllerError : public AppError {
public:
    // Class constructor
    ControllerError(int);
};

class ValidatonError : public AppError {
public:
    // Class constructor
    ValidatonError(int);
};

class Validator {
public:
    // Function which checks if a dog object can be created with the given field values
    void validateDog(const std::string&, const std::string&, int, const std::string&) const;
    // Function which checks if a dog object is correctly created
    void validateDogObject(const Dog& dog);
};

#endif //LAB5_6_APPERROR_H
