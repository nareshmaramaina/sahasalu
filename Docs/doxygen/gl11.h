/** @file gl11.h
 * GL11POS APIs and Definitions
 *
 * Company Name: Linkwell Telesystems Pvt. Ltd (visiontek.co.in).
 * API Description: GL11POS LCD, Keypad, RTC, Printer, Magnetic Swipe, SAM, IFD, Barcode, Audio, USB, Camera, GSM, GPS, Ethernet, WiFi, Bluetooth and Version APIs.
 */

/**
 * @file gl11.h
 * @authors RAVIKUMAR.K
 */

#ifndef GL11_H
#define GL11_H

/** @defgroup A IODEVS Module Header.
 * @{
 */

/** @brief 
 *	This API Function is used to open io control devices.
 * Note: This function must be called before calling any API started with gl11_ prefix functions.
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_iodev_open(void);

/** @brief
 *	This API Function is used to close io control devices. 
 * Note: This function must be called after any LCD and Keypad,buzzer functions.
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_iodev_close(void);

/** @brief
 *	This API used to change the lcd contrast.
 * @param chngval
 *	Description: variable to be passed to change the contrast.
 *	Type: Input
 *	Range: 0 to 31
 *
 * @return
 *	 0 on Success,
 *	-1 on Failure and
 *	-2 Argument Error.
*/
int gl11_lcd_contrast(int chngval);

/** @brief
 *	This API used to change the lcd brightness.
 * @param chngval
 *	Description: variable to be passed to change the brightness.\n
 *	Type: Input
 *	Range: 0 to 127
 *
 * @return
 *	 0 on Success,
 *	-1 on Failure and
 *	-2 Argument Error.
 */
int gl11_lcd_brightness(int chngval);

/** @brief
 *	This API used to set default lcd contrast brightness.
 *
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_lcd_default(void);

/** @brief
 *	This API used to set backlight timeout.
 * @param val
 *	Description: variable to be used to change backlight time out value.
 *	Type: Input
 *	Range: 16 to 90
 * @return 
 *	 0 on Success,
 *	-1 on Failure and
 *	-2 Argument Error.
 */
int gl11_lcdbklt_time_duration(int val);

/** @brief
 *	This API used to On the backlight.
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_lcdbklt_on(void);

/** @brief
 *	This API used to OFF the backlight.
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_lcdbklt_off(void);

/** @brief
 *	This API used to OFF the buzzer sound.
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_buzz_off(void);

/** @brief
 *	This API used to On the buzzer sound.
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_buzz_on(void);

/** @brief
 *	This API used to Off the keypad buzzer sound.
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_keypad_buzz_off(void);

/** @brief
 *	This API used to ON the keypad buzzer sound.
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_keypad_buzz_on(void);

/** @brief
 *	This API used to Off the Touch buzzer sound.
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_touch_buzz_off(void);

/** @brief
 *	This API used to On the Touch buzzer sound.
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_touch_buzz_on(void);

/** @brief
 *	This API used to On the GSM Modem reset.
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_modem_reset(void);

/** @brief
 *	This API used to set gsm_usb power control.
 * @param val
 *	Description: variable to be used to gsm_usb power control.
 *	Type: Input
 *	Range: 0 and 1
 * @return
 *	 0 on Success,
 *	-1 on Failure and
 *	-2 Argument Error.
 */
int gl11_gsm_usb_pwr_cntrl(int val);

/** @brief
 *	This API function is used to Poweron or Power off Camera Module.
 * @param val:
 *	Description: Camera power on or Power Off. 
 *	Type: Input
 *  	Range: 0- For power off and 1- For power on.
 * @return
 *	 0 on Success,
 *	-1 Failure and
 *	-2 Argument Error.
 */
int gl11_cam_control(int val);
 
/** @brief
 *	This API function is used to Poweron Camera flash.
 * @param val
 *	Description: Camera flash poweron or Power Off.
 *	Type: Input
 *  	Range: 0- For power off and 1- For power on.
 * @return
 *	 0 on Success,
 *	-1 Failure and
 *	-2 Argument Error.
 */
int gl11_internal_camflash(int val);

/** @brief
 *	This API function is used to Poweron or Poweroff IFD Module.
 * @param val
 *	Description: IFD power on or Power Off.
 *	Tepe: Input
 *	Range: 0- For power off and 1- For power on.
 * @return
 *	 0 on Success,
 *	-1 Failure and
 *	-2 Argument Error.
 */
int gl11_ifd_control(int val);

/** @brief
 *	This API function is used to Poweron or Poweroff SAM Module.
 * @param val
 *	Description: SAM power on or Power Off.
 *	Tepe: Input
 *	Range: 0- For power off and 1- For power on.
 * @return
 *	 0 on Success,
 *	-1 Failure and
 *	-2 Argument Error.
 */
int gl11_sam_pwr_ctrl(int val);

/** @brief
 *	This API function is used to Poweron or Poweroff Bluetooth Module.
 * @param val
 *	Description: Bluetooth power on or Power Off.
 *	Tepe: Input
 *	Range: 0- For power off and 1- For power on.
 * @return
 *	 0 on Success,
 *	-1 Failure and
 *	-2 Argument Error.
 */
int gl11_bluetooth_control(int val);

/** @brief
 *	This API is used to get battery and adapter status.
 * @param Apresent
 *	Description: Pointer variables to be passed to get the status of Adapter.
 *	Type: Output
 *	Range: 1 if adapter present and 0 if not present.
 *@param Bpresent
 *	Description: Pointer variables to be passed to get the status of Battery.
 *	Type: Output
 *	Range: 0 indicates need to charge the battery and 1 indicates battery is filled.
 * @param Bvolts
 *	Description: To get the battery voltage.
 *	Type: Output
 *	Range: Raw Value.
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_GetBatteryInfo(int *Apresent, int *Bpresent, int *Bvolts);

/**
 * @}
 */


/** @defgroup B RTC Module Header.
 * @{
 */

/** @brief
 *	This API Function gets the time from the RTC chip or from the OS if already set.
 * @param *dt
 *	Description: A pointer to tm structure(time.h) The API call populates this structure.
 *	Type: Output
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_getrtc(struct tm *dt);

/** @brief
 *	This API function sets the time to the RTC chip as well as for OS.
 * @param *dt
 *	Description: A pointer to tm structure(time.h) The API call populates this structure.
 *	Type: Input
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_setrtc(struct tm *dt);

/**
 * @}
 */


/** @defgroup C Printer Module Header.
 * @{
 */

/** @brief
 *	This API Function is used to open the printer device.
 * @note
 *	This function must be called before any printer function.
 * @return
 *	 1 on Success,
 *	 2 if the device is Already Opened and
 *	-1 on Failure.
 */
int prn_open(void);

/** @brief
 *	This API Function is used to close the printer device.
 * @return
 *	 1 if the device Closed Successfully and
 *	-1 if the device is Failure in Closing.
 */
int prn_close(void);

/** @brief
 *	This API Function is used to detect paper presence status.
 * @return
 *	 0 on Success and
 *	-2 on Error.
 */
int prn_paperstatus(void);

/** @brief
 *	This API Function is used printer Platen Switch(LID) is Open or Close.
 * @return
 *	 0 on Success(Lid Close) and
 *	-2 on Failure(Lid Open).
 */
int prn_lid_status(void);

/** @brief
 *	This API Function is used to advance the paper(move the paper in advance of given no.of lines).
 * @param scanlines
 *	Description: scanlines is to be passed as parameter (1 text line is equal to 17 scan lines).
 *	Type: INPUT
 *	Range: 1 to 50
 * @return
 *	 0 on Success,
 *	-1 if Error occurs,
 *	-2 if the length is more or less,
 *	-3 NO Paper,
 *	-4 Low Battery,
 *	-5 Max Temp,
 *	-6 No Lines and
 *	-7 WRITE Error.
 */
int prn_paper_feed(int scanlines);

/** @brief
 *	This API Function is used to prints the text.
 * @param *text
 *	Description: pointer to the buffer from which the text to be printed.
 *	Type: INPUT
 * @param len
 *	Description: length of the text.
 *	Type: INPUT
 * @param font
 *	Description: font of the the text presently there are two fonts are supported.(1 and 2 fonts).
 *	Type: INPUT
 * @return
 *	 0 on Success,
 *	-1 if the device not Opened,
 *	-2 if the length is more,
 *	-3 NO Paper,
 *	-4 Low Battery,
 *	-5 Max Temp,
 *	-6 No Lines and
 *	-7 WRITE Error.
 */
int prn_write_text(unsigned char *text, int len, int font);

/** @brief
 *	This API Function is used to print bmp data.
 * @param *bitmap
 *	Description: pointer to the buffer from which the data to be printed.The image size is 384x480 pixels.
 *	Type: INPUT
 * @param len
 *	Description:Length of the text.
 *	Type: INPUT
 * @return
 *	 0 no. of characters written on Success,
 *	-1 if Error Occurs or Device not Open,
 *	-2 if the length is more,
 *	-3  NO Paper,
 *	-4 Low Battery,
 *	-5 Max temp,
 *	-6 No Lines and
 *	-7 WRITE_Error.
 */
int prn_write_bmp(unsigned char *bitmap, long len);

/**
 * @}
 */


/** @defgroup D Magswipe Device Module Header.
 * @{
 */

/** @brief
 *	This API Function is used to open magswipe device. 
 * @note
 *	This function must be called before any magswipe function.
 * @return
 *	 1 on Success,
 *	 2 on Already Open and
 *	-1 on Failure.
 */
int mscr_open(void);

/** @brief 
 *	This API Function is to close magnetic swipe device.
 * @return
 *	 1 on Success and
 *	-1 on Failure.
 */
int mscr_close(void);

/** @brief 
 *	This API Function is used to check wether the device is having valid data(both track1 and track2 data).
 * @return
 *	 1 on Success and
 *	-1 if there is no Valid Data.
 */
int mscr_getstate(void);

/** @brief
 *	This API function reads the data of the tracks from the card.
 * @param *track_1_data, *track_2_data, *track_3_data 
 *	Description: Pointers to the buffers,where tracks data are copied to the passed buffers,these track1,track2 and track3 are character pointer data types and the memory allocated to them should be length of the expected data+1(suggested 256 bytes each).
 *	Type: INPUT
 *	Range: 256 bytes
 * @return
 *	 1 if only track1 data is valid and copied data into track_1_data buffer,
 *	 2 if only track2 data is valid and copied data into track_2_data buffer,
 *	 3 if only track2 data is valid and copied data into track_3_data buffer,
 *	 4 if track 1 & 2 are valid and copied data into track_1_data buffer & track_2_data buffer,
 *	 5 if track 2 & 3 are valid and copied data into track_2_data buffer & track_3_data buffer,
 *	 6 if track 1 & 3 are valid and copied data into track_1_data buffer & track_3_data buffer,
 *	 7 if track 1, 2 & 3 are valid and copied into all three buffers and
 *	-1 if there is no valid data of all three tracks or Device not Opened.
 */
int mscr_read(char *track_1_data, char *track_2_data, char *track_3_data);

/** @brief
 *	This API Function clears the card reader device buffer.
 * @return
 *	 1 on Success and
 *	-1 on Failure or May be Device not Open.
 */
int mscr_flush(void);

/**
 * @}
 */


/** @defgroup E IFD Module Header. 
 * @{
 */

/** @brief
 *	This function checks for the existence of the IFD card reader device and if found prepares it for further communication.Before attempting any operations related to Sam card reader device this function should be called. 
 * @note
 *	Backward compatabilty with IFD API's are also existed.
 * @return
 *	>0 on Success and
 *	<0 on Error.
 */
int scr_open(void);

/** @brief
 *	This function closes the IFD device. After finishing all the operations related to IFD card reader this function should get called.
 * @return
 *	 0 on Success.
 */
int scr_close(void);

/** @brief
 *	This API is to select the IFD card slot.
 * @param card
 *	Description: 1 - External IFD Card and 2 - internal IFD Card.
 *	Type: INPUT
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int select_card(int card);

/** @brief
 *	This API is to power up the card in 5 Volts.
 * @return
 *	 0 on Success,
 *	 1 on Write Error and
 *	-1 on Failure.
 */
int powerup_5v(void);

/** @brief
 *	This API is to power up the card in 3 Volts.
 * @return
 *	 0 on Success,
 *	 1 on Write Error and
 *	-1 on Failure.
 */
int powerup_3v(void);

/** @brief
 *	This API is to power up the card in 1.8 Volts.
 * @return
 *	 0 on Success,
 *	 1 on Write Error and
 *	-1 on Failure.
 */
int powerup1_8v(void);

/** @brief
 *	This API reads ATR(Answer to The Response) from the card.
 * @param *Aresp
 *	Description: Buffer which holds ATR response from the card.
 *	Type: OUTPUT
 * @param *Alen
 *	Description: Length of ATR from card in bytes.
 *	Type: OUTPUT
 * @return
 *	 0 on Success and
 *	-1 on Error 'if unable to receive ATR or if card is not present in slot'.
 */
int SCR_getATR(unsigned char *Aresp, unsigned int *Alen);

/** @brief
 *	This API is used to check the card presence in Selected Slot.
 * @return
 *	11 for card Presence,
 *	12 for card Absence and
 *	-1 for Error.
 */
int SCR_Checkup_CardPresence(void);

/** @brief
 *	This API is used to send all the EMV compatible CAPDUs to the card. The API sends the command contained in CAPDU Data buffer and gives the response and its length out through RAPDU Data and RLen variables respectively.
 * @param *Cmd
 *	Description:Buffer holding the command APDU in the standard format.
 *	Type:INPUT
 * @param CLen
 *	Description:length of the CAPDU Data buffer.
 *	Type:INPUT
 * @param *Resp
 *	Description:Buffer to hold the response APDU in the standard format.
 *	Type:OUTPUT
 * @param *RLen
 *	Description:variable to hold response length. 
 *	Type:OUTPUT
 * @return
 *	 0 on Success and
 *	-1 on Error. 
 */
int SCR_SendCommand(unsigned char *Cmd, int CLen, unsigned char *Resp, unsigned int *RLen);

/** @brief
 *	This API is used to Power down the IFD cards.
 * @return
 *	 0 on Success and 
 *	-1 on Failure.
 */
int powerdown(void);

/** @brief
 *	This API is used to get SCR Firmware Version number.
 * @param *Fresp
 *	Description: Buffer to hold the response APDU in the standard format.
 *	Type: OUTPUT
 * @param *Flen
 *	Description: variable to hold response length.
 *	Type: OUTPUT
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int SCR_GetFV(unsigned char *Fresp, unsigned int *Flen);

/** @brief
 *	This API is used to get SCR Software Build number.
 * @param *Sresp
 *	Description: Buffer to hold the response APDU in the standard format.
 *	Type: OUTPUT
 * @param *Slen
 *	Description: variable to hold response length.
 *	Type: OUTPUT
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int SCR_GetSB(unsigned char *Sresp, unsigned int *Slen);

/**
 * @}
 */


/** @defgroup F SAM Module Header.
 * @{
 */

/** @brief
 *	This function checks for the existence of the Sam card reader device and if found prepares it for further communication. Before attempting any operations related to Sam card reader device this function should be called. 
 *
 * @return      
 *	 0 on Success and
 *	-1 on Failure.
 */
int SAM_Open(void);

/** @brief
 *	This function closes the SAM device. After finishing all the operations related to SAM card reader this function should get called.
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int SAM_Close(void);

/** @brief
 *	This API reads ATR from the card.
 * @param *length
 *	Description: length  of ATR from card in bytes.
 *	Type: Output 
 * @param *buffer
 *	Description: pointer to buffer which holds ATR response from the card.
 *	Type: Output
 *
 * @return
 *	 0 on Success and
 *	-1 on Error 'if unable to receive ATR this happens only if card is not present in slot'.
 */
int SAM_GetAtr(unsigned int *length, unsigned char *buffer);

/** @brief
 *	This API is used to send all the EMV complaint CAPDUs to the card. The API call sends the command contained in CAPDU Data buffer and gives the response and *its length out through RAPDU Data and RLen variables respectively.
 *
 * @param *CAPDU_Data
 *	Description: Buffer holding the command APDU in the standard format.
 *	Type: Input
 *
 * @param CLen
 *	Description: length of the CAPDU Data buffer.
 *	Type: Input
 *
 * @param *RAPDU_Data
 *	Description: Buffer to hold the response APDU in the standard format.
 *	Type: Output
 *
 * @param RLen
 *	Description: variable to hold response length. 
 *	Type: Output
 *
 * @return
 *	 0 on Success and
 *	-1 on Failure 'communication error occurred and the device is closed'.
 *
 */
int SAM_SendCommand(unsigned char *CAPDU_Data, unsigned int CLen, unsigned char *RAPDU_Data, unsigned int *RLen);

/** @brief
 *	This API is to power up the card,after this call Vcc is applied as selected during card select API. After this call only we can do any command operations on card.
 *
 * @param selection
 *	Description: 1- card1 1.8v, 2- card1 3v, 3- card1 5v, 4- card2 1.8v, 5- card2 3v and 6- card3 5v.
 *	Type: Input
 *
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 *
 */
int SAM_ColdReset(int selection);

/**
 * @}
 */


/** @defgroup G Barcode Module Header.
 * @{
 */

/** @brief
 *	This API Function is used to open barcode device.
 * @note
 *	This function must be called before any barcode function.
 * @return
 *	 0 on Success and
 *	-1 on Failure. 
 */
int bar_code_open(void);

/** @brief
 *	This API Function reads the barcode.
 * @param *rxbuf
 *	Description: buffer used to store barcode data.
 *	Type: output
 *	Range: 0 - 256
 * @param len
 *	Description:len means size of data to receive(receive buffer size).
 *	Type: input
 *	Range: 0 - 256
 * @return
 *	>0 on Success and
 *	-1 on Error.
 */
int bar_code_read(unsigned char *rxbuf, int len);

/** @brief 
 *	This API Function closes the barcode.
 * @return
 *	 0 on Success and
 *	-1 on Error.
 */
int bar_code_close(void);

/**
 * @}
 */


/** @defgroup H Audio Module Header. 
 * @{
 */

/** @brief 
 *	This API Function is used to power on audio device.
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_audio_power_on(void);

/** @brief
 *	This API Function is used to power off audio device.
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_audio_power_off(void);

/** @brief
 *	This API function is used to control Audio Volume.
 * @param val:
 *	Description: Audio Volume control
 *	Type: Input
 *	Range: 130-190 
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_audio_vol_control(int val);

/**
 * @}
 */


/** @defgroup I USB-HOST Module Header. 
 * @{
 */

/** @brief 
 *	This API Function is used to power on usb-host device.
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_host_pwron(void);

/** @brief 
 *	This API Function is used to power off usb-host device.
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_host_pwroff(void)

/** @brief 
 *	This API Function is used to power on optcap(Finger Print) device.
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_optcap_pwron(void);

/** @brief 
 *	This API Function is used to power off optcap(Finger Print) device.
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_optcap_pwroff(void);

/**
 * @}
 */


/** @defgroup J Gsm_Gprs module header 
 * @{ 
 */

/** @brief
 *	This API Function used to Select gsm Card1 or Card2.
 * @param sel
 *	Description: Select card1 or card2.
 *	Type: Input
 *	Range: '1' - card1 and '2' - card2.
 * @param baudrate
 *	Description: Open gsm modem with given Baudrate.
 *	Type: Input
 *	Range: Preferably '9600' or 115200.
 * @return
 *	 0 on Success.
 *	-1 on Error(AT command response),
 *	-2 on Arguments Error,
 *	-3 Sim Not Present and
 *	-4 on Gsm Port not Found(Please Call gl11_gsm_select Function).
 */
int gl11_gsm_select(int sel, int baudrate);

/** @brief
 *	This API function is used to power off the gsm module.
 * @return
 *	 0 on Success.
 */
int gl11_gsm_pwroff(void);

/** @brief
 *	This API is used to get the response from  AT Commands.
 * @note
 *	Some commands works with sim card and some commands works with-out sim card and returns Error. This API give Response slow.
 * @param *Cmd
 *	Description: These are the Cmd parameters(AT Commands) passsed to Gsm modem(Ex:AT+CPIN?, AT+CPOS?, AT+CREG? and etc,.).
 *	Type: Input
 * @param *Resp
 *	Description: This parameter fills the Gsm modem with the response of AT commands(Passed in the first parameter).
 *	Type: Output
 * @param *Ans[]
 *	Description: This parameter(Expectation of AT Command Response) passsed to Gsm modem(Ex:OK, ERROR, NO CARRIER and etc,.), This parameter fills the Gsm modem with the response of AT commands(Passed in the first parameter).
 *	Type: Output
 * @param Tout
 *	Description: This parameter is used to set the timeout for GSM module to get the response.
 *	Type: Input
 * @return
 *	 3 on NO CARRIER,
 *	 2 on NO DIALTONE,
 *	 1 on Command Response Error,
 *	 0 on Success (>0 Return Value for Depends on Passing 3rd Argument),
 *	-1 on Failure,
 *	-2 on Time out and
 *	-4 on Gsm Port not Found(Please Call gl11_gsm_select Function).
 */
int gl11_gsmatcmd_response(char *Cmd, char *Resp, char *Ans[], int Tout);

/**
 * @}
 */


/** @defgroup K Version Module Header.
 * @{
 */

/** @brief
 *	This API used to get the Serial number.
 * @param *Uid
 *	Description: Variable buffer to be passed to get the Serial number.
 *	Type: Output
 *	Range: 16 Characters(bytes).
 *
 * @return 
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_getuid(char *Uid);

/** @brief
 *	This API function is used to get the PIN PAD ID. (Pre Requirements: This id should be set at u-boot prompt before call this API do like as: VISIONTEK> setenv machineid 1234567890 then VISIONTEK> saveenv).
 * @param *machineid
 *	Description: Read machine ID of 10 digits from u-boot environment variables.
 *	Type: Output
 *	Range: 10 digits (bytes).
 * @return Return Values
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_getpinpadid(char *machineid);

/** @brief
 *	This API function is used to get the Hardware ID. (Pre Requirements: This id should be set at u-boot prompt before call this API do like as: VISIONTEK> setenv hwid 87654321 then VISIONTEK> saveenv).
 * @param *hwid
 *	Description: Read Hardware ID of 8 digits from u-boot environment variables.
 *	Type: Output
 *	Range: 8 digits (bytes).
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_gethwid(char *hwid);

/** @brief
 *	This API function is used to get the MAC ID(8C:89:A5:EB:8E:9C).
 * @param *macid
 *	Description: Buffer which holds MAC ID details.
 *	Type: Output
 *	Range: 17 characters(bytes).
 * @return
 *	 0 on Success and
 *	-1 on Failure.
 */
int gl11_getmacid(har *macid);

/** @brief 
 *	This API Function used to get bootloader version details.
 * @param *Bver
 *	Description: Buffer which holds uboot version details.
 *	Type: Output
 * @return
 *	 0 on Success and
 *	-1 on Error.
 */
int bootloader_details(char *Bver);

/** @brief 
 *	This API Function used to get kernel version details.
 * @param *Kver
 *	Description: Buffer which holds kernel version details.
 *	Type: Output
 * @return
 *	 0 on Success and
 *	-1 on Error.
 */
int kernel_details(char *Kver);

/** @brief 
 *	This API Function used to get rootfs version details.
 * @param *Rver
 *	Description: Buffer which holds rootfs version details.
 *	Type: Output
 * @return
 *	 0 on Success and
 *	-1 on Error.
 */
int rootfs_details(char *Rver);

/**
 * @}
 */

#endif 

