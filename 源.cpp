#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#define ERR_SKILL_LIST_EXCEED -1	//���ܱ�Խ��

#define skillNum 4					//���ܸ���
#define nameLength 20				//���Ƴ���

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

void UI_fight(Entity, Entity);					/*ս������UI*/
void setEntityName(Entity* entity);				/*����ʵ������*/
void setEntity(Entity* entity, int i);			/*��ʼ��ʵ��*/

/*˳��������*/
void InitList(SkillList*);						//���ձ�
int Length(SkillList);							//���
void Insert(SkillList*, int, Skill);				//��������

int difficulty = 1;		/*�Ѷ�����*/

/*�����б�*/
static Skill skillNull{ "NULL",0 };
static Skill a{ "ײ��",10 };
static Skill b{ "����",30 };
static Skill c{ "С���λ�",50 };

int main() {
	Entity player;
	printf("��ӭ������Ϸ\n");
	printf("***********\n");
	printf("��������������\n");
	putchar('\n');
	setEntityName(&player);
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
			break;
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
  ��iΪ2ʱ��ʵ��Ϊ�û�����
  ��iΪ3ʱ��ʵ��Ϊ��Ӣ����*/
void setEntity(Entity* entity, int i) {
	entity->HP = i * difficulty * 100;
	entity->i = i;
	InitList(&entity->SkillList);
	Insert(&entity->SkillList, 0, skillNull);
}
/*����ʵ������*/
void setEntityName(Entity* entity) {
	gets_s(entity->name);
}

/*ս��UI*/
void UI_fight() {
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
/*��������*/
void Insert(SkillList* list, int i, Skill x) {
	int j = Length(*list);
	for (j;j > i - 1;j--)
		list->data[j + 1] = list->data[j];
	list->data[i] = x;
}