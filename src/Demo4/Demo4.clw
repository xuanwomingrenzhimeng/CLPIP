; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDemo4View
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Demo4.h"
LastPage=0

ClassCount=7
Class1=CDemo4App
Class2=CDemo4Doc
Class3=CDemo4View
Class4=CMainFrame

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CChildFrame
Class6=CAboutDlg
Resource3=IDR_DEMO4TYPE
Class7=RotateDlg
Resource4=IDD_DIALOG_Rotate

[CLS:CDemo4App]
Type=0
HeaderFile=Demo4.h
ImplementationFile=Demo4.cpp
Filter=N

[CLS:CDemo4Doc]
Type=0
HeaderFile=Demo4Doc.h
ImplementationFile=Demo4Doc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CDemo4Doc

[CLS:CDemo4View]
Type=0
HeaderFile=Demo4View.h
ImplementationFile=Demo4View.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=id_Binary


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=Demo4.cpp
ImplementationFile=Demo4.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_DEMO4TYPE]
Type=1
Class=CDemo4View
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_APP_ABOUT
Command12=id_ColorToGray
Command13=id_Prewitt
Command14=id_Binary
Command15=ID_MENUITEM32775
Command16=ID_MENUITEM32776
Command17=id_FreeRotate
Command18=id_ColorToGray
Command19=id_Prewitt
Command20=id_Binary
Command21=ID_MENUITEM32783
Command22=ID_MENUITEM32784
CommandCount=22

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_DIALOG_Rotate]
Type=1
Class=RotateDlg
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_Edit_Angle,edit,1350631552
Control3=IDOK,button,1342242816
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,button,1342177287
Control6=IDC_RADIO1,button,1342177289
Control7=IDC_RADIO2,button,1342177289
Control8=IDC_RADIO3,button,1342177289

[CLS:RotateDlg]
Type=0
HeaderFile=RotateDlg.h
ImplementationFile=RotateDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

