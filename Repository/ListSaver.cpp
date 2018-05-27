//
// Created by razvan on 26.04.2018.
//

#include "ListSaver.h"

CSVListSaver::CSVListSaver(AdoptionList &list) : adoptionList(list) {}

void CSVListSaver::saveToFile() {
    std::ofstream fout("savedList.csv", std::ios::out | std::ios::trunc);

    std::vector<Dog> list = this->adoptionList.getList();

    std::for_each(list.begin(), list.end(), [&fout](const Dog& dog) {
        fout << dog << '\n';
    });

    fout.close();
}

void CSVListSaver::open() {
    system("gedit savedList.csv");
}


HTMLListSaver::HTMLListSaver(AdoptionList &list) : adoptionList(list) {}


void HTMLListSaver::saveToFile() {
    std::ofstream fout("savedList.html", std::ios::out | std::ios::trunc );

    std::vector<Dog> list = this->adoptionList.getList();

    fout << "<!DOCTYPE html>\n<html>\n\t<head>\n\t\t<title>Adoption list</title>\n</head>\n";
    fout << "<body>\n\t\t<table border=\"1\">\n\t\t<tr>\n";
    fout << "\t\t\t<td>Breed</td>\n\t\t\t<td>Name</td>\n\t\t\t<td>Age</td>\n\t\t\t<td>Link</td>\n";
    fout << "\t\t</tr>\n";

    std::for_each(list.begin(), list.end(), [&fout](const Dog& dog) {
        fout << "\t\t<tr>\n\t\t\t<td>" << dog.getBreed() << "</td>\n\t\t\t<td>" << dog.getName() << "</td>\n\t\t\t<td>"\
             << dog.getAge() << "</td>\n\t\t\t<td><a href=\"" << dog.getPhoto() << "\"/>Link</td>\n\t\t</tr>";
    });

    fout << "\t\t\t</table>\n\t</body>\n</html>\n";
}

void HTMLListSaver::open() {
    system("firefox savedList.html");
}


