#include "DumpActsTrackingGeometryAlg.h"

DumpActsTrackingGeometryAlg::DumpActsTrackingGeometryAlg(
    const std::string& name, ISvcLocator* svcLoc)
    : Gaudi::Algorithm(name, svcLoc)
{}

StatusCode DumpActsTrackingGeometryAlg::initialize() {
  StatusCode sc = Gaudi::Algorithm::initialize();
  if (!sc.isSuccess()) return sc;

  info() << "Initializing DumpActsTrackingGeometryAlg" << endmsg;

  if (!m_tgSvc.retrieve().isSuccess()) {
    error() << "Failed to retrieve IActsTrackingGeometrySvc '"
            << m_tgSvc.name() << "'" << endmsg;
    return StatusCode::FAILURE;
  }

  info() << "Retrieved tracking geometry service: "
         << m_tgSvc.name() << endmsg;

  return StatusCode::SUCCESS;
}

StatusCode DumpActsTrackingGeometryAlg::execute(const EventContext&) const {
  auto tgPtr = m_tgSvc->trackingGeometry();
  if (!tgPtr) {
    error() << "TrackingGeometry is nullptr!" << endmsg;
    return StatusCode::FAILURE;
  }

  const Acts::TrackingVolume* world = tgPtr->highestTrackingVolume();
  if (!world) {
    error() << "TrackingGeometry->highestTrackingVolume() returned nullptr"
            << endmsg;
    return StatusCode::FAILURE;
  }

  info() << "Dumping tracking geometry hierarchy..." << endmsg;

  dumpVolume(*world, "");

  return StatusCode::SUCCESS;
}

StatusCode DumpActsTrackingGeometryAlg::finalize() {
  info() << "Finalizing DumpActsTrackingGeometryAlg" << endmsg;
  return Gaudi::Algorithm::finalize();
}

void DumpActsTrackingGeometryAlg::dumpVolume(
    const Acts::TrackingVolume& v,
    const std::string& indent) const
{
  info() << indent << "Volume: " << v.volumeName() << endmsg;

  // Dump boundary surfaces
  for (const auto& bs : v.boundarySurfaces()) {
    info() << indent << "  BoundarySurface: "
           << bs->surfaceRepresentation().name()
           << " ID=" << bs->surfaceRepresentation().geometryId()
           << endmsg;
  }

  // Dump surfaces in the volume
  for (const auto& srf : v.surfaces()) {
    info() << indent << "  Surface: " << srf.name()
           << " ID=" << srf.geometryId()
           << endmsg;
  }

  // Dump contained volumes
  for (const Acts::TrackingVolume& child : v.volumes()) {
    dumpVolume(child, indent + "  ");
  }
}


// Declare as Gaudi component
DECLARE_COMPONENT(DumpActsTrackingGeometryAlg)

