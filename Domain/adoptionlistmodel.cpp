#include "adoptionlistmodel.h"

AdoptionListModel::AdoptionListModel(AdoptionList& a) : adoptionList(a) {}

int AdoptionListModel::rowCount(const QModelIndex &parent) const
{
    return adoptionList.getList().size();
}

int AdoptionListModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant AdoptionListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int column = index.column();

    auto dogs = adoptionList.getList();
    Dog dog = dogs[row];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch(column) {
            case 0:
                return QString::fromStdString(dog.getBreed());
            case 1:
                return QString::fromStdString(dog.getName());
            case 2:
                return QString::number(dog.getAge());
            case 3:
                return QString::fromStdString(dog.getPhoto());
            default:
                break;
        }
    }
    return QVariant();
}

QVariant AdoptionListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
          return QVariant();
     if (orientation == Qt::Horizontal) {
         switch(section) {
           case 0:
             return "Breed";
           case 1:
             return "Name";
           case 2:
             return "Age";
           case 3:
             return "Link";
         }
     }

     return QVariant();
}




