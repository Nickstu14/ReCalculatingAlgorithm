#ifndef _HELP_H_
#define _HELP_H_

#include "GameData.h"
#include "Text.h"
#include <string>

class Text;

class Help : public TextGO2D
{
public :
	Help(std::string _Text, Vector2 _Pos, Vector2 _Scale, Color _Colour);
	~Help();

	void Tick(GameData * _GD);
	void Draw(DrawData2D* _DD2D);


private:
	bool m_toggle;
};


#endif // ! _HELP_H_


