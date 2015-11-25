/*	File:		MyPortModule.c	Contains:		Written by: 		Copyright:	Copyright � 1998-1999 by Apple Computer, Inc., All Rights Reserved.				You may incorporate this Apple sample source code into your program(s) without				restriction. This Apple sample source code has been provided "AS IS" and the				responsibility for its operation is yours. You are not permitted to redistribute				this Apple sample source code as "Apple sample source code" after having made				changes. If you're going to re-distribute the source, we require that you make				it clear in the source that the code was descended from Apple sample source				code, but that you've made changes.	Change History (most recent first):				8/16/1999	Karl Groethe	Updated for Metrowerks Codewarror Pro 2.1				*/#include <OpenTptModule.h>#include <OpenTptLinks.h>#include "EnablerSample.h"#include "MyPortCalls.h"#pragma import onOTPortRecord		gPortRecord;//extern void 	OfflineThePort(void);extern void		RegisterThePort(const RegEntryID *cardRef);/*void OfflineThePort(void){#if	DEBUG_WATCH_FUNC		DebugStr("\pCustomCardEnabler: OfflineThePort");		#endif	if (OTStrLength(gPortRecord.fPortName) > 0)	{		OTOfflinePort(gPortRecord.fPortName, nil);		gPortRecord.fPortName[0] = 0;	}}*/void	 RegisterThePort(const RegEntryID *cardRef){	UInt16 			other = 0;	size_t			sIndex = 0;	#if	DEBUG_WATCH_FUNC		DebugStr("\pCustomCardEnabler:  RegisterThePort");		#endif	OTMemzero(&gPortRecord, sizeof(gPortRecord));	OTMemcpy(&gPortRecord.fModuleName, &gDriverName, sizeof(gDriverName) + 1);			// find a unique "other" value for this device	do	{		gPortRecord.fRef = OTCreatePortRef(kOTPCCardBus, kOTEthernetDevice, 0, other++);	} while ( OTFindPortByRef(gPortRecord.fRef) != 0 );			// now find the associated slot number	gPortRecord.fSlotID[0] = 0;		// for the fInfoFlag the 0x1 indicates the module is DLPI		// for a TPI interface, set the value to 0x2	gPortRecord.fInfoFlags				= 0x1 | kOTPortIsSystemRegistered | kOTModUsesInterrupts;	gPortRecord.fCapabilities			= kOTFramingEthernet | kOTFramingEthernetIPX | kOTFraming8022;	gPortRecord.fNumChildPorts			= 0;	gPortRecord.fPortName[0]				= 0;		OTRegisterPort(&gPortRecord, (void*)cardRef);		}#pragma import off