import FWCore.ParameterSet.Config as cms
from SimCalorimetry.HGCalSimProducers.hgcalDigitizer_cfi import *
from RecoLocalCalo.HGCalRecProducers.HGCalUncalibRecHit_cfi import *

dEdX_weights = cms.vdouble(0.0,   # there is no layer zero
                           8.366557,   # Mev
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           10.425456,  
                           31.497849,  
                           51.205434,  
                           52.030486,  
                           52.030486,  
                           52.030486,  
                           52.030486,  
                           52.030486,  
                           52.030486,  
                           52.030486,  
                           52.030486,  
                           52.030486,  
                           52.030486,  
                           71.265149,  
                           90.499812,  
                           90.894274,  
                           90.537470,  
                           89.786205,  
                           89.786205,  
                           89.786205,  
                           89.786205,  
                           89.786205,  
                           89.786205,  
                           89.786205,  
                           89.786205,  
                           89.786205)

# HGCAL rechit producer
HGCalRecHit = cms.EDProducer(
    "HGCalRecHitProducer",
    HGCEErechitCollection = cms.string('HGCEERecHits'),
    HGCEEuncalibRecHitCollection = cms.InputTag('HGCalUncalibRecHit:HGCEEUncalibRecHits'),
    HGCHEFrechitCollection = cms.string('HGCHEFRecHits'),
    HGCHEFuncalibRecHitCollection = cms.InputTag('HGCalUncalibRecHit:HGCHEFUncalibRecHits'),
    HGCHEBrechitCollection = cms.string('HGCHEBRecHits'),
    HGCHEBuncalibRecHitCollection = cms.InputTag('HGCalUncalibRecHit:HGCHEBUncalibRecHits'),

    # digi constants
    HGCEE_keV2DIGI  = hgceeDigitizer.digiCfg.keV2fC,
    HGCEE_isSiFE    = HGCalUncalibRecHit.HGCEEConfig.isSiFE,
    HGCEE_fCPerMIP  = HGCalUncalibRecHit.HGCEEConfig.fCPerMIP,
    HGCHEF_keV2DIGI = hgchefrontDigitizer.digiCfg.keV2fC,
    HGCHEF_isSiFE   = HGCalUncalibRecHit.HGCHEFConfig.isSiFE,
    HGCHEF_fCPerMIP = HGCalUncalibRecHit.HGCHEFConfig.fCPerMIP,
    HGCHEB_keV2DIGI = hgchebackDigitizer.digiCfg.keV2MIP,
    HGCHEB_isSiFE   = HGCalUncalibRecHit.HGCHEBConfig.isSiFE,
    # don't produce rechit if detid is a ghost one
    rangeMask = cms.uint32(4294442496),
    rangeMatch = cms.uint32(1161838592),


    # EM Scale calibrations
    layerWeights = dEdX_weights,

    thicknessCorrection = cms.vdouble(0.759,0.760,0.773), # 120, 200, 300 um
    HGCEE_noise_fC = hgceeDigitizer.digiCfg.noise_fC,
    HGCEE_cce = hgceeDigitizer.digiCfg.chargeCollectionEfficiencies,
    HGCHEF_noise_fC = hgchefrontDigitizer.digiCfg.noise_fC,
    HGCHEF_cce = hgchefrontDigitizer.digiCfg.chargeCollectionEfficiencies,
    HGCHEB_noise_MIP = hgchebackDigitizer.digiCfg.noise_MIP,
    # algo
    algo = cms.string("HGCalRecHitWorkerSimple")

    )


