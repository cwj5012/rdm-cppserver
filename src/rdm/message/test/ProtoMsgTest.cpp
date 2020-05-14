//#include <gtest/gtest.h>
//#include <google/protobuf/message.h>
//
//#include <LibServer/msg/ProtoMsg.h>
//#include <LibServer/msg/proto/Person.pb.h>
//
//using namespace rdm;
//
//TEST(proto_msg, test)
//{
//    std::shared_ptr<Person> ptrPerson1 = std::make_shared<Person>();
//    ptrPerson1->set_name("abc");
//    ptrPerson1->set_id(1);
//    ptrPerson1->set_email("example@qq.com");
//
//    ProtoMsg<Person> msg1(ptrPerson1);
//
//    std::vector<uint8_t> buf;
//    msg1.packData(buf);
//
//    std::shared_ptr<Person> ptrPerson2 = std::make_shared<Person>();
//    ProtoMsg<Person> msg2(ptrPerson2);
//    msg2.getData(buf);
//
//    EXPECT_EQ(msg2.getMsg()->name(), "abc");
//}