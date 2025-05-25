#include <windows.h>
#include <process.h>
#include "datapath.h"

void splitInstructionIntoStrings(const word* instruction, const Format format, char** values);
//Create an instruction view, it return a parent window with an array of table values handles
void createInstructionView(const Format format, const unsigned int width, const unsigned int height,const unsigned int offset,const HWND orig_parent,HWND* parent_handle, HWND table_values_handles[6]);