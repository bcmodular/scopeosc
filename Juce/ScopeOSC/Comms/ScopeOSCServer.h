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

#ifndef SCOPEOSCSERVER_H_INCLUDED
#define SCOPEOSCSERVER_H_INCLUDED

#include <JuceHeader.h>
class ScopeOSCServer : private OSCReceiver
{
public:
	ScopeOSCServer();

	void setup();

	// UDP Setup
	void   setLocalPortNumber(int portNumber);
	
	void   setRemoteHostname(String hostname);
	String getRemoteHostname() const;
	void   setRemotePortNumber(int portNumber);
	int    getRemotePortNumber() const;

	bool   sendMessage(const OSCAddressPattern pattern, float valueToSend);

	void   registerOSCListener(Listener<RealtimeCallback>* newListener);
	void   unregisterOSCListener(Listener<RealtimeCallback>* listenerToRemove);

	juce_DeclareSingleton (ScopeOSCServer, false)

private:
	
	static const int bufferSize = 4098;

	int	   receivePortNumber;
		   
	String remoteHostname;
	int	   remotePortNumber;
	bool   remoteChanged;

	OSCSender sender;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ScopeOSCServer)
};

#endif  // SCOPEOSCSERVER_H_INCLUDED
