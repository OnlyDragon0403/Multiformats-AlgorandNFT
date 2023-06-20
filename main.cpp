//
// Created by Bruno on 6/19/2023.
//

#include "multiformats/cid.hpp"
#include "utils/base.h"
#include <iostream>

typedef std::vector<unsigned char> bytes;

std::vector<std::string> splitString(std::string str, std::string delimiter) {
  std::vector<std::string> tokens;
  std::size_t start = 0, end = 0;
  while ((end = str.find(delimiter, start)) != std::string::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + delimiter.length();
  }
  tokens.push_back(str.substr(start));

  return tokens;
}

int main () {
  std::cout<< "hello" <<std::endl;
//  std::string url = "template-ipfs://{ipfscid:1:dag-pb:reserve:sha2-256}/nfd.json";
  std::string url = "template-ipfs://{ipfscid:0:dag-pb:reserve:sha2-256}";
//  std::string reserve = "GFQBC3TR742IL3RH5YCYJAS4ZIM7C4OHAUX4WVH3QXCR3HTSBVWR27XTUQ";
    std::string reserve = "A3AXILWQ3KQG7TV3ASS2PWOCBHZCKSRSW4UBLMPPG3DMUWKBJN23CCRFDQ";

  std::vector<std::string> chunks = splitString(url, "://");

  std::string prefix = std::string("{ipfscid:");
  if(chunks[0] ==std::string("template-ipfs") && chunks[1].substr(0, prefix.length()) == prefix) {
    // Look for something like: template:ipfs://{ipfscid:1:raw:reserve:sha2-256} and parse into components
    chunks[0] = 'ipfs';

    const std::vector<std::string> cidComponents = splitString(chunks[1], std::string(":"));
    if(cidComponents.size() != 5) {
      return 0; // give up
    }

    const std::string cidVersion = cidComponents[1];    // 1
    const std::string cidCodec = cidComponents[2];      // raw
    const std::string asaField = cidComponents[3];      // reserve
    const std::string cidHash = cidComponents[4];       // sha2-256

    if(splitString(cidHash, std::string("}"))[0] != std::string("sha2-256")) {
      return 0;
    }

    if(cidCodec != std::string("raw") && cidCodec != std::string("dag-pb"))
      return 0;

    if(asaField != std::string("reserve"))
      return 0;

    int cidCodecCode;
    if(cidCodec == std::string("raw"))
      cidCodecCode = 0x55;
    if(cidCodec == std::string("dag-pb"))
      cidCodecCode = 0x70;

    const Multiformats::Varint version(std::stoi(cidVersion));
    const Multiformats::Varint type(cidCodecCode);

    bytes with_checksum = b32_decode(reserve);
    bytes public_key(bytes{with_checksum.begin(), with_checksum.begin() + 32});

    Multiformats::Multihash mh_reserve(public_key, "sha2-256");

    std::string uri;
    std::vector<std::string> uri_vec = splitString(cidHash, std::string("/"));
    if(uri_vec.size() > 1) uri = uri_vec[1];

    Multiformats::Cid cid{version, type,  mh_reserve};

    std::string cid_string;
    if(version == 1)
      cid_string = cid.to_string(Multiformats::Multibase::Protocol::Base32);  // comparasion encoded
    else {
      cid_string = cid.to_string(
          Multiformats::Multibase::Protocol::Base58Btc); // comparasion encoded
      cid_string = cid_string.erase(0, 1);
    }
    std::cout<< cid_string << std::endl;

    chunks[1] = "https://ipfs.io/ipfs/" + cid_string + "/" + uri;

    std::cout<< "redirecting to ipfs:" << chunks[1] << std::endl;
  }

//  std::string human_string = cid.human_readable(Multiformats::Multibase::Protocol::Base58Btc);
//  std::cout<< human_string << std::endl;
  return 0;
}

