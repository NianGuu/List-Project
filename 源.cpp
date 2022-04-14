#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include<math.h> 

#define ERR_SKILL_LIST_EXCEED -1	//技能表越界

#define skillNum 4					//实体技能个数
#define nameLength 20				//名称长度
#define skillLength 5				//总技能个数
#define M 3							//总药品个数

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
}Food;
/*实体结构体定义*/
typedef struct {
	char name[nameLength];		//实体名称
	int HP;						//实体生命值
	SkillList SkillList;		//实体所带技能表
	SkillLink OwnSkill;			//实体已拥有技能表
	SkillLink NoneSkill;		//实体未获得技能表
	Food Food[M];				//实体持有的药品
	int FoodNum[M];				//实体持有的药品数量
	int i;						//实体类型 
}Entity;

void UI_fight(Entity*);											/*战斗界面UI*/
int UI_fighting(Entity, Entity);								/*战斗中UI*/
void UI_Jade(Entity player, Entity mob, int i);					/*战斗信息*/
void UI_fightSkill(Entity player);								/*战斗中技能UI*/
void UI_fightFood(Entity player);								/*战斗中药品UI*/
void UI_gain(Entity*,Entity);									/*掉落物UI*/

void UI_skill(Entity*);											/*技能界面UI*/
int UI_UnloadSkill(Entity*);									/*卸下技能UI*/
int UI_LoadSkill(Entity*);										/*装载技能UI*/

void UI_Food(Entity*);											/*药品界面UI*/

Food CatchFood(int i);											/*调用药品*/

int attack(Entity*, Entity*, int);								/*战斗计算*/

void SetEntity(Entity*, int, char name[nameLength]);			/*初始化实体*/
Skill CatchSkill(int i);										/*调用技能*/
void GetSkill(Entity*, int);									/*获取新技能*/
void next();													/*按任意键下一步*/
Entity SetMob();												/*随机生成怪物*/

int UnloadSkill(Entity*, int);									/*卸下技能*/
int LoadSkill(Entity*, int);									/*装配技能*/

int ToInt(char[]);									//字符串类型转换为整型

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
	printf("欢迎进入游戏\n");
	printf("***********\n");
	printf("请输入您的名称\n");
	putchar('\n');
	gets_s(name);
	SetEntity(&player, 2, name);
	while (true) {
		system("CLS");
		puts(player.name);
		printf("等级：%d\n", difficulty);
		printf("请输入你的操作：\n");
		printf("*************************\n");
		printf("1.战斗\n");
		printf("2.技能\n");
		printf("3.药品\n");
		printf("0.退出\n");
		char choose;
		choose = getchar();
		while (getchar() != '\n');
		if (choose == '1')
			UI_fight(&player);
		else if (choose == '2')
			UI_skill(&player);
		else if (choose == '3')
			UI_Food(&player);
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
	updata(&entity->SkillList, 0, CatchSkill(4));
	updata(&entity->SkillList, 1, CatchSkill(0));
	updata(&entity->SkillList, 2, CatchSkill(0));
	updata(&entity->SkillList, 3, CatchSkill(0));
	entity->OwnSkill = InitListNode();			//初始化已获取技能表
	entity->NoneSkill = InitListNode();			//初始化未获取技能表
	for (int i = 0;i < skillLength;i++)
		InsertNode(entity->NoneSkill, i + 1, CatchSkill(i + 1));
	for (int i = 0;i < M;i++) {					//初始化持有的药品
		entity->Food[i] = CatchFood(i + 1);
		entity->FoodNum[i] = 1;
	}
}

/*战斗界面UI*/
void UI_fight(Entity* player) {
head:
	system("CLS");
	Entity mob = SetMob();
	printf("你遇到了一个%d级的%s！\n", difficulty, mob.name);
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
	int result = UI_fighting(*player,mob);
	system("CLS");
	switch (result) {
	case -1: {			//战斗失败
		printf("\n战斗失败！\n");
		difficulty--;
	};break;
	case 1: {			//战斗胜利
		printf("\n战斗胜利！\n");
		difficulty++;
	};break;
	case 0: {			//逃跑
		printf("\n你逃跑了！\n");
	};break;
	}
	system("PAUSE");
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
		printf("你要进行什么操作?\n");
		printf("    1.技能\n");
		printf("    2.药品\n");
		printf("    0.逃跑\n");
		choose = ToInt(gets_s(chooseChar));
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
			printf("\n确定要逃跑吗？\n输入0确认选择\n");
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
		choose = ToInt(gets_s(chooseChar));
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
		printf("    %-2d.%-10s伤害：%-10d\n", i + 1, player.SkillList.data[i].name, player.SkillList.data[i].atk);
	printf("    输入0退出\n\n");
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
void UI_gain(Entity* player,Entity mob) {
	srand((unsigned)time(NULL));
	int get = 1 + rand() % skillNum;
}

/*战斗计算*/
/*攻击方在前，受击方在后,choose为使用的技能，返回值为造成伤害*/
int attack(Entity* entity1, Entity* entity2, int choose) {
	int harm;
	harm = entity1->SkillList.data[choose - 1].atk;
	entity2->HP -= harm;
	return harm;
}

/*技能界面UI*/
void UI_skill(Entity* player) {
head:
	system("CLS");
	printf("%s\n等级：%d\n", player->name, difficulty);
	printf("当前技能：\n");
	for (int i = 0;i < skillNum;i++)
		printf("%d.%s\n", i + 1, player->SkillList.data[i].name);
	printf("\n已拥有的技能：\n");
	Traversal(player->OwnSkill);
	printf("\n请输入操作：\n");
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

/*药品界面UI*/
void UI_Food(Entity* player) {
	system("CLS");
	printf("%s\n等级：%d\n", player->name, difficulty);
	printf("当前药品：\n");
	for (int i = 0;i < M;i++)
		printf("%d.%s\t数量：%d\t治疗量：%d\n", i + 1, player->Food[i].name, player->FoodNum[i], player->Food[i].effect);
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
	return mob;
}

/*调用技能*/
Skill CatchSkill(int i) {
	/*技能列表*/
	Skill skill_ERROR{ -1,"ERROR",-114514 };
	Skill skill_Null{ 0, "NULL",0 };
	Skill skill_One{ 1,"撞击",10 };
	Skill skill_Two{ 2,"大兜子",30 };
	Skill skill_Three{ 3, "小亮の活",50 };
	Skill skill_Four{ 4,"五十万",70 };
	Skill skill_Five{ 5,"鸡汤",90 };
	/*函数返回*/
	switch (i) {
	case 0:return skill_Null;
	case 1:return skill_One;
	case 2:return skill_Two;
	case 3:return skill_Three;
	case 4:return skill_Four;
	case 5:return skill_Five;
	default:return skill_ERROR;
	}
}
/*调用药品*/
Food CatchFood(int i) {
	/*药品列表*/
	Food food_ERROR{ "ERROR",-114514 };
	Food food_One{ "金疮药",20 };
	Food food_Two{ "大力丸",40 };
	Food food_Three{ "续命丸",60 };
	/*药品返回*/
	switch (i) {
	case 1:return food_One;
	case 2:return food_Two;
	case 3:return food_Three;
	default:return food_ERROR;
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