#include "StdAfx.h"
#include "Stage3.h"

CStage3::CStage3(void)
{
	TILECOUNTX = 69;
	TILECOUNTY = 40;
	m_ViewTile = false;

	m_dwTime	=	GetTickCount();
}

CStage3::~CStage3(void)
{
	Release();
}

void CStage3::Initialize()
{
	CSoundMgr::GetInstance()->PlayBgm(L"field2.mp3");
	CBitMgr::GetInstance()->LoadImageByScene(SCENE_STAGE3);

	//m_pPlayer->GetInfo()->fX = 100;
	//m_pPlayer->GetInfo()->fY = 900;

	FILE*	pFile = NULL;
	fopen_s(&pFile, "Stage03.dat", "rb");

	//상수 저장할 때 임시변수 만들어서 저장해라...
	int iTileCntX = 0;
	int iTileCntY = 0;

	fread(&iTileCntX, sizeof(int), 1, pFile);
	fread(&iTileCntY, sizeof(int), 1, pFile);

	if(m_vecTile.empty() != true)
	{
		for(size_t i = 0; i < m_vecTile.size(); ++i)
		{
			SAFE_DELETE(m_vecTile[i]);
		}
		m_vecTile.clear();
	}

	m_vecTile.reserve(iTileCntX * iTileCntY);

	for(int i = 0; i < iTileCntX * iTileCntY; ++i)
	{
		TILE*	pTile = new TILE;
		fread(pTile, sizeof(TILE), 1, pFile);
		m_vecTile.push_back(pTile);
	}

	fclose(pFile);


	//몬스터 리스트 Get
	m_pListMon = CObjMgr::GetInstance()->GetList(OBJ_MON);

	CObj* pMon = new CMonster(200.f, 500.f,1);
	pMon->Initialize();
	CObjMgr::GetInstance()->AddObj(pMon, OBJ_MON);

	pMon = new CMonster(600.f, 1000.f, 2);
	pMon->Initialize();
	CObjMgr::GetInstance()->AddObj(pMon, OBJ_MON);

	pMon = new CMonster(300.f, 1000.f, 1);
	pMon->Initialize();
	CObjMgr::GetInstance()->AddObj(pMon, OBJ_MON);

	pMon = new CMonster(500.f, 1000.f, 1);
	pMon->Initialize();
	CObjMgr::GetInstance()->AddObj(pMon, OBJ_MON);

	pMon = new CMonster(1300.f, 100.f, 2);
	pMon->Initialize();
	CObjMgr::GetInstance()->AddObj(pMon, OBJ_MON);

	pMon = new CMonster(1000.f, 100.f, 2);
	pMon->Initialize();
	CObjMgr::GetInstance()->AddObj(pMon, OBJ_MON);

	pMon = new CMonster(1500.f, 300.f, 1);
	pMon->Initialize();
	CObjMgr::GetInstance()->AddObj(pMon, OBJ_MON);

	pMon = new CMonster(1600.f, 1000.f, 1);
	pMon->Initialize();
	CObjMgr::GetInstance()->AddObj(pMon, OBJ_MON);

	pMon = new CMonster(1000.f, 100.f, 1);
	pMon->Initialize();
	CObjMgr::GetInstance()->AddObj(pMon, OBJ_MON);
	


	//넘어온 맵의 번호에 따라 캐릭터 초기 위치 설정
	if(2 == static_cast<CPlayer*>(m_pPlayer)->m_iPrevMap)
	{
		m_pPlayer->GetInfo()->fX = 430;
		m_pPlayer->GetInfo()->fY = 250;
		static_cast<CPlayer*>(m_pPlayer)->m_iPrevMap = 3;
	}
	else if(4 == static_cast<CPlayer*>(m_pPlayer)->m_iPrevMap)
	{
		m_pPlayer->GetInfo()->fX = 250;
		m_pPlayer->GetInfo()->fY = 1000;
		static_cast<CPlayer*>(m_pPlayer)->m_iPrevMap = 3;
	}

}

int CStage3::Update()
{
	//몬스터 생성
	if(m_dwTime + 20000 < GetTickCount())
	{
		m_dwTime = GetTickCount();

		CObj* pMon = new CMonster(200.f, 500.f,1);
		pMon->Initialize();
		CObjMgr::GetInstance()->AddObj(pMon, OBJ_MON);

		pMon = new CMonster(600.f, 1000.f, 3);
		pMon->Initialize();
		CObjMgr::GetInstance()->AddObj(pMon, OBJ_MON);

		pMon = new CMonster(300.f, 1000.f, 3);
		pMon->Initialize();
		CObjMgr::GetInstance()->AddObj(pMon, OBJ_MON);

		pMon = new CMonster(500.f, 1000.f, 2);
		pMon->Initialize();
		CObjMgr::GetInstance()->AddObj(pMon, OBJ_MON);

		pMon = new CMonster(1300.f, 100.f, 3);
		pMon->Initialize();
		CObjMgr::GetInstance()->AddObj(pMon, OBJ_MON);

		pMon = new CMonster(1000.f, 100.f, 3);
		pMon->Initialize();
		CObjMgr::GetInstance()->AddObj(pMon, OBJ_MON);

		pMon = new CMonster(1500.f, 300.f, 1);
		pMon->Initialize();
		CObjMgr::GetInstance()->AddObj(pMon, OBJ_MON);

		pMon = new CMonster(1600.f, 1000.f, 3);
		pMon->Initialize();
		CObjMgr::GetInstance()->AddObj(pMon, OBJ_MON);

		pMon = new CMonster(1000.f, 100.f, 3);
		pMon->Initialize();
		CObjMgr::GetInstance()->AddObj(pMon, OBJ_MON);
	}

	if(GetAsyncKeyState('T') & 1)
	{
		if(m_ViewTile)
		{
			m_ViewTile = false;
		}
		else
		{
			m_ViewTile = true;
		}
	}

	TileCrush();

	//for(size_t i = 0; i < m_vecTile.size(); ++i)
	//{
	//	switch(m_vecTile[i]->iOption)
	//	{
	//	case TILE_DISABLE:

	//		if(((m_vecTile[i]->fX - (m_vecTile[i]->fCX / 2)) <= m_pPlayer->GetInfo()->fX)
	//			&& ((m_vecTile[i]->fX + (m_vecTile[i]->fCX / 2)) >= m_pPlayer->GetInfo()->fX)
	//			&& ((m_vecTile[i]->fY - (m_vecTile[i]->fCY / 2)) <= m_pPlayer->GetInfo()->fY + 30)
	//			&& ((m_vecTile[i]->fY + (m_vecTile[i]->fCY / 2)) >= m_pPlayer->GetInfo()->fY + 30))
	//		{
	//			m_pPlayer->GetInfo()->fY -= 5;
	//			static_cast<CPlayer*>(m_pPlayer)->m_fJumpAcc = 0.f;
	//			//m_dwState = PLY_STAND;
	//			static_cast<CPlayer*>(m_pPlayer)->m_bIsJump = false;
	//			//MessageBox(g_hWnd, L"충돌!",L"뜨든!", MB_OK);
	//		}
	//	}
	//}

	CObjMgr::GetInstance()->Update();
	return 0;
}

void CStage3::Render()
{
	BitBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
		static_cast<int>((0 + m_ptScroll.x) / 2.5f),
		static_cast<int>((0 + m_ptScroll.y) / 2.5f),
		1440,
		900,
		CBitMgr::GetInstance()->GetImage(L"BackGround"),
		0,
		0, SRCCOPY);

	TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
		static_cast<int>(0 + m_ptScroll.x),
		static_cast<int>(0 + m_ptScroll.y),
		2070,
		1200,
		CBitMgr::GetInstance()->GetImage(L"Stage03"),
		0,
		0,
		2070,
		1200,
		RGB(66, 66, 66));

	if(m_ViewTile)
	{
		int iCullX = (int)(-m_ptScroll.x) / TILESIZEX;

		int iCullY = (int)(-m_ptScroll.y) / TILESIZEY;

		int iCullEndX = WINCX / TILESIZEX;
		int iCullEndY = WINCY / TILESIZEY;

		//나의 빌어먹을 컬링
		//for(int i = 0; i < TILECOUNTX; ++i)
		//{
		//	for(int j = 0; j < TILECOUNTY; ++j)
		//	{
		//		int iIndex = i * TILECOUNTX + j;

		//		/*if((m_vecTile[iIndex]->fX - TILESIZEX / 2 + m_ptScroll.x < 0)
		//			|| (m_vecTile[iIndex]->fX - TILESIZEX / 2 + m_ptScroll.x > 1024)
		//			|| (m_vecTile[iIndex]->fY - TILESIZEY / 2 + m_ptScroll.y < 0)
		//			|| (m_vecTile[iIndex]->fY - TILESIZEY / 2 + m_ptScroll.y > 768))*/
		//	
		//		/*if(m_vecTile[iIndex]->fX < 0)
		//		{
		//			continue;
		//		}

		//		if(m_vecTile[iIndex]->fX > 1024)
		//		{
		//			continue;
		//		}

		//		if(m_vecTile[iIndex]->fY < 0)
		//		else
		//		*/
		//		if(m_vecTile[iIndex]->fX + 15 > 0 && m_vecTile[iIndex]->fX +15 < 1024 && m_vecTile[iIndex]->fY + 15> 0 && m_vecTile[iIndex]->fX + 15 < 768)
		//		{
		//			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
		//				,int(m_vecTile[iIndex]->fX - TILESIZEX / 2 + m_ptScroll.x)
		//				,int(m_vecTile[iIndex]->fY - TILESIZEY / 2 + m_ptScroll.y)
		//				,TILESIZEX
		//				,TILESIZEY
		//				,CBitMgr::GetInstance()->GetImage(L"Tile")
		//				,TILESIZEX * m_vecTile[iIndex]->iDrawID
		//				,0
		//				,30
		//				,30
		//				, RGB(66, 66, 66));
		//		}
		//	}
		//}


		//송쌤의 컬링
		for(int i = iCullY; i < iCullY + iCullEndY; ++i)
		{
			for(int j = iCullX; j < iCullX + iCullEndX; ++j)
			{
				int iIndex = i * TILECOUNTX + j;

				if(iIndex < 0 || TILECOUNTX * TILECOUNTY < iIndex)
					continue;

				

				TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
				,int(m_vecTile[iIndex]->fX - TILESIZEX / 2 + m_ptScroll.x)
				,int(m_vecTile[iIndex]->fY - TILESIZEY / 2 + m_ptScroll.y)
				,TILESIZEX
				,TILESIZEY
				,CBitMgr::GetInstance()->GetImage(L"Tile")
				,TILESIZEX * m_vecTile[iIndex]->iDrawID
				,0
				,30
				,30
				, RGB(66, 66, 66));
				
			}
		}
	}




	CObjMgr::GetInstance()->Render();
}

void CStage3::Release()
{
	vector<TILE*>::iterator iter = m_vecTile.begin();
	vector<TILE*>::iterator iter_end = m_vecTile.end();

	for(; iter != iter_end; ++iter)
	{
		SAFE_DELETE(*iter);
	}

	m_vecTile.clear();

	list<CObj*>::iterator MonIter = CObjMgr::GetInstance()->GetList(OBJ_MON)->begin();
	list<CObj*>::iterator MonIter_end = CObjMgr::GetInstance()->GetList(OBJ_MON)->end();

	for(MonIter; MonIter != MonIter_end; ++MonIter)
	{
		delete (*MonIter);
	}
	CObjMgr::GetInstance()->GetList(OBJ_MON)->clear();
}

void CStage3::TileCrush()
{
	vector<TILE*>::iterator iter		=	m_vecTile.begin();
	vector<TILE*>::iterator iter_end	=	m_vecTile.end();

	for(iter; iter != iter_end; ++iter)
	{
		static_cast<CPlayer*>(m_pPlayer)->TileCrush(*iter);
		
		list<CObj*>::iterator MonIter = m_pListMon->begin();
		list<CObj*>::iterator MonIter_end = m_pListMon->end();

		for(MonIter; MonIter != MonIter_end; ++MonIter)
		{
			static_cast<CMonster*>(*MonIter)->TileCrush(*iter);
		}

	}
}