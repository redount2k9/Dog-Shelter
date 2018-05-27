#include "mywindow.h"
#include "ui_mywindow.h"
#include "string.hpp"
#include "listformatdialog.h"
#include <iostream>

MyWindow::MyWindow(Controller &c, QWidget *parent) : controller(c), QWidget(parent), ui(new Ui::MyWindow)
{
    ui->setupUi(this);
    this->initGUI();
    formatDialog = new ListFormatDialog(this);
    formatDialog->exec();
    this->connectAll();
}


MyWindow::~MyWindow()
{
    delete ui;
}

void MyWindow::initGUI()
{
    QHBoxLayout *horizontalLayout = new QHBoxLayout(this);
    QVBoxLayout *leftVLayout = new QVBoxLayout();
    QVBoxLayout *rightVLayout = new QVBoxLayout();
    QVBoxLayout *centralVLayout = new QVBoxLayout();

    QLabel *informationLabel = new QLabel("Dogs");
    QLabel *breedLabel = new QLabel("Breed");
    QLabel *nameLabel = new QLabel("Name");
    QLabel *ageLabel = new QLabel("Age");
    QLabel *linkLabel = new QLabel("Link");

    showComboBox = new QComboBox();

    showComboBox->addItem("Detailed");
    showComboBox->addItem("Short");

    QLabel *filterBreedLabel = new QLabel("Breed");
    QLabel *filterAgeLabel = new QLabel("Age");

    breedLineEdit = new QLineEdit();
    nameLineEdit = new QLineEdit();
    ageLineEdit = new QLineEdit();
    linkLineEdit = new QLineEdit();
    filterBreedLineEdit = new QLineEdit();
    filterAgeLineEdit = new QLineEdit();

    QVBoxLayout *leftInputVerticalLayout = new QVBoxLayout();
    QHBoxLayout *horizontalBreedLayout = new QHBoxLayout();
    QHBoxLayout *horizontalNameLayout = new QHBoxLayout();
    QHBoxLayout *horizontalAgeLayout = new QHBoxLayout();
    QHBoxLayout *horizontalLinkLayout = new QHBoxLayout();

    QHBoxLayout *horizontalFilterBreedLayout = new QHBoxLayout();
    QHBoxLayout *horizontalFilterAgeLayout = new QHBoxLayout();

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    QHBoxLayout *buttonsLayoutUndo = new QHBoxLayout();
    QHBoxLayout *dogListButtonsLayout = new QHBoxLayout();

    horizontalBreedLayout->addWidget(breedLabel);
    horizontalBreedLayout->addWidget(breedLineEdit);

    leftInputVerticalLayout->addLayout(horizontalBreedLayout);

    horizontalNameLayout->addWidget(nameLabel);
    horizontalNameLayout->addWidget(nameLineEdit);

    leftInputVerticalLayout->addLayout(horizontalNameLayout);

    horizontalAgeLayout->addWidget(ageLabel);
    horizontalAgeLayout->addWidget(ageLineEdit);

    leftInputVerticalLayout->addLayout(horizontalAgeLayout);

    horizontalLinkLayout->addWidget(linkLabel);
    horizontalLinkLayout->addWidget(linkLineEdit);

    leftInputVerticalLayout->addLayout(horizontalLinkLayout);

    this->list = new QListWidget();

    leftVLayout->addWidget(informationLabel);
    leftVLayout->addWidget(showComboBox);
    leftVLayout->addWidget(this->list);
    leftVLayout->addLayout(leftInputVerticalLayout);

    this->addButton = new QPushButton("Add");
    this->deleteButton = new QPushButton("Delete");
    this->updateButton = new QPushButton("Update");
    this->saveButton = new QPushButton("Save");
    this->viewContentButton = new QPushButton("View Content");
    this->viewContentButton->setStyleSheet("color: blue;");
    this->undoButton = new QPushButton("Undo");
    this->undoButton->setStyleSheet("background-color: #f320f0; color: #003300;");
    this->redoButton = new QPushButton("Redo");
    this->redoButton->setStyleSheet("background-color: #99ff33; color: #993399;");

    buttonsLayout->addWidget(this->addButton);
    buttonsLayout->addWidget(this->deleteButton);
    buttonsLayout->addWidget(this->updateButton);

    buttonsLayoutUndo->addWidget(this->undoButton);
    buttonsLayoutUndo->addWidget(this->redoButton);

    leftVLayout->addLayout(buttonsLayout);
    leftVLayout->addLayout(buttonsLayoutUndo);

    QVBoxLayout *leftFilterVerticalLayout = new QVBoxLayout();

    horizontalFilterBreedLayout->addWidget(filterBreedLabel);
    horizontalFilterBreedLayout->addWidget(filterBreedLineEdit);

    leftFilterVerticalLayout->addLayout(horizontalFilterBreedLayout);

    horizontalFilterAgeLayout->addWidget(filterAgeLabel);
    horizontalFilterAgeLayout->addWidget(filterAgeLineEdit);

    leftFilterVerticalLayout->addLayout(horizontalFilterAgeLayout);

    this->filterButton = new QPushButton("Filter");

    leftFilterVerticalLayout->addWidget(this->filterButton);

    leftVLayout->addLayout(leftFilterVerticalLayout);
    horizontalLayout->addLayout(leftVLayout);

    QLabel *adoptionLabel = new QLabel("Adoption List");

    this->adoptionList = new QListWidget();
    this->adoptionList->setSelectionMode(QAbstractItemView::NoSelection);

    rightVLayout->addWidget(adoptionLabel);
    rightVLayout->addWidget(this->adoptionList);
    rightVLayout->addWidget(this->saveButton);
    rightVLayout->addWidget(this->viewContentButton);

    this->nextButton = new QPushButton("Next");
    this->displayButton = new QPushButton("Display");

    dogListButtonsLayout->addWidget(this->displayButton);
    dogListButtonsLayout->addWidget(this->nextButton);

    this->transferButton = new QPushButton(">");

    singleDogTextEdit = new QTextEdit();
    singleDogTextEdit->setFixedWidth(300);
    singleDogTextEdit->setReadOnly(true);

    centralVLayout->addWidget(singleDogTextEdit);
    centralVLayout->addWidget(transferButton);
    centralVLayout->addLayout(dogListButtonsLayout);

    horizontalLayout->addLayout(centralVLayout);
    horizontalLayout->addLayout(rightVLayout);

    populateList(controller.getDogsFromRepository(), true);
    updateDogListSingly();
    populateDogListSingly(dogList);
}

void MyWindow::clearFields()
{
    breedLineEdit->clear();
    nameLineEdit->clear();
    ageLineEdit->clear();
    linkLineEdit->clear();
}



void MyWindow::connectAll()
{
    connect(this->addButton, &QPushButton::clicked, this, [this]() {
        std::string breed = breedLineEdit->text().toStdString();
        std::string name = nameLineEdit->text().toStdString();
        int age = ageLineEdit->text().toInt(nullptr, 10);
        std::string link = linkLineEdit->text().toStdString();

        try {
        controller.addDogToRepository(breed, name, age, link, true);
        clearFields();

        } catch(AppError &e ) {
            QString error = QString::fromStdString("Error");
            QString msg = QString::fromStdString(e.getMessage());
            QMessageBox errorBox(QMessageBox::Warning, error, msg);
            errorBox.exec();
       }
        updateDogListSingly();
        populateList(controller.getDogsFromRepository(), true);
    });

    connect(this->deleteButton, &QPushButton::clicked, this, [this]() {


        try {
        std::vector<std::string> values = getCurrentItemValues(list);
        Dog dog = controller.findDog(values[0], values[1]);
        controller.deleteFromList(*dogList, dog);
        controller.removeDogFromRepository(values[0], values[1], true);
        clearFields();

        } catch(AppError &e) {
            QString error = QString::fromStdString("Error");
            QString msg = QString::fromStdString(e.getMessage());
            QMessageBox errorBox(QMessageBox::Warning, error, msg);
            errorBox.exec();
        }
        updateDogListSingly();
        populateList(controller.getDogsFromRepository(), true);
    });

    connect(this->updateButton, &QPushButton::clicked, this, [this]() {

        std::string breed = breedLineEdit->text().toStdString();
        std::string name = nameLineEdit->text().toStdString();
        int age = ageLineEdit->text().toInt(nullptr, 10);
        std::string link = linkLineEdit->text().toStdString();

        try {
        std::vector<std::string> values = getCurrentItemValues(list);
        controller.updateDogFromRepository(values[0], values[1], breed, name, age, link, true);
        clearFields();
        } catch(AppError &e) {
            QString error = QString::fromStdString("Error");
            QString msg = QString::fromStdString(e.getMessage());
            QMessageBox errorBox(QMessageBox::Warning, error, msg);
            errorBox.exec();
        }
        updateDogListSingly();
        populateList(controller.getDogsFromRepository(), true);
    });

    connect(this->filterButton, &QPushButton::clicked, this, [this]() {
        std::string breed = filterBreedLineEdit->text().toStdString();
        int age = filterAgeLineEdit->text().toInt(nullptr, 10);

        DogListSingly* ds = new DogListSingly{controller.getDogsByBreedAndAge(breed, age)};
        this->dogList = ds;
        populateDogListSingly(dogList);

    });

    connect(this->transferButton, &QPushButton::clicked, this, [this]() {
        try {
            Dog currentDog = dogList->getCurrentDog();
            controller.addDogToAdoptionList(currentDog);
            controller.removeDogFromRepository(currentDog.getBreed(), currentDog.getName(), false);
            controller.deleteFromList(*dogList, currentDog);
            dogList->next();
            populateDogListSingly(dogList);
            controller.clearRedo();
        } catch(AppError &e) {
            QString error = QString::fromStdString("Error");
            QString msg = QString::fromStdString(e.getMessage());
            QMessageBox errorBox(QMessageBox::Warning, error, msg);
            errorBox.exec();
        }

        populateAdoptionList();
        populateList(controller.getDogsFromRepository(),true);
    });

    connect(this->list, &QListWidget::itemClicked, this, [this]() {
        std::vector<std::string> values = getCurrentItemValues(list);

        breedLineEdit->setText(QString::fromStdString(values[0]));
        nameLineEdit->setText(QString::fromStdString(values[1]));
        ageLineEdit->setText(QString::fromStdString(values[2]));
        linkLineEdit->setText(QString::fromStdString(values[3]));
    });

    connect(this->displayButton, &QPushButton::clicked, this, [this]() {
        std::vector<std::string> values = getCurrentSingleDogValues(singleDogTextEdit);
        controller.openPhoto(values[3]);
    });

    connect(this->nextButton, &QPushButton::clicked, this, [this]() {
       dogList->next();
       populateDogListSingly(dogList);
    });

    connect(this->saveButton, &QPushButton::clicked, this, [this]() {
         controller.setAdoptionListFormat(formatDialog->getFormat());
         controller.saveAdoptionList();
         controller.openAdoptionList();
    });

    connect(this->showComboBox, &QComboBox::currentTextChanged, this, [this]() {
        if (this->showComboBox->currentText() == "Short") {
            populateList(controller.getDogsFromRepository(), false);
        } else {
            populateList(controller.getDogsFromRepository(), true);
        }
    });

    connect(this->viewContentButton, &QPushButton::clicked, this, [this]() {
       adoptionModel = new AdoptionListModel{this->controller.getAdoptionList()};
       adoptionView = new AdoptionListView{adoptionModel};
       adoptionView->show();
    });

    connect(this->undoButton, &QPushButton::clicked, this, [this]() {
        this->controller.undo();
        updateDogListSingly();
        populateList(controller.getDogsFromRepository(), true);
    });

    connect(this->redoButton, &QPushButton::clicked, this, [this]() {
        this->controller.redo();
        updateDogListSingly();
        populateList(controller.getDogsFromRepository(), true);
    });
}

std::vector<std::__cxx11::string> MyWindow::getCurrentItemValues(QListWidget *list)
{
    QListWidgetItem* selectedItem = list->currentItem();
    if ( selectedItem == nullptr )
        throw ControllerError(5);
    std::string text = selectedItem->text().toStdString();

    std::vector<std::string> values;

    boost::split(values, text, [](char c) {
        return c == ',';
    });

    return values;
}

void MyWindow::populateList(std::vector<Dog> dogs, bool longFormat) {
    list->clear();
    std::string dogTxt;
    for ( auto dog : dogs ) {
        if (longFormat)
            dogTxt = dog.toString();
        else
            dogTxt = dog.toShortString();
        list->addItem(QString::fromStdString(dogTxt));
    }
    if (!longFormat)
        list->setDisabled(true);
    else
        list->setEnabled(true);

}

void MyWindow::populateAdoptionList()
{
    adoptionList->clear();
    for ( auto dog : controller.getAdoptionList().getList() ) {
        adoptionList->addItem(QString::fromStdString(dog.toString()));
    }

}

void MyWindow::populateDogListSingly(DogListSingly* dls)
{
    singleDogTextEdit->clear();
    if (!dls->isEmpty())
        singleDogTextEdit->setText(QString::fromStdString(dls->getCurrentDog().toString()));

}

void MyWindow::updateDogListSingly()
{
    dogList = new DogListSingly{};
    for (auto dog : controller.getDogsFromRepository())
        dogList->add(dog);
}

std::vector<std::string> MyWindow::getCurrentSingleDogValues(QTextEdit *edit)
{
    std::string text = edit->toPlainText().toStdString();
    std::vector<std::string> values;

    boost::split(values, text, [](char c) {
        return c == ',';
    });

    return values;
}
