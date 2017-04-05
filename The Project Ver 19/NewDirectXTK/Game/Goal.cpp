#include "Goal.h"


Goal::Goal(string _fileName, ID3D11Device* _GD, Vector2 _Pos, Vector2 _Scale) : ImageGO2D( _fileName, _GD )
{
	m_pos = Vector2((_Pos.x * 50) + 0.5f, (_Pos.y * 50) + 0.5f);
	m_scale = _Scale;
}

Goal::~Goal()
{

}


void Goal::Tick(GameData* _GD)
{
	m_pos = getGoalPos();

	GameObject2D::Tick(_GD);
}


void Goal::Draw(DrawData2D * _DD2D)
{
		ImageGO2D::Draw(_DD2D);
}