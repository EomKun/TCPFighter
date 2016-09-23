#include "stdafx.h"
#include "BaseObject.h"
#include "PlayerObject.h"

CPlayerObject::CPlayerObject(BOOL PlayerCharacter, int iObjectID, int iObjectType, char chHP, int iDirection)
	: CBaseObject(iObjectID, iObjectType), m_bPlayerCharacter(PlayerCharacter), m_chHP(chHP), m_dwActionCur(dfACTION_STAND),
	m_dwActionOld(dfACTION_STAND), m_iDirCur(iDirection), m_iDirOld(iDirection)
{
	SetSprite(ePLAYER_STAND_R01, ePLAYER_STAND_R_MAX, 5);
}

CPlayerObject::~CPlayerObject()
{

}

/*---------------------------------------------------------------------------------------------------------*/
// Action
// 메인 액션
/*---------------------------------------------------------------------------------------------------------*/
DWORD CPlayerObject::Action(DWORD dwParam)
{
	NextFrame();
	ActionProc();
	return FALSE;
}

/*---------------------------------------------------------------------------------------------------------*/
// 액션 처리부
// 입력된 액션을 처리한다
/*---------------------------------------------------------------------------------------------------------*/
void CPlayerObject::ActionProc()
{
	// 공격이 안끝났을 때
	if ((m_dwActionCur == dfACTION_ATTACK1 || m_dwActionCur == dfACTION_ATTACK2 || m_dwActionCur == dfACTION_ATTACK3)
		&& (!isEndFrame()))
	{
		m_dwActionInput = m_dwActionCur;
		return;
	}

	// 공격이 끝났을 때
	else if ((m_dwActionCur == dfACTION_ATTACK1 || m_dwActionCur == dfACTION_ATTACK2 || m_dwActionCur == dfACTION_ATTACK3)
		&& isEndFrame())
	{
		SetActionStand();
		m_dwActionInput = dfACTION_STAND;
	}

	switch (m_dwActionInput)
	{
	case dfACTION_ATTACK1 :
		SetActionAttack1();
		break;

	case dfACTION_ATTACK2 :
		SetActionAttack2();
		break;

	case dfACTION_ATTACK3 :
		SetActionAttack3();
		break;

	default :
		InputActionProc();
		break;
	}
}

/*---------------------------------------------------------------------------------------------------------*/
// Draw
// 해당 객체를 Screen에 그린다
/*---------------------------------------------------------------------------------------------------------*/
void CPlayerObject::Draw(CSpriteDib *pSprite, BYTE* bypDest, int iDestWidth, int iDestHeight, int iDestPitch)
{
	int iDrawX = GetCurX() - g_cTileMap.GetDrawPosX();
	int	iDrawY = GetCurY() - g_cTileMap.GetDrawPosY();
	
	if (GetCurX() < dfSCREEN_WIDTH / 2)					iDrawX = GetCurX();
	if (GetCurY() < dfSCREEN_HEIGHT / 2 + 20)			iDrawY = GetCurY();
	if (GetCurX() + dfSCREEN_WIDTH / 2 > dfMAP_WIDTH)	
		iDrawX = dfSCREEN_WIDTH - (dfMAP_WIDTH - GetCurX());
	if (GetCurY() + dfSCREEN_HEIGHT / 2 - 20 > dfMAP_HEIGHT)
		iDrawY = dfSCREEN_HEIGHT - (dfMAP_HEIGHT - GetCurY());

	pSprite->DrawSprite50(eSHADOW, iDrawX, iDrawY, bypDest, iDestWidth, iDestHeight, iDestPitch);
	
	if (m_bPlayerCharacter)
		pSprite->DrawSpriteRed(GetSprite(), iDrawX, iDrawY, bypDest, iDestWidth, iDestHeight, iDestPitch);

	else
		pSprite->DrawSprite(GetSprite(), iDrawX, iDrawY, bypDest, iDestWidth, iDestHeight, iDestPitch);

	pSprite->DrawSprite(eGUAGE_HP, iDrawX - 35, iDrawY + 9, bypDest, iDestWidth, iDestHeight, iDestPitch, m_chHP);
}

/*---------------------------------------------------------------------------------------------------------*/
// 입력 액션 처리
// 액션 셋팅과 방향, 스프라이트를 설정한다.
/*---------------------------------------------------------------------------------------------------------*/
void CPlayerObject::InputActionProc()
{
	switch (m_dwActionInput)
	{
	case dfACTION_STAND:														//서있을 때
		SetActionStand();
		break;

	case dfACTION_MOVE_LL :														//왼쪽
		SetActionMove(dfACTION_MOVE_LL);

		if (isPlayer() && GetCurX() - dfSPEED_PLAYER_X <= dfRANGE_MOVE_LEFT)
			SetPosition(GetCurX(), GetCurY());
		else
			SetPosition(GetCurX() - dfSPEED_PLAYER_X, GetCurY());
		
		break;

	case dfACTION_MOVE_RR :														//오른쪽
		SetActionMove(dfACTION_MOVE_RR);

		if (isPlayer() && GetCurX() + dfSPEED_PLAYER_X >= dfRANGE_MOVE_RIGHT)
			SetPosition(GetCurX(), GetCurY());
		else
			SetPosition(GetCurX() + dfSPEED_PLAYER_X, GetCurY());
		
		break;

	case dfACTION_MOVE_DD:														//아래
		SetActionMove(dfACTION_MOVE_DD);

		if (isPlayer() && GetCurY() + dfSPEED_PLAYER_Y >= dfRANGE_MOVE_BOTTOM)
			SetPosition(GetCurX(), GetCurY());
		else
			SetPosition(GetCurX(), GetCurY() + dfSPEED_PLAYER_Y);
		
		break;

	case dfACTION_MOVE_UU :														//위
		SetActionMove(dfACTION_MOVE_UU);

		if (isPlayer() && GetCurY() - dfSPEED_PLAYER_Y <= dfRANGE_MOVE_TOP)
			SetPosition(GetCurX(), GetCurY());
		else
			SetPosition(GetCurX(), GetCurY() - dfSPEED_PLAYER_Y);
		
		break;

	case dfACTION_MOVE_LD :														//왼쪽아래
		SetActionMove(dfACTION_MOVE_LD);

		if (isPlayer() && (GetCurX() - dfSPEED_PLAYER_X <= dfRANGE_MOVE_LEFT) ||
			(GetCurY() + dfSPEED_PLAYER_Y >= dfRANGE_MOVE_BOTTOM))
			SetPosition(GetCurX(), GetCurY());
		else
			SetPosition(GetCurX() - dfSPEED_PLAYER_X, GetCurY() + dfSPEED_PLAYER_Y);
		
		break;

	case dfACTION_MOVE_LU :														//왼쪽위
		SetActionMove(dfACTION_MOVE_LU);

		if (isPlayer() && (GetCurX() - dfSPEED_PLAYER_X <= dfRANGE_MOVE_LEFT) ||
			(GetCurY() - dfSPEED_PLAYER_Y <= dfRANGE_MOVE_TOP)) 
			SetPosition(GetCurX(), GetCurY());
		else
			SetPosition(GetCurX() - dfSPEED_PLAYER_X, GetCurY() - dfSPEED_PLAYER_Y);
		
		break;

	case dfACTION_MOVE_RD :														//오른쪽아래
		SetActionMove(dfACTION_MOVE_RD);

		if (isPlayer() && (GetCurX() + dfSPEED_PLAYER_X >= dfRANGE_MOVE_RIGHT) ||
			(GetCurY() + dfSPEED_PLAYER_Y >= dfRANGE_MOVE_BOTTOM))
			SetPosition(GetCurX(), GetCurY());
		else
			SetPosition(GetCurX() + dfSPEED_PLAYER_X, GetCurY() + dfSPEED_PLAYER_Y);
		
		break;

	case dfACTION_MOVE_RU :														//오른쪽 위
		SetActionMove(dfACTION_MOVE_RU);

		if (isPlayer() && (GetCurX() + dfSPEED_PLAYER_X >= dfRANGE_MOVE_RIGHT) ||
			(GetCurY() - dfSPEED_PLAYER_Y <= dfRANGE_MOVE_TOP))
			SetPosition(GetCurX(), GetCurY());
		else
			SetPosition(GetCurX() + dfSPEED_PLAYER_X, GetCurY() - dfSPEED_PLAYER_Y);
		
		break;
	}
}

/*---------------------------------------------------------------------------------------------------------*/
// 플레이어 확인
// 해당 플레이어인지 확인한다
/*---------------------------------------------------------------------------------------------------------*/
BOOL CPlayerObject::isPlayer()
{
	if (m_bPlayerCharacter == TRUE)	return true;
	else							return false;
}

/*---------------------------------------------------------------------------------------------------------*/
// 방향 확인
// 플레이어 방향 확인
/*---------------------------------------------------------------------------------------------------------*/
int CPlayerObject::GetDirection()
{
	return m_iDirCur;
}

/*---------------------------------------------------------------------------------------------------------*/
// 공격 액션 설정
// 해당 공격 액션을 설정한다
/*---------------------------------------------------------------------------------------------------------*/
void CPlayerObject::SetActionAttack1()	
{ 
	m_dwActionOld = m_dwActionCur;
	m_dwActionCur = dfACTION_ATTACK1;

	if (m_dwActionOld != m_dwActionCur){
		if (GetDirection() == LEFT)
			SetSprite(ePLAYER_ATTACK1_L01, ePLAYER_ATTACK1_L_MAX, 3);
		else if (GetDirection() == RIGHT)
			SetSprite(ePLAYER_ATTACK1_R01, ePLAYER_ATTACK1_R_MAX, 3);
	}

	if (isPlayer() && m_dwActionCur != m_dwActionOld && m_dwActionCur != dfACTION_STAND)
		sendProc_Attack1(GetDirection(), GetCurX(), GetCurY());
}

void CPlayerObject::SetActionAttack2()	
{
	m_dwActionOld = m_dwActionCur;
	m_dwActionCur = dfACTION_ATTACK2;

	if (m_dwActionOld != m_dwActionCur){
		if (GetDirection() == LEFT)
			SetSprite(ePLAYER_ATTACK2_L01, ePLAYER_ATTACK2_L_MAX, 4);
		else if (GetDirection() == RIGHT)
			SetSprite(ePLAYER_ATTACK2_R01, ePLAYER_ATTACK2_R_MAX, 4);
	}

	if (isPlayer() && m_dwActionCur != m_dwActionOld && m_dwActionCur != dfACTION_STAND)
		sendProc_Attack2(GetDirection(), GetCurX(), GetCurY());
}

void CPlayerObject::SetActionAttack3()	
{
	m_dwActionOld = m_dwActionCur;
	m_dwActionCur = dfACTION_ATTACK3;
	if (m_dwActionOld != m_dwActionCur){
		if (GetDirection() == LEFT)
			SetSprite(ePLAYER_ATTACK3_L01, ePLAYER_ATTACK3_L_MAX, 4);
		else if (GetDirection() == RIGHT)
			SetSprite(ePLAYER_ATTACK3_R01, ePLAYER_ATTACK3_R_MAX, 4);
	}

	if (isPlayer() && m_dwActionCur != m_dwActionOld && m_dwActionCur != dfACTION_STAND)
		sendProc_Attack3(GetDirection(), GetCurX(), GetCurY());
}

/*---------------------------------------------------------------------------------------------*/
// Player Move Setting
/*---------------------------------------------------------------------------------------------*/
void CPlayerObject::SetActionMove(DWORD actionMove)		
{
	m_dwActionOld = m_dwActionCur;
	m_dwActionCur = actionMove;

	if (GetCurX() > GetOldX())			SetDirection(RIGHT);
	else if (GetCurX() < GetOldX())		SetDirection(LEFT);

	if (m_dwActionOld == dfACTION_STAND || GetDirection() != m_iDirOld)
	{
		if (m_iDirCur == RIGHT)			SetSprite(ePLAYER_MOVE_R01, ePLAYER_MOVE_R_MAX, 4);
		else if (m_iDirCur == LEFT) 	SetSprite(ePLAYER_MOVE_L01, ePLAYER_MOVE_L_MAX, 4);
	}

	if (isPlayer() && m_dwActionCur != m_dwActionOld && m_dwActionCur != dfACTION_STAND)
		sendProc_MoveStart(m_dwActionCur, GetCurX(), GetCurY());
}

/*---------------------------------------------------------------------------------------------*/
// Player Stand Setting
/*---------------------------------------------------------------------------------------------*/
void CPlayerObject::SetActionStand()	
{
	m_dwActionOld = m_dwActionCur;
	m_dwActionCur = dfACTION_STAND;

	if (m_dwActionOld != dfACTION_STAND){
		if (m_iDirCur == LEFT)			SetSprite(ePLAYER_STAND_L01, ePLAYER_STAND_L_MAX, 5);
		else if (m_iDirCur == RIGHT)	SetSprite(ePLAYER_STAND_R01, ePLAYER_STAND_R_MAX, 5);
	}

	if (isPlayer() && m_dwActionCur != m_dwActionOld && m_dwActionCur == dfACTION_STAND &&
		m_dwActionOld != dfACTION_ATTACK1 && m_dwActionOld != dfACTION_ATTACK2 && m_dwActionOld != dfACTION_ATTACK3)
		sendProc_MoveStop(GetDirection(), GetCurX(), GetCurY());
}

/*---------------------------------------------------------------------------------------------*/
// Player Direction Setting
/*---------------------------------------------------------------------------------------------*/
void CPlayerObject::SetDirection(int dir)		
{
	m_iDirOld = m_iDirCur;
	m_iDirCur = dir;
}

/*---------------------------------------------------------------------------------------------*/
// Player HP Setting
/*---------------------------------------------------------------------------------------------*/
void CPlayerObject::SetHP(char hp)				
{
	m_chHP = hp;
}