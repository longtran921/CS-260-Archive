//
// Created by ACER NITRO on 10/19/2023.
//

#ifndef UNTITLED9_CHAINHASH_HPP
#define UNTITLED9_CHAINHASH_HPP

#include <string>
#include <utility>

class ChainHash {
public:
    explicit ChainHash(int size = 7);
    ~ChainHash();

    void addItem(const std::string& value);
    bool findItem(const std::string& value);
    void removeItem(const std::string& value);
    [[nodiscard]] std::string displayTable() const;

private:
    int tableSize;
    int numItems;
    class ChainLink {
    public:
        std::string data;
        ChainLink* next;
        explicit ChainLink(std::string  val) : data(std::move(val)), next(nullptr) {}
    };
    ChainLink** table;

    [[nodiscard]] int hash(const std::string& value) const;
    void expandTable();
};

#endif