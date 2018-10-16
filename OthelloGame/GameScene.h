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
		/* ゲームシーンクラスを一度だけインスタンスするようにしている */
		return *s_Instance;
	}
	void Run();
	Vector2 GetScreenSize(void);	// ゲーム画面のサイズを取得するための関数
	Vector2 GetActiveBoardSize(void);
private:

	/* GameSceneクラスのdeleterを設定している */
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

	/* プレイヤー関係の処理 (ゲーム)*/
	void MakePlayer(void);
	void NextPlayer(void);
	bool AutoPassPlayer(void);

	/* ボードに配置されたピースの個数をカウントしている(ゲーム) */
	void PutPieceST(void);

	/* 勝利したプレイヤーを判定している(タイトル) */
	PIECE_ST WinJudge(int pCntB, int pCntW);
	void DrawWinner(PIECE_ST pState);

	int SysInit();
	int SysDestroy();

	/* ゲームシーン関係の関数 */
	int TitleInit();
	int TitleMain();
	int GameInit();
	int GameMain();
	int GameDestroy();
	int ResultInit();
	int ResultMain();

	int (GameScene::*gScenePtr)(void);

	/* ゲームとタイトル */
	int pieceW = 0;
	int pieceB = 0;

	static std::unique_ptr<GameScene, GameSceneDeleter>	s_Instance;
	std::unique_ptr<GameBoard> boardPtr;
	std::unique_ptr<MouseCtl>  mousePtr;
	std::unique_ptr<GamePiece> turnPLpiece;

	player_list playerList;
	player_list::iterator player;
};

/* ゲームシーンクラスに必要な関数や変数は残しておき、
	移動しても大丈夫なものはそれぞれのシーンの情報を渡すようにする*/