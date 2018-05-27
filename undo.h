#ifndef UNDO_H
#define UNDO_H
#include "Repository/Repository.h"
#include <memory>

class UndoAction
{
public:
    explicit UndoAction();
    virtual ~UndoAction() = default;
    virtual void undo(std::vector<std::shared_ptr<UndoAction>>&) = 0;
    UndoAction(const UndoAction &) = delete;
    UndoAction& operator=(const UndoAction&) = delete;
};

class UndoAdd : public UndoAction {
public:
    UndoAdd(Repository&, const Dog&);
    void undo(std::vector<std::shared_ptr<UndoAction> > &) override;
private:
    Repository& repository;
    Dog dog;
};

class UndoDelete : public UndoAction {
public:
    UndoDelete(Repository&, const Dog&);
    void undo(std::vector<std::shared_ptr<UndoAction> > &) override;
private:
    Repository& repository;
    Dog dog;
};

class UndoUpdate: public UndoAction {
public:
    UndoUpdate(Repository&, const Dog&, const Dog&);
    void undo(std::vector<std::shared_ptr<UndoAction> > &) override;
private:
    Repository& repository;
    Dog oldDog, newDog;
};

#endif // UNDO_H
