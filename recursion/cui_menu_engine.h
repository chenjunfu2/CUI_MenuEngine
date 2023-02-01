#pragma once

#define MAX_OPTION_NAME_LENGTH 32
#define STATIC_SUBMENU_COUNT(submenu) (sizeof(submenu)/sizeof(menu_t))

struct menu_t
{
	char option_name[MAX_OPTION_NAME_LENGTH];
	bool IsSubmenu;//为true代表本选项为子菜单，否则代表本选项是一个功能
	union
	{
		struct//功能
		{
			void *function_arg;//将要给功能函数传递的参数
			unsigned long (*function_ptr)(void *function_arg);//功能函数，仅在不存在子菜单时调用，函数返回值代表当函数结束时要返回的层数，如果为0则在当前层继续循环，否则返回到指定的层数
		}Function;

		struct//子菜单
		{
			unsigned long submenu_count;//子菜单项数目
			const menu_t *submenu_list;//指向子菜单列表的指针
		}SubMenu;
	};
};

unsigned long call(const menu_t *menu_list, int menu_size);