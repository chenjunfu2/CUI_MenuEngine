#include <stdio.h>
#include <stdlib.h>

#include "cui_menu_engine.h"

void EatStdinLine(void)
{
	while (getchar() != '\n')
	{
		continue;
	}
}

long GetUserChoice(long min, long max)//从min(包含min)到max(包含max)
{
	long choice = 0;
	while (true)
	{
		while (scanf("%d", &choice) != 1)
		{
			EatStdinLine();//吞掉输入缓冲区内的非法输入字符
			printf("输入有误,请重新输入:");
		}

		EatStdinLine();//吞掉剩余字符

		if (choice < min || choice > max)
		{
			printf("输入超出选项范围,请重新输入:");
			continue;
		}

		//验证无误，退出循环
		break;
	}

	return choice;
}

unsigned long call(const menu_t *menu_list, int menu_size)
{
	while (true)
	{
		system("cls");
		for (int i = 0; i < menu_size; ++i)
		{
			printf("%d.%s\n", i + 1, menu_list[i].option_name);
		}

		printf("\n请输入序号选择:");
		long choice = GetUserChoice(1, menu_size) - 1;

		if (menu_list[choice].IsSubmenu)//存在子菜单
		{
			unsigned long func_ret = call(menu_list[choice].SubMenu.submenu_list, menu_list[choice].SubMenu.submenu_count);//递归进入下一层菜单
			if (func_ret != 0)
			{
				return func_ret - 1;
			}
			continue;//重新回到本层
		}

		//不存在子菜单
		if (menu_list[choice].Function.function_ptr == 0)//如果该项不存在功能则重新进入本层菜单
		{
			printf("该功能不存在!");
			system("pause");
			continue;//重新回到本层
		}

		system("cls");//清屏进入函数
		unsigned long func_ret = menu_list[choice].Function.function_ptr(menu_list[choice].Function.function_arg);//该层菜单没有子菜单，则调用功能函数
		if (func_ret != 0)
		{
			return func_ret - 1;
		}
	}
}