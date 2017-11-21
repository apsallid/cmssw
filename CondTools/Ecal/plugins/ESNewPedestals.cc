/**\class EcalPedestalHistory

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// $Id: EcalEcalPedestalHistory.cc,v 0.0 2016/05/02 jean fay Exp $
//
//

#include "CondTools/Ecal/plugins/ESNewPedestals.h" 
#include "CondFormats/EcalObjects/interface/EcalChannelStatus.h"
#include "CondFormats/DataRecord/interface/EcalChannelStatusRcd.h"
#include "OnlineDB/ESCondDB/interface/ESMonPedestalsDat.h"
#include "OnlineDB/ESCondDB/interface/ODESFEPedestalOffsetsDat.h"

//#include<fstream>

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TProfile.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>

using namespace edm;
using namespace cms;
using namespace std;
  
//
// constants, enums and typedefs
//
//const Int_t kSample=10;
//
// static data member definitions
//
//int gainValues[3] = {12, 6, 1};

//
// constructors and destructor
//


//====================================================================
ESNewPedestals::ESNewPedestals( const edm::ParameterSet& iConfig ) {
//====================================================================
   //now do what ever initialization is needed   
  //  EBDigiCollection_          = iConfig.getParameter<edm::InputTag>("EBDigiCollection");
  runnumber_                 = iConfig.getUntrackedParameter<int>("runnumber",-1);
  therecid_                 = iConfig.getUntrackedParameter<int>("ESFECONFINFO_recid",-1);
  thegain_                   = iConfig.getUntrackedParameter<int>("Gain",-1);
  zerosup                    = iConfig.getParameter<std::string>("ZS");
  readfeconfinfo             = iConfig.getParameter<bool>("ReadESFECONFINFO"),
  writefeconfinfo            = iConfig.getParameter<bool>("WriteESFECONFINFO"),
  readfeconfdat              = iConfig.getParameter<bool>("ReadESFECONFDAT"),
  writefeconfdat              = iConfig.getParameter<bool>("WriteESFECONFDAT"),
  cmc                        = iConfig.getParameter<std::string>("cmc");
  highlowg                   = iConfig.getParameter<std::string>("HighLowG");
  Ped_sub                    = iConfig.getParameter<std::string>("Ped_sub");
  Magnet                     = iConfig.getParameter<std::string>("Magnet");
  ECALType_                  = iConfig.getParameter<std::string>("ECALType");
  runType_                   = iConfig.getParameter<std::string>("runType");
  startevent_                = iConfig.getUntrackedParameter<unsigned int>("startevent", 1);

  lookuptable_               = iConfig.getUntrackedParameter<FileInPath>("LookupTable");
  
  // read in look-up table
  for (int i=0; i<2; ++i){ 
    for (int j=0; j<2; ++j){ 
      for (int k=0; k<40; ++k){ 
        for (int m=0; m<40; ++m) {
          FED[i][j][k][m] = 0;
	  for (int n=0; n<32; ++n) {
	    MASK[i][j][k][m][n] = 0;
	    CMMASK[i][j][k][m][n] = 0;
	    ZS[i][j][k][m][n] = 0;
	    CMRange[i][j][k][m][n] = 0;
	  }
	}
      }
    }
  }

  int nLines, iz, ip, ix, iy, fed, kchip, pace, bundle, fiber, optorx;
  std::ifstream file;
  file.open(lookuptable_.fullPath().c_str());

  if( file.is_open() ) {
    
    file >> nLines;
    for (int i=0; i<nLines; ++i) {
      file >> iz >> ip >> ix >> iy >> fed >> kchip >> pace >> bundle >> fiber >> optorx ;

      int zside = (iz==1) ? 0: 1; 

      FED[zside][ip-1][ix-1][iy-1] = fed;
      KCHIP[zside][ip-1][ix-1][iy-1] = kchip;
      PACE[zside][ip-1][ix-1][iy-1] = pace;
      FIBER[zside][ip-1][ix-1][iy-1] = fiber;
      OPTORX[zside][ip-1][ix-1][iy-1] = optorx;
    }
  } else {
    cout<<"ESNewPedestals::ESNewPedestals : Look up table file can not be found in "<<lookuptable_.fullPath().c_str()<<endl;
  }

  std::cout << "EcalPedestals Source handler constructor\n" << std::endl;
  m_firstRun = static_cast<unsigned int>(atoi(iConfig.getParameter<std::string>("firstRun").c_str()));
  m_lastRun = static_cast<unsigned int>(atoi(iConfig.getParameter<std::string>("lastRun").c_str()));
  m_sid = iConfig.getParameter<std::string>("OnlineDBSID");
  m_user = iConfig.getParameter<std::string>("OnlineDBUser");
  m_pass = iConfig.getParameter<std::string>("OnlineDBPassword");
  m_locationsource = iConfig.getParameter<std::string>("LocationSource");
  m_location = iConfig.getParameter<std::string>("Location");
  m_gentag = iConfig.getParameter<std::string>("GenTag");
  m_esmonruniovtag= iConfig.getParameter<std::string>("ESMonRunIOVTag");
  std::cout << m_sid<<"/"<<m_user<<"/"<<m_pass<<"/"<<m_location<<"/"<<m_gentag   << "/"<<m_esmonruniovtag <<std::endl;

  vector<int> listDefaults;
  listDefaults.push_back(-1);  

  cnt_evt_ = 0;
  cout << "Exiting constructor" << endl;
}//constructor


//========================================================================
ESNewPedestals::~ESNewPedestals() {
//========================================================================
  cout << "ANALYSIS FINISHED" << endl;
}//destructor

//========================================================================
void ESNewPedestals::beginRun(edm::Run const &, edm::EventSetup const & c) {
///========================================================================

  cout << "Entering beginRun" << endl;
  /*     do not use any tag...
  edm::ESHandle<EcalChannelStatus> pChannelStatus;
  c.get<EcalChannelStatusRcd>().get(pChannelStatus);
  const EcalChannelStatus* chStatus = pChannelStatus.product();  
  EcalChannelStatusMap::const_iterator chit;
  for (int iChannel = 0; iChannel < kEBChannels; iChannel++) {
    EBDetId id = EBDetId::unhashIndex(iChannel);
    chit = chStatus->getMap().find(id.rawId());
    if( chit != chStatus->getMap().end() ) {
      EcalChannelStatusCode ch_code = (*chit);
      uint16_t statusCode = ch_code.getStatusCode() & 31;
      if(statusCode == 1 || (statusCode > 7 && statusCode < 12))
	maskedChannels_.push_back(iChannel);
    }
  }
  for (int iChannel = 0; iChannel < kEEChannels; iChannel++) {
    EEDetId id = EEDetId::unhashIndex(iChannel);
    chit = chStatus->getMap().find(id.rawId());
    if( chit != chStatus->getMap().end() ) {
      EcalChannelStatusCode ch_code = (*chit);
      uint16_t statusCode = ch_code.getStatusCode() & 31;
      if(statusCode == 1 || (statusCode > 7 && statusCode < 12))
	maskedEEChannels_.push_back(iChannel);
    }
  }
  */
  /*TH1F** hMean = new TH1F*[15];
  TH1F** hRMS = new TH1F*[15];
  TFile f("PedHist.root","RECREATE");

  typedef struct {
    int iChannel;
    int ix;
    int iy;
    int iz;
  } Chan_t;
  Chan_t Chan;
  Chan.iChannel = -1;
  Chan.ix = -1; 
  Chan.iy = -1;
  Chan.iz = -1;

  TTree* tPedChan = new TTree("PedChan", "Channels"); // Output tree for channels
  tPedChan->Branch("Channels", &Chan.iChannel, "iChannel/I");
  tPedChan->Branch("x", &Chan.ix, "ix/I");
  tPedChan->Branch("y", &Chan.iy, "iy/I");
  tPedChan->Branch("z", &Chan.iz, "iz/I");
  for (int iChannel = 0; iChannel < kEBChannels; iChannel++) {
    Chan.iChannel = iChannel;
    EBDetId myEBDetId = EBDetId::unhashIndex(iChannel);
    Chan.ix = myEBDetId.ieta();  // -85:-1,1:85
    Chan.iy = myEBDetId.iphi();  // 1:360
    Chan.iz = 0;
    if(iChannel%10000 == 0)  cout << " EB channel " << iChannel << " eta " << Chan.ix << " phi " << Chan.iy << endl;
    tPedChan->Fill();
  }
  for (int iChannel = 0; iChannel < kEEChannels; iChannel++) {
    Chan.iChannel = iChannel;
    EEDetId myEEDetId = EEDetId::unhashIndex(iChannel);
    Chan.ix = myEEDetId.ix();
    Chan.iy = myEEDetId.iy();
    Chan.iz = myEEDetId.zside();
    if(iChannel%1000 == 0) cout << " EE channel " << iChannel << " x " << Chan.ix << " y " << Chan.iy << " z " << Chan.iz << endl;
    tPedChan->Fill();
  }
  tPedChan->Write();
  tPedChan->Print();

  typedef struct {
    int Run; 
    double Mean[kChannels]; 
    double RMS[kChannels];
  } Ped_t;
  Ped_t PedVal;
  PedVal.Run = -1;        // initialization
  for (int iChannel = 0; iChannel < kChannels; iChannel++) {
    PedVal.Mean[iChannel] = -1.;
    PedVal.RMS[iChannel] = -1.;
  }
  TTree* tPedHist = new TTree("PedHist","Pedestal History"); // Output tree for pedestal mean/rms
  tPedHist->Branch("Pedestals", &PedVal.Run, "Run/I");
  tPedHist->Branch("Mean", PedVal.Mean, "Mean[75848]/D");
  tPedHist->Branch("RMS", PedVal.RMS, "RMS[75848]/D");*/

  // here we retrieve all the runs after the last from online DB 
  std::cout << "Retrieving run list from ONLINE DB ... " << std::endl;
  econn = new ESCondDBInterface( m_sid, m_user, m_pass );
  std::cout << "Connection done" << std::endl;
  if (!econn) {
    std::cout << " Problem with OMDS: connection parameters " <<m_sid <<"/"<<m_user<<"/"<<m_pass<<std::endl;
    throw cms::Exception("OMDS not available");
  } 

  // these are the online conditions DB classes 
  
  RunTag my_runtag;
  LocationDef my_locdef;
  RunTypeDef my_rundef;
	
  my_locdef.setLocation("P5PRO");
  my_rundef.setRunType("PEDESTAL");
  my_runtag.setLocationDef(my_locdef);
  my_runtag.setRunTypeDef(my_rundef);
  my_runtag.setGeneralTag(m_gentag); //was LOCAL in a previous time. This is GEN_TAG of RUN_TAG. PEDESTAL

  // here we retrieve the Monitoring run records
  MonVersionDef monverdef;
  monverdef.setMonitoringVersion("test01");
  MonRunTag mon_tag;
  mon_tag.setGeneralTag(m_esmonruniovtag); //was CMSSW
  mon_tag.setMonVersionDef(monverdef);
  
  run_t myRun=runnumber_; //289591  133734
  subrun_t mySubRun=1;
  
  //Creating output tag
  std::string cmcT= "CMC"; 
  std::string CMC_Range="4.3";
  std::string zsT="ZS";
  std::string ZS_Val="3.0";
  std::string sub_PedT="PS";

  if ( zerosup=="OFF" ) {  
    std::cout << "Setting ZS = 1.0 " << std::endl;
    ZS_Val="1.0";
    zsT="NZS";
  } else {
    std::cout << "ZS_Val(3.0): Going with this for now " << std::endl;
    zsT="ZS";
  }

  if( cmc=="OFF" ){ CMC_Range="0.0"; cmcT="NCMC";} 
  else { CMC_Range = "4.3"; cmcT= "CMC"; }

  if( Ped_sub =="OFF" ) { sub_PedT = "NPS"; } 
  else { sub_PedT="PS"; }

  std::string outtag = sub_PedT+"_"+zsT+"_"+cmcT+"_"+highlowg+"_"+Magnet;
  std::cout << "This is the out tag " << outtag << std::endl;
  
  

        std::cout<<"Looking for run: "<< myRun <<std::endl;
	try {
  		ESMonRunIOV myMonIOV = econn->fetchESMonRunIOV(&my_runtag, m_esmonruniovtag, myRun,mySubRun );	
		std::cout<<"MonIOV ID: "<<myMonIOV.fetchID()<<std::endl;
		std::map<EcalLogicID, ESMonPedestalsDat> dataset_mon;
		econn->fetchDataSet(&dataset_mon, &myMonIOV);
		typedef std::map<EcalLogicID, ESMonPedestalsDat>::const_iterator CImon;
		std::cout<<"Extracted "<<dataset_mon.size()<<" dataset."<<std::endl;
	        EcalLogicID ecid_xt;
        	ESMonPedestalsDat  rd_ped;
		//This is to write the table
		// std::map<EcalLogicID, ODESFEPedestalOffsetsDat > myosfeconfdat; 
		std::vector<ODESFEPedestalOffsetsDat > myosfeconfdat;
		myosfeconfdat.clear();
		

		ODESFEPedestalOffsetInfo myosfeconfinfo;
		// Get Last Version for tag
		// myosfeconfinfo.setId(276180);
		// myosfeconfinfo.setConfigTag(outtag);//outtag
		// myosfeconfinfo.setVersion(1);
		// myosfeconfinfo.setIov_pl(276180);
		// myosfeconfinfo.setIov_mi(276180);
		// myosfeconfinfo.setUser_comment("");
		//econn->fetchConfigSet(&myosfeconfinfo);

		// The following is to read from database ES_FE_CONF_INFO
		if (readfeconfinfo){
		  myosfeconfinfo.setId(therecid_);
		  // myosfeconfinfo.setConfigTag("PS_ZS_CMC_HG_BON");//outtag
		  // myosfeconfinfo.setVersion(4);
		  // myosfeconfinfo.setIov_pl(131328);
		  // myosfeconfinfo.setIov_mi(131327);
		  // myosfeconfinfo.setUser_comment("");
		  econn->fetchConfigSet(&myosfeconfinfo);
		  std::cout << "Version="  << myosfeconfinfo.getVersion() << " Iov+= " << myosfeconfinfo.getIov_pl() << " Iov-= " << myosfeconfinfo.getIov_mi() << endl;
		  std::cout << "COMMENT= " <<  myosfeconfinfo.getUser_comment() << "  Id= " << myosfeconfinfo.getId() << " Tag=" << myosfeconfinfo.getConfigTag()  << endl;
		}
		
		
		// int version= myosfeconfinfo.getVersion()+1;
		// std::cout << "The TAG = " << outtag << "  is now set with the version number: " << version << endl;

	

		//The following is to write to the database
		if (writefeconfinfo){
		  myosfeconfinfo.setId(0);//=>The code will increment from the last max rec_id when it sees the 0.
		  myosfeconfinfo.setConfigTag(outtag);//outtag
		  myosfeconfinfo.setVersion(1);
		  myosfeconfinfo.setIov_pl(0);
		  myosfeconfinfo.setIov_mi(0);
		  myosfeconfinfo.setUser_comment("write test andreas");
		  // myosfeconfinfo.setMagnet(0);
		  // myosfeconfinfo.setGain(0);
		  // myosfeconfinfo.setZero(0);

		  econn->insertConfigSet(&myosfeconfinfo) ;
		}

		//The following is to read the esfeconfdat table from the database
		if (readfeconfdat){
		  std::vector<ODESFEPedestalOffsetsDat> osfeconfdatread;
		  osfeconfdatread.clear();

		  econn->fetchConfigDataSet(&osfeconfdatread, &myosfeconfinfo);

		  for (std::vector<ODESFEPedestalOffsetsDat>::iterator it = osfeconfdatread.begin(); it != osfeconfdatread.end(); ++it ){
		    (*it).print();		      
		  }

		}
		
		for (CImon p = dataset_mon.begin(); p != dataset_mon.end(); p++) {
		        ODESFEPedestalOffsetsDat tmposfeconfdat;
			
			ecid_xt = p->first;
	                rd_ped  = p->second;
			// zs here is 1,2,3,4 -> ES+F ES+R ES-F ES-R
			int zs =  ( ( (int) ecid_xt.getLogicID()/1000000 ) % 10 ); 
			int zside = (zs==1 || zs==2 )? 0 : 1; //z=1 or 2 is ES+ (0) and z=3 or 4 is ES- (1)
			int lay = (zs==1 || zs==3 ) ? 0 : 1; //z=1 or 3 is first layer (0) and z=2 or 4 is second layer (1). 
			int st = ecid_xt.getLogicID() % 100; //goes from 1 to 32. 
			int ix = ecid_xt.getID2() + 1;
			int iy = ecid_xt.getID3() + 1;

			if ( ( FED[zside][lay][ix][iy] < 520) || ( FED[zside][lay][ix][iy] > 575) ){continue;}
			PED[zside][lay][ix][iy][st-1] = rd_ped.getPedMean();
			PEDRMS[zside][lay][ix][iy][st-1] = rd_ped.getPedRMS();

			// This is for the strip_id: Flip strip numbering from detector id to HW id
			int istr = st-1;
			
			if (zside==0 && lay==0 && iy<20) istr = 31 - istr;
			if (zside==0 && lay==1 && ix>=20) istr = 31 - istr;
			if (zside==1 && lay==0 && iy>=20) istr = 31 - istr;
			if (zside==1 && lay==1 && ix<20) istr = 31 - istr;
	
			// std::cout<<"Mean: "<<rd_ped.getPedMean() <<" - RMS: "<< rd_ped.getPedRMS()<< " - LOGIC_ID: " << ecid_xt.getLogicID() << " - id1: "<< ecid_xt.getID1() <<" - id2: " << ix << " - id3: "<< iy << " - getMapsTo: "<< ecid_xt.getMapsTo() << " - z value: " << ( (int) ecid_xt.getLogicID()/1000000 ) % 10 << " - strip " << ecid_xt.getLogicID() % 100  << std::endl;			
			// // Here I will fill the table with the required values
			// std::cout << "REC_ID " << myRun <<  " FED_ID " << FED[zside][lay][ix][iy] << " OPTORX_ID " << OPTORX[zside][lay][ix][iy] << " FIBER_ID " << FIBER[zside][lay][ix][iy] << " KCHIP_ID " << KCHIP[zside][lay][ix][iy] << " PACE_ID " << PACE[zside][lay][ix][iy] << " STRIP_ID " << istr+1 << " PEDESTAL " << PED[zside][lay][ix][iy][st-1] << " GAIN " << thegain_ << " ZS " << ZS[zside][lay][ix][iy][st-1] << " MASKED " << 0 << " CM_MASKED " << CMMASK[zside][lay][ix][iy][st-1] << " CM_RANGE " << CMRange[zside][lay][ix][iy][st-1] << std::endl; 

			int maskedval = 0;
			if( (PEDRMS[zside][lay][ix][iy][st-1] > 20) || (PEDRMS[zside][lay][ix][iy][st-1] < 3 ) ) {maskedval = 1;}
			else {maskedval = 0;}
			
			if( std::atof(CMC_Range.c_str()) != 0.0 ) { 
			  CMRange[zside][lay][ix][iy][st-1] = std::atof(CMC_Range.c_str()) * PEDRMS[zside][lay][ix][iy][st-1];
			} else { 
			  CMRange[zside][lay][ix][iy][st-1] = 0;
			}

			if(PEDRMS[zside][lay][ix][iy][st-1] > 8 ) { CMMASK[zside][lay][ix][iy][st-1] = 1; }
			else { CMMASK[zside][lay][ix][iy][st-1] = 0; }

			if( std::atof(ZS_Val.c_str()) != 1.0) { 
			  ZS[zside][lay][ix][iy][st-1] = std::atof(ZS_Val.c_str()) * PEDRMS[zside][lay][ix][iy][st-1];
			} else {
			  ZS[zside][lay][ix][iy][st-1] = 1;
			}


			tmposfeconfdat.setId(therecid_); 
			tmposfeconfdat.setFedId(FED[zside][lay][ix][iy]); 
			tmposfeconfdat.setFiberId(FIBER[zside][lay][ix][iy]); 
			tmposfeconfdat.setKchipId(KCHIP[zside][lay][ix][iy]); 
			tmposfeconfdat.setPaceId(PACE[zside][lay][ix][iy]); 
			tmposfeconfdat.setStripId(istr+1); 
			tmposfeconfdat.setRxId(OPTORX[zside][lay][ix][iy]); 
			tmposfeconfdat.setGain(thegain_); 
			tmposfeconfdat.setPedestal(PED[zside][lay][ix][iy][st-1]); 
			tmposfeconfdat.setMasked(maskedval); 
			tmposfeconfdat.setZs(ZS[zside][lay][ix][iy][st-1]); 
			tmposfeconfdat.setCmMasked(CMMASK[zside][lay][ix][iy][st-1]); 
			tmposfeconfdat.setCmRange(CMRange[zside][lay][ix][iy][st-1]); 
			tmposfeconfdat.setRms(PEDRMS[zside][lay][ix][iy][st-1]); 

			// myosfeconfdat.insert( std::map<EcalLogicID, ODESFEPedestalOffsetsDat >::value_type( ecid_xt,  tmposfeconfdat ) );

			myosfeconfdat.push_back( tmposfeconfdat );

			


		}	

		if ( econn && writefeconfdat ) {
		  try {
		    std::cout << "Inserting new Config Pedestals Data ..." << std::endl;
		    std::cout << myosfeconfdat.size() << std::endl;
		    if ( myosfeconfdat.size() != 0 ) econn->insertConfigDataArraySet(myosfeconfdat,&myosfeconfinfo);
		    // if ( myosfeconfdat.size() != 0 ) econn->insertConfigDataSet(myosfeconfdat,&myosfeconfinfo);

		    // if ( myosfeconfdat.size() != 0 ) econn->insertDataArraySet(&myosfeconfdat,&myosfeconfinfo);

		    std::cout << "done." << std::endl;
		  } catch (runtime_error &e) {
		    cerr << e.what() << endl;
		  }
		}
			

	

	} catch (exception &e) {
		std::cout << e.what() << std::endl;
	}

	RunTag my_outruntag;
	my_outruntag.setLocationDef(my_locdef);
	my_outruntag.setRunTypeDef(my_rundef);
	my_outruntag.setGeneralTag("LOCAL");	

	run_t myoutRun=276180;
	RunIOV outRunIOV;
	outRunIOV.setRunTag(my_outruntag);
	outRunIOV.setRunNumber(myoutRun);

	// ESMonRunIOV outMonIOV;
	// outMonIOV.setSubRunNumber(mySubRun);
	// outMonIOV.setRunIOV(outRunIOV);
	// outMonIOV.writeDB( &ecid_xt, &rd_ped, &outMonIOV );


	int mon_runs = 1;
  std::cout << "number of Mon runs is : " << mon_runs<< std::endl;

//  if(mon_runs > 0) {
  /*  int NbChan = 0;
    for (int iChannel = 0; iChannel < kEBChannels; iChannel++) {
      if(iChannel%10000 == 1) {
	hMean[NbChanNewPedestals_TEST.cc = new TH1F(Form("Mean_%i",NbChan),Form("Mean EB %i",iChannel), mon_runs, 0., mon_runs);
	hRMS[NbChan] = new TH1F(Form("RMS_%i",NbChan),Form("RMS EB %i",iChannel), mon_runs, 0., mon_runs);
	NbChan++;
      }
    }
    for (int iChannel = 0; iChannel < kEEChannels; iChannel++) {
      if(iChannel%2000 == 1) {
	hMean[NbChan] = new TH1F(Form("Mean_%i",NbChan),Form("Mean EE %i",iChannel), mon_runs, 0., mon_runs);
	hRMS[NbChan] = new TH1F(Form("RMS_%i",NbChan),Form("RMS EE %i",iChannel), mon_runs, 0., mon_runs);
	NbChan++;
      }
    }*/

    //    int krmax = std::min(mon_runs, 30);
      //std::cout << "-kr------:  "<< kr << std::endl;


      //unsigned int irun = static_cast<unsigned int>(myMon.getRunNumber());
      //std::cout << "retrieve the data for run number: "<< irun << std::endl;
      //if (myMon.getSubRunNumber() <=1){ 

	// retrieve the data for a given run
/*	RunIOV runiov_prime = myMon.getRunIOV();
	// retrieve the pedestals from OMDS for this run 
	std::map<EcalLogicID, ESMonPedestalsDat> dataset_mon;
	econn->fetchDataSet(&dataset_mon, &myMon);
	std::cout <<"OMDS record for run "<<irun  <<" is made of "<< dataset_mon.size() << std::endl;
	//int nEB = 0, nEE = 0, nEBbad = 0, nEEbad =0;
	typedef std::map<EcalLogicID, ESMonPedestalsDat>::const_iterator CImon;
	EcalLogicID ecid_xt;
	ESMonPedestalsDat  rd_ped;

	// this to validate ...	      
int nbad = 0;
	for (CImon p = dataset_mon.begin(); p != dataset_mon.end(); p++) {

		ecid_xt = p->first;
		rd_ped  = p->second;
		//std::cout<< rd_ped.getG1AvgSample01() << " " << rd_ped.getG1AvgSample02() <<std::endl;

	  ecid_xt = p->first;
	  rd_ped  = p->second;
	  int sm_num = ecid_xt.getID1();
	  int xt_num = ecid_xt.getID2();
	  int yt_num = ecid_xt.getID3();

	  //checkPedestal
	  bool result=true;
	  if(rd_ped.getPedRMSG12() > 3 || rd_ped.getPedRMSG12()<= 0 || rd_ped.getPedRMSG6() >2 || rd_ped.getPedRMSG12() <= 0
	     || rd_ped.getPedRMSG1() > 1 || rd_ped.getPedRMSG1() <= 0
	     || rd_ped.getPedMeanG12() > 300 || rd_ped.getPedMeanG12() <= 100
	     || rd_ped.getPedMeanG6() > 300 || rd_ped.getPedMeanG6() <= 100
	     || rd_ped.getPedMeanG1() > 300 || rd_ped.getPedMeanG6() <= 100) result=false; 

	  // here we check and count how many bad channels we have 
	  if(!result ) {
	    nbad++;
	    if(nbad < 10) std::cout <<"BAD LIST: channel " << sm_num << "/" << xt_num << "/"<< yt_num 
				    <<  "ped/rms "<< rd_ped.getPedMeanG12() << "/"<< rd_ped.getPedRMSG12() << std::endl;
	  }
	  if(ecid_xt.getName()=="EB_crystal_number") {
	    nEB++;
	    if(!result ) nEBbad++;
	  }
	  else {
	    nEE++;
	    if(!result ) nEEbad++;
	  }*/
	//}  // end loop over pedestal data
	// ok or bad? A bad run is for more than 5% bad channels 
/*
	//	      if(nbad<(dataset_mon.size()*0.1)){
	if(nbad < (dataset_mon.size()*0.05) && (nEB > 10200 || nEE > 2460)) {   // this is good run, fill histo and tree
	  PedVal.Run = irun;
	  int NbChan = 0;
	  for (CImon p = dataset_mon.begin(); p != dataset_mon.end(); p++) {
	    ecid_xt = p->first;
	    rd_ped  = p->second;
	    int sm_num = ecid_xt.getID1();
	    int xt_num = ecid_xt.getID2(); 
	    int yt_num = ecid_xt.getID3();

	    if(ecid_xt.getName()=="EB_crystal_number") {     // Barrel
	      EBDetId ebdetid(sm_num, xt_num, EBDetId::SMCRYSTALMODE);
	      int iChannel = ebdetid.hashedIndex();
	      if(iChannel < 0 || iChannel > 61200) cout << " SM " << sm_num << " Chan in SM " << xt_num 
							<< " IChannel " << iChannel << endl;
	      if(iChannel%10000 == 1) {
		hMean[NbChan]->Fill(kr, rd_ped.getPedMeanG12());
		hRMS[NbChan]->Fill(kr, rd_ped.getPedRMSG12());
		NbChan++;
	      }
	      PedVal.Mean[iChannel] = rd_ped.getPedMeanG12();
	      PedVal.RMS[iChannel] = rd_ped.getPedRMSG12();
	      if(iChannel%10000 == 0) cout << " channel " << iChannel << " mean " << PedVal.Mean[iChannel] << " RMS " << PedVal.RMS[iChannel] << endl;
	    }
	    else {   // Endcaps
	      if(EEDetId::validDetId(xt_num, yt_num, sm_num)) {
		EEDetId eedetid(xt_num,yt_num,sm_num);
		int iChannel = eedetid.hashedIndex();
		if(iChannel < 0 || iChannel > 14648) cout << " x " << sm_num << " y " << xt_num << " z " << yt_num
							  << " IChannel " << iChannel << endl;
		if(iChannel%2000 == 1) {
		  hMean[NbChan]->Fill(kr, rd_ped.getPedMeanG12());
		  hRMS[NbChan]->Fill(kr, rd_ped.getPedRMSG12());
		  NbChan++;
		}
		int iChanEE = kEBChannels + iChannel;
		//		cout << " channel EE " << iChanEE << endl;
		PedVal.Mean[iChanEE] = rd_ped.getPedMeanG12();
		PedVal.RMS[iChanEE] = rd_ped.getPedRMSG12();
	      }  // valid ee Id
	    }   // Endcaps
	  }    // loop over channels
	  tPedHist->Fill();
	  cout << " We got a good run " << irun << endl;
	}   // good run*/
      //}   // mon_run_vec
    //}   // loop over all runs
  //}   // number of runs > 0
  cout << "Exiting beginRun" << endl;
  /*for(int NbChan = 0; NbChan < 15; NbChan++) {
    if(hMean[NbChan]->GetEntries() > 0.) {    // save only when filled!
      hMean[NbChan]->Write();
      hRMS[NbChan]->Write();
    }
  }
  tPedHist->Write();
  tPedHist->Print();
  f.Close();*/

}//beginRun

//========================================================================
void ESNewPedestals::beginJob() {
///========================================================================

  cout << "Entering beginJob" << endl;

  cout << "Exiting beginJob" << endl;
}//beginJob

//========================================================================
void
ESNewPedestals::endJob() {
//========================================================================

  cout << "Entering endJob" << endl;
  cout << "Exiting endJob" << endl;
}//endJob

//
// member functions
//

//========================================================================
void
ESNewPedestals::analyze( const edm::Event& iEvent, const edm::EventSetup& iSetup ) {
//========================================================================
  
  if(cnt_evt_ == 0) {
    if(ECALType_ == "EB" || ECALType_ == "EA") {
      cout << " Barrel data : nb channels " << kEBChannels << endl;
  }
    else if(ECALType_ == "EE" || ECALType_ == "EA") {
      cout << " End cap data : nb channels " << kEEChannels << endl;
    }
    else {
      cout << " strange ECALtype : " << ECALType_ << " abort " << endl;
      return;
    }
    /*
    int NbOfmaskedChannels =  maskedChannels_.size();
    cout << " Nb masked EB channels " << NbOfmaskedChannels << endl;
    for (vector<int>::iterator iter = maskedChannels_.begin(); iter != maskedChannels_.end(); ++iter)
      cout<< " : masked channel " << *(iter) << endl;
    NbOfmaskedChannels =  maskedEEChannels_.size();
    cout << " Nb masked EE channels " << NbOfmaskedChannels << endl;
    for (vector<int>::iterator iter = maskedEEChannels_.begin(); iter != maskedEEChannels_.end(); ++iter)
      cout<< " : masked channel " << *(iter) << endl;
    */
  }
  cnt_evt_++;

  cout << "Exiting analyze" << endl;
}//analyze

//define this as a plug-in
DEFINE_FWK_MODULE( ESNewPedestals );
