#ifndef TETRIS
#define TETRIS
#include<Windows.h>
#include<time.h>
#define WIDTH 376
#define HEIGHT 639
#define LENGTH 30
#define ID_MYTIMER 400
ATOM InitApp(HINSTANCE); //WindowsClassEx�̏�����
BOOL InitInstance(HINSTANCE, int); //�E�B���h�E�̍쐬
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM); //�E�B���h�E�v���[�W���[
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
	int status; //0�F�w�i //�P�F�� //�Q�F�ړ����̃u���b�N //�R�F�ړ����̃u���b�N�̉�]���S //�S�F��~�����u���b�N
	POINT pt; //�u���b�N�̍���̍��W
}BLOCKINFO;

//�u���b�N�Ɖ摜�̑Ή��֌W
const POINT BmpColor[7] = {
	{0,0},//0�̓O���[
	{0,64},//1�͐�
	{0,128},//2�͐�
	{0,192},//3�͗�
	{0,256},//4�͎�
	{0,320},//5�̓I�����W
	{0,384},//6�͍�
};

const TCHAR szClassName[] = TEXT("Tetris"); //�N���X�l�[��

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