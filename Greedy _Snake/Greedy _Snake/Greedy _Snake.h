#ifndef _GREEDY_SNAKE_H_
#define _GREEDY_SNAKE_H_
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>//�������
#include<time.h>//ʳ�����
#include<conio.h>//�������
#include<graphics.h>//ͼ�ν����
#include<mmsystem.h>//��ý���豸�ӿ�
#pragma comment(lib,"Winmm.lib")

//////////////////////////////////////////////////////////////////////////////////////////////
////�궨��

#define Sanke_Size  100     //�ߵ���󳤶�


//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
////���������ӿ�

void Load_music();//��������
void Start_interface();//���ƿ�ʼ����
void Description_interface();//����˵������
void Game_over(int sh);//���ƽ�������
void GameInIt();  //��ʼ��
void DrawSnake_1(int i);//�ò�ͬ��ɫ����һ����
void DrawSnake();//������
void SnakeMove(); //�ߵ��ƶ�
void Changch(char input);//�ı䷽��
void CreateFood();//����ʳ������ʳ��
void DrawFood();//����ʳ��
int eatFood();//�ж�ʳ���Ƿ񱻳�ʳ��
int  SnakeStatus();  //�ߵ�״̬�����ж��Ƿ������Ϸ
void ShowStatus_bar();//��ʾ״̬��
int myspeed();//��ȡ�ٶ�
void Changespeed(char c);//�ı��ٶ�
int myHight_Score();//��ȡ��ǰ��߷�
void Hight_Score_in();//����߷�д���ļ�
int Hight_Score_out();//���ļ���ķ�������

#endif /*_GREEDY_SNAKE_H_*/