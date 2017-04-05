#include "Text.h"

Text::Text(string _Text, Vector2 _Pos, Vector2 _Scale, Color _Colour) : TextGO2D ( _Text)
{
	m_pos = _Pos;
	m_scale = _Scale;
	m_colour = _Colour;
	
}

Text::~Text() {};

void Text::Tick(GameData* _GD)
{
	TextGO2D::m_text = GetText();

	//TextGO2D::Tick(_GD);
}
void Text::Draw(DrawData2D* _DD2D)
{
	TextGO2D::Draw(_DD2D);
}