//////////////////////////////////////////////////////////////////////////////
//
//                 (C) Copyright 1988-2002 by Autodesk, Inc.
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _aduiBaseDialog_h
#define _aduiBaseDialog_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////////////
#pragma warning(push)
#pragma warning(disable : 4275)
class ADUI_PORT CAdUiBaseDialog : public CDialog {
    DECLARE_DYNAMIC(CAdUiBaseDialog);

public:
                CAdUiBaseDialog (
                    UINT idd,
                    CWnd *pParent=NULL,
                    HINSTANCE hDialogResource=NULL
                );
virtual         ~CAdUiBaseDialog ();

// AdUi message handlers
protected:
virtual ADUI_REPLY DoAdUiMessage (
                    ADUI_NOTIFY notifyCode, UINT controlId, LPARAM lParam
                );
virtual ADUI_REPLY OnNotifyControlChange (UINT controlId, LPARAM lParam);
virtual ADUI_REPLY OnNotifyControlValid (UINT controlId, BOOL isValid);
virtual ADUI_REPLY OnNotifyGeneric (UINT controlId, LPARAM lParam);
virtual ADUI_REPLY OnNotifyUpdateTip (CWnd *control);

// Drawing Editor Interaction
private:
        HINSTANCE m_commandResourceInstance;
        BOOL    m_commandWindowWasEnabled;
        HWND    m_commandWindowWithFocus;

protected:
        ADUI_COMMAND_STATE m_commandState;

        void    BeginEditorCommand ();
        void    CancelEditorCommand ();
        void    CompleteEditorCommand (BOOL restoreDialogs=TRUE);
        void    MakeDialogsVisible (BOOL visible);
public:
        BOOL    EditorCommandCancelled ();

// Context help
protected:
        CString m_contextHelpFileName;
        CString m_contextHelpFullPathName;
        CString m_contextHelpPrefix;    // Must be 4 ASCII characters.

virtual BOOL    FindContextHelpFullPath (LPCTSTR fileName, CString& fullPath);
public:
        LPCTSTR GetContextHelpFileName ();    
        void    SetContextHelpFileName (LPCTSTR pFileName);
        LPCTSTR GetContextHelpFullPathName ();    
        void    SetContextHelpFullPathName (LPCTSTR pFullPathName);
        LPCTSTR GetContextHelpPrefix ();   
        void    SetContextHelpPrefix (LPCTSTR pPrefix);

        CToolTipCtrl* GetToolTipCtrl();        
// Misc.
private:
        BOOL    m_bRunningModal;
        HINSTANCE m_hDialogResourceSaved;

        // Substitute font used when charset isn't supported in the default font
        CFont   m_substFont;

protected:
        BOOL    m_bUseTips;
        HINSTANCE m_hDialogResource;
        HICON   m_hIcon;
        CAdUiTextTip *m_pTextTip;
        CToolTipCtrl *m_pToolTip;
        CString m_rootKey;

		friend class CAdUiAssist;
	    static CAdUiAssist* m_pUIAssist;

protected:
virtual void    OnInitDialogBegin ();
virtual void    OnInitDialogFinish ();
public:
virtual CWnd    *AppMainWindow ();
virtual HINSTANCE AppResourceInstance ();
virtual LPCTSTR AppRootKey ();
        void    SetAppRootKey (LPCTSTR key);

        // Modeless dialogs should be created using one of the following
        // Create() methods (as per the MFC documentation). These are
        // provided to handle resource switching (like the new DoModal()).
        // ** Note: These methods are NOT declared virtual, yet duplicate
        //          the signature of the inherited methods.
        BOOL Create (LPCTSTR lpszTemplateName, CWnd* pParentWnd=NULL);
        BOOL Create (UINT nIDTemplate, CWnd* pParentWnd=NULL);

virtual void    EnableFloatingWindows (BOOL allow);     // INTERNAL USE ONLY
virtual int IsMultiDocumentActivationEnabled();         // INTERNAL USE ONLY
virtual int EnableMultiDocumentActivation(BOOL bEnable);// INTERNAL USE ONLY
virtual BOOL DoDialogHelp();                            // INTERNAL USE ONLY


        BOOL    GetUseTips ();
        void    SetUseTips (BOOL useTips);

        HICON   GetDialogIcon();
        void    SetDialogIcon(HICON hIcon);        

// Data Exchange methods
public:
        BOOL    DisplayData ();
virtual BOOL    ExchangeData (BOOL bSaveAndValidate);
        BOOL    ValidateData ();

// ClassWizard-controlled
public:
    //{{AFX_DATA(CAdUiBaseDialog)
    enum { IDD = 0 };
    //}}AFX_DATA

    //{{AFX_VIRTUAL(CAdUiBaseDialog)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);        // INTERNAL USE ONLY
	virtual int DoModal();                              // INTERNAL USE ONLY
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();                       // INTERNAL USE ONLY
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);     // INTERNAL USE ONLY
	//}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiBaseDialog)
    virtual BOOL OnInitDialog();
    afx_msg LONG OnAdUiMessage (WPARAM wParam, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);// INTERNAL USE ONLY
    afx_msg BOOL OnHelpInfo(HELPINFO* lpHelpInfo);
    afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
    afx_msg void OnAdUiTimer(UINT nIDEvent);
	//}}AFX_MSG
    afx_msg BOOL OnNotify_ToolTipText(UINT id, NMHDR *pNMHDR, LRESULT *pResult);
    DECLARE_MESSAGE_MAP()
};
#pragma warning(pop)
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

/////////////////////////////////////////////////////////////////////////////