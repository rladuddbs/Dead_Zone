#include "pch.h"
#include "Player.h"
#include "Resources.h"
#include "Transform.h"
#include "Input.h"
#include "Timer.h"

Player::Player() : Component(COMPONENT_TYPE::PLAYER)
{
	_obj = make_shared<GameObject>();
	_obj->AddComponent(make_shared<Transform>());
	_obj->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 100.f));
	_obj->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, 350.f));
	_obj->SetStatic(false);

	_meshRenderer = make_shared<MeshRenderer>();

	_characterMesh = GET_SINGLE(Resources)->LoadSphereMesh();
	_material = make_shared<Material>();
	_shader = GET_SINGLE(Resources)->Get<Shader>(L"Deferred");
	_texture = GET_SINGLE(Resources)->Load<Texture>(L"Cliff_Rock", L"..\\Resources\\Texture\\Cliff_Rock_basecolor.png");
	_normal = GET_SINGLE(Resources)->Load<Texture>(L"Cliff_Rock_Normal", L"..\\Resources\\Texture\\Cliff_Rock_normal.png");

	_material->SetShader(_shader);
	_material->SetTexture(0, _texture);
	_material->SetTexture(1, _normal);

	_meshRenderer->SetMesh(_characterMesh);
	_meshRenderer->SetMaterial(_material);

	_obj->AddComponent(_meshRenderer);
}

Player::~Player()
{
}

void Player::LateUpdate()
{
	Vec3 pos = GetTransform()->GetLocalPosition();

	if (INPUT->GetButton(KEY_TYPE::W))
		pos += GetTransform()->GetLook() * _speed * DELTA_TIME;

	if (INPUT->GetButton(KEY_TYPE::S))
		pos -= GetTransform()->GetLook() * _speed * DELTA_TIME;

	if (INPUT->GetButton(KEY_TYPE::A))
		pos -= GetTransform()->GetRight() * _speed * DELTA_TIME;

	if (INPUT->GetButton(KEY_TYPE::D))
		pos += GetTransform()->GetRight() * _speed * DELTA_TIME;



	GetTransform()->SetLocalPosition(pos);
}
