include(ExternalProject)

set(NAME sndfile)
set(VERSION 1.0.28)
set(PREFIX ${EP_DEPENDENCIES_PATH}/${NAME})

message (STATUS "Adding ${NAME}:${VERSION} as an external project.")

ExternalProject_Add(${NAME}
  URL http://www.mega-nerd.com/libsndfile/files/libsndfile-${VERSION}.tar.gz
  UPDATE_DISCONNECTED ON
  BUILD_IN_SOURCE ON
  CONFIGURE_COMMAND ./configure --prefix ${PREFIX}
  CMAKE_COMMAND ""
)

set(SNDFILE_INCLUDE_DIR ${PREFIX}/include PARENT_SCOPE)
set(SNDFILE_LIB_DIR ${PREFIX}/lib PARENT_SCOPE)
set(SNDFILE_LIBRARIES
        -lsndfile
PARENT_SCOPE)