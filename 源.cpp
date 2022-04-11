#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define skillNum 4					//技能个数
#define nameLength 20				//名称长度
/*技能结构体定义*/
typedef struct {
	char name[nameLength] = {};		//技能名称
	int atk=0;						//技能伤害
}Skill;						
/*技能表顺序表定义*/
typedef struct{
	Skill data[skillNum];			//技能表中所含技能数组
	int length=0;					//技能表长度
}SkillList;					
/*实体结构体定义*/
typedef struct {								
	char name[nameLength] = {};		//实体名称
	int HP=0;						//实体生命值
	SkillList SkillList;			//实体所带技能表
	int i=0;						//实体类型 
}Entity;			

void UI_fight(Entity, Entity);					/*战斗界面UI*/
void UI_skill();								/*技能列表UI*/
void setEntityName(Entity* entity);				/*设置实体名称*/
void setEntity(Entity* entity, int i);			/*初始化实体*/
void skillMenu();								/*初始化技能菜单*/

/*顺序表操作集*/
/*建空表*/
void InitList(SkillList*);
/*求表长*/
int Length(SkillList);

int difficulty = 1;		/*难度因子*/
int main() {
	Entity player;
	printf("欢迎进入游戏\n");
	printf("***********\n");
	printf("请输入您的名称\n");
	putchar('\n');
	setEntityName(&player);
	while (true) {
		system("CLS");
		puts(player.name);
		printf("请输入你的操作：\n");
		printf("*************************\n");
		printf("1.战斗\n");
		printf("2.技能\n");
		printf("3.退出\n");
		char choose;
		choose = getchar();
		while (getchar() != '\n');
		if (choose == '1')
			break;
		else if (choose == '2')
			break;
		else if (choose == '3')
			return 0;
		else {
			printf("请输入正确的选项！\n");
			Sleep(1000);
		}

	}

}
/*初始化实体*/
/*当i为1时，实体为小怪类型
  当i为2时，实体为用户类型
  当i为3时，实体为精英类型*/
void setEntity(Entity* entity, int i) {
	entity->HP = i * difficulty * 100;
	entity->i = i;
	InitList(&entity->SkillList);
}
/*设置实体名称*/
void setEntityName(Entity* entity) {
	gets_s(entity->name);
}
/*技能菜单*/
void skillMenu() {
	static Skill a{ "撞击",10 };
	static Skill b{ "大兜子",30 };
	static Skill c{ "小亮の活",50 };
}

/*战斗UI*/
void UI_fight() {
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