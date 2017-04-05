#ifndef _GOAL_H_
#define _GOAL_H_
#include "ImageGO2D.h"

class Goal : public ImageGO2D
{
public :
	Goal(string _fileName, ID3D11Device* _GD, Vector2 _Pos,Vector2 _Scale);
	~Goal();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD2D);

	void setGoalPos(Vector2 _Pos) { m_GoalPos = Vector2((_Pos.x * 50) + 0.5f, (_Pos.y * 50) + 0.5f);}
	Vector2 getGoalPos() { return m_GoalPos; }


private:
	
	Vector2 m_GoalPos;


};


#endif