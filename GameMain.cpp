#include "stdafx.h"
#include "GameMain.h"

GameMain::GameMain(HINSTANCE instance)
	: Window(instance)
{

}

GameMain::~GameMain()
{

}

void GameMain::Initialize()
{
	//test = new VertexTest();
	//test = new PaintTest();
	//test = new VertexBufferTest;
	//test = new WVPTest;
	//test = new TextureTest;
	//test = new SliceTest;
	//test = new SRTTest;
	//test = new AlphaTest;
	//test = new AniTest;
	test = new XmlTest;
}

void GameMain::Destroy()
{
	
}

void GameMain::Update()
{
	test->Update();
}

void GameMain::Render()
{
	test->Render();
}
