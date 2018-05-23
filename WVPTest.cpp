#include "stdafx.h"
#include "WVPTest.h"
//������ ������ ����
// - 3D�� ������� ����3���� �̷���� ������ �׸��� ������� �𿩼�
//������� �Ž��� ����ڰ� ���� ȭ�鿡 2D�� �ѷ��ֱ� ���� ���ľ� �ϴ� ����

DWORD WVPTest::Vertex::fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;
//1.���� ��ȯ(World Transform)
// - �������� ��ǥ�� ��� ������ǥ�� �����̰� ǥ���� ��
//���忡 �ѷ��ֱ� ���ؼ� ��ġ�� ����

//2.�� ��ȯ(View Transform)
//- ������ǥ�� ������ ��ġ�� ������ ī�޶� ������
//��ȯ�ϴ� ����

//���� ��ȯ(Proejction Transform)
//�� ��ȯ���� �� ��ģ ���¿��� ī�޶� ���ߴ� ȭ����
//����ڰ� ���� ȭ������ ǥ���ϴ� ����

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

	//D3DXMatrixIdentity : ����� �׵�(����)��ķ� ����� �ִ� �Լ�
	//11 12 13 14
	//21 22 23 24
	//31 32 33 34
	//41 42 43 44

	//41, 42, 43 : ��ġ
	//11, 22, 33 : ũ��
	//(22, 23, 32, 33) : x�� ȸ��
	//(11, 21, 13, 23) : y�� ȸ��
	//(11, 21, 12, 22) : z�� ȸ��
	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&projection);

	//D3DVIEWPORT9 : ��(ī�޶�) ������ ������ �ִ� ����ü
	D3DVIEWPORT9 viewport;	
	DEVICE->GetViewport(&viewport);

	//��������� �����ϴ� �Լ�
	D3DXMatrixOrthoOffCenterLH(&projection,
		0.0f, viewport.Width, viewport.Height, 0.0f,
		-1, 1);	

	//������ ������ ����
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
