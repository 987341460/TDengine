CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(TDengine)

INCLUDE_DIRECTORIES(${TD_COMMUNITY_DIR}/src/inc)
INCLUDE_DIRECTORIES(${TD_COMMUNITY_DIR}/src/client/inc)
INCLUDE_DIRECTORIES(${TD_OS_DIR}/inc)
INCLUDE_DIRECTORIES(inc)

IF (TD_LINUX_64)
  AUX_SOURCE_DIRECTORY(./src SRC)
  LIST(REMOVE_ITEM SRC ./src/shellWindows.c)
  ADD_EXECUTABLE(shell ${SRC})  
  TARGET_LINK_LIBRARIES(shell taos_static)
  SET_TARGET_PROPERTIES(shell PROPERTIES OUTPUT_NAME taos)
ELSEIF (TD_WINDOWS_64)
  INCLUDE_DIRECTORIES(${TD_COMMUNITY_DIR}/deps/pthread)
  INCLUDE_DIRECTORIES(${TD_COMMUNITY_DIR}/deps/regex)
  LIST(APPEND SRC ./src/shellEngine.c)
  LIST(APPEND SRC ./src/shellMain.c)
  LIST(APPEND SRC ./src/shellWindows.c)
  ADD_EXECUTABLE(shell ${SRC})
  TARGET_LINK_LIBRARIES(shell taos_static)
  SET_TARGET_PROPERTIES(shell PROPERTIES OUTPUT_NAME taos)
ELSEIF (TD_DARWIN_64)
  LIST(APPEND SRC ./src/shellEngine.c)
  LIST(APPEND SRC ./src/shellMain.c)
  LIST(APPEND SRC ./src/shellWindows.c)
  ADD_EXECUTABLE(shell ${SRC})
  TARGET_LINK_LIBRARIES(shell taos_static)
  SET_TARGET_PROPERTIES(shell PROPERTIES OUTPUT_NAME taos)
ENDIF ()

