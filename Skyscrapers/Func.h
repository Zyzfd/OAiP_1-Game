#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

extern int N;
extern int gameMode;
extern char playername[20];

#define KEY +5
#define encryption 1
#define MAX_NUM_RECORDS 10
#define debug 0

int checkLeft();
int checkRight();
int checkUp();
int checkDown();
int checkIfTrue(HWND hWnd);
BOOL checknulls();
int checkcolumn();
int checkline();
void printmain(HDC hdc);
void catch_data(HWND hWnd);
int saveLevel(char filename[]);
int loadLevel(char* filename);
char* DrawRecords();
void addRecord(char* playername, int time_h, int time_m, int time_s);
void save_load_buttons_show(HWND hBtn1, HWND hBtn2, HWND hWnd, HFONT hFont, HWND hListBox);
void SaveRecords();
void LoadRecords();
void LoadRecordsEncoded();
void SaveRecordsEncoded();
int encodeChar(int ch);
void encodeString(char str[]);
int decodeChar(int ch);
void decodeString(char* str);
char* filename_search(HWND hListBox, HWND hWnd);
int mas_search(int i, int j);