/**
 * Description of the scopefx input and output parameters, used
 * by the Scope "Effect" class for communication between Scope
 * applications and the ScopeOSCSender DLL.
 *
 *  (C) Copyright 2018 bcmodular (http://www.bcmodular.co.uk/)
 *
 * This file is part of ScopeOSC.
 *
 * ScopeSync is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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
		INPAD_PARAM1,
        INPAD_PARAM2,
        INPAD_PARAM3,
        INPAD_PARAM4,
        INPAD_PARAM5,
        INPAD_PARAM6,
        INPAD_PARAM7,
        INPAD_PARAM8,
        INPAD_PARAM9,
        INPAD_PARAM10,
        INPAD_PARAM11,
        INPAD_PARAM12,
        INPAD_PARAM13,
        INPAD_PARAM14,
        INPAD_PARAM15,
        INPAD_PARAM16,
		INPAD_DEVICE_INSTANCE,
		INPAD_DEVICE_UID,
		INPAD_PARAMETER_GROUP,
		INPAD_REMOTEHOST_OCT1,
		INPAD_REMOTEHOST_OCT2,
		INPAD_REMOTEHOST_OCT3,
		INPAD_REMOTEHOST_OCT4,
		INPAD_REMOTEPORT,
		INPAD_SNAPSHOT_COUNTER,
		INPAD_SEND_MESSAGES,
		INPAD_CONFIGUID,
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
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_PARAM1
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_PARAM2
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_PARAM3
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_PARAM4
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_PARAM5
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_PARAM6
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_PARAM7
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_PARAM8
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_PARAM9
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_PARAM10
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_PARAM11
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_PARAM12
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_PARAM13
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_PARAM14
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_PARAM15
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_PARAM16
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_DEVICE_INSTANCE
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_DEVICE_UID
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_PARAMETER_GROUP
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_REMOTEHOST_OCT1
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_REMOTEHOST_OCT2
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_REMOTEHOST_OCT3
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_REMOTEHOST_OCT4
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_REMOTEPORT
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_SNAPSHOT_COUNTER
		{ DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_SEND_MESSAGES
        { DTYPE_INT, FRAC_MIN, FRAC_MAX },  // INPAD_CONFIGUID
	};

//    static PadType outputPadTypes[NUM_ASYNCOUTPADS + NUM_SYNCOUTPADS] = {
//		{ DTYPE_INT, FRAC_MIN, FRAC_MAX, numParameters }  // OUTPAD_PARAMS
//	};

    //--------------------------------------------------------------------------
    static nameDesc inputNameDescs[NUM_ASYNCINPADS + NUM_SYNCINPADS] = {
		{ "I1",   "Parameter Input 1" },
		{ "I2",   "Parameter Input 2" },
		{ "I3",   "Parameter Input 3" },
		{ "I4",   "Parameter Input 4" },
		{ "I5",   "Parameter Input 5" },
		{ "I6",   "Parameter Input 6" },
		{ "I7",   "Parameter Input 7" },
		{ "I8",   "Parameter Input 8" },
		{ "I9",   "Parameter Input 9" },
		{ "I10",  "Parameter Input 10" },
		{ "I11",  "Parameter Input 11" },
		{ "I12",  "Parameter Input 12" },
		{ "I13",  "Parameter Input 13" },
		{ "I14",  "Parameter Input 14" },
		{ "I15",  "Parameter Input 15" },
		{ "I16",  "Parameter Input 16" },
		{ "Inst", "Device Instance" },
		{ "DUID", "Device UID" },
		{ "PmGp", "Parameter Group" },
		{ "HoO1", "Remote Host Octet 1" },
		{ "HoO2", "Remote Host Octet 2" },
		{ "HoO3", "Remote Host Octet 3" },
		{ "HoO4", "Remote Host Octet 4" },
		{ "Port", "Remote Port" },
		{ "Snap", "Snapshot Counter" },
		{ "Send", "Send Messages" },
		{ "cfg",  "configuration uid" },
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
