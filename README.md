# GameProject
游戏素材网址
http://www.java1234.com/a/kaiyuan/sucai/2014/0930/2967.html

##### Cocos2d笔记

```
创建项目
进入cmd模式，切换目录
cd D:\cocos2d-x-3.17.1\tools\cocos2d-console\bin
运行脚本，创建新项目
cocos new LittlePlane -p com.cainiao.org -l cpp -d E:/smallinsect/GameProject/cocosgame
打开proj.win32文件夹下的LittleDemo.sln
按下F5，运行项目
```

##### C/C++笔记

```
c++11 特性
定义
enum class NewColor{ Red, Green, Blue};
使用
NewColor r = NewColor::Red;

//编译生成的文件名为main
g++ -o main main.cpp
//c++11标准编译
g++ -std=c++11 main.cpp
//添加thread动态库
g++ -std=c++11 main.cpp -lphtread

查看版本 gcc --version

官网 http://gcc.gnu.org/

安装clang软件 sudo apt-get install clang

安装make工具 sudo apt-get install make
安装cmake工具 sudo apt-get install cmake

g++ -o server server.cpp
gdb ./server
r启动调试
```








# MFC常用代码笔记

## 显示图片流程

1. 获取窗口DC
2. 创建位图并调用LoadImage装载图标、光标、或位图
3. 定义病创建一个内存设备环境DC，调用函数CreateCompatibleDC创建兼容的DC
4. 调用函数SelectObject将位图选入兼容内存设备环境DC中
5. 将兼容的DC中的位图添加当前DC中，调用函数BitBlt、StrechBlt、TransparentBlt显示图像
6. 恢复临时DC的位图，删除内存中的位图，删除兼容的DC，及释放系统资源

## 获取窗口DC

```
HDC GetDC(HWND hwnd)              // HWND指要获取DC对应的窗口的句柄
int ReleaseDC(HWND hWnd, HDC hDC) // 释放DC
```

## 加载位图

```
LoadImage(NULL, TEXT("./res/walk.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);

IMAGE_BITMAP
IMAGE_ICON
IMAGE_CURSOR

```

## 创建兼容DC

```
HDC CreateCompatibleDC(HDC hdc)
DeleteDC(HDC dc)

必须在所要进行绘图的DC中选择位图，才会产生预期的绘图效果
HGDIOBJ SelectObject(HDC hdc, HGDIOBJ GDI)
GDI对象有：画笔，画刷，位图，字体，区域，调色板。
GDI一旦建立就会占用内存，一旦不使用就务必用DeletObject将他们删除。
BOOL DeleteObject(HGDIOBJ GDI对象)
删除成功返回TRUE，失败返回FALSE
```

## 将缓存中图选入显示器DC中



```
BitBlt、StrechBlt、TransparentBlt
```

## 位图透明处理

方法一

```
BitBlt(hDC, x1, y1, w, h, hMdc, x2, y2, SRC_AND)
BitBlt(hDC, x1, y1, w, h, hMdc, x2, y2, SRC_PAINT)
```

方法二

```
StretchBlt(hDC, x1, y1, w1, h1, hMdc, x2, y2, w2, h2, SRC_AND)
StretchBlt(hDC, x1, y1, w1, h1, hMdc, x2, y2, w2, h2, SRC_PAINT)
```

方法三

```
TransparentBlt(hDC, x1, y1, w1, h1, hMdc, x2, y2, w2, h2, RGB(0, 255, 0))
```



## 实际使用

显示图片

```
// 加载位图
HBITMAP hbmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), TEXT("./res/walk.bmp"), IMAGE_BITMAP, 0, 0, NULL);
// 创建兼容DC
HDC hMDC = ::CreateCompatibleDC(hDC);
// 图片加入兼容DC
::SelectObject(hMDC, hbmp);
// 获取显示器DC
HDC hDC = ::GetDC(this->m_hWnd);
// 将内存DC中的图片选入显示器DC中
::BitBlt(hDC, 0, 0, 400, 200, hMDC, 0, 0, SRCCOPY);
// 删除内存DC
::DeleteDC(hMDC);
// 释放显示器DC
::ReleaseDC(this->m_hWnd, hDC);
```

透明处理：方法一

```
// 加载位图
HBITMAP hbmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), TEXT("./res/walk.bmp"), IMAGE_BITMAP, 0, 0, NULL);
// 创建兼容DC
HDC hMDC = ::CreateCompatibleDC(hDC);
// 图片加入兼容DC
::SelectObject(hMDC, hbmp);
// 获取显示器DC
HDC hDC = ::GetDC(this->m_hWnd);
// 将内存DC中的图片选入显示器DC中
::TransparentBlt(hDC, 0, 0, 40, 40, hMDC, 0, 0, 40, 40, RGB(0, 255, 0));//最后一个参数是需要过滤的颜色
// 删除内存DC
::DeleteDC(hMDC);
// 释放显示器DC
::ReleaseDC(this->m_hWnd, hDC);
```

透明处理：方法二

```
// 加载位图
HBITMAP hbmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), TEXT("./res/walk.bmp"), IMAGE_BITMAP, 0, 0, NULL);
// 创建兼容DC
HDC hMDC = ::CreateCompatibleDC(hDC);
// 图片加入兼容DC
::SelectObject(hMDC, hbmp);
// 获取显示器DC
HDC hDC = ::GetDC(this->m_hWnd);
// 将内存DC中的图片选入显示器DC中
::BitBlt(hDC, 0, 0, 40, 40, hMDC, 0, 0, SRCAND);// 先进行与
::BitBlt(hDC, 0, 0, 40, 40, hMDC, 0, 40, SRCPAINT);// 在进行或
// 删除内存DC
::DeleteDC(hMDC);
// 释放显示器DC
::ReleaseDC(this->m_hWnd, hDC);
```

透明处理：方法三

```
// 加载位图
HBITMAP hbmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), TEXT("./res/walk.bmp"), IMAGE_BITMAP, 0, 0, NULL);
// 创建兼容DC
HDC hMDC = ::CreateCompatibleDC(hDC);
// 图片加入兼容DC
::SelectObject(hMDC, hbmp);
// 获取显示器DC
HDC hDC = ::GetDC(this->m_hWnd);
// 将内存DC中的图片选入显示器DC中
::StretchBlt(hDC, 0, 0, 40, 40, hMDC, 0, 0, 40, 40, SRCAND);// 先进行与
::StretchBlt(hDC, 0, 0, 40, 40, hMDC, 0, 40, 40, 40, SRCPAINT);// 在进行或
// 删除内存DC
::DeleteDC(hMDC);
// 释放显示器DC
::ReleaseDC(this->m_hWnd, hDC);
```



```
CBitmap m_tank;
BITMAP m_bm;

HBITMAP hbmp = (HBITMAP)LoadImage(NULL, TEXT("./res/walk.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
if (hbmp == NULL) {
    AfxMessageBox(TEXT("加载位图失败"));
    return CView::PreCreateWindow(cs);
}
m_tank.Attach(hbmp);
m_tank.GetBitmap(&m_bm);
```

画图

```
CDC* pDC = GetDC();
m_dc.CreateCompatibleDC(pDC);//创建缓存DC
m_dc.SelectObject(m_tank);//缓存DC绑定坦克图片

pDC->StretchBlt(x, y,
    m_bm.bmWidth, m_bm.bmHeight,
    &m_dc,
    0, 0,
    m_bm.bmWidth, m_bm.bmHeight,
    SRCCOPY);
m_dc.DeleteDC();

ReleaseDC(pDC);
```

```
int w = GetSystemMetrics(SM_CXSCREEN);//获取桌面屏幕宽度
int h = GetSystemMetrics(SM_CYSCREEN);//获取桌面屏幕高度
//移动窗口位置0,0，窗口大小宽w，高h
MoveWindow(0, 0, w, h);
```

## 鼠标消息

```
WM_MOUSEFIRST    
WM_MOUSEMOVE     
WM_LBUTTONDOWN   
WM_LBUTTONUP     
WM_LBUTTONDBLCLK 
WM_RBUTTONDOWN   
WM_RBUTTONUP     
WM_RBUTTONDBLCLK 
WM_MBUTTONDOWN   
WM_MBUTTONUP     
WM_MBUTTONDBLCLK 
```

## 键盘消息

```
WM_KEYDOWN
WM_KEYUP
```

使用

```
void CMyTankView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
	if (nChar == 'W') {
		// ...
	}
}
```

## 定时器

```
开启定时器
UINT_PTR SetTimer(
    HWND hWnd,             // 执行的窗口
    UINT_PTR nIDEvent,     // 定时器 ID
    UINT uElapse,          // 间隔时间秒
    TIMERPROC lpTimerFunc);// 定时器执行的函数

// 关闭定时器
BOOL KillTimer(
    HWND hWnd,         // 执行的窗口
    UINT_PTR uIDEvent);// 定时器ID
```

## 双缓冲技术



























