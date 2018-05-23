#include "stdafx.h"
#include "VertexBufferTest.h"

//버텍스버퍼(VertexBuffer)
// - 사용자 정의 탑의 버텍스 정보들을 담고 있는 버퍼
// - 버텍스 데이터를 보관하는 연속적인 메모리 저장 공간
// - 비디오 메모리에 버퍼를 저장하는데 시스템 메모리 데이터를
// 랜더링 하는 것 보다 비디오 메모리를 랜더링 하는 것이 훨씬
// 빠르므로 배열 대신 버퍼를 사용한다.


DWORD VertexBufferTest::Vertex::fvf
= D3DFVF_XYZRHW | D3DFVF_DIFFUSE;

VertexBufferTest::VertexBufferTest()
{
	vertexCount = 6;

	vertex = new Vertex[vertexCount];

	vertex[0].position = { 100, 100, 0, 1};
	vertex[0].color = COLOR_R;

	vertex[1].position = { 200, 100, 0, 1 };
	vertex[1].color = COLOR_B;

	vertex[2].position = { 200, 200, 0, 1 };
	vertex[2].color = COLOR_G;

	vertex[3].position = { 200, 200, 0, 1 };
	vertex[3].color = COLOR_G;

	vertex[4].position = { 100, 200, 0, 1 };
	vertex[4].color = COLOR_W;

	vertex[5].position = { 100, 100, 0, 1 };
	vertex[5].color = COLOR_R;

	UINT vertexSize = sizeof(Vertex) * vertexCount;
	DEVICE->CreateVertexBuffer(vertexSize, 0,
		Vertex::fvf, D3DPOOL_DEFAULT, &vertexBuffer, NULL);
	
	void* vertexData = NULL;
	//Lock : 데이터 공간을 확보하는 함수
	vertexBuffer->Lock(0, vertexSize, &vertexData, NULL);
	memcpy(vertexData, vertex, vertexSize);
	vertexBuffer->Unlock();
	//Unlock : 확보한 데이터를 랜더링 하기위해 사용
	//SAFE_DELETE_ARRAY(vertex);
	speed = 5.0f;
}

VertexBufferTest::~VertexBufferTest()
{
}

void VertexBufferTest::Update()
{
	/*
	if (KEYBOARD->KeyPress(VK_RIGHT))
	{
		for (int i = 0; i < vertexCount; i++)
		{
			vertex[i].position.x += speed;
		}
	}

	if (KEYBOARD->KeyPress(VK_LEFT))
	{
		for (int i = 0; i < vertexCount; i++)
		{
			vertex[i].position.x -= speed;
		}
	}

	if (KEYBOARD->KeyPress(VK_UP))
	{
		for (int i = 0; i < vertexCount; i++)
		{
			vertex[i].position.y -= speed;
		}
	}

	if (KEYBOARD->KeyPress(VK_DOWN))
	{
		for (int i = 0; i < vertexCount; i++)
		{
			vertex[i].position.y += speed;
		}
	}*/
	/*
	//모든 정점 움직이기
	UINT vertexSize = sizeof(Vertex) * vertexCount;
	void* vertexData = NULL;
	vertexBuffer->Lock(0, vertexSize, &vertexData, NULL);
	memcpy(vertexData, vertex, vertexSize);
	vertexBuffer->Unlock();
	*/

	int moveIndex = 3;

	if (KEYBOARD->KeyPress(VK_RIGHT))
	{
		vertex[moveIndex].position.x += speed;
	}
	if (KEYBOARD->KeyPress(VK_LEFT))
	{
		vertex[moveIndex].position.x -= speed;
	}
	//정점 하나 움직이기
	UINT start = sizeof(Vertex) * moveIndex;
	void* vertexData = NULL;
	vertexBuffer->Lock(start, sizeof(Vertex), &vertexData, NULL);
	memcpy(vertexData, &vertex[moveIndex], sizeof(Vertex));
	vertexBuffer->Unlock();
}

void VertexBufferTest::Render()
{
	DEVICE->SetFVF(Vertex::fvf);
	DEVICE->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));

	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}
