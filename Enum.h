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

	PLY_DRIVE,	//��ų �¼�
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
	TILE_NORMAL,	//�ƹ��͵� ���� �� Ÿ��
	TILE_DISABLE,	//����� �� ���� ���� Ÿ��
	TILE_LINE,		//���� Ÿ��
	TILE_TOPLINE,	//������ ���� ���κ� Ÿ��
	TILE_HILL,		//���������� ������ ��� Ÿ��
	TILE_PTR,		//���� ��Ʈ�� �� Ÿ��
	TILE_END
};

enum eAtkType	//��ų ����Ʈ
{
	Atk_DMG,
	Atk_SHOOT,		//�Ϲ� ����
	Atk_DRIVER,		//���� ����̹�
	Atk_HIGH,		//����ű ��������
	Atk_RING,		//�̽�Ÿ���� ��
	Atk_RINGSHOOT,	//���� ȭ��
	Atk_ENREAL,		//�������� ����
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