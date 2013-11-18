#include <string>

#include "Assets.h"

std::map<std::string, Surface*> Assets::Graphics;
std::map<std::string, Animation*> Assets::Animations;
std::map<std::string, Mix_Chunk*> Assets::Sounds;
std::map<std::string, Level*> Assets::Levels;

void Assets::Load() {            
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
	
	//Menu
	Animations["menu"] = new Animation("menu");
	Animations["menu"]->FrameTime = 0.1f;

	for(int i = 0; i < 4; i++) {
		std::string file = "assets/menu/mainmenu_" + std::to_string(i) + ".png";
		Animations["menu"]->AddSprite(new Surface(&file[0]));
	}

	Graphics["menu_select"] = new Surface("assets/Menu/mainmenu_selector.png");
	Graphics["menuitem_startgame"] = new Surface("assets/Menu/mainmenu_option_1.png");
	Graphics["menuitem_leveleditor"] = new Surface("assets/Menu/mainmenu_option_2.png");

	//Player
	//Small
	Animations["player_small_run_left"] = new Animation("player_small_run_left");
	Animations["player_small_run_left"]->FrameTime = 0.08f;
	Animations["player_small_run_left"]->AddSprite(new Surface("assets/player/s_l_run_0.png"));
	Animations["player_small_run_left"]->AddSprite(new Surface("assets/player/s_l_run_1.png"));
	Animations["player_small_run_left"]->AddSprite(new Surface("assets/player/s_l_run_2.png"));

	Animations["player_small_run_right"] = new Animation("player_small_run_right");
	Animations["player_small_run_right"]->FrameTime = 0.08f;
	Animations["player_small_run_right"]->AddSprite(new Surface("assets/player/s_r_run_0.png"));
	Animations["player_small_run_right"]->AddSprite(new Surface("assets/player/s_r_run_1.png"));
	Animations["player_small_run_right"]->AddSprite(new Surface("assets/player/s_r_run_2.png"));

	Graphics["player_small_idle_left"] = new Surface("assets/player/s_l_idle.png");
	Graphics["player_small_idle_right"] = new Surface("assets/player/s_r_idle.png");

	Graphics["player_small_jump_left"] = new Surface("assets/player/s_l_jump.png");
	Graphics["player_small_jump_right"] = new Surface("assets/player/s_r_jump.png");

	Graphics["player_small_turn_left"] = new Surface("assets/player/s_l_skid.png");
	Graphics["player_small_turn_right"] = new Surface("assets/player/s_r_skid.png");

	//Growing
	Animations["player_small_grow_left"] = new Animation("player_grow_run_left");
	Animations["player_small_grow_left"]->FrameTime = 0.1f;
	Animations["player_small_grow_left"]->LoopAnimation = false;
	Surface* leftGrow0 = new Surface("assets/player/l_grow_0.png");
	Surface* leftGrow1 = new Surface("assets/player/l_grow_1.png");
	Surface* leftGrow2 = new Surface("assets/player/l_grow_2.png");

	Animations["player_small_grow_left"]->AddSprite(leftGrow0);
	Animations["player_small_grow_left"]->AddSprite(leftGrow1);
	Animations["player_small_grow_left"]->AddSprite(leftGrow2);

	Animations["player_small_grow_left"]->AddSprite(leftGrow0);
	Animations["player_small_grow_left"]->AddSprite(leftGrow1);
	Animations["player_small_grow_left"]->AddSprite(leftGrow2);

	Animations["player_small_grow_left"]->AddSprite(leftGrow0);
	Animations["player_small_grow_left"]->AddSprite(leftGrow1);
	Animations["player_small_grow_left"]->AddSprite(leftGrow2);

	Animations["player_small_grow_right"] = new Animation("player_small_grow_right");
	Animations["player_small_grow_right"]->FrameTime = 0.1f;
	Animations["player_small_grow_right"]->LoopAnimation = false;
	Surface* rightGrow0 = new Surface("assets/player/r_grow_0.png");
	Surface* rightGrow1 = new Surface("assets/player/r_grow_1.png");
	Surface* rightGrow2 = new Surface("assets/player/r_grow_2.png");

	Animations["player_small_grow_right"]->AddSprite(rightGrow0);
	Animations["player_small_grow_right"]->AddSprite(rightGrow1);
	Animations["player_small_grow_right"]->AddSprite(rightGrow2);

	Animations["player_small_grow_right"]->AddSprite(rightGrow0);
	Animations["player_small_grow_right"]->AddSprite(rightGrow1);
	Animations["player_small_grow_right"]->AddSprite(rightGrow2);

	Animations["player_small_grow_right"]->AddSprite(rightGrow0);
	Animations["player_small_grow_right"]->AddSprite(rightGrow1);
	Animations["player_small_grow_right"]->AddSprite(rightGrow2);

	//Big
	Animations["player_big_run_left"] = new Animation("player_big_run_left");
	Animations["player_big_run_left"]->FrameTime = 0.08f;
	Animations["player_big_run_left"]->AddSprite(new Surface("assets/player/l_l_run_0.png"));
	Animations["player_big_run_left"]->AddSprite(new Surface("assets/player/l_l_run_1.png"));
	Animations["player_big_run_left"]->AddSprite(new Surface("assets/player/l_l_run_2.png"));

	Animations["player_big_run_right"] = new Animation("player_big_run_right");
	Animations["player_big_run_right"]->FrameTime = 0.08f;
	Animations["player_big_run_right"]->AddSprite(new Surface("assets/player/l_r_run_0.png"));
	Animations["player_big_run_right"]->AddSprite(new Surface("assets/player/l_r_run_1.png"));
	Animations["player_big_run_right"]->AddSprite(new Surface("assets/player/l_r_run_2.png"));

	Graphics["player_big_idle_left"] = new Surface("assets/player/l_l_idle.png");
	Graphics["player_big_idle_right"] = new Surface("assets/player/l_r_idle.png");

	Graphics["player_big_jump_left"] = new Surface("assets/player/l_l_jump.png");
	Graphics["player_big_jump_right"] = new Surface("assets/player/l_r_jump.png");

	Graphics["player_big_turn_left"] = new Surface("assets/player/l_l_skid.png");
	Graphics["player_big_turn_right"] = new Surface("assets/player/l_r_skid.png");

	//BigGrowing
	Animations["player_big_grow_left"] = new Animation("player_grow_run_left");
	Animations["player_big_grow_left"]->FrameTime = 0.1f;
	Animations["player_big_grow_left"]->LoopAnimation = false;
	Surface* leftBigGrow0 = new Surface("assets/player/l_transform_0.png");
	Surface* leftBigGrow1 = new Surface("assets/player/l_transform_1.png");
	Surface* leftBigGrow2 = new Surface("assets/player/l_transform_2.png");

	Animations["player_big_grow_left"]->AddSprite(leftBigGrow0);
	Animations["player_big_grow_left"]->AddSprite(leftBigGrow1);
	Animations["player_big_grow_left"]->AddSprite(leftBigGrow2);

	Animations["player_big_grow_left"]->AddSprite(leftBigGrow0);
	Animations["player_big_grow_left"]->AddSprite(leftBigGrow1);
	Animations["player_big_grow_left"]->AddSprite(leftBigGrow2);

	Animations["player_big_grow_left"]->AddSprite(leftBigGrow0);
	Animations["player_big_grow_left"]->AddSprite(leftBigGrow1);
	Animations["player_big_grow_left"]->AddSprite(leftBigGrow2);

	Animations["player_big_grow_right"] = new Animation("player_big_grow_right");
	Animations["player_big_grow_right"]->FrameTime = 0.1f;
	Animations["player_big_grow_right"]->LoopAnimation = false;
	Surface* rightBigGrow0 = new Surface("assets/player/r_transform_0.png");
	Surface* rightBigGrow1 = new Surface("assets/player/r_transform_1.png");
	Surface* rightBigGrow2 = new Surface("assets/player/r_transform_2.png");

	Animations["player_big_grow_right"]->AddSprite(rightBigGrow0);
	Animations["player_big_grow_right"]->AddSprite(rightBigGrow1);
	Animations["player_big_grow_right"]->AddSprite(rightBigGrow2);

	Animations["player_big_grow_right"]->AddSprite(rightBigGrow0);
	Animations["player_big_grow_right"]->AddSprite(rightBigGrow1);
	Animations["player_big_grow_right"]->AddSprite(rightBigGrow2);

	Animations["player_big_grow_right"]->AddSprite(rightBigGrow0);
	Animations["player_big_grow_right"]->AddSprite(rightBigGrow1);
	Animations["player_big_grow_right"]->AddSprite(rightBigGrow2);

	//BigShrinking
	Animations["player_big_shrink_left"] = new Animation("player_shrink_left");
	Animations["player_big_shrink_left"]->FrameTime = 0.1f;
	Animations["player_big_shrink_left"]->LoopAnimation = false;
	Surface* leftBigShrink0 = new Surface("assets/player/l_shrink_0.png");
	Surface* leftBigShrink1 = new Surface("assets/player/l_shrink_1.png");
	Surface* leftBigShrink2 = new Surface("assets/player/l_shrink_2.png");

	Animations["player_big_shrink_left"]->AddSprite(leftBigShrink0);
	Animations["player_big_shrink_left"]->AddSprite(leftBigShrink1);
	Animations["player_big_shrink_left"]->AddSprite(leftBigShrink2);

	Animations["player_big_shrink_left"]->AddSprite(leftBigShrink0);
	Animations["player_big_shrink_left"]->AddSprite(leftBigShrink1);
	Animations["player_big_shrink_left"]->AddSprite(leftBigShrink2);

	Animations["player_big_shrink_left"]->AddSprite(leftBigShrink0);
	Animations["player_big_shrink_left"]->AddSprite(leftBigShrink1);
	Animations["player_big_shrink_left"]->AddSprite(leftBigShrink2);

	Animations["player_big_shrink_right"] = new Animation("player_big_shrink_right");
	Animations["player_big_shrink_right"]->FrameTime = 0.1f;
	Animations["player_big_shrink_right"]->LoopAnimation = false;
	Surface* rightBigShrink0 = new Surface("assets/player/r_shrink_0.png");
	Surface* rightBigShrink1 = new Surface("assets/player/r_shrink_1.png");
	Surface* rightBigShrink2 = new Surface("assets/player/r_shrink_2.png");

	Animations["player_big_shrink_right"]->AddSprite(rightBigShrink0);
	Animations["player_big_shrink_right"]->AddSprite(rightBigShrink1);
	Animations["player_big_shrink_right"]->AddSprite(rightBigShrink2);

	Animations["player_big_shrink_right"]->AddSprite(rightBigShrink0);
	Animations["player_big_shrink_right"]->AddSprite(rightBigShrink1);
	Animations["player_big_shrink_right"]->AddSprite(rightBigShrink2);

	Animations["player_big_shrink_right"]->AddSprite(rightBigShrink0);
	Animations["player_big_shrink_right"]->AddSprite(rightBigShrink1);
	Animations["player_big_shrink_right"]->AddSprite(rightBigShrink2);

	Animations["gui_coin"] = new Animation("gui_coin");
	Animations["gui_coin"]->FrameTime = 0.1f;
	Animations["gui_coin"]->AddSprite(new Surface("assets/player/coin_0.png"));
	Animations["gui_coin"]->AddSprite(new Surface("assets/player/coin_1.png"));
	Animations["gui_coin"]->AddSprite(new Surface("assets/player/coin_2.png"));
	Animations["gui_coin"]->AddSprite(new Surface("assets/player/coin_3.png"));

	//Fire
	Animations["player_fire_run_left"] = new Animation("player_fire_run_left");
	Animations["player_fire_run_left"]->FrameTime = 0.08f;
	Animations["player_fire_run_left"]->AddSprite(new Surface("assets/player/g_l_run_0.png"));
	Animations["player_fire_run_left"]->AddSprite(new Surface("assets/player/g_l_run_1.png"));
	Animations["player_fire_run_left"]->AddSprite(new Surface("assets/player/g_l_run_2.png"));

	Animations["player_fire_run_right"] = new Animation("player_fire_run_right");
	Animations["player_fire_run_right"]->FrameTime = 0.08f;
	Animations["player_fire_run_right"]->AddSprite(new Surface("assets/player/g_r_run_0.png"));
	Animations["player_fire_run_right"]->AddSprite(new Surface("assets/player/g_r_run_1.png"));
	Animations["player_fire_run_right"]->AddSprite(new Surface("assets/player/g_r_run_2.png"));

	Graphics["player_fire_idle_left"] = new Surface("assets/player/g_l_idle.png");
	Graphics["player_fire_idle_right"] = new Surface("assets/player/g_r_idle.png");

	Graphics["player_fire_jump_left"] = new Surface("assets/player/g_l_jump.png");
	Graphics["player_fire_jump_right"] = new Surface("assets/player/g_r_jump.png");

	Graphics["player_fire_turn_left"] = new Surface("assets/player/g_l_skid.png");
	Graphics["player_fire_turn_right"] = new Surface("assets/player/g_r_skid.png");

	Animations["fire"] = new Animation("fire");
	Animations["fire"]->FrameTime = 0.1f;
	Animations["fire"]->AddSprite(new Surface("assets/player/fire_0.png"));
	Animations["fire"]->AddSprite(new Surface("assets/player/fire_1.png"));
	Animations["fire"]->AddSprite(new Surface("assets/player/fire_2.png"));

	Graphics["player_die"] = new Surface("assets/player/s_die.png");

	//Environment
	Graphics["brick_normal"] = new Surface("assets/Environment/brick_normal.png");

	Animations["coincrate"] = new Animation("coincrate");
	Animations["coincrate"]->FrameTime = 0.15f;
	Graphics["empty_crate"] = new Surface("assets/Environment/block_02_0.png");

	for(int i = 0; i < 6; i++) {
		std::string file = "assets/Environment/block_03_" + std::to_string(i) + ".png";
		Animations["coincrate"]->AddSprite(new Surface(&file[0]));
	}

	Animations["coin_jump"] = new Animation("coin_jump");
	Animations["coin_jump"]->FrameTime = 0.06f;
	Animations["coin_jump"]->AddSprite(new Surface("assets/Environment/s_coin_0.png"));
	Animations["coin_jump"]->AddSprite(new Surface("assets/Environment/s_coin_1.png"));
	Animations["coin_jump"]->AddSprite(new Surface("assets/Environment/s_coin_2.png"));
	Animations["coin_jump"]->AddSprite(new Surface("assets/Environment/s_coin_3.png"));

	Animations["coin_stay"] = new Animation("coin_stay");
	Animations["coin_stay"]->FrameTime = 0.1f;
	Animations["coin_stay"]->AddSprite(new Surface("assets/Environment/b_coin_0.png"));
	Animations["coin_stay"]->AddSprite(new Surface("assets/Environment/b_coin_1.png"));
	Animations["coin_stay"]->AddSprite(new Surface("assets/Environment/b_coin_2.png"));
	Animations["coin_stay"]->AddSprite(new Surface("assets/Environment/b_coin_3.png"));

	Graphics["mushroom"] = new Surface("assets/Environment/mushroom.png");

	Animations["flower"] = new Animation("flower");
	Animations["flower"]->FrameTime = 0.08f;
	Animations["flower"]->AddSprite(new Surface("assets/Environment/plant_0.png"));
	Animations["flower"]->AddSprite(new Surface("assets/Environment/plant_1.png"));
	Animations["flower"]->AddSprite(new Surface("assets/Environment/plant_2.png"));
	Animations["flower"]->AddSprite(new Surface("assets/Environment/plant_3.png"));

	Graphics["pipe_horizontal"] = new Surface("assets/Environment/pipe_horizontal.png");
	Graphics["pipe_vertical"] = new Surface("assets/Environment/pipe_vertical.png");
	Graphics["flag"] = new Surface("assets/Environment/flag.png");

	Graphics["vine_top"] = new Surface("assets/Environment/vine_top.png");
	Graphics["vine_part"] = new Surface("assets/Environment/vine_part.png");

	//Enemies
	Animations["goomba"] = new Animation("goomba");
	Animations["goomba"]->FrameTime = 0.15f;
	Animations["goomba"]->AddSprite(new Surface("assets/Enemies/goomba_1_r_0.png"));
	Animations["goomba"]->AddSprite(new Surface("assets/Enemies/goomba_1_r_1.png"));

	Graphics["goomba"] = new Surface("assets/Enemies/goomba_1_f.png");
	Graphics["goomba_flipped"] = new Surface("assets/Enemies/goomba_flipped.png");

	Animations["koopa_walk_left"] = new Animation("koopa_walk_left");
	Animations["koopa_walk_left"]->FrameTime = 0.15f;
	Animations["koopa_walk_left"]->AddSprite(new Surface("assets/Enemies/koopa_1_l_r_0.png"));
	Animations["koopa_walk_left"]->AddSprite(new Surface("assets/Enemies/koopa_1_l_r_1.png"));

	Animations["koopa_walk_right"] = new Animation("koopa_walk_right");
	Animations["koopa_walk_right"]->FrameTime = 0.15f;
	Animations["koopa_walk_right"]->AddSprite(new Surface("assets/Enemies/koopa_1_r_r_0.png"));
	Animations["koopa_walk_right"]->AddSprite(new Surface("assets/Enemies/koopa_1_r_r_1.png"));

	Animations["koopa_shell"] = new Animation("koopa_shell");
	Animations["koopa_shell"]->FrameTime = 0.1f;
	Animations["koopa_shell"]->LoopAnimation = false;
	Animations["koopa_shell"]->AddSprite(new Surface("assets/Enemies/koopa_1_n_0.png"));
	Animations["koopa_shell"]->AddSprite(new Surface("assets/Enemies/koopa_1_n_1.png"));

	Animations["koopa_die"] = new Animation("koopa_shell");
	Animations["koopa_die"]->FrameTime = 0.1f;
	Animations["koopa_die"]->LoopAnimation = false;
	Animations["koopa_die"]->AddSprite(new Surface("assets/Enemies/koopa_1_f_0.png"));
	Animations["koopa_die"]->AddSprite(new Surface("assets/Enemies/koopa_1_f_1.png"));

	//Levels
	Levels["1"] = new Level("1");
	Levels["1"]->Init();

	Levels["11"] = new Level("11");
	Levels["11"]->Init();

	Levels["2"] = new Level("2");
	Levels["2"]->Init();

	//Editor
	for(int i = 1; i <= TYPE_COUNT; i++) {
		std::string file = "assets/Editor/editor_" + std::to_string(i) + ".png";
		std::string name = "editor_" + std::to_string(i);
		
		Graphics[name] = new Surface(&file[0]);
	}

	//Characters
	std::string chars = "-_0123456789abcdefghijklmnopqrstuvwxyz";
	for(int i = 0; i < chars.length(); i++) {
		std::string fileName = "assets/Characters/";
		fileName += chars[i];
		fileName += ".png";

		std::string charKey = "chars_";
		charKey += chars[i];
		Assets::Graphics[charKey] = new Surface(&fileName[0]);
	}
}

void Assets::DestroyLevels() {	

}