// Utilities for testing
//
// Author: Matthew Knight
// File Name: util.hpp
// Date: 2019-10-16

#pragma once

#include <vector>
#include <stdexcept>
#include <iterator>
#include <string>

#include <cstdint>
#include <cstring>

std::vector<std::uint8_t> operator""_hex(char const* hex, std::size_t size);
