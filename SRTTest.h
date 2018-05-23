#pragma once

class SRTTest : public Test
{
private:
	Texture * texture;

	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;
	D3DXVECTOR2 translation;

	D3DXMATRIX world;
	D3DXMATRIX projection;

	float speed;

public:
	SRTTest();
	~SRTTest();

	void Update();
	void Render();
};