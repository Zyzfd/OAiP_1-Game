#include "Func.h"

int N;
char filenameRecords[] = "C:\\Users\\yanka\\OneDrive\\stuff\\Skyscrapers\\records_table.txt";
char filenameRecordsEncoded[] = "C:\\Users\\yanka\\OneDrive\\stuff\\Skyscrapers\\records_table_encoded.txt";
int levelname;
int mas[99][99];

char* filename_search(HWND hListBox, HWND hWnd) {
    char filename[60];
    char massive[101][60] = {};
    char name[60] = "";
    char tru[3] = "";
    int level;
    for (int i = 0; i < 30; i++) {

        if (debug) {
            sprintf_s(name, "C:\\Users\\yanka\\OneDrive\\stuff\\Skyscrapers\\game%dsolve.txt", i);
        }
        else {
            sprintf_s(name, "C:\\Users\\yanka\\OneDrive\\stuff\\Skyscrapers\\game%d.txt", i);
        }
        

        FILE* fin = fopen(name, "rt");
        if (fin != NULL) {
            sprintf_s(tru, "%d", i);
            strcpy(massive[i - 1], name);
            fclose(fin);
        }

    }

    level = SendMessageA(hListBox, LB_GETCURSEL, 0, 0);
    if (level != LB_ERR) {
        strcpy(filename, massive[level]);
    }
    else {
        MessageBoxA(hWnd, "Уровней нет", "Уровней нет", MB_OK);
    }
    return filename;
}

struct Record {
    char playername[20];
    int levelname;
    unsigned int year;
    unsigned int month;
    unsigned int day;
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
};

struct Record records[MAX_NUM_RECORDS + 1];
int numRecords = 0;


int checkLeft() {
    int i;
    int j;
    int max;
    int k;
    for (i = 1; i < N - 2; i++) {
        if (mas[i][0] == 0) {
            return N;
        }
        max = 0;
        k = 0;
        for (j = 1; j <= N - 2; j++) {
            if (mas[i][j] > max) {
                max = mas[i][j];
                k++;
            }
        }

        if (k == mas[i][0]) {
            continue;
        }
        else {
            return i;
        }

    }
    return N;
}

int checkRight() {
    int i;
    int j;
    int max;
    int k;
    for (i = 1; i < N - 2; i++) {
        if (mas[i][N-1] == 0) {
            return N;
        }
        max = 0;
        k = 0;
        for (j = N - 2; j >= 1; j--) {
            if (mas[i][j] > max) {
                max = mas[i][j];
                k++;
            }
        }

        if (k == mas[i][N - 1]) {
            continue;
        }
        else {
            return i;
        }

    }
    return N;
}

int checkUp() {
    int i;
    int j;
    int max = 0;
    int k;
    for (j = 1; j < N - 2; j++) {
        if (mas[0][j] == 0) {
            return N;
        }
        max = 0;
        k = 0;
        for (i = 1; i <= N - 2; i++) {
            if (mas[i][j] > max) {
                max = mas[i][j];
                k++;
            }
        }

        if (k == mas[0][j]) {
            continue;
        }
        else {
            return j;
        }

    }
    return N;
}

int checkDown() {
    int i;
    int j;
    int max = 0;
    int k;
    for (j = 1; j <= N - 2; j++) {
        if (mas[N-1][j] == 0) {
            return N;
        }
        max = 0;
        k = 0;
        for (i = N - 2; i >= 1; i--) {
            if (mas[i][j] > max) {
                max = mas[i][j];
                k++;
            }
        }

        if (k == mas[N - 1][j]) {
            continue;
        }
        else {
            return j;
        }

    }
    return N;
}

BOOL checknulls() {
    int i;
    int j;
    for (j = 1; j < N - 1; j++) {
        for (i = N - 2; i >= 1; i--) {
            if (mas[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

BOOL checkmax() {
    for (int j = 1; j < N - 1; j++) {
        for (int i = N - 2; i >= 1; i--) {
            if (mas[i][j] > N-2) {
                return false;
            }
        }
    }
    return true;
}

int checkcolumn() {
    for (int j = 1; j < N - 1; j++) {
        for (int i = 1; i < N-2; i++) {
            for (int k = i; k >= 1; k--) {
                if (i != k) {
                    if (mas[i][j] == mas[k][j]) {
                        return k * 100 + i * 10 + j;
                    }
                }
            }
        }
    }
    return N;
}

int checkline() {
    for (int i = 1; i < N - 1; i++) {
        for (int j = 1; j < N - 1; j++) {
            for (int k = j; k >= 1; k--) {
                if (j != k) {
                    if (mas[i][j] == mas[i][k]) {
                        return k * 100 + i * 10 + j;
                    }
                }
            }
        }
    }
    return N;
}

int checkIfTrue(HWND hWnd) {
    char mes[50] = "";
    if (!checknulls()) {
        MessageBoxA(hWnd, "Неверно. Результат содержит нули.", "Проверка результата", MB_OK);
        return 0;
    }
    if (!checkmax()) {
        MessageBoxA(hWnd, "Неверно. Имеются значения больше максимального.", "Проверка результата", MB_OK);
        return 0;
    }

    int funcLeft = checkLeft();
    int funcRight = checkRight();
    int funcUp = checkUp();
    int funcDown = checkDown();
    if (funcLeft != N) {
        sprintf_s(mes, "Неверно. Ошибка левого условия в %d строке", funcLeft);
        MessageBoxA(hWnd, mes, "Проверка результата", MB_OK);
        return 0;
    }
    if (funcRight != N) {
        sprintf_s(mes, "Неверно. Ошибка правого условия в %d строке", funcRight);
        MessageBoxA(hWnd, mes, "Проверка результата", MB_OK);
        return 0;
    }
    if (funcUp != N) {
        sprintf_s(mes, "Неверно. Ошибка вехнего условия в %d столбце", funcUp);
        MessageBoxA(hWnd, mes, "Проверка результата", MB_OK);
        return 0;
    }
    if (funcDown != N) {
        sprintf_s(mes, "Неверно. Ошибка нижнего условия в %d столбце", funcDown);
        MessageBoxA(hWnd, mes, "Проверка результата", MB_OK);
        return 0;
    }

    int funccolumn = checkcolumn();
    int funcline = checkline();

    if (funccolumn != N) {
        sprintf_s(mes, "Неверно. Ячейки (%d,%d) и (%d,%d) совпадают", funccolumn % 1000 / 100, funccolumn % 100 / 10, funccolumn % 10, funccolumn % 100 / 10);
        MessageBoxA(hWnd, mes, "Проверка результата", MB_OK);
        return 0;
    }
    if (funcline != N) {
        sprintf_s(mes, "Неверно. Ячейки (%d,%d) и (%d,%d) совпадают", funcline % 100 / 10, funcline % 1000 / 100, funcline % 100 / 10, funcline % 10);
        MessageBoxA(hWnd, mes, "Проверка результата", MB_OK);
        return 0;
    }

    return 1;
}


void printmain(HDC hdc) {
    int c = 30;
    int l = 60;
    int c_max = 30;
    int l_max = 30;
    for (int i = 0; i < N - 1; i++) {
        c_max += 30;
    }
    for (int j = 0; j < N - 1; j++) {
        l_max += 30;
    }
    wchar_t text[2];
    for (int i = 0; i < N - 1; i++) {
        if (mas[i][0] == 0) {
            wsprintfW(text, L"%c", ' ');
        }
        else {
            wsprintfW(text, L"%d", mas[i][0]);
        }
        
        TextOut(hdc, 30, c, text, 1);
        c += 30;
    }
    c = 30;
    for (int i = 0; i < N - 1; i++) {
        if (mas[i][N - 1] == 0) {
            wsprintfW(text, L"%c", ' ');
        }
        else {
            wsprintfW(text, L"%d", mas[i][N - 1]);
        }
        TextOut(hdc, l_max, c, text, 1);
        c += 30;
    }
    for (int j = 1; j < N - 1; j++) {
        if (mas[0][j] == 0) {
            wsprintfW(text, L"%c", ' ');
        }
        else {
            wsprintfW(text, L"%d", mas[0][j]);
        }
        TextOut(hdc, l, 30, text, 1);
        l += 30;
    }
    l = 30;
    for (int j = 0; j < N; j++) {
        if (mas[N - 1][j] == 0) {
            wsprintfW(text, L"%c", ' ');
        }
        else {
            wsprintfW(text, L"%d", mas[N - 1][j]);
        }
        TextOut(hdc, l, c_max, text, 1);
        l += 30;
    }
}

int mas_search(int i, int j) {
    return mas[i][j];
}

void catch_data(HWND hWnd) {
    int a = 0;
    for (int i = 1; i < N - 1; i++) {
        for (int j = 1; j < N - 1; j++) {
            a = i * 10 + j;
            mas[i][j] = GetDlgItemInt(hWnd, a, FALSE, false);
        }
    }
}

void save_load_buttons_show(HWND hBtn1, HWND hBtn2, HWND hWnd, HFONT hFont, HWND hListBox) {
    hBtn1 = CreateWindow(L"BUTTON", L"Load level", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1000, 150, 150, 35, hWnd, (HMENU)1, NULL, NULL);
    hBtn2 = CreateWindow(L"BUTTON", L"Save level", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1000, 200, 150, 35, hWnd, (HMENU)2, NULL, NULL);
    

    
    SendMessage(hBtn1, WM_SETFONT, WPARAM(hFont), TRUE);
    SendMessage(hBtn2, WM_SETFONT, WPARAM(hFont), TRUE);
    
}



int loadLevel(char* filename) {
    FILE* fin = fopen(filename, "rt");
    int a = 0;

    if (fin == NULL) {
        printf_s("File %s is not opened", filename);
        return 0;
    }

    fscanf_s(fin, "%d", &levelname);

    fscanf_s(fin, "%d", &N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf_s(fin, "%d", &a);
            mas[i][j] = a;
        }
    }

    fclose(fin);
    return 1;
}

int saveLevel(char filename[]) {
    FILE* fin = fopen(filename, "wt");

    if (fin == NULL) {
        printf_s("File %s is not opened", filename);
        return 0;
    }

    fprintf(fin, "%d", levelname);
    fprintf(fin, "%s", "\n");


    fprintf(fin, "%d", N);
    fprintf(fin, "%s", "\n");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf_s(fin, "%d", mas[i][j]);
            fprintf_s(fin, "%s", " ");
        }
        fprintf_s(fin, "%s", "\n");
    }

    fclose(fin);
    return 1;
}

void addRecord(char* playername, int time_h, int time_m, int time_s) {
    strcpy(records[numRecords].playername, playername);
    records[numRecords].levelname = levelname;

    SYSTEMTIME st;
    GetLocalTime(&st);

    records[numRecords].year = st.wYear;
    records[numRecords].month = st.wMonth;
    records[numRecords].day = st.wDay;

    records[numRecords].hour = time_h;
    records[numRecords].minute = time_m;
    records[numRecords].second = time_s;

    numRecords++;
}

char * DrawRecords() {
    char string1[13000] =  "! No ! Дата           ! Время    ! Имя                             ! Название уровня  !" ;

    int i;
    for (i = 0; i < numRecords; i++) {
        char str[90];

        sprintf(str, "! %4d ! %02d.%02d.%04d ! %02d:%02d:%02d ! %-20s\t ! %d                             !",
            i + 1,
            records[i].day, records[i].month, records[i].year,
            records[i].hour, records[i].minute, records[i].second,
            records[i].playername, records[i].levelname
        );

        strcat(string1, "\n");
        strcat(string1, str);
    }

    return string1;
}

void SaveRecords() {
    FILE* fout = fopen(filenameRecords, "wt");
    if (fout == NULL) {
        return;
    }

    fprintf(fout, "%d\n", numRecords);

    int i;
    for (i = 0; i < numRecords; i++) {
        fprintf(fout, "%s %d %d %d %d %d %d %d %d\n",
            records[i].playername,
            records[i].levelname,
            records[i].year,
            records[i].month,
            records[i].day,
            records[i].hour,
            records[i].minute,
            records[i].second
        );
    }
    fclose(fout);
}

void LoadRecords() {
    FILE* fout = fopen(filenameRecords, "rt");
    if (fout == NULL) {
        return;
    }

    fscanf(fout, "%d", &numRecords);

    int i;
    for (i = 0; i < numRecords; i++) {
        fscanf(fout, "%s%d%d%d%d%d%d%d%d\n",
            records[i].playername,
            &records[i].levelname,
            &records[i].year,
            &records[i].month,
            &records[i].day,
            &records[i].hour,
            &records[i].minute,
            &records[i].second
        );
    }
    fclose(fout);
}



int encodeChar(int ch) {

    int newCh = ch;

    if (ch >= 'A' && ch <= 'Z') {
        newCh = ch + KEY;
        if (newCh > 'Z')
            newCh = 'A' + (newCh - 'Z' - 1);
    }

    if (ch >= 'a' && ch <= 'z') {
        newCh = ch + KEY;
        if (newCh > 'z')
            newCh = 'a' + (newCh - 'z' - 1);
    }

    if (ch >= '1' && ch <= '9') {
        newCh = ch + KEY;
        if (newCh > '9') {
            newCh = '1' + (newCh - '9' - 1);
        }
    }
    return newCh;
}

void encodeString(char str[]) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        str[i] = encodeChar(str[i]);
    }
}

int decodeChar(int ch) {

    int newCh = ch;

    if (ch >= 'A' && ch <= 'Z') {
        newCh = ch - KEY;
        if (newCh < 'A')
            newCh = 'Z' - ('A' - newCh - 1);
    }

    if (ch >= 'a' && ch <= 'z') {
        newCh = ch - KEY;
        if (newCh < 'a')
            newCh = 'z' - ('a' - newCh - 1);
    }

    if (ch >= '1' && ch <= '9') {
        newCh = ch - KEY;
        if (newCh < '1') {
            newCh = '9' - ('1' - newCh - 1);
        }
    }

    return newCh;
}

void decodeString(char* str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        str[i] = decodeChar(str[i]);
    }
}


void SaveRecordsEncoded() {
    FILE* fout = fopen(filenameRecordsEncoded, "wt");
    if (fout == NULL) {
        return;
    }

    char str[90];
    sprintf(str, "%d\n", numRecords);
    encodeString(str);
    fprintf(fout, "%s", str);

    int i;
    for (i = 0; i < numRecords; i++) {
        sprintf(str, "%s %d %d %d %d %d %d %d %d\n",
            records[i].playername,
            records[i].levelname,
            records[i].year,
            records[i].month,
            records[i].day,
            records[i].hour,
            records[i].minute,
            records[i].second
        );
        encodeString(str);
        fprintf(fout, "%s", str);
    }
    fclose(fout);
}

void LoadRecordsEncoded() {
    FILE* fin = fopen(filenameRecordsEncoded, "rt");
    if (fin == NULL) {
        return;
    }
    char str[90];

    fgets(str, 89, fin);
    decodeString(str);
    sscanf(str, "%d", &numRecords);
    int i;
    for (i = 0; i < numRecords; i++) {
        fgets(str, 89, fin);
        decodeString(str);

        sscanf(str, "%s%d%d%d%d%d%d%d%d\n",
            records[i].playername,
            &records[i].levelname,
            &records[i].year,
            &records[i].month,
            &records[i].day,
            &records[i].hour,
            &records[i].minute,
            &records[i].second
        );
    }
    fclose(fin);
}
