#include "gui_utils.h"

static unsigned int yOffset =0;

void splitInstructionIntoStrings(const word* instruction, const Format format, char** values){
    int w_int;
    word_to_int(instruction, &w_int);

    int opcode = w_int >> (32 - 4);
    (*values) = (char*)malloc(sizeof(char) * 5);
    to_binary(*values, opcode, 4);
    //get individual components
    switch (format)
    {
    case R_TYPE:
        int r1r = (w_int >> (32- (4+ 5))) & 0x0000001F;
        int r2r = (w_int >> (32- (4+ 5 +5)))  & 0x0000001F;
        int r3 = (w_int >> (32- (4+ 5 +5 +5)))  & 0x0000001F;
        int shamt = (w_int >> 0)  & 0x00001FFF;

        (*(values + 1)) = (char*)malloc(sizeof(char) * 6);
        (*(values + 2)) = (char*)malloc(sizeof(char) * 6);
        (*(values + 3)) = (char*)malloc(sizeof(char) * 6);
        (*(values + 4)) = (char*)malloc(sizeof(char) * 14);
        (*(values + 5)) = NULL;

        to_binary(*(values + 1), r1r, 5);
        to_binary(*(values + 2), r2r, 5);
        to_binary(*(values + 3), r3, 5);
        to_binary(*(values + 4), shamt, 13);

    break;
    case I_TYPE:
        int r1i = (w_int >> (32- (4+ 5))) & 0x0000001F;
        int r2i = (w_int >> (32- (4+ 5 +5)))  & 0x0000001F;
        int imm = (w_int >> 0)  & 0x02FFFF;

        (*(values + 1)) = (char*)malloc(sizeof(char) * 6);
        (*(values + 2)) = (char*)malloc(sizeof(char) * 6);
        (*(values + 3)) = (char*)malloc(sizeof(char) * 19);
        (*(values + 4)) = NULL;

        char r1_str[6],r2_str[6],imm_str[19];
        to_binary(*(values + 1), r1i, 5);
        to_binary(*(values + 2), r2i, 5);
        to_binary(*(values + 3), imm, 18);

    break;
    case J_TYPE:
        int address = (w_int >> 0) & 0x0FFFFFFF;

        (*(values + 1)) = (char*)malloc(sizeof(char) * 29);
        (*(values + 2)) = NULL;

        to_binary(*(values + 1), address, 28);

    break;
    default:
        break;
    }
}
void createInstructionView(const Format format, const unsigned int width,const unsigned int height,const unsigned int offset, const HWND orig_parent,HWND *parent_handle, HWND table_values_handles[6])
{
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
                table_values_handles[0] = CreateWindowEx(
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
                table_values_handles[1] = CreateWindowEx(
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
                table_values_handles[2] = CreateWindowEx(
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
                table_values_handles[3] = CreateWindowEx(
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
                table_values_handles[4] = CreateWindowEx(
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
                table_values_handles[5] = NULL; 
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
                table_values_handles[0] = CreateWindowEx(
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
                table_values_handles[1] = CreateWindowEx(
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
                table_values_handles[2] = CreateWindowEx(
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
                table_values_handles[3] = CreateWindowEx(
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
                table_values_handles[4] = NULL;
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
                table_values_handles[0] = CreateWindowEx(
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
                table_values_handles[1] = CreateWindowEx(
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

                table_values_handles[2] = NULL; 
                    break;
                default:
                    break;
                }

                yOffset += height;
                yOffset += offset;

}