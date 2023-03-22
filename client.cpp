#include <iostream>
#include <windows.h>
#include <string>
#include <stdlib.h>
using namespace std;
HANDLE memory_handle;
LPVOID memoryPointer;
typedef struct _DATAFILEANDREGEDIT {
    char FILE_DATA[640];
    char REGEDIT_DATA[640];
    _DATAFILEANDREGEDIT() {
        memset(FILE_DATA,    NULL, 640);
        memset(REGEDIT_DATA, NULL, 640);
    }
}*PDATAFILEANDREGEDIT, DATAFILEANDREGEDIT;

//--------------------------------------------------------------------------
//     DT - DATA TRANSFER
LPVOID DT_MapViewEnable() {
    const char* memory_name = "Global\\example_memory";
    const int memory_size = 1024;
    memory_handle = OpenFileMapping(FILE_MAP_ALL_ACCESS, TRUE, (LPCWSTR)memory_name);
    if (memory_handle == NULL) {
        std::cerr << "Bellek alanına bağlanma hatası: " << GetLastError() << std::endl;
        return NULL;
    }
    LPVOID  pBuf = MapViewOfFile(memory_handle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(DATAFILEANDREGEDIT));
    if (pBuf == NULL) {
        std::cout << "Could not map view of file: " << GetLastError() << std::endl;
        CloseHandle(memory_handle);
        return NULL;
    }
    memoryPointer=pBuf;
    return pBuf;
}
//--------------------------------------------------------------------------
void DT_MapViewDisable() {
    UnmapViewOfFile(memory_handle);
    CloseHandle(memory_handle);
}
//--------------------------------------------------------------------------
int DT_MapViewRead() {
    char buffer[641];
    buffer[640] = '\0';
    memcpy(&buffer, ((PDATAFILEANDREGEDIT)memoryPointer)->FILE_DATA , 640);
    for (int i = 0; i < 640; i += 64) {
        char c_buffer[65];
        memcpy_s(c_buffer,64,buffer + i,64);
        c_buffer[64] = '\0';
        if (c_buffer[0] !='\0') {
            cout << c_buffer << endl;
        }
    }
    return 1;
}
//--------------------------------------------------------------------------
int main() {
    DT_MapViewEnable();
    DT_MapViewRead();
    DT_MapViewDisable();
}
