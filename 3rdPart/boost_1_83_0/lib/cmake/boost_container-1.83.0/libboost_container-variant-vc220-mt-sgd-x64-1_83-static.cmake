# Generated by Boost 1.83.0

# address-model=64

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
  _BOOST_SKIPPED("libboost_container-vc220-mt-sgd-x64-1_83.lib" "64 bit, need 32")
  return()
endif()

# layout=versioned

# toolset=vc220

if(Boost_COMPILER)
  if(NOT "vc220" IN_LIST Boost_COMPILER AND NOT "-vc220" IN_LIST Boost_COMPILER)
    _BOOST_SKIPPED("libboost_container-vc220-mt-sgd-x64-1_83.lib" "vc220, Boost_COMPILER=${Boost_COMPILER}")
    return()
  endif()
else()
  if(BOOST_DETECTED_TOOLSET AND NOT BOOST_DETECTED_TOOLSET STREQUAL "vc220")
    _BOOST_SKIPPED("libboost_container-vc220-mt-sgd-x64-1_83.lib" "vc220, detected ${BOOST_DETECTED_TOOLSET}, set Boost_COMPILER to override")
    return()
  endif()
endif()

# link=static

if(DEFINED Boost_USE_STATIC_LIBS)
  if(NOT Boost_USE_STATIC_LIBS)
    _BOOST_SKIPPED("libboost_container-vc220-mt-sgd-x64-1_83.lib" "static, Boost_USE_STATIC_LIBS=${Boost_USE_STATIC_LIBS}")
    return()
  endif()
else()
  if(NOT WIN32 AND NOT _BOOST_SINGLE_VARIANT)
    _BOOST_SKIPPED("libboost_container-vc220-mt-sgd-x64-1_83.lib" "static, default is shared, set Boost_USE_STATIC_LIBS=ON to override")
    return()
  endif()
endif()

# runtime-link=static

if(NOT Boost_USE_STATIC_RUNTIME)
  _BOOST_SKIPPED("libboost_container-vc220-mt-sgd-x64-1_83.lib" "static runtime, Boost_USE_STATIC_RUNTIME not ON")
  return()
endif()

# runtime-debugging=on

if(NOT "${Boost_USE_DEBUG_RUNTIME}" STREQUAL "" AND NOT Boost_USE_DEBUG_RUNTIME)
  _BOOST_SKIPPED("libboost_container-vc220-mt-sgd-x64-1_83.lib" "debug runtime, Boost_USE_DEBUG_RUNTIME=${Boost_USE_DEBUG_RUNTIME}")
  return()
endif()

# threading=multi

if(DEFINED Boost_USE_MULTITHREADED AND NOT Boost_USE_MULTITHREADED)
  _BOOST_SKIPPED("libboost_container-vc220-mt-sgd-x64-1_83.lib" "multithreaded, Boost_USE_MULTITHREADED=${Boost_USE_MULTITHREADED}")
  return()
endif()

# variant=debug

if(NOT "${Boost_USE_DEBUG_LIBS}" STREQUAL "" AND NOT Boost_USE_DEBUG_LIBS)
  _BOOST_SKIPPED("libboost_container-vc220-mt-sgd-x64-1_83.lib" "debug, Boost_USE_DEBUG_LIBS=${Boost_USE_DEBUG_LIBS}")
  return()
endif()

if(Boost_VERBOSE OR Boost_DEBUG)
  message(STATUS "  [x] libboost_container-vc220-mt-sgd-x64-1_83.lib")
endif()

# Create imported target Boost::container

if(NOT TARGET Boost::container)
  add_library(Boost::container STATIC IMPORTED)

  set_target_properties(Boost::container PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${_BOOST_INCLUDEDIR}"
    INTERFACE_COMPILE_DEFINITIONS "BOOST_CONTAINER_NO_LIB"
  )
endif()

# Target file name: libboost_container-vc220-mt-sgd-x64-1_83.lib

get_target_property(__boost_imploc Boost::container IMPORTED_LOCATION_DEBUG)
if(__boost_imploc)
  message(SEND_ERROR "Target Boost::container already has an imported location '${__boost_imploc}', which is being overwritten with '${_BOOST_LIBDIR}/libboost_container-vc220-mt-sgd-x64-1_83.lib'")
endif()
unset(__boost_imploc)

set_property(TARGET Boost::container APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)

set_target_properties(Boost::container PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG CXX
  IMPORTED_LOCATION_DEBUG "${_BOOST_LIBDIR}/libboost_container-vc220-mt-sgd-x64-1_83.lib"
  )

list(APPEND _BOOST_CONTAINER_DEPS headers)
