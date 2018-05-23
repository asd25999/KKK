#include "stdafx.h"

TigerBoy::TigerBoy()
{
	aniType = RUN;
	//pos = { 500, 300 };
	speed = 100;

	LoadXml();
	actions[aniType]->Play();
	world = new World;
	world->translation = { 500, 300 };
	world->scale = { 0.5f, 0.5f };
}

TigerBoy::~TigerBoy()
{
}

void TigerBoy::Update()
{
	actions[aniType]->Update();

	//D3DXMatrixTranslation(&world, pos.x, pos.y, 0.0f);
	world->Update();
}

void TigerBoy::Render()
{
	//Device::SetWorld(&world);
	Device::SetWorld(&world->matWorld);
	Device::StartAlphaRender();
	actions[aniType]->Render();
	Device::EndAlphaRender();
}

void TigerBoy::LoadXml()
{
	XmlDocument* doc = new XmlDocument;
	XmlError error;
	error = doc->LoadFile("Image/tigerboy.xml");
	assert(error == Xml::XML_SUCCESS);

	XmlElement* atlas = doc->FirstChildElement("TextureAtlas");
	string fileName = atlas->Attribute("imagePath");
	fileName = "Image/" + fileName;
	wstring path;
	path.assign(fileName.begin(), fileName.end());

	XmlElement* action = NULL;
	action = atlas->FirstChildElement();
	for (; action != NULL; action = action->NextSiblingElement())
	{
		UINT repeat = action->UnsignedAttribute("Repeat");
		DWORD time = action->UnsignedAttribute("Time");

		vector<AnimationClip> clips;

		XmlElement* frame = action->FirstChildElement();
		for (; frame != NULL; frame = frame->NextSiblingElement())
		{
			D3DXVECTOR2 startPos;
			startPos.x = frame->FloatAttribute("x");
			startPos.y = frame->FloatAttribute("y");
			D3DXVECTOR2 endPos;
			endPos.x = frame->FloatAttribute("w");
			endPos.y = frame->FloatAttribute("h");
			endPos += startPos;

			Texture* texture = Texture::Add(path, startPos, endPos);
			clips.push_back(AnimationClip(texture, time));
		}

		Animator* animator = new Animator(&clips, (Type)repeat);
		actions.push_back(animator);
	}

	SAFE_DELETE(doc);
}
