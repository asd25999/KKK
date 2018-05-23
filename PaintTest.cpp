#include "stdafx.h"
#include "PaintTest.h"

DWORD PaintTest::Vertex::fvf = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;

PaintTest::PaintTest()
{
	state = LINE;
	selectColor = 0xffff0000;
}

PaintTest::~PaintTest()
{

}

void PaintTest::Update()
{
	if (KEYBOARD->KeyDown(VK_F1))
	{
		selectColor = COLOR_R;
	}
	if (KEYBOARD->KeyDown(VK_F2))
	{
		selectColor = COLOR_G;
	}
	if (KEYBOARD->KeyDown(VK_F3))
	{
		selectColor = COLOR_B;
	}

	if (KEYBOARD->KeyDown('1'))
	{
		state = LINE;
	}

	if (KEYBOARD->KeyDown('2'))
	{
		state = TRIANGLE;
	}

	if (KEYBOARD->KeyDown('3'))
	{
		state = RECTANGLE;
	}

	//if (MOUSE->ButtonDown(0))
	if(KEYBOARD->KeyDown(VK_LBUTTON))
	{
		Point mousePos = MOUSE->GetPosition();

		Vertex v;
		v.position = { mousePos.x, mousePos.y, 0, 1 };
		v.color = selectColor;

		switch (state)
		{
		case PaintTest::LINE:
			lineVertex.push_back(v);			
			break;
		case PaintTest::TRIANGLE:
			triangleVertex.push_back(v);
			break;
		case PaintTest::RECTANGLE:
			rectangleVertex.push_back(v);
			break;
		default:
			break;
		}
	}

	//if (MOUSE->ButtonUp(0))
	if (KEYBOARD->KeyUp(VK_LBUTTON))
	{
		Point mousePos = MOUSE->GetPosition();

		Vertex v;
		v.position = { mousePos.x, mousePos.y, 0, 1 };
		v.color = selectColor;

		switch (state)
		{
		case PaintTest::LINE:
			lineVertex.push_back(v);
			break;
		case PaintTest::TRIANGLE:
		{
			//triangleVertex.push_back(v);			
			Vertex startVertex = triangleVertex.back();

			Vertex thirdVertex;
			thirdVertex.position = { mousePos.x,
				startVertex.position.y, 0, 1 };			
			thirdVertex.color = selectColor;
			triangleVertex.push_back(thirdVertex);
			triangleVertex.push_back(v);
		}
			break;
		case PaintTest::RECTANGLE:
		{
			Vertex startPos = rectangleVertex.back();
			Vertex v1, v2, v3, v4;
			v1.position = { mousePos.x, startPos.position.y, 0, 1 };
			v2.position = v.position;
			v3.position = { startPos.position.x, mousePos.y, 0, 1 };
			v4.position = startPos.position;

			rectangleVertex.push_back(v1);
			rectangleVertex.push_back(v2);
			rectangleVertex.push_back(v3);
			rectangleVertex.push_back(v4);
			rectangleVertex.push_back(v);
		}
			break;
		default:
			break;
		}
	}
}

void PaintTest::Render()
{
	DEVICE->SetFVF(Vertex::fvf);
	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	int lineNum = lineVertex.size() / 2;

	if (lineVertex.size() > 0)
	{
		DEVICE->DrawPrimitiveUP(D3DPT_LINELIST, 
			lineNum, &lineVertex[0], sizeof(Vertex));
	}

	int triangleNum = triangleVertex.size() / 3;
	if (triangleVertex.size() > 0)
	{
		DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			triangleNum, &triangleVertex[0], sizeof(Vertex));
	}

	int rectNum = rectangleVertex.size() / 3;
	if (rectangleVertex.size() > 0)
	{
		DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			rectNum, &rectangleVertex[0], sizeof(Vertex));
	}
}
