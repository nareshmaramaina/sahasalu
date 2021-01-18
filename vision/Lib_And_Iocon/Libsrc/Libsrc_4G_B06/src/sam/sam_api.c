
/************************************************************************************************ 
 ** 
 **Copyright(c)2010, Linkwell Telesystems (P) Ltd 
 **1-11-252/1/A, Gowra Klassic, Begumpet 
 **Hyderabad 500016 INDIA 
 ** 
 **Author:Pavani Sireesha.K
 **Dept: Research & Development 
 **File Name:gl11-test_sam.c 
 **Description: Checking the functionality of SAM cards.
 ******************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "wintypes.h"
#include "winscard.h"
//#include "sam_api.h"

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

static LONG rv=0;
SCARDCONTEXT hContext;
DWORD dwReaders=0;
LPSTR mszReaders = NULL;
static char *ptr, **readers = NULL;
static int nbReaders=0;
SCARDHANDLE hCard=0;
DWORD dwActiveProtocol, dwReaderLen, dwState, dwProt, dwAtrLen;
BYTE pbAtr[MAX_ATR_SIZE] = "";
static char pbReader[MAX_READERNAME] = "";
static int reader_nb=0;
const SCARD_IO_REQUEST *pioSendPci=NULL;
static SCARD_IO_REQUEST pioRecvPci;


/* PCSC error message pretty print */
#define PCSC_ERROR(rv, text) \
	if (rv != SCARD_S_SUCCESS) \
{\
	printf(text ": %s (0x%lX)\n", pcsc_stringify_error(rv), rv); \
	return -1;\
} \
else \
{ \
	printf(text ": OK\n\n"); \
}
int SAM_PowerDown();
int SAM_Open ( void )
{
	int ret=0;
//	ret=sam_pwron( );

gl11_sam_pwr_ctrl(1);

	sleep(3);
/*	if(ret!=0)
	{
		printf("Sam power on failed\n");
		return -1;
	}
	else
		printf("Sam power on success\n");*/
	

	rv = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext);
	if (rv != SCARD_S_SUCCESS)
	{
		printf("SCardEstablishContext: Cannot Connect to Resource Manager %lX\n", rv);
		return -1;
	}

	/* Retrieve the available readers list. */
	dwReaders = SCARD_AUTOALLOCATE;
	rv = SCardListReaders(hContext, NULL, (LPSTR)&mszReaders, &dwReaders);
	PCSC_ERROR(rv, "SCardListReaders")
		/* Extract readers from the null separated string and get the total
		 * number of readers */
		nbReaders = 0;
	ptr = mszReaders;
	while (*ptr != '\0')
	{
		ptr += strlen(ptr)+1;
		nbReaders++;
	}

	if (nbReaders == 0)
	{
		printf("No reader found\n");
		SAM_Close();
		return -1;
	}

	/* allocate the readers table */
	readers = calloc(nbReaders, sizeof(char *));
	if (NULL == readers)
	{
		printf("Not enough memory for readers[]\n");
		SAM_Close();
		return -1;
	}

	/* fill the readers table */
	nbReaders = 0;
	ptr = mszReaders;
	while (*ptr != '\0')
	{
		printf("%d: %s\n", nbReaders, ptr);
		readers[nbReaders] = ptr;
		ptr += strlen(ptr)+1;
		nbReaders++;
	}
	printf("no of readers = %d \n",nbReaders);
	return 0;
}

int SAM_ColdReset(int selection)
{

	unsigned int count=0;

	if((selection==1) || (selection== 2 ) || (selection==3)){
		reader_nb=0;
	}
	else if((selection==4) || (selection== 5 ) || (selection==6)){
		reader_nb=1;
	}
	else{
		return -1;
	}
	if(hCard!=0){

		dwAtrLen=0;
		memset(pbAtr,'\0',MAX_ATR_SIZE);
		SAM_PowerDown();
		hCard=0;
	}
	dwActiveProtocol = -1;
	printf("reader_nb= %d \n",reader_nb);
	rv = SCardConnect(hContext, readers[reader_nb], SCARD_SHARE_SHARED,SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hCard, &dwActiveProtocol);
	printf(" Protocol: %ld\n", dwActiveProtocol);
	PCSC_ERROR(rv, "SCardConnect")
		/* get card status */
		dwAtrLen = sizeof(pbAtr);
	dwReaderLen = sizeof(pbReader);
	rv = SCardStatus(hCard, /*NULL*/ pbReader, &dwReaderLen, &dwState, &dwProt,pbAtr, &dwAtrLen);
	printf(" Reader: %s (length %ld bytes)\n", pbReader, dwReaderLen);
	printf(" State: 0x%lX\n", dwState);
	printf(" Prot: %ld\n", dwProt);
	printf(" ATR (length %ld bytes):", dwAtrLen);
	for (count=0; count < dwAtrLen; count++)
		printf(" %02X", pbAtr[count]);
	printf("\n");
	PCSC_ERROR(rv, "SCardStatus")
		switch(dwActiveProtocol)
		{
			case SCARD_PROTOCOL_T0:
				pioSendPci = SCARD_PCI_T0;
				break;
			case SCARD_PROTOCOL_T1:
				pioSendPci = SCARD_PCI_T1;
				break;
			default:
				printf("Unknown protocol\n");
				return -1;
		}
		return 0;

}
int SAM_GetAtr ( unsigned int * length, unsigned char * buffer )
{
	unsigned int loop;
	*length=dwAtrLen;
	for (loop=0; loop < dwAtrLen; loop++){
		printf(" %02X ", pbAtr[loop]);
		buffer[loop]=pbAtr[loop];
	}
	return 0;
}
int SAM_SendCommand (unsigned char *CAPDU_Data,unsigned int CLen,unsigned char *RAPDU_Data,unsigned int *RLen )

{
	unsigned int count=0;
	DWORD RLenSam=0;
	if(hCard==0){
		printf("Card is Absent or Card is UnPowered\n");
		return -1;
	}
	/* exchange APDU */
	printf("Sending: ");
	for (count=0; count < CLen; count++)
		printf("%02X ",CAPDU_Data[count]);
	printf("\n");

       /* begin transaction */
        rv = SCardBeginTransaction(hCard);
        PCSC_ERROR(rv, "SCardBeginTransaction")

	//rv = SCardTransmit(hCard, pioSendPci, CAPDU_Data, CLen,	&pioRecvPci, RAPDU_Data,(DWORD *)&RLen);
	rv = SCardTransmit(hCard, pioSendPci, CAPDU_Data, CLen,	&pioRecvPci, RAPDU_Data,(DWORD *)RLen);

	RLenSam = *RLen;
	printf("Received len = %d \n ",*RLen);
	for (count=0;  count < RLenSam; count++)
		printf("%02X ", RAPDU_Data[count]);
	printf("\n");

	rv = SCardEndTransaction(hCard, SCARD_LEAVE_CARD);
	PCSC_ERROR(rv, "SCardEndTransaction")
	
	return 0;

}
int SAM_PowerDown ( )
{
	//	int loop;
	/* end transaction */
	printf("IN SAM POWER DOWN \n");
	if(hCard!=0)
	{

			/* card disconnect */
		rv = SCardDisconnect(hCard, SCARD_UNPOWER_CARD);
		PCSC_ERROR(rv, "SCardDisconnect")
			hCard=0;
	}
	return 0;

}
int SAM_Close ( )
{
	int ret=0;
	SAM_PowerDown();
	/* free allocated memory */
	if (mszReaders)
		SCardFreeMemory(hContext, mszReaders);

	/* We try to leave things as clean as possible */
	rv = SCardReleaseContext(hContext);
	PCSC_ERROR(rv, "SCardReleaseContext")

		if (readers!=NULL)
			free(readers);
	readers=NULL;
	struct stat statBuffer;
	rv = stat("/var/run/pcscd/pcscd.pid", &statBuffer);
	if(rv==0) 
	{
		system("kill -9 `pidof pcscd`");
		system("rm /var/run/pcscd/*");

	}	

gl11_sam_pwr_ctrl(0);
/*	ret=sam_pwroff( );
	if(ret!=0){
		printf("Sam power off failed \n");
		return -1;	
	}
	else
		printf("Sam power off success\n");*/
	return 0;	

}
