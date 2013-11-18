#include "Helper.h"
#include "Assets.h"
#include "Input.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "LoadScene.h"
#include "MenuScene.h"
#include "Fire.h"
#include "ScoreEntity.h"

#include "Player.h"

#define PLAYER_ACCELERATION 2.5f
#define PLAYER_MAX_SPEED 200
#define PLAYER_DIE_FALL_SPEED 350
#define PLAYER_PIPE_GO_SPEED 50

Player::Player() : GravityEntity() {

	RunAnimations[SMALL_PLAYER_DIRECTION_LEFT] = new Animation(*Assets::Animations["player_small_run_left"]);
	RunAnimations[SMALL_PLAYER_DIRECTION_RIGHT] = new Animation(*Assets::Animations["player_small_run_right"]);
	
	IdleGraphics[SMALL_PLAYER_DIRECTION_LEFT] = Assets::Graphics["player_small_idle_left"];
	IdleGraphics[SMALL_PLAYER_DIRECTION_RIGHT] = Assets::Graphics["player_small_idle_right"];

	JumpGraphics[SMALL_PLAYER_DIRECTION_LEFT] = Assets::Graphics["player_small_jump_left"];
	JumpGraphics[SMALL_PLAYER_DIRECTION_RIGHT] = Assets::Graphics["player_small_jump_right"];

	TurnGraphics[SMALL_PLAYER_DIRECTION_LEFT] = Assets::Graphics["player_small_turn_left"];
	TurnGraphics[SMALL_PLAYER_DIRECTION_RIGHT] = Assets::Graphics["player_small_turn_right"];

	RunAnimations[BIG_PLAYER_DIRECTION_LEFT] = new Animation(*Assets::Animations["player_big_run_left"]);
	RunAnimations[BIG_PLAYER_DIRECTION_RIGHT] = new Animation(*Assets::Animations["player_big_run_right"]);
	
	IdleGraphics[BIG_PLAYER_DIRECTION_LEFT] = Assets::Graphics["player_big_idle_left"];
	IdleGraphics[BIG_PLAYER_DIRECTION_RIGHT] = Assets::Graphics["player_big_idle_right"];

	JumpGraphics[BIG_PLAYER_DIRECTION_LEFT] = Assets::Graphics["player_big_jump_left"];
	JumpGraphics[BIG_PLAYER_DIRECTION_RIGHT] = Assets::Graphics["player_big_jump_right"];

	TurnGraphics[BIG_PLAYER_DIRECTION_LEFT] = Assets::Graphics["player_big_turn_left"];
	TurnGraphics[BIG_PLAYER_DIRECTION_RIGHT] = Assets::Graphics["player_big_turn_right"];

	RunAnimations[FIRE_PLAYER_DIRECTION_LEFT] = new Animation(*Assets::Animations["player_fire_run_left"]);
	RunAnimations[FIRE_PLAYER_DIRECTION_RIGHT] = new Animation(*Assets::Animations["player_fire_run_right"]);
	
	IdleGraphics[FIRE_PLAYER_DIRECTION_LEFT] = Assets::Graphics["player_fire_idle_left"];
	IdleGraphics[FIRE_PLAYER_DIRECTION_RIGHT] = Assets::Graphics["player_fire_idle_right"];

	JumpGraphics[FIRE_PLAYER_DIRECTION_LEFT] = Assets::Graphics["player_fire_jump_left"];
	JumpGraphics[FIRE_PLAYER_DIRECTION_RIGHT] = Assets::Graphics["player_fire_jump_right"];

	TurnGraphics[FIRE_PLAYER_DIRECTION_LEFT] = Assets::Graphics["player_fire_turn_left"];
	TurnGraphics[FIRE_PLAYER_DIRECTION_RIGHT] = Assets::Graphics["player_fire_turn_right"];

	GrowAnimations[SMALL_PLAYER_DIRECTION_LEFT] = new Animation(*Assets::Animations["player_small_grow_left"]);
	GrowAnimations[SMALL_PLAYER_DIRECTION_RIGHT] = new Animation(*Assets::Animations["player_small_grow_right"]);
	GrowAnimations[BIG_PLAYER_DIRECTION_LEFT] = new Animation(*Assets::Animations["player_big_grow_left"]);
	GrowAnimations[BIG_PLAYER_DIRECTION_RIGHT] = new Animation(*Assets::Animations["player_big_grow_right"]);

	ShrinkAnimations[BIG_PLAYER_DIRECTION_LEFT] = new Animation(*Assets::Animations["player_big_shrink_left"]);
	ShrinkAnimations[BIG_PLAYER_DIRECTION_RIGHT] = new Animation(*Assets::Animations["player_big_shrink_right"]);
	ShrinkAnimations[FIRE_PLAYER_DIRECTION_LEFT] = new Animation(*Assets::Animations["player_big_shrink_left"]);
	ShrinkAnimations[FIRE_PLAYER_DIRECTION_RIGHT] = new Animation(*Assets::Animations["player_big_shrink_right"]);

	Velocity.x = Velocity.y = 0;

	SizeX = 24;
	SizeY = 32;

	Mode = PLAYER_MODE_SMALL;
	Direction = SMALL_PLAYER_DIRECTION_RIGHT;
	State = PLAYER_STATE_DEFAULT;

	Graphic = IdleGraphics[Direction];

	Type = "player";

	GScene = 0;

	DefaultGravity = 30;
	ActualGravity = 30;
	MinimunGravity = 15;
	HorizontalAcceleration = PLAYER_ACCELERATION;	

	hurtable = true;
	notHurtableTime = 3.0f;
	notHurtableTimer = 0;

	MaxSpeed = PLAYER_MAX_SPEED;

	Score = 0;
	Lifes = 3;
	CoinCount = 0;

	dieTimer = 0;

	pipeTime = 0.5f;
	pipeTimer = 0;

	ZOrder = 20;
}


Player::~Player(void) {
}

void Player::Init() {
	GravityEntity::Init();

	dieTimer = 0;
	Velocity.x = Velocity.y = 0;

	SizeX = 24;
	SizeY = 32;

	Mode = PLAYER_MODE_SMALL;
	Direction = SMALL_PLAYER_DIRECTION_RIGHT;
	State = PLAYER_STATE_DEFAULT;

	Graphic = IdleGraphics[Direction];
}

void Player::Update(float deltaTime) {
	switch (State) {
		case PLAYER_STATE_DEFAULT:
			updateDefaultState(deltaTime);
			break;
		case PLAYER_STATE_GROWING:						
			if(CurrentAnimation->Finished) {
				SizeY = 64;				
				if(Mode == PLAYER_MODE_BIG) {
					Mode = PLAYER_MODE_FIRE;
				} else {
					Mode = PLAYER_MODE_BIG;
				}
				
				State = PLAYER_STATE_DEFAULT;

				switch(Direction) {
					case SMALL_PLAYER_DIRECTION_LEFT:
						Direction = BIG_PLAYER_DIRECTION_LEFT;
						break;
					case SMALL_PLAYER_DIRECTION_RIGHT:
						Direction = BIG_PLAYER_DIRECTION_RIGHT;
						break;
					case BIG_PLAYER_DIRECTION_LEFT:
						Direction = FIRE_PLAYER_DIRECTION_LEFT;
						break;
					case BIG_PLAYER_DIRECTION_RIGHT:
						Direction = FIRE_PLAYER_DIRECTION_RIGHT;
						break;
				}

				Velocity.y = 0;
			}
			break;
		case PLAYER_STATE_SHRINKING:
			if(CurrentAnimation->Finished) {
				SizeY = 32;
				Position.y += 32;
				Mode = PLAYER_MODE_SMALL;
				State = PLAYER_STATE_DEFAULT;

				hurtable = false;

				if(Direction == BIG_PLAYER_DIRECTION_LEFT || Direction == FIRE_PLAYER_DIRECTION_LEFT) {
					Direction = SMALL_PLAYER_DIRECTION_LEFT;
				} else {
					Direction = SMALL_PLAYER_DIRECTION_RIGHT;
				}

				Velocity.y = 0;
			}
			
			break;
		case PLAYER_STATE_DYING:
			dieTimer += deltaTime;

			if(dieTimer <= 1.0f) {
				//stay
			} else if(dieTimer <= 1.2f) {
				Position.y -= PLAYER_DIE_FALL_SPEED * deltaTime;
			} else if(dieTimer > 1.2f) {
				Position.y += PLAYER_DIE_FALL_SPEED * deltaTime;
			}
			break;
		case PLAYER_STATE_PIPE_IN:
			Position += Velocity * deltaTime;

			pipeTimer += deltaTime;
			if(pipeTimer >= pipeTime) {
				pipeTimer = 0;
				State = PLAYER_STATE_DEFAULT;
				GScene->SwitchToSubLevel();
			}
			break;
		case PLAYER_STATE_ON_FLAG:	
			OnGround = true;
			if(!CollidesWithTiles(Position.x, Position.y + (Velocity.y * deltaTime))) {
				Position.y += Velocity.y * deltaTime;
			}
			break;
		case PLAYER_STATE_GO_TO_FINISH:
			GravityEntity::Update(deltaTime);
			animate();

			if(CollidesWith("level_end")) {
				State = PLAYER_STATE_DEFAULT;
				GScene->SwitchToNextLevel();
			}
			break;
		case PLAYER_STATE_ON_VINE:
			OnGround = true;
			CurrentAnimation = 0;
			Graphic = IdleGraphics[Direction];
			if(Input::IsKeyDown(SDLK_UP)) {
				Position.y -= 50 * deltaTime;
			}
			if(Input::IsKeyDown(SDLK_DOWN)) {
				Position.y += 50 * deltaTime;
			}
			if(Input::IsKeyDown(SDLK_LEFT)) {
				Position.x -= 50 * deltaTime;
			}
			if(Input::IsKeyDown(SDLK_RIGHT)) {
				Position.x += 50 * deltaTime;
			}
		default:
			break;
	}
}

void Player::updateDefaultState(float deltaTime) {
	GravityEntity::Update(deltaTime);

	if(Mode == PLAYER_MODE_FIRE && Input::IsKeyJustPressed(SDLK_LSHIFT)) {
		Scene->AddEntity(new Fire(Position.x + SizeX, Position.y, Direction == FIRE_PLAYER_DIRECTION_LEFT ? -1 : 1));
	}

	if(Input::IsKeyDown(SDLK_LSHIFT)) {
		HorizontalAcceleration = PLAYER_ACCELERATION * 1.5f;
		MaxSpeed = PLAYER_MAX_SPEED * 1.5f;
	} else {
		HorizontalAcceleration = PLAYER_ACCELERATION;
		MaxSpeed = PLAYER_MAX_SPEED;
	}

	if(Input::IsKeyDown(SDLK_RIGHT)) {
		Velocity.x += HorizontalAcceleration;				
	}
	if(Input::IsKeyDown(SDLK_LEFT)) {
		Velocity.x -= HorizontalAcceleration;		
	}	

	if(OnGround) {		
		if(Input::IsKeyJustPressed(SDLK_SPACE)) {
			Velocity.y = -500;
		}		
	} else {
		if(Velocity.y < 0) {
			if(Input::IsKeyDown(SDLK_SPACE)) {
				Gravity = MinimunGravity;
			} else {
				Gravity = DefaultGravity;
			}
		} else {
			Gravity = DefaultGravity;
		}		
	}

	animate();	

	if(!Input::IsKeyDown(SDLK_LEFT) && !Input::IsKeyDown(SDLK_RIGHT) && Velocity.x != 0) {
		if(Velocity.x > 0) {
			Velocity.x = max(Velocity.x - 1, 0);
		} else {		
			Velocity.x = min(0, Velocity.x + 1);
		}
	}

	if((Velocity.x > 0 && Input::IsKeyDown(SDLK_LEFT)) || Velocity.x < 0 && Input::IsKeyDown(SDLK_RIGHT)) {
		Velocity.x -= Helper::Sign(Velocity.x) * 2;	
	}

	if (abs(Velocity.x) > MaxSpeed) { 
		Velocity.x = Helper::Sign(Velocity.x) * MaxSpeed; 
	}

	Entity* mush = CollidesWith("mushroom");
	if(mush) {	
		Scene->AddEntity(new ScoreEntity(Position.x, Position.y, 300));
		if(Mode != PLAYER_MODE_FIRE) {
			if(Mode == PLAYER_MODE_SMALL) {
				Position.y -= 32;
			}
			
			State = PLAYER_STATE_GROWING;	
			GrowAnimations[Direction]->Play(false);
			CurrentAnimation = GrowAnimations[Direction];
		}
		Scene->RemoveEntity(mush);
	}

	if(hurtable && !(Velocity.y > 0)) {
		if(CollidesWith("enemy") || CollidesWith("shell")) {
			if(Mode != PLAYER_MODE_SMALL) {				
				State = PLAYER_STATE_SHRINKING;
				ShrinkAnimations[Direction]->Play(false);
				CurrentAnimation = ShrinkAnimations[Direction];
			} else {
				CurrentAnimation = 0;
				Graphic = Assets::Graphics["player_die"];
				State = PLAYER_STATE_DYING;
			}
			
		}
	}

	if(!hurtable) {
		Hidden = (bool)Helper::GetRandomInt(0, 2);
		notHurtableTimer += deltaTime;
		if(notHurtableTimer >= notHurtableTime) {
			notHurtableTimer = 0;
			hurtable = true;
			Hidden = false;
		}
	}

	if(Input::IsKeyJustPressed(SDLK_DOWN) && CollidesWith("pipe_in", Position.x, Position.y + 2)) {
		Velocity.y = PLAYER_PIPE_GO_SPEED;
		Velocity.x = 0;
		State = PLAYER_STATE_PIPE_IN;
	}

	if(Input::IsKeyDown(SDLK_RIGHT) && CollidesWith("pipe_in_vert", Position.x + 3, Position.y)) {
		Velocity.x = PLAYER_PIPE_GO_SPEED;	
		Velocity.y = 0;
		State = PLAYER_STATE_PIPE_IN;
	}

	if(Position.x < Scene->Camera.x) {
		Position.x = Scene->Camera.x;
	}
}

void Player::animate() {
	if(Velocity.x > 0 && OnGround) {
		switch (Mode)
		{
			case PLAYER_MODE_SMALL:
				Direction = SMALL_PLAYER_DIRECTION_RIGHT;
				break;
			case PLAYER_MODE_BIG:
				Direction = BIG_PLAYER_DIRECTION_RIGHT;
				break;
			case PLAYER_MODE_FIRE:
				Direction = FIRE_PLAYER_DIRECTION_RIGHT;
				break;
			default:
				break;
		}
	} else if(Velocity.x < 0 && OnGround) {
		switch (Mode)
		{
			case PLAYER_MODE_SMALL:
				Direction = SMALL_PLAYER_DIRECTION_LEFT;
				break;
			case PLAYER_MODE_BIG:
				Direction = BIG_PLAYER_DIRECTION_LEFT;
				break;
			case PLAYER_MODE_FIRE:
				Direction = FIRE_PLAYER_DIRECTION_LEFT;
				break;
			default:
				break;
		}		
	}
	
	if(abs(Velocity.x) > 0 && OnGround) {
		CurrentAnimation = RunAnimations[Direction];
	} else if(!OnGround) {
		CurrentAnimation = 0;
		Graphic = JumpGraphics[Direction];
	} else {
		CurrentAnimation = 0;
		Graphic = IdleGraphics[Direction];
	}

	if(OnGround) {
		if(Velocity.x > 0 && Input::IsKeyDown(SDLK_LEFT)) {
			CurrentAnimation = 0;
			switch (Mode)
			{
				case PLAYER_MODE_SMALL:
					Graphic = TurnGraphics[SMALL_PLAYER_DIRECTION_LEFT];
					break;
				case PLAYER_MODE_BIG:
					Graphic = TurnGraphics[BIG_PLAYER_DIRECTION_LEFT];
					break;
				case PLAYER_MODE_FIRE:
					Graphic = TurnGraphics[FIRE_PLAYER_DIRECTION_LEFT];
					break;
				default:
					break;
			}	
		}

		if(Velocity.x < 0 && Input::IsKeyDown(SDLK_RIGHT)) {
			CurrentAnimation = 0;
			switch (Mode)
			{
				case PLAYER_MODE_SMALL:
					Graphic = TurnGraphics[SMALL_PLAYER_DIRECTION_RIGHT];
					break;
				case PLAYER_MODE_BIG:
					Graphic = TurnGraphics[BIG_PLAYER_DIRECTION_RIGHT];
					break;
				case PLAYER_MODE_FIRE:
					Graphic = TurnGraphics[FIRE_PLAYER_DIRECTION_RIGHT];
					break;
				default:
					break;
			}	
		}
	}
}

void Player::Draw(Surface* screen, float deltaTime) {
	Entity::Draw(screen, deltaTime);
	Helper::PrintText(50, 15, "mario", screen);
	Helper::PrintText(50, 32, Helper::FixedLength(Score, 6), screen);

	Assets::Animations["gui_coin"]->Update(deltaTime);
	Assets::Animations["gui_coin"]->GetCurrentSurface()->AlphaCopyTo(screen, 190, 28);
	std::string coins = "x" + Helper::FixedLength(CoinCount, 2);
	Helper::PrintText(210, 32, coins, screen);
	
	
	Helper::PrintText(285, 15, "world", screen);
	if(!Inited || GScene->CurrentLevel->Name.compare("1") == 0) {
		Helper::PrintText(300, 32, "1-1", screen);
	} else {
		Helper::PrintText(300, 32, "1-2", screen);
	}
	
	Helper::PrintText(400, 15, "time", screen);
	if(Inited) {
		Helper::PrintText(415, 32, Helper::FixedLength(GScene->Time, 3), screen);
	} else {
		Helper::PrintText(415, 32, Helper::FixedLength(400, 3), screen);
	}
	
}

SDL_Rect Player::GetBottom() {
	SDL_Rect bottom;
	bottom.x = Position.x;
	bottom.y = Position.y + SizeY;
	bottom.w = SizeX;
	bottom.h = 5;	

	return bottom;
}

void Player::Die() {
	State = PLAYER_STATE_DEFAULT;
	Mode = PLAYER_MODE_SMALL;
	Direction = SMALL_PLAYER_DIRECTION_RIGHT;

	Graphic = IdleGraphics[Direction];
	Lifes--;
	if(Lifes >= 0) {
		Scene->Manager->SwitchScene(new LoadScene(this, GScene->CurrentLevel->Name));
		Scene = 0;
		GScene = 0;
		Inited = false;
	} else {
		Scene->Manager->SwitchScene(new MenuScene());
	}
	
}