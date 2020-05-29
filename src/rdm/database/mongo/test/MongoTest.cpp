#include <iostream>

#include <catch2/catch.hpp>

#include "../MongoHeader.h"

using namespace rdm;

TEST_CASE("MongoTest", "[]") {
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{}};

    bsoncxx::builder::stream::document document{};

    auto collection = conn["testdb"]["testcollection"];
    document << "hello" << "world";

    collection.insert_one(document.view());
    auto cursor = collection.find({});

    for (auto&& doc : cursor) {
        // { "_id" : { "$oid" : "5ed154df6644f10493208512" }, "hello" : "world" }
        // std::cout << bsoncxx::to_json(doc) << std::endl;
        REQUIRE(bsoncxx::to_json(doc).size() == 70);
    }
}