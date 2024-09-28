#include <windows.h>
#include <stdio.h>
#include <signal.h>

char *window_title;
int is_locked = 0; 
HWND hwnd = NULL;  

void lock_cursor_in_window(HWND hwnd) {
    RECT rect;
    GetWindowRect(hwnd, &rect);
    ClipCursor(&rect);
    printf("[+] locked cursor within bounding box...\n");
}

void unlock_cursor() {
    ClipCursor(NULL); 
    printf("[-] lost focus, unlocked cursor\n");
}

void CALLBACK handle_win_event(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwndForeground, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime) {
    char windowTitle[256];

    if (event == EVENT_OBJECT_SHOW) {
        GetWindowTextA(hwndForeground, windowTitle, sizeof(windowTitle));
        if (strstr(windowTitle, window_title) != NULL) {
            hwnd = hwndForeground;
            printf("[+] %s window created: %p\n", window_title, hwnd);
        }
    } 
    else if (event == EVENT_OBJECT_HIDE) {

        if (hwndForeground == hwnd) {
            printf("[+] %s window closed: %p\n", window_title, hwnd);
            hwnd = NULL; 
            if (is_locked) {
                unlock_cursor();
                is_locked = 0;
            }

            exit(0);
        }
    } 
    else if (event == EVENT_SYSTEM_FOREGROUND) {
        if (hwndForeground == hwnd && !is_locked) {
            lock_cursor_in_window(hwnd);
            is_locked = 1;
        } else if (hwndForeground != hwnd && is_locked) {
            unlock_cursor();
            is_locked = 0;
        }
    }
}

int main() {
    FILE *fp;
    char buff[255];
    fp = fopen("wnd_target.txt", "r");
    if (fp == NULL) {
        printf("[-] Error opening file\n");
        return 1;
    }
    fscanf(fp, "%s", buff);
    fclose(fp);
    window_title = buff;

    signal(SIGINT, unlock_cursor);

    printf("[+] listening for window creation and closing events for '%s'.\n", window_title);
    printf("[+] press ^C to exit.\n");

    HWINEVENTHOOK hEventHook = SetWinEventHook(EVENT_MIN, EVENT_MAX, NULL, handle_win_event, 0, 0, WINEVENT_OUTOFCONTEXT);

    if (!hEventHook) {
        printf("[-] failed to register for window events.\n");
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (is_locked) {
        unlock_cursor();
    }

    UnhookWinEvent(hEventHook);
    return 0;
}
