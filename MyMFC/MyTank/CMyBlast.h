#pragma once
class CMyBlast{
private:
	CPoint m_pos;// 爆炸坐标

	int m_iCurFrame;// 当前帧数
	int m_iFrame; // 总共帧数

	CBitmap m_cb[5];//爆炸位图
	BITMAP m_bm[5];//图片大小

	CDC m_dc;//内存兼容DC
public:
	CPoint GetPos() {
		return m_pos;
	}
	void SetPos(CPoint pos) {
		m_pos = pos;
	}

	void Init();
	void Update();
	void Draw(CDC *pDC);
};

