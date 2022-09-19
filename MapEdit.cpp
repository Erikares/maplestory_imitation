#include "StdAfx.h"
#include "MapEdit.h"
#include "BitMgr.h"
#include "KeyMgr_60.h"
#include "Mouse.h"

CMapEdit::CMapEdit(void)
{
	m_fScrollX = 0.f;
	m_fScrollY = 0.f;
	
	TILECOUNTX = 69;
	TILECOUNTY = 40;
}

CMapEdit::~CMapEdit(void)
{
	Release();
}

void CMapEdit::Initialize(void)
{
	CBitMgr::GetInstance()->LoadImageByScene(SCENE_MAP);

	for(int i = 0; i < TILECOUNTY; ++i)
	{
		for(int j = 0; j < TILECOUNTX; ++j)
		{
			float fX = float((TILESIZEX * j) + TILESIZEX / 2);
			float fY = float((TILESIZEY * i) + TILESIZEY / 2);

			m_vecTile.push_back(new TILE(fX, fY));
		}
	}
}

int CMapEdit::Update(void)
{
	Picking();
	KeyCheck();


	return 0;
}

void CMapEdit::Render(void)
{
	//���� ���� �����ս��� ���� ���ؼ�
	//ȭ�鿡 �׷����� �� ��ü�鸸 �׸���
	//�׸��� ���� ���� �ɷ����� �۾���
	//�츮�� �ø��̶�� �θ���...

	//ȭ�� ���� ������ ���� �κ��� ������ ���� �׷����� �� ����X
	int iCullX = (int)(-m_fScrollX) / TILESIZEX;

	//ȭ�� ���� ������ ���� �κ��� ������ ���� �׷����� �� ����Y
	int iCullY = (int)(-m_fScrollY) / TILESIZEY;

	//ȭ�� ũ�Ⱑ ������ �� ȭ�� �ȿ� �� �� �ִ� Ÿ���� ������
	//������ �ֱ� ������ �Ʒ��� ���� ������ ������ x,y�� ���� �� �ִ�.
	int iCullEndX = WINCX / TILESIZEX + 2;
	int iCullEndY = WINCY / TILESIZEY + 2;

	BitBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
				static_cast<int>(0 + m_fScrollX) / 2.5f,
				static_cast<int>(0 + m_fScrollY) / 2.5f,
				1920,
				1080,
				CBitMgr::GetInstance()->GetImage(L"BackGround"),
				0,
				0, SRCCOPY);

			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
				static_cast<int>(0 + m_fScrollX),
				static_cast<int>(0 + m_fScrollY),
				2070,
				1200,
				CBitMgr::GetInstance()->GetImage(L"Stage"),
				0,
				0,
				2070,
				1200,
				RGB(66, 66, 66));


	for(int i = iCullY; i < iCullY + iCullEndY - 1; ++i)
	{
		for(int j = iCullX; j < iCullX + iCullEndX - 1; ++j)
		{
			int iIndex = i * TILECOUNTX + j;

			if(iIndex < 0 || TILECOUNTX * TILECOUNTY < iIndex)
				continue;

			

			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
			,int(m_vecTile[iIndex]->fX - TILESIZEX / 2 + m_fScrollX)
			,int(m_vecTile[iIndex]->fY - TILESIZEY / 2 + m_fScrollY)
			,TILESIZEX
			,TILESIZEY
			,CBitMgr::GetInstance()->GetImage(L"Tile")
			,TILESIZEX * m_vecTile[iIndex]->iDrawID
			,0
			,30
			,30
			, RGB(66, 66, 66));
			
			//BitBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
			//	int(m_vecTile[iIndex]->fX - TILESIZEX / 2 + m_fScrollX) ,
			//	int(m_vecTile[iIndex]->fY - TILESIZEY / 2 + m_fScrollY),
			//	TILESIZEX,
			//	TILESIZEY,
			//	CBitMgr::GetInstance()->GetImage(L"Tile"),
			//	TILESIZEX * m_vecTile[iIndex]->iDrawID,
			//	0,
			//	SRCCOPY);
		}
	}
}

void CMapEdit::Release(void)
{
	vector<TILE*>::iterator iter = m_vecTile.begin();
	vector<TILE*>::iterator iter_end = m_vecTile.end();

	for(; iter != iter_end; ++iter)
	{
		SAFE_DELETE(*iter);
	}

	m_vecTile.clear();
}

void CMapEdit::Picking(void)
{
	//���ϰ��� �ϴ� ��ǥ�� ���� �ε����� ȯ���Ѵ�..
	//

	//x�� ��ǥ�� Ÿ���� x������ ũ��� ������.(x�ε��� ��ȣ�� ���ϴ� ���..)
	//y�� ��ǥ�� Ÿ���� y������ ũ��� ������.(y�ε��� ��ȣ�� ���ϴ� ���..)

	if(CKeyMgr_60::GetInstance()->GetKeyDown(VK_LBUTTON))
	//if(GetAsyncKeyState(VK_LBUTTON) & 1)
	{
		//���콺 ��ǥ���� ��ũ�� ���� ���������� �Ѵ�...
		int iXIndex = (CMouse::GetPos().x - int(m_fScrollX)) / TILESIZEX;
		int iYIndex = (CMouse::GetPos().y - int(m_fScrollY)) / TILESIZEY;

		//�̰� �츮�� ���� �ε���...
		int iIndex = iYIndex * TILECOUNTX + iXIndex;

		if(m_vecTile[iIndex]->iDrawID == 4)
		{
			m_vecTile[iIndex]->iDrawID = 0;
			m_vecTile[iIndex]->iOption = 0;
		}
		else
		{
			++(m_vecTile[iIndex]->iDrawID);
			++(m_vecTile[iIndex]->iOption);
		}
	}

	if(CKeyMgr_60::GetInstance()->GetKeyUp(VK_LBUTTON))
	{
	}

	if(CKeyMgr_60::GetInstance()->GetKeyDown(VK_RBUTTON))
	{
		//���콺 ��ǥ���� ��ũ�� ���� ���������� �Ѵ�...
		int iXIndex = (CMouse::GetPos().x - int(m_fScrollX)) / TILESIZEX;
		int iYIndex = (CMouse::GetPos().y - int(m_fScrollY)) / TILESIZEY;

		//�̰� �츮�� ���� �ε���...
		int iIndex = iYIndex * TILECOUNTX + iXIndex;

		if(m_vecTile[iIndex]->iDrawID == 0)
		{
			m_vecTile[iIndex]->iDrawID = 4;
			m_vecTile[iIndex]->iOption = 4;
		}
		else
		{
			--(m_vecTile[iIndex]->iDrawID);
			--(m_vecTile[iIndex]->iOption);
		}
	}

	if(CKeyMgr_60::GetInstance()->GetKeyUp(VK_RBUTTON))
	{
	}


}

void CMapEdit::KeyCheck(void)
{
	if(CKeyMgr_60::GetInstance()->GetKeyState(VK_LEFT))
	{
		m_fScrollX += 10.f;

		
	}
	if(CKeyMgr_60::GetInstance()->GetKeyState(VK_RIGHT))
	{
		m_fScrollX -= 10.f;

		//��ũ�Ѱ��� �������̱� ������ 0���� Ŀ���� ��찡
		//�������� ����� ����̴�..
	}
	if(CKeyMgr_60::GetInstance()->GetKeyState(VK_UP))
	{
		m_fScrollY += 10.f;
	}
	if(CKeyMgr_60::GetInstance()->GetKeyState(VK_DOWN))
	{
		m_fScrollY -= 10.f;
	}

	if(m_fScrollX > 0)
		m_fScrollX = 0;
	
	if(m_fScrollY > 0)
		m_fScrollY = 0;

	if(m_fScrollX < WINCX - (TILESIZEX * TILECOUNTX))
		m_fScrollX = static_cast<float>(WINCX - (TILESIZEX * TILECOUNTX));
	
	if(m_fScrollY < WINCY - (TILESIZEY * TILECOUNTY))
		m_fScrollY = static_cast<float>(WINCY - (TILESIZEY * TILECOUNTY));

	if(CKeyMgr_60::GetInstance()->GetKeyDown('Z'))
	{
		SaveData();
	}
	if(CKeyMgr_60::GetInstance()->GetKeyDown('X'))
	{
		LoadData();
	}


}

void CMapEdit::SaveData(void)
{
	FILE*	pFile = NULL;
	fopen_s(&pFile, "Stage03.dat", "wb");

	//��� ������ �� �ӽú��� ���� �����ض�...
	int iTileX = TILECOUNTX;
	int iTileY = TILECOUNTY;

	fwrite(&iTileX, sizeof(int), 1, pFile);
	fwrite(&iTileY, sizeof(int), 1, pFile);

	for(size_t i = 0; i < m_vecTile.size(); ++i)
	{
		fwrite(m_vecTile[i], sizeof(TILE), 1, pFile);
	}

	fclose(pFile);

	MessageBox(g_hWnd,  L"SaveData Succeed", L"SaveData!!", MB_OK);
}

void CMapEdit::LoadData(void)
{
	FILE*	pFile = NULL;
	fopen_s(&pFile, "Stage03.dat", "rb");

	//��� ������ �� �ӽú��� ���� �����ض�...
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
}
