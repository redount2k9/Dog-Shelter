//
// Created by razvan on 24.03.2018.
//

#ifndef LAB5_6_CONTROLLER_H
#define LAB5_6_CONTROLLER_H


#include "../Repository/Repository.h"
#include "../Repository/AdoptionList.h"
#include "../Validators/AppError.h"
#include "../Repository/ListSaver.h"
#include "../undo.h"
#include <memory>

class Controller {
protected:
    Repository& repository;
    AdoptionList& adoptionList;
    Validator validator;
    std::shared_ptr<ListSaver> listSaver;
    std::vector<std::shared_ptr<UndoAction>> history;
    std::vector<std::shared_ptr<UndoAction>> history2;
public:
    // Class constructor
    explicit Controller(Repository& repo, AdoptionList& list) : repository(repo), adoptionList(list) {}
    //Controller(const Controller& c);
    // Adds a dog to the repository
    void addDogToRepository(std::string breed,
                            std::string name,
                            int age,
                            std::string url_photo,
                            bool undo = false);
    // Adds a dog to the adoption list
    int addDogToAdoptionList(const Dog& dog);
    // Removes a dog from the adoption list
    int deleteDogFromAdoptionList(const Dog& dog);
    // Removes a dog identified by its breed and name from the repository
    void removeDogFromRepository(std::string breed,
                                 std::string name,
                                 bool undo = false);
    // Updates a dog from repository
    void updateDogFromRepository(std::string oldBreed,
                                std::string oldName,
                                std::string newBreed,
                                std::string newName,
                                int age,
                                std::string url_photo,
                                bool undo = false);
    // Returns the list of dogs (as a pointer to the first element)
    std::vector<Dog> getDogsFromRepository();
    // Returns the size of the vector
    int getVectorSize();
    // Filters the vector by removing adopted dogs
    void filterAdoptedDogs(std::vector<Dog>&);
    // Deletes the dog object from the DogListSingly object
    void deleteFromList(DogListSingly&, Dog&);
    // Returns a DogListSingly object containing the dogs which meet the breed and age criteria
    DogListSingly getDogsByBreedAndAge(std::string breed, int age);
    // Checks if a dog is adopted
    bool isAdopted(const Dog& dog) const;
    // Returns the adoption list
    AdoptionList& getAdoptionList() const {
        return adoptionList;
    }
    void openAdoptionList() {
        this->listSaver->open();
    }
    void setAdoptionListFormat(const std::string& format);
    void saveAdoptionList() {
        listSaver->saveToFile();
    }
    Dog createDog(std::vector<std::string> vec);
    Dog findDog(std::string breed, std::string name) {
        return repository.findDogByBreedAndName(breed, name);
    }

    void openPhoto(std::string url);
    void undo();
    void redo();
    void clearRedo() {
        history2.clear();
    }
};


#endif //LAB5_6_CONTROLLER_H
