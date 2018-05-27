#ifndef LISTFORMATDIALOG_H
#define LISTFORMATDIALOG_H

#include <QDialog>
#include <QString>
namespace Ui {
class ListFormatDialog;
}

class ListFormatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ListFormatDialog(QWidget *parent = 0);
    ~ListFormatDialog();
    std::string getFormat() {
        return format.toStdString();
    }

private slots:
    void on_HTMLButton_clicked();

    void on_CSVButton_clicked();

private:
    Ui::ListFormatDialog *ui;
    QString format;
};

#endif // LISTFORMATDIALOG_H
