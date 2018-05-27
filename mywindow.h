#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QtWidgets>
#include "Controller/Controller.h"
#include "Domain/adoptionlistmodel.h"
#include "adoptionlistview.h"
#include "listformatdialog.h"

namespace Ui {
    class MyWindow;
}

//The window class
class MyWindow : public QWidget
{
    Q_OBJECT
public:
    //The constructor
    explicit MyWindow(Controller &controller, QWidget *parent = 0);
    ~MyWindow();
signals:

public slots:

private:
    Controller controller;
    QListWidget *list;
    QListWidget *adoptionList;
    QLineEdit *breedLineEdit;
    QLineEdit *nameLineEdit;
    QLineEdit *ageLineEdit;
    QLineEdit *linkLineEdit;
    QLineEdit *filterBreedLineEdit;
    QLineEdit *filterAgeLineEdit;
    QTextEdit *singleDogTextEdit;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *updateButton;
    QPushButton *displayButton;
    QPushButton *nextButton;
    QPushButton *transferButton;
    QPushButton *filterButton;
    QPushButton *saveButton;
    QPushButton *viewContentButton;
    QPushButton *undoButton;
    QPushButton *redoButton;
    DogListSingly *dogList;
    QDialog *saveDialog;
    ListFormatDialog *formatDialog;
    QComboBox *showComboBox;
    AdoptionListModel *adoptionModel;
    AdoptionListView *adoptionView;
    Ui::MyWindow *ui;
    //Function which initializes the GUI
    void initGUI();
    //Function which clears the input fields
    void clearFields();
    //Function which populates the QListWidget object
    void populateList(std::vector<Dog>, bool);
    //Function which makes all signal-slots connections
    void connectAll();
    //Function which retrieves the values from the item currently selected, which belongs to the QListWidget given as parameter
    std::vector<std::string> getCurrentItemValues(QListWidget *);
    //Function which populates the adoption list
    void populateAdoptionList();
    //Function which populates the one-by-one view
    void populateDogListSingly(DogListSingly*);

    void updateDogListSingly();
    //Function which retrieves the values from the one-by-one view
    std::vector<std::string> getCurrentSingleDogValues(QTextEdit* );
};

#endif // MYWINDOW_H
