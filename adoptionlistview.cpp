#include "adoptionlistview.h"
#include "ui_adoptionlistview.h"

AdoptionListView::AdoptionListView(AdoptionListModel *a, QWidget *parent) :
    QWidget(parent),
    adoptionListModel(a),
    ui{new Ui::AdoptionListView}
{
    ui->setupUi(this);
    ui->tableView->setModel(adoptionListModel);
    ui->tableView->resizeColumnsToContents();
}

AdoptionListView::~AdoptionListView()
{
    delete ui;
}
