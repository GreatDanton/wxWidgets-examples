#include "scrolledimage.h"
#include <math.h>

ScrolledImage::ScrolledImage(wxPanel *parent) : wxScrolled<wxPanel>(parent, -1)
{
    wxBoxSizer *panelSizer = new wxBoxSizer(wxVERTICAL);

    m_imgPlaceholder =
        new wxStaticBitmap(this, -1, wxNullBitmap, wxDefaultPosition, wxSize(-1, -1));

    // TODO: remove this, currently loads image on start up for testing purposes
    // wxBitmap m_bmp = wxBitmap(wxT("testImage.png"), wxBITMAP_TYPE_ANY);
    // m_imgPlaceholder->SetBitmap(m_bmp);

    // placeholder should be able to grow
    panelSizer->Add(m_imgPlaceholder, 1);

    this->SetSizer(panelSizer);
    // display scrollbars
    this->FitInside();
    this->SetScrollRate(10, 10);

    // mouse click is only captured if the user clicked on the image
    m_imgPlaceholder->Bind(wxEVT_LEFT_DOWN, &ScrolledImage::mouseClick, this);
    // mouse click is released even if the user clicked outside of the application window
    this->Bind(wxEVT_LEFT_UP, &ScrolledImage::mouseRelease, this);
    parent->Bind(wxEVT_LEFT_UP, &ScrolledImage::mouseRelease, this);
    m_imgPlaceholder->Bind(wxEVT_LEFT_UP, &ScrolledImage::mouseRelease, this);

    ///////////////////////////
    // DRAG EVENT LISTENERS
    ////////////////////////////
    // over image placeholder
    m_imgPlaceholder->Bind(wxEVT_MOTION, &ScrolledImage::mouseMove, this);
    // drag should work when mouse cursor goes outside application window
    this->Bind(wxEVT_MOTION, &ScrolledImage::mouseMove, this);
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

void ScrolledImage::mouseRelease(wxMouseEvent &event)
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
    // previously new position is now old position
    m_oldCursorPos.x = m_newCursorPos.x;
    m_oldCursorPos.y = m_newCursorPos.y;

    // current cursor position is now new position
    m_newCursorPos.x = event.GetPosition().x;
    m_newCursorPos.y = event.GetPosition().y;

    int dX = m_newCursorPos.x - m_oldCursorPos.x;
    int dY = m_newCursorPos.y - m_oldCursorPos.y;

    int newX = round((m_oldCursorPos.x + dX) / 10.0);
    int newY = round((m_oldCursorPos.y + dY) / 10.0);

    this->Scroll(newX, newY);
}
