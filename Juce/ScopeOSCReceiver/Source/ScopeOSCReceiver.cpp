/**
 * O(pen) S(ound) C(ontrol) message handler
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

#include "ScopeOSCReceiver.h"

ScopeOSCReceiver::ScopeOSCReceiver()
{
	const String filename ("ScopeOSC");

    PropertiesFile::Options options;
    options.applicationName     = filename;
    options.folderName          = ProjectInfo::projectName;
    options.filenameSuffix      = "settings";
    options.osxLibrarySubFolder = "Application Support";
    
    properties = new PropertiesFile(options);

	int localPortNumber = 8000;

	if (properties->isValidFile())
	{
		localPortNumber = properties->getIntValue("localPortNumber", 8000);
		properties->setValue("localPortNumber", localPortNumber);
		properties->saveIfNeeded();
	}

	setLocalPortNumber(localPortNumber);
}

ScopeOSCReceiver::~ScopeOSCReceiver()
{
	disconnect();	
}


void ScopeOSCReceiver::setLocalPortNumber(int portNumber)
{
	if (portNumber != receivePortNumber && portNumber != 0)
	{
		if (connect(portNumber))
		{
			DBG("ScopeSyncOSCServer::setLocalPortNumber - set local port number to: " + String(portNumber));
			receivePortNumber = portNumber;
		}
		else
		{
			AlertWindow::showMessageBoxAsync (
				AlertWindow::WarningIcon,
				"Connection error",
				"OSC Error: could not connect to UDP port: " + String(receivePortNumber),
				"OK");		
		}
	}
}

void ScopeOSCReceiver::registerOSCListener(ListenerWithOSCAddress<RealtimeCallback>* newListener, OSCAddress address)
{
	removeListener(newListener);
	addListener(newListener, address);
}

void ScopeOSCReceiver::unregisterOSCListener(ListenerWithOSCAddress<RealtimeCallback>* listenerToRemove)
{
	removeListener(listenerToRemove);
}
