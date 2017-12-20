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
#include "ScopeOSCServer.h"

class BCMParameter : public  Value::Listener,
					 private OSCReceiver::ListenerWithOSCAddress<OSCReceiver::RealtimeCallback>
{
public:
    BCMParameter(String initialOSCUID);
    ~BCMParameter();

	int  getScopeIntValue() const;
    void setScopeIntValue(int newValue);

	String getOSCPath() const;

private:
	void  valueChanged(Value& valueThatChanged) override;
	void  oscMessageReceived (const OSCMessage& message) override;

	int   scopeIntValue;
	Value oscUID;

	SharedResourcePointer<ScopeOSCServer> scopeOSCServer;
};

#endif  // BCMPARAMETER_H_INCLUDED
