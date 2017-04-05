#include"Objects.h"


Objects::Objects(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, GameData* _GD) : GameObject()
{
	/*for (int m_amount = 0; m_amount < _GD->m_scrWidth; m_amount++)
	{
		m_object.push_back(new Object(_fileName, _pd3dDevice, _EF));
	}*/
}

Objects::~Objects()
{

}

void Objects::Tick(GameData * _GD)
{

}
