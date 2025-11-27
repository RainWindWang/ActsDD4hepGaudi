###############################################
# key4hep
###############################################
source /cvmfs/sw.hsf.org/key4hep/setup.sh

###############################################
# local ACTS
###############################################
export CMAKE_PREFIX_PATH=/data/dust/user/wangyufe/ACTS_v44/install:$CMAKE_PREFIX_PATH

###############################################
# runtime: ACTS lib
###############################################
export LD_LIBRARY_PATH=/data/dust/user/wangyufe/ACTS_v44/install/lib64:$LD_LIBRARY_PATH

###############################################
# runtime: Gaudi Plugin & components
###############################################
export LD_LIBRARY_PATH=/data/dust/user/wangyufe/ActsDD4hepGaudi/build/install/lib:$LD_LIBRARY_PATH
export GAUDI_PLUGIN_PATH=/data/dust/user/wangyufe/ActsDD4hepGaudi/build/install/lib:$GAUDI_PLUGIN_PATH

###############################################
# python: Gaudi auto-generated Conf modules
###############################################
export PYTHONPATH=/data/dust/user/wangyufe/ActsDD4hepGaudi/build/install/python:$PYTHONPATH

###############################################
# python option path
###############################################
export PYTHONPATH=/data/dust/user/wangyufe/ActsDD4hepGaudi/options:$PYTHONPATH

###############################################
# python import ACTS
###############################################
export PYTHONPATH=/data/dust/user/wangyufe/ACTS_v44/install/python:$PYTHONPATH
