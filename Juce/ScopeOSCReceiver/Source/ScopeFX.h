/**
 * Wrapper class that hosts the ScopeSync object and its GUI
 * on behalf of the Scope (or Scope SDK) applications, using 
 * the ScopeFX SDK. This requires it to be derived from the Effect
 * class.
 *
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

#ifndef SCOPEFX_H_INCLUDED
#define SCOPEFX_H_INCLUDED

//#include <vld.h>
#include <JuceHeader.h>
#include <atomic>
#include <array>
#include "../../../External/SonicCore/effclass.h"
#include "ScopeFXParameterDefinitions.h"
#include "BCMParameter.h"

using namespace ScopeFXParameterDefinitions;

class ScopeFX : public Effect
{
public:
    ScopeFX();

    // Process a set of Sync data coming in from Scope
    // and fill in outgoing streams as appropriate
    int  syncBlock (PadData** asyncIn,  PadData* syncIn,
                    PadData*  asyncOut, PadData* syncOut, 
                    int       off,      int      cnt);

    // Process new Async values coming in from Scope and pass on
    // updates from within ScopeSync
    int  async (PadData** asyncIn,  PadData* syncIn,
                PadData*  asyncOut, PadData* syncOut);

	void setParameterValue(int parameterNumber, int newValue);

private:	
	ScopedJuceInitialiser_GUI guiInitialiser;
	OwnedArray<BCMParameter> parameters;

	std::array<std::atomic<int>, 16> parameterValues {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
};

#endif  // SCOPEFX_H_INCLUDED
