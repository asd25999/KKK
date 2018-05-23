#pragma once

class AlphaTest : public Test
{
private:
	Camera * camera;
	Texture* mario;
	Texture* bg;
	
	D3DXVECTOR2 marioPos;
	D3DXMATRIX marioWorld;
	D3DXMATRIX bgWorld;

public:
	AlphaTest();
	~AlphaTest();

	void Update();
	void Render();
};