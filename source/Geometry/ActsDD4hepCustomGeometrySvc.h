#ifndef ACTS_DD4HEP_CUSTOM_GEOMETRY_SVC_H
#define ACTS_DD4HEP_CUSTOM_GEOMETRY_SVC_H

/////////////////////////////////////////
// place holder
/////////////////////////////////////////

#include "Geometry/IActsTrackingGeometrySvc.h"
#include "Geometry/IActsDD4hepGeometrySvc.h"

#include "GaudiKernel/Service.h"

class ActsDD4hepCustomGeometrySvc
  : public extends<Service, IActsTrackingGeometrySvc> {

public:
  using extends::extends;

  StatusCode initialize() override;
  StatusCode finalize() override;

  const Acts::TrackingGeometry* trackingGeometry() const override;
  Acts::GeometryContext geometryContext() const override;

  std::string buildMode() const override { return "CustomDD4hep"; }

private:
  ServiceHandle<IActsDD4hepGeometrySvc> m_dd4hepSvc{
      this, "DD4hepSvc", "ActsDD4hepGeometrySvc",
      "DD4hep loader service providing dd4hep::Detector"};
};

#endif

