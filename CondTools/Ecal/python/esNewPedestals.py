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

  runnumber = cms.untracked.int32(234594),
  Gain = cms.untracked.int32(1),
  ECALType = cms.string("EE"),
  runType = cms.string("Pedes"),
  startevent = cms.untracked.uint32(1),
  xtalnumber = cms.untracked.int32(0),

  LookupTable = cms.untracked.FileInPath("EventFilter/ESDigiToRaw/data/ES_lookup_table.dat"),

#  Source = cms.PSet(
    GenTag = cms.string('LOCAL'),
#    RunTag = cms.string('TEST_PULSE'),
#    firstRun = cms.string('240000'),
    firstRun = cms.string('157000'),
    lastRun = cms.string('100000000'),
    LocationSource = cms.string('P5'),
    OnlineDBUser = cms.string('cms_es_cond'),
    OnlineDBPassword = cms.string('********'),
    debug = cms.bool(True),
    Location = cms.string('P5_Co'),
    OnlineDBSID = cms.string('cms_orcon_adg')
#  )
)

process.p = cms.Path(process.esnewpedestals)

