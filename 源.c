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
	char name[nameLength];		//��������
	int atk;						//�����˺�
}Skill;
/*���ܱ�˳�����*/
typedef struct {
	Skill data[skillNum];			//���ܱ���������������
	int length;					//���ܱ���
}SkillList;
/*ʵ��ṹ�嶨��*/
typedef struct {
	char name[nameLength];		//ʵ������
	int HP;						//ʵ������ֵ
	SkillList SkillList;			//ʵ���������ܱ�
	int i;						//ʵ������ 
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
static Skill skill_ERROR={ "ERROR",-114514 };
static Skill skill_Null={ "NULL",0 };
static Skill skill_One={ "ײ��",10 };
static Skill skill_Two={ "����",30 };
static Skill skill_Three={ "С���λ�",50 };

int main() {
	Entity player;
	char name[nameLength];
	printf("��ӭ������Ϸ\n");
	printf("***********\n");
	printf("��������������\n");
	putchar('\n');
	gets(name);
	setEntity(&player, 2, name);
	while (1) {
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
	strcpy_s(entity->name,sizeof(entity->name), name);
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
	case 1:strcpy_s(iname, sizeof(iname), "С��");break;
	case 2:strcpy_s(iname, sizeof(iname), "��Ӣ");break;
	case 3:strcpy_s(iname, sizeof(iname), "����");break;
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
	char ch;
	while (ch = getchar()) {					//�����ѡ���Ƿ�ս�������������������ת���Ӻ�����ͷ
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
	difficulty += UI_fighting(player, mob);		//��ʤ�����Ѷ�ϵ��+1����ʧ����-1��
}

/*ս����UI*/
int UI_fighting(Entity player, Entity mob) {
	system("CLS");
	putchar(10);
	int i = 0;
	while (player.HP > 0 && mob.HP > 0) {
		i++;												//�غϼ�����
		printf("***********��%d�غ�************\n", i);
		printf("%s������ֵʣ��%d\n", player.name, player.HP);
		printf("%s������ֵʣ��%d\n", mob.name, mob.HP);
		putchar(10);
		printf("��Ҫ��ʲô��\n");
		for (int i = 0;i < skillNum;i++) {
			printf("%d.%s", i + 1, player.SkillList.data[i].name);
		}
		int choose;
		scanf_s("%d", &choose);								//����̨��������ͷŵļ���
		if (i >= 1 && i < skillNum) {
			mob.HP -= player.SkillList.data[i - 1].atk;
			printf("%sʹ����%s,��%s�����%d���˺�!\n%sʣ��Ѫ��%d", player.name, player.SkillList.data[i - 1].name, mob.name, player.SkillList.data[i - 1].atk, mob.name, mob.HP);
		}
		if (mob.HP <= 0)break;
		choose = rand() % skillNum;							//��������������ͷŵļ���
		player.HP -= mob.SkillList.data[choose].atk;
		printf("%sʹ����%s,��%s�����%d���˺�!\n%sʣ��Ѫ��%d", mob.name, mob.SkillList.data[choose].name, player.name, mob.SkillList.data[choose].atk, player.name, player.HP);
		if (player.HP <= 0)break;
	}
	printf("ս��������\n");
	if (player.HP <= 0) {
		printf("��ʧ���ˣ�\n");
		printf("����������ء�\n");
		while (getchar() != '\n');
		return -1;
	}
	else {
		printf("��ʤ���ˣ�\n");
		printf("����������ء�\n");
		while (getchar() != '\n');
		return 1;
	}
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