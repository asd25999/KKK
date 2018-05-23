#include "stdafx.h"
#include "AniTest.h"

AniTest::AniTest()
{
	pos = { 300, 300 };

	//camera = new Camera;

	state = STAND;

	stand = Texture::Add(fileNames[4], 2, 3, 8, 4);
	left1 = Texture::Add(fileNames[4], 4, 0, 8, 4);
	left2 = Texture::Add(fileNames[4], 5, 0, 8, 4);

	vector<AnimationClip> clips;
	clips.push_back(AnimationClip(stand, 100));
	actions.push_back(new Animator(&clips));

	clips.clear();
	clips.push_back(AnimationClip(left1, 100));
	clips.push_back(AnimationClip(left2, 100));
	actions.push_back(new Animator(&clips, Type::LOOP));	

	//actions[state]->Play();
}

AniTest::~AniTest()
{
}

void AniTest::Update()
{
	state = STAND;

	if (KEYBOARD->KeyDown(VK_RIGHT))
	{
		actions[LEFT]->Play();
	}

	if (KEYBOARD->KeyPress(VK_RIGHT))
	{
		pos.x += 100 * TIMER->TimeElapsed();
		state = LEFT;
	}

	D3DXMatrixTranslation(&world, pos.x, pos.y, 0.0f);
	actions[state]->Update();

	//camera->Update();
}

void AniTest::Render()
{
	Device::StartAlphaRender();
	Device::SetWorld(&world);
	actions[state]->Render();
	Device::EndAlphaRender();
}
