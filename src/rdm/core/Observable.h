#pragma once

#include <vector>
#include <cstdint>

#include "Observer.h"

namespace rdm {

template<typename TData>
class Observable {
public:
    Observable();

    virtual ~Observable();

    void addObserver(Observer <TData>* o);

    void deleteObserver(Observer <TData>* o);

    void deleteObservers();

    void notifyObservers();

    void notifyObservers(TData data);

    void setChanged();

    void clearChanged();

    bool getChanged();

    int32_t countObservers();

private:
    bool changed_;
    std::vector<Observer < TData>*>
    obs_;
};

/////////////////////////////////////////////////
// define
/////////////////////////////////////////////////

template<typename TData>
Observable<TData>::Observable()
        :changed_(false) {
}

template<typename TData>
Observable<TData>::~Observable() {
    obs_.clear();
}

template<typename TData>
void Observable<TData>::addObserver(Observer <TData>* o) {
    if (o == nullptr) {
        return;
    }

    auto it = std::find(obs_.begin(), obs_.end(), o);
    if (it == obs_.end()) {
        obs_.push_back(o);
    }
}

template<typename TData>
void Observable<TData>::deleteObserver(Observer <TData>* o) {
    auto it = std::find(obs_.begin(), obs_.end(), o);
    if (it != obs_.end()) {
        obs_.erase(it);
    }
}

template<typename TData>
void Observable<TData>::deleteObservers() {
    obs_.clear();
}

template<typename TData>
void Observable<TData>::notifyObservers() {
    notifyObservers(0);
}

template<typename TData>
void Observable<TData>::notifyObservers(TData data) {
    if (!changed_) {
        return;
    }

    clearChanged();
    for (auto o : obs_) {
        o->update(data);
    }
}

template<typename TData>
void Observable<TData>::setChanged() {
    changed_ = true;
}

template<typename TData>
void Observable<TData>::clearChanged() {
    changed_ = false;
}

template<typename TData>
bool Observable<TData>::getChanged() {
    return changed_;
}

template<typename TData>
int32_t Observable<TData>::countObservers() {
    return static_cast<int32_t>(obs_.size());
}

}