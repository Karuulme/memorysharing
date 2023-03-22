#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

const char* memory_name = "Global\\example_memory";
LPVOID memory_pointer;
HANDLE memory_handle;
typedef struct _DATAFILEANDREGEDIT {
    char FILE_DATA[640];
    char REGEDIT_DATA[640];
    _DATAFILEANDREGEDIT() {
        memset(FILE_DATA,    NULL, 640);
        memset(REGEDIT_DATA, NULL, 640);
    }
}*PDATAFILEANDREGEDIT, DATAFILEANDREGEDIT;
LPVOID DT_MapViewEnable() {
    memory_handle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(DATAFILEANDREGEDIT), (LPCWSTR)memory_name);
    if (memory_handle == NULL) {
        std::cerr << "İsimli bellek alanı oluşturma hatası: " << GetLastError() << std::endl;
        return NULL;
    }
    memory_pointer = MapViewOfFile(memory_handle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(DATAFILEANDREGEDIT));
    if (memory_pointer == NULL) {
        std::cerr << "Bellek alanına bağlanma hatası: " << GetLastError() << std::endl;
        CloseHandle(memory_handle);
        return NULL;
    }
}
LPVOID DT_MapViewWrite() {
    memset(memory_pointer, NULL, sizeof(DATAFILEANDREGEDIT));
    memset(memory_pointer, NULL, sizeof(DATAFILEANDREGEDIT));
    DATAFILEANDREGEDIT dataTransfer;
    memcpy(dataTransfer.FILE_DATA, "4503a99b9520490c17d469ecb4feb688173a0b41309c2085b4f61358a907e4ff4503a99b9520490c17d469ecb4feb688173a0b41309c2085b4f61358a907e4ff", 128);
    memcpy(memory_pointer, &dataTransfer, sizeof(DATAFILEANDREGEDIT));
}
void DT_MapViewDisable() {
    UnmapViewOfFile(memory_handle);
    CloseHandle(memory_handle);
}
int main() {
    DT_MapViewEnable();
    DT_MapViewWrite();

    DT_MapViewDisable();
    return 0;
}
