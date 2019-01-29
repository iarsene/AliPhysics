#ifndef AliAnalysisTaskSpherocity_H
#define AliAnalysisTaskSpherocity_H
/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice */
/* $Id$ */


// ROOT includes
#include <TList.h>
#include <TH1.h>
#include <TProfile.h>
#include <TTreeStream.h>
#include <TRandom.h>
#include <TObject.h>

// AliRoot includes
#include <AliAnalysisTaskSE.h>
#include <AliESDEvent.h>
#include <AliAODEvent.h>
#include <AliMCEvent.h>
#include <AliAnalysisFilter.h>
#include <AliStack.h>
#include <AliGenEventHeader.h>
#include <AliVHeader.h>
#include <AliAODMCParticle.h> 
#include <AliESDtrackCuts.h>
#include <AliPIDResponse.h>
#include "AliTPCPIDResponse.h"
#include <AliSpherocityUtils.h>
#include <AliEventCuts.h>
#include "AliVTrack.h"



class AliAnalysisTaskSpherocity : public AliAnalysisTaskSE
{
public:


		AliAnalysisTaskSpherocity();
		AliAnalysisTaskSpherocity(const char *name);
		virtual ~AliAnalysisTaskSpherocity();

		virtual void   UserCreateOutputObjects();
		virtual void   UserExec(Option_t *option);

		Bool_t   GetAnalysisMC() { return fAnalysisMC; }   
		Double_t GetEtaCut() { return fEtaCut; }     

		virtual void  SetTrackFilterGolden(AliAnalysisFilter* trackF) {fTrackFilterGolden = trackF;}
		virtual void  SetTrackFilterTPC(AliAnalysisFilter* trackF) {fTrackFilterTPC = trackF;}
		virtual void  SetTrackFilter2015PbPb(AliAnalysisFilter* trackF) {fTrackFilter2015PbPb = trackF;}
		virtual void  SetTrackCutsSpherocity(AliAnalysisFilter* fTrackFilter);
		virtual void  SetAnalysisType(const char* analysisType) {fAnalysisType = analysisType;}
		virtual void  SetAnalysisMC(Bool_t isMC) {fAnalysisMC = isMC;}
		virtual void  SetNcl(const Int_t ncl){fNcl = ncl;}
		virtual void  SetEtaCut(Double_t etaCut){fEtaCut = etaCut;}
		virtual void  SetMinCent(Float_t minvalc) {fMinCent = minvalc;}
		virtual void  SetMaxCent(Float_t maxvalc) {fMaxCent = maxvalc;}
		virtual void  SetAnalysisPbPb(Bool_t isanaPbPb) { fAnalysisPbPb = isanaPbPb; }
		virtual void  SetAnalysisTask(Bool_t PostCalib) { fdEdxCalibrated = PostCalib; }
		virtual void  SetAnalysisPID(Bool_t makePid) { fMakePid = makePid; }
		virtual void  SetAddLowPt(Bool_t addlowpt) { fLowPt = addlowpt; }
		virtual void  SetPeriod(Int_t isLHC16l) { fLHC16l = isLHC16l; }

	private:
//		virtual Float_t GetVertex(const AliVEvent* event) const;
//		virtual void AnalyzeESD(AliESDEvent* esd); 
		virtual void ProduceArrayTrksESD(AliESDEvent* event, const Int_t cent, const Int_t sperocity);
		virtual void ProduceArrayV0ESD(AliESDEvent* event, const Int_t cent, const Int_t sperocity );
		Short_t   GetPidCode(Int_t pdgCode) const;
		void      ProcessMCTruthESD( const Int_t cent );

		Short_t   GetPythiaEventProcessType(Int_t pythiaType);
		Short_t   GetDPMjetEventProcessType(Int_t dpmJetType);
		ULong64_t GetEventIdAsLong(AliVHeader* header) const;

		TParticle* FindPrimaryMother(AliStack* stack, Int_t label);
		Int_t      FindPrimaryMotherLabel(AliStack* stack, Int_t label);


		TParticle* FindPrimaryMotherV0(AliStack* stack, Int_t label);
		Int_t      FindPrimaryMotherLabelV0(AliStack* stack, Int_t label, Int_t& nSteps);
		Bool_t selectVertex2015pp(AliESDEvent* esd, Bool_t checkSPDres, Bool_t requireSPDandTrk, Bool_t checkProximity);
		Bool_t IsGoodSPDvertexRes(const AliESDVertex* spdVertex = NULL);
		Bool_t IsGoodZvertexPos(AliESDEvent *esd);
		Bool_t PhiCut(Double_t pt, Double_t phi, Double_t q, Float_t   mag, TF1* phiCutLow, TF1* phiCutHigh);
		Float_t GetMaxDCApTDep(TF1* fcut, Double_t pt );
		Double_t EtaCalibrationNeg(const Int_t centrality, const Double_t Eta);
		Double_t EtaCalibrationPos(const Int_t centrality, const Double_t Eta);
		Double_t EtaCalibrationNegEl(const Int_t centrality, const Double_t Eta);
		Double_t EtaCalibrationPosEl(const Int_t centrality, const Double_t Eta);


		static const Double_t fgkClight;   // Speed of light (cm/ps)

		AliESDEvent* fESD;                  //! ESD object
		AliAODEvent* fAOD;                  //! AOD object
		AliEventCuts fEventCuts;
		AliMCEvent*  fMC;                   //! MC object
		AliStack*    fMCStack;              //! MC ESD stack
		TClonesArray* fMCArray;             //! MC array for AOD
		AliPIDResponse* fPIDResponse;       //! Pointer to PIDResponse
		AliAnalysisFilter* fTrackFilter2015PbPb;    //  Track Filter, set 2010 with golden cuts
		AliAnalysisFilter* fTrackFilterGolden;    //  Track Filter, set 2010 with golden cuts
		AliAnalysisFilter* fTrackFilterTPC; // track filter for TPC only tracks
		AliAnalysisFilter* fTrackFilter;
		AliAnalysisUtils* utils;
		AliSpherocityUtils* fSpheroUtils;
		TString       fAnalysisType;        //  "ESD" or "AOD"
		Bool_t        fAnalysisMC;          //  Real(kFALSE) or MC(kTRUE) flag
		Bool_t        fAnalysisPbPb;        //  true you want to analyze PbPb data, false for pp
		TRandom*      fRandom;              //! random number generator

		//
		// Cuts and options
		//

		Int_t        fNcl;                
		Double_t     fEtaCut;             // Eta cut used to select particles
		Int_t        fCent; //minimum centrality
		Int_t        fSpherocity;
		Float_t      fMinCent; //minimum centrality
		Float_t      fMaxCent; //maximum centrality
                const Double_t fDeDxMIPMin;
                const Double_t fDeDxMIPMax;
                const Double_t fdEdxHigh;
                const Double_t fdEdxLow;

		//
		// Help variables
		//
		Short_t      fMcProcessType;      // -1=invalid, 0=data, 1=ND, 2=SD, 3=DD
		Short_t      fTriggeredEventMB;   // 1 = triggered, 0 = not trigged (MC only)
		Short_t      fVtxStatus;          // -1 = no vtx, 0 = outside cut, 1 = inside cut
		Float_t      fZvtx;               // z vertex
		Float_t      fZvtxMC;             // z vertex MC (truth)
		Int_t        fRun;                // run no
		ULong64_t    fEventId;            // unique event id

		//
		// Output objects
		//
		TList*        fListOfObjects;     //! Output list of objects
		TH2F*         fEvents;            //! No of accepted events
		TH1F*         fVtxMC;             //! Event vertex info for ALL MC events
		Bool_t       fdEdxCalibrated;
		Bool_t       fMakePid;
		Bool_t       fLowPt;
		Int_t  fLHC16l;
		TH1F* fcent;
		TH1F* fcentAfterPrimaries;
		TH1F* fcentAfterV0s;


		// Histograms for Spherocity

		TH1D *hphiso;
		TH1D *hetaso;
		TH1D *hSo[11];

		// Histograms for PreCalibration

		TH2D *hMIPVsEta[11][3];
		TProfile *pMIPVsEta[11][3];
		TH2D *hMIPVsEtaV0s[11][3];
		TProfile *pMIPVsEtaV0s[11][3];
		TH2D *hPlateauVsEta[11][3];
		TProfile *pPlateauVsEta[11][3];
		TH2D *hPhi[11];

		TH2D *hMIPVsV0M[4];
		TProfile *pMIPVsV0M[4];
		TH2D *hMIPVsNch[4];
		TProfile *pMIPVsNch[4];

		TH2D     *hMIPVsPhi[11][4];
		TProfile *pMIPVsPhi[11][4];
		TH2D     *hPlateauVsPhi[11][4];
		TProfile *pPlateauVsPhi[11][4];


		// Histograms for PostCalibration


		TH1D *hPtAll[11][3];
		TH1D *hPtAllPos[11];
		TH1D *hPtAllNeg[11];
		TH2D *hPtVsP[11][4];

		TH2D *hDeDxVsP[11][4];

		TH2D *hnSigmaPiPos[11][4];
		TH2D *hnSigmaKPos[11][4];
		TH2D *hnSigmaPPos[11][4];

		TH2D *hnSigmaPiNeg[11][4];
		TH2D *hnSigmaKNeg[11][4];
		TH2D *hnSigmaPNeg[11][4];

		TH2D* histPiV0[11][4];
		TH1D* histpPiV0[11][4];

		TH2D* histPV0[11][4];
		TH1D* histpPV0[11][4];

		TH2D* histPiTof[11][4];
		TH1D* histpPiTof[11][4];

		TH2D* histEV0[11][4];

		TH1D* hMcIn[11][7];
		TH1D* hMcOut[11][7];
		TH1D* hMcInNeg[11][7];
		TH1D* hMcInPos[11][7];
		TH1D* hMcOutNeg[11][7];
		TH1D* hMcOutPos[11][7];

		TF1* fEtaCalibrationNeg;
		TF1* fEtaCalibration;
		TF1* felededxfitPos;
		TF1* felededxfitNeg;
		TF1* fcutDCAxy;
		TF1* fcutLow;
		TF1* fcutHigh;

		AliAnalysisTaskSpherocity(const AliAnalysisTaskSpherocity&);            // not implemented
		AliAnalysisTaskSpherocity& operator=(const AliAnalysisTaskSpherocity&); // not implemented
		ClassDef(AliAnalysisTaskSpherocity, 1);    //Analysis task for high pt analysis 
};

#endif


