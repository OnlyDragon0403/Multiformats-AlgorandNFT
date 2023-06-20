// Tests for multibase
//
// Author: Matthew Knight
// File Name: multibase.cpp
// Date: 2019-09-17

#include "multiformats/multibase.hpp"

#include <gtest/gtest.h>

using namespace Multiformats::Multibase;

std::string const yes_mani_str{"yes mani !"};
std::string const unicode_one_str{"÷ïÿ"};
std::string const unicode_two_str{"÷ïÿ🥰÷ïÿ😎🥶🤯"};

std::vector<std::uint8_t> const yes_mani{yes_mani_str.begin(),
                                         yes_mani_str.end()};
std::vector<std::uint8_t> const unicode_one{unicode_one_str.begin(),
                                            unicode_one_str.end()};
std::vector<std::uint8_t> const unicode_two{unicode_two_str.begin(),
                                            unicode_two_str.end()};
std::vector<std::uint8_t> const f{0x66};
std::vector<std::uint8_t> const fo{0x66, 0x6f};
std::vector<std::uint8_t> const foo{0x66, 0x6f, 0x6f};
std::vector<std::uint8_t> const foob{0x66, 0x6f, 0x6f, 0x62};
std::vector<std::uint8_t> const fooba{0x66, 0x6f, 0x6f, 0x62, 0x61};
std::vector<std::uint8_t> const foobar{0x66, 0x6f, 0x6f, 0x62, 0x61, 0x72};
std::vector<std::uint8_t> const cid_decoded{
    0x01, 0x55, 0x12, 0x20, 0x6e, 0x6f, 0xf7, 0x95, 0x0a, 0x36,
    0x18, 0x7a, 0x80, 0x16, 0x13, 0x42, 0x6e, 0x85, 0x8d, 0xce,
    0x68, 0x6c, 0xd7, 0xd7, 0xe3, 0xc0, 0xfc, 0x42, 0xee, 0x03,
    0x30, 0x07, 0x2d, 0x24, 0x5c, 0x95};
std::string const cid_encoded{
    "zb2rhe5P4gXftAwvA4eXQ5HJwsER2owDyS9sKaQRRVQPn93bA"};

struct Parameter {
    Protocol protocol;
    std::vector<std::uint8_t> buf;
    std::string encoded;
};

std::vector<Parameter> const parameters{
    {Protocol::Base2, yes_mani,
     "0011110010110010101110011001000000110110101100001011011100110100100100000"
     "00100001"},
    {Protocol::Base8, yes_mani, "7171312714403326055632220041"},
    {Protocol::Base10, yes_mani, "9573277761329450583662625"},
    {Protocol::Base10, {0x00, 0x01}, "901"},
    {Protocol::Base10, {0x00, 0x00, 0xff}, "900255"},
    {Protocol::Base10, {0x01, 0x00}, "9256"},
    {Protocol::Base10, {0x00, 0x01, 0x00}, "90256"},
    {Protocol::Base10, {100}, "9100"},
    {Protocol::Base10, {0xff, 0xff, 0xff}, "916777215"},
    {Protocol::Base10, {243}, "9243"},
    {Protocol::Base10, {0xfe, 0xdc}, "965244"},
    {Protocol::Base16, yes_mani, "f796573206d616e692021"},
    {Protocol::Base16Upper, yes_mani, "F796573206D616E692021"},

    {Protocol::Base16, {0x01}, "f01"},
    {Protocol::Base16, {0x0f}, "f0f"},
    {Protocol::Base16, f, "f66"},
    {Protocol::Base16, fo, "f666f"},
    {Protocol::Base16, foo, "f666f6f"},
    {Protocol::Base16, foob, "f666f6f62"},
    {Protocol::Base16, fooba, "f666f6f6261"},
    {Protocol::Base16, foobar, "f666f6f626172"},

    {Protocol::Base32, yes_mani, "bpfsxgidnmfxgsibb"},
    {Protocol::Base32, f, "bmy"},
    {Protocol::Base32, fo, "bmzxq"},
    {Protocol::Base32, foo, "bmzxw6"},
    {Protocol::Base32, foob, "bmzxw6yq"},
    {Protocol::Base32, fooba, "bmzxw6ytb"},
    {Protocol::Base32, foobar, "bmzxw6ytboi"},

    {Protocol::Base32Upper, yes_mani, "BPFSXGIDNMFXGSIBB"},
    {Protocol::Base32Upper, f, "BMY"},
    {Protocol::Base32Upper, fo, "BMZXQ"},
    {Protocol::Base32Upper, foo, "BMZXW6"},
    {Protocol::Base32Upper, foob, "BMZXW6YQ"},
    {Protocol::Base32Upper, fooba, "BMZXW6YTB"},
    {Protocol::Base32Upper, foobar, "BMZXW6YTBOI"},

    {Protocol::Base32Pad, yes_mani, "cpfsxgidnmfxgsibb"},
    {Protocol::Base32Pad, f, "cmy======"},
    {Protocol::Base32Pad, fo, "cmzxq===="},
    {Protocol::Base32Pad, foo, "cmzxw6==="},
    {Protocol::Base32Pad, foob, "cmzxw6yq="},
    {Protocol::Base32Pad, fooba, "cmzxw6ytb"},
    {Protocol::Base32Pad, foobar, "cmzxw6ytboi======"},

    {Protocol::Base32PadUpper, yes_mani, "CPFSXGIDNMFXGSIBB"},
    {Protocol::Base32PadUpper, f, "CMY======"},
    {Protocol::Base32PadUpper, fo, "CMZXQ===="},
    {Protocol::Base32PadUpper, foo, "CMZXW6==="},
    {Protocol::Base32PadUpper, foob, "CMZXW6YQ="},
    {Protocol::Base32PadUpper, fooba, "CMZXW6YTB"},
    {Protocol::Base32PadUpper, foobar, "CMZXW6YTBOI======"},

    {Protocol::Base32Hex, yes_mani, "vf5in683dc5n6i811"},
    {Protocol::Base32Hex, f, "vco"},
    {Protocol::Base32Hex, fo, "vcpng"},
    {Protocol::Base32Hex, foo, "vcpnmu"},
    {Protocol::Base32Hex, foob, "vcpnmuog"},
    {Protocol::Base32Hex, fooba, "vcpnmuoj1"},
    {Protocol::Base32Hex, foobar, "vcpnmuoj1e8"},

    {Protocol::Base32HexUpper, yes_mani, "VF5IN683DC5N6I811"},
    {Protocol::Base32HexUpper, f, "VCO"},
    {Protocol::Base32HexUpper, fo, "VCPNG"},
    {Protocol::Base32HexUpper, foo, "VCPNMU"},
    {Protocol::Base32HexUpper, foob, "VCPNMUOG"},
    {Protocol::Base32HexUpper, fooba, "VCPNMUOJ1"},
    {Protocol::Base32HexUpper, foobar, "VCPNMUOJ1E8"},

    {Protocol::Base32HexPad, yes_mani, "tf5in683dc5n6i811"},
    {Protocol::Base32HexPad, f, "tco======"},
    {Protocol::Base32HexPad, fo, "tcpng===="},
    {Protocol::Base32HexPad, foo, "tcpnmu==="},
    {Protocol::Base32HexPad, foob, "tcpnmuog="},
    {Protocol::Base32HexPad, fooba, "tcpnmuoj1"},
    {Protocol::Base32HexPad, foobar, "tcpnmuoj1e8======"},

    {Protocol::Base32HexPadUpper, yes_mani, "TF5IN683DC5N6I811"},
    {Protocol::Base32HexPadUpper, f, "TCO======"},
    {Protocol::Base32HexPadUpper, fo, "TCPNG===="},
    {Protocol::Base32HexPadUpper, foo, "TCPNMU==="},
    {Protocol::Base32HexPadUpper, foob, "TCPNMUOG="},
    {Protocol::Base32HexPadUpper, fooba, "TCPNMUOJ1"},
    {Protocol::Base32HexPadUpper, foobar, "TCPNMUOJ1E8======"},

    {Protocol::Base32Z, yes_mani, "hxf1zgedpcfzg1ebb"},
    {Protocol::Base58Flickr, yes_mani, "Z7Pznk19XTTzBtx"},
    {Protocol::Base58Btc, yes_mani, "z7paNL19xttacUY"},
    {Protocol::Base58Btc, cid_decoded, cid_encoded},

    {Protocol::Base64, unicode_one, "mw7fDr8O/"},
    {Protocol::Base64, f, "mZg"},
    {Protocol::Base64, fo, "mZm8"},
    {Protocol::Base64, foo, "mZm9v"},
    {Protocol::Base64, foob, "mZm9vYg"},
    {Protocol::Base64, fooba, "mZm9vYmE"},
    {Protocol::Base64, foobar, "mZm9vYmFy"},
    {Protocol::Base64, unicode_two, "mw7fDr8O/8J+lsMO3w6/Dv/CfmI7wn6W28J+krw"},

    {Protocol::Base64Pad, f, "MZg=="},
    {Protocol::Base64Pad, fo, "MZm8="},
    {Protocol::Base64Pad, foo, "MZm9v"},
    {Protocol::Base64Pad, foob, "MZm9vYg=="},
    {Protocol::Base64Pad, fooba, "MZm9vYmE="},
    {Protocol::Base64Pad, foobar, "MZm9vYmFy"},

    {Protocol::Base64Url, unicode_one, "uw7fDr8O_"},
    {Protocol::Base64Url, unicode_two,
     "uw7fDr8O_8J-lsMO3w6_Dv_CfmI7wn6W28J-krw"},

    {Protocol::Base64UrlPad, f, "UZg=="},
    {Protocol::Base64UrlPad, fo, "UZm8="},
    {Protocol::Base64UrlPad, foo, "UZm9v"},
    {Protocol::Base64UrlPad, foob, "UZm9vYg=="},
    {Protocol::Base64UrlPad, fooba, "UZm9vYmE="},
    {Protocol::Base64UrlPad, foobar, "UZm9vYmFy"},
    {Protocol::Base64UrlPad, unicode_two,
     "Uw7fDr8O_8J-lsMO3w6_Dv_CfmI7wn6W28J-krw=="}};

class MultibaseParamTestFixture : public ::testing::TestWithParam<Parameter> {};

TEST_P(MultibaseParamTestFixture, CompatibilityEncode) {
    Parameter param = GetParam();

    EXPECT_EQ(param.encoded,
              Multiformats::Multibase::encode(param.protocol, param.buf));
}

TEST_P(MultibaseParamTestFixture, CompatibilityDecode) {
    Parameter param = GetParam();

    EXPECT_EQ(param.buf, Multiformats::Multibase::decode(param.encoded));
}

INSTANTIATE_TEST_CASE_P(MultibaseTests, MultibaseParamTestFixture,
                        ::testing::ValuesIn(parameters), [](auto& param_info) {
                            return Multiformats::Multibase::to_string(
                                       param_info.param.protocol) +
                                   "_" + std::to_string(param_info.index);
                        });
