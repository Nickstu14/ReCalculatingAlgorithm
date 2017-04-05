#ifndef _TERRAIN_H_
#define _TERRAIN_H_
#include "CMOGO.h"
#include "GameData.h"
//#include "grid.h"

//=================================================================
//Terrian Game Object Class (i.e. an Object that just sits there)
//=================================================================

class grid;

class Terrain : public CMOGO
{
public:
	
	Terrain(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, Vector3 _pos, float _pitch, float _yaw, float _roll, Vector3 _scale, GameData* _GD);
	~Terrain();

	virtual void Tick(GameData* _GD);
	//virtual void Draw(DrawData* _DD);

	void PrintToConsole();
private :

	//vector<grid *> m_grid; //terrain grid
	
protected:


};

#endif