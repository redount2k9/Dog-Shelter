//
// Created by razvan on 08.04.2018.
//

#ifndef LAB5_6_FILEREPOSITORY_H
#define LAB5_6_FILEREPOSITORY_H

#include "Repository.h"
#include <fstream>

class FileRepository : public Repository {
public:
    // Class constructor
    explicit FileRepository(std::string);
    // Class destructor
    ~FileRepository();
    // Function which overrides the corresponding function from Repository
    int addDog(const Dog& dog) override;
    // Function which overrides the corresponding function from Repository
    int removeDog(const Dog& dog) override;
    // Function which overrides the corresponding function from Repository
    int updateDog(const Dog& oldDog, const Dog& newDog) override;
    // Function which writes the repository content to file
    void write();
private:
    // the name of the file from which we want to read the repository content
    std::string filename;
    // Function which reads the repository content from a file
    void read();
};



#endif //LAB5_6_FILEREPOSITORY_H
