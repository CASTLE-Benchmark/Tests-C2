#include <stdio.h>
#include <wchar.h>

#define SRC_STRING L"random string that definitely has no issues"

void main()
{
    wchar_t dataBuffer[100] = L"";
    wchar_t * data = dataBuffer;

    if (snprintf(data, 100 - wcslen(SRC_STRING) -1, L"%ls\n", SRC_STRING) == 0)
    {
        printf("snprintf failed!");
    }

    printf("%ls\n", data);
}