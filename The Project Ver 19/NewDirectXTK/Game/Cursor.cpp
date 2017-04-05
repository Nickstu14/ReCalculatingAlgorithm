#include "Cursor.h"


Cursor::Cursor(string _Name, ID3D11Device* _GD,Vector2 _Pos, Vector2 _Scale) : ImageGO2D(_Name,  _GD)
{
	m_pos = _Pos;
	m_scale = _Scale;
}

Cursor::~Cursor() {};

void Cursor::Tick(GameData * _GD)
{
	float speed = 0.5f;
	m_pos.x = _GD->m_mousePosX;  //+= speed * _GD->m_mouseState->lX;
	m_pos.y = _GD->m_mousePosY; //+= speed * _GD->m_mouseState->lY;

	if (_GD->m_mouseState->rgbButtons[0] /*&& !m_GD->m_MouseLeftClick*/)
	{
		int i = 0;
	}

	//_GD->m_mousePosX = m_pos.x /50;
	//_GD->m_mousePosY = m_pos.y /50;


}
void Cursor::Draw(DrawData2D * _DD2D)
{
	ImageGO2D::Draw(_DD2D);
}