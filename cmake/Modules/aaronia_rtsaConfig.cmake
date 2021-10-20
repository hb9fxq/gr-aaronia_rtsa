INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_AARONIA_RTSA aaronia_rtsa)

FIND_PATH(
    AARONIA_RTSA_INCLUDE_DIRS
    NAMES aaronia_rtsa/api.h
    HINTS $ENV{AARONIA_RTSA_DIR}/include
        ${PC_AARONIA_RTSA_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    AARONIA_RTSA_LIBRARIES
    NAMES gnuradio-aaronia_rtsa
    HINTS $ENV{AARONIA_RTSA_DIR}/lib
        ${PC_AARONIA_RTSA_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/aaronia_rtsaTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(AARONIA_RTSA DEFAULT_MSG AARONIA_RTSA_LIBRARIES AARONIA_RTSA_INCLUDE_DIRS)
MARK_AS_ADVANCED(AARONIA_RTSA_LIBRARIES AARONIA_RTSA_INCLUDE_DIRS)
