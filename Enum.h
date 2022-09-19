#ifndef Enum_
#define Enum_

enum eSceneType
{
	SCENE_START = 0,
	SCENE_STAGE1,
	SCENE_STAGE2,
	SCENE_STAGE3,
	SCENE_BOSS,
	SCENE_MAP,
	SCENE_END
};


enum eObjList
{
	OBJ_BG = 0,
	OBJ_MON,
	OBJ_PLY,
	OBJ_ATK,
	OBJ_MOUSE,
	OBJ_EFFECT,
	OBJ_END
};

enum eItemType
{
	ITEM_USE = 1,
	ITEM_WP,
	ITEM_AR,
	ITEM_HEAD,
	ITEM_GLOVES,
	ITEM_SHOES,
	ITEM_ETC,
	ITEM_END
};

enum ePlayerState
{
	PLY_STAND,
	PLY_RUN,
	PLY_JUMP,
	PLY_PRONE,
	PLY_ALERT,
	PLY_SHOOT,

	PLY_DRIVE,	//스킬 태세
	PLY_HIGH,
	PLY_ENREAL,

	PLY_CLIMB,
	PLY_DEAD,
	PLY_END
};

enum eMonsterState
{
	MON_STAND,
	MON_RUN,
	MON_JUMP,
	MON_HIT,
	MON_DEAD,
	MON_END
};

enum eTile
{
	TILE_NORMAL,	//아무것도 없는 빈 타일
	TILE_DISABLE,	//통과할 수 없는 지면 타일
	TILE_LINE,		//밧줄 타일
	TILE_TOPLINE,	//밧줄의 제일 윗부분 타일
	TILE_HILL,		//하향점프가 가능한 언덕 타일
	TILE_PTR,		//몬스터 패트롤 용 타일
	TILE_END
};

enum eAtkType	//스킬 리스트
{
	Atk_DMG,
	Atk_SHOOT,		//일반 공격
	Atk_DRIVER,		//차지 드라이버
	Atk_HIGH,		//하이킥 데몰리션
	Atk_RING,		//이슈타르의 링
	Atk_RINGSHOOT,	//링의 화살
	Atk_ENREAL,		//래쓰오브 엔릴
	Atk_SKILL,
	OBJ_PORTAL
};

enum eArrow
{
	DIR_LEFT,
	DIR_RIGHT
};

enum eMonList
{
	MON1 = 1,
	MON2,
	MON3
};
#endif