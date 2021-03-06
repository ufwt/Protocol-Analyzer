// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

// ============================================================================
// Copyright (c) 2017-2018, by Vitaly Grigoriev, <Vit.link420@gmail.com>.
// This file is part of ProtocolAnalyzer open source project under MIT License.
// ============================================================================


#include <bitset>
#include <iostream>

#include "../include/framework/Timer.hpp"
#include "../include/framework/AnalyzerApi.hpp"

namespace types = analyzer::framework::common::types;
using analyzer::framework::common::types::BinaryDataEngine;
using analyzer::framework::common::types::BinaryStructuredDataEngine;
using timer = analyzer::framework::diagnostic::Timer;



int32_t main (int32_t size, char** data)
{
#pragma pack(push, 1)
    struct Data
    {
        uint32_t SequenceNumber;
        uint32_t AcknowledgmentNumber;
        uint8_t Offset_Reserved_NS;
        uint8_t CWR_ECE_TcpFlags;
        uint16_t WindowSize;
        uint16_t Checksum;
        uint16_t UrgentPointer;
    } tcp { 0x00000000, 0x00000000, 0x0C, 0x00, 0x00FF, 0xAAAA, 0x0000 };
#pragma pack(pop)

    /*BinaryDataEngine buffer(sizeof(tcp), types::DATA_MODE_DEFAULT);
    //buffer.SetDataModeType(types::DATA_MODE_INDEPENDENT);
    buffer.AssignReference(reinterpret_cast<std::byte*>(&tcp), sizeof(tcp));
    uint32_t value = buffer.BitsTransform().Convert<uint32_t>(1000, 1100);
    std::cout << value << std::endl;*/

    //return EXIT_FAILURE;
    const uint16_t field = 0x00FF;
    const uint16_t byte_pattern[7] = { 4, 4, 1, 1, 2, 2, 2 };
    const uint16_t bit_pattern[10] = { 32, 32, 4, 3, 3, 6, 9, 7, 16, 16 };


    BinaryStructuredDataEngine buffer1(types::DATA_BIG_ENDIAN);
    buffer1.AssignData(&tcp, byte_pattern, 7);
    std::cout << buffer1.Data().ToHexString() << std::endl;
    //uint8_t value = buffer1.GetSubField<uint8_t>(4, 0, 7);
    //std::cout << buffer1.ToFormattedString() << std::endl << std::endl;
    //std::cout << uint16_t(buffer1.GetSubField<uint32_t>(2, 4, 3)) << std::endl;

    /*std::cout << '-' << buffer1.GetNonemptyFieldIndex(0, bit_pattern, 10).value() << std::endl;
    std::cout << '-' << buffer1.GetNonemptyFieldIndex(1, bit_pattern, 10).value() << std::endl;
    std::cout << '-' << buffer1.GetNonemptyFieldIndex(2, bit_pattern, 10).value() << std::endl;
    std::cout << '-' << buffer1.GetNonemptyFieldIndex(3, bit_pattern, 10).value() << std::endl;
    std::cout << '-' << buffer1.GetNonemptyFieldIndex(4, bit_pattern, 10).value() << std::endl;
    std::cout << '-' << buffer1.GetNonemptyFieldIndex(5, bit_pattern, 10).value() << std::endl;
    std::cout << '-' << buffer1.GetNonemptyFieldIndex(6, bit_pattern, 10).value() << std::endl;
    std::cout << '-' << buffer1.GetNonemptyFieldIndex(7, bit_pattern, 10).value() << std::endl;
    std::cout << '-' << buffer1.GetNonemptyFieldIndex(8, bit_pattern, 10).value() << std::endl;
    std::cout << '-' << buffer1.GetNonemptyFieldIndex(9, bit_pattern, 10).value() << std::endl;*/

    timer Timer(true);
    for (uint16_t idx = 0; idx < 100; ++idx) {
        buffer1.GetNonemptyFieldIndex(0, bit_pattern, 10).value();
    }
    std::cout << Timer.UpdateAndGetCount().MicroSeconds() / 100 << std::endl;
    for (uint16_t idx = 0; idx < 100; ++idx) {
        buffer1.GetNonemptyFieldIndex(1, bit_pattern, 10).value();
    }
    std::cout << Timer.UpdateAndGetCount().MicroSeconds() / 100 << std::endl;
    for (uint16_t idx = 0; idx < 100; ++idx) {
        buffer1.GetNonemptyFieldIndex(2, bit_pattern, 10).value();
    }
    std::cout << Timer.UpdateAndGetCount().MicroSeconds() / 100  << std::endl;
    for (uint16_t idx = 0; idx < 100; ++idx) {
        buffer1.GetNonemptyFieldIndex(3, bit_pattern, 10).value();
    }
    std::cout << Timer.UpdateAndGetCount().MicroSeconds() / 100  << std::endl;
    for (uint16_t idx = 0; idx < 100; ++idx) {
        buffer1.GetNonemptyFieldIndex(4, bit_pattern, 10).value();
    }
    std::cout << Timer.UpdateAndGetCount().MicroSeconds() / 100  << std::endl;
    for (uint16_t idx = 0; idx < 100; ++idx) {
        buffer1.GetNonemptyFieldIndex(5, bit_pattern, 10).value();
    }
    std::cout << Timer.UpdateAndGetCount().MicroSeconds() / 100  << std::endl;
    for (uint16_t idx = 0; idx < 100; ++idx) {
        buffer1.GetNonemptyFieldIndex(6, bit_pattern, 10).value();
    }
    std::cout << Timer.UpdateAndGetCount().MicroSeconds() / 100  << std::endl;
    for (uint16_t idx = 0; idx < 100; ++idx) {
        buffer1.GetNonemptyFieldIndex(7, bit_pattern, 10).value();
    }
    std::cout << Timer.UpdateAndGetCount().MicroSeconds() / 100  << std::endl;
    for (uint16_t idx = 0; idx < 100; ++idx) {
        buffer1.GetNonemptyFieldIndex(8, bit_pattern, 10).value();
    }
    std::cout << Timer.UpdateAndGetCount().MicroSeconds() / 100  << std::endl;
    for (uint16_t idx = 0; idx < 100; ++idx) {
        buffer1.GetNonemptyFieldIndex(9, bit_pattern, 10).value();
    }
    std::cout << Timer.PauseAndGetCount().MicroSeconds() / 100  << std::endl;
    return EXIT_SUCCESS;

    std::cout << buffer1.SetField(4, field) << std::endl;
    std::cout << buffer1.ToFormattedString() << std::endl;
    buffer1.SetFieldBit<types::DATA_MODE_DEPENDENT>(0, 0, false);
    buffer1.SetFieldBit<types::DATA_MODE_DEPENDENT>(0, 1, false);
    buffer1.SetFieldBit<types::DATA_MODE_DEPENDENT>(0, 8, false);
    buffer1.SetFieldBit<types::DATA_MODE_DEPENDENT>(0, 16, false);
    buffer1.SetFieldBit<types::DATA_MODE_DEPENDENT>(0, 31, false);
    std::cout << buffer1.ToFormattedString() << std::endl;
    std::cout << buffer1.GetFieldBit<types::DATA_MODE_DEPENDENT>(0, 0);
    std::cout << buffer1.GetFieldBit<types::DATA_MODE_DEPENDENT>(0, 1);
    std::cout << buffer1.GetFieldBit<types::DATA_MODE_DEPENDENT>(0, 8);
    std::cout << buffer1.GetFieldBit<types::DATA_MODE_DEPENDENT>(0, 16);
    std::cout << buffer1.GetFieldBit<types::DATA_MODE_DEPENDENT>(0, 31) << std::endl;

    BinaryDataEngine field1 = buffer1.GetField<types::DATA_MODE_DEFAULT, types::DATA_LITTLE_ENDIAN>(0);
    std::cout << field1.BitsTransform().Length() << std::endl;
    std::cout << field1.BitsTransform() << std::endl;

    BinaryDataEngine field3 = buffer1.GetFieldByReference(0);
    std::cout << field3.BitsTransform().Length() << std::endl;
    std::cout << field3.BitsTransform() << std::endl;
    field3.BitsTransform().RoundShiftLeft(8);
    field3.Clear();
    std::cout << buffer1.ToFormattedString() << std::endl;


    /*BinaryStructuredDataEngine buffer2(types::DATA_LITTLE_ENDIAN);
    std::cout << buffer2.AssignData(&tcp, pattern, 7) << std::endl;
    buffer2.SetFieldBit<types::DATA_MODE_DEPENDENT>(6, 0, true);
    buffer2.SetFieldBit<types::DATA_MODE_DEPENDENT>(6, 1, true);
    buffer2.SetFieldBit<types::DATA_MODE_DEPENDENT>(6, 8, true);
    buffer2.SetFieldBit<types::DATA_MODE_DEPENDENT>(6, 15, true);
    std::cout << buffer2.ToFormattedString() << std::endl;
    std::cout << buffer2.GetFieldBit<types::DATA_MODE_DEPENDENT>(6, 0);
    std::cout << buffer2.GetFieldBit<types::DATA_MODE_DEPENDENT>(6, 1);
    std::cout << buffer2.GetFieldBit<types::DATA_MODE_DEPENDENT>(6, 8);
    std::cout << buffer2.GetFieldBit<types::DATA_MODE_DEPENDENT>(6, 15) << std::endl;

    BinaryDataEngine field6 = buffer2.GetField<types::DATA_MODE_DEFAULT, types::DATA_BIG_ENDIAN>(6);
    std::cout << field6.BitsTransform().Length() << std::endl;
    std::cout << field6.BitsTransform() << std::endl;*/



    //return EXIT_SUCCESS;

    const uint16_t value_0 = 37988;
    const uint32_t value_1 = 573475684;
    const uint16_t value_2 = 12345;
    const uint32_t value_3 = 397327479;
    const uint32_t value_4 = value_1 ^ value_2;
    const uint32_t value_5 = value_2 ^ value_3;
    const uint32_t value_6 = value_1 & value_2;
    const uint32_t value_7 = value_2 & value_3;
    const uint32_t value_8 = value_1 | value_2;
    const uint32_t value_9 = value_2 | value_3;

    BinaryDataEngine buffer_1;
    const auto& engine_1 = buffer_1.BitsTransform();
    buffer_1.AssignData(&value_1, 1);
    std::cout << "Count 1: " << engine_1.Count() << "   " << engine_1 << std::endl;
    buffer_1.SetDataEndianType(types::DATA_BIG_ENDIAN);
    std::cout << "Count 1: " << engine_1.Count() << "   " << engine_1 << std::endl;
    buffer_1.SetDataEndianType(types::DATA_LITTLE_ENDIAN);

    BinaryDataEngine buffer_2;
    const auto& engine_2 = buffer_2.BitsTransform();
    buffer_2.AssignData(&value_2, 1);
    std::cout << "Count 2: " << engine_2.Count() << "   " << engine_2 << std::endl;

    BinaryDataEngine buffer_3;
    const auto& engine_3 = buffer_3.BitsTransform();
    buffer_3.AssignData(&value_3, 1);
    std::cout << "Count 3: " << engine_3.Count() << "   " << engine_3 << std::endl;


    std::cout << "Results:" << std::endl;


    BinaryDataEngine buffer_r1;
    const auto& engine_r1 = buffer_r1.BitsTransform();
    buffer_r1.AssignData(&value_4, 1);
    std::cout << "Count 4: " << engine_r1.Count() << "   " << engine_r1 << std::endl;

    BinaryDataEngine buffer_r2;
    const auto& engine_r2 = buffer_r2.BitsTransform();
    buffer_r2.AssignData(&value_5, 1);
    std::cout << "Count 5: " << engine_r2.Count() << "   " << engine_r2 << std::endl;

    BinaryDataEngine buffer_r3;
    const auto& engine_r3 = buffer_r3.BitsTransform();
    buffer_r3.AssignData(&value_6, 1);
    std::cout << "Count 6: " << engine_r3.Count() << "   " << engine_r3 << std::endl;

    BinaryDataEngine buffer_r4;
    const auto& engine_r4 = buffer_r4.BitsTransform();
    buffer_r4.AssignData(&value_7, 1);
    std::cout << "Count 7: " << engine_r4.Count() << "   " << engine_r4 << std::endl;

    BinaryDataEngine buffer_r5;
    const auto& engine_r5 = buffer_r5.BitsTransform();
    buffer_r5.AssignData(&value_8, 1);
    std::cout << "Count 8: " << engine_r5.Count() << "   " << engine_r5 << std::endl;

    BinaryDataEngine buffer_r6;
    const auto& engine_r6 = buffer_r6.BitsTransform();
    buffer_r6.AssignData(&value_9, 1);
    std::cout << "Count 9: " << engine_r6.Count() << "   " << engine_r6 << std::endl;


    std::cout << "XOR:" << std::endl;


    BinaryDataEngine buffer_4 = engine_1 ^ engine_2;
    const auto& engine_4 = buffer_4.BitsTransform();
    std::cout << "Count 4: " << engine_4.Count() << "   " << engine_4 << std::endl;

    BinaryDataEngine buffer_5 = engine_2 ^ engine_3;
    const auto& engine_5 = buffer_5.BitsTransform();
    std::cout << "Count 5: " << engine_5.Count() << "   " << engine_5 << std::endl;

    buffer_1.SetDataEndianType(types::DATA_BIG_ENDIAN);
    BinaryDataEngine buffer_6 = engine_1 ^ engine_2;
    const auto& engine_6 = buffer_6.BitsTransform();
    std::cout << "Count 4: " << engine_6.Count() << "   " << engine_6 << std::endl;
    buffer_1.SetDataEndianType(types::DATA_LITTLE_ENDIAN);

    buffer_2.SetDataEndianType(types::DATA_BIG_ENDIAN);
    BinaryDataEngine buffer_7 = engine_2 ^ engine_3;
    const auto& engine_7 = buffer_7.BitsTransform();
    std::cout << "Count 5: " << engine_7.Count() << "   " << engine_7 << std::endl;
    buffer_2.SetDataEndianType(types::DATA_LITTLE_ENDIAN);


    std::cout << "AND:" << std::endl;


    BinaryDataEngine buffer_8 = engine_1 & engine_2;
    const auto& engine_8 = buffer_8.BitsTransform();
    std::cout << "Count 6: " << engine_8.Count() << "   " << engine_8 << std::endl;

    BinaryDataEngine buffer_9 = engine_2 & engine_3;
    const auto& engine_9 = buffer_9.BitsTransform();
    std::cout << "Count 7: " << engine_9.Count() << "   " << engine_9 << std::endl;

    buffer_1.SetDataEndianType(types::DATA_BIG_ENDIAN);
    BinaryDataEngine buffer_10 = engine_1 & engine_2;
    const auto& engine_10 = buffer_10.BitsTransform();
    std::cout << "Count 6: " << engine_10.Count() << "   " << engine_10 << std::endl;
    buffer_1.SetDataEndianType(types::DATA_LITTLE_ENDIAN);

    buffer_2.SetDataEndianType(types::DATA_BIG_ENDIAN);
    BinaryDataEngine buffer_11 = engine_2 & engine_3;
    const auto& engine_11 = buffer_11.BitsTransform();
    std::cout << "Count 7: " << engine_11.Count() << "   " << engine_11 << std::endl;
    buffer_2.SetDataEndianType(types::DATA_LITTLE_ENDIAN);


    std::cout << "OR:" << std::endl;


    BinaryDataEngine buffer_12 = engine_1 | engine_2;
    const auto& engine_12 = buffer_12.BitsTransform();
    std::cout << "Count 8: " << engine_12.Count() << "   " << engine_12 << std::endl;

    BinaryDataEngine buffer_13 = engine_2 | engine_3;
    const auto& engine_13 = buffer_13.BitsTransform();
    std::cout << "Count 9: " << engine_13.Count() << "   " << engine_13 << std::endl;

    buffer_1.SetDataEndianType(types::DATA_BIG_ENDIAN);
    BinaryDataEngine buffer_14 = engine_1 | engine_2;
    const auto& engine_14 = buffer_14.BitsTransform();
    std::cout << "Count 8: " << engine_14.Count() << "   " << engine_14 << std::endl;
    buffer_1.SetDataEndianType(types::DATA_LITTLE_ENDIAN);

    buffer_2.SetDataEndianType(types::DATA_BIG_ENDIAN);
    BinaryDataEngine buffer_15 = engine_2 | engine_3;
    const auto& engine_15 = buffer_15.BitsTransform();
    std::cout << "Count 9: " << engine_15.Count() << "   " << engine_15 << std::endl;
    buffer_2.SetDataEndianType(types::DATA_LITTLE_ENDIAN);

    return EXIT_SUCCESS;
}
