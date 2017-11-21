import FWCore.ParameterSet.Config as cms

process = cms.Process("Noise")

process.load("FWCore.MessageService.test.Services_cff")

process.MessageLogger = cms.Service("MessageLogger",
  destinations = cms.untracked.vstring('messages.txt'),
)

#######################################################################################
process.source = cms.Source("EmptySource",
  firstRun = cms.untracked.uint32(1)
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)
#######################################################################################


# Conditions (Global Tag is used here):
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = 'GR_R_74_V15B'
#process.prefer("GlobalTag")

process.esnewpedestals = cms.EDAnalyzer("ESNewPedestals",

  runnumber = cms.untracked.int32(133734), #133734 #289591
  # To fill the following number first decide what you want to do: 
  # 1. Read ESFECONFINFO: Find the rec_id from the database. 
  # 2. Write ESFECONFINFO: When you write the the ES_FE_CONF_INFO table, 
  #    this table is not needed since in that case the code will increment 
  #    the rec_id from the latest rec_id he will find in the database. 
  # 3. Write ESFECONFDAT: Put the rec_id of the ESFECONFINFO you just created. 
  #    ReadESFECONFINFO below should be to true.
  # 4. Read ESFECONFDAT: 

  ESFECONFINFO_recid = cms.untracked.int32(37),
  Gain = cms.untracked.int32(1),
  ReadESFECONFINFO = cms.bool(True),
  #Be Careful: When to true it will increment the rec_id and then will create a new ES_FE_CONF_INFO table!!!
  WriteESFECONFINFO = cms.bool(False),
  ReadESFECONFDAT = cms.bool(True),
  WriteESFECONFDAT = cms.bool(False),
  ZS   = cms.string("ON"), # Options are ON or OFF
  cmc   = cms.string("ON"), # Options are ON or OFF
  HighLowG   = cms.string("LG"), # Options are HG or LG
  Ped_sub    = cms.string("ON"), # Options are ON or OFF
  Magnet     = cms.string("BON"), # Options are BON or BOFF
  ECALType = cms.string("EE"),
  runType = cms.string("Pedes"),
  startevent = cms.untracked.uint32(1),
  xtalnumber = cms.untracked.int32(0),

  LookupTable = cms.untracked.FileInPath("EventFilter/ESDigiToRaw/data/ES_lookup_table.dat"),

#  Source = cms.PSet(
    GenTag = cms.string('LOCAL'), #was LOCAL in a previous time (run 133734). This is GEN_TAG of RUN_TAG. PEDESTAL (this is for 289591)
    ESMonRunIOVTag = cms.string('CMSSW'), #CMSSW #CMSSW-offline-private
#    RunTag = cms.string('TEST_PULSE'),
#    firstRun = cms.string('240000'),
    firstRun = cms.string('127000'),
    lastRun = cms.string('100000000'),
    LocationSource = cms.string('P5'),
    OnlineDBUser = cms.string('cms_es_conf'), #
#    OnlineDBPassword = cms.string('*******'),
#    OnlineDBUser = cms.string(''),
    OnlineDBPassword = cms.string('********'), #
    debug = cms.bool(True),
    Location = cms.string('P5_Co'), #P5PRO
    OnlineDBSID = cms.string('int9r') #cms_orcon_adg
#  )
)

process.p = cms.Path(process.esnewpedestals)

