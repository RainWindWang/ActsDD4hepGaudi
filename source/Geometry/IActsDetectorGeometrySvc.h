#ifndef IACTSDETECTORGEOMETRYSVC_H
#define IACTSDETECTORGEOMETRYSVC_H

#include "GaudiKernel/IInterface.h"

#include "Acts/Detector/Detector.hpp"
#include "Acts/Geometry/GeometryContext.hpp"

// DD4hep-backed DetectorElement store
#include "ActsPlugins/DD4hep/DD4hepDetectorElement.hpp"

/**
 * @class IActsDetectorGeometrySvc
 *
 * @brief Gaudi interface for ACTS Gen-3 Detector geometry.
 *
 * This interface is the standard entry point for all algorithms
 * (digitization, seeding, track reconstruction, simulation) that
 * need access to ACTS 3rd-generation geometry.
 *
 * It intentionally abstracts away *how* the geometry is constructed.
 * Implementations may come from:
 *   - Official DD4hep -> ACTS converter (DD4hepDetectorStructure)
 *   - Custom geometry construction
 *   - Mock geometry for testing
 *
 * Algorithms should only depend on this interface, never on
 * ActsPluginGeometrySvc directly.
 */
class IActsDetectorGeometrySvc : virtual public IInterface {
public:
  /// Gaudi interface ID
  DeclareInterfaceID(IActsDetectorGeometrySvc, 1, 0);

  /// Return the ACTS Gen-3 detector (top-level volume graph)
  virtual const Acts::Experimental::Detector*
      detector() const = 0;

  /// Return DD4hep-backed detector-element store
  /// needed to retrieve bound surfaces for sensitive elements
  virtual const ActsPlugins::DD4hepDetectorElement::Store&
      dd4hepStore() const = 0;

  /// Return the geometry context (thread-safe, event-independent)
  virtual const Acts::GeometryContext&
      geoContext() const = 0;

  virtual ~IActsDetectorGeometrySvc() = default;
};

#endif

