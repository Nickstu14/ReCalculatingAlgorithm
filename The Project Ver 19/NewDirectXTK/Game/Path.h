#ifndef _PATH_H_
#define _PATH_H_

#include "ImageGO2D.h"
class Path :public ImageGO2D
{
public:
	Path(string _fileName, ID3D11Device* _GD, Vector2 _Pos, Vector2 _Scale, int _VecLoc);
	~Path();

	virtual void Tick(GameData * _GD);
	virtual void Draw(DrawData2D *_DD2D);

	void setIsAlive(bool _alive) { m_alive = _alive; }
	bool getIsAlive() { return m_alive; }

	int getVecLoc() { return m_VecLoc; }

private:
	bool m_alive;
	int m_VecLoc;
};







#endif // !_PATH_H_

