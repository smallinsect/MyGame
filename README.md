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








##### MFC常用代码笔记

加载位图

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

```
int w = GetSystemMetrics(SM_CXSCREEN);//获取桌面屏幕宽度
int h = GetSystemMetrics(SM_CYSCREEN);//获取桌面屏幕高度
//移动窗口位置0,0，窗口大小宽w，高h
MoveWindow(0, 0, w, h);
```

