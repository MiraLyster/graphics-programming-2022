# Install script for directory: C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/exercises

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/ITU-graphics-programming")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_1/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_10/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_10_solutions/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_11/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_11_solutions/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_12/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_12_solutions/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_1_solutions/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_2/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_2_solutions/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_3/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_3_solutions/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_4/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_4_solutions/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_5/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_5_solutions/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_6/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_6_solutions/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_7/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_7_solutions/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_8/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_8_solutions/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_9/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/exercise_9_solutions/cmake_install.cmake")
  include("C:/Users/Laustsen/Desktop/Graphics2022/graphics-programming-2022/builds/exercises/raytracer/cmake_install.cmake")

endif()

