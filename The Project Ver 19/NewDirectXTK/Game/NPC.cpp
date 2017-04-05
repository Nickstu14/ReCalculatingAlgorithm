#include "NPC.h"



NPC::NPC(string _fileName, ID3D11Device* _GD, Vector2 _Pos, Vector2 _Scale) : ImageGO2D(_fileName, _GD)
{

	m_pos = Vector2((_Pos.x * 50) + 0.5f, (_Pos.y * 50) + 0.5f);
	m_scale = _Scale;
}

NPC::~NPC()
{

}

void NPC::Tick(GameData * _GD)
{
	m_pos = GetNPCPos();

	GameObject2D::Tick(_GD);
}

void NPC::Draw(DrawData2D * _DD)
{
		ImageGO2D::Draw(_DD);
}
