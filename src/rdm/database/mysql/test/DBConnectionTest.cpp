#include <catch2/catch.hpp>

#include "../DBConnection.h"

using namespace rdm;

TEST_CASE("DBService", "[]") {
    DatabaseLoginInfo info;
    info.name = "root";
    info.passwd = "1234";
    info.ip = "127.0.0.1";
    info.port = 3306;

    DBConnection conn(get_driver_instance(), info);

    conn.connect();
    conn.execute("use mysql");
    conn.execute("drop table if exists test");
    conn.execute("create table test(id int, label char(1))");
    conn.execute("insert into test(id, label) values (1, 'a')");
    conn.execute("insert into test(id, label) values (2, 'b')");

    conn.executeQuery("select id, label from test order by id asc");
    auto* res = conn.result();

    std::vector<int> id{1, 2};
    std::vector<std::string> values{"a", "b"};
    int i = 0;

    while (res->next()) {
        REQUIRE(id[i] == res->getInt(1));            // test.id
        REQUIRE(values[i] == res->getString(2));    // test.label
        ++i;
    }

}