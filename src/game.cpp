#include "game.h"
#include "utils.h"
#include "entity.h"
#include "physics.h"
#include "level.h"
#include "gui.h"

#include <lua.hpp>

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
int FRAME_RATE = 60;
int ANIMATION_RATE = 4;
int BUTTON_JUMP = 0;
bool quit = false;

SDL_Window* window = NULL;
SDL_Renderer* windowRenderer = NULL;
SDL_Joystick* controller = NULL;
SDL_Event e;
lua_State* lua_global = NULL;

Level map[10][10];
Level* currLevel;
Entity player;

int main(int argc, char** argv){
  if(!init()){
    std::clog<<"Critical Error: Could not initialise"<<std::endl;
    return 1;
  }

  mainLoop();

  close();
  
  return 0;
  
}

int xdir = 0;

void handleEvents(){

  while(SDL_PollEvent(&e) != 0){
	  
      if(e.type == SDL_QUIT){
		quit = true;
      }
      else if(e.type == SDL_JOYAXISMOTION){
		//Controller 0
		if(e.jaxis.which == 0){
		  ///X-axis
		  if(e.jaxis.axis == 0){
			if(e.jaxis.value < -8000){
			  xdir = -1;
			}
			else if(e.jaxis.value>8000){
			  xdir = 1;
			}
			else{
			  xdir = 0;
			}
		  } 
		}
      }
      else if(e.type == SDL_JOYBUTTONDOWN){
		if(player.pBody.grounded && e.jbutton.button == BUTTON_JUMP){
		  std::clog<<"jump"<<std::endl;
		  player.pBody.addForce(0,-100);
		  player.pBody.grounded = false;
		}
      }
	  else if(e.type == SDL_KEYDOWN){
		if(player.pBody.grounded && e.key.keysym.sym == SDLK_w){
		  player.pBody.addForce(0,-100);
		  player.pBody.grounded = false;
		}
		else if(e.key.keysym.sym == SDLK_a){
		  xdir = -1;
		  //player.pBody.velx -=1;
		}
		else if(e.key.keysym.sym == SDLK_d){
		  xdir = 1;
		  //player.pBody.velx +=1;
		}
	  }
	  else if(e.type == SDL_KEYUP){
		if(e.key.keysym.sym == SDLK_d && xdir == 1){
		  xdir = 0;
		  //player.pBody.velx -=1;
		}
		else if(e.key.keysym.sym == SDLK_a && xdir == -1){
		  xdir = 0;
		  //player.pBody.velx +=1;
		}
	  }
    }

  player.transform.move(xdir, 0);
  
}

void renderFrame(){

  SDL_RenderClear(windowRenderer);
  SDL_SetRenderDrawColor(windowRenderer,0,0,0,255);
  
  (*currLevel).render(windowRenderer);
  for(int i = 0; i<currLevel->lights.size(); i++){
    player.renderShadow(windowRenderer, currLevel->lights[i]);
  }
  player.render(windowRenderer);
  
  SDL_RenderPresent(windowRenderer);
  
}

void mainLoop(){
  
  SDL_Rect screenRect;
  float xdir = 0;
  Physics physics = Physics(100);
  int startTime = 0;
  int framecount = 0;
  int animationTime = 0;
  
  screenRect.x=0;
  screenRect.y=0;
  screenRect.w = SCREEN_WIDTH;
  screenRect.h = SCREEN_HEIGHT;

  player = Entity(new Transform(90,90,20,20), new Sprite("spriteTest.bmp",10,10),new PhysicsBody());
  player.transform.constrain(screenRect);
  player.pBody.target = &player.transform;

  SDL_SetTextureAlphaMod(player.sprite.sheet, 0xFF);
  
  physics.add(&player.pBody);

  std::vector<Tile> temp;
  temp.push_back(Tile(new Transform(90,200,20,20), new Sprite("spriteTest.bmp",10,10)));
  
  map[0][0] = Level(&temp, loadTexture("test.bmp"));
  map[0][0].lights.push_back(Light(0,0,3));
  map[0][0].lights.push_back(Light(200,0,4));
  currLevel = &map[0][0];
  
  while(!quit){

	handleEvents();

	//Render new frame
    startTime = SDL_GetTicks();
	renderFrame();
	if(SDL_GetTicks()-startTime < 1000.f/FRAME_RATE){   //Cap Framerate
	  SDL_Delay(1000.f/FRAME_RATE-(SDL_GetTicks()-startTime));
	}

	//Frame independant updates
	////Update animation state
    animationTime+=SDL_GetTicks()-startTime;
	if(animationTime>1000.f/ANIMATION_RATE){
      player.sprite.nextFrame();
      (*currLevel).update();
      animationTime-=1000.f/ANIMATION_RATE;
    }

	////Physics Update
	physics.update((SDL_GetTicks()-startTime)/1000.f);
	player.pBody.update((SDL_GetTicks()-startTime)/1000.f);
	
	////Level Update
    if((*currLevel).collides(&(player.transform))){
      player.pBody.vely = 0;
      player.pBody.grounded = true;
    }
	else{
	  player.pBody.grounded = false;
	}
	if((*currLevel).checkWarp(&(player.transform))>=0){
	  int index = (*currLevel).checkWarp(&(player.transform));
	  player.transform.setPosition((*currLevel).warps[index].x, (*currLevel).warps[index].y);
	  currLevel = &map[(*currLevel).warps[index].dest_level_x][(*currLevel).warps[index].dest_level_y];
	}

	//Output framerate information
    std::clog<<framecount/(SDL_GetTicks()/1000.f)<<std::endl;
    framecount++;

  }

}

