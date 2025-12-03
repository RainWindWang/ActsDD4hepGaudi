#ifndef ACTSPLUGINGEOMETRYSVC_H
#define ACTSPLUGINGEOMETRYSVC_H

#include "Geometry/IActsTrackingGeometrySvc.h"
#include "Geometry/IActsDD4hepGeometrySvc.h"

#include "GaudiKernel/Service.h"
#include <Gaudi/Property.h>

#include "Acts/Geometry/TrackingGeometry.hpp"
#include "Acts/Geometry/GeometryContext.hpp"

#include <memory>

class ActsPluginGeometrySvc
  : public extends<Service, IActsTrackingGeometrySvc> {

public:
  using extends::extends;

  StatusCode initialize() override;
  StatusCode finalize() override;

  const Acts::TrackingGeometry*
      trackingGeometry() const override;

  const Acts::GeometryContext&
      geoContext() const override;
  
  std::string buildMode() const override;

private:
  Gaudi::Property<std::string> m_dd4hepSvcName{
      this, "DD4hepSvc", "ActsDD4hepGeometrySvc",
      "Name of DD4hep geometry service"};

  SmartIF<IActsDD4hepGeometrySvc> m_dd4hepSvc;

  std::shared_ptr<const Acts::TrackingGeometry> m_trackingGeometry;

  Acts::GeometryContext m_geoCtx;

  Gaudi::Property<bool> m_writeObj{
      this, "WriteObj", false, "Write OBJ geometry"};

  Gaudi::Property<std::string> m_objFileName{
      this, "ObjFile", "actsGeometry.obj", "OBJ file name"};
};

#endif
