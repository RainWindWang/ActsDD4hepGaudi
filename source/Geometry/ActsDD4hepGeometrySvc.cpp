#include "Geometry/IActsDD4hepGeometrySvc.h"

#include "GaudiKernel/Service.h"
#include "GaudiKernel/MsgStream.h"
#include <Gaudi/Property.h>
#include "GaudiKernel/StatusCode.h"
#include "GaudiKernel/ISvcLocator.h"

#include "DD4hep/Detector.h"

class ActsDD4hepGeometrySvc
  : public extends<Service, IActsDD4hepGeometrySvc> {

public:
  using extends::extends;

  StatusCode initialize() override {
    StatusCode sc = Service::initialize();
    if (!sc.isSuccess()) return sc;

    info() << "Initializing ActsDD4hepGeometrySvc" << endmsg;
    info() << "DD4hep compact file: " << m_dd4hepXmlFile << endmsg;

    if (m_dd4hepXmlFile.value().empty()) {
      error() << "Property DD4hepXMLFile is empty! Please set it in job options."
              << endmsg;
      return StatusCode::FAILURE;
    }

    try {
      dd4hep::Detector& det = dd4hep::Detector::getInstance();
      det.fromCompact(m_dd4hepXmlFile.value());
      m_dd4hepDetector = &det;
    } catch (const std::exception& e) {
      error() << "Exception while loading DD4hep compact geometry: "
              << e.what() << endmsg;
      return StatusCode::FAILURE;
    }

    if (!m_dd4hepDetector) {
      error() << "DD4hep detector pointer is null after fromCompact()."
              << endmsg;
      return StatusCode::FAILURE;
    }

    info() << "Successfully loaded DD4hep geometry from '"
           << m_dd4hepXmlFile.value() << "'" << endmsg;
    return StatusCode::SUCCESS;
  }

  StatusCode finalize() override {
    info() << "Finalizing ActsDD4hepGeometrySvc" << endmsg;
    m_dd4hepDetector = nullptr;
    return Service::finalize();
  }

  dd4hep::Detector* detector() override { return m_dd4hepDetector; }

  const dd4hep::Detector* detector() const override {
    return m_dd4hepDetector;
  }

private:
  /// compact XML file path
  Gaudi::Property<std::string> m_dd4hepXmlFile{
      this,
      "DD4hepXMLFile",
      "",
      "Path to the DD4hep compact XML file"};

  dd4hep::Detector* m_dd4hepDetector{nullptr};
};

// Declare as Gaudi component
DECLARE_COMPONENT(ActsDD4hepGeometrySvc)
