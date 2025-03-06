#pragma once
//-----------------------------------------------------------------------
// CGame
// 
// Erklärung : Eine weitestgehend leere Klasse, 
//             sinnfällig in eine Windows-Applikation eingebettet,
//             um ein Spiel bzw. eine 3D-Simulation zu erzeugen
// Autor     : Prof. Dr. Tobias Breiner
// Ort       : Pfungstadt
// Zeit      : seit Aug. 2011 (mit seitdem ständigen Verbesserungs-Updates)
// Copyright : Tobias Breiner  
// Disclaimer: Nutzung auf eigene Gefahr, keine Gewähr, no warranty!
//------------------------------------------------------------------------


#ifdef _WIN64
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug64.lib")
#pragma comment (lib, "VektoriaMath_Debug64.lib")
#else
#pragma comment (lib, "Vektoria_Release64.lib")
#pragma comment (lib, "VektoriaMath_Release64.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug.lib")
#pragma comment (lib, "VektoriaMath_Debug.lib")
#else
#pragma comment (lib, "Vektoria_Release.lib")
#pragma comment (lib, "VektoriaMath_Release.lib")
#endif
#endif

#define NR_OF_STONES 500 //für anzahl an random objekten
#define NR_OF_DEATHSTARS 11 //für random anzahl an Todessternen
#define NR_OF_BULLETS 30 


#include "Vektoria\Root.h"

using namespace Vektoria;


class CGame
{
public:
	// Wird vor Begin einmal aufgerufen (Konstruktor):
	CGame(void);																				

	// Wird nach Ende einmal aufgerufen (Destruktor):
	~CGame(void);																				

	// Wird zu Begin einmal aufgerufen:
	void Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash);	

	// Wird während der Laufzeit bei jedem Bildaufbau aufgerufen:
	void Tick(float fTime, float fTimeDelta);						

	// Wird am Ende einmal aufgerufen:
	void Fini();																				

	// Wird immer dann aufgerufen, wenn der Benutzer die Fenstergröße verändert hat:
	void WindowReSize(int iNewWidth, int iNewHeight);											

	// Holt das minimale Zeitdelta zur eventuellen Frame-Rate-Beschränkung:
	float GetTimeDeltaMin();																	

	// Holt die Versionsnummer:
	float GetVersion();


private:

	// Die Wurzel des Szenengrafen: 
	CRoot m_zr; 
	// Hier meins:
	CScene m_zs;
	CPlacement m_zpCamera;
	CPlacement m_zpErde;
	CGeoSphere m_zgErde;
	CFrame m_zf;
	CViewport m_zv;
	CCamera m_zc;
	CLightParallel m_zl;
	//für material -> texture
	CMaterial m_zm; //glow, specular, bump auf das drauf
	//für splitscreen
	CPlacement m_zpCameraSplitR;
	CViewport m_zvSplitR;
	CCamera m_zcSplitR;
	CPlacement m_zpCameraSplitL;
	CViewport m_zvSplitL;
	CCamera m_zcSplitL;

	//Mond, Sonne
	CPlacement m_zpErdeMond;
	CPlacement m_zpMond;
	CGeoSphere m_zgMond;
	CMaterial m_zmMond;
	CPlacement m_zpSonne;
	CGeoSphere m_zgSonne;
	CMaterial m_zmSonne;

	//Ufo aus Geometrischen Primitiven
	CPlacement m_zpUfo;
	CPlacement m_zpUfopartB;
	CGeoCube m_zgUfopartA;
	CGeoPyramid m_zgUfopartB;
	CMaterial m_zmUfopartA;
	CMaterial m_zmUfopartB;

	//Todesstern Aufgabe 6 (mit Bump map statt Displacement) -> für instantiieren kopiere einfach code des objekts
	/*
	CPlacement m_zpTod1;
	CGeoSphere m_zgTod1;
	CMaterial m_zmTod1;

	CPlacement m_zpTod2;
	CGeoSphere m_zgTod2;
	CPlacement m_zpTod3;
	CGeoSphere m_zgTod3;
	CPlacement m_zpTod4;
	CGeoSphere m_zgTod4;
	CPlacement m_zpTod5;
	CGeoSphere m_zgTod5;
	CPlacement m_zpTod6;
	CGeoSphere m_zgTod6;
	CPlacement m_zpTod7;
	CGeoSphere m_zgTod7;
	CPlacement m_zpTod8;
	CGeoSphere m_zgTod8;
	CPlacement m_zpTod9;
	CGeoSphere m_zgTod9;
	CPlacement m_zpTod10;
	CGeoSphere m_zgTod10;
	CPlacement m_zpTod11;
	CGeoSphere m_zgTod11;
	//zusätzlicher todesstern zum anklicken
	CPlacement m_zpTod0;
	CGeoSphere m_zgTod0;
	*/

	//Todessterne als Array
	CPlacement m_azpDeathStar[NR_OF_DEATHSTARS];
	//CGeoSphere m_zgDeathStar;
	CMaterial m_zmDeathStar;
	CHVector m_avDeathStarRand[NR_OF_DEATHSTARS];
	//test für auswählen
	CGeoSphere m_azgDeathStars[NR_OF_DEATHSTARS];
	//auswählen
	CGeos m_zgsPreselected;
	unsigned int iCounter_Mat_Tod = 0;
	CMaterial m_zm_Tod_red;
	

	/*
	//alternative für todesstern -> anzahl an random objekten
	CPlacement m_azpStone[NR_OF_STONES];
	CGeoQuad m_zgStone;
	CMaterial m_zmStone;					//ein stein
	CHVector m_avStoneRandom[NR_OF_STONES];
	CMaterial m_zamStone[4];				//4 steine
	*/

	//freiwillig:Wolkenschicht, große kugel mit sternentextur in der Erde ist
	CPlacement m_zpCloud;
	CGeoSphere m_zgCloud;
	CMaterial m_zmcloud;
	
	CPlacement m_zpSphereStars;
	CGeoSphere m_zgSphereStars;
	CMaterial m_zmstars;

	//WASD Steuerung
	CDeviceKeyboard m_zdKeyboard;

	//Curser ersetzen
	CDeviceCursor m_zdc;
	CImage m_ziRocket;
	CImage m_ziHand;
	//CImage m_ziArrow; //weiß nicht ob braucht
	COverlay m_zoRocket;
	COverlay m_zoHand;
	

	//freiwillig controller steuerung
	//CDeviceGameController m_zdController1;

	//Startbildschirm
	CImage m_ziLogo;
	CImage m_ziSingle;
	CImage m_ziMulty;
	COverlay m_zoLogo;
	COverlay m_zoSingle;
	COverlay m_zoMulty;
	COverlays m_zos;
	bool m_IsSinglePlayer = true;
	//zu Startbildschirm zurück
	COverlay m_zoBack2Start;
	COverlays m_zosInGame;
	CImage m_ziBack2Start;
	bool m_ingame = false;

	//Asteroidengürtel um sonne
	CPlacement m_azpStone[NR_OF_STONES];
	CGeoQuad m_zgStone;
	CMaterial m_zmStone;
	CHVector m_avStoneRand[NR_OF_STONES];

	//Nebel
	CPlacement m_azpNebula[5];
	CGeoQuad m_zgNebula;
	CMaterial m_zmNebula;

	//Bullets
	CPlacements m_zpsBullets;
	CPlacement m_zpBulletsTemplate;
	CGeoCone m_zgBullets;
	CMaterial m_zmBullets;
	CPlacements m_zpsEBullets;
	CPlacement m_zpEBulletsTemplate;
	CGeoCone m_zgEBullets;
	CMaterial m_zmEBullets;
	//collision
	CHVector m_avBulletLastPos[NR_OF_BULLETS];
	CHVector m_avEBulletLastPos[NR_OF_BULLETS];

	//Sound
	CAudio m_zaMusic;
	CAudio m_azaGunShot[NR_OF_BULLETS];
	CAudio m_zaHit;

	//importer OBJ
	CFileWavefront m_filewf1;
	CFileWavefront m_filewf2;
	CFileWavefront m_filewf3;
	CGeoTriangleTable* m_pzgImported_1 = nullptr;
	CGeoTriangleTable* m_pzgImported_2 = nullptr;
	CGeoTriangleTable* m_pzgImported_3 = nullptr;
	CPlacement m_zpSpaceshipS;
	CMaterial m_zmSpaceshipViolet;
	CPlacement m_zpSpaceshipML;
	CMaterial m_zmSpaceshipCyan;
	CPlacement m_zpSpaceshipMR;
	CMaterial m_zmSpaceshipMagenta;
	//damit geo intersect geht
	CPlacement m_zpWeS;
	CPlacement m_zpWeML;
	CPlacement m_zpWeMR;
	CGeoCubeWire m_zgWeS;
	CGeoCubeWire m_zgWeML;
	CGeoCubeWire m_zgWeMR;
	CMaterial m_zmTransparent;

	//writing Points, Healthbar, win/lose
	CWritingFont m_zwfWhite;
	CWritingFont m_zwfRed;
	CWriting m_zwPointsL;
	CWriting m_zwPointsR;
	CWriting m_zwHealthL;
	CWriting m_zwHealthR;
	int m_iPointsL = 0;
	int m_iPointsR = 0;
	int m_iHealthL = 100;
	int m_iHealthR = 100;
	CWriting m_zwWinL;
	CWriting m_zwWinR;
	CWriting m_zwLose;
	char m_cWon1[50] = "Player 1 WON!";
	char m_cWon2[50] = "Player 2 WON!";
	char m_cWon[50] = "YOU WON!";
	char m_cLose[50] = "You lost the Game!";

	//"KI-Gegner"
	CPlacement m_zpKI;
	CPlacement m_zpKIpartA;
	CPlacement m_zpKIpartB;
	CGeoEllipsoid m_zgKIpartA;
	CGeoDome m_zgKIpartB;
	CMaterial m_zmKIpartA;
	CMaterial m_zmKIpartB;

	int who = 0; //auf wen schießen

	//Satelit
	CPlacement m_zpSatelit;
	CGeoEllipsoid m_zgSatelit;
	CMaterial m_zmSatelit;
	CMaterial m_zmSatelitOff;
	bool m_bSatelitOn = true;
};


