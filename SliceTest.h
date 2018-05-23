#pragma once

class SliceTest : public Test
{
private:
	Texture * image;

	D3DXMATRIX projection;
public:
	SliceTest();
	~SliceTest();

	void Update();
	void Render();
};