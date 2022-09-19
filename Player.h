#pragma once
#include "obj.h"
#include "Item.h"
#include "KeyMgr_60.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "Mouse.h"
#include "Atk.h"
//#include "MainUI.h"

class CItem;
//typedef struct tEquipInfo
//{
//	CItem*	tHead;
//	CItem*	tWeapon;
//	CItem*	tArmor;
//	CItem*	tGloves;
//	CItem*	tBoots;
//
//	tEquipInfo(int, int, int, int, int)
//		:tHead(NULL), tWeapon(NULL), tArmor(NULL), tGloves(NULL), tBoots(NULL) {}
//}EINFO;

class CPlayer : public CObj
{
private:
	PINFO			m_tPlayer;
	EINFO			m_tEquip;
	
	float			m_fSpeed;
	int				iItemNum;			//�κ� ���� ������ ������ üũ
	POINT			pt;
	POINT			m_ptOffset;

private:	//�ൿ ����
	eArrow			m_eArrow;
	bool			m_bIsAtk;			//���� ��
	bool			m_bIsJump;			//���� ��
	bool			m_bIsFall;			//�߶� ��
	bool			m_bIsHit;			//�´� ��
	
	//��ų ����
	bool			m_bIsSkilling;		//��ų ���� ��
	bool			m_bIsDrive;			//���� ����̺� ���� ��
	bool			m_bIsHigh;			//����ű �������� ���� ��
	bool			m_bIsRing;			//�̽�Ÿ�� �� ���� ��


	bool			m_bIsClimb;			//��� ����
	bool			m_bIsGhost;			//Ÿ�� ��� ����
	bool			m_bIsHill;			//���� ���� ����
	bool			m_bIsKnockBack;		//�˹� ����


	float			m_fJumpAcc;			//���� ���ӵ�
	float			m_fKnockBack;		//�˹� ��ġ

	float			m_fTime;

	bool			m_Drag;
	DWORD			m_dwActiveTime;		//�ǰ� Ȱ��ȭ �ð�
	DWORD			m_dwItemTime;		//������ ������ ���� �ð����� ����ǰ� �ϱ�

	DWORD			m_dwState;			//�÷��̾��� �������
	DWORD			m_dwPrevState;		//�÷��̾��� ��������
	
	FRAME			m_tFrame;			//ĳ���� ������ ��ǥ ����

	DWORD			m_dwFrameTime;		

private:
	void			ItemSwap(void);
	void			ItemCrush(void);
	void			FrameMove(void);
	void			KeyCheck(void);
	void			Scroll(void);
	void			UseItem(CItem &pItem);
	
	vector<CItem*>	m_vecInven;
	vector<TILE*>*	m_pvecTile;
	list<CObj*>*	m_plistAtk;

public:
	void			TileCrush(TILE*	_Tile);

public:	//������
	QSLOT	m_Quick;

	int				m_iPrevMap;
	bool			m_bIsSuper;			//�浹����
	
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);

	void	HpMgr(int _iDmg, int iAtkType, eArrow e_Arrow);

	void	SetTile(vector<TILE*>* pTileVector)
	{
		m_pvecTile = pTileVector;
	}

	void	SetAtk(list<CObj*>* pAtkList)
	{
		m_plistAtk = pAtkList;
	}

	const	PINFO*	GetPInfo(void)
	{
		return &m_tPlayer;
	}

	vector<CItem*>* GetVector(void)
	{
		return &m_vecInven;
	}

	QSLOT*	GetQuick(void)
	{
		return &m_Quick;
	}

	EINFO*	GetEquip(void)
	{
		return &m_tEquip;
	}

public:
	CPlayer(void);
	virtual ~CPlayer(void);
};
