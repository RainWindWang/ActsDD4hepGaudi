#include "ActsPluginGeometrySvc.h"

#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/MsgStream.h"

#include "Acts/Visualization/ObjVisualization3D.hpp"
#include "Acts/Visualization/GeometryView3D.hpp"

// ActsPlugins headers
#include "ActsPlugins/DD4hep/ConvertDD4hepDetector.hpp"

DECLARE_COMPONENT(ActsPluginGeometrySvc)

StatusCode ActsPluginGeometrySvc::initialize() {
  StatusCode sc = Service::initialize();
  if (!sc.isSuccess()) return sc;

  info() << "Initializing ActsPluginGeometrySvc" << endmsg;

  // Retrieve DD4hep geometry service
  m_dd4hepSvc = Gaudi::svcLocator()->service<IActsDD4hepGeometrySvc>(m_dd4hepSvcName);
  if (!m_dd4hepSvc) {
    error() << "Failed to retrieve DD4hep geometry service '"
            << m_dd4hepSvcName << "'" << endmsg;
    return StatusCode::FAILURE;
  }

  dd4hep::Detector* det = m_dd4hepSvc->detector();
  if (!det) {
    error() << "DD4hep detector pointer is null!" << endmsg;
    return StatusCode::FAILURE;
  }

  // Build Acts geometry
  auto logger = Acts::getDefaultLogger("ActsPluginGeometry", Acts::Logging::INFO);

  info() << "Converting DD4hep -> Acts TrackingGeometry ..." << endmsg;

  m_trackingGeo = ActsPlugins::convertDD4hepDetector(
      det->world(), *logger,
      Acts::equidistant, Acts::equidistant, Acts::equidistant,
      Acts::UnitConstants::mm, Acts::UnitConstants::mm,
      Acts::UnitConstants::fm,
      ActsPlugins::sortDetElementsByID,
      m_geoCtx);

  if (!m_trackingGeo) {
    error() << "Failed to convert DD4hep geometry to Acts TrackingGeometry" << endmsg;
    return StatusCode::FAILURE;
  }

  info() << "TrackingGeometry successfully built." << endmsg;

  // Optional: write OBJ file
  if (m_writeObj) {
    return writeObjFile();
  }

  return StatusCode::SUCCESS;
}

StatusCode ActsPluginGeometrySvc::finalize() {
  info() << "Finalizing ActsPluginGeometrySvc" << endmsg;
  m_trackingGeo.reset();
  return Service::finalize();
}

StatusCode ActsPluginGeometrySvc::writeObjFile() {
  info() << "Writing OBJ geometry file: " << m_objFileName << endmsg;

  Acts::ObjVisualization3D objWriter;

  m_trackingGeo->visitSurfaces([&](const Acts::Surface* surface) {
    if (!surface) return;
    Acts::GeometryView3D::drawSurface(objWriter, *surface, m_geoCtx);
  });

  objWriter.write(m_objFileName.value());

  info() << "OBJ file written successfully." << endmsg;
  return StatusCode::SUCCESS;
}

// Declare as Gaudi component
DECLARE_COMPONENT(ActsPluginGeometrySvc)
