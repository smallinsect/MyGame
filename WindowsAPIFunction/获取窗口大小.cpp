

//该函数返回指定窗口的边框矩形的尺寸。该尺寸以相对于屏幕坐标左上角的屏幕坐标给出。
GetWindowRect(hWnd, &rect);
len = wsprintf(szBuffer, TEXT("left=%d top=%d right=%d bottom=%d"), rect.left, rect.top, rect.right, rect.bottom);
TextOut(hdc, 0, 0, szBuffer, len);

//该函数获取窗口客户区的大小。注意一下：窗口的客户区为窗口中除标题栏、菜单栏之外的地方。
GetClientRect(hWnd, &rect);
len = wsprintf(szBuffer, TEXT("left=%d top=%d right=%d bottom=%d"), rect.left, rect.top, rect.right, rect.bottom);
TextOut(hdc, 0, 30, szBuffer, len);

