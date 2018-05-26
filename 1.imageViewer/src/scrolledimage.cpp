#include "scrolledimage.h"
#include <math.h>

ScrolledImage::ScrolledImage(wxPanel *parent) : wxScrolled<wxPanel>(parent, -1)
{
    wxBoxSizer *panelSizer = new wxBoxSizer(wxVERTICAL);

    m_imgPlaceholder =
        new wxStaticBitmap(this, -1, wxNullBitmap, wxDefaultPosition, wxSize(-1, -1));

    // TODO: remove this, currently loads image on start up for testing purposes
    wxBitmap m_bmp = wxBitmap(wxT("testImage.png"), wxBITMAP_TYPE_ANY);
    m_imgPlaceholder->SetBitmap(m_bmp);

    panelSizer->Add(m_imgPlaceholder, 1);
    this->SetSizer(panelSizer);

    // display scrollbars
    this->FitInside();

    // set scroll pixels per unit
    this->SetScrollRate(10, 10);
    m_pxPerUnit = {10, 10};

    // -------------------------------------------------------------------------------------------
    // Event handlers
    // -------------------------------------------------------------------------------------------

    // mouse click is only captured if the user clicked on the image container
    m_imgPlaceholder->Bind(wxEVT_LEFT_DOWN, &ScrolledImage::mouseClick, this);

    // mouse click should be released even if the user clicked outside of the application window
    this->Bind(wxEVT_LEFT_UP, &ScrolledImage::mouseRelease, this);
    parent->Bind(wxEVT_LEFT_UP, &ScrolledImage::mouseRelease, this);
    m_imgPlaceholder->Bind(wxEVT_LEFT_UP, &ScrolledImage::mouseRelease, this);

    // mouse drag over image placeholder
    m_imgPlaceholder->Bind(wxEVT_MOTION, &ScrolledImage::mouseMove, this);

    // mouse cursor goes outside of application window, ensures drag still works
    this->Bind(wxEVT_MOTION, &ScrolledImage::mouseMove, this);

    // capture thumbtrack events
    this->Bind(wxEVT_SCROLLWIN_THUMBRELEASE, &ScrolledImage::thumbtrackScroll, this);
    this->Bind(wxEVT_SCROLLWIN_THUMBTRACK, &ScrolledImage::thumbtrackScroll, this);

    // capture mouse wheel scroll
    this->Bind(wxEVT_MOUSEWHEEL, &ScrolledImage::mouseWheelScroll, this);

    // capture key press event
    this->Bind(wxEVT_KEY_DOWN, &ScrolledImage::keypressScroll, this);
}

void ScrolledImage::setImage(std::shared_ptr<wxBitmap> image)
{
    if (image != nullptr)
    {
        m_imgPlaceholder->SetBitmap(*image);
        // makes the scrollbars visible if the image is larger than its container
        this->SetVirtualSize(image->GetSize());
    }
}

void ScrolledImage::mouseClick(wxMouseEvent &event)
{
    m_mouseDrag = true;
    m_newCursorPos.x = event.GetPosition().x;
    m_newCursorPos.y = event.GetPosition().y;
}

void ScrolledImage::mouseRelease(wxMouseEvent &WXUNUSED(event))
{
    if (!m_mouseDrag)
    {
        return;
    }
    m_mouseDrag = false;
}

void ScrolledImage::mouseMove(wxMouseEvent &event)
{
    if (!m_mouseDrag)
    {
        return;
    }

    wxSize m_oldCursorPos{0, 0};
    // previously set new position is now old position
    m_oldCursorPos.x = m_newCursorPos.x;
    m_oldCursorPos.y = m_newCursorPos.y;

    // current cursor position is now new position
    m_newCursorPos.x = event.GetX();
    m_newCursorPos.y = event.GetY();

    int dX = m_newCursorPos.x - m_oldCursorPos.x;
    int dY = m_newCursorPos.y - m_oldCursorPos.y;

    // move scrollbars of the scroll component
    m_currentScroll.x += dX;
    m_currentScroll.y += dY;

    this->smoothScroll();
}

void ScrolledImage::thumbtrackScroll(wxScrollWinEvent &event)
{
    // moving vertical scrollbar
    if (event.GetOrientation() == wxVERTICAL)
    {
        m_currentScroll.y = event.GetPosition() * m_pxPerUnit.y;
    }
    else
    { // moving horizontal scrollbar
        m_currentScroll.x = event.GetPosition() * m_pxPerUnit.x;
    }

    this->smoothScroll();
}

void ScrolledImage::mouseWheelScroll(wxMouseEvent &event)
{
    if (event.GetWheelAxis() == wxMOUSE_WHEEL_VERTICAL)
    {
        int amount = m_pxPerUnit.y * 3;
        if (event.GetWheelRotation() > 0)
        {
            amount = -amount;
        }
        m_currentScroll.y += amount;
    }
    else
    { // scrolling horizontaly (if horizontal scrollbar is in focus)
        int amount = m_pxPerUnit.x * 3;
        if (event.GetWheelRotation() < 0)
        {
            amount = -amount;
        }
        m_currentScroll.x += amount;
    }

    this->smoothScroll();
}

void ScrolledImage::keypressScroll(wxKeyEvent &event)
{
    switch (event.GetKeyCode())
    {
    case WXK_UP: // moving up
        m_currentScroll.y -= m_pxPerUnit.y;
        break;
    case WXK_DOWN: // moving down
        m_currentScroll.y += m_pxPerUnit.y;
        break;
    case WXK_LEFT: // moving left
        m_currentScroll.x -= m_pxPerUnit.x;
        break;
    case WXK_RIGHT: // moving right
        m_currentScroll.x += m_pxPerUnit.x;
        break;
    }
    this->smoothScroll();
}

void ScrolledImage::smoothScroll()
{
    wxSize imgSize = m_imgPlaceholder->GetBitmap().GetSize();
    // set viewport scroll boundaries
    int maxScrollX = imgSize.GetX() - this->GetClientSize().GetX();
    int maxScrollY = imgSize.GetY() - this->GetClientSize().GetY();

    // ensures we don't scroll past the viewport X scroll boundaries. If we scroll past the
    // boundaries and then try to scroll back again, the image will not move until we get to
    // x < maxScrollX coordinate.
    if (m_currentScroll.x > maxScrollX)
    {
        m_currentScroll.x = maxScrollX;
    }
    else if (m_currentScroll.x < 0)
    {
        m_currentScroll.x = 0;
    }

    // ensures we don't scroll past the viewport Y scroll boundaries
    if (m_currentScroll.y > maxScrollY)
    {
        m_currentScroll.y = maxScrollY;
    }
    else if (m_currentScroll.y < 0)
    {
        m_currentScroll.y = 0;
    }

    // we have to provide scroll coordinates in scroll units
    int newX = static_cast<int>(round(m_currentScroll.x / m_pxPerUnit.x));
    int newY = static_cast<int>(round(m_currentScroll.y / m_pxPerUnit.y));

    this->Scroll(newX, newY);
}
