CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(TDengine)

INCLUDE_DIRECTORIES(inc)
INCLUDE_DIRECTORIES(jni)
INCLUDE_DIRECTORIES(${TD_COMMUNITY_DIR}/src/inc)
INCLUDE_DIRECTORIES(${TD_OS_DIR}/inc)
AUX_SOURCE_DIRECTORY(./src SRC)

IF (TD_LINUX_64)
  INCLUDE_DIRECTORIES(${TD_COMMUNITY_DIR}/deps/jni/linux)

  # set the static lib name
  ADD_LIBRARY(taos_static STATIC ${SRC})
  TARGET_LINK_LIBRARIES(taos_static trpc tutil pthread m rt)
  SET_TARGET_PROPERTIES(taos_static PROPERTIES OUTPUT_NAME "taos_static")
  SET_TARGET_PROPERTIES(taos_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

  # generate dynamic library (*.so)
  ADD_LIBRARY(taos SHARED ${SRC})
  TARGET_LINK_LIBRARIES(taos trpc tutil pthread m rt)
  SET_TARGET_PROPERTIES(taos PROPERTIES CLEAN_DIRECT_OUTPUT 1)

  #set version of .so
  #VERSION    so version
  #SOVERSION  api version
  IF (TD_LITE)
    execute_process(COMMAND chmod 777 ${TD_COMMUNITY_DIR}/packaging/tools/get_version.sh)
    execute_process(COMMAND ${TD_COMMUNITY_DIR}/packaging/tools/get_version.sh ${TD_COMMUNITY_DIR}/src/util/src/version.c
          OUTPUT_VARIABLE
          VERSION_INFO)
    MESSAGE(STATUS "build lite version ${VERSION_INFO}")
  ELSE ()
    execute_process(COMMAND chmod 777 ${TD_COMMUNITY_DIR}/packaging/tools/get_version.sh)
    execute_process(COMMAND ${TD_COMMUNITY_DIR}/packaging/tools/get_version.sh ${TD_COMMUNITY_DIR}/src/util/src/version.c
            OUTPUT_VARIABLE
            VERSION_INFO)
    MESSAGE(STATUS "build cluster version ${VERSION_INFO}")
  ENDIF ()

  MESSAGE(STATUS "build version ${VERSION_INFO}")
  SET_TARGET_PROPERTIES(taos PROPERTIES VERSION ${VERSION_INFO} SOVERSION 1)
  
ELSEIF (TD_WINDOWS_64)
  INCLUDE_DIRECTORIES(${TD_COMMUNITY_DIR}/deps/jni/windows)
  INCLUDE_DIRECTORIES(${TD_COMMUNITY_DIR}/deps/jni/windows/win32)
  INCLUDE_DIRECTORIES(${TD_COMMUNITY_DIR}/deps/pthread)
  
  ADD_LIBRARY(taos_static STATIC ${SRC})
  TARGET_LINK_LIBRARIES(taos_static trpc tutil)

  # generate dynamic library (*.dll)
  ADD_LIBRARY(taos SHARED ${SRC})
  SET_TARGET_PROPERTIES(taos PROPERTIES LINK_FLAGS /DEF:${TD_COMMUNITY_DIR}/src/client/src/taos.def)
  TARGET_LINK_LIBRARIES(taos trpc)

ELSEIF (TD_DARWIN_64)
  INCLUDE_DIRECTORIES(${TD_COMMUNITY_DIR}/deps/jni/linux)

  ADD_LIBRARY(taos_static STATIC ${SRC})
  TARGET_LINK_LIBRARIES(taos_static trpc tutil pthread m)
  SET_TARGET_PROPERTIES(taos_static PROPERTIES OUTPUT_NAME "taos_static")

  # generate dynamic library (*.dylib)
  ADD_LIBRARY(taos SHARED ${SRC})
  TARGET_LINK_LIBRARIES(taos trpc tutil pthread m)
  
ENDIF ()

