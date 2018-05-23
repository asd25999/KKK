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
	//알파 연산을 시작하겠다!
	//DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	////알파 연산을 하는데 덧셈으로 연산하겠다!
	//DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	////DEST : 배경 색깔(뿌릴 색깔 뒤에 있는 색)
	////SRC : 뿌릴 색깔
	////SRCALPHA : 뿌릴 색깔의 알파값
	////INVSRCALPHA : 1 - SRCALPHA	

	////배경 색에 뿌릴 이미지의 알파에 역수를 곱하겠다.
	//DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	////뿌릴 색에 자기 알파 값을 곱하겠다.
	//DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device::StartAlphaRender();
	mario->Render();
	Device::EndAlphaRender();

	//알파연산을 종료하겠다.
	//DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
