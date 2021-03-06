/**
 * Models a parameter
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

#ifndef BCMPARAMETER_H_INCLUDED
#define BCMPARAMETER_H_INCLUDED

#include <JuceHeader.h>
#include "ScopeOSCReceiver.h"
class ScopeFX;

class BCMParameter : public Value::Listener,
					 OSCReceiver::ListenerWithOSCAddress<OSCReceiver::RealtimeCallback>
{
public:
    BCMParameter(int paramNumber, ScopeFX* owner);
    ~BCMParameter();

	String getOSCPath() const;

	void setDeviceInstance  (int newValue) {deviceInstance = newValue;}
	void setDeviceUID       (int newValue) {deviceUID = newValue;}
	void setParameterGroup  (int newValue) {parameterGroup = newValue;}
	void toggleListening    (int newValue) {listening = (newValue == 0) ? false : true;}
	void setConfigurationUID(int newValue) {configurationUID = newValue;}

private:
	void  valueChanged(Value& valueThatChanged) override;
	void  oscMessageReceived(const OSCMessage& message) override;

	bool listening{};
	
	ScopeFX* scopeFX;

	Value deviceInstance;
	Value deviceUID;
	Value parameterGroup;
	Value configurationUID;
	int   parameterNumber;

	SharedResourcePointer<ScopeOSCReceiver> scopeOSCReceiver;
};

#endif  // BCMPARAMETER_H_INCLUDED
