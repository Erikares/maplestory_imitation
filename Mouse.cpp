#include "StdAfx.h"
#include "Mouse.h"

CMouse::CMouse(void)
{
}

CMouse::~CMouse(void)
{
	Release();
}

void CMouse::Initialize(void)
{
	
}

int CMouse::Update(void)
{
	return 0;
}

void CMouse::Render(void)
{
	
}

void CMouse::Release(void)
{
	
}

POINT CMouse::GetPos(void)
{
	POINT	ptMouse;
	GetCursorPos(&ptMouse);

	ScreenToClient(g_hWnd, &ptMouse);

	return ptMouse;
}
