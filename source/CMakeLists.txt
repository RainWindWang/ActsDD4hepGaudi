# ActsDD4hepGaudi/source/CMakeLists.txt

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Geometry
  ${CMAKE_CURRENT_SOURCE_DIR}/Algorithms
)

set(sources
  Geometry/ActsDD4hepGeometrySvc.cpp
  Algorithms/DumpActsGeometryAlg.cpp
)

gaudi_add_module(ActsDD4hepGeometry
  SOURCES ${sources}
  LINK
    Gaudi::GaudiKernel
    DD4hep::DDCore
    Acts::Core
    Acts::PluginDD4hep
)

install(TARGETS ActsDD4hepGeometry
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" COMPONENT bin
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT shlib
  COMPONENT dev
)
