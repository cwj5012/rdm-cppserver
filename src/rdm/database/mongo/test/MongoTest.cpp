#include <iostream>

#include <catch2/catch.hpp>

#include "../../../util/Time.h"
#include "../MongoHeader.h"

using namespace rdm;

TEST_CASE("MongoTest", "[]") {
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{}};

    bsoncxx::builder::stream::document document{};

    auto collection = conn["testdb"]["testcollection"];
    document << "hello" << "world";

    StopWatch sw;
    sw.start();
    for (int i = 0; i < 10 * 1000; ++i) {
        collection.insert_one(document.view());
    }
    sw.end();
    std::cout << "insert_one 1w, " << sw.durationMs() << " ms" << std::endl;
    sw.reset();

    sw.start();
    std::vector<bsoncxx::document::value> documents;
    documents.reserve(100 * 1000);
    for (int i = 0; i < 100 * 1000; ++i) {
        documents.push_back( bsoncxx::builder::stream::document{} << "i" << i << "j" << i << bsoncxx::builder::stream::finalize);
    }
    collection.insert_many(documents);
    sw.end();
    std::cout << "insert_many 10w, " << sw.durationMs() << " ms" << std::endl;
    sw.reset();

//    auto cursor = collection.find({});
//
//    for (auto&& doc : cursor) {
//        // { "_id" : { "$oid" : "5ed154df6644f10493208512" }, "hello" : "world" }
//        // std::cout << bsoncxx::to_json(doc) << std::endl;
//        REQUIRE(bsoncxx::to_json(doc).size() == 70);
//    }
}