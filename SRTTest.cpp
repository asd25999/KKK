#include "stdafx.h"
#include "SRTTest.h"

SRTTest::SRTTest()
{
	texture = Texture::Add(L"Image/test.jpg", { 200, 30 },
		{ 450, 370 });
	scale = { 1.0f, 1.0f };
	rotation = { 0, 0, 0 };
	translation = { 0, 0 };

	D3DXMatrixIdentity(&world);

	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);

	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f,
		viewport.Width, viewport.Height, 0.0f, -1, 1);

	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	speed = 10;
}

SRTTest::~SRTTest()
{
}

void SRTTest::Update()
{
	if (KEYBOARD->KeyPress(VK_RIGHT))
	{
		translation.x += speed;
		rotation.y = 0;
	}
	if (KEYBOARD->KeyPress(VK_LEFT))
	{
		translation.x -= speed;
		rotation.y = Math::PI;
	}
	if (KEYBOARD->KeyPress(VK_UP))
	{
		translation.y -= speed;
		rotation.x = Math::PI;
	}
	if (KEYBOARD->KeyPress(VK_DOWN))
	{
		translation.y += speed;
		rotation.x = 0;
	}

	if (KEYBOARD->KeyPress('D'))
	{
		scale.x += 0.1f;
	}
	if (KEYBOARD->KeyPress('A'))
	{
		scale.x -= 0.1f;
	}
	if (KEYBOARD->KeyPress('W'))
	{
		scale.y -= 0.1f;
	}
	if (KEYBOARD->KeyPress('S'))
	{
		scale.y += 0.1f;
	}

	if (KEYBOARD->KeyPress(VK_PRIOR))
	{
		rotation.z += 0.01f;
	}
	if (KEYBOARD->KeyPress(VK_NEXT))
	{
		rotation.z -= 0.01f;
	}

	//이미지 크기 구하는 방법
	D3DXVECTOR2 imageSize;
	texture->GetRealSize(&imageSize);
	//scale.x = WIN_WIDTH / imageSize.x;
	//scale.y = WIN_HEIGHT / imageSize.y;

	D3DXVECTOR2 center;
	center = imageSize * 0.5f;

	D3DXMATRIX S;
	D3DXMATRIX R;
	D3DXMATRIX T;	
		
	D3DXMATRIX matCenter;
	D3DXMATRIX matInvCenter;

	D3DXMatrixTranslation(&matCenter, center.x, center.y, 0.0f);
	//Inverse : 역행렬을 구하는 함수
	D3DXMatrixInverse(&matInvCenter, NULL, &matCenter);

	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, scale.x, scale.y, 1.0f);
	S = matInvCenter * matScale * matCenter;
	//z축만 회전할 때
	//D3DXMatrixRotationZ(&R, rotation.z);
	D3DXMATRIX matRotation;
	D3DXMatrixRotationYawPitchRoll(&matRotation, rotation.y, rotation.x,
		rotation.z);

	R = matInvCenter * matRotation * matCenter;

	D3DXMatrixTranslation(&T, translation.x,
		translation.y, 0.0f);
	
	//메트릭스 연산 순서는 바뀌면 안된다!
	//곱셈 연산은 교환법칙이 성립하지 않기 때문
	world = S * R * T;
}

void SRTTest::Render()
{
	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);

	DEVICE->SetTransform(D3DTS_WORLD, &world);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	texture->Render();
}
