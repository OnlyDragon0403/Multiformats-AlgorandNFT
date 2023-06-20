// Multiaddr unit tests
//
// Author: Matthew Knight
// File Name: multiaddr-test.cpp
// Date: 2019-10-16

#include "util.hpp"

#include "multiformats/multiaddr.hpp"

#include <gtest/gtest.h>

#include <vector>

struct MultiaddrTestParam {
    std::string address;
    std::vector<std::uint8_t> binary;
};

std::vector<MultiaddrTestParam> const parameters{
    {"/ip4/127.0.0.1", "047f000001"_hex},
    {"/ip4/127.0.0.1/tcp/5000", "047f000001061388"_hex},
    {"/ip6/2001:8a0:7ac5:4201:3ac9:86ff:fe31:7095",
     "29200108a07ac542013ac986fffe317095"_hex},
    {"/ip6/2001:8a0:7ac5:4201:3ac9:86ff:fe31:7095/tcp/5000",
     "29200108a07ac542013ac986fffe317095061388"_hex},
    {"/ip4/127.0.0.1/tcp/80/unix/a/b/c/d/e/f",
     "047f00000106005090030b612f622f632f642f652f66"_hex},
    {"/ip6/2001:8a0:7ac5:4201:3ac9:86ff:fe31:7095/tcp/8000/http",
     "29200108a07ac542013ac986fffe317095061f40e003"_hex},
    {"/unix/a/b/c/d/e", "900309612f622f632f642f65"_hex}};
/*
"/ip4/127.0.0.1/udp/5000"
"/ip6/2001:8a0:7ac5:4201:3ac9:86ff:fe31:7095/udp/5000"
"/ip4/127.0.0.1/p2p/QmcgpsyWgH8Y8ajJz1Cu72KnS5uo2Aa2LpzU7kinSupNKC/tcp/1234"
"/ip4/127.0.0.1/ipfs/QmcgpsyWgH8Y8ajJz1Cu72KnS5uo2Aa2LpzU7kinSupNKC/tcp/1234"
"/ip6/2001:8a0:7ac5:4201:3ac9:86ff:fe31:7095/p2p/QmcgpsyWgH8Y8ajJz1Cu72KnS5uo2Aa2LpzU7kinSupNKC/tcp/1234"
"/ip4/127.0.0.1/udp/5000/utp"
"/ip6/2001:8a0:7ac5:4201:3ac9:86ff:fe31:7095/udp/5000/utp"
"/ip4/127.0.0.1/tcp/8000/http"
"/ip6/2001:8a0:7ac5:4201:3ac9:86ff:fe31:7095/tcp/8000/unix/a/b/c/d/e/f"
"/ip4/127.0.0.1/tcp/8000/https"
"/ip6/2001:8a0:7ac5:4201:3ac9:86ff:fe31:7095/tcp/8000/https"
"/ip4/127.0.0.1/tcp/8000/ws"
"/ip6/2001:8a0:7ac5:4201:3ac9:86ff:fe31:7095/tcp/8000/ws"
"/ip6/2001:8a0:7ac5:4201:3ac9:86ff:fe31:7095/tcp/8000/ws/ipfs/QmcgpsyWgH8Y8ajJz1Cu72KnS5uo2Aa2LpzU7kinSupNKC"
"/ip6/2001:8a0:7ac5:4201:3ac9:86ff:fe31:7095/tcp/8000/ws/p2p/QmcgpsyWgH8Y8ajJz1Cu72KnS5uo2Aa2LpzU7kinSupNKC"
"/ip6/2001:8a0:7ac5:4201:3ac9:86ff:fe31:7095/udp/4001/quic/ipfs/QmcgpsyWgH8Y8ajJz1Cu72KnS5uo2Aa2LpzU7kinSupNKC"
"/ip6/2001:8a0:7ac5:4201:3ac9:86ff:fe31:7095/udp/4001/quic/p2p/QmcgpsyWgH8Y8ajJz1Cu72KnS5uo2Aa2LpzU7kinSupNKC"
"/p2p/QmcgpsyWgH8Y8ajJz1Cu72KnS5uo2Aa2LpzU7kinSupNKC"
"/ipfs/QmcgpsyWgH8Y8ajJz1Cu72KnS5uo2Aa2LpzU7kinSupNKC"
"/onion/timaq4ygg2iegci7:1234"
"/onion/timaq4ygg2iegci:80"
"/onion/timaq4ygg2iegci7:-1"
"/onion/timaq4ygg2iegci7"
"/onion3/vww6ybal4bd7szmgncyruucpgfkqahzddi37ktceo3ah7ngmcopnpyyd:1234"
"/onion3/vww6ybal4bd7szmgncyruucpgfkqahzddi37ktceo3ah7ngmcopyyd:1234"
"/onion3/vww6ybal4bd7szmgncyruucpgfkqahzddi37ktceo3ah7ngmcopnpyyd:-1"
"/onion3/vww6ybal4bd7szmgncyruucpgfkqahzddi37ktceo3ah7ngmcopnpyyd"
"/p2p-circuit/p2p/QmcgpsyWgH8Y8ajJz1Cu72KnS5uo2Aa2LpzU7kinSupNKC"
"/p2p/QmcgpsyWgH8Y8ajJz1Cu72KnS5uo2Aa2LpzU7kinSupNKC/p2p-circuit"
"/ipfs/QmcgpsyWgH8Y8ajJz1Cu72KnS5uo2Aa2LpzU7kinSupNKC/p2p-circuit"
"/ip4/127.0.0.1/tcp/9090/ws/p2p-webrtc-star/p2p/QmcgpsyWgH8Y8ajJz1Cu72KnS5uo2Aa2LpzU7kinSupNKC"
"/ip4/127.0.0.1/tcp/9090/ws/p2p-webrtc-star/ipfs/QmcgpsyWgH8Y8ajJz1Cu72KnS5uo2Aa2LpzU7kinSupNKC"
"/ip4/127.0.0.1/tcp/9090/http/p2p-webrtc-direct"
"/ip4/127.0.0.1/tcp/9090/ws/p2p-websocket-star"
"/dns/ipfs.io"
"/dnsaddr/ipfs.io"
"/dns4/ipfs.io"
"/dns6/ipfs.io"
"/ip4/127.0.0.1"
"/ip4/127.0.0.1"
*/

class MultiaddrParamTestFixture
    : public ::testing::TestWithParam<MultiaddrTestParam> {};

TEST_P(MultiaddrParamTestFixture, StringToBinary) {
    auto [address, binary] = GetParam();

    Multiformats::Multiaddr multiaddr{address};
    EXPECT_EQ(multiaddr.to_binary(), binary);
}

TEST_P(MultiaddrParamTestFixture, BinaryToString) {
    auto [address, binary] = GetParam();

    Multiformats::Multiaddr multiaddr{binary};
    EXPECT_EQ(multiaddr.to_string(), address);
}

INSTANTIATE_TEST_CASE_P(MultiaddrTests, MultiaddrParamTestFixture,
                        ::testing::ValuesIn(parameters));
