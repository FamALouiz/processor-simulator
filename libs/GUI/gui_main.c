#include <windows.h>
#include <process.h>    // for _beginthreadex
#include "gui_utils.h"

#define WM_APP_LOG (WM_APP+1)
#define WM_APP_MEM_ADD_INS (WM_APP+1)

HWND g_hWnd;
HWND insHWND;

#define INS_WIDTH 700
#define INS_HEIGHT 700

#define INS_TABLE_HEIGHT 100
unsigned __stdcall CLIThread(void *pv) {
    // Initialize logger for both file and terminal with debug level verbosity
    init_logger(LOG_TO_FILE_AND_TERMINAL, LOG_VERBOSITY_DEBUG);
    info("Processor simulator started");

    const char *filename = "test.asm";
    const char *properties_filename = "config/InstructionMappings.config";

    // Load instruction configurations and parse assembly file
    load_properties(properties_filename);
    parse_and_encode(filename);

    //Sample first instruction
    word* w = (word*)malloc(sizeof(word));
    mem_read(w, 0);

    int w_int;
    word_to_int(w, &w_int);
    int opcode = w_int >> (32 - 4);
    
    char bin[5];
    to_binary(bin, opcode, 4);

    Format type;
    char* mnemonic = NULL;
    get_config_mnemonic(&mnemonic, bin, &type);

    //Add instruction, determin format
    PostMessage(insHWND, WM_APP_MEM_ADD_INS, (WPARAM)0, (LPARAM)(&type));

    initProgramCounter(0);
    pipeline_stage *stages = initializeStages();

    while (1)
    {
        char** buf = (char**)malloc(sizeof(char*));
        runPipeline(stages, buf);
        // tell UI thread to append text
        
        PostMessage(g_hWnd, WM_APP_LOG, 0, (LPARAM)strdup(*buf));
        
    }
    
    
    info("Processor simulator completed successfully");
    close_logger();
    return 0;
}

LRESULT CALLBACK WndProcMain(HWND h, UINT m, WPARAM w, LPARAM l) {
    static HWND hEdit;
    switch(m) {
    case WM_CREATE:
        g_hWnd = h;
        hEdit = CreateWindow(
            "EDIT","",WS_CHILD|WS_VISIBLE|ES_MULTILINE|WS_VSCROLL,
            0,0,500,300,h,NULL,NULL,NULL);
        // fire off your logic on a worker thread
        _beginthreadex(NULL,0,CLIThread,NULL,0,NULL);
        break;
    case WM_APP_LOG: {
        char *txt = (char*)l;
        int len = GetWindowTextLength(hEdit);
        SendMessage(hEdit, EM_SETSEL, len, len);
        SendMessage(hEdit, EM_REPLACESEL, FALSE, (LPARAM)txt);
        free(txt);
    } break;
    case WM_SIZE:
        MoveWindow(hEdit,0,0,LOWORD(l),HIWORD(l),TRUE);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(h,m,w,l);
}

LRESULT CALLBACK WndProcIns(HWND h, UINT m, WPARAM w, LPARAM l)
{
    static HWND instructions_handle[10];

    switch (m)
    {
    case WM_CREATE:
        insHWND = h;
    case WM_APP_MEM_ADD_INS:
        {
            //unsigned int control = *((unsigned int*) w);

            //if(control == 0)
            //{
                //We are at the stage of creation 
                Format format = *((Format*)l);

                switch (format)
                {
                case R_TYPE:
                instructions_handle[0] = 
                CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0,0,INS_WIDTH, INS_TABLE_HEIGHT,
                    h,
                    NULL,
                    NULL,
                    NULL);
                
                CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "R-TYPE",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0,0, INS_WIDTH, (int)INS_TABLE_HEIGHT/2,
                    instructions_handle[0],
                    NULL,
                    NULL,
                    NULL
                );

                
                //OPCODE
                CreateWindowEx(
                        0,
                        TEXT("STATIC"),
                        "OPCODE",
                        WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                        0,(int)INS_TABLE_HEIGHT/2, (int)(INS_WIDTH / 5), (int)INS_TABLE_HEIGHT/2,
                        instructions_handle[0],
                        NULL,
                        NULL,
                        NULL
                );

                //R1
                CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "R1",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0 + (int)(INS_WIDTH / 5),(int)INS_TABLE_HEIGHT/2, (int)(INS_WIDTH / 5), (int)INS_TABLE_HEIGHT/2,
                    instructions_handle[0],
                    NULL,
                    NULL,
                    NULL
                );

                //R2
                CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "R2",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0 + 2 * (int)(INS_WIDTH / 5),(int)INS_TABLE_HEIGHT/2, (int)(INS_WIDTH / 5), (int)INS_TABLE_HEIGHT/2,
                    instructions_handle[0],
                    NULL,
                    NULL,
                    NULL
                );

                //R3
                CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "R3",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0 + 3 * (int)(INS_WIDTH / 5),(int)INS_TABLE_HEIGHT/2, (int)(INS_WIDTH / 5), (int)INS_TABLE_HEIGHT/2,
                    instructions_handle[0],
                    NULL,
                    NULL,
                    NULL
                );

                //SHAMT
                CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "SHAMT",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0 + 4 * (int)(INS_WIDTH / 5),(int)INS_TABLE_HEIGHT/2, (int)(INS_WIDTH / 5), (int)INS_TABLE_HEIGHT/2,
                    instructions_handle[0],
                    NULL,
                    NULL,
                    NULL
                );
                
                    break;
                case I_TYPE:
                instructions_handle[0] = 
                CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0,0,INS_WIDTH, INS_TABLE_HEIGHT,
                    h,
                    NULL,
                    NULL,
                    NULL);
                
                CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "I-TYPE",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0,0, INS_WIDTH, (int)INS_TABLE_HEIGHT/2,
                    instructions_handle[0],
                    NULL,
                    NULL,
                    NULL
                );

                
                //OPCODE
                CreateWindowEx(
                        0,
                        TEXT("STATIC"),
                        "OPCODE",
                        WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                        0,(int)INS_TABLE_HEIGHT/2, (int)(INS_WIDTH / 4), (int)INS_TABLE_HEIGHT/2,
                        instructions_handle[0],
                        NULL,
                        NULL,
                        NULL
                );

                //R1
                CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "R1",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0 + (int)(INS_WIDTH / 4),(int)INS_TABLE_HEIGHT/2, (int)(INS_WIDTH / 4), (int)INS_TABLE_HEIGHT/2,
                    instructions_handle[0],
                    NULL,
                    NULL,
                    NULL
                );

                //R2
                CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "R2",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0 + 2 * (int)(INS_WIDTH / 4),(int)INS_TABLE_HEIGHT/2, (int)(INS_WIDTH / 4), (int)INS_TABLE_HEIGHT/2,
                    instructions_handle[0],
                    NULL,
                    NULL,
                    NULL
                );

                //IMMEDIATE
                CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "IMMEDIATE",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0 + 3 * (int)(INS_WIDTH / 4),(int)INS_TABLE_HEIGHT/2, (int)(INS_WIDTH / 4), (int)INS_TABLE_HEIGHT/2,
                    instructions_handle[0],
                    NULL,
                    NULL,
                    NULL
                );
                    break;
                case J_TYPE:
                instructions_handle[0] = 
                CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0,0,INS_WIDTH,(int)INS_TABLE_HEIGHT,
                    h,
                    NULL,
                    NULL,
                    NULL);
                
                CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "J-TYPE",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0,0, INS_WIDTH, (int)INS_TABLE_HEIGHT/2,
                    instructions_handle[0],
                    NULL,
                    NULL,
                    NULL
                );

                
                //OPCODE
                CreateWindowEx(
                        0,
                        TEXT("STATIC"),
                        "OPCODE",
                        WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                        0,(int)INS_TABLE_HEIGHT/2, (int)(INS_WIDTH /2), (int)INS_TABLE_HEIGHT/2,
                        instructions_handle[0],
                        NULL,
                        NULL,
                        NULL
                );

                //ADDRESS
                CreateWindowEx(
                    0,
                    TEXT("STATIC"),
                    "ADDRESS",
                    WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
                    0 + (int)(INS_WIDTH / 2),(int)INS_TABLE_HEIGHT/2, (int)(INS_WIDTH / 2), (int)INS_TABLE_HEIGHT/2,
                    instructions_handle[0],
                    NULL,
                    NULL,
                    NULL
                );

                
                    break;
                default:
                    break;
                }

            //}else if(control == 1)
            {
                //We now want to create the table itself with values
            }
           
            
                
            //SendMessage(htext, WM_SETTEXT, (WPARAM)0, (LPARAM)l);
        }
    default:
        break;
    }
    return DefWindowProc(h,m,w,l);
}

int WINAPI WinMain(HINSTANCE hI, HINSTANCE h, LPSTR l, int nS) {
    WNDCLASS wc = { 0 };
    wc.hInstance   = hI;
    wc.lpszClassName = "MyCLIGUI";
    
    wc.lpfnWndProc = WndProcMain;
    wc.lpszClassName = "ClassMain";
    RegisterClass(&wc);

    wc.lpfnWndProc = WndProcIns;
    wc.lpszClassName = "ClassIns";
    RegisterClass(&wc);

    HWND main = CreateWindowEx(0, TEXT("ClassMain"), TEXT("Processor Simulator"), 
    WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
    700,700, NULL,NULL, hI, NULL);
    
    HWND ins = CreateWindowEx(0, TEXT("ClassIns"), TEXT("Processor Simulator Instruction Table"), 
    WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
    INS_WIDTH,INS_HEIGHT, NULL,NULL, hI, NULL);

    ShowWindow(main, SW_SHOW);
    ShowWindow(ins, SW_SHOW);

    MSG msg;
    while (GetMessage(&msg,0,0,0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
