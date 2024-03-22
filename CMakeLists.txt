cmake_minimum_required(VERSION 3.20.0)
project(duneprofiling VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

# If the build type is not set, we want a Releas build.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()

#add_compile_options(-Wall -Wextra -Wpedantic -Ofast -march=native -mfma -funsafe-math-optimizations -ffinite-math-only -fno-signed-zeros -funroll-loops -fverbose-asm -mprefer-vector-width=128 -momit-leaf-frame-pointer)

#if($CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#  add_compile_options(-mpreferred-stack-boundary=4 -malign-data=cacheline)
#endif()

Include(FetchContent)


# We use nanobench for simple benchmarking
FetchContent_Declare(
  nanobench
  GIT_REPOSITORY https://github.com/martinus/nanobench.git
  GIT_TAG v4.1.0
  GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(nanobench)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 10.2.1
  GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(fmt)

add_library(operations SHARED operations.cc)
add_library(fill_functions SHARED fill_functions.cc)

add_executable(fast_acos_t fast_acos_t.cc ieee_acos.cc)
target_link_libraries(fast_acos_t PRIVATE nanobench)

add_executable(fast_atan_t fast_atan_t.cc)
target_link_libraries(fast_atan_t PRIVATE nanobench)

add_executable(omega_t omega_t.cc)
target_link_libraries(omega_t PRIVATE nanobench)

add_executable(simphotons_choices simphotons_choices.cc)
target_link_libraries(simphotons_choices PRIVATE operations operations fill_functions nanobench fmt)

