set (MOSAIC_RUNTIME_VERSION_MAJOR 1)
set (MOSAIC_RUNTIME_VERSION_MINOR 0)
set (MOSAIC_RUNTIME_VERSION_REVISION 0)

set (CMAKE_CXX_STANDARD 17)

option(WITH_RESET "build with reset" OFF)
if(WITH_RESET)
  set(Mosaic_Runtime_OPTION_RESET ON)
endif()

# update config header with variables
configure_file ("${PROJECT_SOURCE_DIR}/src/include/options.hpp.in" "${PROJECT_BINARY_DIR}/src/include/options.hpp")

# update mosaic config with variables
#configure_file ("${PROJECT_SOURCE_DIR}/conf/mosaic.conf.in" "${PROJECT_BINARY_DIR}/conf/mosaic.conf")
#configure_file ("${PROJECT_SOURCE_DIR}/conf/modules.conf.in" "${PROJECT_BINARY_DIR}/conf/modules.conf")
#configure_file ("${PROJECT_SOURCE_DIR}/conf/languages.conf.in" "${PROJECT_BINARY_DIR}/conf/languages.conf")
#configure_file ("${PROJECT_SOURCE_DIR}/conf/storage.conf.in" "${PROJECT_BINARY_DIR}/conf/storage.conf")
#configure_file ("${PROJECT_SOURCE_DIR}/conf/systems.conf.in" "${PROJECT_BINARY_DIR}/conf/systems.conf")

# add the binary tree to the search path for include files
include_directories("${PROJECT_BINARY_DIR}/src/include")
include_directories("${PROJECT_SOURCE_DIR}/src/include")
include_directories("${PROJECT_SOURCE_DIR}/submodules/backward-cpp")
include_directories("${PROJECT_SOURCE_DIR}/submodules/json/single_include/nlohmann")
include_directories("${PROJECT_SOURCE_DIR}/submodules/fifo_map/src")
include_directories("${PROJECT_SOURCE_DIR}/src/runtime")
include_directories("${PROJECT_BINARY_DIR}/src/runtime")
# link_directories("${PROJECT_BINARY_DIR}/src/lib")

FIND_PACKAGE(Boost 1.40 COMPONENTS regex REQUIRED)
FIND_PACKAGE(PythonInterp REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

#add_executable(mosaic mosaic.cpp config.cpp manager.cpp modulemanager.cpp importable.cpp revisions.cpp)
add_executable(mosaic mosaic.cpp options.cpp modules.cpp importable.cpp)

TARGET_LINK_LIBRARIES(mosaic LINK_PUBLIC ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(mosaic LINK_PUBLIC "${PROJECT_BINARY_DIR}/src/lib/mosaic/libmosaic.a")
TARGET_LINK_LIBRARIES(mosaic LINK_PUBLIC dl)
#TARGET_LINK_LIBRARIES(mosaic LINK_PUBLIC stdc++fs)
TARGET_LINK_LIBRARIES(mosaic LINK_PUBLIC bfd)

install (TARGETS "mosaic" DESTINATION ${MOSAIC_BIN_DIR})
#install (FILES "${PROJECT_BINARY_DIR}/conf/mosaic.conf" DESTINATION "etc/mosaic")
#install (FILES "${PROJECT_BINARY_DIR}/conf/modules.conf" DESTINATION "etc/mosaic")
#install (FILES "${PROJECT_BINARY_DIR}/conf/languages.conf" DESTINATION "etc/mosaic")
#install (FILES "${PROJECT_BINARY_DIR}/conf/storage.conf" DESTINATION "etc/mosaic")
#install (FILES "${PROJECT_BINARY_DIR}/conf/systems.conf" DESTINATION "etc/mosaic")
#install (FILES "${PROJECT_SOURCE_DIR}/tools/hocon2json" DESTINATION "bin" PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_READ WORLD_EXECUTE)
#install (DIRECTORY "${PROJECT_SOURCE_DIR}/python/modtool" DESTINATION "lib/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/dist-packages")
