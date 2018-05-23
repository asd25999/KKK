#include "stdafx.h"
#include "WVPTest.h"
//랜더링 파이프 라인
// - 3D로 만들어진 정점3개로 이루어진 폴리곤 그리고 폴곤들이 모여서
//만들어진 매쉬가 사용자가 보는 화면에 2D로 뿌려주기 위해 거쳐야 하는 과정

DWORD WVPTest::Vertex::fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;
//1.월드 변환(World Transform)
// - 정점들의 좌표가 담긴 로컬좌표를 움직이고 표현이 될
//월드에 뿌려주기 위해서 거치는 과정

//2.뷰 변환(View Transform)
//- 월드좌표상에 시점을 배치해 정점을 카메라 공간에
//변환하는 과정

//투영 변환(Proejction Transform)
//뷰 변환까지 다 마친 상태에서 카메라가 비추는 화면을
//사용자가 보는 화면으로 표현하는 과정

WVPTest::WVPTest()
{
	vertexCount = 6;
	worldPos = { 100, 100 };
	worldPos2 = { 0, 0 };
	cameraPos = { 0, 0 };
	
	vertex = new Vertex[vertexCount];
	vertex[0].position = { 0, 0, 0 };
	vertex[0].color = COLOR_R;
	vertex[1].position = { 100, 0, 0 };
	vertex[1].color = COLOR_G;
	vertex[2].position = { 100, 100, 0 };
	vertex[2].color = COLOR_B;
	vertex[3].position = { 100, 100, 0 };
	vertex[3].color = COLOR_B;
	vertex[4].position = { 0, 100, 0 };
	vertex[4].color = COLOR_W;
	vertex[5].position = { 0, 0, 0 };
	vertex[5].color = COLOR_R;

	UINT vertexSize = sizeof(Vertex) * vertexCount;
	DEVICE->CreateVertexBuffer(vertexSize, 0, Vertex::fvf,
		D3DPOOL_DEFAULT, &vertexBuffer, NULL);

	void* vertexData = NULL;
	vertexBuffer->Lock(0, vertexSize, &vertexData, NULL);
	memcpy(vertexData, vertex, vertexSize);
	vertexBuffer->Unlock();

	//D3DXMatrixIdentity : 행렬을 항등(단위)행렬로 만들어 주는 함수
	//11 12 13 14
	//21 22 23 24
	//31 32 33 34
	//41 42 43 44

	//41, 42, 43 : 위치
	//11, 22, 33 : 크기
	//(22, 23, 32, 33) : x축 회전
	//(11, 21, 13, 23) : y축 회전
	//(11, 21, 12, 22) : z축 회전
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
}

WVPTest::~WVPTest()
{
}

void WVPTest::Update()
{
	D3DXMatrixTranslation(&world, worldPos.x, worldPos.y,
		0.0f);

	if (KEYBOARD->KeyPress(VK_RIGHT))
	{
		worldPos2.x++;
	}
	if (KEYBOARD->KeyPress(VK_LEFT))
	{
		worldPos2.x--;
	}
	if (KEYBOARD->KeyPress(VK_UP))
	{
		worldPos2.y--;
	}
	if (KEYBOARD->KeyPress(VK_DOWN))
	{
		worldPos2.y++;
	}

	D3DXMatrixTranslation(&world2, worldPos2.x,
		worldPos2.y, 0.0f);

	if (KEYBOARD->KeyPress('D'))
	{
		cameraPos.x++;
	}
	if (KEYBOARD->KeyPress('A'))
	{
		cameraPos.x--;
	}
	if (KEYBOARD->KeyPress('W'))
	{
		cameraPos.y--;
	}
	if (KEYBOARD->KeyPress('S'))
	{
		cameraPos.y++;
	}

	D3DXMatrixTranslation(&view, cameraPos.x, cameraPos.y,
		0.0f);
}

void WVPTest::Render()
{
	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);	
	DEVICE->SetFVF(Vertex::fvf);

	DEVICE->SetTransform(D3DTS_VIEW, &view);

	DEVICE->SetTransform(D3DTS_WORLD, &world);
	DEVICE->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	DEVICE->SetTransform(D3DTS_WORLD, &world2);
	DEVICE->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}
