/**
 * Description of the scopefx input and output parameters, used
 * by the Scope "Effect" class for communication between Scope
 * applications and the ScopeOSCSender DLL.
 *
 *  (C) Copyright 2014 bcmodular (http://www.bcmodular.co.uk/)
 *
 * This file is part of ScopeOSC.
 *
 * ScopeSync is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * ScopeSync is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ScopeSync.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Contributors:
 *  Will Ellis
 */

#ifndef SCOPEFXPARAMETERDEFINITIONS_H_INCLUDED
#define SCOPEFXPARAMETERDEFINITIONS_H_INCLUDED
#include <effclass.h>

namespace ScopeFXParameterDefinitions {

    static const int numParameters = 16;
    static const int maxAddrLength = 1024;

    /** the async input numbers*/
    enum asyncInPads {
		INPAD_REMOTEHOST,
		INPAD_REMOTEPORT,
		INPAD_PARAMS,
//		INPAD_ADDRS,
		NUM_ASYNCINPADS
    };

    /** so far no sync inputs used*/
    enum syncInPads {
        NUM_SYNCINPADS
    };

    /** each control that should be connected to the sdk circuit needs an async outpad*/
    enum asyncOutPads {
        NUM_ASYNCOUTPADS
    };

    enum syncOutPads {
        NUM_SYNCOUTPADS
    };

   //-------------------------- Pad Definitions -------------------------------

    static PadType inputPadTypes[NUM_ASYNCINPADS + NUM_SYNCINPADS] = {
		{ DTYPE_STRING, 0, 0xFFFFFFFF },                 // INPAD_REMOTEHOST
		{ DTYPE_INT,    FRAC_MIN, FRAC_MAX },            // INPAD_REMOTEPORT
//		{ DTYPE_STRING, 0, 0xFFFFFFFF, numParameters },  // INPAD_ADDRS
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX, numParameters } // INPAD_PARAMS
	};

//    static PadType outputPadTypes[NUM_ASYNCOUTPADS + NUM_SYNCOUTPADS] = {
//		{ DTYPE_INT, FRAC_MIN, FRAC_MAX, numParameters }  // OUTPAD_PARAMS
//	};

    //--------------------------------------------------------------------------
    static nameDesc inputNameDescs[NUM_ASYNCINPADS + NUM_SYNCINPADS] = {
		{ "Host", "OSC Remote Hostname" },
		{ "Port", "OSC Remote Port" },
        { "In",   "Input Parameters" },
	};

//    static nameDesc outputNameDescs[NUM_ASYNCOUTPADS + NUM_SYNCOUTPADS] = {
//		{ "Out", "Parameter Outputs" },
//};

	//--------------------------------------------------------------------------
    static EffectDescription effectDescription = {

        NUM_ASYNCINPADS,   // int32    asyncinPads;
        NUM_SYNCINPADS,    // int32    syncinPads;
        //
        NUM_ASYNCOUTPADS,  // int32    asyncoutPads;
        NUM_SYNCOUTPADS,   // int32    syncoutPads;
        //
        inputPadTypes,     // PadType *typeOfInPad;
        NULL,              // PadType *typeOfOutPad;
        //outputPadTypes,    // PadType *typeOfOutPad;
        //
        MODFLAG_HASASYNC | MODFLAG_SINGLE,  // int32    flags;
        "OSCSender", // char    *shortName;
        "OSCSender", // char    *longName;
        NULL,              // int32   *delay;      // internal delay of output pads relative to input
        //                 // this delay is not part of the effect but has to be
        //                 // compensated
        0,                 // int32    cpuUsage;   // some measure for cpu usage
        inputNameDescs,    // char   **inPadNames  // array of short and long names of inpads
        NULL,    // char   **outPadNames  // array of short and long names of outpads
		//outputNameDescs,   // char   **outPadNames
    };
}

#endif  // SCOPEFXPARAMETERDEFINITIONS_H_INCLUDED
