#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include<math.h> 

#define ERR_SKILL_LIST_EXCEED -1	//���ܱ�Խ��

#define skillNum 4					//ʵ�弼�ܸ���
#define nameLength 20				//���Ƴ���
#define skillLength 3				//�ܼ��ܸ���
#define M 3

/*���ܽṹ�嶨��*/
typedef struct {
	short ID;						//����ID
	char name[nameLength];			//��������
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
<<<<<<< Updated upstream
=======
/*ҩƷ�ṹ�嶨��*/
typedef struct {
	char name[nameLength];		//ҩƷ���� 
	int effect;					//ҩƷЧ����ÿ��һ���Ӷ�������ֵ 
}Food;
/*�����ṹ�嶨��*/
typedef struct {
	int ID;						//����ID
	char name[nameLength];		//��������
	int ATK;					//����������
}Weapon;
/*���׽ṹ�嶨��*/
typedef struct {
	int ID;						//����ID
	char name[nameLength];		//��������
	int DEF;					//���׷�����
}Armour;
/*װ���ṹ�嶨��*/
typedef struct {
	Weapon Weapon;				//����
	Armour Armour;				//����
}Equi;
>>>>>>> Stashed changes
/*ʵ��ṹ�嶨��*/
typedef struct {
	char name[nameLength];		//ʵ������
	int HP;						//ʵ������ֵ
	SkillList SkillList;		//ʵ���������ܱ�
	SkillLink OwnSkill;			//ʵ����ӵ�м��ܱ�
	SkillLink NoneSkill;		//ʵ��δ��ü��ܱ�
	int i;						//ʵ������ 
}Entity;
struct food //����ҩƷ�ṹ������ 
{
	char name[20]; //ҩƷ���� 
	int count;  //ҩƷ���� 
	int effect;  //ҩƷЧ����ÿ��һ���Ӷ�������ֵ 
}fd[M];

void UI_fight(Entity*);											/*ս������UI*/
int UI_fighting(Entity, Entity);								/*ս����UI*/
void UI_skill(Entity*);											/*���ܽ���UI*/
int UI_UnloadSkill(Entity*);									/*ж�¼���UI*/
int UI_LoadSkill(Entity*);										/*װ�ؼ���UI*/

void init();

void SetEntity(Entity*, int, char name[nameLength]);			/*��ʼ��ʵ��*/
Skill CatchSkill(int i);										/*���ü���*/
void GetSkill(Entity*, int);									/*��ȡ�¼���*/
void next();													/*���������һ��*/

int UnloadSkill(Entity*, int);									/*ж�¼���*/
int LoadSkill(Entity*, int);									/*װ�似��*/

int ToInt(char[]);			//�ַ�������ת��Ϊ����

/*˳��������*/
void InitList(SkillList*);							//���ձ�
int Length(SkillList);								//���
void updata(SkillList*, int, Skill);				//�޸�����
int Locate(SkillList, Skill);						//��ֵ֪���±�

/*�����������*/
SkillLink InitListNode();						//��ʼ��������
void InsertNode(SkillLink, int, Skill);			//���뵥����
int LengthNode(SkillLink);						//���
void Traversal(SkillLink);						//����
SkillLink Delete(SkillLink, int);				//ɾ��
int LocateNode(SkillLink, Skill);				//��ֵ֪�������
SkillLink GetElem(SkillLink, int);				//��֪��Ų���ֵ

int difficulty = 1;		/*�Ѷ�ϵ��*/



int main() {
	Entity player;
	char name[nameLength];
	printf("+----------------------------+\n");
	printf("|	��ӭ������Ϸ         |\n");
	printf("|****************************|\n");
	printf("+----------------------------+\n");
	printf("\n��������������:  ");
	gets_s(name);
	SetEntity(&player, 2, name);
	while (true) {
		system("CLS");
<<<<<<< Updated upstream
		puts(player.name);
		printf("�ȼ���%d\n", difficulty);
		printf("��������Ĳ�����\n");
		printf("*************************\n");
		printf("1.ս��\n");
		printf("2.����\n");
		printf("0.�˳�\n");
=======
		printf("*********************************************************\n");
		printf("*	����:%-10s	�ȼ�:%-2d		���:%-10d *\n", player.name, difficulty, player.Gold);
		printf("*                                                       *\n");
		printf("*	�����б�:                                       *\n");
		printf("*                                                       *\n");
		printf("*	1.ս��		2.����		3.ҩƷ		*\n");
		printf("*                                                       *\n");
		printf("*	4.װ��		5.�̵�		0.�˳�		*\n");
		printf("*********************************************************\n");
		printf("\n������Ĳ���\n");
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
			printf("��������ȷ��ѡ�\n");
			Sleep(1000);
		}
	}
}
/*��ʼ��ʵ��*/
/*��iΪ1ʱ��ʵ��ΪС������
  ��iΪ2ʱ��ʵ��Ϊ��Ӣ����
  ��iΪ3ʱ��ʵ��Ϊ��������*/
void SetEntity(Entity* entity, int i, char name[nameLength]) {
	strcpy_s(entity->name, name);				//����
	entity->HP = i * difficulty * 100;			//Ѫ��
	entity->i = i;								//ʵ������
	InitList(&entity->SkillList);				//��ʼ�����ܱ�
	updata(&entity->SkillList, 0, CatchSkill(3));
	updata(&entity->SkillList, 1, CatchSkill(2));
	updata(&entity->SkillList, 2, CatchSkill(1));
	updata(&entity->SkillList, 3, CatchSkill(4));
	entity->OwnSkill = InitListNode();			//��ʼ���ѻ�ȡ���ܱ�
	entity->NoneSkill = InitListNode();			//��ʼ��δ��ȡ���ܱ�
	for (int i = 0;i < skillLength;i++)
		InsertNode(entity->NoneSkill, i + 1, CatchSkill(i + 1));
}

void init()										//����ҩƷ���֣�ʹ�ô���
{
	int i;
	char name[M][20] = { "��ҩ","������","������" };		//����
	srand(time(NULL));
	for (i = 0;i < M;i++)
	{
		strcpy_s(fd[i].name, name[i]);
		fd[i].count = 1;									//����
		fd[i].effect = i + 1;								//Ч��
	}
}

/*ս������UI*/
void UI_fight(Entity* player) {
head:
	system("CLS");
<<<<<<< Updated upstream
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
	SetEntity(&mob, i, iname);					//��������ʵ�岢������������͸�ֵ���Լ�����
	for (int i = 4;i;i--) {						//����������＼�ܱ�
		srand((unsigned)time(NULL));
		int a = 1 + rand() % (skillLength - 1);
		updata(&mob.SkillList, i - 1, CatchSkill(a));
	}
	printf("�Ƿ�ʼս����\n");
	printf("Y/N\n");
=======
	Entity mob = SetMob();
	printf("...........................................\n");
	printf(".	��������һ��%d����%s��		  .\n", difficulty, mob.name);
	printf("...........................................\n\n");
	printf("!!!\n");
	printf("\n�Ƿ�ʼս����\n");
	printf("\nY/N  (����Y��ʼ��N����)\n\n");
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	difficulty += UI_fighting(*player, mob);		//��ʤ�����Ѷ�ϵ��+1����ʧ����-1��
=======
	int result = UI_fighting(*player, mob);
	system("CLS");
	switch (result) {
	case -1: {			//ս��ʧ��
		printf("\n  �i�n�i...\n");
		printf("+-----------------------+\n");
		printf("|	ս��ʧ�ܣ�	|\n");
		printf("+-----------------------+\n");
		difficulty--;
	};break;
	case 1: {			//ս��ʤ��
		printf("\n  o(^��^)o\n");
		printf("\n+++++++++++++++++++++++++\n");
		printf("|	ս��ʤ����	|\n");
		printf("+++++++++++++++++++++++++\n");
		difficulty++;
		UI_gain(player, mob);
	};break;
	case 0: {			//����
		printf("\n  <(�� �k ��)@m ���⣿\n");
		printf("\n�������ˣ�\n");
	};break;
	}
	system("PAUSE");
>>>>>>> Stashed changes
}
/*ս����UI*/
int UI_fighting(Entity player, Entity mob) {
	system("CLS");
	putchar(10);
	int i = 0;
	int choose;
	while (player.HP > 0 && mob.HP > 0) {
<<<<<<< Updated upstream
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
=======
		i++;
	head:
		UI_Jade(player, mob, i);
		printf("#|*********************************|#\n");
		printf("#|	   ��Ҫ����ʲô����?	   |#\n");
		printf("#|                                 |#\n");
		printf("#|		1.����		   |#\n");
		printf("#|                                 |#\n");
		printf("#|		2.ҩƷ		   |#\n");
		printf("#|                                 |#\n");
		printf("#|		0.����		   |#\n");
		printf("#|*********************************|#\n");
		choose = ToInt32(gets_s(chooseChar));
		if (choose == 1) {					//ѡ����
		branch1:
			UI_Jade(player, mob, i);
			UI_fightSkill(player);
			branch = 1;
		}
		else if (choose == 2) {				//ѡ��ҩƷ
		branch2:
			UI_Jade(player, mob, i);
			UI_fightFood(player);
			branch = 2;
		}
		else if (choose == 0) {
			system("CLS");
			printf("!!!\n");
			printf("ȷ��Ҫ������\n\n����0ȷ��ѡ��\n");
			chooseChar[1] = getchar();
>>>>>>> Stashed changes
			while (getchar() != '\n');
			if (choose >= 1 && choose <= skillNum) {
				break;
			}
			else
				printf("��������ȷ��ѡ�");
		}
		init();
		if (choose==4) {
			int i;
			for (i = 0;i < M;i++)
			{

				printf("%d: %s%d�� ����֮��������HP%d\n", i, fd[i].name, fd[i].count, (fd[i].effect) * 20);
			}
			printf("ѡ����Ҫ�Ե�ҩƷ���(-1ȡ��):");
			scanf_s("%d", &i);			//����ʹ���ĸ�ҩƷ
			if (i >= 0 && i < M)
			{
				if (fd[i].count > 0)	
				{
					printf("�����һ��%s,HP������%d", fd[i].name, (fd[i].effect) * 20);	
					player.HP += (fd[i].effect) * 20;			//�ָ�Ч��
					fd[i].count--;								//���ٴ���
					if (player.HP > 200)player.HP = 200;			//�ָ���
				}
				else
				{
					printf("��û�����ҩƷ!");
				}
			}
			Sleep(500);
		}
		else {
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
	}
	printf("ս��������\n");
	if (player.HP <= 0) {
		printf("��ʧ���ˣ�\n");
		printf("����������ء�\n");
		while (getchar() != '\n');
		return -1;
<<<<<<< Updated upstream
=======
	else if (mob.HP <= 0)			//ʤ������ֵ1
		return 1;
	else							//���ܷ���ֵ0
		return 0;
}
/*ս����Ϣ*/
/*����ս��˫���Լ��غ���*/
void UI_Jade(Entity player, Entity mob, int i) {
	system("CLS");
	printf("*��������������������%2d�غϡ���������������������*\n", i);
	printf("|\t\t\t\t\t\t |\n");
	printf("|\t%-10s�ȼ���%-7dHP��%-12d\t |\n", mob.name, difficulty, mob.HP);
	printf("|\t\t\t\t\t\t |\n");
	printf("|\t%-10s�ȼ���%-7dHP��%-12d\t |\n", player.name, difficulty, player.HP);
	printf("|\t\t\t\t\t\t |\n");
	printf("*������������������������������������������������*\n\n");
}
/*ս���еļ��ܽ���*/
void UI_fightSkill(Entity player) {
	printf("����Ҫʹ���ĸ����ܣ�\n");
	for (int i = 0;i < skillNum;i++)
		printf("\n    %-2d.%-10s�˺���%-10d\n", i + 1, player.SkillList.data[i].name, player.SkillList.data[i].atk);
	printf("\n    ����0�˳�\n\n");
}
/*ս���е�ҩƷ����*/
void UI_fightFood(Entity player) {
	printf("����Ҫʹ���ĸ�ҩƷ��\n");
	for (int i = 0;i < M;i++)
		printf("    %-2d.%-10s������%-10d��������%-10d\n", i + 1, player.Food[i].name, player.FoodNum[i], player.Food[i].effect);
	printf("    ����0�˳�\n\n");
}
/*������*/
/*�Թ���Ϊ�������������*/
void UI_gain(Entity* player, Entity mob) {
	srand((unsigned)time(NULL));

	int get = 1 + rand() % skillNum;			//������������������ĸ�����
	if (LocateNode(player->NoneSkill, mob.SkillList.data[get - 1]) != -1) {
		GetSkill(player, LocateNode(player->NoneSkill, mob.SkillList.data[get - 1]));
		printf("\n�����˼��ܣ�%s��\n", mob.SkillList.data[get - 1].name);
>>>>>>> Stashed changes
	}
	else {
		printf("��ʤ���ˣ�\n");
		printf("����������ء�\n");
		while (getchar() != '\n');
		return 1;
	}
<<<<<<< Updated upstream
=======
	player->Gold += mob.Gold;					//��ȡ����Ľ��
	printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$");
	printf("\n$                       $");
	printf("\n$    ������%d��ң�    $", mob.Gold);
	printf("\n$                       $");
	printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$\n");
}

/*ս������*/
/*��������ǰ���ܻ����ں�,chooseΪʹ�õļ��ܣ�����ֵΪ����˺�*/
int attack(Entity* entity1, Entity* entity2, int choose) {
	int harm;
	harm = entity1->SkillList.data[choose - 1].atk;
	entity2->HP -= harm;
	return harm;
>>>>>>> Stashed changes
}

/*���ܽ���UI*/
void UI_skill(Entity* player) {
head:
	system("CLS");
<<<<<<< Updated upstream
	printf("%s\n�ȼ���%d\n", player->name, difficulty);
	printf("��ǰ���ܣ�\n");
=======
	printf("*********************************************************\n");
	printf("*	����:%-10s	�ȼ�:%-2d		���:%-10d *\n", player->name, difficulty, player->Gold);
	printf("*-------------------------------------------------------*\n");
	printf("*��ǰ����:                                              *\n");
>>>>>>> Stashed changes
	for (int i = 0;i < skillNum;i++)
		printf("*%d.%-10s                                           *\n", i + 1, player->SkillList.data[i].name);
	printf("*-------------------------------------------------------*\n");
	printf("��ӵ�еļ���:\n");
	Traversal(player->OwnSkill);
	printf("�����������\n");
	printf("1.�鿴δӵ�м���\n");
	printf("2.ж�¼���\n");
	printf("3.װ�ؼ���\n");
	printf("0.�˳�\n");
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
			printf("��������ȷ��ѡ�\n");
			Sleep(300);
			goto head;
		}
		}
		break;
	}
}
/*ж�¼���UI*/
int UI_UnloadSkill(Entity* player) {
	char i[nameLength];
	int num = -1;
head:
	system("CLS");
	printf("��ǰ���ܣ�\n");
	for (int i = 0;i < skillNum;i++)
		printf("%d.%s\n", i + 1, player->SkillList.data[i].name);
	printf("\n��ӵ�еļ��ܣ�\n");
	Traversal(player->OwnSkill);
	printf("\n��ѡ����Ҫж�µļ���(1-4)\n����0�˳�\n");
	num = ToInt(gets_s(i));
	if (num == 0)
		return 0;
	if (num == -1) {
		printf("��������ȷ�ļ�����(1-4)!\n");
		Sleep(300);
		goto head;
	}
	int j = UnloadSkill(player, num);
	switch (j) {
	case -1:printf("��λ���޼��ܣ�ж��ʧ�ܣ�\n");break;
	case -2:printf("��������ȷ�ļ�������");break;
	default:printf("�ѽ�%dλ�ϵļ���ж�£�\n", num);break;
	}
	Sleep(300);
	goto head;
}
/*װ�ؼ���UI*/
int UI_LoadSkill(Entity* player) {
	char i[nameLength];
	int num;
head:
	system("CLS");
	printf("��ǰ���ܣ�\n");
	for (int i = 0;i < skillNum;i++)
		printf("%d.%s\n", i + 1, player->SkillList.data[i].name);
	printf("\n��ӵ�еļ��ܣ�\n");
	Traversal(player->OwnSkill);
	printf("��������Ҫװ�صļ��ܣ�\n����0�˳�\n");
	num = ToInt(gets_s(i));
	if (num == 0)
		return 0;
	if (num == -1) {
		printf("��������ȷ�ļ��ܴ���!\n");
		Sleep(300);
		goto head;
	}
	int j = LoadSkill(player, num);
	switch (j) {
	case 0:printf("�ѳɹ�װ�似�ܣ�");break;
	case -1:printf("�������������޷�װ�䣡\n");break;
	case -2:printf("��û�д˼��ܣ���������ȷ�ļ��ܣ�\n");break;
	}
	Sleep(300);
	goto head;
}

<<<<<<< Updated upstream
=======
/*ҩƷ����UI*/
void UI_Food(Entity* player) {
	system("CLS");
	printf("*********************************************************\n");
	printf("*	����:%-10s	�ȼ�:%-2d		���:%-10d *\n", player->name, difficulty, player->Gold);
	printf("*-------------------------------------------------------*\n");
	printf("��ǰҩƷ��\n");
	for (int i = 0;i < M;i++)
		printf("%d.%s\t������%d\t��������%d\n", i + 1, player->Food[i].name, player->FoodNum[i], player->Food[i].effect);
	printf("�������������\n");
	getchar();
}

/*װ������UI*/
void UI_Equi(Entity* player) {
	char chooseChar[nameLength];
	int choose;
head:
	UI_EquiInfo(*player);
	printf("\n��Ҫ��ʲô��\n");
	printf("1.  ����\n");
	printf("2.  ����\n");
	printf("0.  ����\n");
	choose = ToInt32(gets_s(chooseChar));
	switch (choose) {
	case 0:break;
	case 1: {
	Weaponhead:
		while (1) {
			UI_EquiInfo(*player);
			UI_WeaponInfo(*player);
			printf("\n��������Ҫװ����������\n����0�ɷ���\n");
			choose = ToInt32(gets_s(chooseChar));
			if (choose > 0 && choose < weaponLength + 1)break;
			else if (choose == -1) {
				printf("\n��������ȷ��ѡ�\n");
				Sleep(300);
				continue;
			}
			else goto head;
		}
		switch (LoadWeapon(player, choose)) {
		case -2: {
			printf("\n��û�и�������\n");
			Sleep(300);
			goto Weaponhead;
		}
		default: {
			printf("\n�ѳɹ�װ��%s!\n", CatchWeapon(choose).name);
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
			printf("\n��������Ҫװ���Ŀ��ף�\n����0�ɷ���\n");
			choose = ToInt32(gets_s(chooseChar));
			if (choose > 0 && choose < weaponLength + 1)break;
			else if (choose == -1) {
				printf("\n��������ȷ��ѡ�\n");
				Sleep(300);
				continue;
			}
			else goto head;
		}
		switch (LoadArmour(player, choose)) {
		case -2: {
			printf("\n��û�иÿ��ף�\n");
			Sleep(300);
			goto Weaponhead;
		}
		default: {
			printf("\n�ѳɹ�װ��%s!\n", CatchArmour(choose).name);
			Sleep(300);
			goto head;
		}
		}
	};break;

	default:printf("\n��������ȷ��ѡ�\n");goto head;
	}
}
/*װ����ϢUI*/
void UI_EquiInfo(Entity player) {
	system("CLS");
	printf("*********************************************************\n");
	printf("*	����:%-10s	�ȼ�:%-2d		���:%-10d *\n", player.name, difficulty, player.Gold);
	printf("*-------------------------------------------------------*\n");
	printf("������%-20s��������%-10d\n", player.Equi.Weapon.name, player.Equi.Weapon.ATK);
	printf("���ף�%-20s��������%-10d\n", player.Equi.Armour.name, player.Equi.Armour.DEF);
}
/*������ϢUI*/
void UI_WeaponInfo(Entity player) {
	for (int i = 0;i < weaponLength;i++)
		printf("\n%d.%-20s������%-10d��������%-10d\n", i + 1, CatchWeapon(i + 1).name, player.WeaponNum[i], CatchWeapon(i + 1).ATK);
}
/*������ϢUI*/
void UI_ArmourInfo(Entity player) {
	for (int i = 0;i < armourLength;i++)
		printf("\n%d.%-20s������%-10d��������%-10d\n", i + 1, CatchArmour(i + 1).name, player.ArmourNum[i], CatchArmour(i + 1).DEF);
}

/*�̵����UI*/
void UI_Shop(Entity* player) {
	UI_ShopInfo(*player);
	getchar();
}
/*�̵���ϢUI*/
void UI_ShopInfo(Entity player) {
	system("CLS");
	printf("\n��%d\n", player.Gold);
	printf("#|*********************************|#\n");
	printf("#|������սʿ�˺��� �һ𵶵���������|#\n");
	printf("#|*********************************|#\n");
	printf("#|��������ʦ����ǿ ��˪��ȫ��������|#\n");
	printf("#|*********************************|#\n");
	printf("#|��������ʿʮ�幷 ȫ�������ߣ�����|#\n");
	printf("#|*********************************|#\n");
	printf("#|������ɢ�˴��� �����ˬ��������|#\n");
	printf("#|*********************************|#\n");
	printf("#|�������ֽ��뵽�� װ���ܻ��գ�����|#\n");
	printf("#|*********************************|#\n");
	printf("#|�������һ��ܴ� �����洫�棡����|#\n");
	printf("#|*********************************|#\n");
	UI_ShopMenu();
}
/*�̵��б�UI*/
void UI_ShopMenu() {
	printf("\n����Ҫ����ʲô��\n");
	printf("\n1.����\n");
	printf("\n2.װ��\n");
	printf("\n3.ҩƷ\n");
	printf("\n0.����\n");
}

/*װ������*/
/*���������򷵻�-2*/
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
/*װ������*/
/*���������򷵻�-2*/
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
/*��ȡ����*/
///i��ֵΪplayerδ��ü��ܱ��еĵ�iλ
///����playerδ��ü��ܱ��еĵ�iλɾ��������player�ѻ�ü��ܱ��еĵ�һλ
void GetSkill(Entity* player, int i) {
	if (LengthNode(player->NoneSkill) >= 1) {
		InsertNode(player->OwnSkill, 1, Delete(player->NoneSkill, i)->data);
	}

}
/*ж�¼���*/
int UnloadSkill(Entity* player, int i) {
	if (i<1 || i>skillNum)
		return -2;												//ж��λ��Խ��
	if (player->SkillList.data[i - 1].ID == CatchSkill(0).ID)
		return -1;												//�˼���Ϊ�գ��޷�ж��
	InsertNode(player->OwnSkill, 1, player->SkillList.data[i - 1]);
	updata(&player->SkillList, i - 1, CatchSkill(0));
	return 0;
}
/*װ�似��*/
int LoadSkill(Entity* player, int i) {
	if (i > LengthNode(player->OwnSkill))
		return -2;									//��û�д˼���
	int j = Locate(player->SkillList, CatchSkill(0));
	if (j == -1)
		return -1;									//����������
	else
		updata(&player->SkillList, j, Delete(player->OwnSkill, i)->data);
}

<<<<<<< Updated upstream
=======
/*������ɹ���*/
Entity SetMob() {
	srand((unsigned)time(NULL));				//���������
	int i = rand() % 3 + 1;						//������ɹ�������
	char iname[nameLength];						//��������
	switch (i) {
	case 1:strcpy_s(iname, "С��");break;
	case 2:strcpy_s(iname, "��Ӣ");break;
	case 3:strcpy_s(iname, "����");break;
	}
	Entity mob;
	SetEntity(&mob, i, iname);					//��������ʵ�岢������������͸�ֵ���Լ�����
	for (int i = 0;i < skillNum;i++) {			//����������＼�ܱ�
		int a = 1 + rand() % (LengthNode(mob.NoneSkill));
		GetSkill(&mob, a);
		LoadSkill(&mob, 1);
	}
	for (int i = 0;i < M; i++) {				//�����������ҩ���
		int a = rand() % ((difficulty / 3) + 1);
		mob.FoodNum[M] = a;
	}
	mob.DEF = difficulty * 5 + rand() % difficulty * 10;					//������ɹ��������
	mob.ATK = difficulty * 5 + rand() % difficulty * 10;					//������ɹ��﹥����
	mob.Gold = difficulty * 5 + rand() % difficulty * 10;					//������ɹ���Я�����
	return mob;
}

>>>>>>> Stashed changes
/*���ü���*/
Skill CatchSkill(int i) {
	/*�����б�*/
	Skill skill_ERROR{ -1,"ERROR",-114514 };
	Skill skill_Null{ 0, "NULL",0 };
	Skill skill_One{ 1,"ײ��",10 };
	Skill skill_Two{ 2,"����",30 };
	Skill skill_Three{ 3, "С���λ�",50 };
	Skill skill_Four{ 4, "ҩƷ",0 };
	/*��������*/
	switch (i) {
	case 0:return skill_Null;
	case 1:return skill_One;
	case 2:return skill_Two;
	case 3:return skill_Three;
	case 4:return skill_Four;
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
/*��ֵ֪�����±�*/
int Locate(SkillList head, Skill x) {
	int i = 0;
	for (i;i < skillNum;i++) {
		if (head.data[i].ID == x.ID)
			return i;
	}
	return -1;
}

/*�ַ���ת��Ϊ����*/
int ToInt(char ch[]) {
	for (int i = 0;ch[i] != '\0';i++)					//���ַ����к��з����֣��򷵻�ֵ-1
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
int LengthNode(SkillLink head) {
	int i = 0;
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
/*��ֵ֪�������*/
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
/*��֪��Ų���ֵ*/
SkillLink GetElem(SkillLink head, int i) {
	int j = 0;
	while (head && j < i) {
		head = head->next;
		j++;
	}
	return head;
}