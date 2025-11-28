#ifndef ACTS_DD4HEP_GEOMETRY_IActsTrackingGeometrySvc_H
#define ACTS_DD4HEP_GEOMETRY_IActsTrackingGeometrySvc_H

#include "GaudiKernel/IInterface.h"
#include <string>

namespace Acts {
  class TrackingGeometry;
  class GeometryContext;
}

class IActsTrackingGeometrySvc : virtual public IInterface {
public:
  DeclareInterfaceID(IActsTrackingGeometrySvc, 1, 0);

  virtual const Acts::TrackingGeometry* trackingGeometry() const = 0;

  // ACTS GeometryContext
  virtual Acts::GeometryContext geometryContext() const = 0;

  // which geometry build method
  virtual std::string buildMode() const = 0;

  virtual ~IActsTrackingGeometrySvc() = default;
};

#endif

