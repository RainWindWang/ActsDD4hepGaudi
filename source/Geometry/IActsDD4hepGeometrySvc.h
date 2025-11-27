#ifndef ACTS_DD4HEP_GEOMETRY_IActsDD4hepGeometrySvc_H
#define ACTS_DD4HEP_GEOMETRY_IActsDD4hepGeometrySvc_H

#include "GaudiKernel/IInterface.h"

namespace dd4hep {
  class Detector;
}

class IActsDD4hepGeometrySvc : virtual public IInterface {
public:
  /// Interface ID
  DeclareInterfaceID(IActsDD4hepGeometrySvc, 1, 0);

  /// Non-const access
  virtual dd4hep::Detector* detector() = 0;

  /// Const access
  virtual const dd4hep::Detector* detector() const = 0;

  virtual ~IActsDD4hepGeometrySvc() = default;
};

#endif
