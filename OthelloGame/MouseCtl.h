#pragma once
#include <array>
#include "Vector2.h"

class PlayerType;

enum M_PUSH
{
	PUSH_NOW,
	PUSH_OLD,
	PUSH_MAX
};

// �v���C���[�̎��
enum class PL_TYPE
{
	MAN,
	CPU,
	MAX
};

// �}�E�X�̏����Œ蒷�z��Ŋi�[���邽�߂̌^ 
using mouse_int = std::array<int, PUSH_MAX>;

class MouseCtl
{
public:
	MouseCtl();
	MouseCtl(PL_TYPE type);
	~MouseCtl();
	Vector2 GetPoint(void) const;
	mouse_int GetButton(void) const;
	PL_TYPE GetPlType(void);
	void SetPlType(PL_TYPE type);
	void Update();
private:
	Vector2   pos;
	PL_TYPE	  type;
	std::unique_ptr<PlayerType> plType;
	mouse_int mButton;
};

