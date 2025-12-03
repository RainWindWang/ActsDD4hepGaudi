#ifndef DUMPACTSTRACKINGGEOMETRYALG_H
#define DUMPACTSTRACKINGGEOMETRYALG_H

#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/EventContext.h"
#include "GaudiKernel/ServiceHandle.h"
#include "GaudiKernel/StatusCode.h"

#include "GaudiKernel/ISvcLocator.h"
#include <Gaudi/Property.h>

#include "Acts/Geometry/TrackingGeometry.hpp"
#include "Acts/Geometry/TrackingVolume.hpp"
#include "Geometry/IActsTrackingGeometrySvc.h"

class DumpActsTrackingGeometryAlg : public Gaudi::Algorithm {
public:
  DumpActsTrackingGeometryAlg(const std::string& name, ISvcLocator* svcLoc);

  StatusCode initialize() override;
  StatusCode execute(const EventContext& ctx) const override;
  StatusCode finalize() override;

private:
  void dumpVolume(const Acts::TrackingVolume& v,
                  const std::string& indent) const;

  ServiceHandle<IActsTrackingGeometrySvc> m_tgSvc{
      this, "ActsTrackingGeometrySvc", "ActsPluginGeometrySvc",
      "Service providing Acts::TrackingGeometry"};

  Gaudi::Property<bool> m_writeObj{
      this, "WriteObj", true,
      "If true, write a Wavefront OBJ file with all surfaces"};

  /// OBJ
  Gaudi::Property<std::string> m_objFileName{
      this, "ObjFileName", "acts_dd4hep_geometry.obj",
      "Output OBJ file name for geometry visualization"};
};

#endif
