#include "game.h"
#include "GameData.h"
#include "drawdata.h"
#include "DrawData2D.h"
#include "gameobject.h"
#include "ObjectList.h"
#include "helper.h"
#include <windows.h>
#include <time.h>
#include "DDSTextureLoader.h"
#include <d3d11shader.h>

using namespace DirectX;

Game::Game(ID3D11Device* _pd3dDevice, HWND _hWnd, HINSTANCE _hInstance) :m_playTime(0), m_fxFactory(nullptr), m_states(nullptr)
{
	//Create DirectXTK spritebatch stuff
	ID3D11DeviceContext* pd3dImmediateContext;
	_pd3dDevice->GetImmediateContext(&pd3dImmediateContext);
	m_DD2D = new DrawData2D();
	m_DD2D->m_Sprites.reset(new SpriteBatch(pd3dImmediateContext));
	m_DD2D->m_Font.reset(new SpriteFont(_pd3dDevice, L"italic.spritefont"));

	//seed the random number generator
	srand((UINT)time(NULL));


	//Direct Input Stuff
	m_hWnd = _hWnd;
	m_pKeyboard = nullptr;
	m_pDirectInput = nullptr;

	HRESULT hr = DirectInput8Create(_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL);
	hr = m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL);
	hr = m_pKeyboard->SetDataFormat(&c_dfDIKeyboard);
	hr = m_pKeyboard->SetCooperativeLevel(m_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	hr = m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pMouse, NULL);
	hr = m_pMouse->SetDataFormat(&c_dfDIMouse);
	hr = m_pMouse->SetCooperativeLevel(m_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);



	//create GameData struct and populate its pointers
	m_GD = new GameData;
	m_GD->m_keyboardState = m_keyboardState;
	m_GD->m_prevKeyboardState = m_prevKeyboardState;
	m_GD->m_GS = GS_NULL;
	m_GD->m_mouseState = &m_mouseState;
	m_GD->m_t = 0.5f;
	m_GD->m_TextToggle = false;
	m_GD->m_HelpText = false;
	m_GD->m_F1 = true;
	m_GD->m_Pause = false;
	m_GD->m_DebugPrint = 0;

	//set up DirectXTK Effects system
	m_fxFactory = new EffectFactory(_pd3dDevice);

	//Tell the fxFactory to look to the correct build directory to pull stuff in from
#ifdef DEBUG
	((EffectFactory*)m_fxFactory)->SetDirectory(L"../Debug");
#else
	((EffectFactory*)m_fxFactory)->SetDirectory(L"../Release");
#endif

	// Create other render resources here
	m_states = new CommonStates(_pd3dDevice);

	//init render system for VBGOs
	VBGO::Init(_pd3dDevice);

	//find how big my window is to correctly calculate my aspect ratio
	RECT rc;
	GetClientRect(m_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;
	float AR = (float)width / (float)height;

	//add window size into GameData
	m_GD->m_scrWidth = (width - 200) / 50;
	m_GD->m_scrHeight = height / 50;

	//create a base camera
	m_cam = new Camera(0.25f * XM_PI, AR, 1.0f, 10000.0f, Vector3::UnitY, Vector3::Zero);
	m_cam->SetPos(Vector3(0.0f, 0.0f, 100.0f));
	m_GameObjects.push_back(m_cam);

	//create a base light
	m_light = new Light(Vector3(0.0f, 100.0f, 160.0f), Color(1.0f, 1.0f, 1.0f, 1.0f), Color(0.4f, 0.1f, 0.1f, 1.0f));
	m_GameObjects.push_back(m_light);

	//create DrawData struct and populate its pointers
	m_DD = new DrawData;
	m_DD->m_pd3dImmediateContext = nullptr;
	m_DD->m_states = m_states;
	m_DD->m_cam = m_cam;
	m_DD->m_light = m_light;

	//creation of the base grid
	m_grid = new Grid(_pd3dDevice, m_GD);
	m_GameObject2Ds.push_back(m_grid);

	/*m_cursor = new Cursor("Cursor", _pd3dDevice, Vector2::One, Vector2(0.25f, 0.25f));
	m_GameObject2Ds.push_back(m_cursor);*/


	//Text settings
	Vector2 m_tempscale = Vector2(0.5f, 0.5f) / 2;
	Color m_tempcolour = Color(255, 69, 0);

	//Mouse Debug text
	m_Text = "Mouse XY: " + std::to_string(m_GD->m_mouseState->lX) + " " + std::to_string(m_GD->m_mouseState->lY);
	m_MouseText = new Text(m_Text, Vector2(0.5f, height - 20.0f), m_tempscale, m_tempcolour); //string _Text, Vector2 _Pos, Vector2 _Scale, Color _Colour);
	m_GameObject2Ds.push_back(m_MouseText);

	//Help Menu
	
	m_Text = "Help Menu";
	m_HelpTextTitle = new Text(m_Text, Vector2(width - 200, 20.0f), m_tempscale, m_tempcolour);
	m_Text = "T - Toggle Grid MoveCost";
	m_GridText = new Text(m_Text, Vector2(width - 200, 30.0f), m_tempscale, m_tempcolour);

	m_Text = "O - SPEED UP";
	m_SpeedUpText = new Text(m_Text, Vector2(width - 200, 50.0f), m_tempscale, m_tempcolour);
	m_Text = "I - SLOW DOWN";
	m_SlowDownText = new Text(m_Text, Vector2(width - 200, 60.0f), m_tempscale, m_tempcolour);
	m_Text = "PAUSE";
	m_PauseText = new Text(m_Text, Vector2(width - 200, 70.0f), m_tempscale, m_tempcolour);
	m_Text = "Game Speed : " + std::to_string(m_GD->m_t);
	m_GameSpeedText = new Text(m_Text, Vector2(width - 200, 90.0f), m_tempscale, m_tempcolour);
	
	m_Text = "Terminal Debug";
	m_CMDTitle = new Text(m_Text, Vector2(width - 200, 110.0f), m_tempscale, m_tempcolour);
	m_Text = "1 - Print Grid";
	m_1Print = new Text(m_Text, Vector2(width - 200, 120.0f), m_tempscale, m_tempcolour);
	m_Text = "2 - Print Est Cost";
	m_2Print = new Text(m_Text, Vector2(width - 200, 130.0f), m_tempscale, m_tempcolour);
	m_Text = "3 - Print Move Cost";
	m_3Print = new Text(m_Text, Vector2(width - 200, 140.0f), m_tempscale, m_tempcolour);
	m_Text = "4 - Print Total Cost";
	m_4Print = new Text(m_Text, Vector2(width - 200, 150.0f), m_tempscale, m_tempcolour);


	//push all text to the gameoobject list
	m_GameObject2Ds.push_back(m_HelpTextTitle);
	m_GameObject2Ds.push_back(m_GridText);
	m_GameObject2Ds.push_back(m_SpeedUpText);
	m_GameObject2Ds.push_back(m_SlowDownText);
	m_GameObject2Ds.push_back(m_PauseText);
	m_GameObject2Ds.push_back(m_GameSpeedText);
	m_GameObject2Ds.push_back(m_CMDTitle);
	m_GameObject2Ds.push_back(m_1Print);
	m_GameObject2Ds.push_back(m_2Print);
	m_GameObject2Ds.push_back(m_3Print);
	m_GameObject2Ds.push_back(m_4Print);


	//lastly set the gamestate to costsetup
	m_GD->m_GS = GS_COSTSETUP;


	//stores initial value for internal timer
	m_TimeStart = std::chrono::steady_clock::now();
	m_GD->m_TimeValue = m_TimeStart;
}

Game::~Game()
{
	//delete Game Data & Draw Data
	delete m_GD;
	delete m_DD;

	//tidy up VBGO render system
	VBGO::CleanUp();

	//tidy away Direct Input Stuff
	if (m_pKeyboard)
	{
		m_pKeyboard->Unacquire();
		m_pKeyboard->Release();
	}
	if (m_pMouse)
	{
		m_pMouse->Unacquire();
		m_pMouse->Release();
	}
	if (m_pDirectInput)
	{
		m_pDirectInput->Release();
	}

	//get rid of the game objects here
	for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		delete (*it);
	}
	m_GameObjects.clear();


	//and the 2D ones
	for (auto it = m_GameObject2Ds.begin(); it != m_GameObject2Ds.end(); it++)
	{
		delete (*it);
	}
	m_GameObject2Ds.clear();

	//clear away CMO render system
	delete m_states;
	delete m_fxFactory;

	delete m_DD2D;
}

bool Game::Update()
{

	//Poll Keyboard & Mouse
	ReadInput();

	//Upon pressing escape QUIT
	if (m_keyboardState[DIK_ESCAPE] & 0x80)
	{
		return false;
	}



	//lock the cursor to the centre of the window
	RECT window;
	GetWindowRect(m_hWnd, &window);
	//SetCursorPos((window.left+window.right)>>1, (window.bottom+window.top)>>1);


	KeyboardInput();


	//calculate frame time-step dt for passing down to game objects
	DWORD currentTime = GetTickCount();
	m_GD->m_dt = min((float)(currentTime - m_playTime) / 1000.0f, 0.1f);
	m_playTime = currentTime;




	//Updates the mouse XY pos
	//Mouse position doesn't match up in release
	POINT p;
#ifdef DEBUG
	GetCursorPos(&p);
	ScreenToClient(m_hWnd, &p);
#else
	GetCursorPos(&p);
#endif



	m_GD->m_mousePosX = (long)p.x;
	m_GD->m_mousePosY = (long)p.y;


		m_Text = "Mouse XY: " + std::to_string(p.x / 50) + " | " + std::to_string(p.y / 50);
		m_MouseText->setText(m_Text);

		m_Text = "Game Speed : " + std::to_string(m_GD->m_t);
		m_GameSpeedText->setText(m_Text);

	
	if (m_GD->m_mouseState->rgbButtons[0] /*&& !m_GD->m_MouseLeftClick*/)
	{
		m_GD->m_MouseLeftClick = true;
		m_grid->Cursor(m_GD);
	}

	//update all objects
	for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		(*it)->Tick(m_GD);
	}
	for (auto it = m_GameObject2Ds.begin(); it != m_GameObject2Ds.end(); it++)
	{
		(*it)->Tick(m_GD);
	}

	return true;
}

void Game::KeyboardInput()
{
	//Toggles to display help text.
	if ((m_keyboardState[DIK_F1] & 0x80) && !(m_prevKeyboardState[DIK_F1] & 0x80))
	{
		if (m_GD->m_HelpText)
		{
			m_GD->m_HelpText = false;
			m_GD->m_F1 = true;
		}
		else
		{
			m_GD->m_HelpText = true;
			m_GD->m_F1 = false;
		}

	}

	//increases and decreases the speed of the game loop, also pause.
	//Pause game
	if ((m_keyboardState[DIK_P] & 0x80) && !(m_prevKeyboardState[DIK_P] & 0x80))
	{
		if (m_GD->m_Pause)
			m_GD->m_Pause = false;
		else
			m_GD->m_Pause = true;

	}
	//Decreases game speed
	if ((m_keyboardState[DIK_I] & 0x80) && !(m_prevKeyboardState[DIK_I] & 0x80))
	{
		if (m_GD->m_t <= 1.0f)
		{
			m_GD->m_t += 0.1f;
		}
	}
	//Increases game speed
	if ((m_keyboardState[DIK_O] & 0x80) && !(m_prevKeyboardState[DIK_O] & 0x80))
	{
		if (m_GD->m_t >= 0.1f)
		{
			m_GD->m_t -= 0.1f;
		}
	}

	//Toggle Text
	if ((m_keyboardState[DIK_T] & 0x80) && !(m_prevKeyboardState[DIK_T] & 0x80))
	{
		if (m_GD->m_TextToggle)
			m_GD->m_TextToggle = false;
		else
			m_GD->m_TextToggle = true;
	}

	//Reset Map, clears all objects and respawns a new map
	/*Doesn't clean up the map, objects are being turned off*/
	/*if ((m_keyboardState[DIK_R] & 0x80) && !(m_prevKeyboardState[DIK_R] & 0x80))
	{
		if (!m_GD->m_HelpText)
			m_GD->m_GS = GS_RESET;
	}*/


	// 1-4 of the different CMD Terminal displays
	//1 - prints basic grid with objets, path, goal and NPC
	if ((m_keyboardState[DIK_1] & 0x80) && !(m_prevKeyboardState[DIK_1] & 0x80))
	{
		m_GD->m_DebugPrint = 1;
	}
	//2 - Prints estimated Cost
	if ((m_keyboardState[DIK_2] & 0x80) && !(m_prevKeyboardState[DIK_2] & 0x80))
	{
		m_GD->m_DebugPrint = 2;
	}
	// 3 - prints move cost
	if ((m_keyboardState[DIK_3] & 0x80) && !(m_prevKeyboardState[DIK_3] & 0x80))
	{
		m_GD->m_DebugPrint = 3;
	}
	// 4 - Prints total cost
	if ((m_keyboardState[DIK_4] & 0x80) && !(m_prevKeyboardState[DIK_4] & 0x80))
	{
		m_GD->m_DebugPrint = 4;
	}



}

void Game::Render(ID3D11DeviceContext* _pd3dImmediateContext)
{
	//set immediate context of the graphics device
	m_DD->m_pd3dImmediateContext = _pd3dImmediateContext;

	//set which camera to be used
	m_DD->m_cam = m_cam;
	/*if (m_GD->m_GS == GS_PLAY_TPS_CAM)
	{
		m_DD->m_cam = m_TPScam;
	}*/

	//update the constant buffer for the rendering of VBGOs
	VBGO::UpdateConstantBuffer(m_DD);

	//draw all objects
	for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		(*it)->Draw(m_DD);
	}

	// Draw sprite batch stuff 
	m_DD2D->m_Sprites->Begin();
	for (auto it = m_GameObject2Ds.begin(); it != m_GameObject2Ds.end(); it++)
	{
		(*it)->Draw(m_DD2D);
	}
	m_DD2D->m_Sprites->End();

	//drawing text screws up the Depth Stencil State, this puts it back again!
	_pd3dImmediateContext->OMSetDepthStencilState(m_states->DepthDefault(), 0);
}

bool Game::ReadInput()
{
	//copy over old keyboard state
	memcpy(m_prevKeyboardState, m_keyboardState, sizeof(unsigned char) * 256);

	//clear out previous state
	ZeroMemory(&m_keyboardState, sizeof(unsigned char) * 256);
	ZeroMemory(&m_mouseState, sizeof(DIMOUSESTATE));

	// Read the keyboard device.
	HRESULT hr = m_pKeyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			m_pKeyboard->Acquire();
		}
		else
		{
			return false;
		}
	}

	// Read the Mouse device.
	hr = m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if (FAILED(hr))
	{
		// If the Mouse lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			m_pMouse->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}





