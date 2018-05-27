#include "listformatdialog.h"
#include "ui_listformatdialog.h"

ListFormatDialog::ListFormatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListFormatDialog)
{
    setWindowFlags((this->windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint);
    ui->setupUi(this);
}

ListFormatDialog::~ListFormatDialog()
{
    delete ui;
}

void ListFormatDialog::on_HTMLButton_clicked()
{
    format = "HTML";
    close();
}

void ListFormatDialog::on_CSVButton_clicked()
{
    format = "CSV";
    close();
}
