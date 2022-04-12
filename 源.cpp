#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>

#define ERR_SKILL_LIST_EXCEED -1	//技能表越界

#define skillNum 4					//实体技能个数
#define nameLength 20				//名称长度
#define skillLength 3				//总技能个数

/*技能结构体定义*/
typedef struct {
	char name[nameLength];		//技能名称
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
/*实体结构体定义*/
typedef struct {
	char name[nameLength];		//实体名称
	int HP;						//实体生命值
	SkillList SkillList;		//实体所带技能表
	SkillLink OwnSkill;			//实体已拥有技能表
	SkillLink NoneSkill;		//实体未获得技能表
	int i;						//实体类型 
}Entity;

void UI_fight(Entity*);											/*战斗界面UI*/
int UI_fighting(Entity, Entity);								/*战斗中UI*/
void UI_skill(Entity*);											/*技能界面UI*/
void setEntity(Entity*, int, char name[nameLength]);			/*初始化实体*/
Skill catchSkill(int i);										/*调用技能*/
void GetSkill(Entity*,int);										/*获取新技能*/
void next();													/*按任意键下一步*/

/*顺序表操作集*/
void InitList(SkillList*);							//建空表
int Length(SkillList);								//求表长
void updata(SkillList*, int, Skill);				//修改数据

/*单链表操作集*/
SkillLink InitListNode();						//初始化单链表
void InsertNode(SkillLink, int, Skill);			//插入单链表
int Length(SkillLink);							//求表长
void Traversal(SkillLink);						//遍历
SkillLink Delete(SkillLink, int);				//删除
int Locate(SkillLink, Skill);					//已知值查找序号

int difficulty = 1;		/*难度系数*/



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
		printf("0.退出\n");
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
void setEntity(Entity* entity, int i, char name[nameLength]) {
	strcpy_s(entity->name, name);				//名称
	entity->HP = i * difficulty * 100;			//血量
	entity->i = i;								//实体类型
	InitList(&entity->SkillList);				//初始化技能表
	updata(&entity->SkillList, 0, catchSkill(0));
	updata(&entity->SkillList, 1, catchSkill(0));
	updata(&entity->SkillList, 2, catchSkill(0));
	updata(&entity->SkillList, 3, catchSkill(0));
	entity->OwnSkill = InitListNode();			//初始化已获取技能表
	entity->NoneSkill = InitListNode();			//初始化未获取技能表
	for (int i = 0;i < skillLength;i++)
		InsertNode(entity->NoneSkill, i+1, catchSkill(i + 1));
}

/*战斗界面UI*/
void UI_fight(Entity* player) {
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
	difficulty += UI_fighting(*player, mob);		//若胜利则难度系数+1，若失败则-1。
}
/*战斗中UI*/
int UI_fighting(Entity player, Entity mob) {
	system("CLS");
	putchar(10);
	int i = 0;
	int choose;
	while (player.HP > 0 && mob.HP > 0) {
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
	printf("0.退出\n");
	printf("1.查看未拥有技能\n");
	while (char i = getchar()) {
		while (getchar() != '\n');
		switch (i) {
		case '0':break;
		case '1': {
			system("CLS");
			Traversal(player->NoneSkill);
			next();
		};goto head;
		default: {
			printf("请输入正确的选项！\n");
			Sleep(300);
			goto head;
		}
		}
		break;
	}
}

/*获取技能*/
void GetSkill(Entity* player,int i) {
	InsertNode(player->OwnSkill, 1, Delete(player->NoneSkill, i)->data);
}
/*调用技能*/
Skill catchSkill(int i) {

	/*技能列表*/
	Skill skill_ERROR{ "ERROR",-114514 };
	Skill skill_Null{ "NULL",0 };
	Skill skill_One{ "撞击",10 };
	Skill skill_Two{ "大兜子",30 };
	Skill skill_Three{ "小亮の活",50 };
	/*函数返回*/
	switch (i) {
	case 0:return skill_Null;
	case 1:return skill_One;
	case 2:return skill_Two;
	case 3:return skill_Three;
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
int Length(SkillLink head) {
	int i = 1;
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
/*查找*/
int Locate(SkillLink head, Skill x) {
	int i = 0;
	while (head) {
		head = head->next;
		i++;
		if (head->data.name == x.name)
			return i;
	}
	return -1;
}