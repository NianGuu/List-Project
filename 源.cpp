#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>

#define ERR_SKILL_LIST_EXCEED -1	//技能表越界

#define skillNum 4					//实体技能个数
#define nameLength 20				//名称长度
#define skillLength 3				//总技能个数
typedef struct {
	int power;				//武器的伤害
	int defensive0;			//防御力
	int money;			//金钱
}weapons;
/*技能结构体定义*/
typedef struct {
	char name[nameLength];		//技能名称
	int atk;						//技能伤害
}Skill;
/*技能表顺序表定义*/
typedef struct {
	Skill data[skillNum];		//技能表中所含技能数组
	int length;					//技能表长度
}SkillList;
/*实体结构体定义*/
typedef struct {
	char name[nameLength];		//实体名称
	int HP;						//实体生命值
	SkillList SkillList;		//实体所带技能表
	int i;						//实体类型 
}Entity;

void UI_fight(Entity);											/*战斗界面UI*/
int UI_fighting(Entity, Entity);								/*战斗中UI*/
void setEntity(Entity*, int, char name[nameLength]);			/*初始化实体*/
Skill catchSkill(int i);										/*调用技能*/
void wqshop();                                                  /*武器*/
/*顺序表操作集*/
void InitList(SkillList*);							//建空表
int Length(SkillList);								//求表长
void updata(SkillList*, int, Skill);				//修改数据

int difficulty = 1;		/*难度系数*/

/*技能列表*/
static Skill skill_ERROR{ "ERROR",-114514 };
static Skill skill_Null{ "NULL",0 };
static Skill skill_One{ "撞击",10 };
static Skill skill_Two{ "大兜子",30 };
static Skill skill_Three{ "小亮の活",50 };

int main() {
	Entity player;
	char name[nameLength];
	printf("欢迎进入游戏\n");
	printf("***********\n");
	printf("请输入您的名称\n");
	putchar('\n');
	gets_s(name);
	setEntity(&player, 2, name);
	while (true) {
		system("CLS");
		puts(player.name);
		printf("等级：%d\n", difficulty);
		printf("请输入你的操作：\n");
		printf("*************************\n");
		printf("1.战斗\n");
		printf("2.技能\n");
		printf("3.商店\n");
		printf("4.退出\n");
		char choose;
		choose = getchar();
		while (getchar() != '\n');
		if (choose == '1')
			UI_fight(player);
		else if (choose == '2')
			break;
		else if (choose == '3')
			wqshop();
		else if (choose == '4')
			return 0;
		else {
			printf("请输入正确的选项！\n");
			Sleep(1000);
		}
	}
}
/*初始化实体*/
/*当i为1时，实体为小怪类型
  当i为2时，实体为精英类型
  当i为3时，实体为首领类型*/
void setEntity(Entity* entity, int i, char name[nameLength]) {
	strcpy_s(entity->name, name);
	int hp = i * difficulty * 100;
	entity->HP = hp;
	entity->i = i;
	InitList(&entity->SkillList);
	updata(&entity->SkillList, 0, skill_Two);
	updata(&entity->SkillList, 1, skill_Null);
	updata(&entity->SkillList, 2, skill_Null);
	updata(&entity->SkillList, 3, skill_Null);
}

/*战斗界面UI*/
void UI_fight(Entity player) {
head:
	system("CLS");
	srand((unsigned)time(NULL));
	int i = rand() % 3 + 1;						//随机生成怪物类型
	char iname[nameLength];
	switch (i) {
	case 1:strcpy_s(iname, "小怪");break;
	case 2:strcpy_s(iname, "精英");break;
	case 3:strcpy_s(iname, "首领");break;
	}
	printf("你遇到了一个%s！\n", iname);
	printf("*****************\n");
	Entity mob;
	setEntity(&mob, i, iname);					//构建怪物实体并以随机到的类型赋值属性及名称
	for (int i = 4;i;i--) {						//随机构建怪物技能表
		srand((unsigned)time(NULL));
		int a = 1 + rand() % (skillLength - 1);
		updata(&mob.SkillList, i - 1, catchSkill(a));
	}
	printf("是否开始战斗？\n");
	printf("Y/N\n");
	while (char ch = getchar()) {					//让玩家选择是否战斗，是则继续，否则跳转至子函数开头
		while (getchar() != '\n');
		if (ch == 'Y' || ch == 'y')
			break;
		else if (ch == 'N' || ch == 'n')
			goto head;
		else {
			printf("请输入正确的选项！\n");
			continue;
		}
		break;
	}
	difficulty += UI_fighting(player, mob);		//若胜利则难度系数+1，若失败则-1。
}

/*战斗中UI*/
int UI_fighting(Entity player, Entity mob) {
	system("CLS");
	putchar(10);
	int i = 0;
	int choose;
	while (player.HP > 0 && mob.HP > 0) {
		i++;//回合计数器
		printf("***********第%d回合************\n", i);
		Sleep(500);
		printf("%s的生命值剩余%d\n", player.name, player.HP);
		Sleep(500);
		printf("%s的生命值剩余%d\n", mob.name, mob.HP);
		Sleep(500);
		putchar(10);
		printf("你要做什么？\n");
		for (int i = 0;i < skillNum;i++) {
			printf("%d.%s\n", i + 1, player.SkillList.data[i].name);
		}
		while (true) {
			scanf_s("%d", &choose);						//控制台输入玩家释放的技能
			while (getchar() != '\n');
			if (choose >= 1 && choose <= skillNum) {
				break;
			}
			else
				printf("请输入正确的选项！");
		}
		mob.HP -= player.SkillList.data[choose - 1].atk;
		printf("%s使用了%s,对%s造成了%d点伤害!\n%s剩余血量%d\n", player.name, player.SkillList.data[choose - 1].name, mob.name, player.SkillList.data[choose - 1].atk, mob.name, mob.HP);
		Sleep(500);
		if (mob.HP <= 0)break;
		srand((unsigned)time(NULL));
		choose = rand() % skillNum;							//随机数决定敌人释放的技能
		printf("%d", choose);
		player.HP -= mob.SkillList.data[choose].atk;
		printf("%s使用了%s,对%s造成了%d点伤害!\n%s剩余血量%d\n", mob.name, mob.SkillList.data[choose].name, player.name, mob.SkillList.data[choose].atk, player.name, player.HP);
		Sleep(500);
		if (player.HP <= 0)break;
		Sleep(500);
	}
	printf("战斗结束！\n");
	if (player.HP <= 0) {
		printf("你失败了！\n");
		printf("按任意键返回。\n");
		while (getchar() != '\n');
		return -1;
	}
	else {
		printf("你胜利了！\n");
		printf("按任意键返回。\n");
		while (getchar() != '\n');
		return 1;
	}
}

/*调用技能*/
Skill catchSkill(int i) {
	switch (i) {
	case 0:return skill_Null;
	case 1:return skill_One;
	case 2:return skill_Two;
	case 3:return skill_Three;
	default:return skill_ERROR;
	}
}

/*顺序表操作集*/
/*建空表*/
void InitList(SkillList* list) {
	list->length = 0;
}
/*求表长*/
int Length(SkillList list) {
	return list.length;
}
/*修改数据*/
void updata(SkillList* list, int i, Skill x) {
	list->data[i] = x;
}
void wqshop()			//武器店 
{
	int dj = 1, cj = 1, bj = 1, szj = 1, wq;//用来分辨已经拥有或没有拥有
	int v = 1;
	weapons my;
	while (v == 1)
	{
		int wq = 0;
		printf("你好勇士，欢迎来到武器店\n请问你需要什么？\n1   短剑(伤害加10)  500金币\n2   长剑(伤害加30)  2000金币\n3   布甲(伤害减免8)   500金币\n4   锁子甲(伤害减免18)   2000金币\n5   退出武器店\n");
		scanf("%d", &wq);
		if (wq > 5)
		{
			while (wq > 6)
			{
				printf("未开放，敬请期待\n");
				wq = 0;
			}
			while (wq == 5)
			{
				printf("你选择退出\n;");
				v = 0;
				wq = 0;
			}
		}
		else
		{
			while (wq == 1)
			{
				if (my.money > 500)
				{
					if (dj == 1)
					{
						printf("你购买了短剑,伤害加十，重复购买无效\n");
						my.power += 10;//声明全局变量，装备加成攻击力
						my.money = my.money - 500;
						dj = 0;
						wq = 0;
					}
					else
					{
						printf("你已经购买过了\n");
					}
				}
				else
				{
					printf("金币不足\n");
				}
				wq = 0;
			}
			while (wq == 2)
			{
				if (my.money > 2000)
				{
					if (cj == 1)
					{
						printf("你购买了长剑，伤害加三十，重复购买无效\n");
						my.power += 30;//声明全局变量，装备加成攻击力
						my.money = my.money - 2000;
						cj = 0;
					}
					else
					{
						printf("你已经购买过了\n");
					}
				}
				else
				{
					printf("金币不足\n");
				}
				wq = 0;
			}
			while (wq == 3)
			{
				if (my.money > 500)
				{
					if (bj == 1)
					{
						printf("你购买了布甲，伤害减免8，重复购买无效\n");
						my.defensive0 += 30;//声明全局变量，装备加成攻击力
						my.money = my.money - 2000;
						bj = 0;
					}
					else
					{
						printf("你已经购买过了\n");
					}
				}
				else
				{
					printf("金币不足\n");
				}
				wq = 0;
			}
			while (wq == 4)
			{
				if (my.money > 2000)
				{
					if (szj == 1)
					{
						printf("你购买了布甲，伤害减免18，重复购买无效\n");
						my.defensive0 += 30;//声明全局变量，装备加成攻击力
						my.money = my.money - 2000;
						szj = 0;
					}
					else
					{
						printf("你已经购买过了\n");
					}
				}
				else
				{
					printf("金币不足\n");
				}
				wq = 0;
			}
		}
	}
}