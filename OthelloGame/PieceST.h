#pragma once
#include <iostream>

// �s�[�X�̏��
enum class PIECE_ST
{
	PIECE_NON,
	PIECE_B,		// ��
	PIECE_W,		// ��
	PIECE_MAX
};


PIECE_ST begin(PIECE_ST);
PIECE_ST end(PIECE_ST);
PIECE_ST operator*(PIECE_ST state);
// enum�l�̉��Z
PIECE_ST operator++(PIECE_ST& state);
// enum�l�̌��Z
PIECE_ST operator--(PIECE_ST& state);