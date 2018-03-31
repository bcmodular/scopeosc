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

#ifndef SCOPEOSCSENDER_H_INCLUDED
#define SCOPEOSCSENDER_H_INCLUDED

#include <JuceHeader.h>
class ScopeOSCSender
{
public:
	ScopeOSCSender();

	// UDP Setup
	void   setRemoteHostname(String hostname);
	void   setRemotePortNumber(int portNumber);
	
	bool   sendMessage(int parameterNumber, int valueToSend);

	String getOSCPath(int parameterNumber) const;

	void setDeviceInstance(int newValue) {deviceInstance = newValue;}
	void setDeviceUID     (int newValue) {deviceUID = newValue;}
	void setParameterGroup(int newValue) {parameterGroup = newValue;}
	void setRemoteHostName(int oct1, int oct2, int oct3, int oct4) {setRemoteHostname(String(oct1) + "." + String(oct2) + "." + String(oct3) + "." + String(oct4));}
	void setConfigurationUID(int newValue) {configurationUID = newValue;}

private:
	
	static const int bufferSize = 4098;
	   
	String remoteHostname;
	int	   remotePortNumber{};
	bool   remoteChanged{};

	OSCSender sender;

	int deviceInstance{};
	int deviceUID{};
	int parameterGroup{};
	int configurationUID{};

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ScopeOSCSender)
};

#endif  // SCOPEOSCSENDER_H_INCLUDED
