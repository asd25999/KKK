#pragma once

class Player : public ISpotPoint
{
private:
	D3DXVECTOR2 pos;

	float speed;

	enum AniType
	{
		IDLE,
		RUN,
		SHOOT
	};

	AniType aniType;

	vector<Animator*> actions;
	UINT animatorIndex;

	D3DXMATRIX world;
public:
	Player();
	~Player();

	void Update();
	void Render();

	void LoadXml();

	void GetSpotPoint(D3DXVECTOR2* position,
		D3DXVECTOR2* size);
};