#include "ActsPluginGeometrySvc.h"

#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/MsgStream.h"

#include "ActsPlugins/DD4hep/ConvertDD4hepDetector.hpp"
#include "ActsPlugins/DD4hep/DD4hepLayerBuilder.hpp"

#include "Acts/Geometry/TrackingGeometry.hpp"
#include "Acts/Geometry/GeometryContext.hpp"
#include "Acts/Utilities/BinningType.hpp"
#include "Acts/Utilities/Logger.hpp"
#include "Acts/Definitions/Units.hpp"

#include "Acts/Visualization/ObjVisualization3D.hpp"
#include "Acts/Visualization/GeometryView3D.hpp"

DECLARE_COMPONENT(ActsPluginGeometrySvc)

StatusCode ActsPluginGeometrySvc::initialize() {
  StatusCode sc = Service::initialize();
  if (!sc.isSuccess()) return sc;

  info() << "Initializing ActsPluginGeometrySvc (no blueprint)"
         << endmsg;

  // import DD4hep geo
  m_dd4hepSvc = Gaudi::svcLocator()->service<IActsDD4hepGeometrySvc>(m_dd4hepSvcName);
  if (!m_dd4hepSvc) {
    error() << "Failed to retrieve DD4hep geometry service '"
            << m_dd4hepSvcName << "'" << endmsg;
    return StatusCode::FAILURE;
  }

  dd4hep::Detector* det = m_dd4hepSvc->detector();
  if (!det) {
    error() << "DD4hep detector pointer is null!" << endmsg;
    return StatusCode::FAILURE;
  }

  m_geoCtx = Acts::GeometryContext{};
  //m_geoCtx = m_dd4hepSvc->geoContext();

  info() << "Constructing ACTS TrackingGeometry using convertDD4hepDetector..."
         << endmsg;

  // -------------
  Acts::BinningType bPhi = Acts::BinningType::equidistant;
  Acts::BinningType bR   = Acts::BinningType::equidistant;
  Acts::BinningType bZ   = Acts::BinningType::equidistant;

  // -------------
  const double layerEnvelopeR        = 0.1 * Acts::UnitConstants::mm;
  const double layerEnvelopeZ        = 0.1 * Acts::UnitConstants::mm;
  const double defaultLayerThickness = 0.01 * Acts::UnitConstants::mm;

  // -------------
  auto sortSubDetectors =
      [](std::vector<dd4hep::DetElement>& detectors) {
        std::sort(detectors.begin(), detectors.end(),
                  [](const dd4hep::DetElement& a,
                     const dd4hep::DetElement& b) {
                    return a.name() < b.name();
                  });
      };

  // MaterialDecorator / GeometryIdentifierHook placeholder
  std::shared_ptr<const Acts::IMaterialDecorator> matDecorator = nullptr;
  std::shared_ptr<const Acts::GeometryIdentifierHook> geoIdHook = nullptr;

  // DetectorElementFactory placeholder
  ActsPlugins::DD4hepLayerBuilder::ElementFactory elementFactory;

  // Logger
  auto logger = Acts::getDefaultLogger("DD4hepConversion",
                                       Acts::Logging::INFO);

  // tracking geo
  std::unique_ptr<const Acts::TrackingGeometry> tgPtrUnique =
      ActsPlugins::convertDD4hepDetector(
          det->world(),                  
          *logger,                       
          bPhi, bR, bZ,                  
          layerEnvelopeR, layerEnvelopeZ,
          defaultLayerThickness,
          sortSubDetectors,              
          m_geoCtx,                      
          matDecorator,                  
          geoIdHook,                     
          elementFactory                 
      );

  if (!tgPtrUnique) {
    error() << "Failed to construct ACTS TrackingGeometry!" << endmsg;
    return StatusCode::FAILURE;
  }

  m_trackingGeometry =
      std::shared_ptr<const Acts::TrackingGeometry>(
          std::move(tgPtrUnique));

  info() << "TrackingGeometry successfully built from DD4hep." << endmsg;

  // dummy visualization
  if (m_writeObj) {
    info() << "Writing OBJ file from TrackingGeometry: "
           << m_objFileName << endmsg;

    Acts::ObjVisualization3D writer;
    m_trackingGeometry->visitSurfaces(
        [&](const Acts::Surface* s) {
          Acts::GeometryView3D::drawSurface(writer, *s, m_geoCtx);
        });

    writer.write(m_objFileName.value());
    info() << "OBJ written." << endmsg;
  }

  return StatusCode::SUCCESS;
}

StatusCode ActsPluginGeometrySvc::finalize() {
  info() << "Finalizing ActsPluginGeometrySvc" << endmsg;
  m_trackingGeometry.reset();
  return Service::finalize();
}

// -----------------------------------------------
const Acts::TrackingGeometry*
ActsPluginGeometrySvc::trackingGeometry() const {
  return m_trackingGeometry.get();
}

const Acts::GeometryContext&
ActsPluginGeometrySvc::geoContext() const {
  return m_geoCtx;
}

std::string ActsPluginGeometrySvc::buildMode() const {
  // Any descriptive string is fine; this is mostly for logging/inspection
  return "DD4hep->Acts TrackingGeometry via ActsPlugins::convertDD4hepDetector";
}

// declare gaudi component
DECLARE_COMPONENT(ActsPluginGeometrySvc)
