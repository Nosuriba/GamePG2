#pragma once
#include <iostream>

// �s�[�X�̏��
enum class PIECE_ST
{
	B,		// ��
	W,		// ��
	NON,
	MAX
};

PIECE_ST begin(PIECE_ST);
PIECE_ST end(PIECE_ST);
int operator*(PIECE_ST state);
// enum�l�̉��Z
PIECE_ST operator++(PIECE_ST& state);
// enum�l�̌��Z
PIECE_ST operator--(PIECE_ST& state);