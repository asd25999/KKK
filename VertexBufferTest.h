#pragma once

class VertexBufferTest : public Test
{
private:
	struct Vertex
	{
		D3DXVECTOR4 position;
		DWORD color;

		static DWORD fvf;
	};

	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	Vertex* vertex;
	UINT vertexCount;
	float speed;
public:
	VertexBufferTest();
	~VertexBufferTest();

	void Update();
	void Render();
};