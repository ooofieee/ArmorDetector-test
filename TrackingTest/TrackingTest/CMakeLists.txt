# CMakeList.txt: TrackingTest 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/resources)

#include_directories("/home/ooofieee/lib/opencv4.10.0_install/include/opencv4")
#link_directories("/home/ooofieee/lib/opencv4.10.0_install/lib")

find_package(OpenCV REQUIRED)

# 将源代码添加到此项目的可执行文件。
add_executable (TrackingTest "src/TrackingTest.cpp"  "src/findLightBar.cpp" "src/findNum_cascade.cpp" "src/cascadeThreadPool.cpp")

target_link_libraries(TrackingTest ${OpenCV_LIBS})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TrackingTest PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
