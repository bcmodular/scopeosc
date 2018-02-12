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

#include "BCMParameter.h"
#include "ScopeFX.h"

BCMParameter::BCMParameter(int paramNumber, ScopeFX* owner)
	: scopeIntValue(0),
	  scopeFX(owner),
	  parameterNumber(paramNumber)
{
	deviceInstance.addListener(this);
	deviceUID.addListener(this);
	parameterGroup.addListener(this);
	scopeOSCReceiver->registerOSCListener(this, getOSCPath());
}

BCMParameter::~BCMParameter()
{
	deviceInstance.removeListener(this);
	deviceUID.removeListener(this);
	parameterGroup.removeListener(this);
	
	scopeOSCReceiver->unregisterOSCListener(this);
};

int BCMParameter::getScopeIntValue() const
{
	return scopeIntValue;
}

void BCMParameter::setScopeIntValue(int newValue)
{
	scopeIntValue = newValue;
}

void BCMParameter::valueChanged(Value& valueThatChanged)
{
	(void)valueThatChanged;

	// New OSC UID
	scopeOSCReceiver->registerOSCListener(this, getOSCPath());
}

String BCMParameter::getOSCPath() const
{
	String oscPath("/" + deviceInstance.toString() + "/" + deviceUID.toString() + "/" + parameterGroup.toString() + "/" + String(parameterNumber));
	DBG("BCMParameter::getOSCPath: returning " + oscPath);
	return oscPath;
}
    
void BCMParameter::oscMessageReceived (const OSCMessage& message)
{
	DBG("BCMParameter::oscMessageReceived - " + message.getAddressPattern().toString());

	if (!listening)
		DBG("BCMParameter::oscMessageReceived - ignoring OSC message");
	else if (message.size() == 1 && message[0].isInt32())
	{
		const int newValue = message[0].getInt32();
		scopeFX->setParameterValue(parameterNumber, newValue);
		DBG("BCMParameter::oscMessageReceived - set value to: " + String(newValue));
	}
	else
		DBG("BCMParameter::oscMessageReceived - received other OSC message");
}

