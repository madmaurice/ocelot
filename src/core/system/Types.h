
#pragma once

#include <string>
#include <vector>

OC_NS_BG;

typedef std::string             String;

typedef int8_t                  uint8;
typedef int16_t                 uint16;
typedef uint32_t                uint32;
typedef uint64_t                uint64;

typedef int8_t                  int8;
typedef int16_t                 int16;
typedef int32_t                 int32;
typedef int64_t                 int64;


template<typename T>
using Vector = std::vector<T>;

OC_NS_END;