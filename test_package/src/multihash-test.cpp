// Tests for multihash
//
// Author: Matthew Knight
// File Name: multihash.cpp
// Date: 2019-10-10

#include "util.hpp"

#include "multiformats/multibase.hpp"
#include "multiformats/multihash.hpp"

#include <gtest/gtest.h>

struct MultihashTestParam {
    std::string protocol;
    std::vector<std::uint8_t> plaintext;
    std::vector<std::uint8_t> raw_multihash;
};

std::vector<MultihashTestParam> const parameters{
    {"blake2b-512", "431fb5d4c9b735ba1a34d0df045118806ae2336f2c"_hex,
     "c0e402409b2d7e635f15ca3cd47ecdb2ab8197ba6d26a019ff72eba34f33aba75260eec6542738bf172fb9dcbdc0ca3337a3b7fa2a14858074b8be17c2611074f323a3dc"_hex},
    {"blake2s-256", "431fb5d4c9b735ba1a34d0df045118806ae2336f2c"_hex,
     "e0e4022012934809335113c1b646ef2600770c57abb00c29f7a186f709b4ce4a18dc3d79"_hex},
    {"md4", "431fb5d4c9b735ba1a34d0df045118806ae2336f2c"_hex,
     "d401102bffa98f583e2b367c01116d0ae891fd"_hex},
    {"md5", "431fb5d4c9b735ba1a34d0df045118806ae2336f2c"_hex,
     "d50110442e492938651ada123b88d67a2e0355"_hex},
    {"sha1", "431fb5d4c9b735ba1a34d0df045118806ae2336f2c"_hex,
     "1114bd3cc4dc97becfa6db0e06c65576d4629347af4f"_hex},
    {"sha2-256", "431fb5d4c9b735ba1a34d0df045118806ae2336f2c"_hex,
     "1220383a43482506d667ff97a5d1e78e8ce8fdeb9778260772b6e5945cc34c9fc849"_hex},
    {"sha2-512", "431fb5d4c9b735ba1a34d0df045118806ae2336f2c"_hex,
     "13409fc7697c52002d4774f733116c9f06c2785ec3cbde71936e15b42902b17a1635bedf30063c00795bcb3ee71e6f108b34d8befc1106a3a09a609447e246443ca3"_hex},
    {"sha3-224", "431fb5d4c9b735ba1a34d0df045118806ae2336f2c"_hex,
     "171cca76c68dda39bf0fc7b60f6eb888ac4e313a6a8f92fcaa0f44869e6b"_hex},
    {"sha3-256", "431fb5d4c9b735ba1a34d0df045118806ae2336f2c"_hex,
     "16204ab7f8026a71aabbe46f6e12a89301a8d5bd2f112f72d7d8733d3b8dbbd505ec"_hex},
    {"sha3-384", "431fb5d4c9b735ba1a34d0df045118806ae2336f2c"_hex,
     "153087307008798e677377eb7171d92886d7b4998347a230c1ef0ae3aff9ed101865328d579f20bc0b57657da070755be4b2"_hex},
    {"sha3-512", "431fb5d4c9b735ba1a34d0df045118806ae2336f2c"_hex,
     "14402a45d152aaa17a04de357c52685108ac31d80e40e61aa582557b4998c561436db7fa68154bb773ad380a5ab108725f92eeb1e73334751bfc69f36892e12f30ed"_hex},
    {"shake-128", "431fb5d4c9b735ba1a34d0df045118806ae2336f2c"_hex,
     "1810c175748f62516ff806eec51343003a0b"_hex},
    {"shake-256", "431fb5d4c9b735ba1a34d0df045118806ae2336f2c"_hex,
     "192043df6ee0884c3836645e4e658f812ff4f7c71ed7c625cbe296bb5f3cb33e6862"_hex}};

class MultihashParamTestFixture
    : public ::testing::TestWithParam<MultihashTestParam> {};

TEST_P(MultihashParamTestFixture, Hash) {
    auto [protocol, input, raw_expected] = GetParam();
    Multiformats::Multihash multihash{input, protocol};

    EXPECT_EQ(multihash.size(), raw_expected.size());
    EXPECT_TRUE(
        std::equal(multihash.begin(), multihash.end(), raw_expected.begin()));
}

TEST(MultihashTests, NotInMulticodec) {
    EXPECT_THROW({
        std::vector<std::uint8_t> buf(5, 1);
        Multiformats::Multihash multihash(buf, "asdf");
    }, std::out_of_range);
}

// using tcp here because it is in multicodec, and isn't a hash
TEST(MultihashTests, NotSupported) {
    EXPECT_THROW({
        std::vector<std::uint8_t> buf(5, 1);
        Multiformats::Multihash multihash(buf, "tcp");
    }, std::invalid_argument);
}

INSTANTIATE_TEST_CASE_P(MultihashTests, MultihashParamTestFixture,
                        ::testing::ValuesIn(parameters), [](auto& param_info) {
                            std::string name{param_info.param.protocol + "_" +
                                             std::to_string(param_info.index)};
                            for (auto& character : name)
                                if (character == '-')
                                    character = '_';
                            return name;
                        });
