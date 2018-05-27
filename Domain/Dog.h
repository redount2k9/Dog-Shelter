//
// Created by razvan on 24.03.2018.
//

#ifndef LAB5_6_DOG_H
#define LAB5_6_DOG_H
#include <string>

class Dog {
private:
    std::string breed;
    std::string name;
    int age;
    std::string url_photo;
public:
    // Class implicit constructor
    Dog();
    Dog(const Dog& dog) {
        this->breed = dog.breed;
        this->name = dog.name;
        this->age = dog.age;
        this->url_photo = dog.url_photo;
    }

    // Class explicit constructor
    Dog(const std::string &breed, const std::string &name, int age, const std::string &url_photo);
    // Assignment operator
    bool operator==(const Dog &a) const;
    // Opens a browser showing the image of the dog
    void display();
    // Returns dog's name
    std::string getName() const;
    // Returns dog's breed
    std::string getBreed() const;
    // Returns dog's age
    int getAge() const;
    // Returns dog's photo
    std::string getPhoto() const;
    std::string toString() const;
    std::string toShortString() const;
    friend std::ostream& operator<<(std::ostream &stream, const Dog& dog);
    friend std::istream& operator>>(std::istream &stream, Dog& dog);
};




#endif //LAB5_6_DOG_H
