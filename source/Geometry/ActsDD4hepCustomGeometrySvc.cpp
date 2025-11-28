/////////////////////////////////////////
// place holder
/////////////////////////////////////////

#include "Geometry/ActsDD4hepCustomGeometrySvc.h"

#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/StatusCode.h"

#include "Acts/Geometry/GeometryContext.hpp"

StatusCode ActsDD4hepCustomGeometrySvc::initialize() {
  StatusCode sc = Service::initialize();
  if (!sc.isSuccess()) return sc;

  info() << "Initializing ActsDD4hepCustomGeometrySvc" << endmsg;

  if (!m_dd4hepSvc.retrieve().isSuccess()) {
    error() << "Failed to retrieve DD4hep loader service" << endmsg;
    return StatusCode::FAILURE;
  }

  info() << "DD4hep -> ACTS geometry builder not implemented yet." << endmsg;

  return StatusCode::SUCCESS;
}

StatusCode ActsDD4hepCustomGeometrySvc::finalize() {
  info() << "Finalizing ActsDD4hepCustomGeometrySvc" << endmsg;
  return Service::finalize();
}

const Acts::TrackingGeometry*
ActsDD4hepCustomGeometrySvc::trackingGeometry() const {
  return nullptr;
}

Acts::GeometryContext ActsDD4hepCustomGeometrySvc::geometryContext() const {
  return Acts::GeometryContext();
}

// Declare as Gaudi component
DECLARE_COMPONENT(ActsDD4hepCustomGeometrySvc)

