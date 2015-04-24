// -*- C++ -*-
//
// Package:    CastorL1Valid/CastorMkL1TestTree
// Class:      CastorMkL1TestTree
// 
/**\class CastorMkL1TestTree CastorMkL1TestTree.cc CastorL1Valid/CastorMkL1TestTree/plugins/CastorMkL1TestTree.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Clemens Wohrmann
//         Created:  Fri, 24 Apr 2015 09:27:01 GMT
//
//

// system include files
#include <memory>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <bitset>
#include <string>

// include root files
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TClonesArray.h"


// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

// include tracks
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

// include vertices
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

// include electrons
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"

// include HF electrons
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidateFwd.h"

// HCAL & ECAL RecHit
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"

// HCAL Towers
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"

// include castorrechits
#include "DataFormats/HcalRecHit/interface/CastorRecHit.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"

// include castortowers
#include "DataFormats/CastorReco/interface/CastorTower.h"

// include castorjets
#include "DataFormats/JetReco/interface/BasicJet.h"
#include "DataFormats/JetReco/interface/CastorJetID.h"
#include "DataFormats/Common/interface/ValueMap.h"

// include ZDC digis
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalRecHit/interface/ZDCRecHit.h"

// include digi converter
#include "CalibFormats/HcalObjects/interface/HcalCoderDb.h"
#include "CalibFormats/HcalObjects/interface/HcalDbService.h"
#include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"

// include MET
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/PFMETFwd.h"

// include GenParticles
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"

// include SimVertices
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"

// geometry
#include "Geometry/CaloTopology/interface/HcalTopology.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"

// HLT Trigger
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "FWCore/Common/interface/TriggerNames.h"

// L1 Trigger DataFormats
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"
//#include "L1Trigger/GlobalTrigger/interface/L1GlobalTrigger.h"

// Pileup Information
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMask.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMaskAlgoTrigRcd.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMaskTechTrigRcd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerRecord.h"


// include cmssw-lorentzvector (is pointing over typedef's to root TLorentzVector)
#include "DataFormats/Candidate/interface/LeafCandidate.h"

//
// class declaration
//

class CastorMkL1TestTree : public edm::EDAnalyzer {
   public:
      explicit CastorMkL1TestTree(const edm::ParameterSet&);
      ~CastorMkL1TestTree();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // --------- user functions ------------------------
      void GetParameterSet(const edm::ParameterSet& iConfig);
      bool GetCollections(const edm::Event& iEvent);
      bool GetGeometry(const edm::EventSetup& iSetup);

      void GetL1TTriggerInfo(const edm::Event&, const edm::EventSetup&);
      int  GetPileUp(edm::Handle< std::vector<PileupSummaryInfo> >& vPU);

      // ----------member data ---------------------------
      const CaloGeometry * geo;
      L1GtUtils m_l1GtUtils;
      HLTConfigProvider hltConfig;

      // --------- flags ---------------------------------
      bool show_trigger_menu;

      // --------- input labels for collections ----------
      edm::InputTag PileUpInfo_;

      edm::InputTag GenPartColl_;
      edm::InputTag GenJetColl_;

      edm::InputTag CasRecHitColl_;
      edm::InputTag BasicJetColl_;
      edm::InputTag CastorJetID_;

      edm::InputTag TrigResults_;
      edm::InputTag VertexColl_;

      // --------- collection handel ---------------------
      edm::Handle< std::vector<PileupSummaryInfo> > PileUpInfo;

      edm::Handle< reco::GenParticleCollection >    GenPartColl;
      edm::Handle< reco::GenJetCollection >         GenJetColl;

      edm::Handle< CastorRecHitCollection >         CasRecHitColl;
      edm::Handle< std::vector<reco::BasicJet> >    BasicJetView;
      edm::Handle< reco::CastorJetIDValueMap >      CasJetIdMap;

      edm::Handle< edm::TriggerResults >            TrigResults;
      edm::Handle<reco::VertexCollection>           VertexColl;

      // --------- tree variables ------------------------
      TTree* myTree;

      static const int max_genpart_size  = 5000;
      static const int max_jet_size      = 100;
      static const int max_vtx_size      = 50;
      int num_pu_vtx;

      TClonesArray* fspart;
      TClonesArray* genjet;
      TClonesArray* casjet;
      TClonesArray* vertex;
      int fspart_size;
      int genjet_size;
      int casjet_size;
      int vertex_size;

      double cas_energy[16][14];
      int fspart_id[max_genpart_size];
      int vtx_ndof[max_vtx_size];
      int vtx_fake[max_vtx_size];
      int totem_mpl[2]; // [0] -> posetive side; [1] -> negative side


      ULong64_t CastorL1DecisionWord;
      ULong64_t AlgoJetDecisionWord1;
      ULong64_t AlgoJetDecisionWord2;
      ULong64_t HLTDecisionWord;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
CastorMkL1TestTree::CastorMkL1TestTree(const edm::ParameterSet& iConfig)

{
  //now do what ever initialization is needed
  GetParameterSet(iConfig);

  edm::Service<TFileService> fs;

  myTree = fs->make<TTree>("myTree","myTree");

  fspart = new TClonesArray("TLorentzVector", max_genpart_size );
  genjet = new TClonesArray("TLorentzVector", max_jet_size );
  casjet = new TClonesArray("TLorentzVector", max_jet_size );
  vertex = new TClonesArray("TVector3" , max_vtx_size );

  myTree->Branch("num_pu_vtx" , &num_pu_vtx , "num_pu_vtx/I");

  myTree->Branch("fspart", "TClonesArray" , &fspart , 32000, 0);
  myTree->Branch("genjet", "TClonesArray" , &genjet , 32000, 0);
  myTree->Branch("casjet", "TClonesArray" , &casjet , 32000, 0);
  myTree->Branch("vertex", "TClonesArray" , &vertex , 32000, 0);
  myTree->Branch("fspart_size" , &fspart_size , "fspart_size/I");
  myTree->Branch("genjet_size" , &genjet_size , "genjet_size/I");
  myTree->Branch("casjet_size" , &casjet_size , "casjet_size/I");
  myTree->Branch("vertex_size" , &vertex_size , "vertex_size/I");
  myTree->Branch("cas_energy" , &cas_energy , "cas_energy[16][14]/D");
  myTree->Branch("fspart_id" , &fspart_id , "fspart_id[fspart_size]/I");
  myTree->Branch("vtx_ndof" , &vtx_ndof , "vtx_ndof[vertex_size]/I");
  myTree->Branch("vtx_fake" , &vtx_fake , "vtx_fake[vertex_size]/I");
  myTree->Branch("totem_mpl" , &totem_mpl , "totem_mpl[2]/I");
  
  myTree->Branch("CastorL1DecisionWord" , &CastorL1DecisionWord , "CastorL1DecisionWord/l");
  myTree->Branch("AlgoJetDecisionWord1" , &AlgoJetDecisionWord1 , "AlgoJetDecisionWord1/l");
  myTree->Branch("AlgoJetDecisionWord2" , &AlgoJetDecisionWord2 , "AlgoJetDecisionWord2/l");
  myTree->Branch("HLTDecisionWord" , &HLTDecisionWord , "HLTDecisionWord/l");
}


CastorMkL1TestTree::~CastorMkL1TestTree()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
CastorMkL1TestTree::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

     using namespace edm;

  num_pu_vtx = 0;

  fspart->Clear();
  genjet->Clear();
  casjet->Clear();
  vertex->Clear();

  fspart_size = 0;
  genjet_size = 0;  
  casjet_size = 0;
  vertex_size = 0;

  // Get all necessary collections
  if( !GetCollections(iEvent) ) return;
  
  num_pu_vtx = GetPileUp(PileUpInfo);
  
  totem_mpl[0] = 0; totem_mpl[1] = 0;

  // GenParticles
  for(size_t i=0; i < GenPartColl->size(); i++)
    {
      const reco::GenParticle & genpart = (*GenPartColl)[i];
  
      if( genpart.status() != 1 )
        continue;

      // only t2 acceptance
      if( std::abs(genpart.eta()) > 5.4 && std::abs(genpart.eta()) < 6.6 &&
          genpart.charge() != 0 )
      {
        if( genpart.eta() > 0 ) totem_mpl[0]++;
        else totem_mpl[1]++;
      }

      // if( std::abs(genpart.pdgId()) != 13 )
      //   continue;

      TVector3 gp_mom(genpart.px(), genpart.py(), genpart.pz());
      double gp_m = genpart.mass();

      TLorentzVector lvgenpart; lvgenpart.SetVectM( gp_mom, gp_m );

      if( fspart_size < max_genpart_size ) {
        new((*fspart)[fspart_size]) TLorentzVector(lvgenpart);
        fspart_id[fspart_size] = genpart.pdgId();
      }

      fspart_size++;
    }


  for(size_t i=0; i < GenJetColl->size(); i++)
  {
    const reco::GenJet & jet = (*GenJetColl)[i];

    TLorentzVector lvjet( jet.px(), jet.py(), jet.pz(), jet.energy() );

    if( genjet_size < max_jet_size ) new((*genjet)[genjet_size]) TLorentzVector(lvjet);
    genjet_size++;
  }

  // Get CastorRecHits
  for (size_t i = 0; i < CasRecHitColl->size(); i++)
    {
      const CastorRecHit & rh = (*CasRecHitColl)[i];
      int isec = rh.id().sector()-1;
      int imod = rh.id().module()-1;
      cas_energy[isec][imod] = rh.energy();
    }

  // Get CastorJets
  for(size_t i = 0; i < BasicJetView->size(); i++)
    {
      const reco::BasicJet & basicjet = (*BasicJetView)[i];
      // edm::RefToBase<reco::BasicJet> jetRef = BasicJetView->refAt(i);
      // reco::CastorJetID const & jetId = (*CasJetIdMap)[jetRef];

      TLorentzVector lvjet( basicjet.px(), basicjet.py(), basicjet.pz(), basicjet.energy() );
      
      if( casjet_size < max_jet_size ) new((*casjet)[casjet_size]) TLorentzVector(lvjet);
      casjet_size++;
    }

  
  CastorL1DecisionWord = 0;
  AlgoJetDecisionWord1 = 0;
  AlgoJetDecisionWord2 = 0;
  HLTDecisionWord = 0;
  GetL1TTriggerInfo(iEvent,iSetup);
  
  // Get Vertices
  for(size_t i = 0; i < VertexColl->size(); i++)
    {
      const reco::Vertex & vtx = (*VertexColl)[i];

      //if( !vtx.isValid() || vtx.isFake() ) continue;

      TVector3 vVtx( vtx.x(), vtx.y(), vtx.z() );

      if( vertex_size < max_vtx_size ) {
        new((*vertex)[vertex_size]) TVector3(vVtx);
        vtx_ndof[vertex_size] = vtx.ndof();
        vtx_fake[vertex_size] = vtx.isFake() ? 1 : 0;
        vtx_fake[vertex_size] += vtx.isValid() ? 2 : 0;
      }
      vertex_size++;
    }

  myTree->Fill();
}

// ------------ methods to get detector collections --------------------------------------
void
CastorMkL1TestTree::GetParameterSet(const edm::ParameterSet& iConfig)
{
  // get flags
  show_trigger_menu = iConfig.getParameter<bool>("ShowTriggerMenu");

  // define collections
  PileUpInfo_       = iConfig.getParameter<edm::InputTag>("PileUpInfo");

  GenPartColl_      = iConfig.getParameter<edm::InputTag>("GenPartColl");
  GenJetColl_       = iConfig.getParameter<edm::InputTag>("GenJetColl");

  BasicJetColl_     = iConfig.getParameter<edm::InputTag>("BasicJetColl");
  CastorJetID_      = iConfig.getParameter<edm::InputTag>("CastorJetID");
  CasRecHitColl_    = iConfig.getParameter<edm::InputTag>("CasRecHitColl");

  TrigResults_      = iConfig.getParameter<edm::InputTag>("TrigResults");
  VertexColl_       = iConfig.getParameter<edm::InputTag>("VertexColl");
}

bool 
CastorMkL1TestTree::GetCollections(const edm::Event& iEvent)
{

  // ******************************** Pilup Information ************************************
  try{ iEvent.getByLabel(PileUpInfo_, PileUpInfo); }
  catch(...) { edm::LogWarning(" PileUpInfo ") << " Cannot get PileUpInfo " << std::endl; }
  
  if( !PileUpInfo.isValid() || PileUpInfo.failedToGet() ) {
    edm::LogWarning(" PileUpInfo ") << " Cannot read PileUpInfo " << std::endl;
    return false;
  }


  // ******************************** GEN Particles ************************************ 
  try{ iEvent.getByLabel(GenPartColl_, GenPartColl); }
  catch(...) { edm::LogWarning(" GenParticle ") << " Cannot get GenParticles " << std::endl; }
  
  if( !GenPartColl.isValid() || GenPartColl.failedToGet() ) {
    edm::LogWarning(" GenParticle ") << " Cannot read GenParticles " << std::endl;
    return false;
  }

  // ******************************** GEN Jets ************************************
  try{ iEvent.getByLabel(GenJetColl_, GenJetColl); }
  catch(...) { edm::LogWarning(" GenJet ") << " Cannot get GenJet" << std::endl; }
  
  if( !GenJetColl.isValid() || GenJetColl.failedToGet() ) {
    edm::LogWarning(" GenJet ") << " Cannot read GenJet " << std::endl;
    return false;
  }
  
  // ******************************** CASTOR RecHits *********************************
  try{ iEvent.getByLabel(CasRecHitColl_, CasRecHitColl); }
  catch(...) { edm::LogWarning(" CasRecHitColl ") << " Cannot get CastorRecHitsColl " << std::endl;  }

  if( !CasRecHitColl.isValid() || CasRecHitColl.failedToGet() ) {
    edm::LogWarning(" CasRecHitColl ") << " Cannot read CasRecHitColl " << std::endl;
    return false;
  }
  
  // ******************************** CASTOR Jets ************************************
  try{ iEvent.getByLabel(BasicJetColl_, BasicJetView); }
  catch(...) { edm::LogWarning(" BasicJet ") << " Cannot get BasicJet " << std::endl;  }

  if( !BasicJetView.isValid() || BasicJetView.failedToGet() ) {
    edm::LogWarning(" BasicJet ") << " Cannot read BasicJet " << std::endl;
    return false;
  }

  try{ iEvent.getByLabel(CastorJetID_, CasJetIdMap); }
  catch(...) { edm::LogWarning(" CastorJet ") << " Cannot get CastorJet " << std::endl;  }

  if( !CasJetIdMap.isValid() || CasJetIdMap.failedToGet() ) {
    edm::LogWarning(" CastorJet ") << " Cannot read CastorJet " << std::endl;
    return false;
  }
  
  // *********************************** Trigger ************************************
  try{ iEvent.getByLabel(TrigResults_, TrigResults); }
  catch(...) { edm::LogWarning(" TrigResults ") << " Cannot get TriggerResults " << std::endl;  }
  if( !TrigResults.isValid() || TrigResults.failedToGet() ) {
    edm::LogWarning(" TrigResults ") << " Cannot read TriggerResults " << std::endl;
    return false;
  }
  
  // ******************************** Vertices ***************************************
  try { iEvent.getByLabel(VertexColl_, VertexColl); }
  catch(...) { edm::LogWarning(" VertexColl ") << " Cannot get VERTICES " << std::endl; }

  if( !VertexColl.isValid() || VertexColl.failedToGet() ) {
    edm::LogWarning(" VertexColl ") << " Cannot read VERTICES " << std::endl;
    return false;
  }

  return true;
}

// ------------ method to get detector geometry -----------------------------------------
bool
CastorMkL1TestTree::GetGeometry(const edm::EventSetup& iSetup)
{
  edm::ESHandle<CaloGeometry> pG;

  try { iSetup.get<CaloGeometryRecord>().get(pG); }
  catch(...) { edm::LogWarning("GEOMETRY ") << " Cannot get CaloGeometryRecord " << std::endl; }
  
  if ( !pG.isValid() ) {
    edm::LogWarning("GEOMETRY ") << " CaloGeometryRecord is not VALID " << std::endl;
    geo = NULL;
    return false;
  }
  
  geo = pG.product();
  return true;
}

void 
CastorMkL1TestTree::GetL1TTriggerInfo(const edm::Event& iEvent, const edm::EventSetup& iConfig)
{
  std::map<int,std::string> L1TT_Menu;
  std::map<int,std::string> L1Algo_Menu;
  std::map<int,std::string> HLT_Menu;
 
  std::bitset<64> CastorL1Bits, AlgoJetBits_lowRange, AlgoJetBits_upperRange, HLTBits;

  bool useL1EventSetup = true;
  bool useL1GtTriggerMenuLite = true;

  m_l1GtUtils.getL1GtRunCache(iEvent, iConfig, useL1EventSetup, useL1GtTriggerMenuLite);

  int iErrorCode = -1;
  int l1ConfCode = -1;
  const bool l1Conf = m_l1GtUtils.availableL1Configuration(iErrorCode, l1ConfCode);
  if( !l1Conf ) { std::cerr << " (*W*) No valid L1 trigger configuration; code: " << l1Conf << std::endl; }

  const L1GtTriggerMenu* m_l1GtMenu          = m_l1GtUtils.ptrL1TriggerMenuEventSetup(iErrorCode);
  const AlgorithmMap&    algorithmMap        = m_l1GtMenu->gtAlgorithmMap();
  const AlgorithmMap&    technicalTriggerMap = m_l1GtMenu->gtTechnicalTriggerMap();
  // const std::string&     menuName     = m_l1GtMenu->gtTriggerMenuName();

  for(CItAlgo itAlgo = algorithmMap.begin(); itAlgo != algorithmMap.end(); itAlgo++) {
    std::string algName      = itAlgo->first;
    int algoBitNumber         = ( itAlgo->second ).algoBitNumber();
    // bool algResultBeforeMask = m_l1GtUtils.decisionBeforeMask(iEvent, itAlgo->first, iErrorCode);
    // bool algResultAfterMask  = m_l1GtUtils.decisionAfterMask (iEvent, itAlgo->first, iErrorCode);
    // int  triggerMask         = m_l1GtUtils.triggerMask       (iEvent, itAlgo->first, iErrorCode);
    bool decision            = m_l1GtUtils.decision          (iEvent, itAlgo->first, iErrorCode); //function identical with decisionAfterMask
    // int  preScale            = m_l1GtUtils.prescaleFactor    (iEvent, itAlgo->first, iErrorCode);
    // if (iErrorCode == 0 && decisionMaskAlgTechTrig)

    if( show_trigger_menu ) {
      L1Algo_Menu[algoBitNumber] = algName;
    }

    if( algoBitNumber < 64 ) AlgoJetBits_lowRange[algoBitNumber] = decision;
    else AlgoJetBits_upperRange[algoBitNumber-64] = decision;
  }


  for (CItAlgo itAlgo = technicalTriggerMap.begin(); itAlgo != technicalTriggerMap.end(); itAlgo++) {
    std::string algName      = itAlgo->first;
    int algoBitNumber         = ( itAlgo->second ).algoBitNumber();
    // bool algResultBeforeMask = m_l1GtUtils.decisionBeforeMask(iEvent, itAlgo->first, iErrorCode);
    // bool algResultAfterMask  = m_l1GtUtils.decisionAfterMask (iEvent, itAlgo->first, iErrorCode);
    // int  triggerMask         = m_l1GtUtils.triggerMask       (iEvent, itAlgo->first, iErrorCode);
    bool decision            = m_l1GtUtils.decision          (iEvent, itAlgo->first, iErrorCode);
    // int  preScale            = m_l1GtUtils.prescaleFactor    (iEvent, itAlgo->first, iErrorCode);

    if( show_trigger_menu ) {
      L1TT_Menu[algoBitNumber] = algName;
    }

    CastorL1Bits[algoBitNumber] = decision;
  }
  

  bool changedConfig = false;
  // int triggerBits[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
  if (!hltConfig.init(iEvent.getRun(), iConfig, "HLT", changedConfig)) {
    std::cerr << "*** (HLT) Initialization of HLTConfigProvider failed!!" << std::endl;
    return;
  }
  for (size_t j = 0; j < hltConfig.triggerNames().size(); j++) {
    // if (TString(hltConfig.triggerNames()[j]).Contains("HLT_L1Tech61_CASTORJet_v1") ) 
    //   triggerBits[0] = j;
    // else if( TString(hltConfig.triggerNames()[j]).Contains("HLT_L1Tech62_CASTORJet_SinglePFJet15_v1") )
    //   triggerBits[1] = j;
    // else if( TString(hltConfig.triggerNames()[j]).Contains("HLT_L1Tech62_CASTORJet_SinglePFJet40_v1") )
    //   triggerBits[2] = j;
    // else if( TString(hltConfig.triggerNames()[j]).Contains("HLT_L1Tech62_CASTORJet_SingleMuon5_v1") )
    //   triggerBits[3] = j;
    // else if( TString(hltConfig.triggerNames()[j]).Contains("HLT_L1Tech62_CASTORJet_SingleMuon10_v1") )
    //   triggerBits[4] = j;
    // else if( TString(hltConfig.triggerNames()[j]).Contains("HLT_L1Tech60_CASTORGap_IsoMu5_v1") )
    //   triggerBits[5] = j;
    // else if( TString(hltConfig.triggerNames()[j]).Contains("HLT_L1Tech62_CASTORGap_SingleMuon5_v1") )
    //   triggerBits[6] = j;

    if( show_trigger_menu ) {
      HLT_Menu[j] = std::string(hltConfig.triggerNames()[j]);
    }
  }
  // for(int i = 0; i < 7; i++) {
  //   if( triggerBits[i] == -1 ) {
  //     std::cerr << "*** (HLT) HLT path not found" << std::endl;
  //     return;
  //   }
  // }
  // else {
  //   // std::cout << "HLT Bit : " << triggerBits[0] << " and " << triggerBits[1] << std::endl;
  //   // std::cout << "TrigResults size : " << TrigResults->size() << std::endl;
  //   // std::cout << "Decision: " << TrigResults->accept(triggerBits[0]) << " and " << TrigResults->accept(triggerBits[1]) << std::endl;
  // }
  // HLTBits[0] = TrigResults->accept(triggerBits[0]);  // HLT_L1Tech61_CASTORJet_v1
  // HLTBits[1] = TrigResults->accept(triggerBits[1]);  // HLT_L1Tech61_CASTORJet_SinglePFJet20_v1
  // HLTBits[2] = TrigResults->accept(triggerBits[2]);  // HLT_L1Tech62_CASTORJet_SinglePFJet40_v1
  // HLTBits[3] = TrigResults->accept(triggerBits[3]);  // HLT_L1Tech62_CASTORJet_SingleMuon5_v1
  // HLTBits[4] = TrigResults->accept(triggerBits[4]);  // HLT_L1Tech62_CASTORJet_SingleMuon10_v1
  // HLTBits[5] = TrigResults->accept(triggerBits[5]);  // HLT_L1Tech60_CASTORGap_IsoMu5_v1
  // HLTBits[6] = TrigResults->accept(triggerBits[6]);  // HLT_L1Tech60_CASTORGap_SingleMuon5_v1

  
  CastorL1DecisionWord = (ULong64_t)CastorL1Bits.to_ulong();
  AlgoJetDecisionWord1 = (ULong64_t)AlgoJetBits_lowRange.to_ulong();
  AlgoJetDecisionWord2 = (ULong64_t)AlgoJetBits_upperRange.to_ulong();
  HLTDecisionWord      = (ULong64_t)HLTBits.to_ulong(); 

  if( show_trigger_menu ) {
    std::cout << "*** L1 TechnicalTrigger Menu ***" << std::endl;
    for(std::map<int,std::string>::iterator it = L1TT_Menu.begin(); it != L1TT_Menu.end(); it++)
      std::cout << "   *** L1 TT Bit[" << it->first << "] = " << it->second << std::endl;

    std::cout << "*** L1 Algorith Menu ***" << std::endl;
    for(std::map<int,std::string>::iterator it = L1Algo_Menu.begin(); it != L1Algo_Menu.end(); it++)
      std::cout << "   *** L1 Algo Bit[" << it->first << "] = " << it->second << std::endl;    

    std::cout << "*** HLT Menu ***" << std::endl;
    for(std::map<int,std::string>::iterator it = HLT_Menu.begin(); it != HLT_Menu.end(); it++)
      std::cout << "   *** HLT Bit[" << it->first << "] = " << it->second << std::endl;        

    show_trigger_menu = false;
  }
}

int
CastorMkL1TestTree::GetPileUp(edm::Handle< std::vector<PileupSummaryInfo> >& vPU)
{
  for(unsigned int i=0; i<vPU->size(); i++)
  {
    // gives you number of events which were additionally added to this event
    if( vPU->at(i).getBunchCrossing() == 0 ) return vPU->at(i).getPU_NumInteractions();
  }

  return -1;
}

// ------------ method called once each job just before starting event loop  ------------
void 
CastorMkL1TestTree::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
CastorMkL1TestTree::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
CastorMkL1TestTree::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
CastorMkL1TestTree::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
CastorMkL1TestTree::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
CastorMkL1TestTree::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
CastorMkL1TestTree::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(CastorMkL1TestTree);