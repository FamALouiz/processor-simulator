#include "gui_utils.h"

static unsigned int yOffset =0;
void createInstructionView(const Format format, const unsigned int width,const unsigned int height,const unsigned int offset, const HWND orig_parent,HWND* *parent_handle, HWND** table_values_handles)
{
    *table_values_handles = (HWND*)malloc(sizeof(HWND) * 6);
    switch (format)
                {
                case R_TYPE:
                *parent_handle = 
                CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0,yOffset,width, height,
                    orig_parent,
                    NULL,
                    NULL,
                    NULL);
                
                CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "R-TYPE",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0,0, width, (int)height/2,
                    *parent_handle,
                    NULL,
                    NULL,
                    NULL
                );

                
                //OPCODE
                (*table_values_handles)[0] = CreateWindowEx(
                        0,
                        TEXT("STATIC"),
                        "OPCODE",
                        WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                        0,0 + (int)height/2, (int)(width / 5), (int)height/2,
                        *parent_handle,
                        NULL,
                        NULL,
                        NULL
                );

                //R1
                (*table_values_handles)[1] = CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "R1",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0 + (int)(width / 5), 0 + (int)height/2, (int)(width / 5), (int)height/2,
                    *parent_handle,
                    NULL,
                    NULL,
                    NULL
                );

                //R2
                (*table_values_handles)[2] = CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "R2",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0 + 2 * (int)(width / 5),0 +  (int)height/2, (int)(width / 5), (int)height/2,
                    *parent_handle,
                    NULL,
                    NULL,
                    NULL
                );

                //R3
                (*table_values_handles)[3] = CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "R3",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0 + 3 * (int)(width / 5), 0 + (int)height/2, (int)(width / 5), (int)height/2,
                    *parent_handle,
                    NULL,
                    NULL,
                    NULL
                );

                //SHAMT
                (*table_values_handles)[4] = CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "SHAMT",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0 + 4 * (int)(width / 5),0 + (int)height/2, (int)(width / 5), (int)height/2,
                    *parent_handle,
                    NULL,
                    NULL,
                    NULL
                );
                (*table_values_handles)[5] = NULL; 
                break;
                case I_TYPE:
                *parent_handle = 
                CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0,yOffset,width, height,
                    orig_parent,
                    NULL,
                    NULL,
                    NULL);
                
                CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "I-TYPE",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0,0, width, (int)height/2,
                    *parent_handle,
                    NULL,
                    NULL,
                    NULL
                );

                
                //OPCODE
                (*table_values_handles)[0] = CreateWindowEx(
                        0,
                        TEXT("STATIC"),
                        "OPCODE",
                        WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                        0,0 + (int)height/2, (int)(width / 4), (int)height/2,
                        *parent_handle,
                        NULL,
                        NULL,
                        NULL
                );

                //R1
                (*table_values_handles)[1] = CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "R1",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0 + (int)(width / 4),0 + (int)height/2, (int)(width / 4), (int)height/2,
                    *parent_handle,
                    NULL,
                    NULL,
                    NULL
                );

                //R2
                (*table_values_handles)[2] = CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "R2",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0 + 2 * (int)(width / 4),0 + (int)height/2, (int)(width / 4), (int)height/2,
                    *parent_handle,
                    NULL,
                    NULL,
                    NULL
                );

                //IMMEDIATE
                (*table_values_handles)[3] = CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "IMMEDIATE",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0 + 3 * (int)(width / 4),0 + (int)height/2, (int)(width / 4), (int)height/2,
                    *parent_handle,
                    NULL,
                    NULL,
                    NULL
                );
                (*table_values_handles)[4] = NULL;
                break;
                case J_TYPE:
                *parent_handle = 
                CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0,yOffset + 0,width,(int)height,
                    orig_parent,
                    NULL,
                    NULL,
                    NULL);
                
                CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "J-TYPE",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0,0 + 0, width, (int)height/2,
                    *parent_handle,
                    NULL,
                    NULL,
                    NULL
                );

                
                //OPCODE
                (*table_values_handles)[0] = CreateWindowEx(
                        0,
                        TEXT("STATIC"),
                        "OPCODE",
                        WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                        0,0 + (int)height/2, (int)(width /2), (int)height/2,
                        *parent_handle,
                        NULL,
                        NULL,
                        NULL
                );

                //ADDRESS
                (*table_values_handles)[1] = CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "ADDRESS",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0 + (int)(width / 2),0 + (int)height/2, (int)(width / 2), (int)height/2,
                    *parent_handle,
                    NULL,
                    NULL,
                    NULL
                );

                (*table_values_handles)[2] = NULL; 
                    break;
                default:
                    break;
                }

                yOffset += height;
                yOffset += offset;

}