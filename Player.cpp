#include "stdafx.h"

Player::Player()
{
	animatorIndex = 0;
	pos = { 300, 300 };
	speed = 100;

	LoadXml();
	D3DXMatrixIdentity(&world);

	actions[animatorIndex]->Play();
}

Player::~Player()
{
}

void Player::Update()
{
	animatorIndex = IDLE;

	if (KEYBOARD->KeyDown(VK_RIGHT))
	{
		actions[RUN]->Play();
	}
	if (KEYBOARD->KeyDown(VK_LEFT))
	{
		actions[RUN]->Play();
	}

	if (KEYBOARD->KeyPress(VK_RIGHT))
	{
		pos.x += speed * TIMER->TimeElapsed();
		animatorIndex = RUN;
	}
	if (KEYBOARD->KeyPress(VK_LEFT))
	{
		pos.x -= speed * TIMER->TimeElapsed();
		animatorIndex = RUN;
	}

	D3DXMatrixTranslation(&world, pos.x, pos.y, 0.0f);

	actions[animatorIndex]->Update();
}

void Player::Render()
{
	Device::SetWorld(&world);
	Device::StartAlphaRender();
	actions[animatorIndex]->Render();
	Device::EndAlphaRender();
}

void Player::LoadXml()
{
	string spritePath = "";
	XmlDocument* doc = new XmlDocument();
	doc->LoadFile("Image/Metalslug.xml");

	XmlElement* player = doc->FirstChildElement("Player");
	XmlAttribute* path = (XmlAttribute*)player->FirstAttribute();
	spritePath = path->Value();

	wstring fileName;
	fileName.assign(spritePath.begin(), spritePath.end());

	XmlElement* action = NULL;

	action = player->FirstChildElement();
	for (; action != NULL; action = action->NextSiblingElement())
	{
		vector<AnimationClip> clips;
		UINT repeat = action->UnsignedAttribute("Repeat");
		XmlElement* frame = action->FirstChildElement();

		for (; frame != NULL; frame = frame->NextSiblingElement())
		{
			DWORD time = frame->UnsignedAttribute("Time");

			XmlElement* start = frame->FirstChildElement("Start");
			D3DXVECTOR2 startPos;
			startPos.x = start->FloatAttribute("x");
			startPos.y = start->FloatAttribute("y");

			XmlElement* end = frame->FirstChildElement("End");
			D3DXVECTOR2 endPos;
			endPos.x = end->FloatAttribute("x");
			endPos.y = end->FloatAttribute("y");

			Texture* texture = Texture::Add(fileName, startPos, endPos);
			clips.push_back(AnimationClip(texture, time));
		}

		Animator* animator = new Animator(&clips, (Type)repeat);
		actions.push_back(animator);
	}

	SAFE_DELETE(doc);
}

void Player::GetSpotPoint(D3DXVECTOR2 * position, D3DXVECTOR2 * size)
{
	*position = pos;
	
	actions[aniType]->GetTexture()->GetRealSize(size);
}
