#pragma once

#include <string>
#include <map>
#include <set>

namespace rdm {

class SortedSet {
public:
    bool empty() const { return size() == 0; }
    int size() const;
    int add(const std::string& key, int64_t score);
    int del(const std::string& key);
    int front(std::string* key, int64_t* score = nullptr) const;
    int back(std::string* key, int64_t* score = nullptr) const;
    int64_t max_score() const;
    int pop_front();
    int pop_back();

private:
    struct Item {
        std::string key;
        int64_t score;
        bool operator<(const Item& b) const {
            return score < b.score || (score == b.score && key < b.key);
        }
    };

    std::map<std::string, std::set<Item>::iterator> existed_;
    std::set<Item> sortedSet_;
};

}
