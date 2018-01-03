/**
 * Models a parameter
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

#ifndef BCMPARAMETER_H_INCLUDED
#define BCMPARAMETER_H_INCLUDED

#include <JuceHeader.h>
#include "ScopeOSCReceiver.h"

class BCMParameter : public  Value::Listener,
					 private OSCReceiver::ListenerWithOSCAddress<OSCReceiver::RealtimeCallback>
{
public:
    BCMParameter(int paramNumber);
    ~BCMParameter();

	int  getScopeIntValue() const;
    void setScopeIntValue(int newValue);

	String getOSCPath() const;

	void setDeviceInstance (int newValue) {deviceInstance = newValue;}
	void setDeviceUID      (int newValue) {deviceUID = newValue;}
	void setParameterGroup (int newValue) {parameterGroup = newValue;}
	void toggleListening   (int newValue) { listening = (newValue == 0) ? false : true; }

private:
	void  valueChanged(Value& valueThatChanged) override;
	void  oscMessageReceived(const OSCMessage& message) override;

	int  scopeIntValue;
	bool listening;
	
	Value deviceInstance;
	Value deviceUID;
	Value parameterGroup;
	Value parameterNumber;

	SharedResourcePointer<ScopeOSCReceiver> scopeOSCReceiver;
};

#endif  // BCMPARAMETER_H_INCLUDED
