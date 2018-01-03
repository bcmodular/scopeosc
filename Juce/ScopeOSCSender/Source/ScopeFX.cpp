/**
 * Wrapper class that hosts the ScopeSync object and its GUI
 * on behalf of the Scope (or Scope SDK) applications, using 
 * the ScopeFX SDK. This requires it to be derived from the Effect
 * class.
 *
 *
 *  (C) Copyright 2014 bcmodular (http://www.bcmodular.co.uk/)
 *
 * This file is part of ScopeOSC.
 *
 * ScopeOSC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * ScopeOSC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ScopeOSC.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Contributors:
 *  Will Ellis
 */

#include "ScopeFX.h"
#include "ScopeOSCSender.h"

#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef _WIN32
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)  
HWND scopeWindow;
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM /* lParam */)
{
    HINSTANCE hinst = (HINSTANCE)GetModuleHandle(NULL);

    if((HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE) == hinst && IsWindowVisible(hwnd))
    {
        scopeWindow = hwnd;
        return FALSE;
    }
    else
        return TRUE;
}
#endif

using namespace ScopeFXParameterDefinitions;
Array<ScopeFX*> ScopeFX::scopeFXInstances;

ScopeFX::ScopeFX()
	: Effect(&effectDescription)
{
	#ifdef _WIN32
        Process::setCurrentModuleInstanceHandle(HINST_THISCOMPONENT);
	#endif
        initialiseJuce_GUI();

	scopeOSCSender = new ScopeOSCSender();

	for (int i = 0; i < numParameters; i++)
		parameters.add(new BCMParameter(i+1, scopeOSCSender));
}

ScopeFX::~ScopeFX()
{
	scopeFXInstances.removeAllInstancesOf(this);

	if (scopeFXInstances.isEmpty())
	{
		shutdownJuce_GUI();
	}
}

int ScopeFX::async(PadData** asyncIn,  PadData* /*syncIn*/,
                   PadData*  asyncOut, PadData* /*syncOut*/)
{
	(void)asyncOut;

	scopeOSCSender->setRemotePortNumber(asyncIn[INPAD_REMOTEPORT]->itg);
	scopeOSCSender->setRemoteHostName(asyncIn[INPAD_REMOTEHOST_OCT1]->itg, 
									  asyncIn[INPAD_REMOTEHOST_OCT2]->itg,
									  asyncIn[INPAD_REMOTEHOST_OCT3]->itg, 
									  asyncIn[INPAD_REMOTEHOST_OCT4]->itg);

	scopeOSCSender->setDeviceInstance(asyncIn[INPAD_DEVICE_INSTANCE]->itg);
	scopeOSCSender->setDeviceUID(asyncIn[INPAD_DEVICE_UID]->itg);
	scopeOSCSender->setParameterGroup(asyncIn[INPAD_PARAMETER_GROUP]->itg);
	
	for (int i = 0; i < numParameters; i++)
	{
		parameters[i]->setScopeIntValue(asyncIn[i]->itg);
		parameters[i]->setSnapshotCounter(asyncIn[INPAD_SNAPSHOT_COUNTER]->itg);
		parameters[i]->toggleMessageSending(asyncIn[INPAD_SEND_MESSAGES]->itg);
	}

	return -1;
}

int ScopeFX::syncBlock(PadData** /*asyncIn*/, PadData* /*syncIn*/,
                       PadData* /*asyncOut*/, PadData* /*syncOut*/, 
                       int /*off*/,
                       int /*cnt*/)
{
	return -1;
}

Effect *newEffect()
{
	return new ScopeFX();
};

void deleteEffect (Effect *eff)
{
   delete eff;
}

EffectDescription *descEffect ()
{
    return &effectDescription;
}

extern "C"
::uint32 ioctlEffect (
					  ::uint32  /* dwService */, ::uint32  /* dwDDB */, ::uint32  /* hDevice */,
					  void * /* lpvInBuffer */, ::uint32 /* cbInBuffer */, 
					  void * /* lpvOutBuffer */, ::uint32 /* cbOutBuffer */,
					  ::uint32 * lpcbBytesReturned )
{
   *lpcbBytesReturned = 0;
   return ERROR_NOT_SUPPORTED;
}
