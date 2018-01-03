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
#include "ScopeOSCSender.h"

BCMParameter::BCMParameter(int paramNumber, ScopeOSCSender* sender)
	: scopeOSCSender(sender),
	  parameterNumber(paramNumber),
	  sendMessages(true)
{
	scopeIntValue = 0;
	scopeIntValue.addListener(this);

	snapshotCounter = 0;
	snapshotCounter.addListener(this);
}

BCMParameter::~BCMParameter()
{
	scopeIntValue.removeListener(this);
	snapshotCounter.removeListener(this);
};

void BCMParameter::setScopeIntValue(int newValue)
{
	scopeIntValue.setValue(newValue);
}

void BCMParameter::setSnapshotCounter(int newValue)
{
	snapshotCounter.setValue(newValue);
}

void BCMParameter::valueChanged(Value& valueThatChanged)
{	
	(void)valueThatChanged;
	
	// Send a message either if the value has changed, or if the snapshot counter has incremented
	if (sendMessages)
		scopeOSCSender->sendMessage(parameterNumber, int(scopeIntValue.getValue()));	
}
