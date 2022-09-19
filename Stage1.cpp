#include "StdAfx.h"
#include "Stage1.h"

CStage1::CStage1(void)
{
	TILECOUNTX = 50;
	TILECOUNTY = 40;
	m_ViewTile = false;
}

CStage1::~CStage1(void)
{
	Release();
}

void CStage1::Initialize()
{
	CSoundMgr::GetInstance()->PlayBgm(L"town.mp3");
	CBitMgr::GetInstance()->LoadImageByScene(SCENE_STAGE1);

	//맵 포탈
	CObj* pEffect = new CEffect(1300, 550, 0, OBJ_PORTAL, true);
	pEffect->Initialize();
	CObjMgr::GetInstance()->AddObj(pEffect, OBJ_EFFECT);

	//맵 타일 데이터 로드
	FILE*	pFile = NULL;
	fopen_s(&pFile, "Stage01.dat", "rb");

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

	//몬스터 생성
	/*CObj* pMon = new CMonster(100.f, 300.f, 3);
	pMon->Initialize();

	CObjMgr::GetInstance()->AddObj(pMon, OBJ_MON);*/



	//넘어온 맵의 번호에 따라 캐릭터 초기 위치 설정
	if(0 == static_cast<CPlayer*>(m_pPlayer)->m_iPrevMap)
	{
		m_pPlayer->GetInfo()->fX = 150;
		m_pPlayer->GetInfo()->fY = 500;
		static_cast<CPlayer*>(m_pPlayer)->m_iPrevMap = 1;
	}
	else if(2 == static_cast<CPlayer*>(m_pPlayer)->m_iPrevMap)
	{
		m_pPlayer->GetInfo()->fX = 1350;
		m_pPlayer->GetInfo()->fY = 500;
		static_cast<CPlayer*>(m_pPlayer)->m_iPrevMap = 1;
	}

}

int CStage1::Update()
{
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

	if(GetAsyncKeyState(VK_TAB) & 1)
	{
		return 2;
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

void CStage1::Render()
{
	BitBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
		0 + m_ptScroll.x / 2,
		0 + m_ptScroll.y / 2,
		1920,
		1080,
		CBitMgr::GetInstance()->GetImage(L"BackGround"),

		0,
		0, SRCCOPY);

	TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
		0 + m_ptScroll.x,
		0 + m_ptScroll.y,
		1483,
		743,
		CBitMgr::GetInstance()->GetImage(L"Stage01"),
		0,
		0,
		1483,
		743,
		RGB(66, 66, 66));

	if(m_ViewTile)
	{
		int iCullX = (int)(-m_ptScroll.x) / TILESIZEX;

		int iCullY = (int)(-m_ptScroll.y) / TILESIZEY;

		int iCullEndX = WINCX / TILESIZEX + 2;
		int iCullEndY = WINCY / TILESIZEY + 2;

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
		for(int i = iCullY; i < iCullY + iCullEndY - 1; ++i)
		{
			for(int j = iCullX; j < iCullX + iCullEndX - 1; ++j)
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

void CStage1::Release()
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

	list<CObj*>::iterator EfIter = CObjMgr::GetInstance()->GetList(OBJ_EFFECT)->begin();
	list<CObj*>::iterator EfIter_end = CObjMgr::GetInstance()->GetList(OBJ_EFFECT)->end();

	for(EfIter; EfIter != EfIter_end; ++EfIter)
	{
		delete (*EfIter);
	}
	CObjMgr::GetInstance()->GetList(OBJ_EFFECT)->clear();
}

void CStage1::TileCrush()
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