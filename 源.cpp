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
#define M 3							//��ҩƷ����

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
/*ҩƷ�ṹ�嶨��*/
typedef struct {
	char name[nameLength]; //ҩƷ���� 
	int effect;  //ҩƷЧ����ÿ��һ���Ӷ�������ֵ 
}Food;
/*ʵ��ṹ�嶨��*/
typedef struct {
	char name[nameLength];		//ʵ������
	int HP;						//ʵ������ֵ
	SkillList SkillList;		//ʵ���������ܱ�
	SkillLink OwnSkill;			//ʵ����ӵ�м��ܱ�
	SkillLink NoneSkill;		//ʵ��δ��ü��ܱ�
	Food Food[M];				//ʵ����е�ҩƷ
	int FoodNum[M];				//ʵ����е�ҩƷ����
	int i;						//ʵ������ 
}Entity;

void UI_fight(Entity*);											/*ս������UI*/
int UI_fighting(Entity, Entity);								/*ս����UI*/

void UI_skill(Entity*);											/*���ܽ���UI*/
int UI_UnloadSkill(Entity*);									/*ж�¼���UI*/
int UI_LoadSkill(Entity*);										/*װ�ؼ���UI*/

void UI_Food(Entity*);											/*ҩƷ����UI*/

Food CatchFood(int i);											/*����ҩƷ*/

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
	printf("��ӭ������Ϸ\n");
	printf("***********\n");
	printf("��������������\n");
	putchar('\n');
	gets_s(name);
	SetEntity(&player, 2, name);
	while (true) {
		system("CLS");
		puts(player.name);
		printf("�ȼ���%d\n", difficulty);
		printf("��������Ĳ�����\n");
		printf("*************************\n");
		printf("1.ս��\n");
		printf("2.����\n");
		printf("3.ҩƷ\n");
		printf("0.�˳�\n");
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
	updata(&entity->SkillList, 3, CatchSkill(0));
	entity->OwnSkill = InitListNode();			//��ʼ���ѻ�ȡ���ܱ�
	entity->NoneSkill = InitListNode();			//��ʼ��δ��ȡ���ܱ�
	for (int i = 0;i < skillLength;i++)
		InsertNode(entity->NoneSkill, i + 1, CatchSkill(i + 1));
	for (int i = 0;i < M;i++) {					//��ʼ�����е�ҩƷ
		entity->Food[i] = CatchFood(i + 1);
		entity->FoodNum[i] = 1;
	}
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
	SetEntity(&mob, i, iname);					//��������ʵ�岢������������͸�ֵ���Լ�����
	for (int i = 4;i;i--) {						//����������＼�ܱ�
		srand((unsigned)time(NULL));
		int a = 1 + rand() % (skillLength - 1);
		updata(&mob.SkillList, i - 1, CatchSkill(a));
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
		printf("%d.ҩƷ\n", skillNum + 1);
		while (true) {
			scanf_s("%d", &choose);						//����̨��������ͷŵļ���
			while (getchar() != '\n');
			if (choose >= 1 && choose <= skillNum+1) {
				break;
			}
			else
				printf("��������ȷ��ѡ�");
		}

		if (choose == (skillNum+1)) {
			char ch[nameLength];
			int j;
			for (j = 0;j < M;j++)
			{

				printf("%d: %s%d�� ����֮��������HP%d\n", j+1, player.Food[j].name, player.FoodNum[j], player.Food[j].effect);
			}
			printf("ѡ����Ҫ�Ե�ҩƷ���\n����0ȡ��:");
			while (j = ToInt(gets_s(ch))) {
				if (j != -1)
					break;
				printf("��������ȷ��ѡ�\n");
			}
			if (j >= 1 && j <= M)
			{
				if (player.FoodNum[j-1]> 0)
				{
					printf("�����һ��%s,HP������%d", player.Food[j-1].name, player.Food[j-1].effect);
					player.HP += player.Food[j-1].effect;			//�ָ�Ч��
					player.FoodNum[j-1]--;								//���ٴ���
					if (player.HP > 200)player.HP = 200;			//�ָ���
				}
				else
				{
					printf("��û�����ҩƷ!");
				}
			}
			else if(j==0) {
				i--;
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

/*ҩƷ����UI*/
void UI_Food(Entity* player) {
	system("CLS");
	printf("%s\n�ȼ���%d\n", player->name, difficulty);
	printf("��ǰҩƷ��\n");
	for (int i = 0;i < M;i++) {
		printf("%d.%s\t������%d\t��������%d\n", i + 1, player->Food[i].name, player->FoodNum[i], player->Food[i].effect);
	}
	getchar();
}

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

/*���ü���*/
Skill CatchSkill(int i) {
	/*�����б�*/
	Skill skill_ERROR{ -1,"ERROR",-114514 };
	Skill skill_Null{ 0, "NULL",0 };
	Skill skill_One{ 1,"ײ��",10 };
	Skill skill_Two{ 2,"����",30 };
	Skill skill_Three{ 3, "С���λ�",50 };
	/*��������*/
	switch (i) {
	case 0:return skill_Null;
	case 1:return skill_One;
	case 2:return skill_Two;
	case 3:return skill_Three;
	default:return skill_ERROR;
	}
}
/*����ҩƷ*/
Food CatchFood(int i) {
	/*ҩƷ�б�*/
	Food food_ERROR{ "ERROR",-114514 };
	Food food_One{ "��ҩ",20 };
	Food food_Two{ "������",40 };
	Food food_Three{ "������",60 };
	/*ҩƷ����*/
	switch (i) {
	case 1:return food_One;
	case 2:return food_Two;
	case 3:return food_Three;
	default:return food_ERROR;
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