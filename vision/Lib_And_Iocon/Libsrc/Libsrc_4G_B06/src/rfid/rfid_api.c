#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <sys/signal.h>
#include <sys/time.h>
#include <string.h>
#include <sys/ioctl.h>


//#define TAMA_DEBUG	//enable this macro for testing only


typedef struct
{
  unsigned char tgno;
  unsigned char sens_res[2];
  unsigned char sel_res;
  unsigned char nfcid_len;
  unsigned char nfcid[4];
} TargetData;
                                                                                                                             
static   int   fd ;
unsigned char  auth_tg;	//To store authenticated tag.
unsigned char  tg_nbtg; //To store number of tags detected
unsigned char* _databuf;
unsigned char  read_buf[1024];

unsigned char One = 0x01;
unsigned char Two = 0x02;

unsigned char  _preamble[] = {0x00,0x00,0xff};
unsigned char  _ack[]      = {0x00,0x00,0xff,0x00,0xff,0x00};
unsigned char  _error[]    = {0x00,0x00,0xff,0x01,0xff,0x7f,0x81};

TargetData tg_data[2];		//To store tag details
struct 	   termios old_termios; //structure to hold previous terminal values(baudrate, no. of transmission/reception bits)



#define PREAMBLE        0x00
#define SOF1            0x00
#define SOF2            0xff
#define TX_TFI          0xd4
#define RX_TFI          0xd5
#define POSTAMBLE       0x00
#define TFI_SIZE        1
#define TAMA_SUCCESS    0
#define TAMA_FAILURE    -1
#define T_MAX           125000
/*-------------- PN531 Command Codes -------------*/
#define DIAGNOSE                0x00
#define GETFIRMWAREVERSION      0x02
#define GETGENERALSTATUS        0x04
#define READREGISTER            0x06
#define WRITEREGISTER           0x08
#define READGPIO                0x0C
#define WRITEGPIO               0x0E
#define SETSERIALBAUDRATE       0x10
#define SETTAMAPARAMETERS       0x12
#define SAMCONFIGURATION        0x14
#define POWERDOWN               0x16
#define RF_CONFIG               0x32
#define RF_INJUMPFORDEP         0x56
#define RF_INJUMPFORPSL         0x46
#define RF_INLISTPASSIVETARGET  0x4A
#define RF_INATR                0x50
#define RF_INPSL                0x4E
#define RF_INDATAEXCHANGE       0x40
#define RF_INCOMMUNICATETHRU    0x42
#define RF_INDESELECT           0x44
#define RF_INRELEASE            0x52
#define RF_INSELECT             0x54
/*------------------------------------------------*/
#ifdef TAMA_DEBUG

unsigned int  TEST_CNT;
unsigned char TEST_CHR;
unsigned char TEST_BUF[256];
#endif


/*-----------------------------------------------------------------------------------
Function: tama_open
Desc. :   Used to open the tama device
Inputs:   --None--
Output:   Returns opened file descriptor on success and < 1 on failure
-----------------------------------------------------------------------------------*/
int tama_open(void)
{

return -1;
}
/*-----------------------------------------------------------------------------------
Function: tama_close
Desc. :   Used to close the tama device
Inputs:   --None--
Output:   --None--
-----------------------------------------------------------------------------------*/
void tama_close(void)
{
}
/*-----------------------------------------------------------------------------------
Function: tama_compute_lcs
Desc. :   Used to compute data length checksum
Inputs:   data length
Output:   Returns the 2's compliment of the length field
-----------------------------------------------------------------------------------*/
unsigned char tama_compute_checksum(unsigned char Data)
{
	return -1;
}
/*-----------------------------------------------------------------------------------
Function: tama_compute_dcs
Desc. :   Compute 2's complement of data passed
Inputs:   Pointer to the data, whose checksum is tobe calculated, length of data
Output:   Returns the 2's compliment of all the data sent
-----------------------------------------------------------------------------------*/
unsigned char tama_compute_dcs(unsigned char* data, unsigned char dlen)
{
	return -1;
}
/*-----------------------------------------------------------------------------------
Function: tama_read_data
Desc. :   Used to read the said data from TAMA
Inputs:   Number of bytes to read
Output:   Stores the read data and returns 0 on success. Returns < 0 on failure
-----------------------------------------------------------------------------------*/
int tama_read_data(int Len)
{
	
	return -1;
}
/*-----------------------------------------------------------------------------------
Function: tama_process_buffer
Desc. :	  Used to traverse the read TAMA data and check for any error in response
Inputs:   --NONE--
Output:   Returns > 0  on success and < 0 on failure
-----------------------------------------------------------------------------------*/
int tama_process_buffer(void)
{
	
	return -1;
}
/*-----------------------------------------------------------------------------------
Function: tama_check_response
Desc. :   Used to check the TAMA response
Inputs:	  --NONE--
Output:   Returns > 0 on success and < 0 on failure
-----------------------------------------------------------------------------------*/
int tama_check_response(void)
{
	return -1;
}
/*-----------------------------------------------------------------------------------
Function: tama_send_command
Desc. :
Inputs:
Output:
-----------------------------------------------------------------------------------*/
int tama_send_command(unsigned char Cmd_Code, unsigned char *Data,  int Dlen)
{
	return -1;
}
/*----------------------------------------------------------------------------------
Function: tama_detectTarget
Desc. :   Used to detect the targets of RFID Card reader
Inputs:   Number of targets to detect(Max. 2), Address of memory to store number of
          Tags detected & Address of memory to store Tag ID
Output:   Number of Tags read/initialized is stored in the address passed to Tg_Detected.
          The read Tag is stored in location pointed by Tag ID pointer and returns 0
          on success. Returns -1 on failure
-----------------------------------------------------------------------------------*/
int tama_detectTarget(unsigned char Tg_Nos, unsigned char *Tg_Detected, unsigned char *Tg_ID)
{
	return -1;
}
/*-----------------------------------------------------------------------------------
Function: tama_authenticate_mifare
Desc. :   Authenticates a Tag's Block for writing/reading with the said key
Inputs:   Tag Number to authenticate(1 - Card 1, 2 - Card 2), Block address, Key, and
          Key type (Key A - 0x0A /Key B - 0x0B)
Output:   Returns 0 on success and < 1 on failure
-----------------------------------------------------------------------------------*/
int tama_authenticate_mifare(unsigned char Tg_No, unsigned char Blk_Addr, unsigned char *Key, unsigned char Key_Type)
{
	return -1;
}
/*-----------------------------------------------------------------------------------
Function: tama_halt_mifare
Desc. :   Halts (Deselects) a tag for access
Inputs:   Tag's logical ID
Output:   Returns 0 on success and < 1 on failure
-----------------------------------------------------------------------------------*/
int tama_halt_mifare(unsigned char Tg_LID)
{
	
	return -1;
}
/*-----------------------------------------------------------------------------------
Function: tama_read_target
Desc. :   Reads the block data and stores it into passed address
Inputs:   Block address to read, pointer to the data in buffer
Output:   Stores the read data from the card into the address pointed to by "Data_In"
          Returns the number of bytes read from the card.
-----------------------------------------------------------------------------------*/
int tama_read_target(unsigned char Blk_Addr, unsigned char *Data_In)
{
	return -1;
}
/*-----------------------------------------------------------------------------------
Function: tama_write_target
Desc. :   Writes the data sent to the said block
Inputs:   Block address to write, pointer to the data, length of data to write
Output:   Returns 0 on success and < 1 on failure
-----------------------------------------------------------------------------------*/
int tama_write_target(unsigned char Blk_Addr, unsigned char *Data_Out, int Dlen)
{
	
	return -1;
}
/*-----------------------------------------------------------------------------------
Function: tama_prepare_valueBlock
Desc. :   Used to prepare a Value Block and write that at the specified block
Inputs:   Block's address tobe prepared, Value (Shld be <= 9999), Address to build a 
          backup mechanism for the block
Output:   Returns 0 On success and < 0 on failure
-----------------------------------------------------------------------------------*/
int tama_prepare_valueBlock(unsigned char Blk_Addr, unsigned int Value, unsigned char Addr)
{

	return -1;
}
/*-----------------------------------------------------------------------------------
Function: tama_inc_dec_block
Desc. :   Used to increment/decrement a block with the value passed
Inputs:   increment/decrement ID, block number tobe incremented/decremented and the
          value
Output:   Returns 0 on success and < 0 on failure
-----------------------------------------------------------------------------------*/
int tama_inc_dec_block(unsigned char Inc_Dec, unsigned char Blk_Addr, unsigned int Value)
{
        return -1;
}
/*-----------------------------------------------------------------------------------
Function: tama_decrement_block
Desc. :   Used to decrement a block with the said value
Inputs:   Block number tobe decremented, Value
Output:   Returns 0 on success, < 0 on failure
-----------------------------------------------------------------------------------*/
int tama_decrement_block(unsigned char Blk_Addr, unsigned int Value)
{

	return -1;
}
/*-----------------------------------------------------------------------------------
Function: tama_increment_block
Desc. :   Used to increment a block with the said value
Inputs:   Block number tobe incremented, Value
Output:   Returns 0 on success, < 0 on failure
-----------------------------------------------------------------------------------*/
int tama_increment_block(unsigned char Blk_Addr, unsigned int Value)
{


        return -1;
}
/*-----------------------------------------------------------------------------------
Function: tama_transfer_block
Desc. :	  Used to transfer data from temporary register to a value block
Inputs:   Block Address to transfer
Output:   Returns 0 on success, and < 0 on failure
-----------------------------------------------------------------------------------*/
int tama_transfer_block(unsigned char Blk_Addr)
{
	
	return -1;
}
/*-----------------------------------------------------------------------------------
Function: tama_restore_block
Desc. :   Used to read the contents of a value block and store it in temporary data
          register
Inputs:   Block Address to restore
Output:   Returns 0 on success, and < 0 on Failure
-----------------------------------------------------------------------------------*/
int tama_restore_block(unsigned char Blk_Addr)
{
        return -1;
}
/*-----------------------------------------------------------------------------------
Function: tama_read_valueBlock
Desc. :   Used to read a value from a value block
Inputs:   Block to read, Address of location to store the read value
Output:   Returns 0 on success and < 0 on failure
-----------------------------------------------------------------------------------*/
 int tama_read_valueBlock(unsigned char Blk_Addr, unsigned int *Value)
{
		return -1;
}



/*-----------------------------------------------------------------------------------
Function: tama_release_atag
Desc. :   Used to forget an RFID Card.
Inputs:   Tag's logical ID
Output:   Returns 0 on success and < 0 on failure
-*-*- CAUTION: The card will be USELESS after this function call -*-*-
-----------------------------------------------------------------------------------*/
/*int tama_release_atag(unsigned char Tg_LID)
{
	unsigned char cmd_buf[3];
	
}*/


int RFFieldOff()


{



return -1;
}
