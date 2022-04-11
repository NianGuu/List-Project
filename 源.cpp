#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

#define ERR_SKILL_LIST_EXCEED -1	//���ܱ�Խ��

#define skillNum 4					//ʵ�弼�ܸ���
#define nameLength 20				//���Ƴ���
#define skillLength 3				//�ܼ��ܸ���

/*���ܽṹ�嶨��*/
typedef struct {
	char name[nameLength] = {};		//��������
	int atk = 0;						//�����˺�
}Skill;
/*���ܱ�˳�����*/
typedef struct {
	Skill data[skillNum];			//���ܱ���������������
	int length = 0;					//���ܱ���
}SkillList;
/*ʵ��ṹ�嶨��*/
typedef struct {
	char name[nameLength] = {};		//ʵ������
	int HP = 0;						//ʵ������ֵ
	SkillList SkillList;			//ʵ���������ܱ�
	int i = 0;						//ʵ������ 
}Entity;

void UI_fight(Entity);											/*ս������UI*/
int UI_fighting(Entity, Entity);								/*ս����UI*/
void setEntity(Entity*, int, char name[nameLength]);			/*��ʼ��ʵ��*/
Skill catchSkill(int i);										/*���ü���*/

/*˳��������*/
void InitList(SkillList*);							//���ձ�
int Length(SkillList);								//���
void updata(SkillList*, int, Skill);				//�޸�����

int difficulty = 1;		/*�Ѷ�ϵ��*/

/*�����б�*/
static Skill skill_ERROR{ "ERROR",-114514 };
static Skill skill_Null{ "NULL",0 };
static Skill skill_One{ "ײ��",10 };
static Skill skill_Two{ "����",30 };
static Skill skill_Three{ "С���λ�",50 };

int main() {
	Entity player;
	char name[nameLength];
	printf("��ӭ������Ϸ\n");
	printf("***********\n");
	printf("��������������\n");
	putchar('\n');
	gets_s(name);
	setEntity(&player, 2, name);
	while (true) {
		system("CLS");
		puts(player.name);
		printf("��������Ĳ�����\n");
		printf("*************************\n");
		printf("1.ս��\n");
		printf("2.����\n");
		printf("3.�˳�\n");
		char choose;
		choose = getchar();
		while (getchar() != '\n');
		if (choose == '1')
			UI_fight(player);
		else if (choose == '2')
			break;
		else if (choose == '3')
			return 0;
		else {
			printf("��������ȷ��ѡ�\n");
			Sleep(1000);
		}
	}
}
/*��ʼ��ʵ��*/
/*��iΪ1ʱ��ʵ��ΪС������
  ��iΪ2ʱ��ʵ��Ϊ��Ӣ����
  ��iΪ3ʱ��ʵ��Ϊ��������*/
void setEntity(Entity* entity, int i, char name[nameLength]) {
	strcpy_s(entity->name, name);
	int hp = i * difficulty * 100;
	entity->HP = hp;
	entity->i = i;
	InitList(&entity->SkillList);
	updata(&entity->SkillList, 0, skill_Null);
	updata(&entity->SkillList, 1, skill_Null);
	updata(&entity->SkillList, 2, skill_Null);
	updata(&entity->SkillList, 3, skill_Null);
}

/*ս������UI*/
void UI_fight(Entity player) {
	head:
	system("CLS");
	int i = rand() % 3 + 1;						//������ɹ�������
	char iname[nameLength];
	switch (i) {
	case 1:strcpy_s(iname, "С��");break;
	case 2:strcpy_s(iname, "��Ӣ");break;
	case 3:strcpy_s(iname, "����");break;
	}
	printf("��������һ��%s��\n", iname);
	printf("*****************\n");
	Entity mob;
	setEntity(&mob, i, iname);					//��������ʵ�岢������������͸�ֵ���Լ�����
	for (int i = 4;i;i--) {						//����������＼�ܱ�
		int a = 1 + rand() % skillLength;
		updata(&mob.SkillList, i, catchSkill(a));
	}
	printf("�Ƿ�ʼս����\n");
	printf("Y/N\n");
	while (char ch = getchar()) {					//�����ѡ���Ƿ�ս�������������������ת���Ӻ�����ͷ
		while (getchar() != '\n');					
		if (ch == 'Y' || ch == 'y')
			break;
		else if (ch == 'N' || ch == 'n')
			goto head;
		else {
			printf("��������ȷ��ѡ�\n");
			continue;
		}
		break;
	}
	UI_fighting(player, mob);
}

/*ս����UI*/
int UI_fighting(Entity player,Entity mob) {
	system("CLS");
	putchar(10);
	int i = 0;
	while (player.HP > 0 && mob.HP > 0&&i<5) {
		i++;
		printf("***********��%d�غ�************\n", i);
		printf("%s������ֵʣ��%d\n", player.name, player.HP);
		printf("%s������ֵʣ��%d\n", mob.name, mob.HP);

	}
	return 0;
}

/*���ü���*/
Skill catchSkill(int i) {
	switch (i) {
	case 0:return skill_Null;
	case 1:return skill_One;
	case 2:return skill_Two;
	case 3:return skill_Three;
	default:return skill_ERROR;
	}
}

/*˳��������*/
/*���ձ�*/
void InitList(SkillList* list) {
	list->length = 0;
}
/*���*/
int Length(SkillList list) {
	return list.length;
}
/*�޸�����*/
void updata(SkillList* list, int i, Skill x) {
	i--;
	list->data[i] = x;
}