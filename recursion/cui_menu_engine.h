#pragma once

#define MAX_OPTION_NAME_LENGTH 32
#define STATIC_SUBMENU_COUNT(submenu) (sizeof(submenu)/sizeof(menu_t))

struct menu_t
{
	char option_name[MAX_OPTION_NAME_LENGTH];
	bool IsSubmenu;//Ϊtrue����ѡ��Ϊ�Ӳ˵����������ѡ����һ������
	union
	{
		struct//����
		{
			void *function_arg;//��Ҫ�����ܺ������ݵĲ���
			unsigned long (*function_ptr)(void *function_arg);//���ܺ��������ڲ������Ӳ˵�ʱ���ã���������ֵ������������ʱҪ���صĲ��������Ϊ0���ڵ�ǰ�����ѭ�������򷵻ص�ָ���Ĳ���
		}Function;

		struct//�Ӳ˵�
		{
			unsigned long submenu_count;//�Ӳ˵�����Ŀ
			const menu_t *submenu_list;//ָ���Ӳ˵��б��ָ��
		}SubMenu;
	};
};

unsigned long call(const menu_t *menu_list, int menu_size);