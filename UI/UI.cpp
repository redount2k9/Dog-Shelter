//
// Created by razvan on 24.03.2018.
//

#include "UI.h"
#include "../Validators/AppError.h"
#include <iostream>
#include <limits>

void UI::printRepositoryMenu() {
    std::cout << '\n';
    std::cout << "1. Add dog\n";
    std::cout << "2. Remove dog\n";
    std::cout << "3. Update dog\n";
    std::cout << "4. Display dogs\n";
    std::cout << "5. Exit\n\n";
}

void UI::printUserMenu() {
    std::cout << '\n';
    std::cout << "1. Admin mode\n";
    std::cout << "2. User mode\n";
    std::cout << "3. Quit\n\n";
}


void UI::printUserModeMenu() {
    std::cout << "1. See all dogs, one by one\n";
    std::cout << "2. See dogs custom\n";
    std::cout << "3. See adoption list\n";
    std::cout << "4. Open adoption list\n";
    std::cout << "5. Save & quit\n\n";
}

void UI::printAdoptionMenu() {
    std::cout << "1. Adopt current dog\n";
    std::cout << "2. Next\n";
    std::cout << "3. Exit\n\n";
}

void UI::printFormatSaver() {
    std::cout << '\n';
    std::cout << "Enter the format you want the adoption list to be stored (CSV/HTML): ";
    std::string format;
    getline(std::cin, format);
    if ( format.find("HTML") == std::string::npos &&
         format.find("CSV") == std::string::npos ) {

        std::cout << "Invalid format!\n";
        printFormatSaver();
        return;
    }
    this->controller.setAdoptionListFormat(format);
}



void UI::printAddDogMenu() {
    std::cout << "Enter breed: ";
    std::string breed;
    getline(std::cin, breed);

    std::cout << "Enter name: ";
    std::string name;
    getline(std::cin, name);

    std::cout << "Enter url: ";
    std::string url;
    getline(std::cin, url);

    int age;
    while (std::cout << "Enter age: " && !(std::cin >> age)) {
        std::cout << "Incorrect age. ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    this->controller.addDogToRepository(breed, name, age, url);
    std::cout << "Dog added successfully!\n";
}

void UI::printDeleteDogMenu() {
    std::cout << "Enter breed: ";
    std::string breed;
    getline(std::cin, breed);
    std::cout << "Enter name: ";
    std::string name;
    getline(std::cin, name);

    this->controller.removeDogFromRepository(breed, name);
    std::cout << "Dog deleted successfully!\n";
}

void UI::printUpdateDogMenu() {
    std::cout << "Enter breed: ";
    std::string oldBreed;
    getline(std::cin, oldBreed);
    std::cout << "Enter name: ";
    std::string oldName;
    getline(std::cin, oldName);

    std::cout << "Enter breed: ";
    std::string newBreed;
    getline(std::cin, newBreed);

    std::cout << "Enter name: ";
    std::string newName;
    getline(std::cin, newName);

    std::cout << "Enter url: ";
    std::string url;
    getline(std::cin, url);

    int age;
    while (std::cout << "Enter age: " && !(std::cin >> age)) {
        std::cout << "Incorrect age. ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    this->controller.updateDogFromRepository(oldBreed, oldName, newBreed, newName, age, url);
    std::cout << "Dog updated successfully!\n";

}

void UI::printAllDogsMenu() {
    std::vector<Dog> dogs = controller.getDogsFromRepository();
    if (controller.getVectorSize() == 0)
        throw ControllerError(4);

    for (int i = 0; i < controller.getVectorSize(); ++i)
        std::cout << "Breed:\t" << dogs[i].getBreed() << " " << "\tName:\t" << dogs[i].getName() << "\tAge:\t"
                   << dogs[i].getAge() << "\t" << dogs[i].getPhoto() << '\n';
}

void UI::printDogsIndividually(std::string breed, int age) {
    DogListSingly list = this->controller.getDogsByBreedAndAge(breed, age);

    if (list.isEmpty())
        throw ControllerError(4);

    for ( list.start(); !list.end(); list.next() ) {
        Dog currentDog = list.getCurrentDog();

        std::cout << "Breed: " << currentDog.getBreed() << '\n';
        std::cout << "Name: " << currentDog.getName() << '\n';
        std::cout << "Age: " << currentDog.getAge() << '\n';
        currentDog.display();
        std::cout << "Image opened in browser\n\n";

        UI::printAdoptionMenu();
        int command(0);
        std::cin >> command;
        std::cin.get();
        if (command == 1) {
            if (!this->controller.addDogToAdoptionList(currentDog)) {
                std::cout << "Dog added to the adoption list\n";
                this->controller.deleteFromList(list, currentDog);
                list.previous();
                this->controller.removeDogFromRepository(currentDog.getBreed(), currentDog.getName());
            }
        }
        else if (command == 2)
            continue;
        else
            break;
    }
}

void UI::printAdoptionList() {
    AdoptionList list = this->controller.getAdoptionList();
    if ( list.isEmpty() )
        throw ControllerError(4);
    for ( list.start(); !list.end(); list.next() ) {
        Dog currentDog = list.getCurrentDog();
        std::cout << "Breed: " << currentDog.getBreed() << '\n';
        std::cout << "Name: " << currentDog.getName() << '\n';
        std::cout << "Age: " << currentDog.getAge() << '\n';
        currentDog.display();
        std::cout << "Image opened in browser\n\n";
    }
}

void UI::start() {
    UI::printFormatSaver();
    while(true) {
        try {
            UI::printUserMenu();
            int command(0);
            std::cout << ">> ";
            std::cin >> command;
            std::cin.get();
            if (command == 1) { // admin mode
                while (true) {
                    UI::printRepositoryMenu();
                    std::cout << ">> ";
                    std::cin >> command;
                    std::cin.get();
                    if (command == 1)
                        this->printAddDogMenu();
                    else if (command == 2)
                        this->printDeleteDogMenu();
                    else if (command == 3)
                        this->printUpdateDogMenu();
                    else if (command == 4)
                        this->printAllDogsMenu();
                    else if (command == 5)
                        break;
                }
            } else if (command == 2) { // user mode
                while (true) {
                    UI::printUserModeMenu();
                    std::cout << ">> ";
                    std::cin >> command;
                    std::cin.get();
                    if (command == 1)
                        this->printDogsIndividually("", -1);
                    else if (command == 2) {
                        std::cout << "Enter breed: ";
                        std::string breed;
                        getline(std::cin, breed);

                        int age;
                        while (std::cout << "Enter age: " && !(std::cin >> age)) {
                            std::cout << "Incorrect age. ";
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                        this->printDogsIndividually(breed, age);
                    }
                    else if (command == 3) {
                        this->printAdoptionList();
                    }
                    else if (command == 4) {
                        this->controller.saveAdoptionList();
                        this->controller.openAdoptionList();
                    }
                    else {
                        this->controller.saveAdoptionList();
                        break;
                    }
                }
            } else break;
        } catch(ControllerError &error) {
            std::cout << error.getMessage();
        }
        catch (ValidatonError &error1) {
            std::cout << error1.getMessage();
        }
    }

}





