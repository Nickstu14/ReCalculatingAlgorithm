#include "TextGO2D.h"
#include "DrawData2D.h"
#include "helper.h"

TextGO2D::TextGO2D(string _text)
{
	m_text = _text;
}



void TextGO2D::Tick(GameData* _GD)
{
	GameObject2D::Tick(_GD);
}


void TextGO2D::Draw(DrawData2D* _DD)
{
	if (m_text != "0")
	{
		_DD->m_Font->DrawString(_DD->m_Sprites.get(), Helper::charToWChar(m_text.c_str()), m_pos, m_colour, m_rotation, m_origin, m_scale);
	}
}