#include "StdAfx.h"
#include "Monster.h"

CMonster::CMonster(void)
{
}

CMonster::CMonster(float _fX, float _fY, int iType)
{
	m_iMonType		=	iType;
	m_tInfo.fX 		= 	_fX;
	m_tInfo.fY 		= 	_fY;

	m_eArrow		=	DIR_RIGHT;
	m_bIsAtk		=	false;
	m_bIsJump		=	false;
	m_bIsFall		=	false;
	m_bIsKnockBack	=	false;

	m_fJumpAcc		=	0.f;
	m_fKnockBack	=	0.f;

	m_dwFrameTime	=	GetTickCount();

	m_iBlend		=	255;


	switch(iType)
	{
	case MON1:
		m_tInfo.fCX		=	50;
		m_tInfo.fCY		=	100;

		m_iAction		=	0;

		m_eArrow		=	DIR_RIGHT;

		m_fJumpAcc		=	0.f;
		m_fKnockBack	=	0.f;

		m_pName			=	L"Right_Snowman";
		m_tFrame		=	FRAME(0, 3, 0, 100);

		break;

	case MON2:			
		m_tInfo.fCX		=	80;
		m_tInfo.fCY		=	50;
		m_iAction		=	0;

		m_eArrow		=	DIR_RIGHT;

		m_fJumpAcc		=	0.f;
		m_fKnockBack	=	0.f;

		m_pName			=	L"Right_Wolf";
		m_tFrame		=	FRAME(0, 3, 0, 100);


		break;

	case MON3:
		m_tInfo.fCX		=	70;
		m_tInfo.fCY		=	100;
		m_iAction		=	0;

		m_eArrow		=	DIR_RIGHT;

		m_fJumpAcc		=	0.f;
		m_fKnockBack	=	0.f;

		m_pName			=	L"Right_Yeti";
		m_tFrame		=	FRAME(0, 3, 0, 100);

		break;
	}

	m_dwState		=	MON_STAND;


}

CMonster::~CMonster(void)
{
	Release();
}
void CMonster::Initialize()
{
	srand((unsigned)time(NULL));

	switch(m_iMonType)
	{
	case MON1:
		m_tMonster.iHp		=	5000;
		m_tMonster.iMaxHp	=	5000;
		m_tMonster.iAtk		=	500;
		m_tMonster.iDef		=	100;
		break;

	case MON2:
		m_tMonster.iHp		=	7000;
		m_tMonster.iMaxHp	=	7000;
		m_tMonster.iAtk		=	1200;
		m_tMonster.iDef		=	100;
		break;

	case MON3:
		m_tMonster.iHp		=	150000;
		m_tMonster.iMaxHp	=	15000;
		m_tMonster.iAtk		=	2500;
		m_tMonster.iDef		=	100;
		break;
	}


	m_dwActiveTime		=	GetTickCount();
	m_dwActive			=	4000;

}

int CMonster::Update()
{
	int iExit = 0;

	iExit = MoveCheck();
	FrameMove();
	CObj::Update();
	return iExit;
}

void CMonster::Render()
{
	//Rectangle(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
	//	m_Rect.left + m_ptScroll.x,
	//	m_Rect.top + m_ptScroll.y,
	//	m_Rect.right + m_ptScroll.x,
	//	m_Rect.bottom + m_ptScroll.y);

	if(m_iAction != 7)
	{
		TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
			static_cast<int>(m_tInfo.fX - 100 + m_ptScroll.x),
			static_cast<int>(m_tInfo.fY - 100 + m_ptScroll.y),
			200,
			200,
			CBitMgr::GetInstance()->GetImage(m_pName),
			200 * m_tFrame.iScene,
			200 * m_tFrame.iFrameStart,
			200, 200,
			RGB(140, 203, 157));
	}
	else
	{

		HDC		dc = GetDC(g_hWnd);
		HDC		dcTemp = CreateCompatibleDC(dc);

		HBITMAP hBitmap = CreateCompatibleBitmap(dc, 200,200);//int(m_tInfo.fCX), int(m_tInfo.fCY));
		HBITMAP	hOld = (HBITMAP)SelectObject(dcTemp, hBitmap);


		//������ ���� ��ġ�� �÷��̾� ��ġ�� �������� �������
		//��ũ�� ���� ���ؼ� ����ؾ� �Ѵ�.
		int iOriStartX = int(m_tInfo.fX - 100) + m_ptScroll.x;
		int	iOriStartY = int(m_tInfo.fY - 100) + m_ptScroll.y;


		//����� ���� ��ġ�� �ϴ�0���� �ʱ�ȭ �س�
		int iDestStartX = 0;
		int iDestStartY = 0;

		//����� �� ��ġ�� �ϴ� �÷��̾� ������� �ʱ�ȭ..
		int iDestEndX = 200;
		int iDestEndY = 200;

		//������ ���� ���� ��ġ�� 0�̵Ǹ� ���簡 �����ʴ´�.(������ �Ǵ� ��Ȳ)
		//��������� �ʱ�ȭ�� �� �־�� ��..
		if(iOriStartX < 0)
		{
			//����� ���� ��ġ�� �ڷ� �������� �Ѵ�.
			iDestStartX = -iOriStartX;
			//���� ���� ��ġ�� 0���� ������ 0���� �����Ѵ�.
			iOriStartX = 0;
		}

		//������ ���� ���� ��ġ + �����
		//�̹����� �Ѿ�� �Ǹ� ���簡 ���� �ʴ´�.
		else if(iOriStartX > WINCX - 200)
		{
			//����� �� ��ġ�� �̹����� ��� ��ŭ��
			//������� ����� �Ѵ�.
			iDestEndX = int(200 + ((WINCX - 200) - iOriStartX));
		}
		//y�൵ �Ȱ��� ó���� �� ��߉�
		if(iOriStartY < 0)
		{
			iDestStartY = -iOriStartY;
			iOriStartY = 0;
		}
		else if(iOriStartY > WINCY - 200)
		{
			iDestEndY = int(200 + ((WINCY - 200) - iOriStartY));
		}


		//����ȭ ó���� ���ؼ� ���ݱ��� ������Ʈ���� �׷��� �ִ� ����۸�
		//���ο� DC���ٰ� �����ϰ� �� DC���� �÷��̾� �̹����� �ø� ������
		//�� dc�� ��°�� ����ۿ��ٰ� �����ϰ� �����Ѵ�.

		//����ۿ��� �÷��̾� ������ ©��
		//���� �ӽ÷� ���� DC���ٰ� ���縦 �Ѵ�.
		TransparentBlt(dcTemp,		//bitblt �� �׷��� �������
			iDestStartX,
			iDestStartY,
			iDestEndX,
			iDestEndY,
			CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
			iOriStartX,
			iOriStartY,
			iDestEndX,
			iDestEndY,
			RGB(0, 0, 0));


		//©�� ���� dc���ٰ� �÷��̾ �׸���.(�� �� ����� ����..)
		TransparentBlt(dcTemp,
			0,//m_tInfo.fX - 100 + m_ptScroll.x,
			0,//m_tInfo.fY - 100 + m_ptScroll.y,
			200,
			200,
			CBitMgr::GetInstance()->GetImage(m_pName),
			200 * m_tFrame.iScene,
			200 * m_tFrame.iFrameStart,
			200, 200,
			RGB(140, 203, 157));


		BLENDFUNCTION	tFunction;
		tFunction.BlendOp = AC_SRC_OVER;
		tFunction.BlendFlags = 0;
		tFunction.SourceConstantAlpha = m_iBlend;	//�� ��ġ�� ����...
		tFunction.AlphaFormat = 0;
		//©��� DC�� �ٽ� ����ۿ��ٰ� �׷��ش�..
		AlphaBlend(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
			int(m_tInfo.fX - 100) + m_ptScroll.x,
			int(m_tInfo.fY - 100) + m_ptScroll.y,
			200,
			200,
			dcTemp,
			0,
			0,
			200,
			200,
			tFunction);

		hBitmap = (HBITMAP)SelectObject(dcTemp, hOld);
		DeleteObject(hBitmap);
		DeleteDC(dcTemp);
		ReleaseDC(g_hWnd, dc);



	}

	//if(m_iBlend > 0)
	m_iBlend -= 5;
	/*else
	m_iBlend = 0;*/
}

void CMonster::Release()
{
}

int CMonster::MoveCheck()
{
	switch(m_iMonType)
	{
	case MON1:
		//Ȱ�� ���� ����
		if(m_dwActiveTime + m_dwActive < GetTickCount())
		{
			//������ �׼��� ��� �׼��̾��ٸ� 1�� ��ȯ
			if(m_iAction == 7)
				return 1;


			m_dwActiveTime = GetTickCount();
			m_iAction = rand() % 3 + 1;
		}

		//���� Ȱ��
		switch(m_iAction)
		{

		case 1:
			//���� ����
			//cout << "�ʻ� ����" << endl;
			m_dwState = MON_STAND;
			m_dwActive = 4000;
			break;

		case 2:
			//���������� �̵�
			//cout << "�ʻ� ����½" << endl;
			m_pName		= L"Right_Snowman";
			m_dwState = MON_RUN;
			m_eArrow  = DIR_RIGHT;
			m_tInfo.fX += 2;
			m_dwActive = 2000;
			break;

		case 3:
			//�������� �̵�
			//cout << "�ʻ� ����" << endl;
			m_pName		= L"Left_Snowman";
			m_dwState = MON_RUN;
			m_eArrow  = DIR_LEFT;
			m_tInfo.fX -= 2;
			m_dwActive = 2000;
			break;

		case 4:
			//cout << "�ʻ� ��Ǫ" << endl;
			m_dwState = MON_JUMP;
			m_bIsJump = true;
			m_dwActive = 0;
			break;

		case 5:
			break;

		case 6:
			//cout << "�ƾ�!" << endl;
			m_dwState = MON_HIT;
			m_dwActive = 500;
			break;
		case 7:
			//cout << "���...." << endl;
			m_dwState = MON_DEAD;
			m_dwActive = 500;
			break;
		}
		break;

	case MON2:
		//Ȱ�� ���� ����
		if(m_dwActiveTime + m_dwActive < GetTickCount())
		{
			//������ �׼��� ��� �׼��̾��ٸ� 1�� ��ȯ
			if(m_iAction == 7)
				return 1;


			m_dwActiveTime = GetTickCount();
			m_iAction = rand() % 5 + 1;
		}

		//���� Ȱ��
		switch(m_iAction)
		{

		case 1:
			//���� ����
			//cout << "�ʻ� ����" << endl;
			m_dwState = MON_STAND;
			m_dwActive = 4000;
			break;

		case 2:
			//���������� �̵�
			//cout << "�ʻ� ����½" << endl;
			m_pName		= L"Right_Wolf";
			m_dwState = MON_RUN;
			m_eArrow  = DIR_RIGHT;
			m_tInfo.fX += 2;
			m_dwActive = 2000;
			break;

		case 3:
			//�������� �̵�
			//cout << "�ʻ� ����" << endl;
			m_pName		= L"Left_Wolf";
			m_dwState = MON_RUN;
			m_eArrow  = DIR_LEFT;
			m_tInfo.fX -= 2;
			m_dwActive = 2000;
			break;

		case 4:
			//cout << "�ʻ� ��Ǫ" << endl;
			m_dwState = MON_JUMP;
			m_bIsJump = true;
			m_dwActive = 0;
			break;

		case 5:
			break;

		case 6:
			//cout << "�ƾ�!" << endl;
			m_dwState = MON_HIT;
			m_dwActive = 500;
			break;
		case 7:
			//cout << "���...." << endl;
			m_dwState = MON_DEAD;
			m_dwActive = 500;
			break;
		}

		break;

	case MON3:
		//Ȱ�� ���� ����
		if(m_dwActiveTime + m_dwActive < GetTickCount())
		{
			//������ �׼��� ��� �׼��̾��ٸ� 1�� ��ȯ
			if(m_iAction == 7)
				return 1;


			m_dwActiveTime = GetTickCount();
			m_iAction = rand() % 5 + 1;
		}

		//���� Ȱ��
		switch(m_iAction)
		{

		case 1:
			//���� ����
			//cout << "�ʻ� ����" << endl;
			m_dwState = MON_STAND;
			m_dwActive = 4000;
			break;

		case 2:
			m_pName		= L"Right_Yeti";
			m_dwState = MON_RUN;
			m_eArrow  = DIR_RIGHT;
			m_tInfo.fX += 2;
			m_dwActive = 2000;
			break;

		case 3:
			m_pName		= L"Left_Yeti";
			m_dwState = MON_RUN;
			m_eArrow  = DIR_LEFT;
			m_tInfo.fX -= 2;
			m_dwActive = 2000;
			break;

		case 4:
			m_dwState = MON_JUMP;
			m_bIsJump = true;
			m_dwActive = 0;
			break;

		case 5:
			break;

		case 6:
			//cout << "�ƾ�!" << endl;
			m_dwState = MON_HIT;
			m_dwActive = 500;
			break;
		case 7:
			//cout << "���...." << endl;
			m_dwState = MON_DEAD;
			m_dwActive = 500;
			break;
		}

	}


	if(m_bIsJump)
	{
		m_fJumpAcc += 0.3f;
		m_tInfo.fY += -8.f + m_fJumpAcc;
	}

	if(m_bIsKnockBack)
	{
		m_dwState = MON_HIT;
		if(m_fKnockBack < -0.5f)
		{
			m_fKnockBack += 0.3f;
			m_tInfo.fX += m_fKnockBack;
		}
		else if(m_fKnockBack > 0.5f)
		{
			m_fKnockBack += -0.3f;
			m_tInfo.fX += m_fKnockBack;
		}
		else
			m_bIsKnockBack = false;
	}
	return 0;
}
void CMonster::TileCrush(TILE*	_Tile)
{
	//���Ϳ� �ٴ��� �Ÿ� ��
	int	iMonDis		=	0;

	switch(m_iMonType)
	{
	case MON1:
		iMonDis		=	50;
		break;
	case MON2:
		iMonDis		=	25;
		break;
	case MON3:
		iMonDis		=	50;
		break;
	}



	switch(_Tile->iOption)
	{
		//�� Ÿ�� �浹
	case TILE_NORMAL:
		//ĳ������ �ٴ��� �� Ÿ���� ��, �߶� ���� ����

		if((_Tile->fX - (_Tile->fCX / 2) <= m_tInfo.fX)
			&& (_Tile->fX + (_Tile->fCX / 2) >= m_tInfo.fX)
			&& (_Tile->fY - (_Tile->fCY / 2) <= m_tInfo.fY + iMonDis + 30)
			&& (_Tile->fY + (_Tile->fCY / 2) >= m_tInfo.fY + iMonDis + 30))
		{

			if(m_bIsFall == false && m_bIsJump == false)
			{
				//cout << "�߶�!!!!!!!" << endl;
				m_bIsFall = true;
				//m_tInfo.fY -= 5;
				m_fJumpAcc = 10.f;
				m_bIsJump = true;
			}
			return;
		}
		break;



		//���� �Ұ� Ÿ��(�ٴ� �� ���)
	case TILE_DISABLE:
	case TILE_HILL:

		//ĳ���Ͱ� ���� ���� ����� �� �о��ش�.
		if((_Tile->fX - (_Tile->fCX / 2) <= m_tInfo.fX - 20)
			&& (_Tile->fX + (_Tile->fCX / 2) >= m_tInfo.fX - 20)
			&& (_Tile->fY - (_Tile->fCY / 2) <= m_tInfo.fY)
			&& (_Tile->fY + (_Tile->fCY / 2) >= m_tInfo.fY))
		{

			m_tInfo.fX += 2;

			return;
		}

		//ĳ���Ͱ� ������ ���� ����� �� �о��ش�.
		if((_Tile->fX - (_Tile->fCX / 2) <= m_tInfo.fX + 20)
			&& (_Tile->fX + (_Tile->fCX / 2) >= m_tInfo.fX + 20)
			&& (_Tile->fY - (_Tile->fCY / 2) <= m_tInfo.fY)
			&& (_Tile->fY + (_Tile->fCY / 2) >= m_tInfo.fY))
		{
			m_tInfo.fX -= 2;

			return;
		}
		//ĳ������ �ٴ��� ����� �� Ÿ�� ���� �÷��ش�.
		if((_Tile->fX - (_Tile->fCX / 2) <= m_tInfo.fX)
			&& (_Tile->fX + (_Tile->fCX / 2) >= m_tInfo.fX)
			&& (_Tile->fY - (_Tile->fCY / 2) <= m_tInfo.fY + iMonDis)
			&& (_Tile->fY + (_Tile->fCY / 2) >= m_tInfo.fY + iMonDis))
		{
			//cout << "�����پƾƤ�������" << endl;
			m_tInfo.fY -= 5;
			m_fJumpAcc = 0.f;
			m_bIsJump = false;
			m_bIsFall = false;

			return;
		}
		break;
	}

}
void CMonster::FrameMove(void)
{
	switch(m_iMonType)
	{
	case MON1:

		if(m_dwState != m_dwPrevState)
		{
			switch(m_dwState)
			{
			case MON_STAND:
				m_tFrame = FRAME(0, 3, 0, 400);
				break;

			case MON_RUN:
				m_tFrame = FRAME(0, 3, 0, 400);
				break;
			case MON_HIT:
				m_tFrame = FRAME(1, 1, 1, 10000);
				break;
			case MON_DEAD:
				m_tFrame = FRAME(0, 3, 1, 150);
				break;
			}
			m_dwPrevState = m_dwState;
		}
		break;

	case MON2:

		if(m_dwState != m_dwPrevState)
		{
			switch(m_dwState)
			{
			case MON_STAND:
				m_tFrame = FRAME(0, 3, 0, 400);
				break;

			case MON_RUN:
				m_tFrame = FRAME(0, 2, 1, 400);
				break;
			case MON_HIT:
				m_tFrame = FRAME(3, 3, 1, 10000);
				break;
			case MON_DEAD:
				m_tFrame = FRAME(0, 3, 2, 150);
				break;
			}
			m_dwPrevState = m_dwState;
		}
		break;

	case MON3:

		if(m_dwState != m_dwPrevState)
		{
			switch(m_dwState)
			{
			case MON_STAND:
				m_tFrame = FRAME(0, 2, 0, 400);
				break;

			case MON_RUN:
				m_tFrame = FRAME(0, 3, 1, 400);
				break;
			case MON_HIT:
				m_tFrame = FRAME(3, 3, 0, 10000);
				break;
			case MON_DEAD:
				m_tFrame = FRAME(0, 3, 2, 150);
				break;
			}
			m_dwPrevState = m_dwState;
		}
		break;
	}

	if(m_dwFrameTime + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_dwFrameTime = GetTickCount();
		++m_tFrame.iFrameStart;
		//cout << "Frameeeeeeeee : " << m_tFrame.iFrameStart << endl;
	}




	if(m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		m_tFrame.iFrameStart = 0;

		//���� �� ������ ��� ���� ����
		if(m_bIsAtk)
		{
			m_bIsAtk = false;
			m_dwState = PLY_STAND;
		}
	}

}
void CMonster::HpMgr(int _iDmg, int iAtkType, eArrow e_Arrow)
{
	CObj* pEffect = NULL;

	switch(iAtkType)
	{
	case Atk_SHOOT:
		cout << "HP : " << m_tMonster.iHp << endl;
		m_dwActiveTime = GetTickCount();
		m_iAction = 6;
		m_tMonster.iHp -= _iDmg;
		m_bIsKnockBack = true;

		pEffect = new CEffect(m_tInfo.fX, m_tInfo.fY, _iDmg, Atk_DMG, false);
		pEffect->Initialize();

		CObjMgr::GetInstance()->AddObj(pEffect, OBJ_EFFECT);

		switch(e_Arrow)
		{
		case DIR_RIGHT:
			switch(m_iMonType)
			{
			case MON1:
				m_pName = L"Left_Snowman";
				CSoundMgr::GetInstance()->MonsterSound(L"snowman.mp3");
				break;
			case MON2:
				m_pName = L"Left_Wolf";
				CSoundMgr::GetInstance()->MonsterSound(L"wolf.mp3");
				break;
			case MON3:
				m_pName = L"Left_Yeti";
				CSoundMgr::GetInstance()->MonsterSound(L"yeti.mp3");
				break;
			}
			m_fKnockBack = 3.f;
			break;
		case DIR_LEFT:
			switch(m_iMonType)
			{
			case MON1:
				m_pName = L"Right_Snowman";
				CSoundMgr::GetInstance()->MonsterSound(L"snowman.mp3");
				break;
			case MON2:
				m_pName = L"Right_Wolf";
				CSoundMgr::GetInstance()->MonsterSound(L"wolf.mp3");
				break;
			case MON3:
				m_pName = L"Right_Yeti";
				CSoundMgr::GetInstance()->MonsterSound(L"yeti.mp3");
				break;
			}
			m_fKnockBack = -3.f;
			break;
		}
		break;

	case Atk_RINGSHOOT:
		m_dwActiveTime = GetTickCount();
		m_iAction = 6;
		m_tMonster.iHp -= _iDmg;
		m_bIsKnockBack = true;

		pEffect = new CEffect(m_tInfo.fX, m_tInfo.fY, _iDmg, Atk_DMG, false);
		pEffect->Initialize();

		CObjMgr::GetInstance()->AddObj(pEffect, OBJ_EFFECT);

		switch(e_Arrow)
		{
		case DIR_RIGHT:
			switch(m_iMonType)
			{
			case MON1:
				m_pName = L"Left_Snowman";
				break;
			case MON2:
				m_pName = L"Left_Wolf";
				break;
			case MON3:
				m_pName = L"Left_Yeti";
				break;
			}
			m_fKnockBack = 1.f;
			break;
		case DIR_LEFT:
			switch(m_iMonType)
			{
			case MON1:
				m_pName = L"Right_Snowman";
				break;
			case MON2:
				m_pName = L"Right_Wolf";
				break;
			case MON3:
				m_pName = L"Right_Yeti";
				break;
			}
			m_fKnockBack = -1.f;
			break;
		}
		break;

	case Atk_DRIVER:

		m_dwActiveTime	=	GetTickCount();
		m_iAction = 6;
		m_tMonster.iHp	-=	_iDmg;
		m_bIsJump		=	true;
		m_fJumpAcc		=	-5.f;

		pEffect = new CEffect(m_tInfo.fX, m_tInfo.fY, _iDmg, Atk_DMG, false);
		pEffect->Initialize();

		CObjMgr::GetInstance()->AddObj(pEffect, OBJ_EFFECT);
		break;

	case Atk_HIGH:
		m_dwActiveTime	=	GetTickCount();
		m_iAction = 6;
		m_tMonster.iHp	-=	_iDmg;
		m_bIsJump		=	true;
		m_fJumpAcc		=	5.f;

		pEffect = new CEffect(m_tInfo.fX, m_tInfo.fY, _iDmg, Atk_DMG, false);
		pEffect->Initialize();

		CObjMgr::GetInstance()->AddObj(pEffect, OBJ_EFFECT);
		break;

	case Atk_ENREAL:
		m_dwActiveTime	=	GetTickCount();
		m_iAction = 6;
		m_tMonster.iHp	-=	_iDmg;
		m_bIsJump		=	true;
		m_fJumpAcc		=	4.f;

		pEffect = new CEffect(m_tInfo.fX, m_tInfo.fY, _iDmg, Atk_DMG, false);
		pEffect->Initialize();

		CObjMgr::GetInstance()->AddObj(pEffect, OBJ_EFFECT);
		break;


	}

	if(m_tMonster.iHp <= 0)
	{
		m_tInfo.fCX = 0;
		m_tInfo.fCY = 0;
		m_iAction = 7;
		m_dwActiveTime = GetTickCount();
	}


}
int CMonster::GetDmg()
{
	return m_tMonster.iAtk;
}
