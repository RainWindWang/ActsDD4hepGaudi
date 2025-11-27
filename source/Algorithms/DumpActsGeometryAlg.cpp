#include "Geometry/IActsDD4hepGeometrySvc.h"

#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/ServiceHandle.h"
#include "GaudiKernel/StatusCode.h"
#include "GaudiKernel/EventContext.h"

#include "DD4hep/Detector.h"
#include "DD4hep/Objects.h"

class DumpActsGeometryAlg : public Gaudi::Algorithm {
public:
  DumpActsGeometryAlg(const std::string& name, ISvcLocator* svcLoc)
    : Gaudi::Algorithm(name, svcLoc) {}

  StatusCode initialize() override {
    StatusCode sc = Gaudi::Algorithm::initialize();
    if (!sc.isSuccess()) return sc;

    info() << "Initializing DumpActsGeometryAlg" << endmsg;

    if (!m_geoSvc.retrieve().isSuccess()) {
      error() << "Failed to retrieve IActsDD4hepGeometrySvc '"
              << m_geoSvc.name() << "'" << endmsg;
      return StatusCode::FAILURE;
    }

    info() << "Retrieved geometry service: " << m_geoSvc.name() << endmsg;
    return StatusCode::SUCCESS;
  }

  StatusCode execute(const EventContext& /*ctx*/) const override {
    if (m_printed) return StatusCode::SUCCESS;

    const dd4hep::Detector* det = m_geoSvc->detector();
    if (!det) {
      error() << "Geometry service returned null dd4hep::Detector" << endmsg;
      return StatusCode::FAILURE;
    }

    // world DetElement
    auto world = det->world();
    info() << "World DetElement name: " << world.name() << endmsg;

    // subdetector elements
    for (const auto& it : det->detectors()) {
      const dd4hep::DetElement& de = it.second;
      info() << "  Subdetector: name=" << de.name()
             << ", id=" << de.id() << endmsg;
    }

    m_printed = true;
    return StatusCode::SUCCESS;
  }

  StatusCode finalize() override {
    info() << "Finalizing DumpActsGeometryAlg" << endmsg;
    return Gaudi::Algorithm::finalize();
  }

private:
  ServiceHandle<IActsDD4hepGeometrySvc> m_geoSvc{
      this, "ActsGeometrySvc", "ActsDD4hepGeometrySvc",
      "Service providing DD4hep / ACTS geometry"};

  mutable bool m_printed{false};
};

DECLARE_COMPONENT(DumpActsGeometryAlg)
