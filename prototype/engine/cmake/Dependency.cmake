# This list is required for static link. 
set(WS_LINKER_LIBS "")

# ---[ Threads
find_package(Threads REQUIRED)
list(APPEND WS_LINKER_LIBS ${CMAKE_THREAD_LIBS_INIT})

# ---[ Google-glog
include("glog.cmake")
include_directories(SYSTEM ${GLOG_INCLUDE_DIRS})
list(APPEND WS_LINKER_LIBS ${GLOG_LIBRARIES})

# ---[ Google-protobuf
include(cmake/ProtoBuf.cmake)

# ---[ OpenCV
find_package(OpenCV QUIET COMPONENTS imgcodecs)
if(OPENCV_IMGCODECS_FOUND)
  find_package(OpenCV REQUIRED COMPONENTS core imgcodecs highgui imgproc videoio video)
  message(STATUS "Found OpenCV 3.x: ${OpenCV_CONFIG_PATH}")
else()
  find_package(OpenCV REQUIRED COMPONENTS core highgui imgproc)
  message(STATUS "Found OpenCV 2.x: ${OpenCV_CONFIG_PATH}")
endif()
include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS})
list(APPEND WS_LINKER_LIBS ${OpenCV_LIBS})
