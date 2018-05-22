#include "main.h"
#include "application.h"

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    Application *app = new Application(wxT("Simple Image Viewer"));
    app->Show(true);

    return true;
}
