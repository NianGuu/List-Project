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
#define skillLength 20				//总技能个数
#define M 7							//总药品个数
#define weaponLength 7				//总武器个数
#define armourLength 7				//总盔甲个数

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
/*药品结构体定义*/
typedef struct {
	char name[nameLength];		//药品名字 
	int effect;					//药品效果，每吃一个加多少生命值 
	int price;					//药品价格
}Food;
/*武器结构体定义*/
typedef struct {
	int ID;						//武器ID
	char name[nameLength];		//武器名称
	int ATK;					//武器攻击力
	int price;					//武器价格
}Weapon;
/*盔甲结构体定义*/
typedef struct {
	int ID;						//盔甲ID
	char name[nameLength];		//盔甲名称
	int DEF;					//盔甲防御力
	int price;					//盔甲价格
}Armour;
/*装备结构体定义*/
typedef struct {
	Weapon Weapon;				//武器
	Armour Armour;				//盔甲
}Equi;
/*实体结构体定义*/
typedef struct {
	char name[nameLength];				//实体名称
	int HP;								//实体生命值
	int ATK;							//实体攻击力
	int DEF;							//实体防御力
	Equi Equi;							//实体携带装备
	int WeaponNum[weaponLength];		//实体携带武器个数
	int ArmourNum[armourLength];		//实体携带盔甲个数
	int Gold;							//实体携带金币
	SkillList SkillList;				//实体所带技能表
	SkillLink OwnSkill;					//实体已拥有技能表
	SkillLink NoneSkill;				//实体未获得技能表
	Food Food[M];						//实体持有的药品
	int FoodNum[M];						//实体持有的药品数量
	int i;								//实体类型 
}Entity;

int UI_fight(Entity*);											/*战斗界面UI*/
int UI_fighting(Entity, Entity);								/*战斗中UI*/
void UI_Jade(Entity player, Entity mob, int i);					/*战斗信息*/
void UI_fightSkill(Entity player);								/*战斗中技能UI*/
void UI_fightFood(Entity player);								/*战斗中药品UI*/
void UI_gain(Entity*, Entity);									/*掉落物UI*/

void UI_skill(Entity*);											/*技能界面UI*/
int UI_UnloadSkill(Entity*);									/*卸下技能UI*/
int UI_LoadSkill(Entity*);										/*装载技能UI*/

void UI_Equi(Entity*);											/*装备界面UI*/
void UI_EquiInfo(Entity);										/*装备信息UI*/
void UI_WeaponInfo(Entity);										/*武器信息UI*/
void UI_ArmourInfo(Entity);										/*盔甲信息UI*/

int UI_Shop(Entity*);											/*商店界面UI*/
void UI_ShopInfo(Entity player);								/*商店信息UI*/
void UI_ShopMenu();												/*商品菜单UI*/
void UI_AttributesShop(Entity);									/*属性点商店UI*/
void UI_EquiShop(Entity);										/*装备商店UI*/
void UI_FoodShop(Entity);										/*药品商店UI*/
void UI_WeaponShop(Entity);										/*武器商店UI*/
void UI_ArmourShop(Entity);										/*盔甲商店UI*/

void UI_Food(Entity*);											/*药品界面UI*/

int LoadWeapon(Entity*, int);									/*装备武器*/
int LoadArmour(Entity*, int);									/*装备盔甲*/

Skill CatchSkill(int i);										/*调用技能*/
Food CatchFood(int i);											/*调用药品*/
Weapon CatchWeapon(int i);										/*调用武器*/
Armour CatchArmour(int i);										/*调用盔甲*/

int attack(Entity*, Entity*, int);								/*战斗计算*/

void SetEntity(Entity*, int, char name[nameLength]);			/*初始化实体*/
void GetSkill(Entity*, int);									/*获取新技能*/
void next();													/*按任意键下一步*/
Entity SetMob();												/*随机生成怪物*/

int UnloadSkill(Entity*, int);									/*卸下技能*/
int LoadSkill(Entity*, int);									/*装配技能*/

int ToInt32(char[]);									//字符串类型转换为整型

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
	system("mode con cols=140 lines=42 ");
	Entity player;
	char name[nameLength];
	printf("**************************************\n");
	printf("*     ******            *****        *\n");
	printf("*       ****            ****         *\n");
	printf("*       ***              ***         *\n");
	printf("*        ***            ***          *\n");
	printf("*         ***          ***           *\n");
	printf("*          ***         **            *\n");
	printf("*             **     **              *\n");
	printf("*               ****                 *\n");
	printf("*              * ** *                *\n");
	printf("*                **                  *\n");
	printf("*                **                  *\n");
	printf("*               ****                 *\n");
	printf("*        *** **********  ***         *\n");
	printf("*                                    *\n");
	printf("*               PLAY                 *\n");
	printf("*                                    *\n");
	printf("*                                    *\n");
	printf("*                                    *\n");
	printf("*            *游戏开始*              *\n");
	printf("**************************************\n");
	printf("\n请输入您的名称:  ");
	gets_s(name);
	SetEntity(&player, 2, name);
	GetSkill(&player, 1);
	LoadSkill(&player, 1);
	while (true) {
		system("CLS");
		printf("*********************************************************\n");
		printf("*                                                       *\n");
		printf("*	名称:%-10s	等级:%-2d		金币:%-10d *\n", player.name, difficulty, player.Gold);
		printf("*                                                       *\n");
		printf("*       生命值：%-8d攻击力：%-8d防御力：%-8d*\n", player.HP, player.ATK + player.Equi.Weapon.ATK, player.DEF + player.Equi.Armour.DEF);
		printf("*                                                       *\n");
		printf("*	操作列表:                                       *\n");
		printf("*                                                       *\n");
		printf("*	1.战斗		2.技能		3.药品		*\n");
		printf("*                                                       *\n");
		printf("*	4.装备		5.商店		0.退出		*\n");
		printf("*                                                       *\n");
		printf("*********************************************************\n");
		printf("\n输入你的操作\n");
		char choose;
		choose = getchar();
		while (getchar() != '\n');
		if (choose == '1')
			UI_fight(&player);
		else if (choose == '2')
			UI_skill(&player);
		else if (choose == '3')
			UI_Food(&player);
		else if (choose == '4')
			UI_Equi(&player);
		else if (choose == '5')
			UI_Shop(&player);
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
	/*血量*/
	entity->HP = 100 * difficulty + difficulty * i * 50;
	entity->i = i;								//实体类型
	InitList(&entity->SkillList);				//初始化技能表
	updata(&entity->SkillList, 0, CatchSkill(0));
	updata(&entity->SkillList, 1, CatchSkill(0));
	updata(&entity->SkillList, 2, CatchSkill(0));
	updata(&entity->SkillList, 3, CatchSkill(0));
	entity->OwnSkill = InitListNode();			//初始化已获取技能表
	entity->NoneSkill = InitListNode();			//初始化未获取技能表
	for (int i = 0;i < skillLength;i++)
		InsertNode(entity->NoneSkill, i + 1, CatchSkill(i + 1));
	for (int i = 0;i < M;i++) {					//初始化持有的药品
		entity->Food[i] = CatchFood(i + 1);
		entity->FoodNum[i] = 0;
	}
	entity->Equi.Armour = CatchArmour(0);		//初始化盔甲
	for (int i = 0;i < armourLength;i++)		//初始化盔甲数量
		entity->ArmourNum[i] = 0;
	entity->Equi.Weapon = CatchWeapon(0);		//初始化武器
	for (int i = 0;i < weaponLength;i++)		//初始化武器数量
		entity->WeaponNum[i] = 0;
	entity->Gold = 0;							//初始化金币
	entity->ATK = 10;							//初始化攻击力
	entity->DEF = 10;							//初始化防御力
}

/*战斗界面UI*/
int UI_fight(Entity* player) {
head:
	system("CLS");
	Entity mob = SetMob();
	printf("...........................................\n");
	printf(".	你遇到了一个%d级的%s！		  .\n", difficulty, mob.name);
	printf("...........................................\n\n");
	printf("!!!\n");
	printf("\n是否开始战斗？\n");
	printf("\nY/N  (输入Y开始，N返回,其余则刷新敌人)\n\n");
	while (char ch = getchar()) {					//让玩家选择是否战斗，是则继续，否则跳转至子函数开头
		while (getchar() != '\n');
		if (ch == 'Y' || ch == 'y')
			break;
		else if (ch == 'N' || ch == 'n')
			return 0;
		else goto head;
	}
	int result = UI_fighting(*player, mob);
	system("CLS");
	switch (result) {
	case -1: {			//战斗失败
		printf("\n  ╥﹏╥...\n");
		printf("+-----------------------+\n");
		printf("|	战斗失败！	|\n");
		printf("+-----------------------+\n");
		difficulty--;
		if (difficulty < 1)
			difficulty = 1;
	};break;
	case 1: {			//战斗胜利
		printf("***************************************\n");
		printf("*      ##     ###      ####           *\n");
		printf("*      ##    ##      ##     ##        *\n");
		printf("*      ##   ##     ##        ##       *\n");
		printf("*      ##  ##      ##         ##      *\n");
		printf("*      ## #        ##         ##      *\n");
		printf("*      ## #        ##         ##      *\n");
		printf("*      ## ##       ##        ##       *\n");
		printf("*      ##  ##       ##      ##        *\n");
		printf("*      ##   ###       ######          *\n");
		printf("*                                     *\n");
		printf("*                                     *\n");
		printf("*             *恭喜,你赢了*           *\n");
		printf("***************************************\n");
		printf("\n  o(^▽^)o\n");
		difficulty++;
		UI_gain(player, mob);
	};break;
	case 0: {			//逃跑
		printf("\n  <(￣ ﹌ ￣)@m 就这？\n");
		printf("\n你逃跑了！\n");
	};break;
	}
	next();
	return 0;
}
/*战斗中UI*/
/*战斗胜利则返回1，战斗失败则返回-1*/
int UI_fighting(Entity player, Entity mob) {
	putchar(10);
	int i = 0;
	char chooseChar[nameLength];
	int choose;
	short branch;
	int playerMaxHp = player.HP;
	int mobMaxHp = mob.HP;
	srand((unsigned)time(NULL));
	while (player.HP > 0 && mob.HP > 0) {
		i++;
	head:
		UI_Jade(player, mob, i);
		printf("#|*********************************|#\n");
		printf("#|                                 |#\n");
		printf("#|        你要进行什么操作?        |#\n");
		printf("#|                                 |#\n");
		printf("#|            1.技能               |#\n");
		printf("#|                                 |#\n");
		printf("#|            2.药品               |#\n");
		printf("#|                                 |#\n");
		printf("#|            0.逃跑               |#\n");
		printf("#|                                 |#\n");
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
			while (getchar() != '\n');
			if (chooseChar[1] == '0')
				break;
			else
				goto head;
		}
		else {
			printf("\n请输入正确的选项！\n");
			Sleep(200);
			goto head;
		}
		choose = ToInt32(gets_s(chooseChar));
		if (choose == 0)
			goto head;
		else
			if (branch == 1) {								//选择技能
				if (choose<1 || choose>skillNum) {			//若输入越界则返回技能列表
					printf("\n请输入正确的选项！\n");
					Sleep(200);
					goto branch1;
				}
				printf("\n%s使用了%s,对%s造成了%d的伤害！", player.name, player.SkillList.data[choose - 1].name, mob.name, attack(&player, &mob, choose));
				if (mob.HP <= 0)break;						//判定胜负
			}
			else if (branch == 2) {							//选择药品
				if (choose<1 || choose>M) {					//若输入越界则返回药品列表
					printf("\n请输入正确的选项！\n");
					Sleep(200);
					goto branch2;
				}
				if (player.FoodNum[choose - 1] < 1) {
					printf("\n当前药品数量不足！\n");
					Sleep(200);
					goto branch2;
				}
				player.HP += player.Food[choose - 1].effect;	//药品使用效果
				if (player.HP > playerMaxHp)
					player.HP = playerMaxHp;
				player.FoodNum[choose - 1]--;
				printf("\n%s使用了%s,恢复了%d的生命！\n", player.name, player.Food[choose - 1].name, player.Food[choose - 1].effect);
			}
		Sleep(500);
		if (mob.HP <= mobMaxHp / 2) {
			for (int j = 0;j < M;j++) {
				if (mob.FoodNum[j] > 0) {
					choose = 1 + rand() % 2;		//当怪物拥有药品并且血量到达一半时，将有概率使用药品
					branch = -1;
					break;
				}
			}
		}
		if (branch != -1)							//当怪物不满足上面的条件，则只会使用技能
			choose = 1;
		if (choose == 1) {							//当怪物使用技能时
			choose = 1 + rand() % skillNum;			//随机数决定怪物使用的技能
			printf("\n%s使用了%s，对%s造成了%d的伤害！\n", mob.name, mob.SkillList.data[choose - 1].name, player.name, attack(&mob, &player, choose));
			if (player.HP <= 0)break;				//判定胜负
		}
		else if (choose == 2) {						//当怪物使用药品时
			while (choose = 1 + rand() % M)
				if (mob.FoodNum[choose - 1] > 0)
					break;
			mob.HP += mob.Food[choose - 1].effect;
			if (mob.HP > mobMaxHp)
				mob.HP = mobMaxHp;
			mob.FoodNum[choose - 1]--;
			printf("\n%s使用了%s,恢复了%d的生命！\n", mob.name, mob.Food[choose - 1].name, mob.Food[choose - 1].effect);
		}
		Sleep(500);
	}
	Sleep(500);
	if (player.HP <= 0)				//失败返回值-1
		return -1;
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
		printf("\n    %-2d.%-20s伤害：%-10d\n", i + 1, player.SkillList.data[i].name, player.SkillList.data[i].atk);
	printf("\n    输入0退出\n\n");
}
/*战斗中的药品界面*/
void UI_fightFood(Entity player) {
	printf("你想要使用哪个药品？\n");
	for (int i = 0;i < M;i++)
		printf("\n    %-2d.%-20s数量：%-10d治疗量：%-10d\n", i + 1, player.Food[i].name, player.FoodNum[i], player.Food[i].effect);
	printf("\n    输入0退出\n\n");
}
/*掉落物*/
/*以怪物为参数计算掉落物*/
void UI_gain(Entity* player, Entity mob) {
	srand((unsigned)time(NULL));

	int get = 1 + rand() % skillNum;			//随机数决定掉落怪物的哪个技能
	if (LocateNode(player->NoneSkill, mob.SkillList.data[get - 1]) != -1) {
		GetSkill(player, LocateNode(player->NoneSkill, mob.SkillList.data[get - 1]));
		printf("\n你获得了技能：%s！\n", mob.SkillList.data[get - 1].name);
	}
	else {
		player->Gold += mob.SkillList.data[get - 1].atk * 10;
		printf("\n你已有技能：%s！已转化为%d金币\n", mob.SkillList.data[get - 1].name, mob.SkillList.data[get - 1].atk * 10);
	}
	player->Gold += mob.Gold;					//获取怪物的金币
	printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$");
	printf("\n$                       $");
	printf("\n$    你获得了%-3d金币！  $", mob.Gold);
	printf("\n$                       $");
	printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$\n");
}

/*战斗计算*/
/*攻击方在前，受击方在后,choose为使用的技能，返回值为造成伤害*/
int attack(Entity* entity1, Entity* entity2, int choose) {
	int harm;
	harm = entity1->SkillList.data[choose - 1].atk + (entity1->ATK / 10) * entity1->SkillList.data[choose - 1].atk - (entity2->DEF / 20) * entity1->SkillList.data[choose - 1].atk;
	if (harm <= 0)
		harm = 1;
	entity2->HP -= harm;
	return harm;
}

/*技能界面UI*/
void UI_skill(Entity* player) {
head:
	system("CLS");
	printf("*********************************************************\n");
	printf("*	名称:%-10s	等级:%-2d		金币:%-10d *\n", player->name, difficulty, player->Gold);
	printf("*-------------------------------------------------------*\n");
	printf("*当前技能:                                              *\n");
	for (int i = 0;i < skillNum;i++)
		printf("*%d.%-20s                                 *\n", i + 1, player->SkillList.data[i].name);
	printf("*-------------------------------------------------------*\n");
	/*printf("\n已拥有的技能:\n\n");
	Traversal(player->OwnSkill);*/
	printf("\n请输入操作：\n");
	printf("\n1.查看未拥有技能\n");
	printf("\n2.卸下技能\n");
	printf("\n3.装载技能\n");
	printf("\n0.退出\n");
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
	printf("\n已拥有的技能：\n\n");
	Traversal(player->OwnSkill);
	printf("\n请选择你要卸下的技能(1-4)\n\n输入0退出\n\n");
	num = ToInt32(gets_s(i));
	if (num == 0)
		return 0;
	if (num == -1) {
		printf("请输入正确的技能栏(1-4)!\n");
		Sleep(300);
		goto head;
	}
	int j = UnloadSkill(player, num);
	switch (j) {
	case -1:printf("\n此位置无技能，卸下失败！\n");break;
	case -2:printf("\n请输入正确的技能栏！\n");break;
	default:printf("\n已将%d位上的技能卸下！\n", num);break;
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
	printf("\n已拥有的技能：\n\n");
	Traversal(player->OwnSkill);
	printf("\n请输入你要装载的技能：\n\n输入0退出\n");
	num = ToInt32(gets_s(i));
	if (num == 0)
		return 0;
	if (num == -1) {
		printf("\n请输入正确的技能代码!\n");
		Sleep(300);
		goto head;
	}
	int j = LoadSkill(player, num);
	switch (j) {
	case 0:printf("\n已成功装配技能！\n");break;
	case -1:printf("\n技能栏已满，无法装配！\n");break;
	case -2:printf("\n你没有此技能，请输入正确的技能！\n");break;
	}
	Sleep(300);
	goto head;
}

/*药品界面UI*/
void UI_Food(Entity* player) {
	system("CLS");
	printf("*********************************************************\n");
	printf("*	名称:%-10s	等级:%-2d		金币:%-10d *\n", player->name, difficulty, player->Gold);
	printf("*-------------------------------------------------------*\n");
	printf("当前药品：\n");
	for (int i = 0;i < M;i++)
		printf("%d.%-20s数量：%-10d治疗量：%-10d\n", i + 1, player->Food[i].name, player->FoodNum[i], player->Food[i].effect);
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
	printf("\n1.  武器\n");
	printf("\n2.  盔甲\n");
	printf("\n0.  返回\n");
	choose = ToInt32(gets_s(chooseChar));
	switch (choose) {
	case 0:break;
	case 1: {
	Weaponhead:
		while (1) {
			UI_EquiInfo(*player);
			UI_WeaponInfo(*player);
			printf("\n请输入你要装备的武器：\n\n输入0可返回\n");
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
			printf("\n请输入你要装备的盔甲：\n\n输入0可返回\n");
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
	printf("\n武器：%-20s攻击力：%-10d\n", player.Equi.Weapon.name, player.Equi.Weapon.ATK);
	printf("\n盔甲：%-20s防御力：%-10d\n", player.Equi.Armour.name, player.Equi.Armour.DEF);
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
int UI_Shop(Entity* player) {
head:
	UI_ShopInfo(*player);
	UI_ShopMenu();
	int choose;
	char chooseChar[nameLength];
	choose = ToInt32(gets_s(chooseChar));
	switch (choose) {
	case 1: {								//属性点商城
		while (1) {
			UI_AttributesShop(*player);
			choose = ToInt32(gets_s(chooseChar));
			if (choose >= 0 && choose < 4) {
				switch (choose) {
				case 0:goto head;
				case 1: {											//买血量
					if (player->Gold >= 10) {
						player->Gold -= 10;
						player->HP += 10;
						printf("\n购物成功，欢迎下次光临！\n");
						Sleep(300);
						continue;
					}
					else {
						printf("\n你没有足够的金币！\n");
						Sleep(300);
						continue;
					}
				};break;
				case 2: {											//买攻击
					if (player->Gold >= 100) {
						player->Gold -= 100;
						player->ATK += 10;
						printf("\n购物成功，欢迎下次光临！\n");
						Sleep(300);
						continue;
					}
					else {
						printf("\n你没有足够的金币！\n");
						Sleep(300);
						continue;
					}
				};break;
				case 3: {											//买防御
					if (player->Gold >= 100) {
						player->Gold -= 100;
						player->DEF += 10;
						printf("\n购物成功，欢迎下次光临！\n");
						Sleep(300);
						continue;
					}
					else {
						printf("\n你没有足够的金币！\n");
						Sleep(300);
						continue;
					}
				};break;
				}
			}
			else {
				printf("请输入正确的选项！\n");
				Sleep(300);
				continue;
			}
		}
	};break;
	case 2: {								//装备商城
		while (1) {
		equihead:
			UI_EquiShop(*player);
			choose = ToInt32(gets_s(chooseChar));
			if (choose == 0)
				goto head;
			else if (choose == 1) {									//武器商店
				while (1) {
					UI_WeaponShop(*player);
					choose = ToInt32(gets_s(chooseChar));
					if (choose == 0)
						goto equihead;
					if (choose > 0 && choose < weaponLength + 1) {
						if (player->Gold >= CatchWeapon(choose).price) {
							player->Gold -= CatchWeapon(choose).price;
							player->WeaponNum[choose - 1]++;
							printf("\n购物成功，欢迎下次光临！\n");
							Sleep(300);
							continue;
						}
						else {
							printf("\n你没有足够的金币！\n");
							Sleep(300);
							continue;
						}
					}
					else {
						printf("请输入正确的选项！\n");
						Sleep(300);
						continue;
					}
				}
			}
			else if (choose == 2) {									//盔甲商店
				while (1) {
					UI_ArmourShop(*player);
					choose = ToInt32(gets_s(chooseChar));
					if (choose == 0)
						goto equihead;
					if (choose > 0 && choose < armourLength + 1) {
						if (player->Gold >= CatchArmour(choose).price) {
							player->Gold -= CatchArmour(choose).price;
							player->ArmourNum[choose - 1]++;
							printf("\n购物成功，欢迎下次光临！\n");
							Sleep(300);
							continue;
						}
						else {
							printf("\n你没有足够的金币！\n");
							Sleep(300);
							continue;
						}
					}
					else {
						printf("请输入正确的选项！\n");
						Sleep(300);
						continue;
					}
				}
			}
			else {
				printf("请输入正确的选项！\n");
				Sleep(300);
				continue;
			}
		}
	};break;
	case 3: {								//药品商城
		while (1) {
			UI_FoodShop(*player);
			choose = ToInt32(gets_s(chooseChar));
			if (choose == 0)
				goto head;
			else if (choose > 0 && choose < M + 1) {
				if (player->Gold >= player->Food[choose - 1].price) {
					player->Gold -= player->Food[choose - 1].price;
					player->FoodNum[choose - 1]++;
					printf("\n购物成功，欢迎下次光临！\n");
					Sleep(300);
					continue;
				}
				else {
					printf("\n你没有足够的金币！\n");
					Sleep(300);
					continue;
				}
			}
			else {
				printf("请输入正确的选项！\n");
				Sleep(300);
				continue;
			}
		}
	}
	case 0:return 0;
	default: {
		printf("\n请输入正确的选项！\n");
		Sleep(300);
		goto head;
	}
	}

}
/*商店信息UI*/
void UI_ShopInfo(Entity player) {
	system("CLS");
	printf("#|*********************************|#\n");
	printf("#|！！！战士伤害高 烈火刀刀爆！！！|#\n");
	printf("#|*********************************|#\n");
	printf("#|！！！法师控制强 冰霜秒全场！！！|#\n");
	printf("#|*********************************|#\n");
	printf("#|！！！道士十五狗 全区横着走！！！|#\n");
	printf("#|*********************************|#\n");
	printf("#|！！！散人打金服 零氪能爽爆！！！|#\n");
	printf("#|*********************************|#\n");
	printf("#|！！！装备能回收 现金秒到账！！！|#\n");
	printf("#|*********************************|#\n");
	printf("#|！！！挂机能打宝 就在真传奇！！！|#\n");
	printf("#|*********************************|#\n");
	printf("\n余额：%d\n", player.Gold);
}
/*商店列表UI*/
void UI_ShopMenu() {
	printf("\n你想要购买什么？\n");
	printf("\n1.属性\n");
	printf("\n2.装备\n");
	printf("\n3.药品\n");
	printf("\n0.返回\n");
}
/*属性点商城*/
void UI_AttributesShop(Entity player) {
	UI_ShopInfo(player);
	printf("\n商品：\n");
	printf("\n1.生命值\t价格：10金币/10点\t当前：%d\n", player.HP);
	printf("\n2.攻击力\t价格：100金币/10点\t当前：%d\n", player.ATK);
	printf("\n3.防御力\t价格：100金币/10点\t当前：%d\n", player.DEF);
	printf("\n你要购买什么？（输入0返回）\n");
}
/*装备商城*/
void UI_EquiShop(Entity player) {
	UI_ShopInfo(player);
	printf("\n1.武器\n");
	printf("\n2.盔甲\n");
	printf("\n你要购买什么？（输入0返回）\n");
}
/*药品商场*/
void UI_FoodShop(Entity player) {
	UI_ShopInfo(player);
	printf("\n商品：\n");
	for (int i = 0;i < M;i++)
		printf("\n%d.%-20s治疗量：%-10d价格：%-10d当前已有：%-10d\n", i + 1, player.Food[i].name, player.Food[i].effect, player.Food[i].price, player.FoodNum[i]);
	printf("\n你要购买什么？（输入0返回）\n");
}
/*武器商店*/
void UI_WeaponShop(Entity player) {
	UI_ShopInfo(player);
	printf("\n商品：\n");
	for (int i = 0;i < weaponLength;i++) {
		printf("\n%d,%-20s攻击力：%-10d价格：%-10d已拥有：%-10d\n", i + 1, CatchWeapon(i + 1).name, CatchWeapon(i + 1).ATK, CatchWeapon(i + 1).price, player.WeaponNum[i]);
	}
	printf("\n你要购买什么？（输入0返回）\n");
}
/*盔甲商店*/
void UI_ArmourShop(Entity player) {
	UI_ShopInfo(player);
	printf("\n商品：\n");
	for (int i = 0;i < armourLength;i++) {
		printf("\n%d,%-20s防御力：%-10d价格：%-10d已拥有：%-10d\n", i + 1, CatchArmour(i + 1).name, CatchArmour(i + 1).DEF, CatchArmour(i + 1).price, player.ArmourNum[i]);
	}
	printf("\n你要购买什么？（输入0返回）\n");
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
/*i为已获得技能栏中的第i位*/
int LoadSkill(Entity* player, int i) {
	if (i > LengthNode(player->OwnSkill))
		return -2;									//你没有此技能
	int j = Locate(player->SkillList, CatchSkill(0));
	if (j == -1)
		return -1;									//技能栏已满
	else
		updata(&player->SkillList, j, Delete(player->OwnSkill, i)->data);
}

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
	mob.HP *= (i / 2.0);
	mob.DEF = (difficulty * 5 + rand() % difficulty * 10) * (i / 2.0);					//随机生成怪物防御力
	mob.ATK = (difficulty * 5 + rand() % difficulty * 10) * (i / 2.0);					//随机生成怪物攻击力
	mob.Gold = 10 * (difficulty * 5 + rand() % difficulty * 10) * (i / 2.0);				//随机生成怪物携带金币
	return mob;
}

/*调用技能*/
Skill CatchSkill(int i) {
	/*技能列表*/
	Skill skill_ERROR{ -1,"ERROR",114514 };
	Skill skill_Null{ 0, "NULL",0 };
	Skill skill_One{ 1,"撞击",10 };
	Skill skill_Two{ 2,"网抑云",12 };
	Skill skill_Three{ 3,"咖喱棒！",15 };
	Skill skill_Four{ 4,"拒收病婿",18 };
	Skill skill_Five{ 5,"光照八荒",20 };
	Skill skill_Six{ 6,"猛猛蓄力嘎嘎出",25 };
	Skill skill_Seven{ 7,"嘚嘚比",28 };
	Skill skill_Eight{ 8,"刺挠",30 };
	Skill skill_Nine{ 9,"嘎嘎蓄转振",30 };
	Skill skill_Ten{ 10,"大兜子",35 };
	Skill skill_Eleven{ 11,"噩梦缠绕",40 };
	Skill skill_Twelve{ 12,"豆浆烩面",45 };
	Skill skill_Thirteen{ 13,"小亮の活",50 };
	Skill skill_Fourteen{ 14,"老坛大臭脚",58 };
	Skill skill_Fifteen{ 15,"猫猫头来全杀了",69 };
	Skill skill_Sixteen{ 16,"国榜甘雨dd瑶妹",77 };
	Skill skill_Seventeen{ 17,"火相幻身",88 };
	Skill skill_Eighteen{ 18,"德莉莎世界第一可爱",90 };
	Skill skill_Nineteen{ 19,"柴猫猫给了你一拳",100 };
	Skill skill_Twenty{ 20,"沙城霸主烈火の刀！",120 };
	/*函数返回*/
	switch (i) {
	case 0:return skill_Null;
	case 1:return skill_One;
	case 2:return skill_Two;
	case 3:return skill_Three;
	case 4:return skill_Four;
	case 5:return skill_Five;
	case 6:return skill_Six;
	case 7:return skill_Seven;
	case 8:return skill_Eight;
	case 9:return skill_Nine;
	case 10:return skill_Ten;
	case 11:return skill_Eleven;
	case 12:return skill_Twelve;
	case 13:return skill_Thirteen;
	case 14:return skill_Fourteen;
	case 15:return skill_Fifteen;
	case 16:return skill_Sixteen;
	case 17:return skill_Seventeen;
	case 18:return skill_Eighteen;
	case 19:return skill_Nineteen;
	case 20:return skill_Twenty;
	default:return skill_ERROR;
	}
}
/*调用药品*/
Food CatchFood(int i) {
	/*药品列表*/
	Food food_ERROR{ "ERROR",-114514,-1 };
	Food food_One{ "小奶一口",200 ,100 };
	Food food_Two{ "胡桃率先出殡",400 ,200 };
	Food food_Three{ "续命术！",600 ,400 };
	Food food_Four{ "稻妻鱼子酱（？）",800 ,600 };
	Food food_Five{ "下北泽の红茶",1000 ,800 };
	Food food_Six{ "吸一口柴猫猫",1500 ,1200 };
	Food food_Seven{ "我出金了！！！",2000 ,1500 };
	/*药品返回*/
	switch (i) {
	case 1:return food_One;
	case 2:return food_Two;
	case 3:return food_Three;
	case 4:return food_Four;
	case 5:return food_Five;
	case 6:return food_Six;
	case 7:return food_Seven;
	default:return food_ERROR;
	}
}
/*调用武器*/
Weapon CatchWeapon(int i) {
	/*武器列表*/
	Weapon weapon_ERROR{ -1,"ERROR",-114514 ,-1 };
	Weapon weapon_Null{ 0,"NULL",0 ,0 };
	Weapon weapon_One{ 1,"博弈失败掏出白太",10,100 };
	Weapon weapon_Two{ 2,"我振他惊雷啊",20,200 };
	Weapon weapon_Three{ 3,"好振下一把",40,400 };
	Weapon weapon_Four{ 4,"双爆太古神龙拳套",80,800 };
	Weapon weapon_Five{ 5,"说啥我都对对对",150,1600 };
	Weapon weapon_Six{ 6,"猫猫头！",200,3200 };
	Weapon weapon_Seven{ 7,"沙城之主の烈火屠龙",250,6480 };
	/*武器返回*/
	switch (i) {
	case 0:return weapon_Null;
	case 1:return weapon_One;
	case 2:return weapon_Two;
	case 3:return weapon_Three;
	case 4:return weapon_Four;
	case 5:return weapon_Five;
	case 6:return weapon_Six;
	case 7:return weapon_Seven;
	default:return weapon_ERROR;
	}
}
/*调用盔甲*/
Armour CatchArmour(int i) {
	/*盔甲列表*/
	Armour armour_ERROR{ -1,"ERROR",-114514,-1 };
	Armour armour_Null{ 0,"NULL",0 ,0 };
	Armour armour_One{ 1,"孙悟空的戏法",10,100 };
	Armour armour_Two{ 2,"尹娜的真言",20 ,200 };
	Armour armour_Three{ 3,"御宅花织",30,300 };
	Armour armour_Four{ 4,"豆浆烩面！",40,400 };
	Armour armour_Five{ 5,"桥洞底下盖小被",50,500 };
	Armour armour_Six{ 6,"猫猫！",50,500 };
	Armour armour_Seven{ 7,"沙城之主の王霸圣战",50,500 };
	/*盔甲返回*/
	switch (i) {
	case 0:return armour_Null;
	case 1:return armour_One;
	case 2:return armour_Two;
	case 3:return armour_Three;
	case 4:return armour_Four;
	case 5:return armour_Five;
	case 6:return armour_Six;
	case 7:return armour_Seven;
	default:return armour_ERROR;
	}
}
/*按任意键下一步*/
void next() {
	printf("\n按任意键进行下一步\n");
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
int ToInt32(char ch[]) {
	if (ch[0] == '\0')
		return -1;
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
		printf("\n%d.%-20s\t伤害：%d\n", i, head->data.name, head->data.atk);
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
	while (head->next) {
		head = head->next;
		i++;
		if (head->data.ID == x.ID)
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