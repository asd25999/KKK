#pragma once 
#include "Window.h"
#include "VertexTest.h"
#include "PaintTest.h"
#include "VertexBufferTest.h"
#include "WVPTest.h"
#include "TextureTest.h"
#include "SliceTest.h"
#include "SRTTest.h"
#include "AlphaTest.h"
#include "AniTest.h"
#include "XmlTest.h"

class GameMain : public Window
{
private:
	Test * test;
public:
	GameMain(HINSTANCE instance);
	~GameMain();

	void Initialize();
	void Destroy();
	void Update();
	void Render();	
};