/*
 * CCEGLViewlinux.cpp
 *
 *  Created on: Aug 8, 2011
 *      Author: laschweinski
 */
#include "CCEGLView.h"
#include "CCGL.h"
#include "glfw3.h"
#include "ccMacros.h"
#include "CCDirector.h"
#include "platform/CCImage.h"
#include "touch_dispatcher/CCTouch.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "text_input_node/CCIMEDispatcher.h"

PFNGLGENFRAMEBUFFERSEXTPROC glGenFramebuffersEXT = NULL;
PFNGLDELETEFRAMEBUFFERSEXTPROC glDeleteFramebuffersEXT = NULL;
PFNGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT = NULL;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2DEXT = NULL;
PFNGLGENERATEMIPMAPEXTPROC glGenerateMipmapEXT = NULL;

PFNGLGENBUFFERSARBPROC glGenBuffersARB = NULL;
PFNGLBINDBUFFERARBPROC glBindBufferARB = NULL;
PFNGLBUFFERDATAARBPROC glBufferDataARB = NULL;
PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB = NULL;
PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB = NULL;

bool initExtensions()
{
#define LOAD_EXTENSION_FUNCTION(TYPE, FN) FN = (TYPE)glfwGetProcAddress(#FN);
	bool bRet = false;
	do
	{

		//		char* p = (char*) glGetString(GL_EXTENSIONS);
		//		printf(p);

		/* Supports frame buffer? */
		if (glfwExtensionSupported("GL_EXT_framebuffer_object") != GL_FALSE)
		{

			/* Loads frame buffer extension functions */
			LOAD_EXTENSION_FUNCTION(PFNGLGENERATEMIPMAPEXTPROC,
									glGenerateMipmapEXT);
			LOAD_EXTENSION_FUNCTION(PFNGLGENFRAMEBUFFERSEXTPROC,
									glGenFramebuffersEXT);
			LOAD_EXTENSION_FUNCTION(PFNGLDELETEFRAMEBUFFERSEXTPROC,
									glDeleteFramebuffersEXT);
			LOAD_EXTENSION_FUNCTION(PFNGLBINDFRAMEBUFFEREXTPROC,
									glBindFramebufferEXT);
			LOAD_EXTENSION_FUNCTION(PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC,
									glCheckFramebufferStatusEXT);
			LOAD_EXTENSION_FUNCTION(PFNGLFRAMEBUFFERTEXTURE2DEXTPROC,
									glFramebufferTexture2DEXT);
		}
		else
		{
			break;
		}

		if (glfwExtensionSupported("GL_ARB_vertex_buffer_object") != GL_FALSE)
		{
			LOAD_EXTENSION_FUNCTION(PFNGLGENBUFFERSARBPROC, glGenBuffersARB);
			LOAD_EXTENSION_FUNCTION(PFNGLBINDBUFFERARBPROC, glBindBufferARB);
			LOAD_EXTENSION_FUNCTION(PFNGLBUFFERDATAARBPROC, glBufferDataARB);
			LOAD_EXTENSION_FUNCTION(PFNGLBUFFERSUBDATAARBPROC,
									glBufferSubDataARB);
			LOAD_EXTENSION_FUNCTION(PFNGLDELETEBUFFERSARBPROC,
									glDeleteBuffersARB);
		}
		else
		{
			break;
		}
		bRet = true;
	} while (0);
	return bRet;
}

NS_CC_BEGIN

CCEGLView::CCEGLView()
	: bIsInit(false), m_fFrameZoomFactor(1.0f)
{
}

CCEGLView::~CCEGLView()
{
}

void error_callback(int error, const char *description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void keyEventHandle(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (scancode == GLFW_RELEASE)
	{
		return;
	}

	if (key == GLFW_KEY_DELETE)
	{
		CCIMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
	}
	else if (key == GLFW_KEY_ENTER)
	{
		CCIMEDispatcher::sharedDispatcher()->dispatchInsertText("\n", 1);
	}
	else if (key == GLFW_KEY_TAB)
	{
	}
}

void charEventHandle(GLFWwindow *window, unsigned int iChar)
{
	// ascii char
	CCIMEDispatcher::sharedDispatcher()->dispatchInsertText((const char *)&iChar, 1);
}

void mouseButtonEventHandle(GLFWwindow *m_window, int button, int action, int /*modify*/)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		CCEGLView *pEGLView = CCEGLView::sharedOpenGLView();
		//get current mouse pos
		double x, y;
		glfwGetCursorPos(m_window, &x, &y);
		CCPoint oPoint((float)x, (float)y);
		/*
		if (!CCRect::CCRectContainsPoint(s_pMainWindow->m_rcViewPort,oPoint))
		{
			CCLOG("not in the viewport");
			return;
		}
		*/
		oPoint.x /= pEGLView->m_fFrameZoomFactor;
		oPoint.y /= pEGLView->m_fFrameZoomFactor;
		int id = 0;
		if (action == GLFW_PRESS)
		{
			pEGLView->handleTouchesBegin(1, &id, &oPoint.x, &oPoint.y);
		}
		else if (action == GLFW_RELEASE)
		{
			pEGLView->handleTouchesEnd(1, &id, &oPoint.x, &oPoint.y);
		}
	}
}

void mousePosEventHandle(GLFWwindow *window, double iPosX, double iPosY)
{
	int iButtonState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

	//to test move
	if (iButtonState == GLFW_PRESS)
	{
		CCEGLView *pEGLView = CCEGLView::sharedOpenGLView();
		int id = 0;
		float x = (float)iPosX;
		float y = (float)iPosY;
		x /= pEGLView->m_fFrameZoomFactor;
		y /= pEGLView->m_fFrameZoomFactor;
		pEGLView->handleTouchesMove(1, &id, &x, &y);
	}
}

void closeEventHandle(GLFWwindow *window)
{
	CCDirector::sharedDirector()->end();
}

void CCEGLView::setTitle(const char *title)
{
	glfwSetWindowTitle(m_window, title);
}

void CCEGLView::setIcon(const char *path)
{
	CCImage *icon = new (std::nothrow) CCImage();
	if (icon && icon->initWithImageFile(path))
	{
	}
	else
	{
		CC_SAFE_DELETE(icon);
	}

	if (!icon)
		return; // No valid images
	GLFWimage *image = new GLFWimage();
	image->width = icon->getWidth();
	image->height = icon->getHeight();
	image->pixels = icon->getData();

	glfwSetWindowIcon(m_window, 1, image);

	CC_SAFE_DELETE(image);
	CC_SAFE_DELETE(icon);
}

void CCEGLView::setFrameSize(float width, float height)
{
	//check
	CCAssert(width != 0 && height != 0, "invalid window's size equal 0");

	//Inits GLFW
	if (!glfwInit())
	{
		CCAssert(0, "fail to init the glfw");
	}

	/* Updates window hint */
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// _monitor = glfwGetPrimaryMonitor();
	// if (nullptr == _monitor)
	// {
	// 	CCAssert(0, "fail to get the glfw monitor");
	// 	return;
	// }

	// const GLFWvidmode *videoMode = glfwGetVideoMode(_monitor);
	// glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);
	// glfwWindowHint(GLFW_RED_BITS, videoMode->redBits);
	// glfwWindowHint(GLFW_BLUE_BITS, videoMode->blueBits);
	// glfwWindowHint(GLFW_GREEN_BITS, videoMode->greenBits);

	/* Create glfw window */
	// m_window = glfwCreateWindow(width, height, "", _monitor, NULL);
	m_window = glfwCreateWindow(width, height, "", NULL, NULL);

	// Set center windwo
	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	if (nullptr == monitor)
		return;

	const GLFWvidmode *mode = glfwGetVideoMode(monitor);
	if (!mode)
		return;

	int monitorX, monitorY;
	glfwGetMonitorPos(monitor, &monitorX, &monitorY);

	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);

	glfwSetWindowPos(m_window,
					 monitorX + (mode->width - windowWidth) / 2,
					 monitorY + (mode->height - windowHeight) * 0.35f);

	/* Success? */
	if (m_window)
	{
		/* Updates its title */
		// glfwSetWindowTitle("Cocos2dx-Linux");

		//set the init flag
		bIsInit = true;

		glfwMakeContextCurrent(m_window);

		glfwSetErrorCallback(error_callback);

		//register the glfw key event
		glfwSetKeyCallback(m_window, keyEventHandle);
		//register the glfw char event
		glfwSetCharCallback(m_window, charEventHandle);
		//register the glfw mouse event
		glfwSetMouseButtonCallback(m_window, mouseButtonEventHandle);
		//register the glfw mouse pos event
		glfwSetCursorPosCallback(m_window, mousePosEventHandle);

		glfwSetWindowCloseCallback(m_window, closeEventHandle);

		CCEGLViewProtocol::setFrameSize(width, height);

		initGL();
	}
}

void CCEGLView::setFrameZoomFactor(float fZoomFactor)
{
	m_fFrameZoomFactor = fZoomFactor;
	glfwSetWindowSize(m_window, m_obScreenSize.width * fZoomFactor, m_obScreenSize.height * fZoomFactor);
	CCDirector::sharedDirector()->setProjection(CCDirector::sharedDirector()->getProjection());
}

float CCEGLView::getFrameZoomFactor()
{
	return m_fFrameZoomFactor;
}

void CCEGLView::setViewPortInPoints(float x, float y, float w, float h)
{
	glViewport((GLint)(x * m_fScaleX * m_fFrameZoomFactor + m_obViewPortRect.origin.x * m_fFrameZoomFactor),
			   (GLint)(y * m_fScaleY * m_fFrameZoomFactor + m_obViewPortRect.origin.y * m_fFrameZoomFactor),
			   (GLsizei)(w * m_fScaleX * m_fFrameZoomFactor),
			   (GLsizei)(h * m_fScaleY * m_fFrameZoomFactor));
}

void CCEGLView::setScissorInPoints(float x, float y, float w, float h)
{
	glScissor((GLint)(x * m_fScaleX * m_fFrameZoomFactor + m_obViewPortRect.origin.x * m_fFrameZoomFactor),
			  (GLint)(y * m_fScaleY * m_fFrameZoomFactor + m_obViewPortRect.origin.y * m_fFrameZoomFactor),
			  (GLsizei)(w * m_fScaleX * m_fFrameZoomFactor),
			  (GLsizei)(h * m_fScaleY * m_fFrameZoomFactor));
}

bool CCEGLView::isOpenGLReady()
{
	return bIsInit;
}

void CCEGLView::end()
{
	/* Exits from GLFW */
	glfwTerminate();
	delete this;
	exit(0);
}

void CCEGLView::swapBuffers()
{
	if (bIsInit)
	{
		/* Swap buffers */
		glfwSwapBuffers(m_window);
	}
}

void CCEGLView::setIMEKeyboardState(bool bOpen)
{
}

bool CCEGLView::initGL()
{
	// check OpenGL version at first
	const GLubyte *glVersion = glGetString(GL_VERSION);

	if (atof((const char *)glVersion) < 1.5)
	{
		char strComplain[256] = {0};
		sprintf(strComplain,
				"OpenGL 1.5 or higher is required (your version is %s). Please upgrade the driver of your video card.",
				glVersion);
		CCMessageBox(strComplain, "OpenGL version too old");
		return false;
	}

#if (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
	GLenum GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		CCMessageBox((char *)glewGetErrorString(GlewInitResult), "OpenGL error");
		return false;
	}

	if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
	{
		CCLOG("Ready for GLSL");
	}
	else
	{
		CCLOG("Not totally ready :(");
	}

	if (glewIsSupported("GL_VERSION_2_0"))
	{
		CCLOG("Ready for OpenGL 2.0");
	}
	else
	{
		CCLOG("OpenGL 2.0 not supported");
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (glew_dynamic_binding() == false)
	{
		ccMessageBox("No OpenGL framebuffer support. Please upgrade the driver of your video card.", "OpenGL error");
		return false;
	}
#endif
#endif

	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

	return true;
}

void CCEGLView::destroyGL()
{
	glfwDestroyWindow(m_window);
}

void CCEGLView::updateFrameSize(float width, float height)
{
	m_obScreenSize = CCSize(width, height);

	if (m_obDesignResolutionSize.equals(CCSizeZero))
		m_obDesignResolutionSize = m_obScreenSize;
}

CCEGLView *CCEGLView::sharedOpenGLView()
{
	static CCEGLView *s_pEglView = NULL;
	if (s_pEglView == NULL)
	{
		s_pEglView = new CCEGLView();
	}
	return s_pEglView;
}

NS_CC_END
