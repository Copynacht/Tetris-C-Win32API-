#include"Tetris.h"

BLOCKINFO blocks[12][20] = { 0 };
int tList[7] = { 0, 1, 2, 3, 4, 5, 6 };
bool arrived = false;
bool finishFlag = false;

//偉い人が作ったシャッフル関数
void shuffle(int array[], int size) {
	for (int i = 0; i < size; i++) {
		int j = rand() % size;
		int t = array[i];
		array[i] = array[j];
		array[j] = t;
	}
}

void InitBlock() {
	for (int x = 0; x < 12; x++) {
		for (int y = 0; y < 20; y++) {
			blocks[x][y].pt.x = x * LENGTH;
			blocks[x][y].pt.y = y * LENGTH;
			if (x == 0 || x == 11 || y == 19) {
				blocks[x][y].status = 1;
				blocks[x][y].color = 6;
			}
			else {
				blocks[x][y].status = 0;
				blocks[x][y].color = 0;
			}
		}
	}
}

void PaintBlock(HDC hdc, HDC hdc_mem) {
	for (int x = 0; x < 12; x++) {
		for (int y = 0; y < 20; y++) {
			StretchBlt(hdc, blocks[x][y].pt.x, blocks[x][y].pt.y, LENGTH, LENGTH, hdc_mem, BmpColor[blocks[x][y].color].x, BmpColor[blocks[x][y].color].y, 64, 64, SRCCOPY);
		}
	}
}

void NewBlock() {
	static int numbering = 0;
	if (finishFlag != true) {
		if (numbering == 0) {
			shuffle(tList, 7);
		}
		int whichBlock = tList[numbering];
		int whichColor = rand() % 5 + 1;
		for (int x = 0; x < 4; x++) {
			for (int y = 0; y < 2; y++) {
				if (tetromino[whichBlock][x][y] == 1) {
					if (blocks[x + 4][y].status != 0)finishFlag = true;
					blocks[x + 4][y].color = whichColor;
					blocks[x + 4][y].status = 2;
				}
				if (tetromino[whichBlock][x][y] == 2) {
					if (blocks[x + 4][y].status != 0)finishFlag = true;
					blocks[x + 4][y].color = whichColor;
					blocks[x + 4][y].status = 3;
				}
			}
		}
	}
	if (finishFlag == true)FinishTetris();
	numbering++;
	if (numbering == 7)numbering = 0;
}

void DropBlock() {
	//flagはブロックが移動していいかどうかを判定する
	bool flag = false;
	//ブロックが移動できるか判定
	for (int x = 1; x < 11; x++) {
		for (int y = 1; y < 20; y++) {
			if ((blocks[x][y].status == 1 || blocks[x][y].status == 4) && (blocks[x][y - 1].status == 2 || blocks[x][y - 1].status == 3)) {
				flag = true;
			}
		}
	}
	if (flag == true) {
		//移動したらダメな場合はブロックを固定して新しいブロックを生成
		for (int x = 1; x < 11; x++) {
			for (int y = 0; y < 20; y++) {
				if (blocks[x][y - 1].status == 2 || blocks[x][y - 1].status == 3) {
					blocks[x][y - 1].status = 4;
				}
			}
		}
		//ここにブロックが一列揃っていたら消す処理を挟む
		DeleteBlock();
		NewBlock();
	}
	else {
		//移動してよいので移動
		for (int x = 1; x < 11; x++) {
			for (int y = 18; y >= 0; y--) {
				if (blocks[x][y].status == 2 || blocks[x][y].status == 3) {
					blocks[x][y + 1].status = blocks[x][y].status;
					blocks[x][y + 1].color = blocks[x][y].color;
					blocks[x][y].status = 0;
					blocks[x][y].color = 0;
				}
			}
		}
	}
	flag = false;
}

void LeftBlock() {
	//flagはブロックが移動していいかどうかを判定する
	bool flag = false;
	//ブロックが移動できるか判定
	for (int x = 0; x < 11; x++) {
		for (int y = 0; y < 20; y++) {
			if ((blocks[x][y].status == 1 || blocks[x][y].status == 4) && (blocks[x + 1][y].status == 2 || blocks[x + 1][y].status == 3)) {
				flag = true;
			}
		}
	}
	if (flag == false) {
		//移動してよいので移動
		for (int x = 1; x < 11; x++) {
			for (int y = 0; y < 19; y++) {
				if (blocks[x][y].status == 2 || blocks[x][y].status == 3) {
					blocks[x - 1][y].status = blocks[x][y].status;
					blocks[x - 1][y].color = blocks[x][y].color;
					blocks[x][y].status = 0;
					blocks[x][y].color = 0;
				}
			}
		}
	}
	flag = false;
}

void RightBlock() {
	//flagはブロックが移動していいかどうかを判定する
	bool flag = false;
	//ブロックが移動できるか判定
	for (int x = 1; x < 12; x++) {
		for (int y = 0; y < 20; y++) {
			if ((blocks[x][y].status == 1 || blocks[x][y].status == 4) && (blocks[x - 1][y].status == 2 || blocks[x - 1][y].status == 3)) {
				flag = true;
			}
		}
	}
	if (flag == false) {
		//移動してよいので移動
		for (int x = 10; x >= 1; x--) {
			for (int y = 0; y < 19; y++) {
				if (blocks[x][y].status == 2 || blocks[x][y].status == 3) {
					blocks[x + 1][y].status = blocks[x][y].status;
					blocks[x + 1][y].color = blocks[x][y].color;
					blocks[x][y].status = 0;
					blocks[x][y].color = 0;
				}
			}
		}
	}
	flag = false;
}

void DeleteBlock() {
	//新しい変数(今まで消したLineの数を格納する)
	int deleteLine = 0;

	for (int y = 18; y > 1; y--) {
		bool flag = true;
		for (int x = 1; x <= 10; x++) {
			if (blocks[x][y].status == 0) {
				flag = false;
			}
		}
		//こっちが消える時の処理
		if (flag == true) {
			for (int x = 1; x <= 10; x++) {
				blocks[x][y].status = 0;
				blocks[x][y].color = 0;
			}
			deleteLine++;
		}
		//こっちが消えない時の処理
		if (flag == false) {
			for (int x = 1; x <= 10; x++) {
				if (blocks[x][y].status == 4) {
					blocks[x][y + deleteLine].status = blocks[x][y].status;
					blocks[x][y + deleteLine].color = blocks[x][y].color;
					if (deleteLine > 0) {
						blocks[x][y].status = 0;
						blocks[x][y].color = 0;
					}
				}
			}
		}
	}
}

void LeftRotateBlock() {
	//回転用盤面
	BLOCKINFO subBlocks[12][20] = { 0 };
	//回転中心の座標
	int originX = 0, originY = 0, xFromOrigin = 0, yFromOrigin = 0;

	//回転用盤面の作成
	for (int x = 0; x < 12; x++) {
		for (int y = 0; y < 20; y++) {
			if (blocks[x][y].status != 2 && blocks[x][y].status != 3) {
				subBlocks[x][y].status = blocks[x][y].status;
				subBlocks[x][y].color = blocks[x][y].color;
			}
		}
	}
	//回転中心の発見
	for (int x = 0; x < 12; x++) {
		for (int y = 0; y < 20; y++) {
			if (blocks[x][y].status == 3) {
				originX = x;
				originY = y;
				subBlocks[x][y].status = 3;
				subBlocks[x][y].color = blocks[x][y].color;
			}
		}
	}
	//回転させる
	for (int x = 0; x < 12; x++) {
		for (int y = 0; y < 20; y++) {
			if (blocks[x][y].status == 2) {
				xFromOrigin = x - originX;
				yFromOrigin = y - originY;
				if (1 > originX + (-1 * yFromOrigin) && originX + (-1 * yFromOrigin) > 10)return;
				if (0 > originY + xFromOrigin && originY + xFromOrigin > 18)return;
				if(subBlocks[originX + (-1 * yFromOrigin)][originY + xFromOrigin].status != 0)return;
				subBlocks[originX + (-1 * yFromOrigin)][originY + xFromOrigin].status = blocks[x][y].status;
				subBlocks[originX + (-1 * yFromOrigin)][originY + xFromOrigin].color = blocks[x][y].color;
			}
		}
	}
	//盤面に反映
	for (int x = 0; x < 12; x++) {
		for (int y = 0; y < 20; y++) {
			blocks[x][y].status = subBlocks[x][y].status;
			blocks[x][y].color = subBlocks[x][y].color;
		}
	}
}

void RightRotateBlock() {
	//回転用盤面
	BLOCKINFO subBlocks[12][20] = { 0 };
	//回転中心の座標
	int originX = 0, originY = 0, xFromOrigin = 0, yFromOrigin = 0;

	//回転用盤面の作成
	for (int x = 0; x < 12; x++) {
		for (int y = 0; y < 20; y++) {
			if (blocks[x][y].status != 2 && blocks[x][y].status != 3) {
				subBlocks[x][y].status = blocks[x][y].status;
				subBlocks[x][y].color = blocks[x][y].color;
			}
		}
	}
	//回転中心の発見
	for (int x = 0; x < 12; x++) {
		for (int y = 0; y < 20; y++) {
			if (blocks[x][y].status == 3) {
				originX = x;
				originY = y;
				subBlocks[x][y].status = 3;
				subBlocks[x][y].color = blocks[x][y].color;
			}
		}
	}
	//回転させる
	for (int x = 0; x < 12; x++) {
		for (int y = 0; y < 20; y++) {
			if (blocks[x][y].status == 2) {
				xFromOrigin = x - originX;
				yFromOrigin = y - originY;
				if (1 > originX + yFromOrigin && originX + yFromOrigin > 10)return;
				if (0 > originY + (-1 * xFromOrigin) && originY + (-1 * xFromOrigin) > 18)return;
				if (subBlocks[originX + yFromOrigin][originY + (-1 * xFromOrigin)].status != 0)return;
				subBlocks[originX + (yFromOrigin)][originY + (-1 * xFromOrigin)].status = blocks[x][y].status;
				subBlocks[originX + (yFromOrigin)][originY + (-1 * xFromOrigin)].color = blocks[x][y].color;
			}
		}
	}
	//盤面に反映
	for (int x = 0; x < 12; x++) {
		for (int y = 0; y < 20; y++) {
			blocks[x][y].status = subBlocks[x][y].status;
			blocks[x][y].color = subBlocks[x][y].color;
		}
	}
}

void FinishTetris() {
	for (int x = 0; x < 12; x++) {
		for (int y = 0; y < 20; y++) {
			if (blocks[x][y].status != 0) {
				blocks[x][y].color = 1;
			}
		}
	}
}