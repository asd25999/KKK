#pragma once

class TextureTest : public Test
{
private:
	struct Vertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 uv;

		static DWORD fvf;

		Vertex() {}
		Vertex(float x, float y, float u, float v)
		{
			position = { x, y, 0 };
			uv = { u, v };
		}
	};

	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	Vertex* vertex;
	UINT vertexCount;

	D3DXVECTOR2 worldPos;	
	D3DXVECTOR2 cameraPos;

	D3DXMATRIX world;	
	D3DXMATRIX view;
	D3DXMATRIX projection;

	LPDIRECT3DTEXTURE9 texture;
public:
	TextureTest();
	~TextureTest();

	void Update();
	void Render();
};