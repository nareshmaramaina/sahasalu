#include<stdio.h>
#include<stdint.h>

#define KEY_RESERVED		0
#define KEY_ESC			1
#define KEY_1			2
#define KEY_2			3
#define KEY_3			4
#define KEY_4			5
#define KEY_5			6
#define KEY_6			7
#define KEY_7			8
#define KEY_8			9
#define KEY_9			10
#define KEY_0			11
#define KEY_MINUS		12
#define KEY_EQUAL		13
#define KEY_BACKSPACE		14
#define KEY_TAB			15
#define KEY_Q			16
#define KEY_W			17
#define KEY_E			18
#define KEY_R			19
#define KEY_T			20
#define KEY_Y			21
#define KEY_U			22
#define KEY_I			23
#define KEY_O			24
#define KEY_P			25
#define KEY_LEFTBRACE		26
#define KEY_RIGHTBRACE		27
#define KEY_ENTER		28
#define KEY_LEFTCTRL		29
#define KEY_A			30
#define KEY_S			31
#define KEY_D			32
#define KEY_F			33
#define KEY_G			34
#define KEY_H			35
#define KEY_J			36
#define KEY_K			37
#define KEY_L			38
#define KEY_SEMICOLON		39
#define KEY_APOSTROPHE		40
#define KEY_GRAVE		41
#define KEY_LEFTSHIFT		42
#define KEY_BACKSLASH		43
#define KEY_Z			44
#define KEY_X			45
#define KEY_C			46
#define KEY_V			47
#define KEY_B			48
#define KEY_N			49
#define KEY_M			50
#define KEY_COMMA		51
#define KEY_DOT			52
#define KEY_SLASH		53
#define KEY_RIGHTSHIFT		54
#define KEY_KPASTERISK		55
#define KEY_LEFTALT		56
#define KEY_SPACE		57
#define KEY_CAPSLOCK		58
#define KEY_F1			59
#define KEY_F2			60
#define KEY_F3			61
#define KEY_F4			62
#define KEY_F5			63
#define KEY_F6			64
#define KEY_F7			65
#define KEY_F8			66
#define KEY_F9			67
#define KEY_F10			68
#define KEY_NUMLOCK		69
#define KEY_SCROLLLOCK		70
#define KEY_KP7			71
#define KEY_KP8			72
#define KEY_KP9			73
#define KEY_KPMINUS		74
#define KEY_KP4			75
#define KEY_KP5			76
#define KEY_KP6			77
#define KEY_KPPLUS		78
#define KEY_KP1			79
#define KEY_KP2			80
#define KEY_KP3			81
#define KEY_KP0			82
#define KEY_KPDOT		83

#define KEY_ZENKAKUHANKAKU	85
#define KEY_102ND		86
#define KEY_F11			87
#define KEY_F12			88
#define KEY_RO			89
#define KEY_KATAKANA		90
#define KEY_HIRAGANA		91
#define KEY_HENKAN		92
#define KEY_KATAKANAHIRAGANA	93
#define KEY_MUHENKAN		94
#define KEY_KPJPCOMMA		95
#define KEY_KPENTER		96
#define KEY_RIGHTCTRL		97
#define KEY_KPSLASH		98
#define KEY_SYSRQ		99
#define KEY_RIGHTALT		100
#define KEY_LINEFEED		101
#define KEY_HOME		102
#define KEY_UP			103
#define KEY_PAGEUP		104
#define KEY_LEFT		105
#define KEY_RIGHT		106
#define KEY_END			107
#define KEY_DOWN		108
#define KEY_PAGEDOWN		109
#define KEY_INSERT		110
#define KEY_DELETE		111
#define KEY_MACRO		112
#define KEY_MUTE		113
#define KEY_VOLUMEDOWN		114
#define KEY_VOLUMEUP		115
#define KEY_POWER		116	/* SC System Power Down */
#define KEY_KPEQUAL		117
#define KEY_KPPLUSMINUS		118
#define KEY_PAUSE		119
#define KEY_SCALE		120	/* AL Compiz Scale (Expose) */

#define KEY_KPCOMMA		121
#define KEY_HANGEUL		122
#define KEY_HANGUEL		KEY_HANGEUL
#define KEY_HANJA		123
#define KEY_YEN			124
#define KEY_LEFTMETA		125
#define KEY_RIGHTMETA		126
#define KEY_COMPOSE		127

#define KEY_STOP		128	/* AC Stop */
#define KEY_AGAIN		129
#define KEY_PROPS		130	/* AC Properties */
#define KEY_UNDO		131	/* AC Undo */
#define KEY_FRONT		132
#define KEY_COPY		133	/* AC Copy */
#define KEY_OPEN		134	/* AC Open */
#define KEY_PASTE		135	/* AC Paste */
#define KEY_FIND		136	/* AC Search */
#define KEY_CUT			137	/* AC Cut */
#define KEY_HELP		138	/* AL Integrated Help Center */
#define KEY_MENU		139	/* Menu (show menu) */
#define KEY_CALC		140	/* AL Calculator */
#define KEY_SETUP		141
#define KEY_SLEEP		142	/* SC System Sleep */
#define KEY_WAKEUP		143	/* System Wake Up */
#define KEY_FILE		144	/* AL Local Machine Browser */
#define KEY_SENDFILE		145
#define KEY_DELETEFILE		146
#define KEY_XFER		147
#define KEY_PROG1		148
#define KEY_PROG2		149
#define KEY_WWW			150	/* AL Internet Browser */
#define KEY_MSDOS		151
#define KEY_COFFEE		152	/* AL Terminal Lock/Screensaver */
#define KEY_SCREENLOCK		KEY_COFFEE
#define KEY_DIRECTION		153
#define KEY_CYCLEWINDOWS	154
#define KEY_MAIL		155
#define KEY_BOOKMARKS		156	/* AC Bookmarks */
#define KEY_COMPUTER		157
#define KEY_BACK		158	/* AC Back */
#define KEY_FORWARD		159	/* AC Forward */
#define KEY_CLOSECD		160
#define KEY_EJECTCD		161
#define KEY_EJECTCLOSECD	162
#define KEY_NEXTSONG		163
#define KEY_PLAYPAUSE		164
#define KEY_PREVIOUSSONG	165
#define KEY_STOPCD		166
#define KEY_RECORD		167
#define KEY_REWIND		168
#define KEY_PHONE		169	/* Media Select Telephone */
#define KEY_ISO			170
#define KEY_CONFIG		171	/* AL Consumer Control Configuration */
#define KEY_HOMEPAGE		172	/* AC Home */
#define KEY_REFRESH		173	/* AC Refresh */
#define KEY_EXIT		174	/* AC Exit */
#define KEY_MOVE		175
#define KEY_EDIT		176
#define KEY_SCROLLUP		177
#define KEY_SCROLLDOWN		178
#define KEY_KPLEFTPAREN		179
#define KEY_KPRIGHTPAREN	180
#define KEY_NEW			181	/* AC New */
#define KEY_REDO		182	/* AC Redo/Repeat */

#define KEY_F13			183
#define KEY_F14			184
#define KEY_F15			185
#define KEY_F16			186
#define KEY_F17			187
#define KEY_F18			188
#define KEY_F19			189
#define KEY_F20			190
#define KEY_F21			191
#define KEY_F22			192
#define KEY_F23			193
#define KEY_F24			194

#define KEY_PLAYCD		200
#define KEY_PAUSECD		201
#define KEY_PROG3		202
#define KEY_PROG4		203
#define KEY_DASHBOARD		204	/* AL Dashboard */
#define KEY_SUSPEND		205
#define KEY_CLOSE		206	/* AC Close */
#define KEY_PLAY		207
#define KEY_FASTFORWARD		208
#define KEY_BASSBOOST		209
#define KEY_PRINT		210	/* AC Print */
#define KEY_HP			211
#define KEY_CAMERA		212
#define KEY_SOUND		213
#define KEY_QUESTION		214
#define KEY_EMAIL		215
#define KEY_CHAT		216
#define KEY_SEARCH		217
#define KEY_CONNECT		218
#define KEY_FINANCE		219	/* AL Checkbook/Finance */
#define KEY_SPORT		220
#define KEY_SHOP		221
#define KEY_ALTERASE		222
#define KEY_CANCEL		223	/* AC Cancel */
#define KEY_BRIGHTNESSDOWN	224
#define KEY_BRIGHTNESSUP	225
#define KEY_MEDIA		226

#define KEY_SWITCHVIDEOMODE	227	/* Cycle between available video
					   outputs (Monitor/LCD/TV-out/etc) */
#define KEY_KBDILLUMTOGGLE	228
#define KEY_KBDILLUMDOWN	229
#define KEY_KBDILLUMUP		230

#define KEY_SEND		231	/* AC Send */
#define KEY_REPLY		232	/* AC Reply */
#define KEY_FORWARDMAIL		233	/* AC Forward Msg */
#define KEY_SAVE		234	/* AC Save */
#define KEY_DOCUMENTS		235

#define KEY_BATTERY		236

#define KEY_BLUETOOTH		237
#define KEY_WLAN		238
#define KEY_UWB			239

#define KEY_UNKNOWN		240

#define KEY_VIDEO_NEXT		241	/* drive next video source */
#define KEY_VIDEO_PREV		242	/* drive previous video source */
#define KEY_BRIGHTNESS_CYCLE	243	/* brightness up, after max is min */
#define KEY_BRIGHTNESS_ZERO	244	/* brightness off, use ambient */
#define KEY_DISPLAY_OFF		245	/* display device to off state */

#define KEY_WIMAX		246
#define KEY_RFKILL		247	/* Key that controls all radios */

/* Code 255 is reserved for special needs of AT keyboard driver */







#define MATRIX_MAX_ROWS         32
#define MATRIX_MAX_COLS         32

#define KEY(row, col, val)      ((((row) & (MATRIX_MAX_ROWS - 1)) << 24) |\
		(((col) & (MATRIX_MAX_COLS - 1)) << 16) |\
		((val) & 0xffff))

#define KEY_ROW(k)              (((k) >> 24) & 0xff)
#define KEY_COL(k)              (((k) >> 16) & 0xff)
#define KEY_VAL(k)              ((k) & 0xffff)
#define MATRIX_SCAN_CODE(row, col, row_shift)   (((row) << (row_shift)) + (col))

static const uint32_t mx6sl_gpio_matrix_keymap[] = 
{
KEY(0, 0, KEY_Q),KEY(0, 1, KEY_I),KEY(0, 2, KEY_G),KEY(0, 3, KEY_C),KEY(0, 4, KEY_TAB),KEY(0, 5, KEY_4),KEY(0, 6, KEY_8),KEY(0, 7, KEY_ENTER),
KEY(1, 0, KEY_W),KEY(1, 1, KEY_O),KEY(1, 2, KEY_H),KEY(1, 3, KEY_V),KEY(1, 4, KEY_1),KEY(1, 5, KEY_5),KEY(1, 6, KEY_9),KEY(1, 7, KEY_RESERVED),
KEY(2, 0, KEY_E),KEY(2, 1, KEY_P),KEY(2, 2, KEY_J),KEY(2, 3, KEY_B),KEY(2, 4, KEY_2),KEY(2, 5, KEY_6),KEY(2, 6, KEY_RIGHT),KEY(2, 7,KEY_RESERVED),
KEY(3, 0, KEY_R),KEY(3, 1, KEY_A),KEY(3, 2, KEY_K),KEY(3, 3, KEY_N),KEY(3, 4, KEY_3),KEY(3, 5, KEY_BACKSPACE),KEY(3, 6, KEY_END),KEY(3, 7, KEY_RESERVED),
KEY(4, 0, KEY_T),KEY(4, 1, KEY_S),KEY(4, 2, KEY_L),KEY(4, 3, KEY_M),KEY(4, 4, KEY_ESC),KEY(4, 5, KEY_LEFT),KEY(4, 6, KEY_RESERVED),KEY(4, 7, KEY_RESERVED),
KEY(5, 0, KEY_Y),KEY(5, 1, KEY_D),KEY(5, 2, KEY_Z),KEY(5, 3, KEY_RIGHTSHIFT),KEY(5, 4, KEY_DOWN),KEY(5, 5, KEY_HOME),KEY(5, 6, KEY_0),KEY(5, 7, KEY_RESERVED),
KEY(6, 0, KEY_U),KEY(6, 1, KEY_F),KEY(6, 2, KEY_X),KEY(6, 3, KEY_UP),KEY(6, 4, KEY_INSERT),KEY(6, 5, KEY_7),KEY(6, 6, KEY_SPACE),KEY(6, 7, KEY_RESERVED),
//KEY(7, 0, KEY_MINUS),KEY(7, 1, KEY_MINUS),KEY(7, 2, KEY_EQUAL),KEY(7, 3, KEY_EQUAL),KEY(7, 4, KEY_LEFTBRACE),KEY(7, 5, KEY_LEFTBRACE),KEY(7, 6, KEY_RIGHTBRACE),KEY(7, 7, KEY_RESERVED),
KEY(7, 0, KEY_MINUS),KEY(7, 1, KEY_RIGHTBRACE),KEY(7, 2, KEY_APOSTROPHE),KEY(7, 3, KEY_SLASH),KEY(7, 4, KEY_TAB),KEY(7, 5, KEY_F4),KEY(7, 6, KEY_F8),KEY(7, 7, KEY_RESERVED),
KEY(8, 0, KEY_MINUS),KEY(8, 1, KEY_RIGHTBRACE),KEY(8, 2, KEY_APOSTROPHE),KEY(8, 3, KEY_SLASH),KEY(8, 4, KEY_F1),KEY(8, 5, KEY_F5),KEY(8, 6, KEY_F9),KEY(8, 7, KEY_RESERVED),
KEY(9, 0, KEY_EQUAL),KEY(9, 1, KEY_BACKSLASH),KEY(9, 2, KEY_COMMA),KEY(9, 3, KEY_GRAVE),KEY(9, 4, KEY_F2),KEY(9, 5, KEY_F6),KEY(9, 6, KEY_RIGHT),KEY(9, 7,KEY_RESERVED),
KEY(10, 0, KEY_EQUAL),KEY(10, 1, KEY_BACKSLASH),KEY(10, 2, KEY_COMMA),KEY(10, 3, KEY_GRAVE),KEY(10, 4, KEY_F3),KEY(10, 5, KEY_BACKSPACE),KEY(10, 6, KEY_END),KEY(10, 7, KEY_RESERVED),
KEY(11, 0, KEY_LEFTBRACE),KEY(11, 1, KEY_SEMICOLON),KEY(11, 2, KEY_DOT),KEY(11, 3, KEY_RESERVED),KEY(11, 4, KEY_ESC),KEY(11, 5, KEY_LEFT),KEY(11, 6, KEY_RESERVED),KEY(11, 7, KEY_RESERVED),
KEY(12, 0, KEY_LEFTBRACE),KEY(12, 1, KEY_SEMICOLON),KEY(12, 2, KEY_DOT),KEY(12, 3, KEY_RIGHTSHIFT),KEY(12, 4, KEY_DOWN),KEY(12, 5, KEY_HOME),KEY(12, 6, KEY_F10),KEY(12, 7, KEY_RESERVED),
KEY(13, 0, KEY_RESERVED),KEY(13, 1, KEY_RESERVED),KEY(13, 2, KEY_RESERVED),KEY(13, 3, KEY_UP),KEY(13, 4, KEY_INSERT),KEY(13, 5, KEY_F7),KEY(13, 6, KEY_SPACE),KEY(13, 7, KEY_RESERVED),
};

//static struct matrix_keymap_data mx6sl_matrix_gpio_keymap_data = {

int main()
{
	unsigned short *keycodes;
	unsigned int row_shift,key;
	int i,n;
	row_shift = 3 ;
	
	keycodes = malloc((14 << row_shift) * sizeof(*keycodes));
	n = sizeof(mx6sl_gpio_matrix_keymap)/sizeof(mx6sl_gpio_matrix_keymap[0]);
	printf(" n = %d\n",n);
	for (i = 0; i < n; i++) {
		unsigned int key = mx6sl_gpio_matrix_keymap[i];
		unsigned int row = KEY_ROW(key);
		unsigned int col = KEY_COL(key);
		unsigned short code = KEY_VAL(key);
		//printf(" MATRIX_SCAN_CODE(row, col, row_shift) = %d \n",MATRIX_SCAN_CODE(row, col, row_shift));
		keycodes[MATRIX_SCAN_CODE(row, col, row_shift)] = code;
		printf("\t%x\n",key);
//		  printf ("row = %d\tcol = %d\tcode = %d\tkeycode[%d] = %d\t\ti = %d\tkey = %x \n",row,col,code,i,keycodes[code],i,key) ;
//		  PrintAllBits(key);
	}

	return 0;
}
int PrintAllBits(int num)
{
        int i=0;
        for(i= ( sizeof(int)*8) -1; i>=0 ; i-- )
                printf("%d ", (( num>>i ) & 1 ) );
        printf("\n");
        return 0;
}

