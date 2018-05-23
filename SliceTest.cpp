#include "stdafx.h"
#include "SliceTest.h"

SliceTest::SliceTest()
{
	image = Texture::Add(L"Image/test.jpg");

	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);

	//��������� �����ϴ� �Լ�
	D3DXMatrixOrthoOffCenterLH(&projection,
		0.0f, viewport.Width, viewport.Height, 0.0f,
		-1, 1);

	//������ ������ ����
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
