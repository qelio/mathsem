//  ����� ����: ���������� �.�., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014

#include "stdafx.h"
#include "SemanticString.h"

//TRANSLATED




// ����������� �� ���������
//
SemanticString::SemanticString()
{
	text = new tstring;
	formula = NULL;
}

//
// ����������
//
SemanticString::~SemanticString()
{
	if(text)
	{
		delete text;
		text = NULL;
	}
}


SemanticString SemanticString::operator=(SemanticString &str) {
	for(int i = 0; i < 256; i++)
	{
		tchars[i] = str.tchars[i];
		symbolics[i] = str.symbolics[i];
	}
	count = str.count;
//	if(text)
//		delete text;
//	text = new tstring;
	if(str.text && str.text->length() > 0)
		*text = *str.text;
	size = str.size;
	return *this;
}


//
// ����� �������� ������ � ��������������� ������ � ��������� �� �� ����� ������� ������ SemanticString. �������������� � Word ��������� ���������� ��
// �������������� ��� ��������� ������, ���������� � ������ forWordExport, ������������ � true
//
bool SemanticString::PrepareSubItemData(tstring & tstr, bool forWordExport)
{
	bool result = true;
		if(!forWordExport)
			*text = tstr;
		count = 0;    // ���������� ��� ���������� ��������
		size.cx = 0;
		size.cy = 0;
		// ������ ������ �� �������������� ������� � ���� <symbol=..>
		bool isFound = false;
		int worked = 0;   // ����� ������������ ��������
		int pos = 0;    // ��������� � ������, � �������� �������� ����� ������ ���� '<'
		while ( (pos = tstr.find(_T("<"), pos)) != -1)    // ���� ����� ��� ������, ������� � ��������� pos
		{
			isFound = false;
			// ��� ������� �� ������� pos ������� � ��������� dataSubItes ��� ������� (�� �������������� �������)
			int diff = pos - worked;    // ����� ��������, ������� ���� �������
			for ( int k = 0; k < diff; k++)
			{
				tchars[count] = tstr.at(worked);     // ������� ��������� ������
				symbolics[count] = 0;                // ���������, ��� ��� ������� ������ ( �� ������ � �� ��������������)
				worked ++;			// ��������� ����� ������������ ��������
				count ++;			// ��������� ����� ������������ � tchar � symbolics ���������
			}
			int pos1 = tstr.find(_T(">"), pos + 1);    // ����� ������� ���� '>' ������,������� � ������� ���������� �� ��������� ����� �����
			if ( pos1 > 0 )     // ���� ������ ��� ������
			{
				tstring part_tstr = tstr.substr(pos + 1, pos1 - pos - 1);    // ������� ��������� ������ ������ � ������� �����
				trimWhitespaces(&part_tstr);    // ������ ��������� � ����������� �������
				// �������� ���������� ��������� �� ������������ ���� <symbol=..> ��� <s=..>
				int pos_of_equal = part_tstr.find(_T("="));    // ������ ������� ��������� ����� ���������
				if ( (pos_of_equal > 0) && (pos_of_equal < ((int)part_tstr.size() - 1)) )   // ���� �� ��������� ������ ���������� ���������
				{
					tstring beforeDelim = part_tstr.substr(0, pos_of_equal);    // ��������� �� ����� ���������
					tstring afterDelim = part_tstr.substr(pos_of_equal + 1, part_tstr.size() - pos_of_equal);    // ��������� ����� ����� ���������
					// ������ ��������� � ����������� ���������� ������� ��� ����� ���������� ��������
					trimWhitespaces(&beforeDelim);     
					trimWhitespaces(&afterDelim);
					transform(beforeDelim.begin(), beforeDelim.end(), beforeDelim.begin(), ::tolower); // �������� ������ �� ���� �������� � lower case
					if (!beforeDelim.compare(_T("s")) || !beforeDelim.compare(_T("symbol")) )    // ��������� �� ���������� � 'symbol' ��� 's'
					{
						// ��������� ������ ��������� � ����������� � ����� �� ����������� �����������, ���� �������, �� ������ � tchar � symbolics �
						// ������ ����, ��� ��������� ����� ���������� ���
						if(!afterDelim.compare(_T("/low")) )  //low index
						{
							tchars[count] = TCHAR(0x20);
							symbolics[count] = LOW_MATHINDEX;
							isFound = true;
						}
						else if(!afterDelim.compare(_T("/high")) ) //high index
						{
							tchars[count] = TCHAR(0x20);
							symbolics[count] = HIGH_MATHINDEX;
							isFound = true;
						}
						else if(!afterDelim.compare(_T("/left_tag")) ) //left tag
						{
//							tchars[count] = TCHAR('<');
//							symbolics[count] = SYMBOL_TYPEFACE;
//							isFound = true;
							if(forWordExport)
								tchars[count] = TCHAR(0xe1);
							else
								tchars[count] = TCHAR(0x2329);
//								tchars[count] = TCHAR(0x2229);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if(!afterDelim.compare(_T("/right_tag")) ) //right tag
						{
//							tchars[count] = TCHAR('>');
//							symbolics[count] = SYMBOL_TYPEFACE;
//							isFound = true;
							if(forWordExport)
								tchars[count] = TCHAR(0xf1);
							else
								tchars[count] = TCHAR(0x232a);
//								tchars[count] = TCHAR(0x2229);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if(!afterDelim.compare(_T("/34")) )  // first quantor
						{
							if(forWordExport)
								tchars[count] = TCHAR(0x22);
							else
								tchars[count] = TCHAR(0x2200);
//								tchars[count] = TCHAR(0x22); ��� ������ Symbol
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if(!afterDelim.compare(_T("/36")) )  //second quantor
						{
							if(forWordExport)
								tchars[count] = TCHAR(0x24);
							else
								tchars[count] = TCHAR(0x2203);
//								tchars[count] = TCHAR(0x24); ��� ������ Symbol
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if ( (!afterDelim.compare(_T("/38")) )  || (!afterDelim.compare(_T("/and")) ) )//and
						{
							if(forWordExport)
								tchars[count] = TCHAR(0x26);
							else
								tchars[count] = TCHAR(0x0026);
//								tchars[count] = TCHAR(0x26); ��� ������ Symbol
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if(!afterDelim.compare(_T("/123")) )  //����� �������� ������
						{
							tchars[count] = TCHAR(123);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if(!afterDelim.compare(_T("/125")) )  //������ �������� ������
						{
							tchars[count] = TCHAR(125);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if ( (!afterDelim.compare(_T("/216")) )  || (!afterDelim.compare(_T("/not")) ) ) //not
						{
							if(forWordExport)
								tchars[count] = TCHAR(216);
							else
								tchars[count] = TCHAR(0x00AC);
//								tchars[count] = TCHAR(0x0428);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if ( (!afterDelim.compare(_T("/218")) ) || (!afterDelim.compare(_T("/or")) ) )//���
						{
							if(forWordExport)
								tchars[count] = TCHAR(0xda); //tchars[count] = TCHAR(0xc7);
							else
								tchars[count] = TCHAR(0x2228);
//								tchars[count] = TCHAR(0x042A);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if ( (!afterDelim.compare(_T("/199")) ) || (!afterDelim.compare(_T("/crossing")) ) )//�����������
						{
							if(forWordExport)
								tchars[count] = TCHAR(0xc7);
							else
								tchars[count] = TCHAR(0x2229);
//								tchars[count] = TCHAR(0x417);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if ( (!afterDelim.compare(_T("/200")) ) || (!afterDelim.compare(_T("/union")) ) )//�����������
						{
							if(forWordExport)
								tchars[count] = TCHAR(0xc8);
							else
								tchars[count] = TCHAR(0x222A);
//								tchars[count] = TCHAR(0x418);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if ( (!afterDelim.compare(_T("/204")) ) || (!afterDelim.compare(_T("/similar")) ) )//�������
						{
							if(forWordExport)
								tchars[count] = TCHAR(0xcc);
							else
								tchars[count] = TCHAR(0x2282);
//								tchars[count] = TCHAR(0x041c);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if (!afterDelim.compare(_T("/empty")) ) //empty_set
						{
							if(forWordExport)
								tchars[count] = TCHAR(0xc6);
							else
								tchars[count] = TCHAR(0x2205);
//								tchars[count] = TCHAR(0x041c);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if (!afterDelim.compare(_T("/fuzzy")) ) //fuzzy inclusion
						{
							if(forWordExport)
								tchars[count] = TCHAR(0xcc);
							else
								tchars[count] = TCHAR(0x2286);
//								tchars[count] = TCHAR(0x041c);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if ( (!afterDelim.compare(_T("/0xCE")) ) || (!afterDelim.compare(_T("/206")) ) || (!afterDelim.compare(_T("/in")) ) )//�������������
						{
							// ��� ����� ������� ���� �������� ��� �������������� � Word'������ ��������
							if(forWordExport)
								tchars[count] = TCHAR(206);
							else
								tchars[count] = TCHAR(0x2208);
//								tchars[count] = TCHAR(0x041E);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
					}
				}
				if(isFound)	// ���� ���������(�) ���(�) ��������� � �������������� ��������, � �� ������ ����
				{
					count++;    // ����������� �������
					isFound = false;     // �������, � ������� ����
					worked += (pos1 + 1 - pos);	// ����������� ������� ����� ������������ ��������
				}
				pos = pos1 + 1; // ���������� pos ��� ����� �������� ������
			}
			else     // �� ������ ������ ���
				break;    // ��������� ����
			if( pos >= ((int)tstr.size() - 2) )    // ���� ��� ������� ������� ������ ��� ��� ������ ��������
				break;    // �������� ����, ��� ��� ������ ������ ������ ���

		}
		// � ����� ��������� ���� �������� �������� � dataSubItme �� ������, ������� �� ������� ����� ���������� ����� �� ��������� ����� ������ ���� 
		// ����� ����, ��� ���� ��� � �� ���������. �� ���� ���������, ���������� �������������� ����� �� �������, ������� ���������� ������� �� ������
		// ��� �������
		if(worked < (int)tstr.size())
		{
			for ( size_t j = worked; j < tstr.size(); j++)
			{
				tchars[count] = tstr.at(j);
				symbolics[count] = 0;
				count++;
			}
		}
		// ������ ���������, ������ ��������� ��� ���������� �� ������ � ���������� ������ ������ �� ����� (���� �� ����������)
		for ( int j = 0; j < count; j++)
		{
			CSize sizeSymbol;
			sizeSymbol.cx = 0;
			sizeSymbol.cy = 0;
			switch(tchars[j])
			{
			case LOW_MATHINDEX:
				// ���� ����� ��������� ������ ���������� �������, ������ ����������
				break;
			case HIGH_MATHINDEX:
				// ���� ����� ��������� ������ ���������� �������, ������ ����������
				break;
			case SYMBOL_TYPEFACE:
				break;
				
			case NONE_MATHSTYLE:
			default:
				CString cstest(tchars[j]);
//				sizeSymbol = dc.GetTextExtent(cstest);
				break;
			}
			size.cx += sizeSymbol.cx;
		}
		tchars[count] = TCHAR(0x00);
	return result;
}

//
// ����� ������������ ������ SemanticString, ������� �������������� ������� 'PrepareSubItemData' � �������������� rectSubItem ��� ��������� 
// ���������� dc. ��� ��������� �������� ������������ ����� m_fIndexes, ��� ��������� �������������� �������� m_fSymbol (��� �������, ����� Symbol)
//
void SemanticString::DrawItem(CDC &dc, CRect &rectSubItem, CFont * m_fSymbol, CFont * m_fIndexes)
{
	CFont * pOldFont = NULL;
	CRect rectReal = rectSubItem;
	rectReal.left += 2;    // �������� ����� ������� �� 2 �������
	int indexing = 0;    // ���������� ��� ���� ��������������, ������������ ������������ ��� ����, ����� ��������, ��� ������ ����� ������������ ��� ������
	// ���� �� ����� ��������, ������������ � ������� SemanticString
	for (int j = 0; j < count; j++)    
	{
		TCHAR tch[4];    // ������ ��� ���������� �������� ���������� �������
		tch[0] = tchars[j];
		tch[1] = TCHAR(0x00);    // ���������� � 0, ����� ������������ ��� �-������
		if( ( symbolics[j] == LOW_MATHINDEX ) || ( symbolics[j] == HIGH_MATHINDEX ) )     // ���� ������
		{
			indexing = symbolics[j];    // ��������� ��� ��������������
			continue;    // ������� � ������������ ������� �� tchars
		}
		CSize sizeSymbol;    // ���������� ��� ������� �������
		CRect rectIndex ;    // ������������� ��� ����������� ������� ��� �������
		if ( indexing == LOW_MATHINDEX ) // ���� ��� ��������� ��� ������ ��������
		{
			pOldFont = dc.SelectObject(m_fIndexes);    // ��������� ����� ��� ����������� ��������
		}
		else
		{
			if ( symbolics[j] == SYMBOL_TYPEFACE )
			{
				pOldFont = dc.SelectObject(m_fSymbol);
				// ���������� ����� Symbol
			}
//				sizeSymbol = dc.GetTextExtent(tch);
		}
		sizeSymbol = dc.GetTextExtent(tch);    // �������� ������
		if ( tch[0] == TCHAR(0x26) ) //  ���� �����������
		{
			tch[1] = tch[0];    // ����������� � ������ ����������, ����� ����������� ���������� (�� ���������� ����������), ����� ���������
			tch[2] = TCHAR(0x00);
		}
		rectReal.right = rectReal.left + sizeSymbol.cx;    // ������������ ������ �������������� ����������� �������
		if( rectReal.right >= rectSubItem.right ) // ���� ����������� ������� �� �������, ��������������� ���� � ��������� ���� 
		{
			if(pOldFont != NULL)
			{
				dc.SelectObject(pOldFont);
				pOldFont = NULL;
			}
			break;
		}
		if(indexing)    // ���� ������������ ������, ���������� ������������� ����������� ��� ����
		{
			rectIndex = rectReal;
			rectIndex.top += (sizeSymbol.cy / 2);    // �������� ���� ������� �������
			rectIndex.bottom += (sizeSymbol.cy / 2);    // �������� ���� ������ �������
		}
		if(( symbolics[j] == SYMBOL_TYPEFACE ) && (tchars[j] == TCHAR(0x2208)))  // ���� ������ ��������������, �� ������� �������� ���
		{
			rectIndex = rectReal;
			rectIndex.top -= (sizeSymbol.cy / 10);    // �������� ���� ������� �������
			rectIndex.bottom -= (sizeSymbol.cy / 10);    // �������� ���� ������ �������
			dc.DrawText(    // ��������� ���������� �������
				tch,
				1,    
				rectIndex,     
				DT_CENTER|DT_SINGLELINE|DT_VCENTER);
		} 
		else
		dc.DrawText(    // ��������� ���������� �������
			tch,
			( tch[0] == TCHAR(0x26) )? 2 : 1,    // ���� ��������, �� ����������� ���� �������� (������ ��������� � ������ �� ������������
			indexing ? rectIndex : rectReal,     // �������� ������������� ��������� � ����������� �� ����, ������������ ��� ������ ��� ���
			DT_CENTER|DT_SINGLELINE|DT_VCENTER);
		rectReal.left += sizeSymbol.cx;	// ��������� ����� ���������� ��� ����������� ���������� �����
	
		if ( pOldFont != NULL )    // ��������������� �������������� ����, �������� ��� ��������
		{
			dc.SelectObject(pOldFont);
			pOldFont = NULL;
		}
		if(indexing)    // ���� ��� ��������� ������
			indexing = 0;    // ������ ���� �������������
		
	}
}