#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include<math.h> 

#define ERR_SKILL_LIST_EXCEED -1	//技能表越界

#define skillNum 4					//实体技能个数
#define nameLength 20				//名称长度
#define skillLength 3				//总技能个数
#define M 3

/*技能结构体定义*/
typedef struct {
	short ID;						//技能ID
	char name[nameLength];			//技能名称
	int atk;						//技能伤害
}Skill;
/*技能表顺序表定义*/
typedef struct {
	Skill data[skillNum];			//技能表中所含技能数组
	int length;						//技能表长度
}SkillList;
/*未获取技能表结点定义*/
typedef struct node {
	Skill data;
	struct node* next;
}SkillNode, * SkillLink;
<<<<<<< Updated upstream
=======
/*药品结构体定义*/
typedef struct {
	char name[nameLength];		//药品名字 
	int effect;					//药品效果，每吃一个加多少生命值 
}Food;
/*武器结构体定义*/
typedef struct {
	int ID;						//武器ID
	char name[nameLength];		//武器名称
	int ATK;					//武器攻击力
}Weapon;
/*盔甲结构体定义*/
typedef struct {
	int ID;						//盔甲ID
	char name[nameLength];		//盔甲名称
	int DEF;					//盔甲防御力
}Armour;
/*装备结构体定义*/
typedef struct {
	Weapon Weapon;				//武器
	Armour Armour;				//盔甲
}Equi;
>>>>>>> Stashed changes
/*实体结构体定义*/
typedef struct {
	char name[nameLength];		//实体名称
	int HP;						//实体生命值
	SkillList SkillList;		//实体所带技能表
	SkillLink OwnSkill;			//实体已拥有技能表
	SkillLink NoneSkill;		//实体未获得技能表
	int i;						//实体类型 
}Entity;
struct food //定义药品结构体类型 
{
	char name[20]; //药品名字 
	int count;  //药品数量 
	int effect;  //药品效果，每吃一个加多少生命值 
}fd[M];

void UI_fight(Entity*);											/*战斗界面UI*/
int UI_fighting(Entity, Entity);								/*战斗中UI*/
void UI_skill(Entity*);											/*技能界面UI*/
int UI_UnloadSkill(Entity*);									/*卸下技能UI*/
int UI_LoadSkill(Entity*);										/*装载技能UI*/

void init();

void SetEntity(Entity*, int, char name[nameLength]);			/*初始化实体*/
Skill CatchSkill(int i);										/*调用技能*/
void GetSkill(Entity*, int);									/*获取新技能*/
void next();													/*按任意键下一步*/

int UnloadSkill(Entity*, int);									/*卸下技能*/
int LoadSkill(Entity*, int);									/*装配技能*/

int ToInt(char[]);			//字符串类型转换为整型

/*顺序表操作集*/
void InitList(SkillList*);							//建空表
int Length(SkillList);								//求表长
void updata(SkillList*, int, Skill);				//修改数据
int Locate(SkillList, Skill);						//已知值求下标

/*单链表操作集*/
SkillLink InitListNode();						//初始化单链表
void InsertNode(SkillLink, int, Skill);			//插入单链表
int LengthNode(SkillLink);						//求表长
void Traversal(SkillLink);						//遍历
SkillLink Delete(SkillLink, int);				//删除
int LocateNode(SkillLink, Skill);				//已知值查找序号
SkillLink GetElem(SkillLink, int);				//已知序号查找值

int difficulty = 1;		/*难度系数*/



int main() {
	Entity player;
	char name[nameLength];
	printf("+----------------------------+\n");
	printf("|	欢迎进入游戏         |\n");
	printf("|****************************|\n");
	printf("+----------------------------+\n");
	printf("\n请输入您的名称:  ");
	gets_s(name);
	SetEntity(&player, 2, name);
	while (true) {
		system("CLS");
<<<<<<< Updated upstream
		puts(player.name);
		printf("等级：%d\n", difficulty);
		printf("请输入你的操作：\n");
		printf("*************************\n");
		printf("1.战斗\n");
		printf("2.技能\n");
		printf("0.退出\n");
=======
		printf("*********************************************************\n");
		printf("*	名称:%-10s	等级:%-2d		金币:%-10d *\n", player.name, difficulty, player.Gold);
		printf("*                                                       *\n");
		printf("*	操作列表:                                       *\n");
		printf("*                                                       *\n");
		printf("*	1.战斗		2.技能		3.药品		*\n");
		printf("*                                                       *\n");
		printf("*	4.装备		5.商店		0.退出		*\n");
		printf("*********************************************************\n");
		printf("\n输入你的操作\n");
>>>>>>> Stashed changes
		char choose;
		choose = getchar();
		while (getchar() != '\n');
		if (choose == '1')
			UI_fight(&player);
		else if (choose == '2')
			UI_skill(&player);
		else if (choose == '0')
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
void SetEntity(Entity* entity, int i, char name[nameLength]) {
	strcpy_s(entity->name, name);				//名称
	entity->HP = i * difficulty * 100;			//血量
	entity->i = i;								//实体类型
	InitList(&entity->SkillList);				//初始化技能表
	updata(&entity->SkillList, 0, CatchSkill(3));
	updata(&entity->SkillList, 1, CatchSkill(2));
	updata(&entity->SkillList, 2, CatchSkill(1));
	updata(&entity->SkillList, 3, CatchSkill(4));
	entity->OwnSkill = InitListNode();			//初始化已获取技能表
	entity->NoneSkill = InitListNode();			//初始化未获取技能表
	for (int i = 0;i < skillLength;i++)
		InsertNode(entity->NoneSkill, i + 1, CatchSkill(i + 1));
}

void init()										//设置药品名字，使用次数
{
	int i;
	char name[M][20] = { "金疮药","大力丸","续命丸" };		//名字
	srand(time(NULL));
	for (i = 0;i < M;i++)
	{
		strcpy_s(fd[i].name, name[i]);
		fd[i].count = 1;									//次数
		fd[i].effect = i + 1;								//效果
	}
}

/*战斗界面UI*/
void UI_fight(Entity* player) {
head:
	system("CLS");
<<<<<<< Updated upstream
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
	SetEntity(&mob, i, iname);					//构建怪物实体并以随机到的类型赋值属性及名称
	for (int i = 4;i;i--) {						//随机构建怪物技能表
		srand((unsigned)time(NULL));
		int a = 1 + rand() % (skillLength - 1);
		updata(&mob.SkillList, i - 1, CatchSkill(a));
	}
	printf("是否开始战斗？\n");
	printf("Y/N\n");
=======
	Entity mob = SetMob();
	printf("...........................................\n");
	printf(".	你遇到了一个%d级的%s！		  .\n", difficulty, mob.name);
	printf("...........................................\n\n");
	printf("!!!\n");
	printf("\n是否开始战斗？\n");
	printf("\nY/N  (输入Y开始，N返回)\n\n");
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	difficulty += UI_fighting(*player, mob);		//若胜利则难度系数+1，若失败则-1。
=======
	int result = UI_fighting(*player, mob);
	system("CLS");
	switch (result) {
	case -1: {			//战斗失败
		printf("\n  ╥﹏╥...\n");
		printf("+-----------------------+\n");
		printf("|	战斗失败！	|\n");
		printf("+-----------------------+\n");
		difficulty--;
	};break;
	case 1: {			//战斗胜利
		printf("\n  o(^▽^)o\n");
		printf("\n+++++++++++++++++++++++++\n");
		printf("|	战斗胜利！	|\n");
		printf("+++++++++++++++++++++++++\n");
		difficulty++;
		UI_gain(player, mob);
	};break;
	case 0: {			//逃跑
		printf("\n  <(￣ ﹌ ￣)@m 就这？\n");
		printf("\n你逃跑了！\n");
	};break;
	}
	system("PAUSE");
>>>>>>> Stashed changes
}
/*战斗中UI*/
int UI_fighting(Entity player, Entity mob) {
	system("CLS");
	putchar(10);
	int i = 0;
	int choose;
	while (player.HP > 0 && mob.HP > 0) {
<<<<<<< Updated upstream
		i++;//回合计数器
		system("CLS");
		printf("***********第%d回合************\n", i);
		//Sleep(500);
		printf("%s的生命值剩余%d\n", player.name, player.HP);
		//Sleep(500);
		printf("%s的生命值剩余%d\n", mob.name, mob.HP);
		//Sleep(500);
		putchar(10);
		printf("你要做什么？\n");
		for (int i = 0;i < skillNum;i++) {
			printf("%d.%s\n", i + 1, player.SkillList.data[i].name);
		}
		while (true) {
			scanf_s("%d", &choose);						//控制台输入玩家释放的技能
=======
		i++;
	head:
		UI_Jade(player, mob, i);
		printf("#|*********************************|#\n");
		printf("#|	   你要进行什么操作?	   |#\n");
		printf("#|                                 |#\n");
		printf("#|		1.技能		   |#\n");
		printf("#|                                 |#\n");
		printf("#|		2.药品		   |#\n");
		printf("#|                                 |#\n");
		printf("#|		0.逃跑		   |#\n");
		printf("#|*********************************|#\n");
		choose = ToInt32(gets_s(chooseChar));
		if (choose == 1) {					//选择技能
		branch1:
			UI_Jade(player, mob, i);
			UI_fightSkill(player);
			branch = 1;
		}
		else if (choose == 2) {				//选择药品
		branch2:
			UI_Jade(player, mob, i);
			UI_fightFood(player);
			branch = 2;
		}
		else if (choose == 0) {
			system("CLS");
			printf("!!!\n");
			printf("确定要逃跑吗？\n\n输入0确认选择\n");
			chooseChar[1] = getchar();
>>>>>>> Stashed changes
			while (getchar() != '\n');
			if (choose >= 1 && choose <= skillNum) {
				break;
			}
			else
				printf("请输入正确的选项！");
		}
		init();
		if (choose==4) {
			int i;
			for (i = 0;i < M;i++)
			{

				printf("%d: %s%d个 吃了之后能增加HP%d\n", i, fd[i].name, fd[i].count, (fd[i].effect) * 20);
			}
			printf("选择你要吃的药品编号(-1取消):");
			scanf_s("%d", &i);			//输入使用哪个药品
			if (i >= 0 && i < M)
			{
				if (fd[i].count > 0)	
				{
					printf("你吃了一个%s,HP增加了%d", fd[i].name, (fd[i].effect) * 20);	
					player.HP += (fd[i].effect) * 20;			//恢复效果
					fd[i].count--;								//减少次数
					if (player.HP > 200)player.HP = 200;			//恢复满
				}
				else
				{
					printf("你没有这个药品!");
				}
			}
			Sleep(500);
		}
		else {
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
	}
	printf("战斗结束！\n");
	if (player.HP <= 0) {
		printf("你失败了！\n");
		printf("按任意键返回。\n");
		while (getchar() != '\n');
		return -1;
<<<<<<< Updated upstream
=======
	else if (mob.HP <= 0)			//胜利返回值1
		return 1;
	else							//逃跑返回值0
		return 0;
}
/*战斗信息*/
/*带入战斗双方以及回合数*/
void UI_Jade(Entity player, Entity mob, int i) {
	system("CLS");
	printf("*—————————第%2d回合———————————*\n", i);
	printf("|\t\t\t\t\t\t |\n");
	printf("|\t%-10s等级：%-7dHP：%-12d\t |\n", mob.name, difficulty, mob.HP);
	printf("|\t\t\t\t\t\t |\n");
	printf("|\t%-10s等级：%-7dHP：%-12d\t |\n", player.name, difficulty, player.HP);
	printf("|\t\t\t\t\t\t |\n");
	printf("*————————————————————————*\n\n");
}
/*战斗中的技能界面*/
void UI_fightSkill(Entity player) {
	printf("你想要使用哪个技能？\n");
	for (int i = 0;i < skillNum;i++)
		printf("\n    %-2d.%-10s伤害：%-10d\n", i + 1, player.SkillList.data[i].name, player.SkillList.data[i].atk);
	printf("\n    输入0退出\n\n");
}
/*战斗中的药品界面*/
void UI_fightFood(Entity player) {
	printf("你想要使用哪个药品？\n");
	for (int i = 0;i < M;i++)
		printf("    %-2d.%-10s数量：%-10d治疗量：%-10d\n", i + 1, player.Food[i].name, player.FoodNum[i], player.Food[i].effect);
	printf("    输入0退出\n\n");
}
/*掉落物*/
/*以怪物为参数计算掉落物*/
void UI_gain(Entity* player, Entity mob) {
	srand((unsigned)time(NULL));

	int get = 1 + rand() % skillNum;			//随机数决定掉落怪物的哪个技能
	if (LocateNode(player->NoneSkill, mob.SkillList.data[get - 1]) != -1) {
		GetSkill(player, LocateNode(player->NoneSkill, mob.SkillList.data[get - 1]));
		printf("\n你获得了技能：%s！\n", mob.SkillList.data[get - 1].name);
>>>>>>> Stashed changes
	}
	else {
		printf("你胜利了！\n");
		printf("按任意键返回。\n");
		while (getchar() != '\n');
		return 1;
	}
<<<<<<< Updated upstream
=======
	player->Gold += mob.Gold;					//获取怪物的金币
	printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$");
	printf("\n$                       $");
	printf("\n$    你获得了%d金币！    $", mob.Gold);
	printf("\n$                       $");
	printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$\n");
}

/*战斗计算*/
/*攻击方在前，受击方在后,choose为使用的技能，返回值为造成伤害*/
int attack(Entity* entity1, Entity* entity2, int choose) {
	int harm;
	harm = entity1->SkillList.data[choose - 1].atk;
	entity2->HP -= harm;
	return harm;
>>>>>>> Stashed changes
}

/*技能界面UI*/
void UI_skill(Entity* player) {
head:
	system("CLS");
<<<<<<< Updated upstream
	printf("%s\n等级：%d\n", player->name, difficulty);
	printf("当前技能：\n");
=======
	printf("*********************************************************\n");
	printf("*	名称:%-10s	等级:%-2d		金币:%-10d *\n", player->name, difficulty, player->Gold);
	printf("*-------------------------------------------------------*\n");
	printf("*当前技能:                                              *\n");
>>>>>>> Stashed changes
	for (int i = 0;i < skillNum;i++)
		printf("*%d.%-10s                                           *\n", i + 1, player->SkillList.data[i].name);
	printf("*-------------------------------------------------------*\n");
	printf("已拥有的技能:\n");
	Traversal(player->OwnSkill);
	printf("请输入操作：\n");
	printf("1.查看未拥有技能\n");
	printf("2.卸下技能\n");
	printf("3.装载技能\n");
	printf("0.退出\n");
	putchar(10);
	while (char i = getchar()) {
		while (getchar() != '\n');
		switch (i) {
		case '0':break;
		case '1': {
			system("CLS");
			Traversal(player->NoneSkill);
			next();
		};goto head;
		case '2':UI_UnloadSkill(player);goto head;
		case '3':UI_LoadSkill(player);goto head;
		default: {
			printf("请输入正确的选项！\n");
			Sleep(300);
			goto head;
		}
		}
		break;
	}
}
/*卸下技能UI*/
int UI_UnloadSkill(Entity* player) {
	char i[nameLength];
	int num = -1;
head:
	system("CLS");
	printf("当前技能：\n");
	for (int i = 0;i < skillNum;i++)
		printf("%d.%s\n", i + 1, player->SkillList.data[i].name);
	printf("\n已拥有的技能：\n");
	Traversal(player->OwnSkill);
	printf("\n请选择你要卸下的技能(1-4)\n输入0退出\n");
	num = ToInt(gets_s(i));
	if (num == 0)
		return 0;
	if (num == -1) {
		printf("请输入正确的技能栏(1-4)!\n");
		Sleep(300);
		goto head;
	}
	int j = UnloadSkill(player, num);
	switch (j) {
	case -1:printf("此位置无技能，卸下失败！\n");break;
	case -2:printf("请输入正确的技能栏！");break;
	default:printf("已将%d位上的技能卸下！\n", num);break;
	}
	Sleep(300);
	goto head;
}
/*装载技能UI*/
int UI_LoadSkill(Entity* player) {
	char i[nameLength];
	int num;
head:
	system("CLS");
	printf("当前技能：\n");
	for (int i = 0;i < skillNum;i++)
		printf("%d.%s\n", i + 1, player->SkillList.data[i].name);
	printf("\n已拥有的技能：\n");
	Traversal(player->OwnSkill);
	printf("请输入你要装载的技能：\n输入0退出\n");
	num = ToInt(gets_s(i));
	if (num == 0)
		return 0;
	if (num == -1) {
		printf("请输入正确的技能代码!\n");
		Sleep(300);
		goto head;
	}
	int j = LoadSkill(player, num);
	switch (j) {
	case 0:printf("已成功装配技能！");break;
	case -1:printf("技能栏已满，无法装配！\n");break;
	case -2:printf("你没有此技能，请输入正确的技能！\n");break;
	}
	Sleep(300);
	goto head;
}

<<<<<<< Updated upstream
=======
/*药品界面UI*/
void UI_Food(Entity* player) {
	system("CLS");
	printf("*********************************************************\n");
	printf("*	名称:%-10s	等级:%-2d		金币:%-10d *\n", player->name, difficulty, player->Gold);
	printf("*-------------------------------------------------------*\n");
	printf("当前药品：\n");
	for (int i = 0;i < M;i++)
		printf("%d.%s\t数量：%d\t治疗量：%d\n", i + 1, player->Food[i].name, player->FoodNum[i], player->Food[i].effect);
	printf("输入任意键返回\n");
	getchar();
}

/*装备界面UI*/
void UI_Equi(Entity* player) {
	char chooseChar[nameLength];
	int choose;
head:
	UI_EquiInfo(*player);
	printf("\n你要做什么？\n");
	printf("1.  武器\n");
	printf("2.  盔甲\n");
	printf("0.  返回\n");
	choose = ToInt32(gets_s(chooseChar));
	switch (choose) {
	case 0:break;
	case 1: {
	Weaponhead:
		while (1) {
			UI_EquiInfo(*player);
			UI_WeaponInfo(*player);
			printf("\n请输入你要装备的武器：\n输入0可返回\n");
			choose = ToInt32(gets_s(chooseChar));
			if (choose > 0 && choose < weaponLength + 1)break;
			else if (choose == -1) {
				printf("\n请输入正确的选项！\n");
				Sleep(300);
				continue;
			}
			else goto head;
		}
		switch (LoadWeapon(player, choose)) {
		case -2: {
			printf("\n你没有该武器！\n");
			Sleep(300);
			goto Weaponhead;
		}
		default: {
			printf("\n已成功装备%s!\n", CatchWeapon(choose).name);
			Sleep(300);
			goto head;
		}
		}
	};break;
	case 2: {
	Armourhead:
		while (1) {
			UI_EquiInfo(*player);
			UI_ArmourInfo(*player);
			printf("\n请输入你要装备的盔甲：\n输入0可返回\n");
			choose = ToInt32(gets_s(chooseChar));
			if (choose > 0 && choose < weaponLength + 1)break;
			else if (choose == -1) {
				printf("\n请输入正确的选项！\n");
				Sleep(300);
				continue;
			}
			else goto head;
		}
		switch (LoadArmour(player, choose)) {
		case -2: {
			printf("\n你没有该盔甲！\n");
			Sleep(300);
			goto Weaponhead;
		}
		default: {
			printf("\n已成功装备%s!\n", CatchArmour(choose).name);
			Sleep(300);
			goto head;
		}
		}
	};break;

	default:printf("\n请输入正确的选项！\n");goto head;
	}
}
/*装备信息UI*/
void UI_EquiInfo(Entity player) {
	system("CLS");
	printf("*********************************************************\n");
	printf("*	名称:%-10s	等级:%-2d		金币:%-10d *\n", player.name, difficulty, player.Gold);
	printf("*-------------------------------------------------------*\n");
	printf("武器：%-20s攻击力：%-10d\n", player.Equi.Weapon.name, player.Equi.Weapon.ATK);
	printf("盔甲：%-20s防御力：%-10d\n", player.Equi.Armour.name, player.Equi.Armour.DEF);
}
/*武器信息UI*/
void UI_WeaponInfo(Entity player) {
	for (int i = 0;i < weaponLength;i++)
		printf("\n%d.%-20s数量：%-10d攻击力：%-10d\n", i + 1, CatchWeapon(i + 1).name, player.WeaponNum[i], CatchWeapon(i + 1).ATK);
}
/*盔甲信息UI*/
void UI_ArmourInfo(Entity player) {
	for (int i = 0;i < armourLength;i++)
		printf("\n%d.%-20s数量：%-10d防御力：%-10d\n", i + 1, CatchArmour(i + 1).name, player.ArmourNum[i], CatchArmour(i + 1).DEF);
}

/*商店界面UI*/
void UI_Shop(Entity* player) {
	UI_ShopInfo(*player);
	getchar();
}
/*商店信息UI*/
void UI_ShopInfo(Entity player) {
	system("CLS");
	printf("\n余额：%d\n", player.Gold);
	printf("#|*********************************|#\n");
	printf("#|！！！战士伤害高 烈火刀刀爆！！！|#\n");
	printf("#|*********************************|#\n");
	printf("#|！！！法师控制强 冰霜秒全场！！！|#\n");
	printf("#|*********************************|#\n");
	printf("#|！！！道士十五狗 全区横着走！！！|#\n");
	printf("#|*********************************|#\n");
	printf("#|！！！散人打金服 零氪能爽爆！！！|#\n");
	printf("#|*********************************|#\n");
	printf("#|！！！现金秒到账 装备能回收！！！|#\n");
	printf("#|*********************************|#\n");
	printf("#|！！！挂机能打宝 就在真传奇！！！|#\n");
	printf("#|*********************************|#\n");
	UI_ShopMenu();
}
/*商店列表UI*/
void UI_ShopMenu() {
	printf("\n你想要购买什么？\n");
	printf("\n1.属性\n");
	printf("\n2.装备\n");
	printf("\n3.药品\n");
	printf("\n0.返回\n");
}

/*装备武器*/
/*数量不足则返回-2*/
int LoadWeapon(Entity* player, int i) {
	if (player->WeaponNum[i - 1] == 0)
		return -2;
	if (player->Equi.Weapon.ID != 0) {
		int inum;
		for (int j = 0;j < weaponLength;j++)
			if (player->Equi.Weapon.ID == CatchWeapon(j + 1).ID)
				inum = j;
		player->Equi.Weapon = CatchWeapon(i);
		player->WeaponNum[i - 1]--;
		player->WeaponNum[inum]++;
		return 0;
	}
	else {
		player->Equi.Weapon = CatchWeapon(i);
		player->WeaponNum[i - 1]--;
		return 0;
	}
}
/*装备盔甲*/
/*数量不足则返回-2*/
int LoadArmour(Entity* player, int i) {
	if (player->ArmourNum[i - 1] == 0)
		return -2;
	if (player->Equi.Armour.ID != 0) {
		int inum;
		for (int j = 0;j < armourLength;j++)
			if (player->Equi.Armour.ID == CatchArmour(j + 1).ID)
				inum = j;
		player->Equi.Armour = CatchArmour(i);
		player->ArmourNum[i - 1]--;
		player->ArmourNum[inum]++;
		return 0;
	}
	player->Equi.Armour = CatchArmour(i);
	player->ArmourNum[i - 1]--;
	return 0;
}

>>>>>>> Stashed changes
/*获取技能*/
///i的值为player未获得技能表中的第i位
///即将player未获得技能表中的第i位删除并插入player已获得技能表中的第一位
void GetSkill(Entity* player, int i) {
	if (LengthNode(player->NoneSkill) >= 1) {
		InsertNode(player->OwnSkill, 1, Delete(player->NoneSkill, i)->data);
	}

}
/*卸下技能*/
int UnloadSkill(Entity* player, int i) {
	if (i<1 || i>skillNum)
		return -2;												//卸下位置越界
	if (player->SkillList.data[i - 1].ID == CatchSkill(0).ID)
		return -1;												//此技能为空，无法卸下
	InsertNode(player->OwnSkill, 1, player->SkillList.data[i - 1]);
	updata(&player->SkillList, i - 1, CatchSkill(0));
	return 0;
}
/*装配技能*/
int LoadSkill(Entity* player, int i) {
	if (i > LengthNode(player->OwnSkill))
		return -2;									//你没有此技能
	int j = Locate(player->SkillList, CatchSkill(0));
	if (j == -1)
		return -1;									//技能栏已满
	else
		updata(&player->SkillList, j, Delete(player->OwnSkill, i)->data);
}

<<<<<<< Updated upstream
=======
/*随机生成怪物*/
Entity SetMob() {
	srand((unsigned)time(NULL));				//随机数种子
	int i = rand() % 3 + 1;						//随机生成怪物类型
	char iname[nameLength];						//怪物名称
	switch (i) {
	case 1:strcpy_s(iname, "小怪");break;
	case 2:strcpy_s(iname, "精英");break;
	case 3:strcpy_s(iname, "首领");break;
	}
	Entity mob;
	SetEntity(&mob, i, iname);					//构建怪物实体并以随机到的类型赋值属性及名称
	for (int i = 0;i < skillNum;i++) {			//随机构建怪物技能表
		int a = 1 + rand() % (LengthNode(mob.NoneSkill));
		GetSkill(&mob, a);
		LoadSkill(&mob, 1);
	}
	for (int i = 0;i < M; i++) {				//随机构建怪物药物表
		int a = rand() % ((difficulty / 3) + 1);
		mob.FoodNum[M] = a;
	}
	mob.DEF = difficulty * 5 + rand() % difficulty * 10;					//随机生成怪物防御力
	mob.ATK = difficulty * 5 + rand() % difficulty * 10;					//随机生成怪物攻击力
	mob.Gold = difficulty * 5 + rand() % difficulty * 10;					//随机生成怪物携带金币
	return mob;
}

>>>>>>> Stashed changes
/*调用技能*/
Skill CatchSkill(int i) {
	/*技能列表*/
	Skill skill_ERROR{ -1,"ERROR",-114514 };
	Skill skill_Null{ 0, "NULL",0 };
	Skill skill_One{ 1,"撞击",10 };
	Skill skill_Two{ 2,"大兜子",30 };
	Skill skill_Three{ 3, "小亮の活",50 };
	Skill skill_Four{ 4, "药品",0 };
	/*函数返回*/
	switch (i) {
	case 0:return skill_Null;
	case 1:return skill_One;
	case 2:return skill_Two;
	case 3:return skill_Three;
	case 4:return skill_Four;
	default:return skill_ERROR;
	}
}




/*按任意键下一步*/
void next() {
	printf("按任意键进行下一步\n");
	while (getchar() != '\n');
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
/*已知值查找下标*/
int Locate(SkillList head, Skill x) {
	int i = 0;
	for (i;i < skillNum;i++) {
		if (head.data[i].ID == x.ID)
			return i;
	}
	return -1;
}

/*字符串转换为整型*/
int ToInt(char ch[]) {
	for (int i = 0;ch[i] != '\0';i++)					//若字符串中含有非数字，则返回值-1
		if (ch[i] < '0' || ch[i]>'9')
			return -1;
	int num = 0;
	int j;
	for (int i = 0;ch[i] != '\0';i++) {
		num *= pow(10, i);
		num += (ch[i] - 48);
	}
	return num;
}

/*单链表操作集*/
/*建空表*/
SkillLink InitListNode() {
	SkillLink head = (SkillLink)malloc(sizeof(SkillNode));
	head->next = NULL;
	return head;
}
/*插入*/
void InsertNode(SkillLink head, int i, Skill x) {
	SkillLink s = (SkillLink)malloc(sizeof(SkillNode));
	s->data = x;
	int j = 0;
	while (j < i - 1 && head) {
		head = head->next;
		j++;
	}
	s->next = head->next;
	head->next = s;
}
/*求表长*/
int LengthNode(SkillLink head) {
	int i = 0;
	while (head = head->next)
		i++;
	return i;
}
/*遍历*/
void Traversal(SkillLink head) {
	int i = 1;
	while (head = head->next) {
		printf("%d.%-6s\t伤害：%d\n", i, head->data.name, head->data.atk);
		i++;
	}
	putchar(10);
}
/*删除*/
SkillLink Delete(SkillLink head, int i) {
	SkillLink s = (SkillLink)malloc(sizeof(SkillNode));
	int j = 0;
	while (head->next && j < i - 1) {
		head = head->next;
		j++;
	}
	s = head->next;
	head->next = s->next;
	s->next = NULL;
	return s;
}
/*已知值查找序号*/
int LocateNode(SkillLink head, Skill x) {
	int i = 0;
	while (head) {
		head = head->next;
		i++;
		if (head->data.name == x.name)
			return i;
	}
	return -1;
}
/*已知序号查找值*/
SkillLink GetElem(SkillLink head, int i) {
	int j = 0;
	while (head && j < i) {
		head = head->next;
		j++;
	}
	return head;
}