#ifndef _CFONT_H_
#define _CFONT_H_

#pragma warning(disable: 4267)  /**< 禁止编译器出现类型转换的警告 */
#pragma warning(disable: 4244)

#include <Windows.h>

class CFont{
public:

	// constructor
	CFont();
	~CFont();

	// method
	bool InitFont();	// initial the font
	void PrintText(char *string, float x, float y);	// print in the screen(x,y)

protected:
	HFONT m_hFont; 	// the handle of font
};
#endif	//_CFONT_H_