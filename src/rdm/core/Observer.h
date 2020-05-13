/**
 * Observer class
 *
 * not thread safe
 *
 * when the Observable change, the update method will be call
 * data type is template TData
 *
 */

#pragma once

namespace rdm {

template<typename TData>
class Observable;

template<typename TData>
class Observer {
public:
    Observer() = default;

    virtual ~Observer() = default;

    virtual void update(TData data) = 0;
};

}


