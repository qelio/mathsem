// Visualization.cpp: файл реализации
//

#include "stdafx.h"
#include "Semantics.h"
#include "Visualization.h"


// Visualization

IMPLEMENT_DYNAMIC(Visualization, CStatic)

Visualization::Visualization()
{

}

Visualization::~Visualization()
{
}


BEGIN_MESSAGE_MAP(Visualization, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// обработчики сообщений Visualization




void Visualization::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: добавьте свой код обработчика сообщений
	// Не вызывать CStatic::OnPaint() для сообщений рисования
}
