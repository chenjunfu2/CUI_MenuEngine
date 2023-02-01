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

long GetUserChoice(long min, long max)//��min(����min)��max(����max)
{
	long choice = 0;
	while (true)
	{
		while (scanf("%d", &choice) != 1)
		{
			EatStdinLine();//�̵����뻺�����ڵķǷ������ַ�
			printf("��������,����������:");
		}

		EatStdinLine();//�̵�ʣ���ַ�

		if (choice < min || choice > max)
		{
			printf("���볬��ѡ�Χ,����������:");
			continue;
		}

		//��֤�����˳�ѭ��
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

		printf("\n���������ѡ��:");
		long choice = GetUserChoice(1, menu_size) - 1;

		if (menu_list[choice].IsSubmenu)//�����Ӳ˵�
		{
			unsigned long func_ret = call(menu_list[choice].SubMenu.submenu_list, menu_list[choice].SubMenu.submenu_count);//�ݹ������һ��˵�
			if (func_ret != 0)
			{
				return func_ret - 1;
			}
			continue;//���»ص�����
		}

		//�������Ӳ˵�
		if (menu_list[choice].Function.function_ptr == 0)//���������ڹ��������½��뱾��˵�
		{
			printf("�ù��ܲ�����!");
			system("pause");
			continue;//���»ص�����
		}

		system("cls");//�������뺯��
		unsigned long func_ret = menu_list[choice].Function.function_ptr(menu_list[choice].Function.function_arg);//�ò�˵�û���Ӳ˵�������ù��ܺ���
		if (func_ret != 0)
		{
			return func_ret - 1;
		}
	}
}