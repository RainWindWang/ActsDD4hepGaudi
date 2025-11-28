#ifndef DUMP_DD4HEP_GEOMETRY_ALG_H
#define DUMP_DD4HEP_GEOMETRY_ALG_H

#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/ServiceHandle.h"
#include "Geometry/IActsDD4hepGeometrySvc.h"

class DumpDD4hepGeometryAlg : public Gaudi::Algorithm {
public:
  DumpDD4hepGeometryAlg(const std::string& name, ISvcLocator* svcLoc);

  StatusCode initialize() override;
  StatusCode execute(const EventContext& ctx) const override;
  StatusCode finalize() override;

private:
  ServiceHandle<IActsDD4hepGeometrySvc> m_geoSvc{
      this, "DD4hepGeometrySvc", "ActsDD4hepGeometrySvc",
      "Service that provides DD4hep::Detector"};

  mutable bool m_printed{false};
};

#endif

