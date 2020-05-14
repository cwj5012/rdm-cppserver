//#include <gtest/gtest.h>
//#include <google/protobuf/message.h>
//#include <google/protobuf/text_format.h>
//
//#include <LibServer/msg/Text.h>
//#include <LibServer/msg/proto/Person.pb.h>
//
//using namespace rdm;
//
//TEST(Text, test)
//{
//
//    std::string base_str = "name: \"enname, 中文测试\" id: 99 email: \"example.qq.com\" "
//                           "phone { number: \"000\" } "
//                           "phone { number: \"111\" type: HOME } "
//                           "phone { number: \"222\" type: WORK } ";
//
//    Person p;
//    p.set_name("enname, 中文测试");
//    p.set_id(99);
//    p.set_email("example.qq.com");
//
//    Person::PhoneNumber* pn = nullptr;
//
//    pn = p.add_phone();
//    pn->set_type(Person::MOBILE);
//    pn->set_number("000");
//
//    pn = p.add_phone();
//    pn->set_type(Person::HOME);
//    pn->set_number("111");
//
//    pn = p.add_phone();
//    pn->set_type(Person::WORK);
//    pn->set_number("222");
//
//    google::protobuf::TextFormat::Printer printer;
//    printer.SetSingleLineMode(true);
//    printer.SetUseShortRepeatedPrimitives(true);
//    printer.SetUseUtf8StringEscaping(true);
//
//    std::string text_out;
//    printer.PrintToString(p, &text_out);
//
//    EXPECT_EQ(text_out, base_str);
//
//    // 解析 text
//
//    Person msg;
//    google::protobuf::TextFormat::ParseFromString(text_out, &msg);
//
//    std::string text_out2;
//    printer.PrintToString(msg, &text_out2);
//
//    EXPECT_EQ(text_out2, base_str);
//
//}