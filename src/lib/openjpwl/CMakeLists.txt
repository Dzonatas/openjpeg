# Makefile for the main JPWL OpenJPEG codecs: JPWL_ j2k_to_image and JPWL_image_to_j2k

add_definitions(-DUSE_JPWL)

set(OPENJPEG_SRCS
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/bio.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/cio.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/dwt.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/event.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/image.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/j2k.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/jp2.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/jpt.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/mct.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/mqc.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/openjpeg.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/opj_clock.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/pi.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/raw.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/t1.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/t2.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/tcd.c
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/tgt.c
 ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2/function_list.c
)

set(JPWL_SRCS crc.c jpwl.c jpwl_lib.c rs.c)
if(APPLE)
  set_source_files_properties(
    rs.c
    PROPERTIES
    COMPILE_FLAGS -fno-common)
endif()

include_directories(
  ${OPENJPEG_BINARY_DIR}/src/lib/openjp2 # opj_config.h
  ${OPENJPEG_SOURCE_DIR}/src/lib/openjp2
  ${OPENJPEG_SOURCE_DIR}/src/lib
  )

# Build the library
if(WIN32)
  if(BUILD_SHARED_LIBS)
    add_definitions(-DOPJ_EXPORTS)
  else()
    add_definitions(-DOPJ_STATIC)
  endif()
endif()
add_library(openjpwl ${JPWL_SRCS} ${OPENJPEG_SRCS})
if(UNIX)
  target_link_libraries(openjpwl m)
endif()
set_target_properties(openjpwl
  PROPERTIES ${OPENJPEG_LIBRARY_PROPERTIES})

# Install library
install(TARGETS openjpwl
  EXPORT OpenJPEGTargets
  RUNTIME DESTINATION ${OPENJPEG_INSTALL_BIN_DIR} COMPONENT Applications
  LIBRARY DESTINATION ${OPENJPEG_INSTALL_LIB_DIR} COMPONENT Libraries
  ARCHIVE DESTINATION ${OPENJPEG_INSTALL_LIB_DIR} COMPONENT Libraries
)
