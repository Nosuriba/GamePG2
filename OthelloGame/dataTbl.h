#define  DB_CHAR_MAX   (4)
#define  DB_STATE_MAX  (3)

enum DB_CHAR
{
	JAKE,		// ジェイク
	MIQUET,		// ミケ
	NANAMI,		// ナナミ
	RIDER,		// ライダー
	CHAR_MAX	// キャラの最大数
};

extern int dataTbl[DB_CHAR_MAX][DB_STATE_MAX];
