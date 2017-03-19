
#include "Input.h"

#include <winuser.h>

OC_NS_BG;

MouseState MouseState::m_prevState;
KeyboardState KeyboardState::m_prevState;
BYTE KeyboardState::m_currState[256];

MouseState MouseState::GetMouseState(HWND hwnd)
{
    POINT pos;
    if (!GetCursorPos(&pos))
    {
        OC_LOG_ERROR("Failed to get cursor position, GetCursorPos returned: " << GetLastError());
    }

    if (hwnd != NULL && !ScreenToClient(hwnd, &pos))
    {
        OC_LOG_ERROR("Failed to convert cursor position, ScreenToClient returned: " << GetLastError());
    }

    MouseState newState;
    newState.X = pos.x;
    newState.Y = pos.y;
    newState.DX = pos.x - m_prevState.X;
    newState.DY = pos.y - m_prevState.Y;

    newState.LButton.IsPressed = (GetKeyState(VK_LBUTTON) & 0x8000) > 0;
    newState.LButton.IsRisingEdge = newState.LButton.IsPressed && !m_prevState.LButton.IsPressed;
    newState.LButton.IsRisingEdge = !newState.LButton.IsPressed && m_prevState.LButton.IsPressed;

    newState.MButton.IsPressed = (GetKeyState(VK_MBUTTON) & 0x8000) > 0;
    newState.MButton.IsRisingEdge = newState.MButton.IsPressed && !m_prevState.MButton.IsPressed;
    newState.MButton.IsRisingEdge = !newState.MButton.IsPressed && m_prevState.MButton.IsPressed;

    newState.RButton.IsPressed = (GetKeyState(VK_RBUTTON) & 0x8000) > 0;
    newState.RButton.IsRisingEdge = newState.RButton.IsPressed && !m_prevState.RButton.IsPressed;
    newState.RButton.IsRisingEdge = !newState.RButton.IsPressed && m_prevState.RButton.IsPressed;

    if (hwnd != NULL)
    {
        RECT clientRect;
        if (!::GetClientRect(hwnd, &clientRect))
        {
            OC_LOG_ERROR("Failed to get client rect, GetClientRect returned: " << GetLastError());
        }
        newState.IsOverWindow = (pos.x >= 0 && pos.x < clientRect.right
            && pos.y >= 0 && pos.y < clientRect.bottom);
    }
    else
    {
        newState.IsOverWindow = false;
    }

    m_prevState = newState;
    return m_prevState;
}

void MouseState::SetCursorPos(int x, int y, HWND hwnd)
{
    POINT pos;
    pos.x = x;
    pos.y = y;

    if (hwnd != NULL && !ClientToScreen(hwnd, &pos))
    {
        OC_LOG_ERROR("Failed to convert cursor position, ClientToScreen returned: " << GetLastError());
        return;
    }

    if (!::SetCursorPos(pos.x, pos.y))
    {
        OC_LOG_ERROR("Failed to set cursor position, SetCursorPos returned: " << GetLastError());
        return;
    }
}

KeyState KeyboardState::GetKeyState(Key key) const
{
    return m_keyStates[static_cast<uint32>(key)];
}

bool KeyboardState::IsKeyDown(Key key) const
{
    return m_keyStates[static_cast<uint32>(key)].IsPressed;
}

bool KeyboardState::RisingEdge(Key key) const
{
    return m_keyStates[static_cast<uint32>(key)].IsRisingEdge;
}

KeyboardState KeyboardState::GetKeyboardState(HWND hwnd)
{
    if (GetForegroundWindow() != hwnd)
        return m_prevState;

    ::GetKeyboardState(m_currState);

    KeyState state;
    for (UINT i = 0; i < 256; ++i)
    {
        state.IsPressed = IsKeyPressed(m_currState[i]);
        state.IsRisingEdge = state.IsPressed && !m_prevState.m_keyStates[i].IsPressed;
        state.IsFallingEdge = !state.IsPressed && m_prevState.m_keyStates[i].IsPressed;
        m_prevState.m_keyStates[i] = state;
    }

    return m_prevState;
}

OC_NS_END;