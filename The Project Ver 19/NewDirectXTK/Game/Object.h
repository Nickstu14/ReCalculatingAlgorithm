#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "ImageGO2D.h"


class Object : public ImageGO2D
{
public:
	Object(string _fileName, ID3D11Device* _GD, Vector2 _Pos, Vector2 _Scale, int _VecLoc);
	~Object();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD2D);

	void setObjectPos(Vector2 _Pos) { m_ObjectPos = Vector2((_Pos.x * 50) + 0.5f, (_Pos.y * 50) + 0.5f);}
	Vector2 GetObjectPos() { return m_ObjectPos; }

	void setIsAlive(bool _alive) { m_alive = _alive; }
	bool getIsAlive() { return m_alive; }

	int getVecLoc() { return m_VecLoc; }

private:

	Vector2 m_ObjectPos;
	bool m_alive;
	int m_VecLoc;


};

#endif