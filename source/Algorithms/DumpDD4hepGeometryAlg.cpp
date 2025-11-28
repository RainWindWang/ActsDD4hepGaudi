#include "DumpDD4hepGeometryAlg.h"

#include "DD4hep/Detector.h"
#include "DD4hep/Objects.h"

DumpDD4hepGeometryAlg::DumpDD4hepGeometryAlg(
    const std::string& name, ISvcLocator* svcLoc)
    : Gaudi::Algorithm(name, svcLoc) {}

StatusCode DumpDD4hepGeometryAlg::initialize() {
  StatusCode sc = Gaudi::Algorithm::initialize();
  if (!sc.isSuccess()) return sc;

  info() << "Initializing DumpDD4hepGeometryAlg" << endmsg;

  if (!m_geoSvc.retrieve().isSuccess()) {
    error() << "Failed to retrieve DD4hep geometry service: "
            << m_geoSvc.name() << endmsg;
    return StatusCode::FAILURE;
  }

  return StatusCode::SUCCESS;
}

StatusCode DumpDD4hepGeometryAlg::execute(const EventContext&) const {
  if (m_printed) return StatusCode::SUCCESS;

  const dd4hep::Detector* det = m_geoSvc->detector();
  if (!det) {
    error() << "DD4hep geometry service returned null detector" << endmsg;
    return StatusCode::FAILURE;
  }

  // print something for cross check

  // world
  auto world = det->world();
  info() << "World DetElement name: " << world.name() << endmsg;

  // subdetectors
  for (const auto& it : det->detectors()) {
    const dd4hep::DetElement& de = it.second;
    info() << "  Subdetector: name=" << de.name()
           << ", id=" << de.id() << endmsg;
  }

  m_printed = true;
  return StatusCode::SUCCESS;
}

StatusCode DumpDD4hepGeometryAlg::finalize() {
  info() << "Finalizing DumpDD4hepGeometryAlg" << endmsg;
  return Gaudi::Algorithm::finalize();
}


// Declare as Gaudi component
DECLARE_COMPONENT(DumpDD4hepGeometryAlg)

