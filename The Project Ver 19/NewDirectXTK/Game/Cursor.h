#ifndef _CURSOR_H_
#define _CURSOR_H_

#include "ImageGO2D.h"
#include "GameData.h"

class Cursor : public ImageGO2D
{
public :
	 Cursor(string _Name, ID3D11Device* _GD, Vector2 _Pos, Vector2 _Scale);
	~Cursor();

	virtual void Tick(GameData * _GD);
	virtual void Draw(DrawData2D * _DD2D);

private:

};




#endif