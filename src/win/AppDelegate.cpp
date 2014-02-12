#include "Precompiled.h"
#include "AppDelegate.h"
#include "GameDelegate.h"

AppDelegate::AppDelegate()
{
    m_gameDelegate = new GameDelegate;
}

AppDelegate::~AppDelegate()
{
    delete m_gameDelegate;
}

void AppDelegate::Init()
{
    RECT rectangle;
    GetClientRect(window, &rectangle);
    m_screen = vec2i(rectangle.right - rectangle.left, rectangle.bottom - rectangle.top);
    m_gameDelegate->init(m_screen.x, m_screen.y);

    m_initialized = true;
}

void AppDelegate::Update(float dt)
{
    if (!m_initialized)
    {
        return;
    }
    dt = min(dt, 34);
    m_gameDelegate->update(dt);
}

void AppDelegate::Render()
{
    if (!m_initialized)
    {
        return;
    }
    m_gameDelegate->render();
    eglSwapBuffers(display, surface);
}


void AppDelegate::onTouchPressed(int x, int y)
{
	m_gameDelegate->onTouchPressed(x, m_screen.y - y);
}

void AppDelegate::onTouchMoved(int x, int y)
{
    if (x < 0 || y < 0 || x > m_screen.x || y > m_screen.y)
    {
		m_gameDelegate->onTouchReleased(x, m_screen.y - y, x, m_screen.y - y);
    }
    else
	{
		m_gameDelegate->onTouchMoved(x, m_screen.y - y, x, m_screen.y - y);
    }
}

void AppDelegate::onTouchReleased(int x, int y)
{
	m_gameDelegate->onTouchReleased(x, m_screen.y - y, x, m_screen.y - y);
}

void AppDelegate::ApplicationWillTerminate()
{
    m_gameDelegate->applicationWillTerminate();
}

void AppDelegate::OnSuspend()
{
    m_gameDelegate->onSuspend();
}

void AppDelegate::OnResume()
{
    m_gameDelegate->onResume();
}
