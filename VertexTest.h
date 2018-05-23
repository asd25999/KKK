#pragma once
//DirectX
//-각종 미디어를 사용한 응용 프로그램이 하드웨어 장치를
//직접 접속하여 고속으로 처리 할 수 있도록 도와주는 API

class VertexTest : public Test
{
private:
	struct Vertex
	{
		D3DXVECTOR4 position;
		DWORD color;

		static DWORD fvf;		
	};

	Vertex* vertex;
	float speed;
public:
	VertexTest();
	~VertexTest();

	void Update();
	void Render();
};