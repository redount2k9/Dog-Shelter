//
// Created by razvan on 26.03.2018.
//

#include <cassert>
#include <iostream>
#include <fstream>
#include "Tests.h"
#include "../Domain/Dog.h"
#include "../Repository/Repository.h"
#include "../Controller/Controller.h"
#include "../Repository/AdoptionList.h"
#include "../Validators/AppError.h"

void Tests::initialize(Controller &controller) {
    controller.addDogToRepository("German Shepherd", "Brenda", 2, "http://cdn2-www.dogtime.com/assets/uploads/gallery/german-shepherd-dog-breed-pictures/standing-7.jpg");
    controller.addDogToRepository("Labrador Retriever", "Steve", 5, "http://cdn3-www.dogtime.com/assets/uploads/gallery/labrador-retriever-dog-breed-pictures/thumbs/thumbs_labrador-retriever-dog-pictures-6.jpg");
    controller.addDogToRepository("Pug", "Mickey", 3, "https://i.redd.it/w2dyg4k71en01.jpg");
    controller.addDogToRepository("Beagle", "John", 1, "https://i.ytimg.com/vi/bx7BjjqHf2U/maxresdefault.jpg");
    controller.addDogToRepository("Chow Chow", "Albert", 2, "http://cdn1-www.dogtime.com/assets/uploads/gallery/chow-chow-dog-breed-pictures/1-face.jpg");
    controller.addDogToRepository("Husky", "Commie", 3, "http://cdn1-www.dogtime.com/assets/uploads/gallery/siberian-husky-dog-breed-pictures/siberian-husky-dog-breed-pictures-2.jpg");
    controller.addDogToRepository("Saint Bernard", "Steve", 3, "http://cdn2-www.dogtime.com/assets/uploads/gallery/saint-bernard-dogs-and-puppies/saint-bernard-dogs-puppies-2.jpg");
    controller.addDogToRepository("Doberman", "Dicky", 7, "http://www.dogbreedslist.info/uploads/allimg/dog-pictures/Doberman-Pinscher-2.jpg");
    controller.addDogToRepository("Shih Tzu", "Denis", 2, "http://cdn2-www.dogtime.com/assets/uploads/gallery/shih-tzu-dog-breed-pictures/shih-tzu-breed-picture-1.jpg");
    controller.addDogToRepository("Chihuahua", "Pziso", 7, "http://www.yourpurebredpuppy.com/dogbreeds/photos-CD/chihuahuasf1.jpg");
}

void Tests::testDog() {
    Dog d1{"German Shepherd", "Brenda", 2, "link"};
    assert(d1.getName() == "Brenda");
    assert(d1.getAge() == 2);

    Dog d2{"", "Tecsi", -2, "link"};
    assert(d2.getBreed().empty());
    assert(d2.getPhoto() == "link");

    assert(!(d1 == d2));
    assert(d1 == d1);

    d2.display();
}

void Tests::testRepository() {
    Repository repository;
    Dog d1{"German Shepherd", "Brenda", 2, "google_link"};
    repository.addDog(d1);
    repository.addDog(d1);
    assert(repository.getVectorSize() == 2);
    assert(repository.getAllDogs()[0].getName() == "Brenda");

    Dog d2{"Labrador Retriever", "Steve", 5, "link"};
    Dog d3{"Pug", "Mickey", 3, "img_link"};
    repository.addDog(d2);
    repository.addDog(d3);

    assert(repository.getVectorSize() == 4);
    assert(repository.getAllDogs()[2].getAge() == 5);

    Dog current_dog = repository.findDogByBreedAndName("Labrador Retriever", "Steve");
    assert(current_dog.getAge() == d2.getAge());
    assert(current_dog == d2);
    assert(current_dog.getAge() == repository.getAllDogs()[2].getAge());

    repository.removeDog(current_dog);
    assert(repository.getVectorSize() == 3);

    Dog invalid_dog = repository.findDogByBreedAndName("Breed", "Mickey");
    assert(invalid_dog.getName().empty());

    assert(!repository.updateDog(d3, d2));
    assert(repository.getAllDogs()[1].getName() == "Brenda");
    assert(repository.updateDog(d3, d1));

    Repository repo;
    repo.findDogByBreedAndName("I", "a");

}


void Tests::testController() {
    Repository repository;
    AdoptionList l;
    Controller controller(repository, l);

    controller.addDogToRepository("Labrador", "Guci", 4, "https://www.google.com/image/");
    try{
        controller.addDogToRepository("Labrador", "Guci", 4, "https://www.google.com/image/");
    } catch (ControllerError& ce) {}

    controller.addDogToRepository("Poodle", "John", 1, "www.ceva.com");
    assert(controller.getVectorSize() == 2);

    controller.addDogToRepository("Pug", "Mickey", 7, "www.asta.com");

    try {
        controller.removeDogFromRepository("Rasa", "Nume");
    } catch (...) {}
    controller.removeDogFromRepository("Labrador", "Guci");


    try {
        controller.updateDogFromRepository("Poodle", "John", "Sheppard", "Leonard", 2, "");
    } catch (...) {}

    controller.updateDogFromRepository("Pug", "Mickey", "", "Rocky", 8, "www.anotherli");
    assert(controller.getDogsFromRepository()[1].getBreed() == "Pug");
    assert(controller.getDogsFromRepository()[1].getName() == "Rocky");
    try {
        controller.updateDogFromRepository("Pug", "Rocky", "Doberman", "", -1, "link");
    }catch(ValidatonError &ve) {}

    try {
        controller.updateDogFromRepository("Pug", "Mickey", "Pug", "Mickey", 2, "linkwww");
    }catch (ControllerError &ce) {
        assert(ce.getMessage() == "Could not update dog\n");
    };

    assert(controller.getDogsFromRepository()[1].getBreed() == "Pug");
    assert(controller.getDogsFromRepository()[1].getAge() == 8);


}

void Tests::testController2nd() {
    Repository repository;
    AdoptionList l;
    Controller controller(repository, l);
    initialize(controller);

    DogListSingly dogs = controller.getDogsByBreedAndAge("", 3);
    assert(dogs.getList().size() == 4);
    assert(dogs.getList()[2] == controller.getDogsFromRepository()[4]);
    Dog dog = dogs.getList()[1];
    controller.deleteFromList(dogs, dog);
    assert(dogs.getList().size() == 3);

    dogs = controller.getDogsByBreedAndAge("Pug", 5);
    assert(dogs.getList().size() == 1);

    controller.addDogToAdoptionList(controller.getDogsFromRepository()[2]);
    assert(controller.isAdopted(controller.getDogsFromRepository()[2]));
    assert(!controller.isAdopted(controller.getDogsFromRepository()[6]));

    controller.addDogToAdoptionList(controller.getDogsFromRepository()[5]);
    controller.deleteDogFromAdoptionList(controller.getDogsFromRepository()[2]);
    assert(controller.getAdoptionList().getList()[0] == controller.getDogsFromRepository()[5]);
    assert(controller.getVectorSize() == 10);

    std::vector<Dog> d = controller.getDogsFromRepository();
    controller.filterAdoptedDogs(d);

}

void Tests::testLists() {
    Repository repository;
    AdoptionList l;
    Controller controller(repository, l);
    initialize(controller);


    DogListSingly dogList;
    dogList.add(controller.getDogsFromRepository()[1]);
    dogList.add(controller.getDogsFromRepository()[2]);
    dogList.add(controller.getDogsFromRepository()[3]);

    int i = 1;
    for(dogList.start(); !dogList.end(); dogList.next()) {
        assert(dogList.getCurrentDog() == controller.getDogsFromRepository()[i]);
        i++;
        if ( i == 3 ) break;
    }

    AdoptionList list;
    list.add(controller.getDogsFromRepository()[1]);
    list.add(controller.getDogsFromRepository()[2]);
    list.add(controller.getDogsFromRepository()[3]);

    i = 1;
    for(list.start(); !list.end(); list.next()) {
        assert(list.getCurrentDog() == controller.getDogsFromRepository()[i]);
        i++;
    }

    AdoptionList ls;
    try {
        if (ls.isEmpty())
            throw ControllerError(4);
    }catch(...) {}
    for(ls.start(); !ls.end(); ls.next());

    DogListSingly dg;
    for(dg.start(); !dg.end(); dg.next());

}

void Tests::testValidator() {
    Validator v;
    try {
        v.validateDog("Beagle", "John", 22, "www.google.com");
    }catch(ValidatonError &ve) {
        assert(ve.getMessage() == "Age is not in a valid range\n");
    }
    try {
        v.validateDog("", "", 2, "");
    }catch(ValidatonError &ve) {
        assert(ve.getMessage() == "Breed cannot be empty\nName cannot be empty\nLink cannot be empty\n");
    }
    v.validateDog("Pug", "Mick", 3, "validwwwlink");


    std::ifstream fin("a", std::ios::in);
    try {
        if (!fin.is_open())
            throw FileError(1);
    }catch (FileError &fe){};

}


void Tests::testAll() {
    testDog();
    testRepository();
    testController();
    testController2nd();
    testLists();
    testValidator();
}









