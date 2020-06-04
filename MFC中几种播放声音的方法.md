# [MFC中的几种播放声音的方法]

一．播放声音文件的简单方法
　　在VC++ 中的多媒体动态连接库中提供了一组与音频设备有关的函数。利用这些函数可以方便地播放声音。最简单的播放声音方法就是直接调用VC++中提供的声音播放函 数BOOL sndPlaySound ( LPCSTR lpszSound,UINT fuSound ); 或BOOL PlaySound( LPCSTR lpszSound, HMODULE hmod, DWORD fuSound );其中参数lpszSound是需要播放声音的.WAV文件的路径和文件名， hmod在这里为NULL，fuSound是播放声音的标志,详细说明请参考VC++中的帮助。 例如播放C:\sound\music.wav可以用sndPlaySound ("c:\\sound\\music.wav",SND_ASYNC);或PlaySound("c:\\sound \\music.wav",NULL, SND_ASYNC|SND_NODEFAULT );如果没有找到music.wav文件，第一种格式将播放系统默认的声音，第二种格式不会播放系统默认的声音。

二．将声音文件加入到程序中
　　在VC++的程序设计中，可以利用各种标准的资源，如位图，菜单，对话框等。同时VC++也允许用户自定义资源，因此我们可以将声音文件作为用户自定义资源加入程序资源文件中，经过编译连接生成EXE文件，实现无.WAV文件的声音播放。
　　要实现作为资源的声音文件的播放，首先要在资源管理器中加入待播放的声音文件（实现过程并不复杂，这里不在叙述）。假设生成的声音文件资源标识符为IDR_WAVE1。在播放时只需要调用下面的语句：
　　PlaySound(MAKEINTRESOURCE(IDR_WAVE1),AfxGetResourceHandle(), 　　SND_ASYNC|SND_RESOURCE|SND_NODEFAULT|SND_LOOP);
　　其中MAKEINTRESOURCE()宏将整数资源标识符转变为字符串，AfxGetResourceHandle()函数返回包含资源的模块句柄，
SND_RESOURCE是必须的标志。
　　作为资源的声音文件的第二种播放方法是把资源读入内存后作为内存数据播放。具体步骤入下：
　　1．获得包含资源的模块句柄：
　　HMODULE hmod=AfxGetResourceHandle();
　　2．检索资源块信息：
　　HRSRC hSndResource=FindResource(hmod,MAKEINTRESOURCE(IDR_WAVE1),_T("WAVE"));
　　3. 装载资源数据并加锁：
　　HGLOBAL hGlobalMem=LoadResource(hmod,hSndResource);
LPCTSTR lpMemSound=(LPCSTR)LockResource(hGlobalMem);
　　4．播放声音文件：
　　sndPlaySound(lpMemSound,SND_MEMORY))；
　　5．释放资源句柄：
　　FreeResource(hGlobalMem);

第三种方法是用PlaySound播放系统声音，Windows启动的声音是由SystemStart定义的系统声音，因此可以用下面的方法播放启动声音：
PlaySound("SystemStart",NULL,SND_ALIAS|SND_ASYNC);
函数sndPlaySound的功能与PlaySound类似，但少了一个参数。函数的声明为：
BOOL sndPlaySound(LPCSTR lpszSound, UINT fuSound);
除 了不能指定资源名字外，参数lpszSound与PlaySound的是一样的。参数fuSound是如何播放声音的标志，可以是SND_ASYNC、 SND_LOOP、SND_MEMORY、SND_NODEFAULT、SND_NOSTOP和SND_SYNC的组合，这些标志的含义与 PlaySound的一样。
可以看出，sndPlaySound不能直接播放声音资源。要用该函数播放WAVE文件，可按下面的方式调用：
sndPlaySound(“MYSOUND.WAV”,SND_ASYNC)