/*
 * 观察者模式，主题基类
 */

#pragma once

namespace rdm {

template<typename T>
class Subject : public T {
public:
    typedef T SubjectType;

    virtual ~Subject() = default;

    virtual void onChange() = 0;
};

}