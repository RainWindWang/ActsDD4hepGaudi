#############################################
# Minimal job options for ACTS Gen-2 Geometry
# via DD4hep plugin conversion
#############################################

from Gaudi.Configuration import *

# ---------------------------------------------------------
# 1) Application Manager
# ---------------------------------------------------------
app = ApplicationMgr()
app.EvtSel = "NONE"
app.EvtMax = 1        # Only need 1 event to dump geometry
app.OutputLevel = INFO

# ---------------------------------------------------------
# 2) Load DD4hep Geometry Service (your existing svc)
# ---------------------------------------------------------
from Configurables import ActsDD4hepGeometrySvc
dd4hepSvc = ActsDD4hepGeometrySvc(
    "ActsDD4hepGeometrySvc",
    DD4hepXMLFile = "/data/dust/user/wangyufe/luxegeo/compact/LUXETracker_BluePrint.xml",
    OutputLevel = INFO
)

# ---------------------------------------------------------
# 3) Load ACTS Plugin Geometry Service (Gen-2 conversion)
# ---------------------------------------------------------
from Configurables import ActsPluginGeometrySvc
actsGeoSvc = ActsPluginGeometrySvc(
    "ActsPluginGeometrySvc",
    DD4hepSvc = "ActsDD4hepGeometrySvc",
    WriteObj = True,
    ObjFile = "actsGen2Geometry.obj",
    OutputLevel = INFO
)

app.ExtSvc += [dd4hepSvc, actsGeoSvc]

# ---------------------------------------------------------
# 4) Load geometry dumping algorithm
# ---------------------------------------------------------
from Configurables import DumpActsTrackingGeometryAlg
dumpAlg = DumpActsTrackingGeometryAlg(
    "DumpActsTrackingGeometryAlg",
    ActsTrackingGeometrySvc = "ActsPluginGeometrySvc",
    OutputLevel = INFO
)

app.TopAlg = [dumpAlg]
