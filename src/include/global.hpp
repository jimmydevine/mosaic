#pragma once


#include "throwable.hpp"
#include "json.hpp"
#include "fifo_map.hpp"


#define THROW throw Mosaic::Throwable().write


template<class K, class V, class dummy_compare, class A> using fifo_map_t = nlohmann::fifo_map<K, V, nlohmann::fifo_map_compare<K>, A>;
using JSON = nlohmann::basic_json<fifo_map_t>;
#define FIFOMAP nlohmann::fifo_map

#define DELETE(x) delete x; x = NULL;