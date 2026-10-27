/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2015 hanxi
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CCEditBoxImplLinux.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

#include "CCEditBox.h"
#include "support/ccUTF8.h"

NS_CC_EXT_BEGIN

CCEditBoxImplLinux::CCEditBoxImplLinux(CCEditBox *pEditText)
	: CCEditBoxImpl(pEditText), m_pLabel(NULL), m_pLabelPlaceHolder(NULL), m_colText(ccWHITE), m_colPlaceHolder(ccGRAY)
{
}

CCEditBoxImplLinux::~CCEditBoxImplLinux()
{
}

bool CCEditBoxImplLinux::initWithSize(const CCSize &size)
{
	//! int fontSize = getFontSizeAccordingHeightJni(size.height-12);
	m_pLabel = CCLabelTTF::create("", "", size.height - 12);
	// align the text vertically center
	m_pLabel->setAnchorPoint(ccp(0, 0.5f));
	m_pLabel->setPosition(ccp(5, size.height / 2.0f));
	m_pLabel->setColor(m_colText);
	m_pEditBox->addChild(m_pLabel);

	m_pLabelPlaceHolder = CCLabelTTF::create("", "", size.height - 12);
	// align the text vertically center
	m_pLabelPlaceHolder->setAnchorPoint(ccp(0, 0.5f));
	m_pLabelPlaceHolder->setPosition(ccp(5, size.height / 2.0f));
	m_pLabelPlaceHolder->setVisible(false);
	m_pLabelPlaceHolder->setColor(m_colPlaceHolder);
	m_pEditBox->addChild(m_pLabelPlaceHolder);

	return true;
}

void CCEditBoxImplLinux::setFont(const char *pFontName, int fontSize)
{
	if (m_pLabel != NULL)
	{
		m_pLabel->setFontName(pFontName);
		m_pLabel->setFontSize(fontSize);
	}

	if (m_pLabelPlaceHolder != NULL)
	{
		m_pLabelPlaceHolder->setFontName(pFontName);
		m_pLabelPlaceHolder->setFontSize(fontSize);
	}
}

void CCEditBoxImplLinux::setFontColor(const ccColor3B &color)
{
	m_colText = color;
	m_pLabel->setColor(color);
}

void CCEditBoxImplLinux::setPlaceholderFont(const char *pFontName, int fontSize)
{
	if (m_pLabelPlaceHolder != NULL)
	{
		m_pLabelPlaceHolder->setFontName(pFontName);
		m_pLabelPlaceHolder->setFontSize(fontSize);
	}
}

void CCEditBoxImplLinux::setPlaceholderFontColor(const ccColor3B &color)
{
	m_colPlaceHolder = color;
	m_pLabelPlaceHolder->setColor(color);
}

void CCEditBoxImplLinux::setText(const char *pText)
{
	if (pText != NULL)
	{
		m_strText = pText;

		if (m_strText.length() > 0)
		{
			m_pLabelPlaceHolder->setVisible(false);

			std::string strToShow;

			if (kEditBoxInputFlagPassword == m_eEditBoxInputFlag)
			{
				long length = cc_utf8_strlen(m_strText.c_str());
				for (long i = 0; i < length; i++)
				{
					strToShow.append("*");
				}
			}
			else
			{
				strToShow = m_strText;
			}

			//! std::string strWithEllipsis = getStringWithEllipsisJni(strToShow.c_str(), m_EditSize.width, m_EditSize.height-12);
			//! m_pLabel->setString(strWithEllipsis.c_str());
			m_pLabel->setString(strToShow.c_str());
		}
		else
		{
			m_pLabelPlaceHolder->setVisible(true);
			m_pLabel->setString("");
		}
	}
}

const char *CCEditBoxImplLinux::getText(void)
{
	return m_strText.c_str();
}

void CCEditBoxImplLinux::setInputMode(EditBoxInputMode inputMode)
{
	m_eEditBoxInputMode = inputMode;
}

void CCEditBoxImplLinux::setInputFlag(EditBoxInputFlag inputFlag)
{
	m_eEditBoxInputFlag = inputFlag;
}

void CCEditBoxImplLinux::setReturnType(KeyboardReturnType returnType)
{
	m_eKeyboardReturnType = returnType;
}

bool CCEditBoxImplLinux::isEditing()
{
	return false;
}

void CCEditBoxImplLinux::openKeyboard()
{
}

NS_CC_EXT_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) */
