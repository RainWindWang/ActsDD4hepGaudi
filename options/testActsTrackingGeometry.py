from Gaudi.Configuration import *
from Configurables import ApplicationMgr

from Configurables import ActsDD4hepGeometrySvc
from Configurables import ActsPluginGeometrySvc
from Configurables import DumpActsTrackingGeometryAlg

# ----------------------------------------------------------------------
# Build DD4hep Geometry compact XML
# ----------------------------------------------------------------------
dd4hep_svc = ActsDD4hepGeometrySvc(
    "ActsDD4hepGeometrySvc",
    DD4hepXMLFile = "/data/dust/user/wangyufe/luxegeo/compact/LUXETrackerAsEndcap.xml"
)

# ----------------------------------------------------------------------
# Build ACTS TrackingGeometry from DD4hep detector
# ----------------------------------------------------------------------
acts_geo_svc = ActsPluginGeometrySvc(
    "ActsPluginGeometrySvc",
    DD4hepSvcName = "ActsDD4hepGeometrySvc",  # must match above
    WriteObj = False,
    ObjFileName = "acts_geometry.obj"
)

# ----------------------------------------------------------------------
# Check ACTS geometry
# ----------------------------------------------------------------------
dump_alg = DumpActsTrackingGeometryAlg(
    "DumpActsTrackingGeometryAlg",
    ActsTrackingGeometrySvc = "ActsPluginGeometrySvc"
)

# ----------------------------------------------------------------------
# ApplicationMgr
# ----------------------------------------------------------------------
ApplicationMgr(
    EvtSel = "NONE",
    EvtMax = 1,
    ExtSvc = [dd4hep_svc, acts_geo_svc],
    TopAlg = [dump_alg]
)

