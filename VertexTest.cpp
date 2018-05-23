#include "stdafx.h"
#include "VertexTest.h"

DWORD VertexTest::Vertex::fvf = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;

//fvf(Flexible Vertex Format) : 유연한 정점 포멧
//정점의 포멧 중 자신이 제작하는 프로그램에 알맞은 것들로 모아
//새로운 포멧을 만드는 것
//D3DFVF_XYZ : 3차원 좌표 체계의 정점 정보
//D3DFVF_XYZRHW : 2차원 공간에서의 정점 좌표
//동치변환 : 3차원 상의 좌표를 화면 상의 2차원 좌표로 변환하는 과정
//동치좌표 : 동치변환을 했을 때 나온 좌표
//W : 동치좌표의 네번 째 성분
//RHW(Reciprocal Homogeneous W);
//Perspective변환 행렬을 정용하면 x, y, z, w라고 표시
//스크린에 출력하려면 w를 나눈 값으로 표현해야 함.
//RHW 는 w의 역수다.

//폴리곤(Polygon) : 정점3개로 이룬 면
//시계 방향을 정면으로 해서 정면에서만 볼 수 있다.
VertexTest::VertexTest()
{
	vertex = new Vertex[4];

	vertex[0].position = { 100, 100, 0, 1 };
	vertex[0].color = 0xFFFF0000;

	vertex[1].position = { 200, 100, 0, 1 };
	vertex[1].color = 0xFF0000FF;

	vertex[2].position = { 100, 200, 0, 1 };
	vertex[2].color = 0xFF00FF00;

	vertex[3].position = { 200, 200, 0, 1 };
	vertex[3].color = 0xFFFFFF00;

	speed = 5.0f;
}

VertexTest::~VertexTest()
{
	SAFE_DELETE_ARRAY(vertex);
}

void VertexTest::Update()
{
	if (KEYBOARD->KeyPress(VK_RIGHT))
	{
		for (int i = 0; i < 4; i++)
		{
			vertex[i].position.x += speed;
		}
	}
	if (KEYBOARD->KeyPress(VK_LEFT))
	{
		for (int i = 0; i < 4; i++)
		{
			vertex[i].position.x -= speed;
		}
	}
	if (KEYBOARD->KeyPress(VK_UP))
	{
		for (int i = 0; i < 4; i++)
		{
			vertex[i].position.y -= speed;
		}
	}

	if (KEYBOARD->KeyPress(VK_DOWN))
	{
		for (int i = 0; i < 4; i++)
		{
			vertex[i].position.y += speed;
		}
	}
}

void VertexTest::Render()
{
	//마우스 사용
	//if(MOUSE->ButtonDown(1))
	//MOUSE->GetPosition().x;

	DEVICE->SetFVF(Vertex::fvf);

	//점그리기
	//DEVICE->DrawPrimitiveUP(D3DPT_POINTLIST, 1, vertex, sizeof(Vertex));

	//선그리기
	//DEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP, 3, vertex, sizeof(Vertex));

	//양면 옵션
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//면그리기(삼각형)
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(Vertex));
}
