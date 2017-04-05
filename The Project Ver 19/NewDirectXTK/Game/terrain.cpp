#include "terrain.h"

Terrain::Terrain(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, Vector3 _pos, float _pitch, float _yaw, float _roll, Vector3 _scale, GameData* _GD) :CMOGO(_fileName, _pd3dDevice, _EF)
{
	m_pos = _pos;
	m_pitch = _pitch;
	m_roll = _roll;
	m_yaw = _yaw;
	m_scale = _scale;

	for (int m_height = 0; m_height < _GD->m_scrHeight; m_height++)
	{
		for (int m_width = 0; m_width < _GD->m_scrWidth; m_width++)
		{
			// adding in the grid
			//m_grid.push_back( new grid(_fileName, _pd3dDevice, _EF, m_height,0, m_width));
		}
	}

	GameObject::Tick(nullptr); //update my world_transform
}

Terrain::~Terrain()
{
	//Nothing additional here but add this just in case
}


void Terrain::Tick(GameData* _GD)
{
	//print the grid to the console
	//PrintToConsole();
}

void Terrain::PrintToConsole()
{

}
