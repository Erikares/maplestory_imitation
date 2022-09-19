#include "StdAfx.h"
#include "BitMgr.h"

IMPLEMENT_SINGLETONE(CBitMgr)

CBitMgr::CBitMgr(void)
{
}

CBitMgr::~CBitMgr(void)
{
	Release();
}
void CBitMgr::Initialize(void)
{
	//캐릭터 이미지
	m_MapBit.insert(make_pair(L"Right_Player", (new CBitMap)->LoadBmp(L"../Resource/Player/Right_Player.bmp")));
	m_MapBit.insert(make_pair(L"Left_Player", (new CBitMap)->LoadBmp(L"../Resource/Player/Left_Player.bmp")));
	m_MapBit.insert(make_pair(L"Climb_Player", (new CBitMap)->LoadBmp(L"../Resource/Player/Climb_Player.bmp")));
	m_MapBit.insert(make_pair(L"Right_Battle", (new CBitMap)->LoadBmp(L"../Resource/Player/Right_Battle.bmp")));

	m_MapBit.insert(make_pair(L"Right_Skill_Player", (new CBitMap)->LoadBmp(L"../Resource/Player/Right_Skill_Player.bmp")));
	m_MapBit.insert(make_pair(L"Left_Skill_Player", (new CBitMap)->LoadBmp(L"../Resource/Player/Left_Skill_Player.bmp")));


	//스킬 이펙트
	m_MapBit.insert(make_pair(L"Charge_Drive", (new CBitMap)->LoadBmp(L"../Resource/Skill/charge_drive.bmp")));
	m_MapBit.insert(make_pair(L"High_Kick", (new CBitMap)->LoadBmp(L"../Resource/Skill/high_kick.bmp")));
	
	m_MapBit.insert(make_pair(L"Right_Enreal", (new CBitMap)->LoadBmp(L"../Resource/Skill/Right_Enreal.bmp")));
	m_MapBit.insert(make_pair(L"Left_Enreal", (new CBitMap)->LoadBmp(L"../Resource/Skill/Left_Enreal.bmp")));

	m_MapBit.insert(make_pair(L"Right_Ring", (new CBitMap)->LoadBmp(L"../Resource/Skill/Right_Ring.bmp")));
	m_MapBit.insert(make_pair(L"Left_Ring", (new CBitMap)->LoadBmp(L"../Resource/Skill/Left_Ring.bmp")));
	m_MapBit.insert(make_pair(L"Left_Ring_Arrow", (new CBitMap)->LoadBmp(L"../Resource/Skill/Left_Ring_Arrow.bmp")));


	//이펙트
	m_MapBit.insert(make_pair(L"Arrow_Right", (new CBitMap)->LoadBmp(L"../Resource/Effect/Arrow_Right.bmp")));
	m_MapBit.insert(make_pair(L"Arrow_Left", (new CBitMap)->LoadBmp(L"../Resource/Effect/Arrow_Left.bmp")));
	m_MapBit.insert(make_pair(L"DamageEffect", (new CBitMap)->LoadBmp(L"../Resource/Effect/DamageEffect.bmp")));
	m_MapBit.insert(make_pair(L"HitEffect", (new CBitMap)->LoadBmp(L"../Resource/Effect/HitEffect.bmp")));
	m_MapBit.insert(make_pair(L"Portal", (new CBitMap)->LoadBmp(L"../Resource/Effect/portal.bmp")));




	//배경 이미지
	m_MapBit.insert(make_pair(L"Black", (new CBitMap)->LoadBmp(L"../Resource/Bg/Black.bmp")));


	//UI 이미지
	m_MapBit.insert(make_pair(L"MainUI", (new CBitMap)->LoadBmp(L"../Resource/UI/MainUI.bmp")));
	m_MapBit.insert(make_pair(L"InvenUI", (new CBitMap)->LoadBmp(L"../Resource/UI/Inven.bmp")));
	m_MapBit.insert(make_pair(L"EquipUI", (new CBitMap)->LoadBmp(L"../Resource/UI/Equip.bmp")));
	m_MapBit.insert(make_pair(L"SkillUI", (new CBitMap)->LoadBmp(L"../Resource/UI/Skill.bmp")));
	m_MapBit.insert(make_pair(L"StateUI", (new CBitMap)->LoadBmp(L"../Resource/UI/State.bmp")));
	m_MapBit.insert(make_pair(L"HpBar", (new CBitMap)->LoadBmp(L"../Resource/UI/HpBar.bmp")));
	m_MapBit.insert(make_pair(L"MpBar", (new CBitMap)->LoadBmp(L"../Resource/UI/MpBar.bmp")));

	//아이템 이미지
	m_MapBit.insert(make_pair(L"None", (new CBitMap)->LoadBmp(L"../Resource/Item/None.bmp")));
	m_MapBit.insert(make_pair(L"Red_Potion", (new CBitMap)->LoadBmp(L"../Resource/Item/Red_potion.bmp")));
	m_MapBit.insert(make_pair(L"Gunbow01", (new CBitMap)->LoadBmp(L"../Resource/Item/Bowgun01.bmp")));
	m_MapBit.insert(make_pair(L"Armor01", (new CBitMap)->LoadBmp(L"../Resource/Item/Armor01.bmp")));
	m_MapBit.insert(make_pair(L"Hat01", (new CBitMap)->LoadBmp(L"../Resource/Item/Hat01.bmp")));
	m_MapBit.insert(make_pair(L"Gloves01", (new CBitMap)->LoadBmp(L"../Resource/Item/Gloves01.bmp")));
	m_MapBit.insert(make_pair(L"Shoes01", (new CBitMap)->LoadBmp(L"../Resource/Item/Shoes01.bmp")));


}
void CBitMgr::Release(void)
{
	map<const TCHAR*, CBitMap*>::iterator iter = m_MapBit.begin();
	map<const TCHAR*, CBitMap*>::iterator iter_end = m_MapBit.end();

	for(iter; iter != iter_end; ++iter)
	{
		delete iter->second;
	}

	m_MapBit.clear();
}

HDC	CBitMgr::GetImage(const TCHAR* pKey)
{
	map<const TCHAR*, CBitMap*>::iterator iter = m_MapBit.find(pKey);

	if(iter == m_MapBit.end())
	{
		MessageBox(g_hWnd, pKey, L"Image Find Failed", MB_OK);
		return 0;
	}

	return iter->second->GetMemDC();
}

void	CBitMgr::LoadImageByScene(eSceneType eType)
{
	switch(eType)
	{
	case SCENE_START:
		m_MapBit.insert(make_pair(L"BackBuffer", (new CBitMap)->LoadBmp(L"../Resource/BackBuffer.bmp")));
		m_MapBit.insert(make_pair(L"BackGround", (new CBitMap)->LoadBmp(L"../Resource/Bg/Title.bmp")));
		m_MapBit.insert(make_pair(L"Start", (new CBitMap)->LoadBmp(L"../Resource/Button/Start.bmp")));
		break;
	case SCENE_STAGE1:
		m_MapBit.erase(L"BackGround");
		m_MapBit.insert(make_pair(L"BackBuffer", (new CBitMap)->LoadBmp(L"../Resource/BackBuffer.bmp")));
		m_MapBit.insert(make_pair(L"BackGround", (new CBitMap)->LoadBmp(L"../Resource/Bg/back001.bmp")));
		m_MapBit.insert(make_pair(L"Stage01", (new CBitMap)->LoadBmp(L"../Resource/Bg/stage01.bmp")));
		m_MapBit.insert(make_pair(L"Tile", (new CBitMap)->LoadBmp(L"../Resource/Tile.bmp")));

		m_MapBit.insert(make_pair(L"Right_Snowman", (new CBitMap)->LoadBmp(L"../Resource/Monster/Right_Snowman.bmp")));
		m_MapBit.insert(make_pair(L"Left_Snowman", (new CBitMap)->LoadBmp(L"../Resource/Monster/Left_Snowman.bmp")));

		m_MapBit.insert(make_pair(L"Left_Wolf", (new CBitMap)->LoadBmp(L"../Resource/Monster/Left_Wolf.bmp")));
		m_MapBit.insert(make_pair(L"Right_Wolf", (new CBitMap)->LoadBmp(L"../Resource/Monster/Right_Wolf.bmp")));

		m_MapBit.insert(make_pair(L"Left_Yeti", (new CBitMap)->LoadBmp(L"../Resource/Monster/Left_Yeti.bmp")));
		m_MapBit.insert(make_pair(L"Right_Yeti", (new CBitMap)->LoadBmp(L"../Resource/Monster/Right_Yeti.bmp")));

		break;

	case SCENE_STAGE2:
		m_MapBit.erase(L"BackGround");
		m_MapBit.insert(make_pair(L"BackBuffer", (new CBitMap)->LoadBmp(L"../Resource/BackBuffer.bmp")));
		m_MapBit.insert(make_pair(L"BackGround", (new CBitMap)->LoadBmp(L"../Resource/Bg/back001.bmp")));
		m_MapBit.insert(make_pair(L"Stage02", (new CBitMap)->LoadBmp(L"../Resource/Bg/stage02.bmp")));
		m_MapBit.insert(make_pair(L"Tile", (new CBitMap)->LoadBmp(L"../Resource/Tile.bmp")));

		m_MapBit.insert(make_pair(L"Left_Wolf", (new CBitMap)->LoadBmp(L"../Resource/Monster/Left_Wolf.bmp")));
		m_MapBit.insert(make_pair(L"Right_Wolf", (new CBitMap)->LoadBmp(L"../Resource/Monster/Right_Wolf.bmp")));

		break;
	
	case SCENE_STAGE3:
		m_MapBit.erase(L"BackGround");
		m_MapBit.insert(make_pair(L"BackBuffer", (new CBitMap)->LoadBmp(L"../Resource/BackBuffer.bmp")));
		m_MapBit.insert(make_pair(L"BackGround", (new CBitMap)->LoadBmp(L"../Resource/Bg/back002.bmp")));
		m_MapBit.insert(make_pair(L"Stage03", (new CBitMap)->LoadBmp(L"../Resource/Bg/stage03.bmp")));
		m_MapBit.insert(make_pair(L"Tile", (new CBitMap)->LoadBmp(L"../Resource/Tile.bmp")));
		break;

	case SCENE_MAP:
		m_MapBit.erase(L"BackGround");
		m_MapBit.insert(make_pair(L"BackBuffer", (new CBitMap)->LoadBmp(L"../Resource/BackBuffer.bmp")));
		m_MapBit.insert(make_pair(L"BackGround", (new CBitMap)->LoadBmp(L"../Resource/Bg/back002.bmp")));
		m_MapBit.insert(make_pair(L"Stage", (new CBitMap)->LoadBmp(L"../Resource/Bg/stage03.bmp")));
		m_MapBit.insert(make_pair(L"Tile", (new CBitMap)->LoadBmp(L"../Resource/Tile.bmp")));
		break;
	}
}