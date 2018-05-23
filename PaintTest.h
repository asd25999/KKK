#pragma once

class PaintTest : public Test
{
private:
	struct Vertex
	{
		D3DXVECTOR4 position;
		DWORD color;

		static DWORD fvf;
	};

	enum State
	{
		LINE,
		TRIANGLE,
		RECTANGLE
	};	

	State state;

	DWORD selectColor;

	vector<Vertex> lineVertex;
	vector<Vertex> triangleVertex;
	vector<Vertex> rectangleVertex;

public:
	PaintTest();
	~PaintTest();

	void Update();
	void Render();
};