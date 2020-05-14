#include "SortedSet.h"

namespace rdm {

int SortedSet::size() const {
    return sortedSet_.size();
}

int SortedSet::add(const std::string& key, int64_t score) {
    int ret = 0;
    auto it = existed_.find(key);
    if (it == existed_.end()) {
        ret = 1;
    } else {
        auto it2 = it->second;
        if (it2->score == score) {
            return ret;
        }
        sortedSet_.erase(it2);
    }

    Item item{.key = key, .score=score};
    auto p = sortedSet_.insert(item);
    existed_[key] = p.first;

    return ret;
}

int SortedSet::del(const std::string& key) {
    int ret = 0;
    auto it = existed_.find(key);
    if (it != existed_.end()) {
        ret = 1;
        sortedSet_.erase(it->second);
        existed_.erase(it);
    }
    return ret;
}

int SortedSet::front(std::string* key, int64_t* score) const {
    auto it = sortedSet_.begin();
    if (it == sortedSet_.end()) {
        return 0;
    }
    *key = it->key;
    if (score) {
        *score = it->score;
    }
    return 1;
}

int SortedSet::back(std::string* key, int64_t* score) const {
    auto it = sortedSet_.rbegin();
    if (it == sortedSet_.rend()) {
        return 0;
    }
    *key = it->key;
    if (score) {
        *score = it->score;
    }
    return 1;
}

int64_t SortedSet::max_score() const {
    int64_t score = 0;
    std::string key;
    back(&key, &score);
    return score;
}

int SortedSet::pop_front() {
    if (sortedSet_.empty()) {
        return 0;
    }
    auto it = sortedSet_.begin();
    existed_.erase(it->key);
    sortedSet_.erase(it);
    return 1;
}

int SortedSet::pop_back() {
    if (sortedSet_.empty()) {
        return 0;
    }
    auto it = sortedSet_.end();
    it--;
    existed_.erase(it->key);
    sortedSet_.erase(it);
    return 1;
}

}