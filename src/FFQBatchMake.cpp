/*************************************************************************
*                                                                        *
*  Copyright (c) 2014 Torben Bruchhaus                                   *
*  http://ffqueue.bruchhaus.dk/                                          *
*  File: FFQBatchMake.cpp                                                *
*                                                                        *
*  This file is part of FFQueue.                                         *
*                                                                        *
*  FFQueue is free software: you can redistribute it and/or modify       *
*  it under the terms of the GNU General Public License as published by  *
*  the Free Software Foundation, either version 3 of the License, or     *
*  (at your option) any later version.                                   *
*                                                                        *
*  FFQueue is distributed in the hope that it will be useful,            *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*  GNU General Public License for more details.                          *
*                                                                        *
*  You should have received a copy of the GNU General Public License     *
*  along with FFQueue.  If not, see <http://www.gnu.org/licenses/>.      *
*                                                                        *
*************************************************************************/

#include "FFQBatchMake.h"
#include "FFQPresetMgr.h"
#include "utils/FFQLang.h"
#include "FFQMain.h"
#include "utils/FFQConsole.h"
#include "utils/FFQProcess.h"
#include "utils/FFQConfig.h"
#include "utils/FFQBuildCmd.h"
#include "utils/FFQMisc.h"
#include "utils/FFQConst.h"

#include <wx/filename.h>
#include <wx/dir.h>

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(FFQBatchMake)
	#include <wx/string.h>
	//*)
#endif
//(*InternalHeaders(FFQBatchMake)
#include <wx/font.h>
//*)

//(*IdInit(FFQBatchMake)
const long FFQBatchMake::ID_JOBINFO = wxNewId();
const long FFQBatchMake::ID_ST1 = wxNewId();
const long FFQBatchMake::ID_INCLUDEVIDEO = wxNewId();
const long FFQBatchMake::ID_INCLUDEAUDIO = wxNewId();
const long FFQBatchMake::ID_INCLUDESUBS = wxNewId();
const long FFQBatchMake::ID_ST2 = wxNewId();
const long FFQBatchMake::ID_PREFAUDIO = wxNewId();
const long FFQBatchMake::ID_ST3 = wxNewId();
const long FFQBatchMake::ID_OUTPUTFORMAT = wxNewId();
const long FFQBatchMake::ID_ST4 = wxNewId();
const long FFQBatchMake::ID_OUTPUTPATH = wxNewId();
const long FFQBatchMake::ID_BROWSEBUTTON = wxNewId();
const long FFQBatchMake::ID_ST5 = wxNewId();
const long FFQBatchMake::ID_PRESET = wxNewId();
const long FFQBatchMake::ID_MAKEBUTTON = wxNewId();
const long FFQBatchMake::ID_CANCELBUTTON = wxNewId();
const long FFQBatchMake::ID_GAUGE = wxNewId();
//*)

BEGIN_EVENT_TABLE(FFQBatchMake,wxDialog)
	//(*EventTable(FFQBatchMake)
	//*)
END_EVENT_TABLE()

//---------------------------------------------------------------------------------------

const wxString PATH_TOKEN = "\"*?*\""; //Just something that is forbidden in paths

//---------------------------------------------------------------------------------------

FFQBatchMake::FFQBatchMake(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(FFQBatchMake)
	wxStaticBoxSizer* SBS1;
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer6;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	MainSizer = new wxFlexGridSizer(4, 1, 0, 0);
	FlexGridSizer2 = new wxFlexGridSizer(1, 1, 0, 0);
	FlexGridSizer2->AddGrowableCol(0);
	FlexGridSizer2->AddGrowableRow(0);
	JobInfo = new wxStaticText(this, ID_JOBINFO, _T("L"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_JOBINFO"));
	wxFont JobInfoFont(12,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	JobInfo->SetFont(JobInfoFont);
	FlexGridSizer2->Add(JobInfo, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	MainSizer->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SBS1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Props"));
	FlexGridSizer3 = new wxFlexGridSizer(5, 1, 0, 0);
	FlexGridSizer3->AddGrowableCol(0);
	FlexGridSizer4 = new wxFlexGridSizer(1, 4, 0, 0);
	FlexGridSizer4->AddGrowableCol(1);
	FlexGridSizer4->AddGrowableCol(2);
	FlexGridSizer4->AddGrowableCol(3);
	ST1 = new wxStaticText(this, ID_ST1, _T("SelC:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_ST1"));
	ST1->SetLabel(FFQS(SID_BATCHMAKE_SEL_CONTENT));
	SBS1->GetStaticBox()->SetLabel(FFQS(SID_BATCHMAKE_DEFINE_PROPERTIES));
	FlexGridSizer4->Add(ST1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	IncludeVideo = new wxCheckBox(this, ID_INCLUDEVIDEO, _T("V"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_INCLUDEVIDEO"));
	IncludeVideo->SetValue(false);
	IncludeVideo->SetLabel(FFQS(SID_COMMON_VIDEO));
	FlexGridSizer4->Add(IncludeVideo, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 0);
	IncludeAudio = new wxCheckBox(this, ID_INCLUDEAUDIO, _T("A"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_INCLUDEAUDIO"));
	IncludeAudio->SetValue(false);
	IncludeAudio->SetLabel(FFQS(SID_COMMON_AUDIO));
	FlexGridSizer4->Add(IncludeAudio, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 0);
	IncludeSubs = new wxCheckBox(this, ID_INCLUDESUBS, _T("S"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_INCLUDESUBS"));
	IncludeSubs->SetValue(false);
	IncludeSubs->SetLabel(FFQS(SID_COMMON_SUBTITLES));
	FlexGridSizer4->Add(IncludeSubs, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer3->Add(FlexGridSizer4, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 3);
	FlexGridSizer1 = new wxFlexGridSizer(1, 2, 0, 0);
	FlexGridSizer1->AddGrowableCol(1);
	ST2 = new wxStaticText(this, ID_ST2, _T("PrefA"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_ST2"));
	ST2->SetLabel(FFQS(SID_BATCHMAKE_PREF_AUDIO_CODEC));
	FlexGridSizer1->Add(ST2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	PrefAudio = new wxComboBox(this, ID_PREFAUDIO, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_PREFAUDIO"));
	PrefAudio->SetSelection( PrefAudio->Append(_T("ac3")) );
	PrefAudio->Append(_T("aac"));
	PrefAudio->Append(_T("eac3"));
	PrefAudio->Append(_T("mp2"));
	PrefAudio->Append(_T("mp3"));
	FlexGridSizer1->Add(PrefAudio, 1, wxALL|wxEXPAND|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer3->Add(FlexGridSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	FlexGridSizer5 = new wxFlexGridSizer(1, 2, 0, 0);
	FlexGridSizer5->AddGrowableCol(1);
	ST3 = new wxStaticText(this, ID_ST3, _T("DestFmt"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_ST3"));
	ST3->SetLabel(FFQS(SID_BATCHMAKE_DEST_FORMAT));
	FlexGridSizer5->Add(ST3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	OutputFormat = new wxComboBox(this, ID_OUTPUTFORMAT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_OUTPUTFORMAT"));
	OutputFormat->SetSelection( OutputFormat->Append(_T("mp4")) );
	OutputFormat->Append(_T("mkv"));
	OutputFormat->Append(_T("m4v"));
	OutputFormat->Append(_T("avi"));
	OutputFormat->Append(_T("mpg"));
	OutputFormat->Append(_T("flv"));
	OutputFormat->Append(_T("mp3"));
	OutputFormat->Append(_T("flac"));
	OutputFormat->Append(_T("wav"));
	FlexGridSizer5->Add(OutputFormat, 1, wxALL|wxEXPAND|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer3->Add(FlexGridSizer5, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 3);
	FlexGridSizer7 = new wxFlexGridSizer(1, 3, 0, 0);
	FlexGridSizer7->AddGrowableCol(1);
	ST4 = new wxStaticText(this, ID_ST4, _T("DestFo"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_ST4"));
	ST4->SetLabel(FFQS(SID_COMMON_DEST_FOLDER));
	FlexGridSizer7->Add(ST4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	OutputPath = new wxTextCtrl(this, ID_OUTPUTPATH, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_OUTPUTPATH"));
	FlexGridSizer7->Add(OutputPath, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BrowseButton = new wxButton(this, ID_BROWSEBUTTON, _T("..."), wxDefaultPosition, wxSize(50,-1), 0, wxDefaultValidator, _T("ID_BROWSEBUTTON"));
	FlexGridSizer7->Add(BrowseButton, 1, wxLEFT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(FlexGridSizer7, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	FlexGridSizer6 = new wxFlexGridSizer(1, 2, 0, 0);
	FlexGridSizer6->AddGrowableCol(1);
	ST5 = new wxStaticText(this, ID_ST5, _T("SelP"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_ST5"));
	ST5->SetLabel(FFQS(SID_BATCHMAKE_SELECT_PRESET));
	FlexGridSizer6->Add(ST5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	Preset = new FFQPresetPanel(this);
	FlexGridSizer6->Add(Preset, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer3->Add(FlexGridSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	SBS1->Add(FlexGridSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	MainSizer->Add(SBS1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	MakeButton = new wxButton(this, ID_MAKEBUTTON, _T("M"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_MAKEBUTTON"));
	MakeButton->SetDefault();
	MakeButton->SetLabel(FFQS(SID_BATCHMAKE_MAKE_JOBS));
	BoxSizer1->Add(MakeButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CancelButton = new wxButton(this, ID_CANCELBUTTON, _T("C"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CANCELBUTTON"));
	CancelButton->SetLabel(FFQS(SID_COMMON_CANCEL));
	BoxSizer1->Add(CancelButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	MainSizer->Add(BoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Gauge = new wxGauge(this, ID_GAUGE, 1000, wxDefaultPosition, wxSize(450,15), 0, wxDefaultValidator, _T("ID_GAUGE"));
	MainSizer->Add(Gauge, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(MainSizer);
	DestPathDlg = new wxDirDialog(this, _T("Select destination folder"), wxEmptyString, wxDD_DEFAULT_STYLE|wxDD_DIR_MUST_EXIST, wxDefaultPosition, wxDefaultSize, _T("wxDirDialog"));
	MainSizer->Fit(this);
	MainSizer->SetSizeHints(this);

	Connect(ID_BROWSEBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FFQBatchMake::OnAction);
	Connect(ID_MAKEBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FFQBatchMake::OnAction);
	Connect(ID_CANCELBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FFQBatchMake::OnAction);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&FFQBatchMake::OnClose);
	//*)

	Connect(wxID_ANY, wxEVT_IDLE, (wxObjectEventFunction)&FFQBatchMake::OnIdle);
	//wxSize cs = Gauge->GetSize();
	//cs.x -= 20; //My bad
	//JobInfo->SetMaxSize(cs);

	//wxSize s = GetSize();
	//SetMaxSize(s);

    SetTitle(FFQS(SID_BATCHMAKE_TITLE));

    CancelButton->Enable(true);
    MakeButton->Enable(true);

	m_Files = NULL;
	m_DoIdleTask = false;

}

//---------------------------------------------------------------------------------------

FFQBatchMake::~FFQBatchMake()
{
	//(*Destroy(FFQBatchMake)
	//*)
}

//---------------------------------------------------------------------------------------

void FFQBatchMake::Clear(bool releaseJobPointers)
{
    //Clear parsers
    for (size_t i = 0; i < PIP_COUNT; i++) m_PIPS[i].SetProbeOutput("");

    //Release job pointers
    if (releaseJobPointers)
    {
        for (size_t i = 0; i < m_Jobs.size(); i++) delete (LPFFQ_JOB)m_Jobs[i];
    }

    //Clear jobs
    m_Jobs.clear();
}

//---------------------------------------------------------------------------------------

bool FFQBatchMake::Execute()
{
    size_t c = (m_Files == NULL) ? 0 : m_Files->Count(), pc = FFQPresetMgr::Get()->GetPresetCount();

    if ((c == 0) || (pc == 0)) return ShowError(NULL, FFQS(SID_NO_FILES_OR_NO_PRESET));

    m_ClearLog = true;
    m_DoIdleTask = true;

    JobInfo->SetLabel(FFQSF(SID_BATCHMAKE_MAKE_JOBS_FOR, c));
    //Layout();
	//MainSizer->Fit(this);
	//MainSizer->SetSizeHints(this);

    Gauge->SetValue(0);
    CancelButton->Enable(true);
    MakeButton->Enable(true);
    m_Making = false;

	//Load options
	wxString cfg = FFQCFG()->batch_config;
    IncludeVideo->SetValue(GetToken(cfg, ',') == STR_YES);
    IncludeAudio->SetValue(GetToken(cfg, ',') == STR_YES);
    IncludeSubs->SetValue(GetToken(cfg, ',') == STR_YES);
    PrefAudio->SetValue(GetToken(cfg, ','));
    OutputFormat->SetValue(FFQCFG()->preferred_format);
    OutputPath->SetValue(FFQCFG()->preferred_path);

    //Keep previous selection
    Preset->FillAndSelect(cfg);

    CenterOnParent();

    bool res = (ShowModal() == wxOK);

    m_Files = NULL;

    return res;

}

//---------------------------------------------------------------------------------------

size_t FFQBatchMake::GetJobCount()
{
    return m_Jobs.size();
}

//---------------------------------------------------------------------------------------

void* FFQBatchMake::GetJob(size_t index)
{
    return m_Jobs[index];
}

//---------------------------------------------------------------------------------------

void FFQBatchMake::SetFiles(wxArrayString *files)
{
    m_Files = files;
}

//---------------------------------------------------------------------------------------

void FFQBatchMake::OnAction(wxCommandEvent& event)
{

    int evtId = event.GetId();

    if (evtId == ID_BROWSEBUTTON)
    {

        DestPathDlg->SetPath(OutputPath->GetValue());
        if (DestPathDlg->ShowModal() == wxID_OK) OutputPath->SetValue(DestPathDlg->GetPath());

    }

    else if (evtId == ID_MAKEBUTTON)
    {

        if ((!IncludeVideo->GetValue()) && (!IncludeAudio->GetValue()) && (!IncludeSubs->GetValue()))
        {
            ShowError(IncludeVideo, FFQS(SID_NO_CONTENT_SELECTED));
            return;
        }

        if (StrTrim(OutputFormat->GetValue()).Len() == 0)
        {
            ShowError(OutputFormat, FFQS(SID_OUTPUT_FORMAT_REQUIRED));
            return;
        }

        wxString dst = StrTrim(OutputPath->GetValue());
        if ((dst.Len() > 0) && (!wxDirExists(dst)))
        {
            ShowError(OutputPath, FFQS(SID_OUTPUT_PATH_EXIST_OR_EMPTY));
            return;
        }

        MakeButton->Enable(false);
        MakeJobs();

        if (m_Abort) EndModal(wxCANCEL);

        else
        {
            SaveConfig();
            EndModal(wxOK);
        }

    }

    else if (evtId == ID_CANCELBUTTON)
    {

        if (m_Making) m_Abort = true;
        else EndModal(wxCANCEL);

    }

}

//---------------------------------------------------------------------------------------

bool FFQBatchMake::FindJobForDest(wxString dest)
{

    //Find in already created jobs
    for (size_t i = 0; i < m_Jobs.size(); i++)
        if ( CompareFileNames(((LPFFQ_JOB)m_Jobs[i])->out, dest) ) return true;

    //Find in main
    if ( ((FFQMain*)GetParent())->FindItemForFile(dest, 0, true) >= 0 ) return true;

    //Not found
    return false;

}

//---------------------------------------------------------------------------------------

void FFQBatchMake::LogLine(wxString line, size_t color)
{

    FFQConsole::Get()->AppendLine(line, color, m_ClearLog);
    m_ClearLog = false;

}

//---------------------------------------------------------------------------------------

bool StreamInfoMatch(LPFFPROBE_STREAM_INFO si, wxString &findStr)
{
    if (findStr.Len() == 0) return true;
    return (si->codec_name.Lower().Find(findStr) >= 0) || (si->codec_long_name.Lower().Find(findStr) >= 0);
}

//---------------------------------------------------------------------------------------

LPFFPROBE_STREAM_INFO FindStreamInfo(FFProbeInfoParser *PIPs, CODEC_TYPE ct, wxString findStr = "")
{

    findStr.LowerCase(); //Always search for lowercase string

    for (size_t pidx = 0; pidx < PIP_COUNT; pidx++)
    {

        FFProbeInfoParser* pip = &PIPs[pidx];

        for (size_t sidx = 0; sidx < pip->GetStreamCount(); sidx++)
        {

            LPFFPROBE_STREAM_INFO si = pip->GetStreamInfo(sidx);

            if (StreamInfoMatch(si, findStr))
            {

                if ((ct == ctVIDEO) && (si->codec_type == CODEC_TYPE_VIDEO)) return si;
                else if ((ct == ctAUDIO) && (si->codec_type == CODEC_TYPE_AUDIO)) return si;
                else if ((ct == ctSUBTITLE) && (si->codec_type == CODEC_TYPE_SUBTITLE) && (!si->IsTeleText())) return si;

            }

        }

    }

    return NULL;
}

//---------------------------------------------------------------------------------------

wxString MakeStreamMapping(LPFFPROBE_STREAM_INFO sinf, int fileID, bool chk)
{
    STREAM_MAPPING smap;
    smap.checked = chk;
    smap.codec_type = sinf->codec_type;
    smap.file_id = fileID;
    smap.stream_id = sinf->index;
    return smap.ToString();
}

//---------------------------------------------------------------------------------------

void FFQBatchMake::MakeJobs()
{

    m_Making = true;
    m_Abort = false;

    LPFFQ_JOB job;
    FFQ_INPUT_FILE in1, in2;
    STREAM_MAPPING smap;
    LPFFPROBE_STREAM_INFO v_inf, a_inf, s_inf, si;

    size_t fileCount = m_Files->Count();
    wxString cur, sub_path;
    long idx, pt_pos;
    LPFFQ_PRESET preset = Preset->GetSelectedPreset();
    bool vid = IncludeVideo->GetValue(), aud = IncludeAudio->GetValue(), sub = IncludeSubs->GetValue();

    FFQMain* main = (FFQMain*)GetParent();
    FFQProcess* proc = new FFQProcess();
    //FFProbeInfoParser* pip = new FFProbeInfoParser();

    //For convenient creation of output names
    //wxString cfg_fmt = FFQCFG()->preferred_format, cfg_path = FFQCFG()->preferred_path;
    //FFQCFG()->preferred_format = StrTrim(OutputFormat->GetValue());
    //FFQCFG()->preferred_path = StrTrim(OutputPath->GetValue());

    for (size_t i = 0; i < fileCount; i++)
    {

        Gauge->SetValue((long)round((float)(i+1) / (float)fileCount * 1000.0));
        FFQCFG()->GetTaskBar()->SetTaskBarProgress(i, fileCount - 1);

        cur = m_Files->Item(i);

        //Make sure that the sub-path is preserved
        pt_pos = cur.Find(PATH_TOKEN);
        if (pt_pos > 0)
        {
            sub_path = cur.SubString(pt_pos + PATH_TOKEN.Len(), cur.Len());
            cur = cur.SubString(0, pt_pos - 1) + wxFileName::GetPathSeparator() + sub_path;
            #ifdef DEBUG
            //LogLine("sub_path=" + sub_path + CRLF + "cur=" + cur + CRLF, COLOR_BLUE);
            #endif // DEBUG
        }
        else sub_path = cur.AfterLast(wxFileName::GetPathSeparator());

        idx = main->FindItemForFile(cur);
        if (idx >= 0) LogLine(FFQSF(SID_LOG_ALREADY_QUEUED, cur), COLOR_RED);
        else try
        {

            job = new FFQ_JOB();
            in1.Reset();
            in2.Reset();

            in1.path = cur;
            in2.path = FFQCFG()->FindSecondaryInputFile(cur);

            LogLine(FFQSF(SID_LOG_MAKE_JOB_FOR, in1.path), COLOR_BLACK);

            //File 1
            proc->FFProbe(in1.path);
            m_PIPS[0].SetProbeOutput(proc->GetProcessOutput(false, true));

            //File 2 - if necessary
            if (in2.path.Len() > 0)
            {
                proc->FFProbe(in2.path);
                m_PIPS[1].SetProbeOutput(proc->GetProcessOutput(false, true));
                if (m_PIPS[1].GetStreamCount() == 0) in2.path = ""; //File 2 was invalid
            }

            v_inf = vid ? FindStreamInfo(m_PIPS, ctVIDEO) : NULL;
            a_inf = aud ? FindStreamInfo(m_PIPS, ctAUDIO, StrTrim(PrefAudio->GetValue())) : NULL;
            bool pref_aud = (a_inf != NULL);
            if ((!pref_aud) && aud) a_inf = FindStreamInfo(m_PIPS, ctAUDIO); //Take first stream
            s_inf = sub ? FindStreamInfo(m_PIPS, ctSUBTITLE) : NULL;

            //Translation hint: FFQS(SID_COMMON_[VIDEO|AUDIO|SUBTITLES]) can be used instead of CODEC_TYPE
            if ((v_inf == NULL) && vid) LogLine("\t" + FFQSF(SID_LOG_CONTENT_NOT_FOUND, CODEC_TYPE_VIDEO), COLOR_RED);
            else if ((a_inf == NULL) && aud) LogLine("\t" + FFQSF(SID_LOG_CONTENT_NOT_FOUND, CODEC_TYPE_AUDIO), COLOR_RED);
            else if ((s_inf == NULL) && sub) LogLine("\t" + FFQSF(SID_LOG_CONTENT_NOT_FOUND, CODEC_TYPE_SUBTITLE), COLOR_RED);

            else
            {

                //Check if in2 is used - if not remove it
                if (in2.path.Len() > 0)
                {
                    if ( (m_PIPS[1].IndexOf(v_inf) < 0) && (m_PIPS[1].IndexOf(a_inf) < 0) && (m_PIPS[1].IndexOf(s_inf) < 0) )
                    {
                        in2.path = "";
                        m_PIPS[1].SetProbeOutput("");
                    }
                }

                job->cmd_line = CMD_DEFAULT;
                m_PIPS[0].GetDuration(in1.duration);
                m_PIPS[0].GetVideoDimension(in1.width, in1.height);

                if (in2.path.Len() > 0)
                {
                    m_PIPS[1].GetDuration(in2.duration);
                    m_PIPS[1].GetVideoDimension(in2.width, in2.height);
                }

                //Name of output file
                //job->out = FFQCFG()->GetPreferredOutputName(in1.path); //Completely wrong!
                job->out = StrTrim(OutputPath->GetValue());
                if (job->out.Len() == 0)
                {

                    //No output path = use source path
                    job->out = in1.path.BeforeLast('.') + "." + StrTrim(OutputFormat->GetValue());

                }
                else
                {
                    //Add sub_path to output path
                    if (job->out[job->out.Len() - 1] != wxFileName::GetPathSeparator()) job->out += wxFileName::GetPathSeparator();
                    job->out += sub_path.BeforeLast('.') + "." + StrTrim(OutputFormat->GetValue());
                }

                //Make sure that source and destination are not equal
                if (in1.path.Lower() == job->out.Lower()) LogLine("\t" + FFQSF(SID_SOURCE_EQUALS_OUTPUT, job->out), COLOR_RED);

                //Make sure that no jobs has already been created with the destination
                else if (FindJobForDest(job->out)) LogLine("\t" + FFQSF(SID_DUPLICATE_JOB_FOR_OUTPUT, job->out), COLOR_RED);

                else
                {

                    //Preset to use
                    job->preset_id = preset->preset_id;

                    if (v_inf != NULL) LogLine("\t" + v_inf->codec_type + " : " + v_inf->codec_long_name, COLOR_GREEN);
                    if (a_inf != NULL) LogLine("\t" + a_inf->codec_type + " : " + a_inf->codec_long_name, pref_aud ? COLOR_GREEN : COLOR_BLUE);
                    if (s_inf != NULL) LogLine("\t" + s_inf->codec_type + " : " + s_inf->codec_long_name, COLOR_GREEN);

                    //All streams has to be implemented to prevent job-editor from sorting streams wrong
                    for (size_t pidx = 0; pidx < PIP_COUNT; pidx++)
                    {

                        FFProbeInfoParser* pip = &m_PIPS[pidx];

                        for (size_t sidx = 0; sidx < pip->GetStreamCount(); sidx++)
                        {
                            si = pip->GetStreamInfo(sidx);
                            job->stream_map += MakeStreamMapping(si, pidx+1, (si == v_inf) || (si == a_inf) || (si == s_inf)) + STREAM_MAPPING_SEPERATOR;
                        }

                    }

                    job->stream_map = job->stream_map.BeforeLast(STREAM_MAPPING_SEPERATOR);

                    //Add input files
                    job->inputs.Add(in1.ToString());
                    if (in2.path.Len() > 0) job->inputs.Add(in2.ToString());

                    m_Jobs.push_back(job);
                    job = NULL;

                }
            }

            if (job != NULL) delete job; //Free unused pointer

        }

        catch (std::exception &err)
        {

            LogLine("Error: " + wxString(err.what()), false);

        }

        Yield_App(); //Process messages in order to accept aborts

        if (m_Abort)
        {
            ShowInfo(this, FFQS(SID_TASK_ABORTED));
            break;
            //EndModal(wxCANCEL);
            //return;
        }

        LogLine("", true); //Blank line before next job..

    }

    //delete pip;
    delete proc;

    //Restore values
    //FFQCFG()->preferred_format = cfg_fmt;
    //FFQCFG()->preferred_path = cfg_path;
    FFQCFG()->GetTaskBar()->SetTaskBarProgress(0, 0);

}

//---------------------------------------------------------------------------------------

void FFQBatchMake::SaveConfig()
{
    LPFFQ_PRESET pst = Preset->GetSelectedPreset();
    wxString s;
    s.Printf(
        "%s,%s,%s,%s,%s",
        BOOLSTR(IncludeVideo->GetValue()),
        BOOLSTR(IncludeAudio->GetValue()),
        BOOLSTR(IncludeSubs->GetValue()),
        StrTrim(PrefAudio->GetValue()),
        pst->preset_id.ToString()
    );
    bool save = FFQCFG()->batch_config != s;
    FFQCFG()->batch_config = s;
    FFQCFG()->SetPreferredAndSave(StrTrim(OutputFormat->GetValue()), StrTrim(OutputPath->GetValue()), save);
}

//---------------------------------------------------------------------------------------

void FFQBatchMake::OnIdle(wxIdleEvent &event)
{

    if (m_DoIdleTask)
    {

        //Prevent task from being repeated
        m_DoIdleTask = false;

        //Expand all folders in the list of files
        wxString s, t;
        wxArrayString tmp;
        size_t i = 0;

        while (i < m_Files->Count())
        {

            //Get item
            s = m_Files->Item(i);

            if (wxDirExists(s))
            {

                //Get all files in folder
                wxDir::GetAllFiles(s, &tmp);

                //Go one level up
                s = s.BeforeLast(wxFileName::GetPathSeparator());

                //Remove the folder
                m_Files->RemoveAt(i);

                //Add files from folder using PATH_TOKEN as separator
                //to signal that a sub-folder must be created in destination folder
                for (size_t ii = 0; ii < tmp.Count(); ii++)
                {

                    t = tmp[ii];
                    m_Files->Insert(s + PATH_TOKEN + t.SubString(s.Len() + 1, t.Len()), i);
                    i++;

                }

                //Clear tmp
                tmp.Clear();

                //Update label
                JobInfo->SetLabel(FFQSF(SID_BATCHMAKE_MAKE_JOBS_FOR, m_Files->Count()));
                JobInfo->Update();

            }
            else i++;

        }

        if (m_Files->Count() == 0)
        {

            //No files was found
            ShowError(NULL, FFQS(SID_NO_FILES_OR_NO_PRESET));
            EndModal(wxID_CANCEL);
            return;

        }

        //Just in case the label has expanded
        Layout();

    }

    else event.Skip();
}

//---------------------------------------------------------------------------------------

void FFQBatchMake::OnClose(wxCloseEvent& event)
{
    if (m_Making && (!m_Abort)) return;
    event.Skip();
}