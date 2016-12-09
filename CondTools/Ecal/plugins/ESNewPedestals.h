#ifndef ESNEWPEDESTALS_H
#define ESNEWPEDESTALS_H

/**\class EcalPedestalHistory

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// $Id: EcalPedestalHistory.h,v 0.0 2016/04/28 $
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"

#include "Geometry/EcalMapping/interface/EcalElectronicsMapping.h"
#include "Geometry/EcalMapping/interface/EcalMappingRcd.h"

#include "CaloOnlineTools/EcalTools/interface/EcalFedMap.h"

#include "OnlineDB/EcalCondDB/interface/all_monitoring_types.h"
#include "OnlineDB/Oracle/interface/Oracle.h"
#include "OnlineDB/ESCondDB/interface/ESCondDBInterface.h"

#include "DataFormats/EcalDetId/interface/EBDetId.h"

#include <string>
#include "TH1.h"
#include "TGraph.h"
#include "TH2.h"
#include<fstream>
#include<map>

using namespace edm;

class ESNewPedestals : public edm::EDAnalyzer {
 public:
  explicit ESNewPedestals( const edm::ParameterSet& );
  ~ESNewPedestals();
  virtual void analyze( const edm::Event&, const edm::EventSetup& );
  virtual void beginRun(edm::Run const &, edm::EventSetup const &);
  virtual void beginJob();
  virtual void endJob();
  ESCondDBInterface* econn;

  enum { kChannels = 75848, kEBChannels = 61200, kEEChannels = 14648};
  enum { kGains = 3, kFirstGainId = 1};
 private:
  int runnumber_;
  int thegain_;
  bool readfeconfinfo, writefeconfinfo, readfeconfdat;
  std::string zerosup, cmc, highlowg, Ped_sub, Magnet;
  unsigned int cnt_evt_;
  std::string ECALType_; // EB or EE
  std::string runType_; // Pedes or Other
  unsigned int startevent_; 
  FileInPath lookuptable_;
  Int_t FED[2][2][40][40], KCHIP[2][2][40][40], PACE[2][2][40][40], FIBER[2][2][40][40], OPTORX[2][2][40][40];
  Int_t PED[2][2][40][40][32], PEDRMS[2][2][40][40][32], MASK[2][2][40][40][32], CMMASK[2][2][40][40][32], ZS[2][2][40][40][32];
  Int_t CMRange[2][2][40][40][32];
  std::vector<int> maskedChannels_;
  std::vector<int> maskedEEChannels_;
  unsigned int m_firstRun ;
  unsigned int m_lastRun ;
  std::string m_location;
  std::string m_gentag;
  std::string m_sid;
  std::string m_user;
  std::string m_pass;
  std::string m_locationsource;
  std::string m_name;
};
#endif
