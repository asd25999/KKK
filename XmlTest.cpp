#include "stdafx.h"
#include "XmlTest.h"

XmlTest::XmlTest()
{
	player = new Player;	
	tigerBoy = new TigerBoy;
	//CAMERA->SetFreeCamera();
	//CAMERA->SetFollowCamera();
	//CAMERA->ChangeSpotPoint(player);
}

XmlTest::~XmlTest()
{
	SAFE_DELETE(player);
	//SAFE_DELETE(camera);
}

void XmlTest::Update()
{
	player->Update();
	//camera->Update();
	tigerBoy->Update();

	CAMERA->Update();
}

void XmlTest::Render()
{
	player->Render();
	tigerBoy->Render();
}
