#include <catch2/catch.hpp>

#include "../DBConnectionPool.h"
#include "../../../util/Time.h"

using namespace rdm;

TEST_CASE("xxxxx", "[]") {

    DatabaseLoginInfo info;
    info.name = "root";
    info.passwd = "1234";
    info.ip = "ubuntu.a.com";
    info.port = 3306;

    DBConnectionPool pool(info);
    pool.initPool(4);

    std::vector<int> id{1, 2, 3};
    std::vector<std::string> values{"a", "b", "c"};

    StopWatch sw;
    sw.start();
    for (int i = 0; i < 5; i++) {
        DBConnection* conn = pool.getConnection();
        conn->execute("use mysql");
        conn->execute("drop table if exists test");
        conn->execute("create table test(id int, label char(1))");
        for (int j = 0; j < 2000; ++j) {
            conn->execute("insert into test(id, label) values (" +std::to_string(j)+ ", 'a')");
        }
        pool.releaseConnnection(conn);
    }

    sw.end();
    std::cout << "insert_one 1w, " << sw.durationMs() << " ms" << std::endl;
    sw.reset();
}
