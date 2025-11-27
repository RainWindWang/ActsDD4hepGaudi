# ActsDD4hepGaudi/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

project(ActsDD4hepGaudi VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# dependence: ACTs from local
find_package(Gaudi REQUIRED)
find_package(DD4hep REQUIRED COMPONENTS DDCore)
find_package(Acts REQUIRED COMPONENTS Core PluginDD4hep)

message(STATUS "Gaudi version: ${Gaudi_VERSION}")
message(STATUS "DD4hep version: ${DD4hep_VERSION}")
message(STATUS "Acts version: ${Acts_VERSION}")

add_subdirectory(source)
