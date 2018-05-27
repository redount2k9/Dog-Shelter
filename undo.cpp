#include "undo.h"


UndoAdd::UndoAdd(Repository & r, const Dog & d) : repository{r}, dog{d} {}

void UndoAdd::undo(std::vector<std::shared_ptr<UndoAction> > &redoList)
{
    // in order to prevent undo/redo after adding from repository to adoption list
    if (!this->repository.removeDog(dog))
        redoList.push_back(std::make_shared<UndoDelete>(repository, dog));
}

UndoDelete::UndoDelete(Repository & r, const Dog & d) : repository{r}, dog{d}{}

void UndoDelete::undo(std::vector<std::shared_ptr<UndoAction> > &redoList)
{
    this->repository.addDog(dog);
    redoList.push_back(std::make_shared<UndoAdd>(repository,dog));
}


UndoUpdate::UndoUpdate(Repository & r, const Dog & _oldDog, const Dog & _newDog) : repository{r},
    oldDog{_oldDog}, newDog{_newDog} {}

void UndoUpdate::undo(std::vector<std::shared_ptr<UndoAction> > &redoList)
{
    // in order to prevent undo/redo after adding from repository to adoption list
    if (!this->repository.updateDog(newDog, oldDog))
        redoList.push_back(std::make_shared<UndoUpdate>(repository,newDog,oldDog));
}

UndoAction::UndoAction()
{

}
