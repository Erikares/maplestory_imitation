#include "StdAfx.h"
#include "MainGame.h"


CMainGame::CMainGame(void)
{
	m_bIsMenu		= false;
	m_bTransScene	= false;
	m_bNotUpdate	= false;
	m_bBlackScene	= false;

	m_iBlend		= 0;
	m_iScene		= 0;

	m_DC = GetDC(g_hWnd);
	m_ptScroll.x = 0;
	m_ptScroll.y = 0;

	srand((unsigned)time(NULL));
	CSoundMgr::GetInstance()->LoadSoundFile();
}

CMainGame::~CMainGame(void)
{
	Release();
}

void CMainGame::Initialize()
{

	CObj* pObj = new CPlayer;
	pObj->Initialize();


	CSceneMgr::GetInstance()->SetPlayer(pObj);
	CSceneMgr::GetInstance()->SetScene(SCENE_START);
	
	CObjMgr::GetInstance()->AddObj(pObj, OBJ_PLY);

	CBitMgr::GetInstance()->Initialize();

	

	//메인 UI, 플레이어 정보 가져감.
	m_pUI = new CMainUI;
	m_pUI->SetPlayer(pObj);
	m_pUI->Initialize();
	
	//장비 UI, 플레이어 정보 가져감
	CUI* pUi = new CEquipUI;
	CUiMgr::GetInstance()->AddUi(pUi, L"EquipUI");
	pUi->SetPlayer(pObj);
	pUi->Initialize();
		
	//인벤 UI, 플레이어 정보, 인벤 벡터 가져감
	pUi = new CInvenUI;
	CUiMgr::GetInstance()->AddUi(pUi, L"InvenUI");
	pUi->SetPlayer(pObj);
	static_cast<CInvenUI*>(pUi)->SetVector(static_cast<CPlayer*>(pObj)->GetVector());

	pUi = new CSkillUI;
	CUiMgr::GetInstance()->AddUi(pUi, L"SkillUI");

	pUi = new CStateUI;
	CUiMgr::GetInstance()->AddUi(pUi, L"StateUI");

	
	pUi = NULL;

	//AllocConsole();

	/*freopen("CONIN$", "rb", stdin);
	freopen("CONOUT$", "wb", stdout);
	freopen("CONOUT$", "wb", stderr);*/
}

void CMainGame::Update()
{
	//cout << "Mouse - X: " << CMouse::GetPos().x << "   Y: " << CMouse::GetPos().y << endl;
	//cout << "Scroll X : " << m_ptScroll.x << "      Scroll Y : " << m_ptScroll.y << endl;
	//if(CKeyMgr_60::GetInstance()->GetKeyDown(VK_LBUTTON))
	/*if(GetAsyncKeyState(VK_LBUTTON) & 0x8001)
	{
		cout << "Click!" << endl;
	}*/


	CursorName = L"None";

	if(!m_bNotUpdate)
	{
		m_iScene = CSceneMgr::GetInstance()->GetScene()->Update();
		if(m_iScene == 1)
		{
			//CSceneMgr::GetInstance()->SetScene(SCENE_STAGE2);
			m_bTransScene = true;
			m_bNotUpdate = true;
		}
		else if(m_iScene == 2)
		{
			m_bTransScene = true;
			m_bNotUpdate = true;
		}
		else if(m_iScene == 3)
		{
			m_bTransScene = true;
			m_bNotUpdate = true;
		}
		
		CUiMgr::GetInstance()->Update();
	}
	//m_pInvenUI->Update();
}

void CMainGame::Render()
{


	CSceneMgr::GetInstance()->GetScene()->Render();

	CUiMgr::GetInstance()->Render();

	if(m_bIsMenu)
		m_pUI->Render();
	




	if(m_bTransScene)
	{
		if(!m_bBlackScene)
		{
			m_iBlend += 5;
		}
		else
		{
			m_iBlend -= 5;
		}
			
		
		HDC		dc = GetDC(g_hWnd);
		HDC		dcTemp = CreateCompatibleDC(dc);

		HBITMAP hBitmap = CreateCompatibleBitmap(dc, 1024, 768);
		HBITMAP	hOld = (HBITMAP)SelectObject(dcTemp, hBitmap);

		BLENDFUNCTION	tFunction;
		tFunction.BlendOp = AC_SRC_OVER;
		tFunction.BlendFlags = 0;
		tFunction.SourceConstantAlpha = m_iBlend;	//이 수치가 투명도...
		tFunction.AlphaFormat = 0;
		//짤라온 DC를 다시 백버퍼에다가 그려준다..
		AlphaBlend(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
			0,0,1024,768,
			CBitMgr::GetInstance()->GetImage(L"Black"),
			0,
			0,
			1024,
			768,
			tFunction);

		hBitmap = (HBITMAP)SelectObject(dcTemp, hOld);
		DeleteObject(hBitmap);
		DeleteDC(dcTemp);
		ReleaseDC(g_hWnd, dc);

		if(m_iBlend == 250)
		{
			m_bIsMenu = true;
			m_bBlackScene = true;
			m_bNotUpdate = false;

			//화면이 완벽하게 어두워지면 다음씬으로 넘어간다.
			switch(m_iScene)
			{
			case 1:
				CSceneMgr::GetInstance()->SetScene(SCENE_STAGE1);
				break;
			case 2:
				CSceneMgr::GetInstance()->SetScene(SCENE_STAGE2);
				break;
			case 3:
				CSceneMgr::GetInstance()->SetScene(SCENE_STAGE3);
				break;
			}
		}

		if(m_iBlend == 0)
		{
			m_bBlackScene = false;
			m_bTransScene = false;
		}
	}

	BitBlt(m_DC, 0, 0, WINCX, WINCY,
	CBitMgr::GetInstance()->GetImage(L"BackBuffer"), 0, 0, SRCCOPY);

	/*BitBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
		0, 0, 1024, 768,
		CBitMgr::GetInstance()->GetImage(L"Black"),
		0, 0, SRCCOPY);*/

	
}

void CMainGame::Release()
{
	FreeConsole();
	CObjMgr::GetInstance()->DestroyInstance();
	CBitMgr::GetInstance()->DestroyInstance();
	CKeyMgr_60::GetInstance()->DestroyInstance();
	CSceneMgr::GetInstance()->DestroyInstance();
	CUiMgr::GetInstance()->DestroyInstance();

	SAFE_DELETE(m_pUI);
}