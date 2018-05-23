#pragma once

class WVPTest : public Test
{
private:
	struct Vertex
	{
		D3DXVECTOR3 position;
		DWORD color;

		static DWORD fvf;
	};

	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	Vertex* vertex;
	UINT vertexCount;

	D3DXVECTOR2 worldPos;
	D3DXVECTOR2 worldPos2;
	D3DXVECTOR2 cameraPos;

	D3DXMATRIX world;
	D3DXMATRIX world2;
	D3DXMATRIX view;
	D3DXMATRIX projection;

public:
	WVPTest();
	~WVPTest();

	void Update();
	void Render();
};