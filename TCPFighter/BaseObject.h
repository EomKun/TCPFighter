#ifndef __BASEOBJECT__H__
#define __BASEOBJECT__H__

class CBaseObject
{
public :
	/////////////////////////////////////////////////////////////////////////
	// 생성자, 파괴자
	/////////////////////////////////////////////////////////////////////////
	CBaseObject();
	~CBaseObject();

	void ActionInput();
	void NextFrame();
	BOOL isEndFrame();

	/////////////////////////////////////////////////////////////////////////
	// Getter
	/////////////////////////////////////////////////////////////////////////
	int GetCurX();
	int GetCurY();
	int GetObjectID();
	int GetObjectType();
	int GetOldX();
	int GetOldY();
	int GetSprite();

	/////////////////////////////////////////////////////////////////////////
	// Setter
	/////////////////////////////////////////////////////////////////////////
	void SetCurPosition(int curX, int curY);
	void SetObjectID(int objectID);
	void SetObjectType(e_OBJECT_TYPE ObjectType);
	void SetOldPosition(int oldX, int oldY);
	void SetPosition(int x, int y);
	void SetSprite(e_SPRITE sStart, e_SPRITE sEnd);

	/////////////////////////////////////////////////////////////////////////
	// Action, Draw 가상함수
	/////////////////////////////////////////////////////////////////////////
	virtual void Action() = 0;
	virtual void Draw() = 0;

private :
	BOOL m_bEndFrame;
	DWORD m_dwActionInput;
	int m_iCurX;
	int m_iCurY;
	int m_iDelayCount;
	int m_iFrameDelay;
	int m_iObjectID;
	int m_iObjectType;
	int m_iOldX;
	int m_iOldY;
	int m_iSpriteEnd;
	int m_iSpriteNow;
	int m_iSpriteStart;
};

#endif