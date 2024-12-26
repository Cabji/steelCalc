#include "MyApp.h"
#include "SteelCalcMain.h"
#include <wx/wx.h>
#include <wx/image.h>
#include <iostream>
#include <windows.h> // for debugging console output messages

#ifdef __WXMSW__
#include <windows.h> // Required for AttachConsole
#endif

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    // Allocate a console for debugging output
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    std::cout << "Console allocated for debugging output." << std::endl;
    // data initialization
    SteelCalcMain *frame = new SteelCalcMain(nullptr, wxID_ANY, "Steel Calculator", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE);
    frame->Show(true);
    return true;
}