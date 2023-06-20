# multiformats
[![pipeline](https://gitlab.com/matt1795/multiformats/badges/master/pipeline.svg)](https://gitlab.com/matt1795/multiformats/commits/master)
[![appveyor](https://ci.appveyor.com/api/projects/status/8rtg893e66xvyjye/branch/master?svg=true)](https://gitlab.com/matt1795/multiformats/commits/master)
[![coverage](https://gitlab.com/matt1795/multiformats/badges/master/coverage.svg)](https://gitlab.com/matt1795/multiformats/commits/master)

C++17 implementation of multiformats.

### Table of Contents
- [multibase](#multibase)

## multibase

Usage example:

```cpp
#include "multiformats/multibase.hpp"

using namespace Multiformats;
// some binary data you want to encode
std::vector<std::uint8_t> buf { 0x00, 0x12, 0x54, 0x54 };

auto str = Multibase::encode(buf, Multibase::Protocol::Base64);

// str value will be: mabjuva==

// don't need to define base when decoding as it is contained within the string
auto another_buf = Multibase::decode(str);
```

Note that as part of the multibase protocol, the first character in the string
denotes the base that the string is encoded in. These characters can be 

These functions throw a `std::runtime_error` exception if the base encoding is
not supported when encoding/decoding, or if there is an error in the string
sequence when decoding.
