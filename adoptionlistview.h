#ifndef ADOPTIONLISTVIEW_H
#define ADOPTIONLISTVIEW_H

#include <QWidget>
#include "Domain/adoptionlistmodel.h"

namespace Ui {
class AdoptionListView;
}

class AdoptionListView : public QWidget
{
    Q_OBJECT

public:
    explicit AdoptionListView(AdoptionListModel *a, QWidget *parent = 0);
    void setAdoptionListModel(AdoptionListModel *a) {
        adoptionListModel = a;
    }

    ~AdoptionListView();

private:
    AdoptionListModel* adoptionListModel;
    Ui::AdoptionListView *ui;
};

#endif // ADOPTIONLISTVIEW_H
