#pragma once
#include <iostream>

// ピースの状態
enum class PIECE_ST
{
	PIECE_NON,
	PIECE_B,		// 黒
	PIECE_W,		// 白
	PIECE_MAX
};


PIECE_ST begin(PIECE_ST);
PIECE_ST end(PIECE_ST);
PIECE_ST operator*(PIECE_ST state);
// enum値の加算
PIECE_ST operator++(PIECE_ST& state);
// enum値の減算
PIECE_ST operator--(PIECE_ST& state);