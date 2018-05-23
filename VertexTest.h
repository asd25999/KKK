#pragma once
//DirectX
//-���� �̵� ����� ���� ���α׷��� �ϵ���� ��ġ��
//���� �����Ͽ� ������� ó�� �� �� �ֵ��� �����ִ� API

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