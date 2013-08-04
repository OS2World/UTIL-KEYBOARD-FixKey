#include "kbdscan.h"
#define INCL_WIN
#define INCL_DOSMODULEMGR
#define INCL_DOSPROCESS        // for DosGetInfoBlocks
#define INCL_DOSSESMGR         // for SSF_TYPE_* constants
#include <os2.h>

BOOL EXPENTRY keyboardHook(HAB hab, PQMSG pqmsg, ULONG fs);  
BOOL installHook(HAB hab);
void uninstallHook(HAB hab);
HMODULE hookModuleHandle;

void uninstallHook(HAB hab)
{
    WinReleaseHook(hab, NULLHANDLE, HK_INPUT, (PFN) keyboardHook,
		   hookModuleHandle);  
}

BOOL installHook(HAB hab)
{
    APIRET rc;
    
    // get DLL module handle 
    rc = DosQueryModuleHandle("FIXHOOK", &hookModuleHandle);
    if (rc != 0) {
	printf("Unable to get fixhook.dll handle: %d\n", rc);
	return(FALSE);
    }
    
    // Install keyboard hook 
    rc = WinSetHook(hab, NULLHANDLE, HK_INPUT, (PFN)keyboardHook,
		    hookModuleHandle);
    if (!rc) {
	printf("Unable to hook system input queue: %d\n", rc);
	return(FALSE);
    }
    return(TRUE);
}

BOOL EXPENTRY keyboardHook(HAB hab, PQMSG pqmsg, ULONG fs)
{
    PTIB ptib;
    PPIB ppib;
    PUSHORT pfsflags;  // pointer to fsflags portion of WM_CHAR message
    PUSHORT pusvk;     // pointer to usvk portion of WM_CHAR message
    PUCHAR puchCh;     // pointer to usch portion of WM_CHAR message
    
    // we are only interested in keyboard events 
    if ((pqmsg->msg) != WM_CHAR) return FALSE;

    // assign pointers to the correct portions of the WM_CHAR message.
    pfsflags = (PUSHORT) &(pqmsg->mp1);
    pusvk = ((PUSHORT) &(pqmsg->mp2)) + 1; // ushort 2 from mp2
    puchCh = (PUCHAR) &(pqmsg->mp2);

    // translate only PM messages 
    DosGetInfoBlocks(&ptib, &ppib);
    if ( ppib->pib_ultype != SSF_TYPE_PM ) return FALSE;

    // special case: keypad enter and '/' key
    if ( *puchCh == 0x0d ) {
	*pusvk = VK_ENTER;
	*pfsflags |= KC_CHAR;
    } else if (*puchCh == 0x2f) 
	*pfsflags |= KC_CHAR;

    // from here, only interested in grey cursor keys and f11/f12 to
    // fixup. 
    if ( *puchCh!=0xe0 && *puchCh )
	return FALSE;
    
    // assign correct virtual key code to message, by first checking the 
    // second byte of the character chr
    switch( *(puchCh+1) ) {
      case K_HOME:
	*pusvk = VK_HOME;
	break;
      case K_UP:
	*pusvk = VK_UP;
	break;
      case K_PAGEUP:
	*pusvk = VK_PAGEUP;
	break;
      case K_LEFT:
	*pusvk = VK_LEFT;
	break;
      case K_RIGHT:
	*pusvk = VK_RIGHT;
	break;
      case K_END:
	*pusvk = VK_END;
	break;
      case K_DOWN:
	*pusvk = VK_DOWN;
	break;
      case K_PAGEDOWN:
	*pusvk = VK_PAGEDOWN;
	break;
      case K_INS:
	*pusvk = VK_INSERT;
	break;
      case K_DEL:
	*pusvk = VK_DELETE;
	break;
      case K_F11:
	*pusvk = VK_F11;
	break;
      case K_F12:
	*pusvk = VK_F12;
	break;
      default:
	return FALSE;
    }

    // assign KC_VIRTUALKEY flag to pfsflags part of message
    *pfsflags |= KC_VIRTUALKEY;
    return FALSE;
}
