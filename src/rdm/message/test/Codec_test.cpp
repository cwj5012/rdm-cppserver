//#include <bitset>
//
//#include <gtest/gtest.h>
//
//#include "Codec.h"
//#include "proto/Person.pb.h"
//#include "../util/DebugPrint.h>
//
//using namespace rdm;
//
//using google::protobuf::Descriptor;
//using google::protobuf::DescriptorPool;
//using google::protobuf::Message;
//using google::protobuf::MessageFactory;
//using google::protobuf::Reflection;
//using google::protobuf::FieldDescriptor;
//
//TEST(Codec, encode)
//{
//    EXPECT_EQ(sizeof(int32_t), 4);
//
//    const Descriptor* desc = DescriptorPool::generated_pool()->FindMessageTypeByName("Person");
//    const Message* proto = MessageFactory::generated_factory()->GetPrototype(desc);
//
//    Person p;
//    p.set_name("abc");
//    p.set_id(99);
//    p.set_email("example@qq.com");
//
//    auto encode_str = encode(p);
//
//    EXPECT_EQ(encode_str[0], 0);
//    EXPECT_EQ(encode_str[1], 0);
//    EXPECT_EQ(encode_str[2], 0);
//    EXPECT_EQ(encode_str[3], 34);
//
//    EXPECT_EQ(encode_str[4], 0);
//    EXPECT_EQ(encode_str[5], 0);
//    EXPECT_EQ(encode_str[6], 0);
//    EXPECT_EQ(encode_str[7], 7);
//
//    EXPECT_EQ(encode_str[8], 'P');
//    EXPECT_EQ(encode_str[9], 'e');
//    EXPECT_EQ(encode_str[10], 'r');
//    EXPECT_EQ(encode_str[11], 's');
//    EXPECT_EQ(encode_str[12], 'o');
//    EXPECT_EQ(encode_str[13], 'n');
//    EXPECT_EQ(encode_str[14], '\0');
//
//    EXPECT_EQ(encode_str[15], 0x0a);
//    EXPECT_EQ(encode_str[16], 0x03);
//    EXPECT_EQ(encode_str[17], 0x61);
//    EXPECT_EQ(encode_str[18], 0x62);
//    EXPECT_EQ(encode_str[19], 0x63);
//    EXPECT_EQ(encode_str[20], 0x10);
//    EXPECT_EQ(encode_str[21], 0x63);
//    EXPECT_EQ(encode_str[22], 0x1a);
//    EXPECT_EQ(encode_str[23], 0x0e);
//    EXPECT_EQ(encode_str[24], 0x65);
//    EXPECT_EQ(encode_str[25], 0x78);
//    EXPECT_EQ(encode_str[26], 0x61);
//    EXPECT_EQ(encode_str[27], 0x6d);
//    EXPECT_EQ(encode_str[28], 0x70);
//    EXPECT_EQ(encode_str[29], 0x6c);
//    EXPECT_EQ(encode_str[30], 0x65);
//    EXPECT_EQ(encode_str[31], 0x40);
//    EXPECT_EQ(encode_str[32], 'q');
//    EXPECT_EQ(encode_str[33], 'q');
//    EXPECT_EQ(encode_str[34], '.');
//    EXPECT_EQ(encode_str[35], 'c');
//    EXPECT_EQ(encode_str[36], 'o');
//    EXPECT_EQ(encode_str[37], 'm');
//}
//
//TEST(Codec, decode)
//{
//    const Descriptor* desc = DescriptorPool::generated_pool()->FindMessageTypeByName("Person");
//    const Message* proto = MessageFactory::generated_factory()->GetPrototype(desc);
//    const Reflection* reflection = proto->GetReflection();
//
//    Person p;
//    p.set_name("abc");
//    p.set_id(99);
//    p.set_email("example@qq.com");
//
//    // 编码
//    auto encode_str = encode(p);
//
//    // 解码
//    Message* msg = decode(encode_str);
//
//    // 检查解码后的结果
//    for (int i = 0; i < desc->field_count(); ++i)
//    {
//        const FieldDescriptor* field = desc->field(i);
//
//        auto name = field->name();
//        if (name == "id")
//        {
//            EXPECT_EQ(reflection->GetInt32(*msg, field), 99);
//        } else if (name == "name")
//        {
//            EXPECT_EQ(reflection->GetString(*msg, field), "abc");
//        } else if (name == "email")
//        {
//            EXPECT_EQ(reflection->GetString(*msg, field), "example@qq.com");
//        }
//
////        std::cout << "type: " << field->type()
////                  << " name: " << field->name()
////                  << " label: " << field->label() << " ";
//
//    }
//
//    delete msg;
//}
//
//TEST(Codec, encodeE)
//{
//    EXPECT_EQ(sizeof(int32_t), 4);
//
//    const Descriptor* desc = DescriptorPool::generated_pool()->FindMessageTypeByName("Person");
//    const Message* proto = MessageFactory::generated_factory()->GetPrototype(desc);
//
//    Person p;
//    p.set_name("abc");
//    p.set_id(99);
//    p.set_email("example@qq.com");
//
//    auto encode_str = encodeE(p);
//
//    EXPECT_EQ(encode_str[0], 0);
//    EXPECT_EQ(encode_str[1], 0);
//    EXPECT_EQ(encode_str[2], 0);
//    EXPECT_EQ(encode_str[3], 27);
//
//    EXPECT_EQ(encode_str[4], 0);
//    EXPECT_EQ(encode_str[5], 0);
//    EXPECT_EQ(encode_str[6], 0);
//    EXPECT_EQ(encode_str[7], 99);
//
//    EXPECT_EQ(encode_str[8], 10);
//    EXPECT_EQ(encode_str[9], 3);
//    EXPECT_EQ(encode_str[10], 'a');
//    EXPECT_EQ(encode_str[11], 'b');
//    EXPECT_EQ(encode_str[12], 'c');
//    EXPECT_EQ(encode_str[13], 16);
//    EXPECT_EQ(encode_str[14], 99);
//    EXPECT_EQ(encode_str[15], 26);
//    EXPECT_EQ(encode_str[16], 14);
//    EXPECT_EQ(encode_str[17], 'e');
//    EXPECT_EQ(encode_str[18], 'x');
//    EXPECT_EQ(encode_str[19], 'a');
//    EXPECT_EQ(encode_str[20], 'm');
//    EXPECT_EQ(encode_str[21], 'p');
//    EXPECT_EQ(encode_str[22], 'l');
//    EXPECT_EQ(encode_str[23], 'e');
//    EXPECT_EQ(encode_str[24], '@');
//    EXPECT_EQ(encode_str[25], 'q');
//    EXPECT_EQ(encode_str[26], 'q');
//    EXPECT_EQ(encode_str[27], '.');
//    EXPECT_EQ(encode_str[28], 'c');
//    EXPECT_EQ(encode_str[29], 'o');
//    EXPECT_EQ(encode_str[30], 'm');
//}
//
//TEST(Codec, decodeE)
//{
//    const Descriptor* desc = DescriptorPool::generated_pool()->FindMessageTypeByName("Person");
//    const Message* proto = MessageFactory::generated_factory()->GetPrototype(desc);
//    const Reflection* reflection = proto->GetReflection();
//
//    Person p;
//    p.set_name("abc");
//    p.set_id(99);
//    p.set_email("example@qq.com");
//
//    // 编码
//    auto encode_str = encodeE(p);
//
//    // 解码
//    Message* msg = decodeE(encode_str);
//
//    // 检查解码后的结果
//    for (int i = 0; i < desc->field_count(); ++i)
//    {
//        const FieldDescriptor* field = desc->field(i);
//
//        auto name = field->name();
//        if (name == "id")
//        {
//            EXPECT_EQ(reflection->GetInt32(*msg, field), 99);
//        } else if (name == "name")
//        {
//            EXPECT_EQ(reflection->GetString(*msg, field), "abc");
//        } else if (name == "email")
//        {
//            EXPECT_EQ(reflection->GetString(*msg, field), "example@qq.com");
//        }
//    }
//}
//
//TEST(Codec, encodeS)
//{
//    EXPECT_EQ(sizeof(int32_t), 4);
//
//    const Descriptor* desc = DescriptorPool::generated_pool()->FindMessageTypeByName("Person");
//    const Message* proto = MessageFactory::generated_factory()->GetPrototype(desc);
//
//    Person p;
//    p.set_name("abc");
//    p.set_id(99);
//    p.set_email("example@qq.com");
//
//    auto encode_str = encodeS(p);
//
//    EXPECT_EQ(encode_str[0], 0);
//    EXPECT_EQ(encode_str[1], 0);
//    EXPECT_EQ(encode_str[2], 0);
//    EXPECT_EQ(encode_str[3], 7);
//
//    EXPECT_EQ(encode_str[4], 'P');
//    EXPECT_EQ(encode_str[5], 'e');
//    EXPECT_EQ(encode_str[6], 'r');
//    EXPECT_EQ(encode_str[7], 's');
//    EXPECT_EQ(encode_str[8], 'o');
//    EXPECT_EQ(encode_str[9], 'n');
//    EXPECT_EQ(encode_str[10], '\0');
//
//    EXPECT_EQ(encode_str[11], 0);
//    EXPECT_EQ(encode_str[12], 0);
//    EXPECT_EQ(encode_str[13], 0);
//    EXPECT_EQ(encode_str[14], 23);
//
//    EXPECT_EQ(encode_str[15], 0x0a);
//    EXPECT_EQ(encode_str[16], 0x03);
//    EXPECT_EQ(encode_str[17], 0x61);
//    EXPECT_EQ(encode_str[18], 0x62);
//    EXPECT_EQ(encode_str[19], 0x63);
//    EXPECT_EQ(encode_str[20], 0x10);
//    EXPECT_EQ(encode_str[21], 0x63);
//    EXPECT_EQ(encode_str[22], 0x1a);
//    EXPECT_EQ(encode_str[23], 0x0e);
//    EXPECT_EQ(encode_str[24], 0x65);
//    EXPECT_EQ(encode_str[25], 0x78);
//    EXPECT_EQ(encode_str[26], 0x61);
//    EXPECT_EQ(encode_str[27], 0x6d);
//    EXPECT_EQ(encode_str[28], 0x70);
//    EXPECT_EQ(encode_str[29], 0x6c);
//    EXPECT_EQ(encode_str[30], 0x65);
//    EXPECT_EQ(encode_str[31], 0x40);
//    EXPECT_EQ(encode_str[32], 'q');
//    EXPECT_EQ(encode_str[33], 'q');
//    EXPECT_EQ(encode_str[34], '.');
//    EXPECT_EQ(encode_str[35], 'c');
//    EXPECT_EQ(encode_str[36], 'o');
//    EXPECT_EQ(encode_str[37], 'm');
//}
//
//TEST(Codec, decodeS)
//{
//    const Descriptor* desc = DescriptorPool::generated_pool()->FindMessageTypeByName("Person");
//    const Message* proto = MessageFactory::generated_factory()->GetPrototype(desc);
//    const Reflection* reflection = proto->GetReflection();
//
//    Person p;
//    p.set_name("abc");
//    p.set_id(99);
//    p.set_email("example@qq.com");
//
//    // 编码
//    auto encode_str = encodeS(p);
//
//    // 解码
//    std::string temp;
//    Message* msg = decodeS(encode_str, temp);
//
//    // 检查解码后的结果
//    for (int i = 0; i < desc->field_count(); ++i)
//    {
//        const FieldDescriptor* field = desc->field(i);
//
//        auto name = field->name();
//        if (name == "id")
//        {
//            EXPECT_EQ(reflection->GetInt32(*msg, field), 99);
//        } else if (name == "name")
//        {
//            EXPECT_EQ(reflection->GetString(*msg, field), "abc");
//        } else if (name == "email")
//        {
//            EXPECT_EQ(reflection->GetString(*msg, field), "example@qq.com");
//        }
//
////        std::cout << "type: " << field->type()
////                  << " name: " << field->name()
////                  << " label: " << field->label() << " ";
//
//    }
//
//    delete msg;
//}
//
//TEST(Codec, encodeM)
//{
//    EXPECT_EQ(sizeof(int32_t), 4);
//
//    const Descriptor* desc = DescriptorPool::generated_pool()->FindMessageTypeByName("Person");
//    const Message* proto = MessageFactory::generated_factory()->GetPrototype(desc);
//
//    Person p;
//    p.set_name("abc");
//    p.set_id(99);
//    p.set_email("example@qq.com");
//
//    std::vector<const google::protobuf::Message*> messages;
//    messages.push_back(&p);
//    messages.push_back(&p);
//
//    auto encode_str = encodeM(messages);
//
//    // 第一条消息
//
//    EXPECT_EQ(encode_str[0], 0);
//    EXPECT_EQ(encode_str[1], 0);
//    EXPECT_EQ(encode_str[2], 0);
//    EXPECT_EQ(encode_str[3], 7);
//
//    EXPECT_EQ(encode_str[4], 'P');
//    EXPECT_EQ(encode_str[5], 'e');
//    EXPECT_EQ(encode_str[6], 'r');
//    EXPECT_EQ(encode_str[7], 's');
//    EXPECT_EQ(encode_str[8], 'o');
//    EXPECT_EQ(encode_str[9], 'n');
//    EXPECT_EQ(encode_str[10], '\0');
//
//    EXPECT_EQ(encode_str[11], 0);
//    EXPECT_EQ(encode_str[12], 0);
//    EXPECT_EQ(encode_str[13], 0);
//    EXPECT_EQ(encode_str[14], 23);
//
//    EXPECT_EQ(encode_str[15], 0x0a);
//    EXPECT_EQ(encode_str[16], 0x03);
//    EXPECT_EQ(encode_str[17], 0x61);
//    EXPECT_EQ(encode_str[18], 0x62);
//    EXPECT_EQ(encode_str[19], 0x63);
//    EXPECT_EQ(encode_str[20], 0x10);
//    EXPECT_EQ(encode_str[21], 0x63);
//    EXPECT_EQ(encode_str[22], 0x1a);
//    EXPECT_EQ(encode_str[23], 0x0e);
//    EXPECT_EQ(encode_str[24], 0x65);
//    EXPECT_EQ(encode_str[25], 0x78);
//    EXPECT_EQ(encode_str[26], 0x61);
//    EXPECT_EQ(encode_str[27], 0x6d);
//    EXPECT_EQ(encode_str[28], 0x70);
//    EXPECT_EQ(encode_str[29], 0x6c);
//    EXPECT_EQ(encode_str[30], 0x65);
//    EXPECT_EQ(encode_str[31], 0x40);
//    EXPECT_EQ(encode_str[32], 'q');
//    EXPECT_EQ(encode_str[33], 'q');
//    EXPECT_EQ(encode_str[34], '.');
//    EXPECT_EQ(encode_str[35], 'c');
//    EXPECT_EQ(encode_str[36], 'o');
//    EXPECT_EQ(encode_str[37], 'm');
//
//    // 第二条消息
//
//    EXPECT_EQ(encode_str[38], 0);
//    EXPECT_EQ(encode_str[39], 0);
//    EXPECT_EQ(encode_str[40], 0);
//    EXPECT_EQ(encode_str[41], 7);
//
//    EXPECT_EQ(encode_str[42], 'P');
//    EXPECT_EQ(encode_str[43], 'e');
//    EXPECT_EQ(encode_str[44], 'r');
//    EXPECT_EQ(encode_str[45], 's');
//    EXPECT_EQ(encode_str[46], 'o');
//    EXPECT_EQ(encode_str[47], 'n');
//    EXPECT_EQ(encode_str[48], '\0');
//
//    EXPECT_EQ(encode_str[49], 0);
//    EXPECT_EQ(encode_str[50], 0);
//    EXPECT_EQ(encode_str[51], 0);
//    EXPECT_EQ(encode_str[52], 23);
//
//    EXPECT_EQ(encode_str[53], 0x0a);
//    EXPECT_EQ(encode_str[54], 0x03);
//    EXPECT_EQ(encode_str[55], 0x61);
//    EXPECT_EQ(encode_str[56], 0x62);
//    EXPECT_EQ(encode_str[57], 0x63);
//    EXPECT_EQ(encode_str[58], 0x10);
//    EXPECT_EQ(encode_str[59], 0x63);
//    EXPECT_EQ(encode_str[60], 0x1a);
//    EXPECT_EQ(encode_str[61], 0x0e);
//    EXPECT_EQ(encode_str[62], 0x65);
//    EXPECT_EQ(encode_str[63], 0x78);
//    EXPECT_EQ(encode_str[64], 0x61);
//    EXPECT_EQ(encode_str[65], 0x6d);
//    EXPECT_EQ(encode_str[66], 0x70);
//    EXPECT_EQ(encode_str[67], 0x6c);
//    EXPECT_EQ(encode_str[68], 0x65);
//    EXPECT_EQ(encode_str[69], 0x40);
//    EXPECT_EQ(encode_str[70], 'q');
//    EXPECT_EQ(encode_str[71], 'q');
//    EXPECT_EQ(encode_str[72], '.');
//    EXPECT_EQ(encode_str[73], 'c');
//    EXPECT_EQ(encode_str[74], 'o');
//    EXPECT_EQ(encode_str[75], 'm');
//}
//
//TEST(Codec, decodeM)
//{
//    const Descriptor* desc = DescriptorPool::generated_pool()->FindMessageTypeByName("Person");
//    const Message* proto = MessageFactory::generated_factory()->GetPrototype(desc);
//    const Reflection* reflection = proto->GetReflection();
//
//    Person p;
//    p.set_name("abc");
//    p.set_id(99);
//    p.set_email("example@qq.com");
//
//    std::vector<const google::protobuf::Message*> in_messages;
//    in_messages.push_back(&p);
//    in_messages.push_back(&p);
//
//    // 编码
//    auto encode_str = encodeM(in_messages);
//
//    // 解码
//    std::vector<google::protobuf::Message*> out_message = decodeM(encode_str);
//
//    EXPECT_EQ(out_message.size(), 2);
//
//    // 检查解码后的结果
//    for (auto& msg : out_message)
//    {
//        for (int i = 0; i < desc->field_count(); ++i)
//        {
//            const FieldDescriptor* field = desc->field(i);
//
//            auto name = field->name();
//            if (name == "id")
//            {
//                EXPECT_EQ(reflection->GetInt32(*msg, field), 99);
//            } else if (name == "name")
//            {
//                EXPECT_EQ(reflection->GetString(*msg, field), "abc");
//            } else if (name == "email")
//            {
//                EXPECT_EQ(reflection->GetString(*msg, field), "example@qq.com");
//            }
//        }
//
//        delete msg;
//    }
//}
//
//TEST(Codec, packHeader)
//{
//    std::string in = "abcd";
//    std::string out = packHeader(in);
//    EXPECT_EQ(out.length(), 8);
//    EXPECT_EQ(out[0], 0);
//    EXPECT_EQ(out[1], 0);
//    EXPECT_EQ(out[2], 0);
//    EXPECT_EQ(out[3], 4);
//    EXPECT_EQ(out[4], 'a');
//    EXPECT_EQ(out[5], 'b');
//    EXPECT_EQ(out[6], 'c');
//    EXPECT_EQ(out[7], 'd');
//}
//
//TEST(Codec, unpackHeader)
//{
//    std::string in = packHeader("abcd");
//    std::string out = unpackHeader(in);
//    EXPECT_EQ(out[0], 'a');
//    EXPECT_EQ(out[1], 'b');
//    EXPECT_EQ(out[2], 'c');
//    EXPECT_EQ(out[3], 'd');
//}