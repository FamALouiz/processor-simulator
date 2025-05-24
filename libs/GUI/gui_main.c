#include <stdlib.h>
#include <windows.h>
#include "datapath.h"

#define WM_APP_LOG (WM_APP +1)
#define TEST_MEMORY_CELLS 5

static HWND mainWind = NULL;
void runCLIThread()
{
    // Initialize logger for both file and terminal with debug level verbosity
    init_logger(LOG_TO_FILE_AND_TERMINAL, LOG_VERBOSITY_DEBUG);
    info("Processor simulator started");

    const char *filename = "test.asm";
    const char *properties_filename = "config/InstructionMappings.config";

    // Load instruction configurations and parse assembly file
    load_properties(properties_filename);
    parse_and_encode(filename);

    initProgramCounter(0);
    pipeline_stage *stages = initializeStages();
    runPipeline(stages);

    //Post to GUI
    char* buff = "TEST";
    PostMessage(mainWind, WM_APP_LOG, 0 ,(LPARAM)buff);

    info("Processor simulator completed successfully");
    close_logger();

}
// Forward declaration of our window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nCmdShow)
{
    const char CLASS_NAME[]  = "Sample Window Class";
    WNDCLASS wc = { 0 };

    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "RegisterClass failed!", "Error", MB_ICONERROR);
        return 0;
    }

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        "My Win32 Window",              // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL) {
        MessageBox(NULL, "CreateWindowEx failed!", "Error", MB_ICONERROR);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND hEdit;
    switch (msg) {
    case WM_CREATE:{
        mainWind = hwnd;

        hEdit = CreateWindowEx(
            0, "EDIT", NULL,
            WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
            0, 0, 400, 300,    // initial size; will be resized in WM_SIZE
            hwnd, NULL, NULL, NULL);

        uintptr_t threadID;
        _beginthreadex(
            NULL,       // security
            0,          // stack size (0 = default)
            runCLIThread,  // thread function
            NULL,       // thread param
            0,          // creation flags
            &threadID   // out: thread identifier
        );
    }

    case WM_APP_LOG:
    {
        char* txt = (char*) lParam;
        int len = GetWindowTextLength(hEdit);
        SendMessage(hEdit, EM_SETSEL, (WPARAM)len, (LPARAM)len);
        SendMessage(hEdit, EM_REPLACESEL, FALSE, (LPARAM)txt);
        free(txt);
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}
