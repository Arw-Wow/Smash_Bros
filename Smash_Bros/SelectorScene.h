#pragma once

#include "SceneManager.h"
#include "Scene.h"
#include "Animation.h"
#include "Player.h"
#include "Peashooter.h"
#include "Sunflower.h"
#include "PlayerID.h"
#include "PlayerType.h"

extern IMAGE img_VS;										// VS字图片
extern IMAGE img_1P;										// 1P文本图片
extern IMAGE img_2P;										// 2P文本图片
extern IMAGE img_1P_desc;									// 1P键位描述图片
extern IMAGE img_2P_desc;									// 2P键位描述图片
extern IMAGE img_gravestone_left;							// 向左的墓碑图片
extern IMAGE img_gravestone_right;							// 向右的墓碑图片
extern IMAGE img_selector_tip;								// 选择角色界面提示图片
extern IMAGE img_selector_background;						// 选择角色界面背景图片
extern IMAGE img_1P_selector_btn_idle_left;					// 1P 向左选择按钮闲置状态图片
extern IMAGE img_1P_selector_btn_idle_right;				// 1P 向右选择按钮闲置状态图片
extern IMAGE img_1P_selector_btn_down_left;					// 1P 向左选择按钮按下状态图片
extern IMAGE img_1P_selector_btn_down_right;				// 1P 向右选择按钮按下状态图片
extern IMAGE img_2P_selector_btn_idle_left;					// 2P 向左选择按钮闲置状态图片
extern IMAGE img_2P_selector_btn_idle_right;				// 2P 向右选择按钮闲置状态图片
extern IMAGE img_2P_selector_btn_down_left;					// 2P 向左选择按钮按下状态图片
extern IMAGE img_2P_selector_btn_down_right;				// 2P 向右选择按钮按下状态图片
extern IMAGE img_peashooter_selector_background_left;		// 选择角色界面豌豆射手朝向左的背景图片
extern IMAGE img_peashooter_selector_background_right;		// 选择角色界面豌豆射手朝向右的背景图片
extern IMAGE img_sunflower_selector_background_left;		// 选择角色界面向日葵朝向左的背景图片
extern IMAGE img_sunflower_selector_background_right;		// 选择角色界面向日葵朝向右的背景图片
	
extern Atlas atlas_peashooter_idle_left;					// 豌豆射手朝向左的闲置动画图集
extern Atlas atlas_sunflower_idle_left;						// 向日葵朝向左的闲置动画图集
extern Atlas atlas_peashooter_idle_right;					// 豌豆射手朝向右的闲置动画图集
extern Atlas atlas_sunflower_idle_right;					// 向日葵朝向右的闲置动画图集

extern IMAGE img_avatar_peashooter;							//豌豆射手头像图片
extern IMAGE img_avatar_sunflower;							//向日葵头像图片

extern Player* player_1;
extern Player* player_2;

extern SceneManager* scene_manager;

class SelectorScene :
    public Scene
{
public:

	SelectorScene() = default;

	~SelectorScene() = default;

	//进入场景（类似init函数，不构造但要初始化）
	void onEnter();
	
	//处理数据
	void onUpdate(int delta);
	
	//渲染绘图
	void onDraw(const Camera& camera);
	
	//处理输入
	void onInput(const ExMessage& msg);
	
	//退出场景
	void onExit();

private:

	POINT pos_img_VS = { 0 };							// VS 字图片位置
	POINT pos_img_tip = { 0 };							// 提示信息文本图片位置
	POINT pos_img_1P = { 0 };							// 1P文本图片位置
	POINT pos_img_2P = { 0 };							// 2P文本图片位置
	POINT pos_img_1P_desc = { 0 };						// 1P键位描述图片位置
	POINT pos_img_2P_desc = { 0 };						// 2P键位描述图片位置
	POINT pos_img_1P_name = { 0 };						// 1P名字位置
	POINT pos_img_2P_name = { 0 };						// 2P名字位置
	POINT pos_img_1P_gravestone = { 0 };				// 1P墓碑位置
	POINT pos_img_2P_gravestone = { 0 };				// 2P墓碑位置
	POINT pos_animation_1P = { 0 };						// 1P动画位置
	POINT pos_animation_2P = { 0 };						// 2P动画位置
	POINT pos_1P_selector_btn_left = { 0 };				// 1P向左切换按钮位置
	POINT pos_1P_selector_btn_right = { 0 };			// 1P向右切换按钮位置
	POINT pos_2P_selector_btn_left = { 0 };				// 2P向左切换按钮位置
	POINT pos_2P_selector_btn_right = { 0 };			// 2P向右切换按钮位置

	Animation animation_1P_peashooter;						// 1P豌豆射手动画
	Animation animation_1P_sunflower;						// 1P向日葵动画
	Animation animation_2P_peashooter;						// 2P豌豆射手动画
	Animation animation_2P_sunflower;						// 2P向日葵动画

	PlayerType player_type_1 = PlayerType::PeaShooter;	// 1P角色类型
	PlayerType player_type_2 = PlayerType::SunFlower;	// 2P角色类型

	LPCTSTR str_peashooter_name = "豌豆射手";				// 豌豆射手名字文本
	LPCTSTR str_sunflower_name = "向日葵";				// 向日葵名字文本

	int selector_background_scorll_offset_x = 0;		// 背景板滚动距离

	bool is_btn_1P_left_down = false;					// 1P左键是否按下
	bool is_btn_1P_right_down = false;					// 1P右键是否按下
	bool is_btn_2P_left_down = false;					// 2P左键是否按下
	bool is_btn_2P_right_down = false;					// 2P右键是否按下

private:
	
	void outtextxy_shaded(int x, int y, LPCTSTR str)
	{
		//绘制阴影
		settextcolor(RGB(45, 45, 45));
		outtextxy(x + 3, y + 3, str);
		
		//绘制文本
		settextcolor(WHITE);
		outtextxy(x, y, str);
	}

};

