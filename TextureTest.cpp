#include "stdafx.h"
#include "TextureTest.h"

DWORD TextureTest::Vertex::fvf = D3DFVF_XYZ |
D3DFVF_TEX1;

TextureTest::TextureTest()
{
	vertexCount = 6;
	worldPos = { 100, 100 };	
	cameraPos = { 0, 0 };

	vertex = new Vertex[vertexCount];
	vertex[0] = Vertex(0, 0, 0, 0);
	vertex[1] = Vertex(500, 0, 0.5f, 0);
	vertex[2] = Vertex(0, 500, 0, 0.5f);
	vertex[3] = Vertex(0, 500, 0, 0.5f);
	vertex[4] = Vertex(500, 0, 0.5f, 0);
	vertex[5] = Vertex(500, 500, 0.5f, 0.5f);

	UINT vertexSize = sizeof(Vertex) * vertexCount;
	DEVICE->CreateVertexBuffer(vertexSize, 0, Vertex::fvf,
		D3DPOOL_DEFAULT, &vertexBuffer, NULL);

	void* vertexData = NULL;
	vertexBuffer->Lock(0, vertexSize, &vertexData, NULL);
	memcpy(vertexData, vertex, vertexSize);
	vertexBuffer->Unlock();
	
	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&projection);

	//D3DVIEWPORT9 : 뷰(카메라) 정보를 가지고 있는 구조체
	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);

	//프로잭션을 생성하는 함수
	D3DXMatrixOrthoOffCenterLH(&projection,
		0.0f, viewport.Width, viewport.Height, 0.0f,
		-1, 1);

	//검은색 조명을 끄기
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	D3DXIMAGE_INFO info;
	D3DXCreateTextureFromFileEx(DEVICE,
		L"Image/test.jpg",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		1,
		NULL,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		0,
		&info,
		NULL,
		&texture
	);
}

TextureTest::~TextureTest()
{
}

void TextureTest::Update()
{
}

void TextureTest::Render()
{
	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);
	DEVICE->SetFVF(Vertex::fvf);

	DEVICE->SetTransform(D3DTS_VIEW, &view);

	DEVICE->SetTransform(D3DTS_WORLD, &world);

	DEVICE->SetTexture(0, texture);
	DEVICE->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}
