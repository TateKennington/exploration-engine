#include "game.h"
#include "utils.h"
#include "entity.h"
#include "physics.h"
#include "level.h"
#include "gui.h"

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
int FRAME_RATE = 60;
int ANIMATION_RATE = 4;
int BUTTON_JUMP = 0;

SDL_Window* window = NULL;
SDL_Renderer* windowRenderer = NULL;
SDL_Joystick* controller = NULL;
SDL_Event e;


int main(int argc, char** argv){
  if(!init()){
    std::clog<<"Critical Error: Could not initialise"<<std::endl;
    return 1;
  }

  mainLoop();

  close();
  
  return 0;
  
}


void mainLoop(){
  
  SDL_Rect screenRect;
  bool quit = false;
  bool grounded = false;
  float xdir = 0, ydir = 0;
  Physics physics = Physics(100);
  int startTime = 0;
  int framecount = 0;
  int animationTime = 0;
  GUISlider gs = GUISlider(loadTexture("test.bmp"), loadTexture("snow.bmp"), new Transform(10,10,100,100), 100, 50);
  
  std::vector<GUIContainer> gui;
  GUIContainer temp;
  temp.item = &gs;
  temp.itemType = SLIDER;
  gui.push_back(temp);
  
  screenRect.x=0;
  screenRect.y=0;
  screenRect.w = SCREEN_WIDTH;
  screenRect.h = SCREEN_HEIGHT;
  
  Entity player = Entity(new Transform(90,90,20,20), new Sprite("spriteTest.bmp",10,10),new PhysicsBody());
  player.transform.constrain(screenRect);
  
  physics.add(&player.pBody);

  Level l = Level();
  l.tiles.push_back(Tile(new Transform(0,SCREEN_HEIGHT-100,100,100), new Sprite("test.bmp",100,100)));
  l.tiles.push_back(Tile(new Transform(100,SCREEN_HEIGHT-100,100,100), new Sprite("test.bmp",100,100)));
  l.tiles.push_back(Tile(new Transform(200,SCREEN_HEIGHT-100,100,100), new Sprite("test.bmp",100,100)));
  l.tiles[1].nextFrame();
  l.tiles[2].nextFrame();
  l.tiles[2].nextFrame();
  l.warps.push_back(Warp(new Transform(SCREEN_WIDTH/2, SCREEN_HEIGHT,20,20), 1, SCREEN_WIDTH/2, 0));
  SDL_SetRenderDrawColor(windowRenderer, 0, 0, 0, 0);

  Level l2 = Level();
  l2.warps.push_back(Warp(new Transform(SCREEN_WIDTH/2, SCREEN_HEIGHT,20,20), 0, SCREEN_WIDTH/2, 0));
  
  Level *currLevel = &l;
  
  Level *levels[2];
  levels[0] = &l;
  levels[1] = &l2;
  
  while(!quit){
    
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
			  xdir=-1;
			}
			else if(e.jaxis.value>8000){
			  xdir=1;
			}
			else{
			  xdir=0;
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
		}
		else if(e.key.keysym.sym == SDLK_d){
		  xdir = 1;
		}
	  }
	  else if(e.type == SDL_KEYUP){
		if(e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_d){
		  xdir = 0;
		}
	  }
    }
    
    startTime = SDL_GetTicks();
    
    //Render
    SDL_RenderClear(windowRenderer);

    gui[0].render(windowRenderer);

    player.render(windowRenderer);
    (*currLevel).render(windowRenderer);
    
    SDL_RenderPresent(windowRenderer);

    if(SDL_GetTicks()-startTime < 1000.f/FRAME_RATE){
      SDL_Delay(1000.f/FRAME_RATE-(SDL_GetTicks()-startTime));
    }
    
    animationTime+=SDL_GetTicks()-startTime;

	physics.update((SDL_GetTicks()-startTime)/1000.f);

	player.pBody.update((SDL_GetTicks()-startTime)/1000.f);
	
    if((*currLevel).collides(&(player.transform))){
      player.pBody.vely = 0;
      player.pBody.grounded = true;
    }
	else{
	  player.pBody.grounded = false;
	}
	
    if(animationTime>1000.f/ANIMATION_RATE){
      player.sprite.nextFrame();
      (*currLevel).update();
      animationTime-=1000.f/ANIMATION_RATE;
	  gs.value++;
    }

    player.transform.move(xdir,0);

	if((*currLevel).checkWarp(&(player.transform))>=0){
	  int index = (*currLevel).checkWarp(&(player.transform));
	  player.transform.setPosition((*currLevel).warps[index].x, (*currLevel).warps[index].y);
	  currLevel = levels[(*currLevel).warps[index].dest_level];
	}
	
    std::clog<<framecount/(SDL_GetTicks()/1000.f)<<std::endl;
    framecount++;

  }

}

