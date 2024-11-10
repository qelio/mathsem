#pragma once


// Visualization

class Visualization : public CStatic
{
	DECLARE_DYNAMIC(Visualization)

public:
	Visualization();
	virtual ~Visualization();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


