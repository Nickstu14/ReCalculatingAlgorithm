#ifndef _OBJECTS_H_
#define _OBJECTS_H_
#include "CMOGO.h"
#include "Object.h"
#include "GameData.h"
#include <list>
#include <string>


class Cell; //Temp storage to a single cell
class Object;

class Objects : public GameObject
{

public:
	Objects(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, GameData * _GD);
	~Objects();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData* _DD) {};

private:
	list <Object*> m_object;

};

#endif