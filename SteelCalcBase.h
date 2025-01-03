///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/grid.h>
#include <wx/choice.h>
#include <wx/gbsizer.h>
#include <wx/textctrl.h>
#include <wx/scrolwin.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class Main
///////////////////////////////////////////////////////////////////////////////
class Main : public wxFrame
{
	private:

	protected:
		enum
		{
			wxID_MENU_FILE_ABOUT = 6000,
			wxID_MENU_FILE_OPTIONS,
			wxID_MENU_FILE_EXIT,
		};

		wxMenuBar* m_menubar;
		wxMenu* m_menuFile;
		wxStatusBar* m_statusBar;
		wxGridBagSizer* m_mainSizer;
		wxScrolledWindow* m_scrolledWindow;
		wxGridBagSizer* m_ScrolledWindowSizer;
		wxGridBagSizer* m_barProcessSizer;
		wxStaticText* m_lblHeaderText;
		wxCheckBox* m_chbCircularInput;
		wxGrid* m_gridLValues;
		wxGridBagSizer* m_InputSizer;
		wxStaticText* m_lblInputSizerHeader;
		wxStaticText* m_lblBarGrade;
		wxChoice* m_specsGandD;
		wxGridBagSizer* m_CalculatedSizer;
		wxStaticText* m_lblCalculatedHeader;
		wxStaticText* m_lblCalculatedTotalBarLength;
		wxStaticText* m_lblCalculatedBarArea;
		wxStaticText* m_lblCalculatedProcessingType;
		wxStaticText* m_lblCalculatedCostPerMg;
		wxStaticText* m_lblWeightPerBar;
		wxGrid* m_gridCircularLValues;
		wxGridBagSizer* m_barCalculatorSizer;
		wxStaticText* m_lblBarCalculator;
		wxStaticText* m_lblBCSpan;
		wxStaticText* m_lblBCBarCentre;
		wxStaticText* m_lblBCTotalQty;
		wxTextCtrl* m_BCSpan;
		wxTextCtrl* m_BCBarCentre;
		wxStaticText* m_BCTotalQty;
		wxGridBagSizer* m_labourCalculatorSizer;
		wxStaticText* m_lblLabourCalculator;
		wxStaticText* m_lblLabourLength;
		wxStaticText* m_lblLabourWidth;
		wxStaticText* m_lblLabourBarCentreA;
		wxStaticText* m_lblLabourBarCentreB;
		wxStaticText* m_lblLabourTieCentre;
		wxStaticText* m_lblLabourTotalQtyTies;
		wxTextCtrl* m_LabourLength;
		wxTextCtrl* m_LabourWidth;
		wxTextCtrl* m_LabourBarCentreA;
		wxTextCtrl* m_LabourBarCentreB;
		wxTextCtrl* m_LabourTieCentre;
		wxStaticText* m_LabourTotalQtyTies;

	public:

		Main( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Steel Calculator"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 920,470 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~Main();

};

///////////////////////////////////////////////////////////////////////////////
/// Class Options
///////////////////////////////////////////////////////////////////////////////
class Options : public wxFrame
{
	private:

	protected:
		wxStaticText* m_lblOptionsLabour;
		wxCheckBox* m_optionsLabourAddPerimeterTies;
		wxCheckBox* m_optionsLabourAddSetupTies;
		wxCheckBox* m_optionsLabourAddLapTies;

	public:

		Options( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 266,135 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~Options();

};

