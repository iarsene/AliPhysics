#ifndef ALIJETFILLUNITARRAYTRACKS_H
#define ALIJETFILLUNITARRAYTRACKS_H
 
/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */
 
//---------------------------------------------------------------------
// Jet Fill Unit Array 
// Called by ESD Reader for jet analysis
// Author: Magali Estienne (magali.estienne@subatech.in2p3.fr)
//---------------------------------------------------------------------

#ifndef ROOT_TTask
#include "TTask.h"
#endif

#include <TMatrixD.h>
#include <TArrayD.h>

class AliEMCALGeometry;
class AliJetDummyGeo;
class AliJetHadronCorrection;
class AliJetReader;
class AliJetESDReader;
class TClonesArray;
class TRefArray;
class AliJetGrid;
class AliEMCALGeometry;
class AliJetDummyGeo;
class AliESD;
class AliESDEvent;

class AliJetFillUnitArrayTracks : public TTask
{
 public: 
  AliJetFillUnitArrayTracks();
  AliJetFillUnitArrayTracks(AliESDEvent *fESD);
  virtual ~AliJetFillUnitArrayTracks();
  
  // Setter
  void          SetReaderHeader(AliJetReaderHeader *readerHeader) {fReaderHeader = readerHeader;}
  void          SetGeom(AliJetDummyGeo *geom) {fGeom = geom;}
  void          SetMomentumArray(TClonesArray *momentumArray) {fMomentumArray = momentumArray;}
  void          SetUnitArray(TClonesArray *unitArray) {fUnitArray = unitArray;}
  void          SetRefArray(TRefArray *refArray) {fRefArray = refArray;}
  void          SetHadCorrection(Int_t flag = 1) {fHCorrection = flag;}
  void          SetHadCorrector(AliJetHadronCorrectionv1* corr) {fHadCorr = corr;}
  void          SetTPCGrid(AliJetGrid *grid) {fTPCGrid = grid;}
  void          SetEMCalGrid(AliJetGrid *grid) {fEMCalGrid = grid;}
  void          SetGrid(Double_t phiMin,Double_t phiMax,Double_t etaMin,Double_t etaMax);
  void          SetESD(AliESDEvent *esd) {fESD = esd;}
  void          SetGrid0(AliJetGrid *grid0){fGrid0 = grid0;}
  void          SetGrid1(AliJetGrid *grid1){fGrid1 = grid1;}
  void          SetGrid2(AliJetGrid *grid2){fGrid2 = grid2;}
  void          SetGrid3(AliJetGrid *grid3){fGrid3 = grid3;}
  void          SetGrid4(AliJetGrid *grid4){fGrid4 = grid4;}
  void          SetProcId(Bool_t id) {fProcId = id;}
  Bool_t        GetProcId() {return fProcId;}

  // Getter
  TClonesArray* GetUnitArray() {return fUnitArray;}
  TRefArray*    GetRefArray() {return fRefArray;}
  void          GetEtaPhiFromIndex(Int_t index,Float_t &eta,Float_t &phi);
  Int_t         GetNeta() {return fNeta;}
  Int_t         GetNphi() {return fNphi;}
  Int_t         GetHadCorrection() {return fHCorrection;}
  Int_t         GetMult() {return fNTracks;}
  Int_t         GetMultCut() {return fNTracksCut;}
  void          Exec(Option_t*);

 protected:
  Int_t                       fNumUnits;        // Number of units in the unit object array (same as num towers in EMCAL)
  Float_t                     fEtaMinCal;       // Define EMCal acceptance in Eta
  Float_t                     fEtaMaxCal;       // Define EMCal acceptance in Eta
  Float_t                     fPhiMinCal;       // Define EMCal acceptance in Phi
  Float_t                     fPhiMaxCal;       // Define EMCal acceptance in Phi
  AliJetHadronCorrectionv1   *fHadCorr;         // Pointer to Hadron Correction Object
  Int_t                       fHCorrection;     // Hadron correction flag
  Int_t                       fNTracks;         // Number of tracks stored in UnitArray
  Int_t                       fNTracksCut;      // Number of tracks stored in UnitArray with a pt cut 
  Int_t                       fOpt;             // Detector to be used for jet reconstruction
  Bool_t                      fDZ;              // Use or not dead zones
  Int_t                       fDebug;           // Debug option

  AliJetReaderHeader          *fReaderHeader;   // ReaderHeader
  TClonesArray                *fMomentumArray;  // MomentumArray
  TClonesArray                *fUnitArray;      // UnitArray
  TRefArray                   *fRefArray;       // UnitArray
  Bool_t                      fProcId;          // Bool_t for TProcessID synchronization  
  AliJetGrid                  *fTPCGrid;        // Define filled grid
  AliJetGrid                  *fEMCalGrid;      // Define filled grid
  AliJetDummyGeo              *fGeom;           // Define EMCal geometry
  AliESDEvent                 *fESD;            // ESD
  AliJetGrid                  *fGrid0;          // Grid used for dead zones definition
  AliJetGrid                  *fGrid1;          // Grid used for dead zones definition
  AliJetGrid                  *fGrid2;          // Grid used for dead zones definition
  AliJetGrid                  *fGrid3;          // Grid used for dead zones definition
  AliJetGrid                  *fGrid4;          // Grid used for dead zones definition

  Int_t                        fNphi;           // number of points in the grid:   phi
  Int_t                        fNeta;           //               "                 eta
  TArrayD                     *fPhi2;           // grid points in phi
  TArrayD                     *fEta2;           // grid points in eta
  TArrayD                     *fPhi;            // grid points in phi
  TArrayD                     *fEta;            // grid points in eta
  TMatrixD                    *fIndex;          // grid points in (phi,eta) 
  TMatrixD                    *fParams;         // matrix of parameters in the grid points  
  Int_t                        fGrid;           // Select the grid acceptance you want to fill
                                                // 0 = TPC acceptance, 1 = TPC-EMCal acceptance
  Float_t                      fPhiMin;
  Float_t                      fPhiMax;
  Float_t                      fEtaMin;
  Float_t                      fEtaMax;
  Int_t                        fEtaBinInTPCAcc;
  Int_t                        fPhiBinInTPCAcc;
  Int_t                        fEtaBinInEMCalAcc;
  Int_t                        fPhiBinInEMCalAcc;
  Int_t                        fNbinPhi;

 private:
  AliJetFillUnitArrayTracks(const AliJetFillUnitArrayTracks &det);
  AliJetFillUnitArrayTracks &operator=(const AliJetFillUnitArrayTracks &det);
  void InitParameters();

  ClassDef(AliJetFillUnitArrayTracks,1) // Fill Unit Array with tpc and/or emcal information
};

#endif
