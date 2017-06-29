//==============================================================================
//
// Title:		Function429.h
// Purpose:		A short description of the interface.
//
// Created on:	2016/9/14 at 15:04:14 by USER-.
// Copyright:	MS. All Rights Reserved.
//
//==============================================================================

#ifndef __Function429_H__
#define __Function429_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files
#include "visa.h"


typedef enum _func{
	A429_BaudRate = 0,
	A429_TxEnable = 1,
	A429_ChannelEnable,
	A429_Speed,
	A429_OutWrap,
	A429_Wrap,
	A429_Reset
}func;

typedef struct									  
{												
   ViInt16 Slot; 	        //slot address
   ViChar InstrDesc[256]; 	//ASCII instrument descriptor string
   ViSession vi;
   ViInt16 chStatus[2];
   ViChar devName[256];
	
   char    vendorName[256];
   char    modelName[256];
   ViInt16  PID;
   ViInt16  VID;
   int  cardNum;
}  AR429_INFO;



//==============================================================================
// Global functions

ViStatus  A429_DmaSendString(short channel, short length ,unsigned int * pValue) ;
ViStatus  A429_DmaGetString(short channel, short length ,unsigned int * pValue,int *pActalLength) ;

ViStatus  A429_ConfigReg(short channel ,func type,unsigned int value);  

ViStatus  InitAR429(AR429_INFO *info, char *dstPC);
ViStatus  UnInitAR429();

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Function429_H__ */
