/*
 * savegame_manager: a tool to backup and restore savegames from Nintendo
 *  DS cartridges. Nintendo DS and all derivative names are trademarks
 *  by Nintendo. EZFlash 3-in-1 is a trademark by EZFlash.
 *
 * strings.cpp: Localised message strings
 *
 * Copyright (C) Pokedoc (2010)
 */
/* 
 * This program is free software; you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation; either version 2 of the License, or 
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License 
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with this program; if not, write to the Free Software Foundation, Inc., 
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
/*
  This file implements the functions and data structures required for localised messages.
 */


#include "strings.h"
#include "libini.h"
#include <nds.h>
#include "fileselect.h"

using namespace std;

// a global string array
char **message_strings;
char txt[512];

#define ADD_STRING(id,text)	strcpy(txt,text);\
	message_strings[id] = new char[strlen(txt)+1];\
	memcpy(message_strings[id], txt, strlen(txt)+1);


bool stringsLoadFile(const char *fname)
{
#define NOT_FINISHED

#ifndef NOT_FINISHED
	// load ini file...
	ini_fd_t ini = 0;
	if (fileExists(fname))
		ini = ini_open(fname, "r", "");
	else
		return false;
#endif

	message_strings = new char*[STR_LAST];
#ifndef NOT_FINISHED
	ini_locateHeading(ini, "");
	char txt[512];
	for (int i = 0; i < STR_LAST; i++) {
		sprintf(txt, "%i", i);
		ini_locateKey(ini, txt);
		ini_readString(ini, txt, 512);
		message_strings[i] = new char[strlen(txt)+1];
		memcpy(message_strings[i], txt, strlen(txt)+1);
	}

	// delete temp file (which is a remnant of inilib)
	remove("/tmpfile");
#else
	ADD_STRING(STR_HW_SWAP_CARD,"Please take out Slot 1\nflash card and insert a game\n\nPress A when done.");
	//
	ADD_STRING(STR_HW_SELECT_FILE,"Please select a .sav file.");
	ADD_STRING(STR_HW_SELECT_FILE_OW,"Please select a file to\noverwrite, or press L+R in afolder to create a new file.");
	ADD_STRING(STR_HW_SEEK_UNUSED_FNAME,"Please wait... searching for\nan unused filename.\n\nTrying: %s");
	ADD_STRING(STR_ERR_NO_FNAME,"ERROR: Unable to get an\nunused nfilename! This means that you have more than\n65536 saves!\n\n(wow!)");
	//
	ADD_STRING(STR_HW_FORMAT_GAME,"Preparing to write to your\ngame. Please wait...");
	ADD_STRING(STR_HW_WRITE_GAME,"Writing the save to your\ngame. Please wait...");
	//
	ADD_STRING(STR_HW_3IN1_FORMAT_NOR,"Preparing to write to the\n3in1. Please wait...");
	ADD_STRING(STR_HW_3IN1_WRITE_NOR,"Writing save data to the\n3in1. Please wait...");
	ADD_STRING(STR_HW_3IN1_PREPARE_REBOOT,"Preparing reboot...");
	ADD_STRING(STR_HW_3IN1_PLEASE_REBOOT,"Save has been written to\nthe 3in1. Please power off\nand restart this tool.");
	ADD_STRING(STR_HW_3IN1_CLEAR_FLAG,"Preparing to dump your\nsave... Please wait...");
	ADD_STRING(STR_HW_3IN1_DUMP,"Dumping the save from the\n3in1 to your flash card.\nFilename:\n%s");
	ADD_STRING(STR_HW_3IN1_DONE_DUMP,"Done. Your game save has\nbeen dumped using your\n3in1. Filename:\n%s\n\nPlease restart your DS.");
	ADD_STRING(STR_HW_3IN1_RESTORE,"Done. Your game save has\nbeen restored using your\n3in1.\n\nPlease restart your DS.");
	//
	ADD_STRING(STR_HW_FTP_SLOW,"FTP is slow, please wait...");
	//
	ADD_STRING(STR_HW_WARN_DELETE,"This will WIPE OUT your\nentire save! ARE YOU SURE?\n\nPress R+up+Y to confim!");
	ADD_STRING(STR_HW_DID_DELETE,"Done. Your game save has\nbeen PERMANENTLY deleted.\n\nPlease restart your DS.");
	//
#endif
	
	return true;
}

const char *stringsGetMessageString(int id)
{
	if (id > STR_LAST)
		return 0;
	else
		return message_strings[id];
}
