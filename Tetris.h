#ifndef TETRIS
#define TETRIS
#include<Windows.h>
#include<time.h>
#define WIDTH 376
#define HEIGHT 639
#define LENGTH 30
#define ID_MYTIMER 400
ATOM InitApp(HINSTANCE); //WindowsClassExの初期化
BOOL InitInstance(HINSTANCE, int); //ウィンドウの作成
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM); //ウィンドウプロージャー
void InitBlock();
void PaintBlock(HDC, HDC);
void DeleteBlock();
void NewBlock();
void DropBlock();
void LeftBlock();
void RightBlock();
void LeftRotateBlock();
void RightRotateBlock();
void FinishTetris();

typedef struct BlockInfo {
	int color;
	int status; //0：背景 //１：壁 //２：移動中のブロック //３：移動中のブロックの回転中心 //４：停止したブロック
	POINT pt; //ブロックの左上の座標
}BLOCKINFO;

//ブロックと画像の対応関係
const POINT BmpColor[7] = {
	{0,0},//0はグレー
	{0,64},//1は赤
	{0,128},//2は青
	{0,192},//3は緑
	{0,256},//4は紫
	{0,320},//5はオレンジ
	{0,384},//6は黒
};

const TCHAR szClassName[] = TEXT("Tetris"); //クラスネーム

const int tetromino[7][4][2] = {
	{ { 1, 0 }, { 1, 0 }, { 2, 0 }, { 1, 0 } }, //I
	{ { 0, 0 }, { 1, 1 }, { 1, 1 }, { 0, 0 } }, //O
	{ { 0, 0 }, { 2, 1 }, { 1, 0 }, { 1, 0 } }, //L
	{ { 0, 0 }, { 0, 1 }, { 2, 1 }, { 1, 0 } }, //S
	{ { 0, 0 }, { 1, 0 }, { 2, 1 }, { 1, 0 } }, //T
	{ { 0, 0 }, { 1, 0 }, { 1, 0 }, { 2, 1 } }, //J
	{ { 0, 0 }, { 1, 0 }, { 2, 1 }, { 0, 1 } } //Z
};
#endif