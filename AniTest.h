#pragma once

class AniTest : public Test
{
private:
	enum AniState
	{
		STAND,
		LEFT,		
		LEFTJUMP,		
	}state;
	//AniState state;

	D3DXVECTOR2 pos;

	D3DXMATRIX world;

	Camera* camera;

	wstring fileNames[6] =
	{
		L"Image/mario_cloud.png",
		L"Image/mario_bush2.png",
		L"Image/mario_bush1.png",
		L"Image/mario_tile1.png",
		L"Image/mario_all.png",
		L"Image/mario_bg.png",
	};

	Texture* mario;

	vector<Animator*> actions;
	Texture* stand;
	Texture* left1, *left2;
	Texture* leftJump[4];

public:
	AniTest();
	~AniTest();

	void Update();
	void Render();
};