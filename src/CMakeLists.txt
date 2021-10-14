
set (CMAKE_CXX_STANDARD 17)

function(BUILDPATH PATH)
	set(LPATH "")
	foreach(arg IN LISTS ARGN)
		IF (NOT ${LPATH} MATCHES "/$")
			set(LPATH ${LPATH}/)
		ENDIF()
		set(LPATH ${LPATH}${arg})
	endforeach()
	set(${PATH} ${LPATH} PARENT_SCOPE)
endfunction(BUILDPATH)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/modules)

BUILDPATH(MOSAIC_CONFIG_DIR ${CMAKE_INSTALL_PREFIX} "etc/mosaic")
BUILDPATH(MOSAIC_BIN_DIR ${CMAKE_INSTALL_PREFIX} "bin")
BUILDPATH(MOSAIC_DATA_DIR ${CMAKE_INSTALL_PREFIX} "var/lib/mosaic")
BUILDPATH(MOSAIC_LIB_DIR ${CMAKE_INSTALL_PREFIX} "lib")
BUILDPATH(MOSAIC_MODULE_DIR ${CMAKE_INSTALL_PREFIX} "lib/mosaic")

add_compile_options(-fPIC -std=c++17 -Wno-literal-suffix -g)

IF(${CMAKE_INSTALL_PREFIX} STREQUAL "/")
	set (MOSAIC_BIN_DIR "/usr/bin")
ENDIF()

MESSAGE(STATUS "")
MESSAGE(STATUS "Mosaic configuration summary:")
MESSAGE(STATUS "")
MESSAGE(STATUS "  CMake Module Path ............................ : ${CMAKE_MODULE_PATH}")
MESSAGE(STATUS "  Configuration directory ...................... : ${MOSAIC_CONFIG_DIR}")
MESSAGE(STATUS "  Binary directory ............................. : ${MOSAIC_BIN_DIR}")
MESSAGE(STATUS "  Data directory ............................... : ${MOSAIC_DATA_DIR}")
MESSAGE(STATUS "  Lib directory ................................ : ${MOSAIC_LIB_DIR}")
MESSAGE(STATUS "  Module directory ............................. : ${MOSAIC_MODULE_DIR}")
MESSAGE(STATUS "")

add_subdirectory(lib)
#add_subdirectory(modules)
add_subdirectory(runtime)
#add_subdirectory(test)