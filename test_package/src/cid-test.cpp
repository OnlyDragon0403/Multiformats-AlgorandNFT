// CID Unit Tests
//
// Author: Matthew Knight
// File Name: cid-test.cpp
// Date: 2019-10-17

#include "multiformats/cid.hpp"

#include <gtest/gtest.h>

#include <iostream>

TEST(CidTests, Test) {
    std::string const encoded{
        "zb2rhe5P4gXftAwvA4eXQ5HJwsER2owDyS9sKaQRRVQPn93bA"};
    std::string const human_readable{
        "base58btc - cidv1 - raw - "
        "sha2-256-256-"
        "6e6ff7950a36187a801613426e858dce686cd7d7e3c0fc42ee0330072d245c95"};

    Multiformats::Cid cid{encoded};

    EXPECT_EQ(cid.to_string(Multiformats::Multibase::Protocol::Base58Btc),
              encoded);
    EXPECT_EQ(cid.human_readable(Multiformats::Multibase::Protocol::Base58Btc),
              human_readable);
}
