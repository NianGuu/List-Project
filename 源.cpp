#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define skillNum 4					//���ܸ���
#define nameLength 20				//���Ƴ���
/*���ܽṹ�嶨��*/
typedef struct {
	char name[nameLength] = {};		//��������
	int atk=0;						//�����˺�
}Skill;						
/*���ܱ�˳�����*/
typedef struct{
	Skill data[skillNum];			//���ܱ���������������
	int length=0;					//���ܱ���
}SkillList;					
/*ʵ��ṹ�嶨��*/
typedef struct {								
	char name[nameLength] = {};		//ʵ������
	int HP=0;						//ʵ������ֵ
	SkillList SkillList;			//ʵ���������ܱ�
	int i=0;						//ʵ������ 
}Entity;			

void UI_fight(Entity, Entity);					/*ս������UI*/
void UI_skill();								/*�����б�UI*/
void setEntityName(Entity* entity);				/*����ʵ������*/
void setEntity(Entity* entity, int i);			/*��ʼ��ʵ��*/
void skillMenu();								/*��ʼ�����ܲ˵�*/

/*˳��������*/
/*���ձ�*/
void InitList(SkillList*);
/*���*/
int Length(SkillList);

int difficulty = 1;		/*�Ѷ�����*/
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
}
/*����ʵ������*/
void setEntityName(Entity* entity) {
	gets_s(entity->name);
}
/*���ܲ˵�*/
void skillMenu() {
	static Skill a{ "ײ��",10 };
	static Skill b{ "����",30 };
	static Skill c{ "С���λ�",50 };
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