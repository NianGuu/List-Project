#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>

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
	int length;						//���ܱ���
}SkillList;
/*δ��ȡ���ܱ��㶨��*/
typedef struct node {
	Skill data;
	struct node* next;
}SkillNode, * SkillLink;
/*ʵ��ṹ�嶨��*/
typedef struct {
	char name[nameLength];		//ʵ������
	int HP;						//ʵ������ֵ
	SkillList SkillList;		//ʵ���������ܱ�
	SkillLink OwnSkill;			//ʵ����ӵ�м��ܱ�
	SkillLink NoneSkill;		//ʵ��δ��ü��ܱ�
	int i;						//ʵ������ 
}Entity;

void UI_fight(Entity*);											/*ս������UI*/
int UI_fighting(Entity, Entity);								/*ս����UI*/
void UI_skill(Entity*);											/*���ܽ���UI*/
void setEntity(Entity*, int, char name[nameLength]);			/*��ʼ��ʵ��*/
Skill catchSkill(int i);										/*���ü���*/
void GetSkill(Entity*,int);										/*��ȡ�¼���*/
void next();													/*���������һ��*/

/*˳��������*/
void InitList(SkillList*);							//���ձ�
int Length(SkillList);								//���
void updata(SkillList*, int, Skill);				//�޸�����

/*�����������*/
SkillLink InitListNode();						//��ʼ��������
void InsertNode(SkillLink, int, Skill);			//���뵥����
int Length(SkillLink);							//���
void Traversal(SkillLink);						//����
SkillLink Delete(SkillLink, int);				//ɾ��
int Locate(SkillLink, Skill);					//��ֵ֪�������

int difficulty = 1;		/*�Ѷ�ϵ��*/



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
		printf("�ȼ���%d\n", difficulty);
		printf("��������Ĳ�����\n");
		printf("*************************\n");
		printf("1.ս��\n");
		printf("2.����\n");
		printf("0.�˳�\n");
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
	strcpy_s(entity->name, name);				//����
	entity->HP = i * difficulty * 100;			//Ѫ��
	entity->i = i;								//ʵ������
	InitList(&entity->SkillList);				//��ʼ�����ܱ�
	updata(&entity->SkillList, 0, catchSkill(0));
	updata(&entity->SkillList, 1, catchSkill(0));
	updata(&entity->SkillList, 2, catchSkill(0));
	updata(&entity->SkillList, 3, catchSkill(0));
	entity->OwnSkill = InitListNode();			//��ʼ���ѻ�ȡ���ܱ�
	entity->NoneSkill = InitListNode();			//��ʼ��δ��ȡ���ܱ�
	for (int i = 0;i < skillLength;i++)
		InsertNode(entity->NoneSkill, i+1, catchSkill(i + 1));
}

/*ս������UI*/
void UI_fight(Entity* player) {
head:
	system("CLS");
	srand((unsigned)time(NULL));
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
		srand((unsigned)time(NULL));
		int a = 1 + rand() % (skillLength - 1);
		updata(&mob.SkillList, i - 1, catchSkill(a));
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
	difficulty += UI_fighting(*player, mob);		//��ʤ�����Ѷ�ϵ��+1����ʧ����-1��
}
/*ս����UI*/
int UI_fighting(Entity player, Entity mob) {
	system("CLS");
	putchar(10);
	int i = 0;
	int choose;
	while (player.HP > 0 && mob.HP > 0) {
		i++;//�غϼ�����
		system("CLS");
		printf("***********��%d�غ�************\n", i);
		//Sleep(500);
		printf("%s������ֵʣ��%d\n", player.name, player.HP);
		//Sleep(500);
		printf("%s������ֵʣ��%d\n", mob.name, mob.HP);
		//Sleep(500);
		putchar(10);
		printf("��Ҫ��ʲô��\n");
		for (int i = 0;i < skillNum;i++) {
			printf("%d.%s\n", i + 1, player.SkillList.data[i].name);
		}
		while (true) {
			scanf_s("%d", &choose);						//����̨��������ͷŵļ���
			while (getchar() != '\n');
			if (choose >= 1 && choose <= skillNum) {
				break;
			}
			else
				printf("��������ȷ��ѡ�");
		}
		mob.HP -= player.SkillList.data[choose - 1].atk;
		printf("%sʹ����%s,��%s�����%d���˺�!\n%sʣ��Ѫ��%d\n", player.name, player.SkillList.data[choose - 1].name, mob.name, player.SkillList.data[choose - 1].atk, mob.name, mob.HP);
		Sleep(500);
		if (mob.HP <= 0)break;
		srand((unsigned)time(NULL));
		choose = rand() % skillNum;							//��������������ͷŵļ���
		printf("%d", choose);
		player.HP -= mob.SkillList.data[choose].atk;
		printf("%sʹ����%s,��%s�����%d���˺�!\n%sʣ��Ѫ��%d\n", mob.name, mob.SkillList.data[choose].name, player.name, mob.SkillList.data[choose].atk, player.name, player.HP);
		Sleep(500);
		if (player.HP <= 0)break;
		Sleep(500);
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

/*���ܽ���UI*/
void UI_skill(Entity* player) {
head:
	system("CLS");
	printf("%s\n�ȼ���%d\n", player->name, difficulty);
	printf("��ǰ���ܣ�\n");
	for (int i = 0;i < skillNum;i++)
		printf("%d.%s\n", i + 1, player->SkillList.data[i].name);
	printf("\n��ӵ�еļ��ܣ�\n");
	Traversal(player->OwnSkill);
	printf("\n�����������\n");
	printf("0.�˳�\n");
	printf("1.�鿴δӵ�м���\n");
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
			printf("��������ȷ��ѡ�\n");
			Sleep(300);
			goto head;
		}
		}
		break;
	}
}

/*��ȡ����*/
void GetSkill(Entity* player,int i) {
	InsertNode(player->OwnSkill, 1, Delete(player->NoneSkill, i)->data);
}
/*���ü���*/
Skill catchSkill(int i) {

	/*�����б�*/
	Skill skill_ERROR{ "ERROR",-114514 };
	Skill skill_Null{ "NULL",0 };
	Skill skill_One{ "ײ��",10 };
	Skill skill_Two{ "����",30 };
	Skill skill_Three{ "С���λ�",50 };
	/*��������*/
	switch (i) {
	case 0:return skill_Null;
	case 1:return skill_One;
	case 2:return skill_Two;
	case 3:return skill_Three;
	default:return skill_ERROR;
	}
}

/*���������һ��*/
void next() {
	printf("�������������һ��\n");
	while (getchar() != '\n');
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
	list->data[i] = x;
}

/*�����������*/
/*���ձ�*/
SkillLink InitListNode() {
	SkillLink head = (SkillLink)malloc(sizeof(SkillNode));
	head->next = NULL;
	return head;
}
/*����*/
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
/*���*/
int Length(SkillLink head) {
	int i = 1;
	while (head = head->next)
		i++;
	return i;
}
/*����*/
void Traversal(SkillLink head) {
	int i = 1;
	while (head = head->next) {
		printf("%d.%-6s\t�˺���%d\n", i, head->data.name, head->data.atk);
		i++;
	}
	putchar(10);
}
/*ɾ��*/
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
/*����*/
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