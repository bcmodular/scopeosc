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

#ifndef SCOPEOSCRECEIVER_H_INCLUDED
#define SCOPEOSCRECEIVER_H_INCLUDED

#include <JuceHeader.h>
class ScopeOSCReceiver : private OSCReceiver
{
public:
	ScopeOSCReceiver();
	~ScopeOSCReceiver();

	// UDP Setup
	void   setLocalPortNumber(int portNumber);
	
	void   registerOSCListener(ListenerWithOSCAddress<RealtimeCallback>* newListener, OSCAddress address);
	void   unregisterOSCListener(ListenerWithOSCAddress<RealtimeCallback>* listenerToRemove);

private:
	
	static const int bufferSize = 4098;

	int	   receivePortNumber;
		   
	String remoteHostname;
	int	   remotePortNumber;
	bool   remoteChanged;

	ScopedPointer<PropertiesFile> properties;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ScopeOSCReceiver)
};

#endif  // SCOPEOSCRECEIVER_H_INCLUDED
