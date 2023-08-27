find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_AARONIA_RTSA gnuradio-aaronia_rtsa)

FIND_PATH(
    GR_AARONIA_RTSA_INCLUDE_DIRS
    NAMES gnuradio/aaronia_rtsa/api.h
    HINTS $ENV{AARONIA_RTSA_DIR}/include
        ${PC_AARONIA_RTSA_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_AARONIA_RTSA_LIBRARIES
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

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-aaronia_rtsaTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_AARONIA_RTSA DEFAULT_MSG GR_AARONIA_RTSA_LIBRARIES GR_AARONIA_RTSA_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_AARONIA_RTSA_LIBRARIES GR_AARONIA_RTSA_INCLUDE_DIRS)
