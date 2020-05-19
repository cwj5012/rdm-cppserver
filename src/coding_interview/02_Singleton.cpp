/**
 * 面试题2：实现 Singleton 模式
 */

#include <catch2/catch.hpp>

class Singleton {
public:
    static Singleton& Instance() {
        static Singleton instance;
        return instance;
    }

    Singleton(Singleton const&) = delete;               // Copy construct
    Singleton(Singleton&&) = delete;                    // Move construct
    Singleton& operator=(Singleton const&) = delete;    // Copy assign
    Singleton& operator=(Singleton&&) = delete;         // Move assign

protected:
    Singleton() = default;
    ~Singleton() = default;
};
