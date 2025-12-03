from Gaudi.Configuration import *
from Configurables import ApplicationMgr
from Configurables import ActsDD4hepGeometrySvc, DumpDD4hepGeometryAlg

# ------------------------------------------------------------
# Geometry service
# ------------------------------------------------------------
geo_svc = ActsDD4hepGeometrySvc("ActsDD4hepGeometrySvc")
#geo_svc.DD4hepXMLFile = "/data/dust/user/wangyufe/luxegeo/compact/LUXETrackerAsEndcap.xml"
#geo_svc.DD4hepXMLFile = "/data/dust/user/wangyufe/luxegeo/compact/LUXETracker.xml"
geo_svc.DD4hepXMLFile = "/data/dust/user/wangyufe/luxegeo/compact/LUXETracker_BluePrint.xml"
#geo_svc.BuildACTSGeometry = False

# ------------------------------------------------------------
# Algorithm
# ------------------------------------------------------------
dump = DumpDD4hepGeometryAlg("DumpDD4hepGeometryAlg")

# ------------------------------------------------------------
# Application manager
# ------------------------------------------------------------
app = ApplicationMgr()
app.TopAlg = [dump]
app.ExtSvc = [geo_svc]
app.EvtSel = "NONE"
app.EvtMax = 1

# load local library
app.Dlls += ["ActsDD4hepGeometry"]

# logging level
app.EvtSel = "NONE"
app.EvtMax = 1

app.OutputLevel = 3  # INFO

#from GaudiKernel import MSG
#app.OutputLevel = MSG.INFO
