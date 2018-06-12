#include "Validation/Geometry/interface/MaterialBudgetHGCalHistos.h"
#include "Validation/Geometry/interface/MaterialBudgetData.h"

template <class T> const T& max ( const T& a, const T& b ) {
  return (b<a)?a:b;     // or: return comp(b,a)?a:b; for the comp version
}



MaterialBudgetHGCalHistos::MaterialBudgetHGCalHistos(MaterialBudgetData* data,
							 TestHistoMgr* mgr,
							 const std::string& fileName ): MaterialBudgetFormat( data ), hmgr(mgr)
{
  theFileName = fileName;
  book();

}


void MaterialBudgetHGCalHistos::book() 
{
  std::cout << "=== booking user histos ===" << std::endl;

  // Parameters for 2D histograms
  int nzbin = 1100;
  float zMax = 5500.;
  float zMin = -5500.;
  int nrbin = 345;
  float rMin = -50.;
  float rMax = 3400.;
  
  // total X0
  hmgr->addHistoProf1( new TProfile("10", "MB prof Eta;#eta;x/X_{0} ", 250, -5., 5. ) );
  hmgr->addHisto1( new TH1F("11", "Eta " , 501, -5., 5. ) );
  hmgr->addHistoProf1( new TProfile("20", "MB prof Phi;#varphi [rad];x/X_{0} ", 180, -3.1416, 3.1416 ) );
  hmgr->addHisto1( new TH1F("21", "Phi " , 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf2( new TProfile2D("30", "MB prof Eta  Phi;#eta;#varphi;x/X_{0} ", 250, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHisto2( new TH2F("31", "Eta vs Phi " , 501, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf1( new TProfile("40", "MB prof R;R [mm];x/X_{0} ", 300, 0., 3000. ) );
  hmgr->addHisto1( new TH1F("41", "R " , 300, 0., 3000. ) );
  hmgr->addHistoProf2( new TProfile2D("50", "MB prof sum R  z;z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("999", "Tot track length for MB", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("51", "R vs z " , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("60", "MB prof local R  z;z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("61", "R vs z " , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  
  // Copper
  hmgr->addHistoProf1( new TProfile("110", "MB prof Eta [Copper];#eta;x/X_{0}", 250, -5.0, 5.0 ) );
  hmgr->addHisto1( new TH1F("111", "Eta [Copper]" , 501, -5., 5. ) );
  hmgr->addHistoProf1( new TProfile("120", "MB prof Phi [Copper];#varphi [rad];x/X_{0}", 180, -3.1416, 3.1416 ) );
  hmgr->addHisto1( new TH1F("121", "Phi [Copper]" , 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf2( new TProfile2D("130", "MB prof Eta  Phi [Copper];#eta;#varphi;x/X_{0}", 250, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHisto2( new TH2F("131", "Eta vs Phi [Copper]" , 501, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf1( new TProfile("140", "MB prof R [Copper];R [mm];x/X_{0}", 300, 0., 3000. ) );
  hmgr->addHisto1( new TH1F("141", "R [Copper]" , 300, 0., 3000. ) );
  hmgr->addHistoProf2( new TProfile2D("150", "MB prof sum R  z [Copper];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("151", "R vs z [Copper]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("160", "MB prof local R  z [Copper];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("161", "R vs z [Copper]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  // H_Scintillator
  hmgr->addHistoProf1( new TProfile("210", "MB prof Eta [Scintillator];#eta;x/X_{0}", 250, -5.0, 5.0 ) );
  hmgr->addHisto1( new TH1F("211", "Eta [Scintillator]" , 501, -5., 5. ) );
  hmgr->addHistoProf1( new TProfile("220", "MB prof Phi [Scintillator];#varphi [rad];x/X_{0}", 180, -3.1416, 3.1416 ) );
  hmgr->addHisto1( new TH1F("221", "Phi [Scintillator]" , 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf2( new TProfile2D("230", "MB prof Eta  Phi [Scintillator];#eta;#varphi;x/X_{0}", 250, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHisto2( new TH2F("231", "Eta vs Phi [Scintillator]" , 501, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf1( new TProfile("240", "MB prof R [Scintillator];R [mm];x/X_{0}", 300, 0., 3000. ) );
  hmgr->addHisto1( new TH1F("241", "R [Scintillator]" , 300, 0., 3000. ) );
  hmgr->addHistoProf2( new TProfile2D("250", "MB prof sum R  z [Scintillator];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("251", "R vs z [Scintillator]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("260", "MB prof local R  z [Scintillator];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("261", "R vs z [Scintillator]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  // Cables
  hmgr->addHistoProf1( new TProfile("310", "MB prof Eta [Cables];#eta;x/X_{0}", 250, -5.0, 5.0 ) );
  hmgr->addHisto1( new TH1F("311", "Eta [Cables]" , 501, -5., 5. ) );
  hmgr->addHistoProf1( new TProfile("320", "MB prof Phi [Cables];#varphi [rad];x/X_{0}", 180, -3.1416, 3.1416 ) );
  hmgr->addHisto1( new TH1F("321", "Phi [Cables]" , 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf2( new TProfile2D("330", "MB prof Eta  Phi [Cables];#eta;#varphi;x/X_{0}", 250, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHisto2( new TH2F("331", "Eta vs Phi [Cables]" , 501, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf1( new TProfile("340", "MB prof R [Cables];R [mm];x/X_{0}", 300, 0., 3000. ) );
  hmgr->addHisto1( new TH1F("341", "R [Cables]" , 300, 0., 3000. ) );
  hmgr->addHistoProf2( new TProfile2D("350", "MB prof sum R  z [Cables];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("351", "R vs z [Cables]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("360", "MB prof local R  z [Cables];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("361", "R vs z [Cables]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  // M_NEMA_FR4_plate
  hmgr->addHistoProf1( new TProfile("410", "MB prof Eta [M_NEMA_FR4_plate];#eta;x/X_{0}", 250, -5.0, 5.0 ) );
  hmgr->addHisto1( new TH1F("411", "Eta [M_NEMA_FR4_plate]" , 501, -5., 5. ) );
  hmgr->addHistoProf1( new TProfile("420", "MB prof Phi [M_NEMA_FR4_plate];#varphi [rad];x/X_{0}", 180, -3.1416, 3.1416 ) );
  hmgr->addHisto1( new TH1F("421", "Phi [M_NEMA_FR4_plate]" , 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf2( new TProfile2D("430", "MB prof Eta  Phi [M_NEMA_FR4_plate];#eta;#varphi;x/X_{0}", 250, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHisto2( new TH2F("431", "Eta vs Phi [M_NEMA_FR4_plate]" , 501, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf1( new TProfile("440", "MB prof R [M_NEMA_FR4_plate];R [mm];x/X_{0}", 300, 0., 3000. ) );
  hmgr->addHisto1( new TH1F("441", "R [M_NEMA_FR4_plate]" , 300, 0., 3000. ) );
  hmgr->addHistoProf2( new TProfile2D("450", "MB prof sum R  z [M_NEMA_FR4_plate];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("451", "R vs z [M_NEMA_FR4_plate]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("460", "MB prof local R  z [M_NEMA_FR4_plate];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("461", "R vs z [M_NEMA_FR4_plate]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  // Silicon
  hmgr->addHistoProf1( new TProfile("510", "MB prof Eta [Silicon];#eta;x/X_{0}", 250, -5.0, 5.0 ) );
  hmgr->addHisto1( new TH1F("511", "Eta [Silicon]" , 501, -5., 5. ) );
  hmgr->addHistoProf1( new TProfile("520", "MB prof Phi [Silicon];#varphi [rad];x/X_{0}", 180, -3.1416, 3.1416 ) );
  hmgr->addHisto1( new TH1F("521", "Phi [Silicon]" , 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf2( new TProfile2D("530", "MB prof Eta  Phi [Silicon];#eta;#varphi;x/X_{0}", 250, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHisto2( new TH2F("531", "Eta vs Phi [Silicon]" , 501, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf1( new TProfile("540", "MB prof R [Silicon];R [mm];x/X_{0}", 300, 0., 3000. ) );
  hmgr->addHisto1( new TH1F("541", "R [Silicon]" , 300, 0., 3000. ) );
  hmgr->addHistoProf2( new TProfile2D("550", "MB prof sum R  z [Silicon];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("551", "R vs z [Silicon]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("560", "MB prof local R  z [Silicon];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("561", "R vs z [Silicon]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  // Other
  hmgr->addHistoProf1( new TProfile("610", "MB prof Eta [Other];#eta;x/X_{0}", 250, -5.0, 5.0 ) );
  hmgr->addHisto1( new TH1F("611", "Eta [Other]" , 501, -5., 5. ) );
  hmgr->addHistoProf1( new TProfile("620", "MB prof Phi [Other];#varphi [rad];x/X_{0}", 180, -3.1416, 3.1416 ) );
  hmgr->addHisto1( new TH1F("621", "Phi [Other]" , 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf2( new TProfile2D("630", "MB prof Eta  Phi [Other];#eta;#varphi;x/X_{0}", 250, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHisto2( new TH2F("631", "Eta vs Phi [Other]" , 501, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf1( new TProfile("640", "MB prof R [Other];R [mm];x/X_{0}", 300, 0., 3000. ) );
  hmgr->addHisto1( new TH1F("641", "R [Other]" , 300, 0., 3000. ) );
  hmgr->addHistoProf2( new TProfile2D("650", "MB prof sum R  z [Other];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("651", "R vs z [Other]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("660", "MB prof local R  z [Other];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("661", "R vs z [Other]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  // Air
  hmgr->addHistoProf1( new TProfile("710", "MB prof Eta [Air];#eta;x/X_{0}", 250, -5.0, 5.0 ) );
  hmgr->addHisto1( new TH1F("711", "Eta [Air]" , 501, -5., 5. ) );
  hmgr->addHistoProf1( new TProfile("720", "MB prof Phi [Air];#varphi [rad];x/X_{0}", 180, -3.1416, 3.1416 ) );
  hmgr->addHisto1( new TH1F("721", "Phi [Air]" , 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf2( new TProfile2D("730", "MB prof Eta  Phi [Air];#eta;#varphi;x/X_{0}", 250, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHisto2( new TH2F("731", "Eta vs Phi [Air]" , 501, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf1( new TProfile("740", "MB prof R [Air];R [mm];x/X_{0}", 300, 0., 3000. ) );
  hmgr->addHisto1( new TH1F("741", "R [Air]" , 300, 0., 3000. ) );
  hmgr->addHistoProf2( new TProfile2D("750", "MB prof sum R  z [Air];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("751", "R vs z [Air]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("760", "MB prof local R  z [Air];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("761", "R vs z [Air]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  //StainlessSteel
  hmgr->addHistoProf1( new TProfile("810", "MB prof Eta [StainlessSteel];#eta;x/X_{0}", 250, -5.0, 5.0 ) );
  hmgr->addHisto1( new TH1F("811", "Eta [StainlessSteel]" , 501, -5., 5. ) );
  hmgr->addHistoProf1( new TProfile("820", "MB prof Phi [StainlessSteel];#varphi [rad];x/X_{0}", 180, -3.1416, 3.1416 ) );
  hmgr->addHisto1( new TH1F("821", "Phi [StainlessSteel]" , 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf2( new TProfile2D("830", "MB prof Eta  Phi [StainlessSteel];#eta;#varphi;x/X_{0}", 250, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHisto2( new TH2F("831", "Eta vs Phi [StainlessSteel]" , 501, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf1( new TProfile("840", "MB prof R [StainlessSteel];R [mm];x/X_{0}", 300, 0., 3000. ) );
  hmgr->addHisto1( new TH1F("841", "R [StainlessSteel]" , 300, 0., 3000. ) );
  hmgr->addHistoProf2( new TProfile2D("850", "MB prof sum R  z [StainlessSteel];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("851", "R vs z [StainlessSteel]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("860", "MB prof local R  z [StainlessSteel];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("861", "R vs z [StainlessSteel]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  //WCu
  hmgr->addHistoProf1( new TProfile("910", "MB prof Eta [WCu];#eta;x/X_{0}", 250, -5.0, 5.0 ) );
  hmgr->addHisto1( new TH1F("911", "Eta [WCu]" , 501, -5., 5. ) );
  hmgr->addHistoProf1( new TProfile("920", "MB prof Phi [WCu];#varphi [rad];x/X_{0}", 180, -3.1416, 3.1416 ) );
  hmgr->addHisto1( new TH1F("921", "Phi [WCu]" , 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf2( new TProfile2D("930", "MB prof Eta  Phi [WCu];#eta;#varphi;x/X_{0}", 250, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHisto2( new TH2F("931", "Eta vs Phi [WCu]" , 501, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf1( new TProfile("940", "MB prof R [WCu];R [mm];x/X_{0}", 300, 0., 3000. ) );
  hmgr->addHisto1( new TH1F("941", "R [WCu]" , 300, 0., 3000. ) );
  hmgr->addHistoProf2( new TProfile2D("950", "MB prof sum R  z [WCu];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("951", "R vs z [WCu]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("960", "MB prof local R  z [WCu];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("961", "R vs z [WCu]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );


  
  // total Lambda0
  hmgr->addHistoProf1( new TProfile("1010", "IL prof Eta;#eta;#lambda/#lambda_{0} ", 250, -5., 5. ) );
  hmgr->addHisto1( new TH1F("1011", "Eta " , 501, -5., 5. ) );
  hmgr->addHistoProf1( new TProfile("1020", "IL prof Phi;#varphi [rad];#lambda/#lambda_{0} ", 180, -3.1416, 3.1416 ) );
  hmgr->addHisto1( new TH1F("1021", "Phi " , 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf2( new TProfile2D("1030", "IL prof Eta  Phi;#eta;#varphi;#lambda/#lambda_{0} ", 250, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHisto2( new TH2F("1031", "Eta vs Phi " , 501, -5., 5., 180, -3.1416, 3.1416 ) );
  
  // rr
  hmgr->addHistoProf1( new TProfile("1040", "IL prof R;R [mm];#lambda/#lambda_{0} ", 300, 0., 3000. ) );
  hmgr->addHisto1( new TH1F("1041", "R " , 300, 0., 3000. ) );
  hmgr->addHistoProf2( new TProfile2D("1050", "IL prof sum R  z;z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1999", "Tot track length for l0", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1051", "R vs z " , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1060", "IL prof local R  z;z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1061", "R vs z " , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  
  // Copper
  hmgr->addHistoProf1( new TProfile("1110", "IL prof Eta [Copper];#eta;#lambda/#lambda_{0}", 250, -5.0, 5.0 ) );
  hmgr->addHisto1( new TH1F("1111", "Eta [Copper]" , 501, -5., 5. ) );
  hmgr->addHistoProf1( new TProfile("1120", "IL prof Phi [Copper];#varphi [rad];#lambda/#lambda_{0}", 180, -3.1416, 3.1416 ) );
  hmgr->addHisto1( new TH1F("1121", "Phi [Copper]" , 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf2( new TProfile2D("1130", "IL prof Eta  Phi [Copper];#eta;#varphi;#lambda/#lambda_{0}", 250, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHisto2( new TH2F("1131", "Eta vs Phi [Copper]" , 501, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf1( new TProfile("1140", "IL prof R [Copper];R [mm];#lambda/#lambda_{0}", 300, 0., 3000. ) );
  hmgr->addHisto1( new TH1F("1141", "R [Copper]" , 300, 0., 3000. ) );
  hmgr->addHistoProf2( new TProfile2D("1150", "IL prof sum R  z [Copper];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1151", "R vs z [Copper]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1160", "IL prof local R  z [Copper];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1161", "R vs z [Copper]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  // H_Scintillator
  hmgr->addHistoProf1( new TProfile("1210", "IL prof Eta [Scintillator];#eta;#lambda/#lambda_{0}", 250, -5.0, 5.0 ) );
  hmgr->addHisto1( new TH1F("1211", "Eta [Scintillator]" , 501, -5., 5. ) );
  hmgr->addHistoProf1( new TProfile("1220", "IL prof Phi [Scintillator];#varphi [rad];#lambda/#lambda_{0}", 180, -3.1416, 3.1416 ) );
  hmgr->addHisto1( new TH1F("1221", "Phi [Scintillator]" , 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf2( new TProfile2D("1230", "IL prof Eta  Phi [Scintillator];#eta;#varphi;#lambda/#lambda_{0}", 250, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHisto2( new TH2F("1231", "Eta vs Phi [Scintillator]" , 501, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf1( new TProfile("1240", "IL prof R [Scintillator];R [mm];#lambda/#lambda_{0}", 300, 0., 3000. ) );
  hmgr->addHisto1( new TH1F("1241", "R [Scintillator]" , 300, 0., 3000. ) );
  hmgr->addHistoProf2( new TProfile2D("1250", "IL prof sum R  z [Scintillator];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1251", "R vs z [Scintillator]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1260", "IL prof local R  z [Scintillator];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1261", "R vs z [Scintillator]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  // Cables
  hmgr->addHistoProf1( new TProfile("1310", "IL prof Eta [Cables];#eta;#lambda/#lambda_{0}", 250, -5.0, 5.0 ) );
  hmgr->addHisto1( new TH1F("1311", "Eta [Cables]" , 501, -5., 5. ) );
  hmgr->addHistoProf1( new TProfile("1320", "IL prof Phi [Cables];#varphi [rad];#lambda/#lambda_{0}", 180, -3.1416, 3.1416 ) );
  hmgr->addHisto1( new TH1F("1321", "Phi [Cables]" , 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf2( new TProfile2D("1330", "IL prof Eta  Phi [Cables];#eta;#varphi;#lambda/#lambda_{0}", 250, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHisto2( new TH2F("1331", "Eta vs Phi [Cables]" , 501, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf1( new TProfile("1340", "IL prof R [Cables];R [mm];#lambda/#lambda_{0}", 300, 0., 3000. ) );
  hmgr->addHisto1( new TH1F("1341", "R [Cables]" , 300, 0., 3000. ) );
  hmgr->addHistoProf2( new TProfile2D("1350", "IL prof sum R  z [Cables];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1351", "R vs z [Cables]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1360", "IL prof local R  z [Cables];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1361", "R vs z [Cables]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  // M_NEMA_FR4_plate
  hmgr->addHistoProf1( new TProfile("1410", "IL prof Eta [M_NEMA_FR4_plate];#eta;#lambda/#lambda_{0}", 250, -5.0, 5.0 ) );
  hmgr->addHisto1( new TH1F("1411", "Eta [M_NEMA_FR4_plate]" , 501, -5., 5. ) );
  hmgr->addHistoProf1( new TProfile("1420", "IL prof Phi [M_NEMA_FR4_plate];#varphi [rad];#lambda/#lambda_{0}", 180, -3.1416, 3.1416 ) );
  hmgr->addHisto1( new TH1F("1421", "Phi [M_NEMA_FR4_plate]" , 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf2( new TProfile2D("1430", "IL prof Eta  Phi [M_NEMA_FR4_plate];#eta;#varphi;#lambda/#lambda_{0}", 250, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHisto2( new TH2F("1431", "Eta vs Phi [M_NEMA_FR4_plate]" , 501, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf1( new TProfile("1440", "IL prof R [M_NEMA_FR4_plate];R [mm];#lambda/#lambda_{0}", 300, 0., 3000. ) );
  hmgr->addHisto1( new TH1F("1441", "R [M_NEMA_FR4_plate]" , 300, 0., 3000. ) );
  hmgr->addHistoProf2( new TProfile2D("1450", "IL prof sum R  z [M_NEMA_FR4_plate];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1451", "R vs z [M_NEMA_FR4_plate]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1460", "IL prof local R  z [M_NEMA_FR4_plate];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1461", "R vs z [M_NEMA_FR4_plate]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  // Silicon
  hmgr->addHistoProf1( new TProfile("1510", "IL prof Eta [Silicon];#eta;#lambda/#lambda_{0}", 250, -5.0, 5.0 ) );
  hmgr->addHisto1( new TH1F("1511", "Eta [Silicon]" , 501, -5., 5. ) );
  hmgr->addHistoProf1( new TProfile("1520", "IL prof Phi [Silicon];#varphi [rad];#lambda/#lambda_{0}", 180, -3.1416, 3.1416 ) );
  hmgr->addHisto1( new TH1F("1521", "Phi [Silicon]" , 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf2( new TProfile2D("1530", "IL prof Eta  Phi [Silicon];#eta;#varphi;#lambda/#lambda_{0}", 250, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHisto2( new TH2F("1531", "Eta vs Phi [Silicon]" , 501, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf1( new TProfile("1540", "IL prof R [Silicon];R [mm];#lambda/#lambda_{0}", 300, 0., 3000. ) );
  hmgr->addHisto1( new TH1F("1541", "R [Silicon]" , 300, 0., 3000. ) );
  hmgr->addHistoProf2( new TProfile2D("1550", "IL prof sum R  z [Silicon];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1551", "R vs z [Silicon]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1560", "IL prof local R  z [Silicon];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1561", "R vs z [Silicon]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  // Other
  hmgr->addHistoProf1( new TProfile("1610", "IL prof Eta [Other];#eta;#lambda/#lambda_{0}", 250, -5.0, 5.0 ) );
  hmgr->addHisto1( new TH1F("1611", "Eta [Other]" , 501, -5., 5. ) );
  hmgr->addHistoProf1( new TProfile("1620", "IL prof Phi [Other];#varphi [rad];#lambda/#lambda_{0}", 180, -3.1416, 3.1416 ) );
  hmgr->addHisto1( new TH1F("1621", "Phi [Other]" , 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf2( new TProfile2D("1630", "IL prof Eta  Phi [Other];#eta;#varphi;#lambda/#lambda_{0}", 250, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHisto2( new TH2F("1631", "Eta vs Phi [Other]" , 501, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf1( new TProfile("1640", "IL prof R [Other];R [mm];#lambda/#lambda_{0}", 300, 0., 3000. ) );
  hmgr->addHisto1( new TH1F("1641", "R [Other]" , 300, 0., 3000. ) );
  hmgr->addHistoProf2( new TProfile2D("1650", "IL prof sum R  z [Other];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1651", "R vs z [Other]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1660", "IL prof local R  z [Other];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1661", "R vs z [Other]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  // Air
  hmgr->addHistoProf1( new TProfile("1710", "IL prof Eta [Air];#eta;#lambda/#lambda_{0}", 250, -5.0, 5.0 ) );
  hmgr->addHisto1( new TH1F("1711", "Eta [Air]" , 501, -5., 5. ) );
  hmgr->addHistoProf1( new TProfile("1720", "IL prof Phi [Air];#varphi [rad];#lambda/#lambda_{0}", 180, -3.1416, 3.1416 ) );
  hmgr->addHisto1( new TH1F("1721", "Phi [Air]" , 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf2( new TProfile2D("1730", "IL prof Eta  Phi [Air];#eta;#varphi;#lambda/#lambda_{0}", 250, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHisto2( new TH2F("1731", "Eta vs Phi [Air]" , 501, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf1( new TProfile("1740", "IL prof R [Air];R [mm];#lambda/#lambda_{0}", 300, 0., 3000. ) );
  hmgr->addHisto1( new TH1F("1741", "R [Air]" , 300, 0., 3000. ) );
  hmgr->addHistoProf2( new TProfile2D("1750", "IL prof sum R  z [Air];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1751", "R vs z [Air]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1760", "IL prof local R  z [Air];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1761", "R vs z [Air]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  //StainlessSteel
  hmgr->addHistoProf1( new TProfile("1810", "IL prof Eta [StainlessSteel];#eta;#lambda/#lambda_{0}", 250, -5.0, 5.0 ) );
  hmgr->addHisto1( new TH1F("1811", "Eta [StainlessSteel]" , 501, -5., 5. ) );
  hmgr->addHistoProf1( new TProfile("1820", "IL prof Phi [StainlessSteel];#varphi [rad];#lambda/#lambda_{0}", 180, -3.1416, 3.1416 ) );
  hmgr->addHisto1( new TH1F("1821", "Phi [StainlessSteel]" , 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf2( new TProfile2D("1830", "IL prof Eta  Phi [StainlessSteel];#eta;#varphi;#lambda/#lambda_{0}", 250, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHisto2( new TH2F("1831", "Eta vs Phi [StainlessSteel]" , 501, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf1( new TProfile("1840", "IL prof R [StainlessSteel];R [mm];#lambda/#lambda_{0}", 300, 0., 3000. ) );
  hmgr->addHisto1( new TH1F("1841", "R [StainlessSteel]" , 300, 0., 3000. ) );
  hmgr->addHistoProf2( new TProfile2D("1850", "IL prof sum R  z [StainlessSteel];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1851", "R vs z [StainlessSteel]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1860", "IL prof local R  z [StainlessSteel];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1861", "R vs z [StainlessSteel]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  //WCu
  hmgr->addHistoProf1( new TProfile("1910", "IL prof Eta [WCu];#eta;#lambda/#lambda_{0}", 250, -5.0, 5.0 ) );
  hmgr->addHisto1( new TH1F("1911", "Eta [WCu]" , 501, -5., 5. ) );
  hmgr->addHistoProf1( new TProfile("1920", "IL prof Phi [WCu];#varphi [rad];#lambda/#lambda_{0}", 180, -3.1416, 3.1416 ) );
  hmgr->addHisto1( new TH1F("1921", "Phi [WCu]" , 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf2( new TProfile2D("1930", "IL prof Eta  Phi [WCu];#eta;#varphi;#lambda/#lambda_{0}", 250, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHisto2( new TH2F("1931", "Eta vs Phi [WCu]" , 501, -5., 5., 180, -3.1416, 3.1416 ) );
  hmgr->addHistoProf1( new TProfile("1940", "IL prof R [WCu];R [mm];#lambda/#lambda_{0}", 300, 0., 3000. ) );
  hmgr->addHisto1( new TH1F("1941", "R [WCu]" , 300, 0., 3000. ) );
  hmgr->addHistoProf2( new TProfile2D("1950", "IL prof sum R  z [WCu];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1951", "R vs z [WCu]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1960", "IL prof local R  z [WCu];z [mm];R [mm];x/X_{0} ", nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  hmgr->addHisto2( new TH2F("1961", "R vs z [WCu]" , nzbin, zMin, zMax, nrbin, rMin, rMax ) );
  //
  
  // rr
  
  std::cout << "=== booking user histos done ===" << std::endl;

}


void MaterialBudgetHGCalHistos::fillStartTrack()
{

}


void MaterialBudgetHGCalHistos::fillPerStep()
{

}


void MaterialBudgetHGCalHistos::fillEndTrack()
{
  //
  // fill histograms and profiles only if the material has been crossed
  //
  
  if( theData->getNumberOfSteps() != 0 ) {
    
    // Total X0
    hmgr->getHisto1(11)->Fill(theData->getEta());
    hmgr->getHisto1(21)->Fill(theData->getPhi());
    hmgr->getHisto2(31)->Fill(theData->getEta(),theData->getPhi());
    
    hmgr->getHistoProf1(10)->Fill(theData->getEta(),theData->getTotalMB());
    hmgr->getHistoProf1(20)->Fill(theData->getPhi(),theData->getTotalMB());
    hmgr->getHistoProf2(30)->Fill(theData->getEta(),theData->getPhi(),theData->getTotalMB());
    
    // rr
    
    // Copper
    hmgr->getHisto1(111)->Fill(theData->getEta());
    hmgr->getHisto1(121)->Fill(theData->getPhi());
    hmgr->getHisto2(131)->Fill(theData->getEta(),theData->getPhi());
    
    hmgr->getHistoProf1(110)->Fill(theData->getEta(),theData->getCopperMB());
    hmgr->getHistoProf1(120)->Fill(theData->getPhi(),theData->getCopperMB());
    hmgr->getHistoProf2(130)->Fill(theData->getEta(),theData->getPhi(),theData->getCopperMB());
    
    // H_Scintillator
    hmgr->getHisto1(211)->Fill(theData->getEta());
    hmgr->getHisto1(221)->Fill(theData->getPhi());
    hmgr->getHisto2(231)->Fill(theData->getEta(),theData->getPhi());
    
    hmgr->getHistoProf1(210)->Fill(theData->getEta(),theData->getH_ScintillatorMB());
    hmgr->getHistoProf1(220)->Fill(theData->getPhi(),theData->getH_ScintillatorMB());
    hmgr->getHistoProf2(230)->Fill(theData->getEta(),theData->getPhi(),theData->getH_ScintillatorMB());
    
    // Cables
    hmgr->getHisto1(311)->Fill(theData->getEta());
    hmgr->getHisto1(321)->Fill(theData->getPhi());
    hmgr->getHisto2(331)->Fill(theData->getEta(),theData->getPhi());
    
    hmgr->getHistoProf1(310)->Fill(theData->getEta(),theData->getCablesMB());
    hmgr->getHistoProf1(320)->Fill(theData->getPhi(),theData->getCablesMB());
    hmgr->getHistoProf2(330)->Fill(theData->getEta(),theData->getPhi(),theData->getCablesMB());
    
    // M_NEMA_FR4_plate
    hmgr->getHisto1(411)->Fill(theData->getEta());
    hmgr->getHisto1(421)->Fill(theData->getPhi());
    hmgr->getHisto2(431)->Fill(theData->getEta(),theData->getPhi());
    
    hmgr->getHistoProf1(410)->Fill(theData->getEta(),theData->getM_NEMA_FR4_plateMB());
    hmgr->getHistoProf1(420)->Fill(theData->getPhi(),theData->getM_NEMA_FR4_plateMB());
    hmgr->getHistoProf2(430)->Fill(theData->getEta(),theData->getPhi(),theData->getM_NEMA_FR4_plateMB());
    
    // Silicon
    hmgr->getHisto1(511)->Fill(theData->getEta());
    hmgr->getHisto1(521)->Fill(theData->getPhi());
    hmgr->getHisto2(531)->Fill(theData->getEta(),theData->getPhi());
    
    hmgr->getHistoProf1(510)->Fill(theData->getEta(),theData->getSiliconMB());
    hmgr->getHistoProf1(520)->Fill(theData->getPhi(),theData->getSiliconMB());
    hmgr->getHistoProf2(530)->Fill(theData->getEta(),theData->getPhi(),theData->getSiliconMB());
    
    // Other
    hmgr->getHisto1(611)->Fill(theData->getEta());
    hmgr->getHisto1(621)->Fill(theData->getPhi());
    hmgr->getHisto2(631)->Fill(theData->getEta(),theData->getPhi());
    
    hmgr->getHistoProf1(610)->Fill(theData->getEta(),theData->getOtherMB());
    hmgr->getHistoProf1(620)->Fill(theData->getPhi(),theData->getOtherMB());
    hmgr->getHistoProf2(630)->Fill(theData->getEta(),theData->getPhi(),theData->getOtherMB());
    
    // Air
    hmgr->getHisto1(711)->Fill(theData->getEta());
    hmgr->getHisto1(721)->Fill(theData->getPhi());
    hmgr->getHisto2(731)->Fill(theData->getEta(),theData->getPhi());
    
    hmgr->getHistoProf1(710)->Fill(theData->getEta(),theData->getAirMB());
    hmgr->getHistoProf1(720)->Fill(theData->getPhi(),theData->getAirMB());
    hmgr->getHistoProf2(730)->Fill(theData->getEta(),theData->getPhi(),theData->getAirMB());
    
    // StainlessSteel
    hmgr->getHisto1(811)->Fill(theData->getEta());
    hmgr->getHisto1(821)->Fill(theData->getPhi());
    hmgr->getHisto2(831)->Fill(theData->getEta(),theData->getPhi());
    
    hmgr->getHistoProf1(810)->Fill(theData->getEta(),theData->getStainlessSteelMB());
    hmgr->getHistoProf1(820)->Fill(theData->getPhi(),theData->getStainlessSteelMB());
    hmgr->getHistoProf2(830)->Fill(theData->getEta(),theData->getPhi(),theData->getStainlessSteelMB());

    // WCu
    hmgr->getHisto1(911)->Fill(theData->getEta());
    hmgr->getHisto1(921)->Fill(theData->getPhi());
    hmgr->getHisto2(931)->Fill(theData->getEta(),theData->getPhi());
    
    hmgr->getHistoProf1(910)->Fill(theData->getEta(),theData->getWCuMB());
    hmgr->getHistoProf1(920)->Fill(theData->getPhi(),theData->getWCuMB());
    hmgr->getHistoProf2(930)->Fill(theData->getEta(),theData->getPhi(),theData->getWCuMB());

    //
    // Compute the total x/X0 crossed at each step radius for each path
    //
    //
    float theTotalMB_TOT = 0.0;
    float theTotalMB_COP = 0.0;
    float theTotalMB_SCI = 0.0;
    float theTotalMB_CAB = 0.0;
    float theTotalMB_MNE = 0.0;
    float theTotalMB_NIM = 0.0;
    float theTotalMB_OTH = 0.0;
    float theTotalMB_AIR = 0.0;
    float theTotalMB_SST = 0.0;
    float theTotalMB_WCU = 0.0;
    for(int iStep = 0; iStep < theData->getNumberOfSteps(); iStep++) {
      theTotalMB_TOT += theData->getStepDmb(iStep);
      theTotalMB_COP += theData->getCopperDmb(iStep);
      theTotalMB_SCI += theData->getH_ScintillatorDmb(iStep);
      theTotalMB_CAB += theData->getCablesDmb(iStep);
      theTotalMB_MNE += theData->getM_NEMA_FR4_plateDmb(iStep);
      theTotalMB_NIM += theData->getSiliconDmb(iStep);
      theTotalMB_OTH += theData->getOtherDmb(iStep);
      theTotalMB_AIR += theData->getAirDmb(iStep);        
      theTotalMB_SST += theData->getStainlessSteelDmb(iStep);        
      theTotalMB_WCU += theData->getWCuDmb(iStep);        

      int iCop = 0;
      int iSci = 0;
      int iCab = 0;
      int iMne = 0;
      int iSil = 0;
      int iOth = 0;
      int iAir = 0;
      int iSst = 0;
      int iWcu = 0;
      if( theData->getCopperDmb(iStep)>0.     ) { iCop = 1; }
      if( theData->getH_ScintillatorDmb(iStep)>0.   ) { iSci = 1; }
      if( theData->getCablesDmb(iStep)>0.      ) { iCab = 1; }
      if( theData->getM_NEMA_FR4_plateDmb(iStep)>0.     ) { iMne = 1; }
      if( theData->getSiliconDmb(iStep)>0. ) { iSil = 1; }
      if( theData->getOtherDmb(iStep)>0.       ) { iOth = 1; }
      if( theData->getAirDmb(iStep)>0.         ) { iAir = 1; }
      if( theData->getStainlessSteelDmb(iStep)>0.         ) { iSst = 1; }
      if( theData->getWCuDmb(iStep)>0.         ) { iWcu = 1; }

      float deltaRadius = sqrt(
			       pow( theData->getStepFinalX(iStep)-theData->getStepInitialX(iStep),2 )
			       +
			       pow( theData->getStepFinalY(iStep)-theData->getStepInitialY(iStep),2 )
			       );
      float deltaz = theData->getStepFinalZ(iStep)-theData->getStepInitialZ(iStep) ;
      
      float x0 = theData->getStepMaterialX0(iStep);

      int nSubStep = 2;
      float boxWidth = 0.1;
      if( (deltaRadius>boxWidth) || (fabs(deltaz)>boxWidth) ) {
	nSubStep = static_cast<int>(max(
		       ceil(deltaRadius/boxWidth/2.)*2,
		       ceil(fabs(deltaz)/boxWidth/2.)*2
		       ));
      }
      
      for(int iSubStep = 1; iSubStep < nSubStep; iSubStep+=2) {

	float subdeltaRadius = deltaRadius/nSubStep;
	float polarRadius = sqrt(
				 pow( theData->getStepInitialX(iStep),2 )
				 +
				 pow( theData->getStepInitialY(iStep),2 )
				 ) + iSubStep*subdeltaRadius;

	float subdeltaz = deltaz/nSubStep;
	float z = theData->getStepInitialZ(iStep) + iSubStep*subdeltaz;

	float subdelta = sqrt(
			      pow ( subdeltaRadius,2 ) + pow( subdeltaz,2 )
			      );

	float fillValue=subdelta/x0;

	//
	// Average length
	hmgr->getHisto2(999)->Fill(z,polarRadius,subdelta);
	// Total
	hmgr->getHisto1(41)->Fill(polarRadius);
	hmgr->getHistoProf1(40)->Fill(polarRadius,theTotalMB_TOT);
	hmgr->getHisto2(51)->Fill(z,polarRadius);
	hmgr->getHistoProf2(50)->Fill(z,polarRadius,theTotalMB_TOT);
	hmgr->getHisto2(61)->Fill(z,polarRadius);
	hmgr->getHisto2(60)->Fill(z,polarRadius,fillValue);
	// Copper
	hmgr->getHisto1(141)->Fill(polarRadius);
	hmgr->getHistoProf1(140)->Fill(polarRadius,theTotalMB_COP);
	hmgr->getHisto2(151)->Fill(z,polarRadius);
	hmgr->getHistoProf2(150)->Fill(z,polarRadius,theTotalMB_COP);
	hmgr->getHisto2(161)->Fill(z,polarRadius);
	hmgr->getHisto2(160)->Fill(z,polarRadius,iCop*fillValue);
	// H_Scintillator
	hmgr->getHisto1(241)->Fill(polarRadius);
	hmgr->getHistoProf1(240)->Fill(polarRadius,theTotalMB_SCI);
	hmgr->getHisto2(251)->Fill(z,polarRadius);
	hmgr->getHistoProf2(250)->Fill(z,polarRadius,theTotalMB_SCI);
	hmgr->getHisto2(261)->Fill(z,polarRadius);
	hmgr->getHisto2(260)->Fill(z,polarRadius,iSci*fillValue);
	// Cables
	hmgr->getHisto1(341)->Fill(polarRadius);
	hmgr->getHistoProf1(340)->Fill(polarRadius,theTotalMB_CAB);
	hmgr->getHisto2(351)->Fill(z,polarRadius);
	hmgr->getHistoProf2(350)->Fill(z,polarRadius,theTotalMB_CAB);
	hmgr->getHisto2(361)->Fill(z,polarRadius);
	hmgr->getHisto2(360)->Fill(z,polarRadius,iCab*fillValue);
	// M_NEMA_FR4_plate
	hmgr->getHisto1(441)->Fill(polarRadius);
	hmgr->getHistoProf1(440)->Fill(polarRadius,theTotalMB_MNE);
	hmgr->getHisto2(451)->Fill(z,polarRadius);
	hmgr->getHistoProf2(450)->Fill(z,polarRadius,theTotalMB_MNE);
	hmgr->getHisto2(461)->Fill(z,polarRadius);
	hmgr->getHisto2(460)->Fill(z,polarRadius,iMne*fillValue);
	// Silicon
	hmgr->getHisto1(541)->Fill(polarRadius);
	hmgr->getHistoProf1(540)->Fill(polarRadius,theTotalMB_NIM);
	hmgr->getHisto2(551)->Fill(z,polarRadius);
	hmgr->getHistoProf2(550)->Fill(z,polarRadius,theTotalMB_NIM);
	hmgr->getHisto2(561)->Fill(z,polarRadius);
	hmgr->getHisto2(560)->Fill(z,polarRadius,iSil*fillValue);
	// Other
	hmgr->getHisto1(641)->Fill(polarRadius);
	hmgr->getHistoProf1(640)->Fill(polarRadius,theTotalMB_OTH);
	hmgr->getHisto2(651)->Fill(z,polarRadius);
	hmgr->getHistoProf2(650)->Fill(z,polarRadius,theTotalMB_OTH);
	hmgr->getHisto2(661)->Fill(z,polarRadius);
	hmgr->getHisto2(660)->Fill(z,polarRadius,iOth*fillValue);
	// Air
	hmgr->getHisto1(741)->Fill(polarRadius);
	hmgr->getHistoProf1(740)->Fill(polarRadius,theTotalMB_AIR);
	hmgr->getHisto2(751)->Fill(z,polarRadius);
	hmgr->getHistoProf2(750)->Fill(z,polarRadius,theTotalMB_AIR);
	hmgr->getHisto2(761)->Fill(z,polarRadius);
	hmgr->getHisto2(760)->Fill(z,polarRadius,iAir*fillValue);
	// StainlessSteel
	hmgr->getHisto1(841)->Fill(polarRadius);
	hmgr->getHistoProf1(840)->Fill(polarRadius,theTotalMB_SST);
	hmgr->getHisto2(851)->Fill(z,polarRadius);
	hmgr->getHistoProf2(850)->Fill(z,polarRadius,theTotalMB_SST);
	hmgr->getHisto2(861)->Fill(z,polarRadius);
	hmgr->getHisto2(860)->Fill(z,polarRadius,iSst*fillValue);
	// WCu
	hmgr->getHisto1(941)->Fill(polarRadius);
	hmgr->getHistoProf1(940)->Fill(polarRadius,theTotalMB_WCU);
	hmgr->getHisto2(951)->Fill(z,polarRadius);
	hmgr->getHistoProf2(950)->Fill(z,polarRadius,theTotalMB_WCU);
	hmgr->getHisto2(961)->Fill(z,polarRadius);
	hmgr->getHisto2(960)->Fill(z,polarRadius,iWcu*fillValue);
	//
      }
    }
    //
    //
    ////////////////////////////////////////////////////////////////////////////////////////////
    //
    //
    //

    
    // Total Lambda0
    hmgr->getHisto1(1011)->Fill(theData->getEta());
    hmgr->getHisto1(1021)->Fill(theData->getPhi());
    hmgr->getHisto2(1031)->Fill(theData->getEta(),theData->getPhi());
    
    hmgr->getHistoProf1(1010)->Fill(theData->getEta(),theData->getTotalIL());
    hmgr->getHistoProf1(1020)->Fill(theData->getPhi(),theData->getTotalIL());
    hmgr->getHistoProf2(1030)->Fill(theData->getEta(),theData->getPhi(),theData->getTotalIL());
    
    // Copper
    hmgr->getHisto1(1111)->Fill(theData->getEta());
    hmgr->getHisto1(1121)->Fill(theData->getPhi());
    hmgr->getHisto2(1131)->Fill(theData->getEta(),theData->getPhi());
    
    hmgr->getHistoProf1(1110)->Fill(theData->getEta(),theData->getCopperIL());
    hmgr->getHistoProf1(1120)->Fill(theData->getPhi(),theData->getCopperIL());
    hmgr->getHistoProf2(1130)->Fill(theData->getEta(),theData->getPhi(),theData->getCopperIL());
    
    // H_Scintillator
    hmgr->getHisto1(1211)->Fill(theData->getEta());
    hmgr->getHisto1(1221)->Fill(theData->getPhi());
    hmgr->getHisto2(1231)->Fill(theData->getEta(),theData->getPhi());
    
    hmgr->getHistoProf1(1210)->Fill(theData->getEta(),theData->getH_ScintillatorIL());
    hmgr->getHistoProf1(1220)->Fill(theData->getPhi(),theData->getH_ScintillatorIL());
    hmgr->getHistoProf2(1230)->Fill(theData->getEta(),theData->getPhi(),theData->getH_ScintillatorIL());
    
    // Cables
    hmgr->getHisto1(1311)->Fill(theData->getEta());
    hmgr->getHisto1(1321)->Fill(theData->getPhi());
    hmgr->getHisto2(1331)->Fill(theData->getEta(),theData->getPhi());
    
    hmgr->getHistoProf1(1310)->Fill(theData->getEta(),theData->getCablesIL());
    hmgr->getHistoProf1(1320)->Fill(theData->getPhi(),theData->getCablesIL());
    hmgr->getHistoProf2(1330)->Fill(theData->getEta(),theData->getPhi(),theData->getCablesIL());
    
    // M_NEMA_FR4_plate
    hmgr->getHisto1(1411)->Fill(theData->getEta());
    hmgr->getHisto1(1421)->Fill(theData->getPhi());
    hmgr->getHisto2(1431)->Fill(theData->getEta(),theData->getPhi());
    
    hmgr->getHistoProf1(1410)->Fill(theData->getEta(),theData->getM_NEMA_FR4_plateIL());
    hmgr->getHistoProf1(1420)->Fill(theData->getPhi(),theData->getM_NEMA_FR4_plateIL());
    hmgr->getHistoProf2(1430)->Fill(theData->getEta(),theData->getPhi(),theData->getM_NEMA_FR4_plateIL());
    
    // Silicon
    hmgr->getHisto1(1511)->Fill(theData->getEta());
    hmgr->getHisto1(1521)->Fill(theData->getPhi());
    hmgr->getHisto2(1531)->Fill(theData->getEta(),theData->getPhi());
    
    hmgr->getHistoProf1(1510)->Fill(theData->getEta(),theData->getSiliconIL());
    hmgr->getHistoProf1(1520)->Fill(theData->getPhi(),theData->getSiliconIL());
    hmgr->getHistoProf2(1530)->Fill(theData->getEta(),theData->getPhi(),theData->getSiliconIL());
    
    // Other
    hmgr->getHisto1(1611)->Fill(theData->getEta());
    hmgr->getHisto1(1621)->Fill(theData->getPhi());
    hmgr->getHisto2(1631)->Fill(theData->getEta(),theData->getPhi());
    
    hmgr->getHistoProf1(1610)->Fill(theData->getEta(),theData->getOtherIL());
    hmgr->getHistoProf1(1620)->Fill(theData->getPhi(),theData->getOtherIL());
    hmgr->getHistoProf2(1630)->Fill(theData->getEta(),theData->getPhi(),theData->getOtherIL());
    
    // Air
    hmgr->getHisto1(1711)->Fill(theData->getEta());
    hmgr->getHisto1(1721)->Fill(theData->getPhi());
    hmgr->getHisto2(1731)->Fill(theData->getEta(),theData->getPhi());
    
    hmgr->getHistoProf1(1710)->Fill(theData->getEta(),theData->getAirIL());
    hmgr->getHistoProf1(1720)->Fill(theData->getPhi(),theData->getAirIL());
    hmgr->getHistoProf2(1730)->Fill(theData->getEta(),theData->getPhi(),theData->getAirIL());
    
    // StainlessSteel
    hmgr->getHisto1(1811)->Fill(theData->getEta());
    hmgr->getHisto1(1821)->Fill(theData->getPhi());
    hmgr->getHisto2(1831)->Fill(theData->getEta(),theData->getPhi());
    
    hmgr->getHistoProf1(1810)->Fill(theData->getEta(),theData->getStainlessSteelIL());
    hmgr->getHistoProf1(1820)->Fill(theData->getPhi(),theData->getStainlessSteelIL());
    hmgr->getHistoProf2(1830)->Fill(theData->getEta(),theData->getPhi(),theData->getStainlessSteelIL());

    // WCu
    hmgr->getHisto1(1911)->Fill(theData->getEta());
    hmgr->getHisto1(1921)->Fill(theData->getPhi());
    hmgr->getHisto2(1931)->Fill(theData->getEta(),theData->getPhi());
    
    hmgr->getHistoProf1(1910)->Fill(theData->getEta(),theData->getWCuIL());
    hmgr->getHistoProf1(1920)->Fill(theData->getPhi(),theData->getWCuIL());
    hmgr->getHistoProf2(1930)->Fill(theData->getEta(),theData->getPhi(),theData->getWCuIL());

    // Compute the total l/l0 crossed at each step radius for each path
    float theTotalIL_TOT = 0.0;
    float theTotalIL_COP = 0.0;
    float theTotalIL_SCI = 0.0;
    float theTotalIL_CAB = 0.0;
    float theTotalIL_MNE = 0.0;
    float theTotalIL_NIM = 0.0;
    float theTotalIL_OTH = 0.0;
    float theTotalIL_AIR = 0.0;
    float theTotalIL_SST = 0.0;
    float theTotalIL_WCU = 0.0;
    for(int iStep = 0; iStep < theData->getNumberOfSteps(); iStep++) {
      theTotalIL_TOT += theData->getStepDil(iStep);
      theTotalIL_COP += theData->getCopperDil(iStep);
      theTotalIL_SCI += theData->getH_ScintillatorDil(iStep);
      theTotalIL_CAB += theData->getCablesDil(iStep);
      theTotalIL_MNE += theData->getM_NEMA_FR4_plateDil(iStep);
      theTotalIL_NIM += theData->getSiliconDil(iStep);
      theTotalIL_OTH += theData->getOtherDil(iStep);
      theTotalIL_AIR += theData->getAirDil(iStep);
      theTotalIL_SST += theData->getStainlessSteelDil(iStep);
      theTotalIL_WCU += theData->getWCuDil(iStep);

      int iCop = 0;
      int iSci = 0;
      int iCab = 0;
      int iMne = 0;
      int iSil = 0;
      int iOth = 0;
      int iAir = 0;
      int iSst = 0;
      int iWcu = 0;

      if( theData->getCopperDil(iStep)>0.     ) { iCop = 1; }
      if( theData->getH_ScintillatorDil(iStep)>0.   ) { iSci = 1; }
      if( theData->getCablesDil(iStep)>0.      ) { iCab = 1; }
      if( theData->getM_NEMA_FR4_plateDil(iStep)>0.     ) { iMne = 1; }
      if( theData->getSiliconDil(iStep)>0. ) { iSil = 1; }
      if( theData->getOtherDil(iStep)>0.       ) { iOth = 1; }
      if( theData->getAirDil(iStep)>0.         ) { iAir = 1; }
      if( theData->getStainlessSteelDil(iStep)>0.         ) { iSst = 1; }
      if( theData->getWCuDil(iStep)>0.         ) { iWcu = 1; }

      float deltaRadius = sqrt(
			       pow( theData->getStepFinalX(iStep)-theData->getStepInitialX(iStep),2 )
			       +
			       pow( theData->getStepFinalY(iStep)-theData->getStepInitialY(iStep),2 )
			       );
      float deltaz = theData->getStepFinalZ(iStep)-theData->getStepInitialZ(iStep) ;
      
      float il = theData->getStepMaterialLambda0(iStep);

      int nSubStep = 2;
      float boxWidth = 0.1;
      if( (deltaRadius>boxWidth) || (fabs(deltaz)>boxWidth) ) {
	nSubStep = static_cast<int>(max(
		       ceil(deltaRadius/boxWidth/2.)*2,
		       ceil(fabs(deltaz)/boxWidth/2.)*2
		       ));
      }
      
      for(int iSubStep = 1; iSubStep < nSubStep; iSubStep+=2) {

	float subdeltaRadius = deltaRadius/nSubStep;
	float polarRadius = sqrt(
				 pow( theData->getStepInitialX(iStep),2 )
				 +
				 pow( theData->getStepInitialY(iStep),2 )
				 ) + iSubStep*subdeltaRadius;

	float subdeltaz = deltaz/nSubStep;
	float z = theData->getStepInitialZ(iStep) + iSubStep*subdeltaz;

	float subdelta = sqrt(
			      pow ( subdeltaRadius,2 ) + pow( subdeltaz,2 )
			      );

	float fillValue=subdelta/il;

	//
	// Average length
	hmgr->getHisto2(1999)->Fill(z,polarRadius,subdelta);
	// Total
	hmgr->getHisto1(1041)->Fill(polarRadius);
	hmgr->getHistoProf1(1040)->Fill(polarRadius,theTotalIL_TOT);
	hmgr->getHisto2(1051)->Fill(z,polarRadius);
	hmgr->getHistoProf2(1050)->Fill(z,polarRadius,theTotalIL_TOT);
	hmgr->getHisto2(1061)->Fill(z,polarRadius);
	hmgr->getHisto2(1060)->Fill(z,polarRadius,fillValue);
	// Copper
	hmgr->getHisto1(1141)->Fill(polarRadius);
	hmgr->getHistoProf1(1140)->Fill(polarRadius,theTotalIL_COP);
	hmgr->getHisto2(1151)->Fill(z,polarRadius);
	hmgr->getHistoProf2(1150)->Fill(z,polarRadius,theTotalIL_COP);
	hmgr->getHisto2(1161)->Fill(z,polarRadius);
	hmgr->getHisto2(1160)->Fill(z,polarRadius,iCop*fillValue);
	// H_Scintillator
	hmgr->getHisto1(1241)->Fill(polarRadius);
	hmgr->getHistoProf1(1240)->Fill(polarRadius,theTotalIL_SCI);
	hmgr->getHisto2(1251)->Fill(z,polarRadius);
	hmgr->getHistoProf2(1250)->Fill(z,polarRadius,theTotalIL_SCI);
	hmgr->getHisto2(1261)->Fill(z,polarRadius);
	hmgr->getHisto2(1260)->Fill(z,polarRadius,iSci*fillValue);
	// Cables
	hmgr->getHisto1(1341)->Fill(polarRadius);
	hmgr->getHistoProf1(1340)->Fill(polarRadius,theTotalIL_CAB);
	hmgr->getHisto2(1351)->Fill(z,polarRadius);
	hmgr->getHistoProf2(1350)->Fill(z,polarRadius,theTotalIL_CAB);
	hmgr->getHisto2(1361)->Fill(z,polarRadius);
	hmgr->getHisto2(1360)->Fill(z,polarRadius,iCab*fillValue);
	// M_NEMA_FR4_plate
	hmgr->getHisto1(1441)->Fill(polarRadius);
	hmgr->getHistoProf1(1440)->Fill(polarRadius,theTotalIL_MNE);
	hmgr->getHisto2(1451)->Fill(z,polarRadius);
	hmgr->getHistoProf2(1450)->Fill(z,polarRadius,theTotalIL_MNE);
	hmgr->getHisto2(1461)->Fill(z,polarRadius);
	hmgr->getHisto2(1460)->Fill(z,polarRadius,iMne*fillValue);
	// Silicon
	hmgr->getHisto1(1541)->Fill(polarRadius);
	hmgr->getHistoProf1(1540)->Fill(polarRadius,theTotalIL_NIM);
	hmgr->getHisto2(1551)->Fill(z,polarRadius);
	hmgr->getHistoProf2(1550)->Fill(z,polarRadius,theTotalIL_NIM);
	hmgr->getHisto2(1561)->Fill(z,polarRadius);
	hmgr->getHisto2(1560)->Fill(z,polarRadius,iSil*fillValue);
	// Other
	hmgr->getHisto1(1641)->Fill(polarRadius);
	hmgr->getHistoProf1(1640)->Fill(polarRadius,theTotalIL_OTH);
	hmgr->getHisto2(1651)->Fill(z,polarRadius);
	hmgr->getHistoProf2(1650)->Fill(z,polarRadius,theTotalIL_OTH);
	hmgr->getHisto2(1661)->Fill(z,polarRadius);
	hmgr->getHisto2(1660)->Fill(z,polarRadius,iOth*fillValue);
	// Air
	hmgr->getHisto1(1741)->Fill(polarRadius);
	hmgr->getHistoProf1(1740)->Fill(polarRadius,theTotalIL_AIR);
	hmgr->getHisto2(1751)->Fill(z,polarRadius);
	hmgr->getHistoProf2(1750)->Fill(z,polarRadius,theTotalIL_AIR);
	hmgr->getHisto2(1761)->Fill(z,polarRadius);
	hmgr->getHisto2(1760)->Fill(z,polarRadius,iAir*fillValue);
	// StainlessSteel
	hmgr->getHisto1(1841)->Fill(polarRadius);
	hmgr->getHistoProf1(1840)->Fill(polarRadius,theTotalIL_SST);
	hmgr->getHisto2(1851)->Fill(z,polarRadius);
	hmgr->getHistoProf2(1850)->Fill(z,polarRadius,theTotalIL_SST);
	hmgr->getHisto2(1861)->Fill(z,polarRadius);
	hmgr->getHisto2(1860)->Fill(z,polarRadius,iSst*fillValue);
	// WCu
	hmgr->getHisto1(1941)->Fill(polarRadius);
	hmgr->getHistoProf1(1940)->Fill(polarRadius,theTotalIL_WCU);
	hmgr->getHisto2(1951)->Fill(z,polarRadius);
	hmgr->getHistoProf2(1950)->Fill(z,polarRadius,theTotalIL_WCU);
	hmgr->getHisto2(1961)->Fill(z,polarRadius);
	hmgr->getHisto2(1960)->Fill(z,polarRadius,iWcu*fillValue);
	//
      }

    }
    
    // rr
  } else {
    std::cout << "*** WARNING This event is out of the acceptance *** " << std::endl;
    std::cout << "eta = "      << theData->getEta()
	      << "\t phi = "   << theData->getPhi()
	      << "\t x/X0 = "  << theData->getTotalMB()
	      << "\t l/l0 = "  << theData->getTotalIL()
	      << "\t steps = " << theData->getNumberOfSteps()
	      << std::endl;
    std::cout << "***" << std::endl;
  }

 
}

void MaterialBudgetHGCalHistos::hend() 
{

  hmgr->getHisto2(60)->Divide(hmgr->getHisto2(999));
  hmgr->getHisto2(160)->Divide(hmgr->getHisto2(999));
  hmgr->getHisto2(260)->Divide(hmgr->getHisto2(999));
  hmgr->getHisto2(360)->Divide(hmgr->getHisto2(999));
  hmgr->getHisto2(460)->Divide(hmgr->getHisto2(999));
  hmgr->getHisto2(560)->Divide(hmgr->getHisto2(999));
  hmgr->getHisto2(660)->Divide(hmgr->getHisto2(999));
  hmgr->getHisto2(760)->Divide(hmgr->getHisto2(999));
  hmgr->getHisto2(860)->Divide(hmgr->getHisto2(999));
  hmgr->getHisto2(960)->Divide(hmgr->getHisto2(999));

  hmgr->getHisto2(160)->Divide(hmgr->getHisto2(1999));
  hmgr->getHisto2(1160)->Divide(hmgr->getHisto2(1999));
  hmgr->getHisto2(1260)->Divide(hmgr->getHisto2(1999));
  hmgr->getHisto2(1360)->Divide(hmgr->getHisto2(1999));
  hmgr->getHisto2(1460)->Divide(hmgr->getHisto2(1999));
  hmgr->getHisto2(1560)->Divide(hmgr->getHisto2(1999));
  hmgr->getHisto2(1660)->Divide(hmgr->getHisto2(1999));
  hmgr->getHisto2(1760)->Divide(hmgr->getHisto2(1999));
  hmgr->getHisto2(1860)->Divide(hmgr->getHisto2(1999));
  hmgr->getHisto2(1960)->Divide(hmgr->getHisto2(1999));

  std::cout << "=== save user histos ===" << std::endl;
  hmgr->save( theFileName );

}


