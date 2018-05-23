#include "stdafx.h"
#include "VertexTest.h"

DWORD VertexTest::Vertex::fvf = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;

//fvf(Flexible Vertex Format) : ������ ���� ����
//������ ���� �� �ڽ��� �����ϴ� ���α׷��� �˸��� �͵�� ���
//���ο� ������ ����� ��
//D3DFVF_XYZ : 3���� ��ǥ ü���� ���� ����
//D3DFVF_XYZRHW : 2���� ���������� ���� ��ǥ
//��ġ��ȯ : 3���� ���� ��ǥ�� ȭ�� ���� 2���� ��ǥ�� ��ȯ�ϴ� ����
//��ġ��ǥ : ��ġ��ȯ�� ���� �� ���� ��ǥ
//W : ��ġ��ǥ�� �׹� ° ����
//RHW(Reciprocal Homogeneous W);
//Perspective��ȯ ����� �����ϸ� x, y, z, w��� ǥ��
//��ũ���� ����Ϸ��� w�� ���� ������ ǥ���ؾ� ��.
//RHW �� w�� ������.

//������(Polygon) : ����3���� �̷� ��
//�ð� ������ �������� �ؼ� ���鿡���� �� �� �ִ�.
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
	//���콺 ���
	//if(MOUSE->ButtonDown(1))
	//MOUSE->GetPosition().x;

	DEVICE->SetFVF(Vertex::fvf);

	//���׸���
	//DEVICE->DrawPrimitiveUP(D3DPT_POINTLIST, 1, vertex, sizeof(Vertex));

	//���׸���
	//DEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP, 3, vertex, sizeof(Vertex));

	//��� �ɼ�
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//��׸���(�ﰢ��)
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(Vertex));
}
