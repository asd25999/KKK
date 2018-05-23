#pragma once

class XmlTest : public Test
{
private:
	Player * player;	
	TigerBoy* tigerBoy;

	MainCamera* camera;
public:
	XmlTest();
	~XmlTest();
	
	void Update();
	void Render();
};