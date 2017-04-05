#ifndef _NPC_H_
#define _NPC_H_

#include "ImageGO2D.h"

class NPC : public ImageGO2D
{

public:
	NPC(string _fileName, ID3D11Device* _GD, Vector2 _Pos, Vector2 _Scale);
	~NPC();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

	
	void setNPCPos(Vector2 _Pos) { m_NPCPos = Vector2((_Pos.x * 50) + 0.5f, (_Pos.y * 50) + 0.5f);}
	Vector2 GetNPCPos() { return m_NPCPos; }





private:
	
	Vector2 m_NPCPos;
	

};

#endif