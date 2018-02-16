/**
 * O(pen) S(ound) C(ontrol) message handler
 *
 *  (C) Copyright 2018 bcmodular (http://www.bcmodular.co.uk/)
 *
 * This file is part of ScopeOSC.
 *
 * ScopeOSC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include "ScopeOSCSender.h"

ScopeOSCSender::ScopeOSCSender()
{
	setRemoteHostname("127.0.0.1");
    setRemotePortNumber(8000);
}

void ScopeOSCSender::setRemoteHostname(String hostname)
{
	if (hostname.compare(remoteHostname) != 0 && hostname != "0.0.0.0")
	{
		DBG("ScopeSyncOSCServer::setRemoteHostname - changed remote hostname to: " + hostname);
		remoteHostname = hostname;
		remoteChanged  = true;
	}
}

void ScopeOSCSender::setRemotePortNumber(int portNumber)
{
	if (portNumber != remotePortNumber && portNumber != 0)
	{
		DBG("ScopeSyncOSCServer::setRemotePortNumber - changed remote port number to: " + String(portNumber));
		remotePortNumber = portNumber;
		remoteChanged    = true;
	}
}

String ScopeOSCSender::getOSCPath(int parameterNumber) const
{
	String oscPath("/" + deviceInstance.toString() + "/" + deviceUID.toString() + "/" + parameterGroup.toString() + "/" + String(parameterNumber));
	DBG("BCMParameter::getOSCPath: returning " + oscPath);
	return oscPath;
}

bool ScopeOSCSender::sendMessage(int parameterNumber, int valueToSend)
{

	if (remoteChanged) {
        if (sender.connect(remoteHostname, remotePortNumber))
			remoteChanged = false;
		else
		{
			AlertWindow::showMessageBoxAsync (
				AlertWindow::WarningIcon,
				"Connection error",
				"OSC Error: could not connect to remote UDP port: " + String(remotePortNumber) + ", on host: " + remoteHostname,
				"OK");

			return false;
		}
    }

	OSCMessage message(getOSCPath(parameterNumber));
	message.addInt32(valueToSend);
	DBG("ScopeOSCSender::sendMessage: sending value: " + String(valueToSend) + " to port: " + String(remotePortNumber) + ", on host: " + remoteHostname);

	sender.send(message);
	return true;
}
