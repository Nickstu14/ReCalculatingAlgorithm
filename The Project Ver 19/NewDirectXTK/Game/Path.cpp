#include "Path.h"


Path::Path(string _fileName, ID3D11Device* _GD, Vector2 _Pos, Vector2 _Scale, int _VecLoc) : ImageGO2D(_fileName, _GD)
{
	m_alive = false;
	m_pos = Vector2((_Pos.x * 50) + 0.5f, (_Pos.y * 50) + 0.5f);
	m_scale = _Scale;
	m_VecLoc = _VecLoc;
}

Path::~Path()
{

}

void Path::Tick(GameData * _GD)
{
	GameObject2D::Tick(_GD);
}

void Path::Draw(DrawData2D * _DD)
{
	if (getIsAlive())
	{
		ImageGO2D::Draw(_DD);
	}
}
