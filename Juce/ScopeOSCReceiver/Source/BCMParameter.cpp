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
#include "BCMMath.h"

BCMParameter::BCMParameter(String initialOSCUID)
	: scopeIntValue(0)
{
	oscUID.addListener(this);
	oscUID.setValue(initialOSCUID);
	DBG("BCMParameter::BCMParameter being constructed, there are now " + String(scopeOSCServer.getReferenceCount()) + " references to scopeOSCServer");
}

BCMParameter::~BCMParameter()
{
	oscUID.removeListener(this);
	scopeOSCServer->unregisterOSCListener(this);
	DBG("BCMParameter::BCMParameter being destroyed, there are now " + String(scopeOSCServer.getReferenceCount()) + " references to scopeOSCServer");
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
	scopeOSCServer->registerOSCListener(this, getOSCPath());
}

String BCMParameter::getOSCPath() const
{
	return oscUID.getValue();
}
    
void BCMParameter::oscMessageReceived (const OSCMessage& message)
{
	DBG("BCMParameter::oscMessageReceived - " + message.getAddressPattern().toString());

	if (message.size() == 1 && message[0].isInt32())
	{
		int newValue = message[0].getInt32();
		setScopeIntValue(newValue);
		DBG("BCMParameter::oscMessageReceived - set value to: " + String(newValue));
	}
	else
		DBG("BCMParameter::handleOSCMessage - received other OSC message");
}

