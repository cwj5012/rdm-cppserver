#include <catch2/catch.hpp>

#include "../DBConnectionPool.h"

using namespace rdm;

TEST_CASE("DBConnectionPool", "[]") {

    DatabaseLoginInfo info;
    info.name = "root";
    info.passwd = "1234";
    info.ip = "127.0.0.1";
    info.port = 3306;

    DBConnectionPool pool(info);
    pool.initPool(4);

    std::vector<int> id{1, 2, 3};
    std::vector<std::string> values{"a", "b", "c"};

    for (int i = 0; i < 5; i++) {
        DBConnection* conn = pool.getConnection();
        conn->execute("use mysql");
        conn->execute("drop table if exists test");
        conn->execute("create table test(id int, label char(1))");
        conn->execute("insert into test(id, label) values (1, 'a')");
        conn->execute("insert into test(id, label) values (2, 'b')");
        conn->execute("insert into test(id, label) values (3, 'c')");

        conn->executeQuery("select id, label from test order by id asc");
        auto* res = conn->result();

        int index = 0;
        while (res->next()) {
            REQUIRE(id[index] == res->getInt(1));            // test.id
            REQUIRE(values[index] == res->getString(2));    // test.label
            ++index;
        }

        pool.releaseConnnection(conn);
    }

}
