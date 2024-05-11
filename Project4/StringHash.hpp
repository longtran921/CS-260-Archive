//
// Created by ACER NITRO on 10/19/2023.
//

#ifndef UNTITLED9_STRINGHASH_HPP
#define UNTITLED9_STRINGHASH_HPP

#include <string>

class StringHash {
public:
    StringHash(int size = 11);
    ~StringHash();

    void addItem(const std::string& value);
    bool findItem(const std::string& value);
    void removeItem(const std::string& value);
    std::string displayTable() const;

private:
    int tableSize;
    std::string* table;
    const std::string empty = "_empty_";
    const std::string deleted = "_deleted_";

    int hash(const std::string& value) const;
};


#endif //UNTITLED9_STRINGHASH_HPP
