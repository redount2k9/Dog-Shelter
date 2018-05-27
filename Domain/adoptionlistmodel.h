#ifndef ADOPTIONLISTMODEL_H
#define ADOPTIONLISTMODEL_H
#include <QAbstractTableModel>
#include "../Repository/AdoptionList.h"

class AdoptionListModel : public QAbstractTableModel
{
public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& parent = QModelIndex(), int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    AdoptionListModel(AdoptionList& );
private:
    AdoptionList& adoptionList;
};

#endif // ADOPTIONLISTMODEL_H
