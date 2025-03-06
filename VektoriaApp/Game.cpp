#include "Game.h"

CGame::CGame(void)
{
}

CGame::~CGame(void)
{
}

void CGame::Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash)
{
	//---------------------------------
	// Initialisiere die Knotenobjekte:
	//---------------------------------
	//Übung 1 + Übung 2 + Übung 3 + Übung 4 + Übung 5 + Übung 6 + Übung 7 + Übung 8

	//solarsystemscope.com  -> Texturen für alle objekte im sonnensystem

	// Zuallererst muss die Root mit dem Splash-Screen initialisiert werden, 
	// damit die Engine freigeschaltet wird:
	m_zr.Init(psplash,false,false,true);

	// Hier meins (grossteil von Folien aus Manual)
	m_zc.Init(QUARTERPI);
	m_zcSplitR.Init(QUARTERPI);
	m_zcSplitL.Init(QUARTERPI);
	m_zf.Init(hwnd, procOS);
	m_zf.AddDeviceKeyboard(&m_zdKeyboard); //Keyboard
	//m_zf.AddDeviceGameController(&m_zdController1); //Controller
	m_zl.Init(CHVector(-30.0f, -30.0f, -10.0f), CColor(1.0f, 1.0f, 1.0f));
	m_zr.AddFrame(&m_zf);
	m_zf.AddViewport(&m_zv);
	m_zf.AddViewport(&m_zvSplitR);
	m_zf.AddViewport(&m_zvSplitL);
	m_zr.AddScene(&m_zs);
	//m_zs.AddPlacement(&m_zpErdeMond); //ErdeMond an Scene oder an Sonne
	m_zs.AddPlacement(&m_zpSonne);	//Sonne an Scene
	m_zs.AddPlacement(&m_zpCamera);
	m_zs.AddLightParallel(&m_zl);
	m_zpCamera.AddCamera(&m_zc);
	m_zpCamera.TranslateZ(85.0f); //Kamera verschieben, damit nicht in Kugel drin 85 -> jatzt 10, damit nicht in raumschiff
	m_zpCamera.SetTranslationSensitivity(20); //WASD sensitivität
	
	m_zs.SetPhysicsSpace(); //für Space Physics, ohne Gravitation
	
	
	//m_zvSplit.Init(&m_zcSplit, C2dRect(0.0F, 0.0F));
	//m_zvSplit.InitHalfRight(&m_zcSplit);
	m_zpCameraSplitR.AddCamera(&m_zcSplitR);
	m_zpCameraSplitR.TranslateZ(85.0f); //Kamera verschieben, damit nicht in Kugel drin
	m_zpCameraSplitR.SetTranslationSensitivity(50);
	m_zs.AddPlacement(&m_zpCameraSplitR);

	m_zpCameraSplitL.AddCamera(&m_zcSplitL);
	m_zpCameraSplitL.TranslateZ(85.0f); //Kamera verschieben, damit nicht in Kugel drin
	m_zpCameraSplitL.SetTranslationSensitivity(50);
	m_zs.AddPlacement(&m_zpCameraSplitL);

	//--------------
	//SplitScreen:
	//--------------
	//m_zvSplitR.Init(&m_zcSplitR, 0.5f, 1.0f, 0.5f, 0.0f);
	m_zvSplitR.InitHalfRight(&m_zcSplitR);
	m_zvSplitR.SwitchOff();
	//m_zvSplitL.Init(&m_zcSplitL, 0.5f, 1.0f, 0.0f, 0.0f);
	m_zvSplitL.InitHalfLeft(&m_zcSplitL);
	m_zvSplitL.SwitchOff();
	m_zv.InitFull(&m_zc);
	//m_zvSplitR.InitFull(&m_zcSplitR);
	//ausprobieren entweder zv mit full und left initialisieren oder zv full, und jew zvLeft und zvRight


	//m_zvSplit.InitHalfRight(&m_zcSplit);
	//m_zv.InitFull(&m_zc);
	//m_zv.InitHalfLeft(&m_zc);
	
	
	

	//------
	//ERDE:
	//------
	m_zgErde.Init(1.0F, &m_zm, 50, 50); //für texture NULL zu &m_zm
	m_zpErde.AddGeo(&m_zgErde);
	m_zm.MakeTextureDiffuse("textures\\earth_image.jpg");
	m_zm.MakeTextureGlow("textures\\earth_glow.jpg");
	m_zm.MakeTextureSpecular("textures\\earth_reflection.jpg");
	m_zm.MakeTextureBump("textures\\earth_bump.jpg");
	
	//cloud
	m_zgCloud.Init(1.05F, &m_zmcloud, 50, 50);
	m_zpCloud.AddGeo(&m_zgCloud);
	m_zmcloud.MakeTextureDiffuse("textures\\clouds_alpha_l1.gif");
	m_zmcloud.SetTransparencyOn();
	m_zpCloud.FixDistance(1.9F); //-> weiß nicht welche wert ich da einsetzen muss
	m_zpErde.AddPlacement(&m_zpCloud); //-> cloud Sphere an Erde anhängen
	

	//-------
	//Sonne:
	//-------
	m_zgSonne.Init(3.0F, &m_zmSonne, 50, 50);
	m_zpSonne.AddGeo(&m_zgSonne);
	//m_zmSonne.MakeTextureDiffuse("textures\\sonne.jpg");
	m_zmSonne.LoadPreset("Sun");
	m_zmSonne.SetGlowStrength(3.0f);
	m_zv.SetBloomOn();
	m_zv.SetBloomStrengthNear(6.0f);
	m_zv.SetBloomStrengthFar(5.0f);
	m_zv.SetBloomWidth(3.0f);
	///*
	m_zvSplitR.SetBloomOn();
	m_zvSplitR.SetBloomStrengthNear(6.0f);
	m_zvSplitR.SetBloomStrengthFar(5.0f);
	m_zvSplitR.SetBloomWidth(3.0f);
	m_zvSplitL.SetBloomOn();
	m_zvSplitL.SetBloomStrengthNear(6.0f);
	m_zvSplitL.SetBloomStrengthFar(5.0f);
	m_zvSplitL.SetBloomWidth(3.0f);
	//*/
	m_zpSonne.AddPlacement(&m_zpErdeMond);


	//-------
	//Mond:
	//-------
	m_zgMond.Init(0.3F, &m_zmMond, 50, 50);
	m_zpMond.AddGeo(&m_zgMond);
	m_zmMond.MakeTextureDiffuse("textures\\Moon_Image.jpg");
	m_zmMond.MakeTextureBump("textures\\moon_bump.jpg");

	
	
	//-------
	//ErdeMond:
	//-------
	m_zpErdeMond.AddPlacement(&m_zpErde);
	m_zpErdeMond.AddPlacement(&m_zpMond);


	//----------
	//Sky:
	//----------
	//weiß nich warum textur so groß skalliert
	m_zgSphereStars.Init(10000.0F, &m_zmstars, 50, 50);
	m_zpSphereStars.AddGeo(&m_zgSphereStars);
	//m_zmstars.MakeTextureSky("textures\\starsSky.jpg");
	m_zmstars.LoadPreset("NasaStars"); //alternativ
	m_zgSphereStars.Flip();
	m_zpSphereStars.SetSky();
	m_zs.AddPlacement(&m_zpSphereStars);

	//----------
	//Ufo: alt
	//----------
	
	/*m_zpUfo.AddPlacement(&m_zpUfopartA);
	m_zpUfo.AddPlacement(&m_zpUfopartB);
	m_zpUfo.RotateY(90);

	m_zpSonne.AddPlacement(&m_zpUfo);
	

	m_zgUfopartA.Init(0.3F, &m_zmUfopartA, 50, 50);
	m_zpUfopartA.AddGeo(&m_zgUfopartA);
	m_zmUfopartA.MakeTextureDiffuse("textures\\green_image.jpg");
	m_zgUfopartA.Flip();

	m_zgUfopartB.Init(2.0F, 0.3F, &m_zmUfopartB, 50);
	m_zpUfopartB.AddGeo(&m_zgUfopartB);
	m_zmUfopartB.MakeTextureDiffuse("textures\\green_image.jpg");
	m_zpUfopartB.TranslateY(0.3F);*/
	

	//------------
	//Todesstern:
	//------------
	/*
	m_zgTod1.Init(0.5F, &m_zmTod1); //kann die letzten pararmeter weg lassen, default jew auf 24
	m_zpTod1.AddGeo(&m_zgTod1);
	m_zmTod1.MakeTextureDiffuse("textures\\tod_image.png");
	m_zmTod1.MakeTextureBump("textures\\tod_bump.jpg");

	m_zpErde.AddPlacement(&m_zpTod1);

	m_zpTod1.RotateY(90);
	//---2
	m_zgTod2.Init(0.5F, &m_zmTod1);
	m_zpTod2.AddGeo(&m_zgTod2);

	m_zpErde.AddPlacement(&m_zpTod2);

	m_zpTod2.RotateY(90);
	//---3
	m_zgTod3.Init(0.5F, &m_zmTod1);
	m_zpTod3.AddGeo(&m_zgTod3);

	m_zpErde.AddPlacement(&m_zpTod3);

	m_zpTod3.RotateY(90);
	//---4
	m_zgTod4.Init(0.5F, &m_zmTod1);
	m_zpTod4.AddGeo(&m_zgTod4);

	m_zpErde.AddPlacement(&m_zpTod4);

	m_zpTod4.RotateY(90);
	//---5
	m_zgTod5.Init(0.5F, &m_zmTod1); 
	m_zpTod5.AddGeo(&m_zgTod5);

	m_zpErde.AddPlacement(&m_zpTod5);

	m_zpTod5.RotateY(90);
	//---6
	m_zgTod6.Init(0.5F, &m_zmTod1); 
	m_zpTod6.AddGeo(&m_zgTod6);

	m_zpErde.AddPlacement(&m_zpTod6);

	m_zpTod6.RotateY(90);
	//---7
	m_zgTod7.Init(0.5F, &m_zmTod1); 
	m_zpTod7.AddGeo(&m_zgTod7);

	m_zpErde.AddPlacement(&m_zpTod7);

	m_zpTod7.RotateY(90);
	//---8
	m_zgTod8.Init(0.5F, &m_zmTod1);
	m_zpTod8.AddGeo(&m_zgTod8);

	m_zpErde.AddPlacement(&m_zpTod8);

	m_zpTod8.RotateY(90);
	//---9
	m_zgTod9.Init(0.5F, &m_zmTod1);
	m_zpTod9.AddGeo(&m_zgTod9);

	m_zpErde.AddPlacement(&m_zpTod9);

	m_zpTod9.RotateY(90);
	//---10
	m_zgTod10.Init(0.5F, &m_zmTod1);
	m_zpTod10.AddGeo(&m_zgTod10);

	m_zpErde.AddPlacement(&m_zpTod10);

	m_zpTod10.RotateY(90);
	//---11
	m_zgTod11.Init(0.5F, &m_zmTod1);
	m_zpTod11.AddGeo(&m_zgTod11);

	m_zpErde.AddPlacement(&m_zpTod11);

	m_zpTod1.RotateY(90);

	//---Tod 0 für anklicken
	m_zgTod0.Init(2.F, &m_zmTod1);
	m_zpTod0.AddGeo(&m_zgTod0);

	m_zpErde.AddPlacement(&m_zpTod0);

	m_zpTod1.RotateY(90);
	*/

	//----------------------
	//Todesstern als Array:
	//----------------------
	m_zmDeathStar.MakeTextureDiffuse("textures\\tod_image.png");
	m_zmDeathStar.MakeTextureBump("textures\\tod_bump.jpg");
	//m_zgDeathStar.Init(0.5f, &m_zmDeathStar);
	
	for (int i = 0; i < NR_OF_DEATHSTARS; i++)
	{
		m_zpErde.AddPlacement(&m_azpDeathStar[i]);
		m_azgDeathStars[i].Init(0.5f, &m_zmDeathStar);
		//m_azpStone[i].SetBillboard(eBillboardType_Parallel); //das default, müsste nicht angeben
		m_azpDeathStar[i].AddGeo(&m_azgDeathStars[i]);
		m_azpDeathStar[i].RotateY(90);
		m_avDeathStarRand[i] = CHVector((rand() % 1000 / 1000.0f + 5.5f),   //x (verschiebung von Erde weg)
			(rand() % 1000 / 1000.0f - 0.5f) * 0.3f,						//y (verschiebung von Erde weg),
			2,																// z (war erstmal 0, macht nicht viel unterschied)
			rand() % 1000 / 1000.0f);										//w (=v=Geschwindigkeit)

		m_zgsPreselected.Add(&m_azgDeathStars[i]);							//alle Geos in Preselected

	}

	//todesstern rot wenn auswählt
	m_zr.AddMaterial(&m_zm_Tod_red);
	m_zm_Tod_red.LoadPreset("Blood");
	


	//-------
	//Cursor:
	//-------
	m_ziRocket.Init("textures\\rocket.gif");
	m_ziHand.Init("textures\\hand.gif");

	m_zoRocket.Init(&m_ziRocket, C2dRect(0.05F, 0.05F), true);
	m_zoHand.Init(&m_ziHand, C2dRect(0.05F, 0.05F), true);
	m_zoRocket.SetLayer(0.1f);
	m_zoHand.SetLayer(0.1f);


	m_zf.AddDeviceCursor(&m_zdc);
	m_zv.AddOverlay(&m_zoRocket);
	m_zv.AddOverlay(&m_zoHand);
	///*
	m_zvSplitR.AddOverlay(&m_zoRocket);
	m_zvSplitR.AddOverlay(&m_zoHand);
	m_zvSplitL.AddOverlay(&m_zoRocket);
	m_zvSplitL.AddOverlay(&m_zoHand);
	//*/

	//-----------------------------
	//Startbildschirm mit Buttons:
	//-----------------------------
	m_ziLogo.Init("textures\\logo2.png");
	m_zoLogo.Init(&m_ziLogo, C2dRect(1.F, 1.F), false);
	m_zoLogo.SetLayer(0.9f);
	
	m_ziSingle.Init("textures\\single.png");
	m_ziMulty.Init("textures\\multi.png");
	m_zoSingle.Init(&m_ziSingle, C2dRect(0.4F, 0.2F, 0.f, 0.8f), false);
	m_zoMulty.Init(&m_ziMulty, C2dRect(0.4F, 0.2F, 0.6f, 0.8f), false);
	m_zoSingle.SetLayer(0.2f);
	m_zoMulty.SetLayer(0.2f);
	m_ziBack2Start.Init("textures\\back.jpg");
	m_zoBack2Start.Init(&m_ziBack2Start, C2dRect(0.03F, 0.03F, 0.96f, 0.95f), false);
	m_zoBack2Start.SetLayer(0.2f);

	m_zv.AddOverlay(&m_zoSingle);
	m_zv.AddOverlay(&m_zoMulty);
	m_zv.AddOverlay(&m_zoLogo);
	m_zv.AddOverlay(&m_zoBack2Start);
	///*
	m_zvSplitR.AddOverlay(&m_zoSingle);
	m_zvSplitR.AddOverlay(&m_zoMulty);
	m_zvSplitR.AddOverlay(&m_zoLogo);
	m_zvSplitR.AddOverlay(&m_zoBack2Start);
	m_zvSplitL.AddOverlay(&m_zoSingle);
	m_zvSplitL.AddOverlay(&m_zoMulty);
	m_zvSplitL.AddOverlay(&m_zoLogo);
	m_zvSplitL.AddOverlay(&m_zoBack2Start);
	//*/
	
	m_zos.Add(&m_zoSingle);
	m_zos.Add(&m_zoMulty);
	m_zosInGame.Add(&m_zoBack2Start);

	//--------------------------
	//Asteroidengürtel um Sonne:
	//--------------------------
	
	m_zmStone.MakeTextureBillboard("textures\\stone_1.jpg"); //ein material
	m_zmStone.SetChromaKeyingOn();
	m_zgStone.Init(0.11f, &m_zmStone);
	/*
	for (int i = 0; i < 4; i++)						//mehrere Materials
	{
		sprintf(ac, "textures\\stone_%i.jpg", i);
		m_zamStone[i].MakeTextureBillboard(ac);
		m_zamStone[i].SetChromaKeyingOn();
		m_zgStone.Init(0.01f, &m_zmStone);
	}
	*/

	for (int i = 0; i < NR_OF_STONES; i++)
	{
		m_zpSonne.AddPlacement(&m_azpStone[i]);
		m_azpStone[i].SetBillboard(eBillboardType_Parallel); //das default, müsste nicht angeben
		m_azpStone[i].AddGeo(&m_zgStone);
		m_avStoneRand[i] = CHVector((rand() % 1000 / 1000.0f + 5.5f),(   //x (verschiebung von Sonne weg)
			rand() % 1000 / 1000.0f - 0.5f) * 0.3f, 0,					//y (verschiebung von erde weg), z (hier erstmal 0)
			rand() % 1000 / 1000.0f);									//w (=v=Geschwindigkeit)

	}


	//------------
	//Nebel:
	//------------
	m_zmNebula.MakeTextureSprite("textures\\nebula.tif"); //sprite statt billboard damit beleuchtet
	m_zmNebula.SetTransparencyOn();
	m_zgNebula.Init(1.0f, &m_zmNebula);
	m_zs.AddPlacement(&m_azpNebula[0]);
	m_azpNebula[0].SetBillboard();
	m_azpNebula[0].TranslateY(7.0f);

	for (int i = 1; i < 5; i++)
	{
		m_azpNebula[0].AddPlacement(&m_azpNebula[i]);
		m_azpNebula[i].AddGeo(&m_zgNebula);
		m_azpNebula[i].TranslateZ(i / 5.0f);
	}

	//----------------------
	//Raumschiff an Camera: (temporär UFO kopiert)
	//----------------------
	/*
	m_zpUfo.AddPlacement(&m_zpUfopartA);
	m_zpUfo.AddPlacement(&m_zpUfopartB);
	m_zpUfo.TranslateZ(-20);
	m_zpUfo.TranslateYDelta(-3);
	//m_zpUfo.RotateY(90);

	m_zpCamera.AddPlacement(&m_zpUfo);
	m_zpCameraSplitR.AddPlacement(&m_zpUfo);
	m_zpCameraSplitL.AddPlacement(&m_zpUfo);

	m_zgUfopartA.Init(0.3F, &m_zmUfopartA, 50, 50);
	m_zpUfopartA.AddGeo(&m_zgUfopartA);
	m_zmUfopartA.MakeTextureDiffuse("textures\\green_image.jpg");
	m_zgUfopartA.Flip();
	m_zpUfopartA.RotateYDelta(10);

	m_zgUfopartB.Init(2.0F, 0.3F, &m_zmUfopartB, 4);
	m_zpUfopartB.AddGeo(&m_zgUfopartB);
	m_zmUfopartB.MakeTextureDiffuse("textures\\green_image.jpg");
	m_zpUfopartB.TranslateY(0.3F);
    */

	//------------------------
	//Raumschiff imported OBJ:
	//------------------------
	m_pzgImported_1 = m_filewf1.LoadGeoTriangleTable("models\\spaceship.obj");
	m_zpCamera.AddPlacement(&m_zpSpaceshipS);//Test andersrum -> Camera an raumschiff
	//m_zpSpaceshipS.AddPlacement(&m_zpCamera);
	m_zpSpaceshipS.AddGeo(m_pzgImported_1);
	m_zpSpaceshipS.TranslateZ(-10);
	//m_zpCamera.TranslateZ(10);
	m_zmSpaceshipViolet.MakeTextureDiffuse("models\\spaceship_violet.png");
	m_pzgImported_1->SetMaterial(&m_zmSpaceshipViolet);

	//m_zpSpaceshipS.TranslateZ(85.0f); //Placement verschieben, damit nicht in Sonne
	//m_zs.AddPlacement(&m_zpSpaceshipS);
	
	//Spaceship drehen
	CHMat mRot;
	mRot.RotateY(PI);
	m_pzgImported_1->Transform(mRot);
	
	m_pzgImported_2 = m_filewf2.LoadGeoTriangleTable("models\\spaceship.obj");
	m_zpCameraSplitL.AddPlacement(&m_zpSpaceshipML); //test andersrum
	//m_zpSpaceshipML.AddPlacement(&m_zpCameraSplitL);
	m_zpSpaceshipML.AddGeo(m_pzgImported_2);
	m_zpSpaceshipML.TranslateZ(-10);
	//m_zpCameraSplitL.TranslateZ(10);
	m_zmSpaceshipCyan.MakeTextureDiffuse("models\\spaceship_cyan.png");
	m_pzgImported_2->SetMaterial(&m_zmSpaceshipCyan);
	m_pzgImported_2->Transform(mRot);

	//m_zpSpaceshipML.TranslateZ(85.0f); //Placement verschieben, damit nicht in Sonne
	//m_zs.AddPlacement(&m_zpSpaceshipML);

	m_pzgImported_3 = m_filewf3.LoadGeoTriangleTable("models\\spaceship.obj");
	m_zpCameraSplitR.AddPlacement(&m_zpSpaceshipMR); //Test andersrum
	//m_zpSpaceshipMR.AddPlacement(&m_zpCameraSplitR);
	m_zpSpaceshipMR.AddGeo(m_pzgImported_3);
	m_zpSpaceshipMR.TranslateZ(-10);
	//m_zpCameraSplitR.TranslateZ(10);
	m_zmSpaceshipMagenta.MakeTextureDiffuse("models\\spaceship_magenta.png");
	m_pzgImported_3->SetMaterial(&m_zmSpaceshipMagenta);
	m_pzgImported_3->Transform(mRot);

	//m_zpSpaceshipMR.TranslateZ(85.0f); //Placement verschieben, damit nicht in Sonne
	//m_zs.AddPlacement(&m_zpSpaceshipMR);

	m_zgWeS.Init(1.f, &m_zmTransparent);
	m_zpWeS.AddGeo(&m_zgWeS);
	m_zmTransparent.MakeTextureDiffuse("textures\\red_image.jpg");
	m_zmTransparent.SetChromaKeyingOn();
	m_zpSpaceshipS.AddPlacement(&m_zpWeS);

	m_zgWeML.Init(1.f, &m_zmTransparent);
	m_zpWeML.AddGeo(&m_zgWeML);
	m_zpSpaceshipML.AddPlacement(&m_zpWeML);

	m_zgWeMR.Init(1.f, &m_zmTransparent);
	m_zpWeMR.AddGeo(&m_zgWeMR);
	m_zpSpaceshipMR.AddPlacement(&m_zpWeMR);


	//--------
	//Bullets:  erstmal nur einen bestimmten Deathstar abschießen
	//--------
	//m_zmBullets.LoadPreset("AshesGlowing");
	m_zmBullets.MakeTextureDiffuse("textures\\green_image.jpg");
	m_zgBullets.Init(0.2, 0.9, & m_zmBullets);
	m_zpBulletsTemplate.AddGeo(&m_zgBullets);
	//m_zpBulletsTemplate.RotateX(10);
	m_zpBulletsTemplate.SetPhysics(2.0f, 0.1f, 3000.0f, 200000.1f, true); //letzter wert war auf 200000.01
	m_zpBulletsTemplate.SwitchOff();
	m_zs.AddPlacement(&m_zpBulletsTemplate);
	//Ring Buffer
	m_zpsBullets.RingMake(NR_OF_BULLETS, m_zpBulletsTemplate);
	m_zs.AddPlacements(m_zpsBullets);

	

	//Enemy Bullets
	m_zmEBullets.MakeTextureDiffuse("textures\\red_image.jpg");
	m_zgEBullets.Init(0.1, 0.5, &m_zmEBullets);
	m_zpEBulletsTemplate.AddGeo(&m_zgEBullets);
	m_zpEBulletsTemplate.SetPhysics(2.0f, 0.1f, 3000.0f, 200000.1f, true); //letzter wert war auf 200000.01
	m_zpEBulletsTemplate.SwitchOff();
	m_zs.AddPlacement(&m_zpBulletsTemplate);
	//Ring Buffer
	m_zpsEBullets.RingMake(NR_OF_BULLETS, m_zpEBulletsTemplate);
	m_zs.AddPlacements(m_zpsEBullets);

	//-------
	//Sound:
	//-------
	m_zaMusic.Init("sounds\\music1.wav"); //existiert noch nicht
	m_zs.AddAudio(&m_zaMusic);
	m_zaMusic.Loop();
	m_zaMusic.SetVolume(0.9f);

	for (int i = 0; i < NR_OF_BULLETS; i++)
	{
		m_zs.AddAudio(&m_azaGunShot[i]);
		m_azaGunShot[i].Init("sounds\\gunshot.wav");
		m_azaGunShot[i].SetVolume(0.7f);
	}

	m_zaHit.Init("sounds\\explosion.wav");
	m_zs.AddAudio(&m_zaHit);
	m_zaHit.SetVolume(0.6);

	//---------------
	//Writing/Points
	//---------------
	//Score
	m_zwfWhite.LoadPreset("SimSunWhite");
	m_zwPointsL.Init(C2dRect(0.1f, 0.05f, 0.05f, 0.1f), 5, &m_zwfWhite);
	m_zwPointsR.Init(C2dRect(0.1f, 0.05f, 0.9f, 0.1f), 5, &m_zwfWhite);
	m_zv.AddOverlay(&m_zwPointsL);
	m_zvSplitL.AddOverlay(&m_zwPointsL);
	m_zvSplitR.AddOverlay(&m_zwPointsR);
	m_zwfWhite.SetChromaKeyingOn();
	m_zwPointsL.SetLayer(0.95f);
	m_zwPointsR.SetLayer(0.95f);
	m_zr.AddMaterial(&m_zwfWhite);
	m_zwPointsL.SwitchOff();
	m_zwPointsR.SwitchOff();
	//Health
	m_zwHealthL.Init(C2dRect(0.1f, 0.05f, 0.05f, 0.2f), 5, &m_zwfWhite);
	m_zwHealthR.Init(C2dRect(0.1f, 0.05f, 0.9f, 0.2f), 5, &m_zwfWhite);
	m_zwHealthL.SetColor(CColor(eColor_Red));
	m_zwHealthR.SetColor(CColor(eColor_Red));
	m_zv.AddOverlay(&m_zwHealthL);
	m_zvSplitL.AddOverlay(&m_zwHealthL);
	m_zvSplitR.AddOverlay(&m_zwHealthR);
	m_zwHealthL.SetLayer(0.95f);
	m_zwHealthR.SetLayer(0.95f);
	m_zwHealthL.SwitchOff();
	m_zwHealthR.SwitchOff();
	//win/lose
	m_zwWinL.Init(C2dRect(2.f, 0.5f, 0.1f, 0.2f), 50, &m_zwfWhite);
	m_zwLose.Init(C2dRect(2.f, 0.5f, 0.1f, 0.2f), 50, &m_zwfWhite);
	m_zwWinL.SetColor(CColor(eColor_Green));
	m_zwLose.SetColor(CColor(eColor_Red));
	m_zv.AddOverlay(&m_zwWinL); 
	m_zv.AddOverlay(&m_zwLose);
	m_zvSplitL.AddOverlay(&m_zwWinL);
	m_zvSplitL.AddOverlay(&m_zwLose);
	m_zvSplitR.AddOverlay(&m_zwWinL);
	m_zvSplitR.AddOverlay(&m_zwLose);
	m_zwWinL.SetLayer(0.95f);
	m_zwLose.SetLayer(0.95f);
	m_zwWinL.SwitchOff();
	m_zwLose.SwitchOff();


	//------------
	//"KI-Gegner":
	//------------

	m_zpKI.AddPlacement(&m_zpKIpartA);
	m_zpKI.AddPlacement(&m_zpKIpartB);
	m_zpKI.TranslateY(10);
	m_zpKI.RotateY(90);

	m_zpSonne.AddPlacement(&m_zpKI);

	m_zgKIpartA.Init(CHVector(2.f, 0.5f, 2.f), &m_zmKIpartA);
	m_zpKIpartA.AddGeo(&m_zgKIpartA);
	m_zmKIpartA.MakeTextureDiffuse("textures\\green_image.jpg");
	//m_zgUfopartA.Flip();
	//m_zpKIpartB.TranslateX(15.3F);
	m_zpSonne.AddPlacement(&m_zpKI);

	m_zgKIpartB.Init(1.2f, 1.f, &m_zmUfopartB);
	m_zpKIpartB.AddGeo(&m_zgKIpartB);
	m_zmKIpartB.MakeTextureDiffuse("textures\\green_image.jpg");
	//m_zpKIpartB.TranslateX(10.3F);
	m_zpSonne.AddPlacement(&m_zpKI);

	//------------
	//Satelit:
	//------------

	m_zpSatelit.TranslateY(10);
	m_zpSatelit.RotateY(90);

	m_zgSatelit.Init(CHVector(0.5f, 2.f, 0.5f), &m_zmSatelit);
	m_zpSatelit.AddGeo(&m_zgSatelit);
	m_zmSatelit.MakeTextureDiffuse("textures\\green_image.jpg");
	m_zpSonne.AddPlacement(&m_zpSatelit);
	m_zmSatelitOff.MakeTextureDiffuse("textures\\red_image.jpg");
	m_zr.AddMaterial(&m_zmSatelitOff);

}

void CGame::Tick(float fTime, float fTimeDelta) //-> ticks sind frame basiert -> mit gutem pc mit hoher framerate kann spiel beschleunigen -> deshalb kann maximale framerate angeben
{
	//-------------------------------------------
	// Veränderungen während der Simulationszeit:
	//-------------------------------------------

	// Hier kommen die Veränderungen pro Renderschritt hinein: 

	//Sonne
	m_zmSonne.RotateHue(fTime/5.0f);

	//Music
	m_zaMusic.Start();
	

	//Keyboard

	//m_zdKeyboard.PlaceWASD(m_zpCamera, fTimeDelta, false);
	//steuerung für andere ufos
	//m_zdKeyboard.PlaceWASD(m_zpCameraSplitL, fTimeDelta, false); //lieber andere? in single wird rakete für multi auch bewegt


	
	// zu kamera ran und weg zoomen mit Taste Z //-> geht nicht?
	if (m_zdKeyboard.KeyPressed(DIK_Z))
	{
		m_zc.SetFov(0.9F + 0.472F * sin(fTime));
	}

	/*
	//Controller
	m_zdController1.GetRelativeX();
	m_zdController1.GetRelativeY();
	m_zdController1.GetRelativeZ();
	m_zdController1.GetRelativeRX();
	m_zdController1.GetRelativeRY();
	m_zdController1.GetRelativeRZ();
	m_zdController1.SetSensitivity(0.0005F);
	*/

	//Cursor
	float fx, fy;
	m_zdc.GetFractional(fx, fy, true); //ob cursor im Frame
	if (m_zdc.ButtonPressedLeft()) //linke maustaste drücken = cursor wechseln -> schauen ob taste los gelassen
	{
		m_zoRocket.SwitchOff(); m_zoHand.SwitchOn();
		m_zoHand.SetPos(fx - 0.01F, fy - 0.01F);
	}
	else
	{
		m_zoRocket.SwitchOn(); m_zoHand.SwitchOff();
		m_zoRocket.SetPos(fx - 0.01F, fy - 0.01F);
	}

	//Todesstern auswählen (Mit array wählt alle gleichzeitig aus)
	if (m_zdc.ButtonUpLeft()) // schauen ob taste los gelassen
	{
		if (m_zdc.PickGeoPreselected(m_zgsPreselected) != nullptr) //wenn das preselected trifft
		{
			if (iCounter_Mat_Tod % 2 == 0) //wechselt zu rot
			{
				//m_azgDeathStars[i].SetMaterial(&m_zm_Tod_red);
			}
			else                          //wechstelt zurück
			{
				//m_azgDeathStars[i].SetMaterial(&m_zmDeathStar);
			}

			iCounter_Mat_Tod++;
		}
	}
	

	//CPlacement* PickPlacement(); //Wie pickup zum leuchten bringen
	//m_zpTod1.PickPlacement(CRay &x,0.1,0.1, ePlacementSearch_OnlyWithDirectGeos); //-> weiß nicht welche values

	//Erde
	m_zpErde.RotateY(fTime);
	//m_zpErde.RotateZDelta(0.24f); //für 2.1 schräglage
	m_zpErde.RotateZDelta(UM_DEG2RAD(24)); //alternative für schräglage
	m_zpCloud.RotateY(fTime * 0.12526); //wolken schneller drehen als erde -> sollte laut ihm RotateYDelta, aber dann so schnell

	//ErdeMond
	m_zpErdeMond.TranslateX(30.f);
	m_zpErdeMond.RotateYDelta(fTime * 0.1); //Warum so schnell?

	//Mond
	m_zpMond.TranslateX(5.f);
	m_zpMond.RotateYDelta(fTime * 0.5); //Warum so schnell?

	//Asteroidengürtel um Sonne
	for (int i = 0; i < NR_OF_STONES; i++)
	{
		m_azpStone[i].Translate(m_avStoneRand[i]);
		m_azpStone[i].RotateYDelta(m_avStoneRand[i].w * fTime);
		m_azpStone[i].RotateZDelta(UM_DEG2RAD(32)); //damit nicht waagerecht sondern mit winkel um sonne
	}

	//Nebel
	for (int i = 1; i < 5; i++)
	{
		m_azpNebula[i].SetBillboardAngle(fTime * i * 0.05f);
		m_azpNebula[i].SetBillboardScaling(1.5f + sinf(fTime * i * 0.07f), 1.5f + cosf(fTime * i * 0.07f));
	}

	//Ufo
	//m_zpUfo.Scale(5); //scaled, aber geht nur größßer, mit - dreht objekt + normals
	//m_zpUfo.TranslateX(5.f);
	//m_zpUfo.RotateZDelta(fTime * 2);

	//"KI-Gegner"
	m_zpKI.TranslateX(25.f);
	m_zpKI.RotateZDelta(fTime * 0.7);

	//Satelit
	m_zpSatelit.TranslateX(15.f);
	m_zpSatelit.RotateYDelta(fTime * 0.7);

	//--------------------
	//Todesstern
	/*
	m_zpTod1.TranslateZ(5.f);
	m_zpTod1.RotateYDelta(fTime * 0.5);

	//2
	m_zpTod2.TranslateZ(4.f);
	m_zpTod2.RotateYDelta(fTime * 9.5);

	//3
	m_zpTod3.TranslateX(6.f);
	m_zpTod3.RotateYDelta(fTime * 0.5);

	//4
	m_zpTod4.TranslateY(6.5);
	m_zpTod4.RotateXDelta(fTime * 1.5);

	//5
	m_zpTod5.TranslateZ(7.f);
	m_zpTod5.RotateYDelta(fTime * 3.5);

	//6
	m_zpTod6.TranslateZ(7.3);
	m_zpTod6.RotateYDelta(fTime * 7.5);

	//7
	m_zpTod7.TranslateZ(7.8);
	m_zpTod7.RotateXDelta(fTime * 0.5);

	//8
	m_zpTod8.TranslateX(8.1);
	m_zpTod8.RotateYDelta(fTime);

	//9
	m_zpTod9.TranslateZ(8.f);
	m_zpTod9.RotateZDelta(fTime * 0.1);

	//10
	m_zpTod10.TranslateY(8.4);
	m_zpTod10.RotateZDelta(fTime * 2);

	//11
	m_zpTod11.TranslateX(8.9);
	m_zpTod11.RotateYDelta(fTime * 5.5);

	//0 zum anklicken
	m_zpTod0.TranslateX(9.9);
	m_zpTod0.RotateYDelta(fTime * 0.5);
	*/


	//Todessterne als Array
	for (int i = 0; i < NR_OF_DEATHSTARS; i++)
	{
		m_azpDeathStar[i].Translate(m_avDeathStarRand[i]);
		m_azpDeathStar[i].RotateYDelta(m_avDeathStarRand[i].w * fTime);
		//m_azpStone[i].RotateZDelta(UM_DEG2RAD(32)); //damit nicht waagerecht sondern mit winkel um sonne
	}

	//Debug: Startbildschirm nur ausschalten mit O
	if (m_zdKeyboard.KeyPressed(DIK_O)) // schauen ob taste los gelassen
	{
		m_zoSingle.SwitchOff();
		m_zoMulty.SwitchOff();
		m_zoLogo.SwitchOff();
	}

	//Startbildschirm mit Buttons
	if (m_zdc.ButtonPressedLeft())
	{
		COverlay* pzo = m_zdc.PickOverlayPreselected(m_zos);
		if (pzo == &m_zoSingle && m_zdc.ButtonPressed(0))
		{
			m_zoSingle.SwitchOff();
			m_zoMulty.SwitchOff();
			m_zoLogo.SwitchOff();
			m_IsSinglePlayer = true;
			m_ingame = true;
		}

		if (pzo == &m_zoMulty && m_zdc.ButtonPressed(0))
		{
			m_zoSingle.SwitchOff();
			m_zoMulty.SwitchOff();
			m_zoLogo.SwitchOff();
			m_IsSinglePlayer = false;
			m_ingame = true;
		}
		//evtl lieber COverlay* pzos = ... -> also umbenennen statt wert zu überschreiben
		COverlay* pzoi = m_zdc.PickOverlayPreselected(m_zosInGame);
		//pzoi = m_zdc.PickOverlayPreselected(m_zosInGame);
		if (pzoi == &m_zoBack2Start && m_zdc.ButtonPressed(0))
		{
			m_IsSinglePlayer = true;
			m_zoSingle.SwitchOn();
			m_zoMulty.SwitchOn();
			m_zoLogo.SwitchOn();
			m_ingame = false;
		}
	}
	//Debug
	/* 
	if (m_zdKeyboard.KeyPressed(DIK_B))
	{
		
		m_zvSplitR.SwitchOff();
		m_zvSplitL.SwitchOff();
		
		m_zv.SwitchOn();
		
		m_IsSinglePlayer = true;
		m_zoSingle.SwitchOn();
		m_zoMulty.SwitchOn();
		m_zoLogo.SwitchOn();
		m_ingame = false;
	}
	*/

	//Reset
	if (m_ingame == false)
	{
		m_zwPointsL.SwitchOff();
		m_zwPointsR.SwitchOff();
		m_zwHealthL.SwitchOff();
		m_zwHealthR.SwitchOff();
		m_zwWinL.SwitchOff();
		m_zwLose.SwitchOff();
		m_iPointsL = 0;
		m_iPointsR = 0;
		m_iHealthL = 100;
		m_iHealthR = 100;
	}

	//Split Screen
	if (m_IsSinglePlayer == false)
	{
		//m_zdKeyboard.PlaceWASD(m_zpCameraSplitL, fTimeDelta, false); //Test andersrum
		m_zdKeyboard.PlaceWASD(m_zpSpaceshipML, fTimeDelta, false);
		m_zv.SwitchOff();
		m_zvSplitR.SwitchOn();
		m_zvSplitL.SwitchOn();
		m_zwPointsL.SwitchOn();
		m_zwPointsR.SwitchOn();
		m_zwHealthL.SwitchOn();
		m_zwHealthR.SwitchOn();
		m_zpSpaceshipS.SwitchOff();
		m_zpSpaceshipML.SwitchOn();
		m_zpSpaceshipMR.SwitchOn();
		m_zwWinL.SwitchOn();
		m_zwLose.SwitchOn();

		if (m_iPointsL >= 20)
		{
			//Spieler 1 hat gewonnen
			m_zwWinL.PrintF("%s", & m_cWon1);
		}
		else if (m_iPointsR >= 20)
		{
			//Spieler 2 hat gewonnen
			m_zwWinL.PrintF("%s", &m_cWon2);
		}
		else if (m_iHealthL <= 0 || m_iHealthR <= 0)
		{
			//Spieler verloren
			m_zwLose.PrintF("%s", &m_cLose);
		}

		//Neigen und Kamera drehen
		if (m_zdKeyboard.KeyPressed(DIK_A))
		{
			m_zpCameraSplitL.RotateYDelta(UM_DEG2RAD(2));
			m_zpSpaceshipML.RotateZDelta(UM_DEG2RAD(1));
			m_zpSpaceshipML.RotateYDelta(UM_DEG2RAD(1));

		}
		else if (m_zdKeyboard.KeyPressed(DIK_D))
		{
			m_zpCameraSplitL.RotateYDelta(UM_DEG2RAD(-2));
			m_zpSpaceshipML.RotateZDelta(UM_DEG2RAD(-1));
			m_zpSpaceshipML.RotateYDelta(UM_DEG2RAD(-1));
		}
		else
		{
			m_zpSpaceshipML.RotateZ(UM_DEG2RAD(0));
			m_zpSpaceshipML.RotateY(UM_DEG2RAD(0));
			m_zpSpaceshipML.TranslateZ(-10);
		}
	}

	if (m_IsSinglePlayer == true)
	{
		m_zdKeyboard.PlaceWASD(m_zpCamera, fTimeDelta, false); //Test andersrum
		//m_zdKeyboard.PlaceWASD(m_zpSpaceshipS, fTimeDelta, false);
		m_zvSplitR.SwitchOff();
		m_zvSplitL.SwitchOff();
		m_zv.SwitchOn();
		m_zwPointsL.SwitchOn();
		m_zwHealthL.SwitchOn();
		m_zpSpaceshipS.SwitchOn();
		m_zpSpaceshipML.SwitchOff();
		m_zpSpaceshipMR.SwitchOff();
		m_zwWinL.SwitchOn();
		m_zwLose.SwitchOn();

		if (m_iPointsL >= 20)
		{
			//Spieler hat gewonnen
			m_zwWinL.PrintF("%s", &m_cWon);
		}
		else if (m_iHealthL <= 0 || m_iHealthR <= 0)
		{
			//Spieler verloren
			m_zwLose.PrintF("%s", &m_cLose);
		}

		//Neigen und Kamera drehen
		if (m_zdKeyboard.KeyPressed(DIK_A))
		{
			m_zpCamera.RotateYDelta(UM_DEG2RAD(2));
			m_zpSpaceshipS.RotateZDelta(UM_DEG2RAD(1));
			m_zpSpaceshipS.RotateYDelta(UM_DEG2RAD(1));

		}
		else if (m_zdKeyboard.KeyPressed(DIK_D))
		{
			m_zpCamera.RotateYDelta(UM_DEG2RAD(-2));
			m_zpSpaceshipS.RotateZDelta(UM_DEG2RAD(-1));
			m_zpSpaceshipS.RotateYDelta(UM_DEG2RAD(-1));
		}
		else
		{
			m_zpSpaceshipS.RotateZDelta(UM_DEG2RAD(0));
			m_zpSpaceshipS.RotateYDelta(UM_DEG2RAD(0));
			m_zpSpaceshipS.TranslateZ(-10);
		}
	}
	
	

	//Bullets collision
	for (int i = 0; i < NR_OF_BULLETS; i++)
	{
		if (m_zpsBullets.m_applacement[i]->IsOn())
		{
			m_avBulletLastPos[i] = m_zpsBullets.m_applacement[i]->GetPosGlobal();
		}

		if (m_zpsEBullets.m_applacement[i]->IsOn())
		{
			m_avEBulletLastPos[i] = m_zpsEBullets.m_applacement[i]->GetPosGlobal();
		}
	}
	//Bullets aus Raumschiff
	if (m_zdKeyboard.KeyDown(DIK_SPACE))
	{
		if (m_zpsBullets.RingIsNotFull())
		{
			CPlacement* pzp = m_zpsBullets.RingInc();

			if (m_IsSinglePlayer == true)
			{
				pzp->SetMat(m_zpSpaceshipS.GetMatGlobal());		//startpunkt = selber wie Ufo
				//CHVector vDir = m_azpDeathStar[1].GetPosGlobal() - m_zpUfo.GetPosGlobal();
				//CHVector vDir(m_zpSpaceshipS.GetDirection());
				CHVector vDir = m_zpSpaceshipS.GetPosGlobal() - m_zpCamera.GetPosGlobal();
				vDir.Normal();
				pzp->SetPhysicsVelocity(vDir * 100.0f);
			}

			else if (m_IsSinglePlayer == false)
			{
				pzp->SetMat(m_zpSpaceshipML.GetMatGlobal());		//startpunkt = selber wie Ufo
				//CHVector vDir = m_azpDeathStar[1].GetPosGlobal() - m_zpUfo.GetPosGlobal();
				//CHVector vDir(m_zpSpaceshipML.GetDirection());
				CHVector vDir = m_zpSpaceshipML.GetPosGlobal() - m_zpCameraSplitL.GetPosGlobal();
				vDir.Normal();
				pzp->SetPhysicsVelocity(vDir * 100.0f);
			}
			
			//m_azgDeathStars->SwitchCollisionGroundOn();
			
			m_azaGunShot[m_zpsBullets.m_uRingStart].Start(); //gushot sound starten
		}
	}
	
	CPlacement* pzpOldestBullet = m_zpsBullets.RingAskLast();
	if (pzpOldestBullet)
		if (pzpOldestBullet->GetPos().Length() > 100.0f)      //ab wie viel meter despawnt
			m_zpsBullets.RingDec();

	
	
	//Enemy Bullets (War mal von Todesstern, aber mache jetzt von "KI-Gegner"
	static float s_fSpawn = 30.0f;
	m_azgDeathStars[1].SetMaterial(&m_zm_Tod_red);
	if (m_zr.IsTime(s_fSpawn)) // oder Tickabhängig -> GetTick() % 50 == 0)
	{
		s_fSpawn += 5.0f; 
		if (m_zpsEBullets.RingIsNotFull())
		{

			CPlacement* pzpE = m_zpsEBullets.RingInc();
			pzpE->SetMat(m_zpKI.GetMatGlobal());		//startpunkt = selber wie Todesstern -> jetzt KI


			if ((who % 3) == 0) //Zielt aud Sonne
			{
				CHVector vDirE = m_zpSonne.GetPosGlobal() - m_zpKI.GetPosGlobal();
				vDirE.Normal();
				pzpE->SetPhysicsVelocity(vDirE * 10.0f);

				who++;
			}

			else if ((who % 3) != 0) //Zielt auf uns
			{
				if (m_IsSinglePlayer == true)
				{
					CHVector vDirE = m_zpSpaceshipS.GetPosGlobal() - m_zpKI.GetPosGlobal();
					vDirE.Normal();
					pzpE->SetPhysicsVelocity(vDirE * 10.0f);
				}

				else if (m_IsSinglePlayer == false)
				{
					CHVector vDirE = m_zpSpaceshipML.GetPosGlobal() - m_zpKI.GetPosGlobal();
					vDirE.Normal();
					pzpE->SetPhysicsVelocity(vDirE * 10.0f);
				}

				who++;
			}
			
			
		}
	}
	CPlacement* pzpOldestBulletE = m_zpsEBullets.RingAskLast();
	if (pzpOldestBulletE)
		if (pzpOldestBulletE->GetPos().Length() > 100.0f)      //ab wie viel meter despawnt
			m_zpsEBullets.RingDec();
	
	
	

	// Lass die Kugel rotieren: (kopiert aus TestApp)
	//m_zpSphere.RotateY(-fTime);
	//m_zpSphere.RotateXDelta(0.8f * sinf(fTime * 0.2f));

	// Lass die Kamera in 7 Metern Abstand zur Kugel rotieren: (Kopiert aus TestApp -> nicht gefordert)
	//m_zpCamera.TranslateZ(7.0f);
	//m_zpCamera.RotateYDelta(fTime * 0.1f);

	// Traversiere am Schluss den Szenengraf und rendere:
	m_zr.Tick(fTimeDelta);

	//für bullet collision
	for (int i = 0; i < NR_OF_BULLETS; i++)
	{
		if (m_zpsBullets.m_applacement[i]->IsOn())
		{
			CRay rayHitEn; //Wir haben Enemy getroffen
			rayHitEn.InitFromTo(m_avBulletLastPos[i], m_zpsBullets.m_applacement[i]->GetPosGlobal());
			CHitPoint hitEn;
			if (m_zgKIpartA.Intersects(rayHitEn, hitEn))
			{
				//m_zgSonne.SwitchOff();
				m_zaHit.Start();
				m_iPointsL += 10;
				//m_iHealthL -= 10;
			}
		}
		m_zwPointsL.PrintF("%i", m_iPointsL);
		//m_zwHealthL.PrintF("%i", m_iHealthL);
		if (m_zpsEBullets.m_applacement[i]->IsOn())
		{
			CRay rayHitWe; //Enemy hat Sonne oder uns getroffen
			rayHitWe.InitFromTo(m_avEBulletLastPos[i], m_zpsEBullets.m_applacement[i]->GetPosGlobal());
			CHitPoint hit;
			if (m_zgSonne.Intersects(rayHitWe, hit))
			{
				//m_zgSonne.SwitchOff();
				m_zaHit.Start();
				m_iHealthL -= 10;
			}
			if (m_zgWeS.Intersects(rayHitWe, hit) || m_zgWeML.Intersects(rayHitWe, hit))
			{
				m_iPointsL -= 2;
			}
			if (m_zgWeMR.Intersects(rayHitWe, hit))
			{
				m_iPointsR -= 2;
			}
		}
		m_zwHealthL.PrintF("%i", m_iHealthL);
		m_zwPointsL.PrintF("%i", m_iPointsL);
		m_zwPointsR.PrintF("%i", m_iPointsR);

		if (m_bSatelitOn == true)
		{
			CRay raySat;
			raySat.InitFromTo(m_zpSpaceshipS.GetPosGlobal(), m_zpSonne.GetPosGlobal());
			CHitPoint hitSat;
			if (m_zgSatelit.Intersects(raySat, hitSat))
			{
				m_iHealthL += 5;
				m_bSatelitOn = false;
				m_zgSatelit.SetMaterial(&m_zmSatelitOff);
			}
			
		}
		static float s_fDelay = fTimeDelta + 20;
		if (fTimeDelta >= s_fDelay)
		{
			m_bSatelitOn = true;
			m_zgSatelit.SetMaterial(&m_zmSatelit);
		}

		CRay rayNeb;
		rayNeb.InitFromTo(m_zpSpaceshipS.GetPosGlobal(), m_zpSonne.GetPosGlobal());
		CHitPoint hitNeb;
		if (m_zgNebula.Intersects(rayNeb, hitNeb))
		{
			/*CHVector vRand;
			vRand.RandomDir();
			vRand += CHVector(0.0f, 2.0f, 0.0f, 0.0f);*/
			m_zpCamera.SetMat(m_zpErde.GetMatGlobal());
			//m_zpSpaceshipS.SetMat(m_zpErde.GetMatGlobal());
		}

		
	}


}

void CGame::Fini()
{
	//-------------------------------
	// Finalisiere die Knotenobjekte:
	//-------------------------------

	// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:

	// Auch die Root sollte finalisiert werden:   
	m_zr.Fini();
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
	// Hier kannst Du dann die Auflösung des Viewports neu einstellen:
	// z.B. mittels: m_zf.ReSize(iNewWidth, iNewHeight);
	//hier meins eingefügt:
	// resize des objekts nachdem fenster grösse geändert -> auch für Cursor essentiell
	m_zf.ReSize(iNewWidth, iNewHeight);
}

float CGame::GetTimeDeltaMin()
{
	return m_zr.GetTimeDeltaMin();
}

float CGame::GetVersion()
{
	return m_zr.GetVersion();
}


