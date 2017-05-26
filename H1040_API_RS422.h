//==============================================================================
//
// Title:		Function429.h
// Purpose:		A short description of the interface.
//
// Created on:	2016/9/14 at 15:04:14 by USER-.
// Copyright:	MS. All Rights Reserved.
//
//==============================================================================

#ifndef __H1040_API_RS422_H__
#define __H1040_API_RS422_H__

#define DLL_API_EXPORT
#ifdef DLL_API_EXPORT
#define NENGTONG_API    __declspec(dllexport)
#else
#define NENGTONG_API    __declspec(dllimport)
#endif

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

//#include "cvidef.h"
//#include <ansi_c.h>
#include "visa.h"


NENGTONG_API ViStatus _VI_FUNC  NT_H1040_RS485_RelayConfig(ViSession vi,int channelStatus) ;  


NENGTONG_API ViStatus _VI_FUNC  NT_H1040_RS422_SendString(ViSession vi,short channel, short length ,unsigned char * pValue,unsigned int *pActualLength) ;
NENGTONG_API ViStatus _VI_FUNC  NT_H1040_RS422_GetString(ViSession vi,short channel, short length ,unsigned char * pValue,int *pActalLength) ;
NENGTONG_API ViStatus _VI_FUNC  NT_H1040_RS422_DataFormatConfig(ViSession vi,short channel ,unsigned long baudrate,int wordlength,int parity,int stopBit); 


NENGTONG_API ViStatus _VI_FUNC  NT_H1040_RS232_DataFormatConfig(ViSession vi,short channel ,unsigned long baudrate,short wordlength,short parity,int stopBit); 
NENGTONG_API ViStatus _VI_FUNC  NT_H1040_RS232_SendString(ViSession vi,short channel, short length ,unsigned char * pValue,unsigned int *pActualLength) ;
NENGTONG_API ViStatus _VI_FUNC  NT_H1040_RS232_GetString(ViSession vi,short channel, short length ,unsigned char * pValue,int *pActalLength) ;



NENGTONG_API ViStatus _VI_FUNC NT_H1040_GetID(ViSession vi);

NENGTONG_API ViStatus _VI_FUNC NT_H1040_InitSession(ViRsrc resourceName, ViSession *vi);
NENGTONG_API ViStatus _VI_FUNC NT_H1040_UnInitSession(ViSession vi) ;

NENGTONG_API ViStatus _VI_FUNC NT_H1040_Rs422Init(ViSession vi);
NENGTONG_API ViStatus _VI_FUNC NT_H1040_Rs422UnInit(ViSession vi) ;

NENGTONG_API ViStatus _VI_FUNC NT_H1040_Rs232Init(ViSession vi);
NENGTONG_API ViStatus _VI_FUNC NT_H1040_Rs232UnInit(ViSession vi) ;


NENGTONG_API ViStatus _VI_FUNC NT_H1040_GetSofewareVer(ViSession vi, ViUInt32* piVersion);
NENGTONG_API ViStatus _VI_FUNC NT_H1040_ReturnDescriptor(ViInt16 iSlotNum[], ViChar descriptor[][256], ViUInt32 *numFound,ViChar fpgaSoft[][256]) ;

#ifdef __cplusplus
    }
#endif

#endif 
