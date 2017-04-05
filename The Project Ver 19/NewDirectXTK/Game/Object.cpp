#include "Object.h"

Object::Object(string _fileName, ID3D11Device*_GD, Vector2 _Pos, Vector2 _Scale, int _VecLoc) : ImageGO2D(_fileName, _GD)
{
	m_alive = false;
	m_pos = Vector2((_Pos.x * 50) + 0.5f, (_Pos.y * 50) + 0.5f);
	m_ObjectPos = Vector2((_Pos.x * 50) + 0.5f, (_Pos.y * 50) + 0.5f);
	m_scale = _Scale;
	m_VecLoc = _VecLoc;
	
}

Object::~Object()
{

}

void Object::Tick(GameData * _GD)
{
	//m_pos = GetObjectPos();

	GameObject2D::Tick(_GD);
}

void Object::Draw(DrawData2D * _DD)
{
	if (getIsAlive())
	{
		ImageGO2D::Draw(_DD);
	}
}

