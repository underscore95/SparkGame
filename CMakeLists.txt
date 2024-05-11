# CMakeList.txt : CMake project for SparkGame, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SparkGame")

include(C:/libs/vcpkg-master/scripts/buildsystems/vcpkg.cmake) # REPLACE PATH

add_executable (SparkGame "src/Main.cpp" "src/GameApp.h" "src/GameApp.cpp" "src/TestComponent.h" "src/TestSystem.h" "src/TestSystem.cpp")

find_package(glm REQUIRED)
target_link_libraries(SparkGame PUBLIC glm::glm)

link_directories("C:/Coding/C++/Spark/Spark/out/build/x64-debug/Spark.dll") # REPLACE PATH
include_directories("C:/Coding/C++/Spark/Spark/out/build/x64-debug/include/") # REPLACE PATH
target_link_libraries(SparkGame PRIVATE Spark.dll)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SparkGame PROPERTY CXX_STANDARD 20)
endif()