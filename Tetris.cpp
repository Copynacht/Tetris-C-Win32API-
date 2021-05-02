#include"Tetris.h"
HINSTANCE hInstance;
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hnInst, LPSTR CmdLine, int CmdShow)
{
	MSG msg;
	BOOL bl;
	hInstance = hInst;
	srand((unsigned int)time(NULL));
	if (!InitApp(hInst))return FALSE;
	if (!InitInstance(hInst, CmdShow))return FALSE;
	while ((bl = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (bl == -1) {
			break;
		}
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}return (int)msg.wParam;
}
ATOM InitApp(HINSTANCE hInst)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInst;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WinProc;
	wc.hIcon = (HICON)LoadImage(hInst, TEXT("MYICON"), IMAGE_ICON, 0, 0, 0);
	wc.hCursor = (HCURSOR)LoadImage(hInst, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
	wc.lpszMenuName = 0;
	wc.lpszClassName = szClassName;
	wc.hIconSm = (HICON)LoadImage(hInst, TEXT("MYICON"), IMAGE_ICON, 0, 0, 0);
	return (RegisterClassEx(&wc));
}
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
	HWND hWnd;
	hWnd = CreateWindow(szClassName, TEXT("テトリス"),
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
		NULL, NULL, hInst, NULL);
	if (!hWnd)
		return FALSE;
	ShowWindow(hWnd, nCmdShow);;
	UpdateWindow(hWnd);
	return TRUE;
}
LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	static HDC hd, hdc, hdc_mem;
	static HBITMAP hBmp, hcBmp;
	static PAINTSTRUCT ps;
	static HBITMAP hbg;
	static int count=0, rcount=0, lcount = 0, rrcount = 0, lrcount = 0;
	switch (msg) {
		//ウィンドウが作成されたときに1回だけ呼ばれる
	case WM_CREATE:
		hBmp = (HBITMAP)LoadImage(hInstance, TEXT("MAINBITMAP"), IMAGE_BITMAP, 0, 0, 0);
		hdc = GetDC(hWnd);
		hdc_mem = CreateCompatibleDC(NULL);
		hbg = CreateCompatibleBitmap(hdc, WIDTH, HEIGHT);
		SelectObject(hdc, hbg);
		SelectObject(hdc_mem, hBmp);
		InitBlock();
		DeleteBlock();
		NewBlock();
		SetTimer(hWnd, ID_MYTIMER, 40, NULL);
		break;
		//ウィンドウの描画が更新されるときに呼ばれる
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		PaintBlock(hdc, hdc_mem);
		EndPaint(hWnd, &ps);
		break;
		//タイマー
	case WM_TIMER:
		count++;
		if (GetAsyncKeyState(VK_RIGHT))rcount++;
		else rcount = 0;
		if (GetAsyncKeyState(VK_LEFT)) lcount++;
		else lcount = 0;
		if (GetAsyncKeyState(0X5a)) rrcount++;
		else rrcount = 0;
		if (GetAsyncKeyState(0x58)) lrcount++;
		else lrcount = 0;
		if (GetAsyncKeyState(VK_DOWN))
			DropBlock();
		if (rcount == 1) {
			rcount = 0;
			RightBlock();
		}
		if (lcount == 1) {
			lcount = 0;
			LeftBlock();
		}
		if (rrcount == 2) {
			rrcount = 0;
			RightRotateBlock();
		}
		if (lrcount == 2) {
			lrcount = 0;
			LeftRotateBlock();
		}
		if (count == 20) {
			count = 0;
			DropBlock();
		}
		
		InvalidateRect(hWnd, NULL, FALSE);
		break;
		//ウィンドウを破棄するときに呼ばれる
	case WM_DESTROY:
		DeleteDC(hdc);
		DeleteDC(hdc_mem);
		DeleteObject(hbg);
		DeleteObject(hBmp);
		PostQuitMessage(0);
		break;
		//それ以外
	default:
		return (DefWindowProc(hWnd, msg, wp, lp));
		break;
	}return 0;
}