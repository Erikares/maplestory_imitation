#include "StdAfx.h"
#include "Start.h"

CStart::CStart(void)
{
	m_ButtonState = 0;
}

CStart::~CStart(void)
{
	Release();
}

void CStart::Initialize()
{
	CBitMgr::GetInstance()->LoadImageByScene(SCENE_START);

	static_cast<CPlayer*>(m_pPlayer)->SetTile(&m_vecTile);
	
	m_rcStart.left	= 200;
	m_rcStart.top		= 500;
	m_rcStart.right	= 351;
	m_rcStart.bottom	= 543;

	CSoundMgr::GetInstance()->PlayBgm(L"maple_login.mp3");
	
}

int CStart::Update()
{
	ptPoint = CMouse::GetPos();
	if(PtInRect(&m_rcStart, ptPoint))
	{
		m_ButtonState = 1;

		if(GetAsyncKeyState(VK_LBUTTON) & 1)
		{
			return 1;
		}
	}
	else
		m_ButtonState = 0;


	//CObjMgr::GetInstance()->Update();
	return 0;
}

void CStart::Render()
{
	BitBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
		0,
		0,
		1024,
		768,
		CBitMgr::GetInstance()->GetImage(L"BackGround"),
		0,
		0, SRCCOPY);

	TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
		200,
		500,
		151,
		43,
		CBitMgr::GetInstance()->GetImage(L"Start"),
		0,
		(43 * m_ButtonState),
		151,
		43,
		RGB(255, 0, 255));




	//CObjMgr::GetInstance()->Render();

}

void CStart::Release()
{
	
}