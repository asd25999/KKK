#include "stdafx.h"
#include "SliceTest.h"

SliceTest::SliceTest()
{
	image = Texture::Add(L"Image/test.jpg");

	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);

	//프로잭션을 생성하는 함수
	D3DXMatrixOrthoOffCenterLH(&projection,
		0.0f, viewport.Width, viewport.Height, 0.0f,
		-1, 1);

	//검은색 조명을 끄기
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
}

SliceTest::~SliceTest()
{
}

void SliceTest::Update()
{
}

void SliceTest::Render()
{
	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);
	image->Render();
}
