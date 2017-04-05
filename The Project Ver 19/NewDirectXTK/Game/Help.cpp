#include "Help.h"


Help::Help(std::string _Text, Vector2 _Pos, Vector2 _Scale, Color _Colour): TextGO2D( _Text)
{
	m_pos = _Pos;
	m_scale = _Scale;
	m_colour = _Colour;
}

Help::~Help() {};

void Help::Tick(GameData *_GD)
{
	if (_GD->m_HelpText)
	{
		m_toggle = true;
	}
	else
	{
		m_toggle = false;
	}
}

void Help::Draw(DrawData2D* _DD2D)
{
	if(m_toggle)
		TextGO2D::Draw(_DD2D);
}