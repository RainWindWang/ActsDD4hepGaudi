#pragma once

#include "GaudiKernel/Service.h"
#include <Gaudi/Property.h>
#include "GaudiKernel/StatusCode.h"

#include "Acts/Geometry/TrackingGeometry.hpp"
#include "Acts/Geometry/GeometryContext.hpp"

#include "Geometry/IActsDD4hepGeometrySvc.h"

// builds Acts TrackingGeometry from existing DD4hep geometry
class ActsPluginGeometrySvc
  : public extends<Service, IInterface> {

public:
  using extends::extends;

  StatusCode initialize() override;
  StatusCode finalize() override;

  // Get Acts TrackingGeometry
  const Acts::TrackingGeometry* trackingGeometry() const { return m_trackingGeo.get(); }

  // Access geometry context
  const Acts::GeometryContext& geometryContext() const { return m_geoCtx; }

private:
  // Name of existing ActsDD4hepGeometrySvc
  Gaudi::Property<std::string> m_dd4hepSvcName{
      this, "DD4hepSvcName", "ActsDD4hepGeometrySvc",
      "Name of the DD4hep geometry service providing dd4hep::Detector"};

  // Optionally write OBJ geometry
  Gaudi::Property<bool> m_writeObj{
      this, "WriteObj", false, "Write OBJ geometry file"};

  Gaudi::Property<std::string> m_objFileName{
      this, "ObjFileName", "acts_geometry.obj",
      "Path of the OBJ output file"};

private:
  IActsDD4hepGeometrySvc* m_dd4hepSvc = nullptr;

  std::unique_ptr<const Acts::TrackingGeometry> m_trackingGeo;
  Acts::GeometryContext m_geoCtx;

  StatusCode writeObjFile();
};

