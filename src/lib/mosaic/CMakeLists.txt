
include_directories("${PROJECT_BINARY_DIR}/src/include")
include_directories("${PROJECT_SOURCE_DIR}/src/include")
include_directories("${PROJECT_SOURCE_DIR}/submodules/backward-cpp")
include_directories("${PROJECT_SOURCE_DIR}/submodules/json/single_include/nlohmann")
include_directories("${PROJECT_SOURCE_DIR}/submodules/fifo_map/src")

add_library("mosaic-lib" STATIC mosaic.cpp loggable.cpp)
set_target_properties("mosaic-lib" PROPERTIES OUTPUT_NAME "mosaic")
install(FILES "${PROJECT_BINARY_DIR}/src/lib/mosaic/libmosaic.a" DESTINATION "lib")


