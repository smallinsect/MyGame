#pragma once
class MyTank
{
public:
	void Init();
	void SetDire(int dire);//设置坦克方向
	void Move();//坦克移动
	void Draw(Graphics* graphics);//画坦克
private:
	int m_dire; // 坦克方向
	int m_frame; // 坦克帧数
	int m_widht; // 坦克每张图片宽度
	int m_height;// 坦克每张图片高度
	int m_speed; //坦克移动速度
	CPoint m_pos; // 坦克坐标
	Image* m_tank[4][2];//坦克图片
};

