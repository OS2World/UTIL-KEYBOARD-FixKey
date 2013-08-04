// FIXKEY 1.0 -- keyboard utility to fix up substandard keyboards. See
//               readme.txt for further details.
//
// Author: Christopher Wong
//         wong1@husc4.harvard.edu


#define INCL_WIN
#include <OS2.H>

#define ICON_RC 1
MRESULT EXPENTRY winFunc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

int main(void)
{
  HAB hab;
  HMQ hmq;
  QMSG qmsg;
  HWND hwnd, hwndClient;
  ULONG flFlags;
  APIRET rc;
  const char FIXKEY[]="FIXKEY";

  flFlags = FCF_STANDARD & ~FCF_MENU & ~FCF_ACCELTABLE;

  hab = WinInitialize(0);
  hmq = WinCreateMsgQueue(hab, 0);

  if ( !WinRegisterClass(hab, FIXKEY, winFunc, CS_SIZEREDRAW, 0)) {
    printf("Registration of window class FIXKEY failed");
    exit(1);
  }

  hwnd = WinCreateStdWindow( HWND_DESKTOP, WS_MINIMIZED, 
			    &flFlags, FIXKEY, "Fixkey 1.0",
			    0, 0, ICON_RC, &hwndClient);
  // install keyboard hook
  if ( !installHook(hab)) exit(1);
  
  // minimize the window (which is blank, displaying nothing anyway.
  WinSetWindowPos(hwnd, HWND_TOP, 0,0,0,0, SWP_SHOW|SWP_MINIMIZE);

  // message loop
  while ( WinGetMsg(hab, &qmsg, NULLHANDLE, 0, 0))
    WinDispatchMsg(hab, &qmsg);

  // shut down: unload keyboard hook.
  printf("Shutting down\n");
  uninstallHook(hab);
  WinDestroyWindow(hwnd);
  WinDestroyMsgQueue(hmq);
  WinTerminate(hab);
}

MRESULT EXPENTRY winFunc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  switch (msg) {
  case WM_ERASEBACKGROUND:
    return (MRESULT) TRUE;
  default:
    return(WinDefWindowProc(hwnd, msg, mp1, mp2));
  }
}

