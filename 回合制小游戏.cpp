#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
/*by yuan_tu*/


//_CRT_SECURE_NO_WARNINGS

//属性结构
struct attribute {		

	int hp;		//血量
	int hit;	//攻击力
	int defense;	//防御力
	int run;		//闪避能力

};

struct attribute player;	//玩家属性
struct attribute computer;	//电脑属性






//菜单界面
int menu() {		
	int a;
	printf(
		"****************\n"
		"**1.开始游戏****\n"
		"**2.退出********\n"
		"****************\n"
							);

	scanf("%d",&a);

	return a;
}

//玩家的属性
int PlayerAttribute(int a) {

	srand((unsigned int)time(NULL));   //用时间作种子

		//玩家随机属性
	if (a == 1) {
		player.hp = (rand() % 51) + 50;		//玩家生命 最少50		最大100
		player.hit = (rand() % 31) + 20;		//玩家攻击力	最少20	最大50
		player.defense = (rand() % 31) + 10;	//玩家防御力 最少10	最大40
		player.run = (rand() % 41);				//玩家治疗成功值 最少0	最大40
	}
	else if (a==2) {
		printf("请输入血量：");
		scanf("%d", &player.hp);

		printf("请输入攻击力：");
		scanf("%d", &player.hit);

		printf("请输入防御力：");
		scanf("%d", &player.defense);

		printf("请输入治疗成功值：");
		scanf("%d", &player.run);
	}

	else {
		printf("输入错误\n");
		return 1;
	}
	return 0;
}


//电脑的属性
void ComputerAttribute() {

	srand((unsigned int)time(NULL));   //用时间作种子

		//电脑随机属性
	
	computer.hp = (rand() % 51) + 50;		//电脑生命 最少50		最大100
	computer.hit = (rand() % 31) + 20;		//电脑攻击力	最少20	最大50
	computer.defense = (rand() % 31) + 10;	//电脑防御力 最少10	最大40
	computer.run = (rand() % 41);				//电脑闪避值 最少0	最大40

	printf("电脑的血量是：%d\n电脑的攻击力是：%d\n电脑的防御力是：%d\n电脑的闪避值是：%d\n", computer.hp, computer.hit, computer.defense, computer.run);

}


	//显示玩家和电脑的属性
void DisplayAttribute() {
	int a,b;
	

	while (1) {				//显示玩家的属性

		printf("选择你的属性\n1.随机生成   2.自行输入");
		scanf("%d", &a);
		b = PlayerAttribute(a);

		putchar('\n');

		if (b == 0) {
			printf("你的血量是：%d\n你的攻击力是：%d\n你的防御力是：%d\n你的治疗成功值是：%d\n", player.hp, player.hit, player.defense, player.run);
			break;
		}
		else {
			printf("请重新输入\n");
		}
	}
	putchar('\n');
	Sleep(1000);							//延迟电脑属性生成时间防止与玩家一样
	ComputerAttribute();	//显示电脑属性

}


//玩家操作
int PlayerRound(int a) {

	srand((unsigned int)time(NULL));   //用时间作种子

	int b,r;		//b为攻击成功概率 r为治疗成功概率
	b = rand() % 51;				//设置一个值如果属性大于值则算成功否则失败
	r = rand() % 24;

	if (a==1) {		//攻击
		if (player.hit>=b) {	//攻击成功
			printf("攻击命中");
			computer.hp = computer.hp - (player.hit - computer.defense / 2);		//计算伤害量
			printf("电脑玩家剩余血量：%d\n\n",computer.hp);
			if (computer.hp<=0) {						//对方HP清零
				printf("电脑玩家已被打败\n");
				return 1;
			}
			else {										//对方未HP清零
				return 0;
			}
		}
		else if (player.hit<b) {				//未击中
			printf("未击中\n\n");
			return 0;
		}
	}
	else if (a==2) {		//治疗
		if (player.run>=r) {		//治疗成功
			printf("治疗成功\n");
			player.hp = player.hp + 20;			//成功奖励
			printf("获得加成Hp加20当前血量:%d\n\n", player.hp);
			
		}
		else if (player.run<r) {	//治疗失败
			printf("治疗失败\n");
			player.hp = player.hp - 10;			//失败惩罚
			printf("受到伤害Hp-10当前血量：%d\n\n", player.hp);
		}
	}
	return 0;
}

//电脑操作
int ComputerRound() {

	srand((unsigned int)time(NULL));   //用时间作种子

	int a,b, r;		//b为攻击成功概率 r为治疗成功概率

	a = (rand() % 2) + 1;			//电脑的选项
	b = rand() % 51;				//设置一个值如果属性大于值则算成功否则失败
	r = rand() % 24;


	if (a == 1) {		//攻击
		if (computer.hit >= b) {	//攻击成功
			printf("攻击命中");
			player.hp = player.hp - (computer.hit - player.defense / 2);		//计算伤害量
			printf("玩家剩余血量：%d\n\n", player.hp);
			if (player.hp <= 0) {						//对方HP清零
				printf("玩家已被打败\n");
				return 1;
			}
			else {										//对方未HP清零
				return 0;
			}
		}
		else if (computer.hit < b) {				//未击中
			printf("未击中\n\n");
			return 0;
		}
	}
	else if (a == 2) {		//治疗
		if (computer.run >= r) {		//治疗成功
			printf("治疗成功\n");
			computer.hp = computer.hp + 20;			//成功奖励
			printf("获得加成Hp加20当前血量:%d\n\n", computer.hp);

		}
		else if (computer.run < r) {	//治疗失败
			printf("治疗失败\n");
			computer.hp = computer.hp - 10;			//失败惩罚
			printf("受到伤害Hp-10当前血量：%d\n\n", computer.hp);
		}
	}
	return 0;
}

//游戏主体
void play() {
	int a,b,c;
	while (1) {
		printf("玩家回合\n");
		printf("1.攻击   2.治疗\n");
		scanf("%d", &a);

		b = PlayerRound(a);
		if (b==1) {
			break;
		}
		Sleep(1000);
		printf("电脑回合\n");
		c = ComputerRound();
		if (c==1) {
			break;
		}
	}

}



int main() {
	while (1) {
		int a;
		a = menu();
		if (a == 1) {	//游玩
			DisplayAttribute();
			putchar('\n');
			play();
			break;
		}
		else if (a == 2) {	//退出

			system("pause");
			exit(1);
			
		}
		else if (a != 1 && a != 2) {
			printf("输入错误\n");
		}
	}
	system("pause");
	return 0;
}