#pragma once

class TigerBoy
{
private:
	//D3DXVECTOR2 pos;
	World * world;

	float speed;

	enum AniType
	{		
		RUN,
		STOP
	};

	AniType aniType;

	vector<Animator*> actions;	

	//D3DXMATRIX world;
public:
	TigerBoy();
	~TigerBoy();

	void Update();
	void Render();

	void LoadXml();
};