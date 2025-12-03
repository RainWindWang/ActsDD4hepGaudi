#include "DumpActsTrackingGeometryAlg.h"

#include "Acts/Visualization/GeometryView3D.hpp"
#include "Acts/Visualization/ObjVisualization3D.hpp"

DECLARE_COMPONENT(DumpActsTrackingGeometryAlg)

DumpActsTrackingGeometryAlg::DumpActsTrackingGeometryAlg(
    const std::string& name, ISvcLocator* svcLoc)
    : Gaudi::Algorithm(name, svcLoc) {}

StatusCode DumpActsTrackingGeometryAlg::initialize() {
  StatusCode sc = Gaudi::Algorithm::initialize();
  if (!sc.isSuccess()) {
    return sc;
  }

  info() << "Initializing DumpActsTrackingGeometryAlg" << endmsg;

  if (!m_tgSvc.retrieve().isSuccess()) {
    error() << "Failed to retrieve IActsTrackingGeometrySvc '"
            << m_tgSvc.name() << "'" << endmsg;
    return StatusCode::FAILURE;
  }

  info() << "Retrieved tracking geometry service: " << m_tgSvc.name()
         << endmsg;

  info() << "OBJ writing is " << (m_writeObj ? "ENABLED" : "DISABLED")
         << ", file = '" << m_objFileName.value() << "'" << endmsg;

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

  info() << "Dumping ACTS tracking geometry hierarchy..." << endmsg;
  dumpVolume(*world, "");

  if (m_writeObj) {
    info() << "Writing OBJ geometry file: '" << m_objFileName.value()
           << "'" << endmsg;

    Acts::ObjVisualization3D objWriter;

    const Acts::GeometryContext& gctx = m_tgSvc->geoContext();

    tgPtr->visitSurfaces(
        [&](const Acts::Surface* surface) {
          if (!surface) {
            return;
          }
          Acts::GeometryView3D::drawSurface(objWriter, *surface, gctx);
        });

    objWriter.write(m_objFileName.value());

    info() << "OBJ file written successfully: '" << m_objFileName.value()
           << "'" << endmsg;
  }

  return StatusCode::SUCCESS;
}

StatusCode DumpActsTrackingGeometryAlg::finalize() {
  info() << "Finalizing DumpActsTrackingGeometryAlg" << endmsg;
  return Gaudi::Algorithm::finalize();
}

void DumpActsTrackingGeometryAlg::dumpVolume(const Acts::TrackingVolume& v,
                                             const std::string& indent) const {
  info() << indent << "Volume: " << v.volumeName() << endmsg;

  // Boundary surfaces
  const auto& bSurfaces = v.boundarySurfaces();
  info() << indent << "  #BoundarySurfaces = " << bSurfaces.size() << endmsg;
  for (const auto& bs : bSurfaces) {
    const auto& sr = bs->surfaceRepresentation();
    info() << indent << "    BoundarySurface: " << sr.name()
           << "  GeoID=" << sr.geometryId() << endmsg;
  }

  // Surfaces inside this volume
  const auto& surfaces = v.surfaces();
  info() << indent << "  #Surfaces = " << surfaces.size() << endmsg;
  for (const auto& srf : surfaces) {
    info() << indent << "    Surface: " << srf.name()
           << "  GeoID=" << srf.geometryId() << endmsg;
  }

  // Child volumes
  const auto& children = v.volumes();
  info() << indent << "  #ChildVolumes = " << children.size() << endmsg;
  for (const Acts::TrackingVolume& child : children) {
    dumpVolume(child, indent + "  ");
  }
}


// Declare as Gaudi component
DECLARE_COMPONENT(DumpActsTrackingGeometryAlg)
