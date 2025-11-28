#ifndef DUMPACTSTRACKINGGEOMETRYALG_H
#define DUMPACTSTRACKINGGEOMETRYALG_H

#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/ServiceHandle.h"
#include "GaudiKernel/EventContext.h"
#include "GaudiKernel/StatusCode.h"

#include "Acts/Geometry/TrackingGeometry.hpp"
#include "Geometry/IActsTrackingGeometrySvc.h"   // <-- 你提供 tracking geometry 的接口

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
      this, "ActsTrackingGeometrySvc", "ActsTrackingGeometrySvc",
      "Service providing Acts::TrackingGeometry" };
};

#endif

