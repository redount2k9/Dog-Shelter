//
// Created by razvan on 26.04.2018.
//

#ifndef LAB5_6_LISTSAVER_H
#define LAB5_6_LISTSAVER_H
#include <fstream>
#include <algorithm>
#include "AdoptionList.h"

class ListSaver {
public:
    // Class constructor
    virtual ~ListSaver() = default;
    // Function which saves repository content to file
    virtual void saveToFile() = 0;
    // Function which opens the adoption list using the appropriate app
    virtual void open() = 0;
};

class CSVListSaver : public ListSaver {
public:
    // Class constructor
    explicit CSVListSaver(AdoptionList &);
    // Function which saves repository content to a CSV file
    void saveToFile() override;
    // Function which opens the adoption list with text editor
    void open() override;
private:
    AdoptionList &adoptionList;
};

class HTMLListSaver : public ListSaver {
public:
    // Class constructor
    explicit HTMLListSaver(AdoptionList &);
    // Function which saves repository content to a HTML file
    void saveToFile() override;
    // Function which opens the adoption list with firefox
    void open() override;
private:
    AdoptionList &adoptionList;
};


#endif //LAB5_6_LISTSAVER_H
