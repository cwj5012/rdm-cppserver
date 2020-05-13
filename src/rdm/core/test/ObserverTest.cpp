#include <catch2/catch.hpp>

#include "../Observer.h"
#include "../Observable.h"

using namespace rdm;

struct WeatherData {
    int32_t temperature;
    int32_t humidity;
};

class Weather : public Observable<WeatherData> {
public:
    ~Weather() override = default;
};

class Board : public Observer<WeatherData> {
public:
    Board() : temperature_(0), humidity_(0) {};

    ~Board() override = default;

    void update(WeatherData data) override {
        temperature_ = data.temperature;
        humidity_ = data.humidity;
    }

    int32_t temperature_;
    int32_t humidity_;
};


TEST_CASE("Observer", "[test]") {
    WeatherData data1{};
    data1.temperature = 10;
    data1.humidity = 20;

    Weather w;
    Board b;

    w.addObserver(&b);
    w.setChanged();
    w.notifyObservers(data1);

    REQUIRE(b.temperature_ == 10);
    REQUIRE(b.humidity_ == 20);
}