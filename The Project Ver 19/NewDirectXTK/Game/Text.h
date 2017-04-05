#ifndef _TEXT_H_
#define _TEXT_H_

#include "TextGO2D.h"

class Text: public TextGO2D
{
public:
	Text(string _Text, Vector2 _Pos, Vector2 _Scale, Color _Colour);
	~Text();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD2D);


	string GetText() { return m_text; }
	void setText(string _Text) { m_text = _Text; }


private:

	//string m_TempText;

};





#endif // !_TEXT_H_

