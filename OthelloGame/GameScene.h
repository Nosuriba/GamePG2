#pragma once
#include <mutex>
#include <memory>
#include <list>
#include <array>
#include "Vector2.h"
#include "GamePiece.h"
#include "PieceState.h"

class GameBoard;
class MouseCtl;
class Player;

#define LpGameScene (GameScene::GetInstance())

using player_ptr = std::shared_ptr<Player>;
using player_list = std::list<player_ptr>;

class GameScene
{
public:
	
	static GameScene & GetInstance()
	{
		/* �Q�[���V�[���N���X����x�����C���X�^���X����悤�ɂ��Ă��� */
		return *s_Instance;
	}
	void Run();
	Vector2 GetScreenSize(void);	// �Q�[����ʂ̃T�C�Y���擾���邽�߂̊֐�
	Vector2 GetActiveBoardSize(void);
private:

	/* GameScene�N���X��deleter��ݒ肵�Ă��� */
	struct GameSceneDeleter
	{
		void operator ()(GameScene* gameScene) const
		{
			delete gameScene;
		}
	};

	GameScene();
	~GameScene();

	int UpDate();

	/* �v���C���[�֌W�̏���*/
	void MakePlayer(void);
	void NextPlayer(void);
	bool AutoPassPlayer(void);

	/* �{�[�h�ɔz�u���ꂽ�s�[�X�̌����J�E���g���Ă��� */
	void PutPieceST(void);

	/* ���������v���C���[�𔻒肵�Ă��� */
	PIECE_ST WinJudge(int pCntB, int pCntW);
	void DrawWinner(PIECE_ST pState);

	int SysInit();
	int SysDestroy();

	/* �Q�[���V�[���֌W�̊֐� */
	int TitleInit();
	int TitleMain();
	int GameInit();
	int GameMain();
	int GameDestroy();
	int ResultInit();
	int ResultMain();

	int (GameScene::*gScenePtr)(void);

	int pieceW = 0;
	int pieceB = 0;

	static std::unique_ptr<GameScene, GameSceneDeleter>	s_Instance;
	std::unique_ptr<GameBoard> boardPtr;
	std::unique_ptr<MouseCtl>  mousePtr;
	std::unique_ptr<GamePiece> turnPLpiece;

	player_list playerList;
	player_list::iterator player;
};