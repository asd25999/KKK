#include "stdafx.h"
#include "AlphaTest.h"

AlphaTest::AlphaTest()
{
	//camera = new Camera();

	//mario = Texture::Add(L"Image/mario_all.png", 5, 3, 8, 4);
	mario = Texture::Add(L"Image/rocket.png");
	bg = Texture::Add(L"Image/mario_bg.png");

	D3DXVECTOR2 bgSize;
	bg->GetRealSize(&bgSize);
	D3DXVECTOR2 bgScale;
	bgScale.x = WIN_WIDTH / bgSize.x;
	bgScale.y = WIN_HEIGHT / bgSize.y;
	D3DXMatrixScaling(&bgWorld, bgScale.x, bgScale.y, 1.0f);	
}

AlphaTest::~AlphaTest()
{
}

void AlphaTest::Update()
{
	if (KEYBOARD->KeyPress(VK_RIGHT))
	{
		marioPos.x++;
	}
	if (KEYBOARD->KeyPress(VK_LEFT))
	{
		marioPos.x--;
	}
	if (KEYBOARD->KeyPress(VK_UP))
	{
		marioPos.y--;
	}
	if (KEYBOARD->KeyPress(VK_DOWN))
	{
		marioPos.y++;
	}

	D3DXMatrixTranslation(&marioWorld, marioPos.x,
		marioPos.y, 0.0f);

	//camera->Update();
}

void AlphaTest::Render()
{
	Device::SetWorld(&bgWorld);
	bg->Render();
	Device::SetWorld(&marioWorld);
	//���� ������ �����ϰڴ�!
	//DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	////���� ������ �ϴµ� �������� �����ϰڴ�!
	//DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	////DEST : ��� ����(�Ѹ� ���� �ڿ� �ִ� ��)
	////SRC : �Ѹ� ����
	////SRCALPHA : �Ѹ� ������ ���İ�
	////INVSRCALPHA : 1 - SRCALPHA	

	////��� ���� �Ѹ� �̹����� ���Ŀ� ������ ���ϰڴ�.
	//DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	////�Ѹ� ���� �ڱ� ���� ���� ���ϰڴ�.
	//DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device::StartAlphaRender();
	mario->Render();
	Device::EndAlphaRender();

	//���Ŀ����� �����ϰڴ�.
	//DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
