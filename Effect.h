#pragma once
#include "obj.h"
#include "BitMgr.h"

class CEffect :	public CObj
{

private:
	int			iDmgNum;
	eAtkType	eType;	//스킬 타입
	bool		Player;	//이펙트 발현지가 플레이어인지 유무

	int			iWidth;		//리소스 가로 간격차
	int			iHeight;	//리소스 세로 간격차

	int			iFrameCount;

	DWORD		m_dwTime;

	//데미지 이펙트 변수
	bool		b100000;
	bool		b10000;
	bool		b1000;
	bool		b100;
	bool		b10;
	bool		b1;

public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CEffect(void);
	CEffect(float, float, int, eAtkType, bool);
	virtual ~CEffect(void);
};
