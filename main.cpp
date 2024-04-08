#include "LTexture.h"
#include "main.h"
bool init()
{
	// flag
	bool success = true;

	// SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		success = false;
	}
	else
	{
		//set texture
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			std::cout << "Warming.."<<std::endl;
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				success = false;
			}
			else
			{

				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{

					success = false;
				}

				//mixer :
				if( Mix_OpenAudio( 48000, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					success = false;
				}
			}
		}
	}
    //TTF
    if(TTF_Init() == -1 )
    {
        success = false ;
    }
    gfont = TTF_OpenFont("Anta-Regular.ttf",28) ; //duong dan dem file .ttf
    if(gfont == NULL)
    {
        success = false ;
    }
	return success;
}

//ham load
bool loadMedia()
{
	bool success = true;

	for(int i=0;i < sovatcantoida ; i++)
    {
        if( !barrier[i].loadFromFile(gRenderer,"barrier.png") )
        {
            success=false;
        }
    }
    for(int i= sovatcantoida;i < sovatcantoida2;i++)
    {
        if(!barrier[i].loadFromFile(gRenderer,"barrier2.png"))
        {
           success = false ;
        }
    }
	if( !gFooTexture.loadFromFile(gRenderer, "plane_fly.png" ) )
	{

		success = false;
	}

    if(!gBackgroundTexture.loadFromFile(gRenderer,"55033334-forest-game-background-background-2d-game-application-vector-design-tileable-horizontally-size.jpg"))
    {
        success = false ;
    }
    //load music
    sound = Mix_LoadMUS( "8bit-music-for-game-68698.mp3");
    if( sound == NULL )
	{
		success = false;
	}

	return success;
}

//ham dong
void close()
{
	for(int i=0;i<sovatcantoida2;i++)
        barrier[i].free() ;
	gFooTexture.free();
	gBackgroundTexture.free();
	//homepage.free();
    heathy2.free();

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

    //ttf
    TTF_CloseFont(gfont);
	//close music
    Mix_FreeMusic(sound);

    Mix_CloseAudio();

	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
	TTF_Quit();
}

void khoitao()
{
 for(int i = 0; i < sovatcantoida2; i++)
  {
    barrierPositionsy[i] = 0;
    barrierPositionsx[i] = randomimage(50,1177);
  }
}
int bestScore() {
    std::ifstream doc("Best score.txt");
    if (doc.is_open()) {
        int n;
        doc >> n;
        doc.close();
        return n;
    }
    return -1;
}
void khoitaoBestScore(int n, int m) {
    int high = std::max(n, m); // Sử dụng hàm max từ thư viện algorithm
    std::ofstream ghi("Best score.txt"); // Mở tệp để ghi
    if (ghi.is_open()) {
        ghi << high;
        ghi.close();
    }
}
//ham khoi tao text : mau den
void rendertext(const std::string &s ,int x ,int y )
{
     SDL_Color textColor = {0, 0, 0};
     SDL_Surface* textSurface = TTF_RenderText_Solid(gfont, s.c_str(), textColor);
     if(textSurface == NULL)
     {
         std :: cout<< "Warming: " <<std::endl;  return;
     }
     else
     {
         SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (texture == NULL)
        {
           std::cout<< "Warming: "<< SDL_GetError(); return;
        }
        else
        {
            SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
            SDL_RenderCopy(gRenderer, texture, NULL, &renderQuad);
            SDL_DestroyTexture(texture);
        }
        SDL_FreeSurface(textSurface);
     }
}
//chu mau do
void rendertext2(const std::string &s ,int x ,int y)
{
    SDL_Color textColor = {255, 0, 0};
     SDL_Surface* textSurface = TTF_RenderText_Solid(gfont, s.c_str(), textColor);
     if(textSurface == NULL)
     {
         std :: cout<< "Warming" << TTF_GetError()<<std::endl;
          return;
     }
     else
     {
         SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (texture == NULL)
        {
           std::cout<< "Warming: "<< SDL_GetError();
            return;
        }
        else
        {
            SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
            SDL_RenderCopy(gRenderer, texture, NULL, &renderQuad);
            SDL_DestroyTexture(texture);
        }
        SDL_FreeSurface(textSurface);
     }
}
void resetGame() {
    gFooTexture.free();
    // Xóa các vật thể rơi xuống
    for(int i = 0; i < sovatcantoida2; ++i) {
        barrier[i].free();
    }

    // Xóa các trái tim cũ
    for(int i = 0; i < YourHeath; ++i) {
        heathy[i].free();
    }

    heathy2.free();
    if (!gFooTexture.loadFromFile(gRenderer, "plane_fly.png")) {

        return;
    }
    for(int i = 0; i < Max_heath; ++i) {
        if (!heathy[i].loadFromFile(gRenderer, "traitim.png")) {

            return;
        }

        heathy[i].render(gRenderer,i * 30, 0);
    }
    //tao lai chuong trinh
    YourHeath = Max_heath;
    vatdai = 125;
    vatrong = 400;
    speed = 0.05;
    // Khởi tạo lại số lượng vật thể rơi xuống
    n = Max_heath;
     //Khởi tạo lại vị trí của các vật thể rơi xuống
    for(int i = 0; i <sovatcantoida ; ++i) {
            if(!barrier[i].loadFromFile(gRenderer,"barrier.png"))
            {
                return ;
            }
    }
    for(int i = sovatcantoida ; i < sovatcantoida2  ;i++)
    {
        if(!barrier[i].loadFromFile(gRenderer,"barrier2.png"))
        {
            return ;
        }
    }
    khoitao();
}

void Menu(bool &quit)
{
    gBackgroundTexture.render(gRenderer,0,0);
    rendertext("BEST SCORE : " +std::to_string(bestScore()) , SCREEN_WIDTH/2 + 275 , SCREEN_HEIGHT/2 -150 );
    rendertext("PLAY" , SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50);
    rendertext("QUIT" , SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 50);

    SDL_RenderPresent(gRenderer);
    bool isclick = false ;

    while(!isclick)
    {
        SDL_Event e ;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                quit = false ;
                isclick = true ;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX > SCREEN_WIDTH / 2 - 100 && mouseX < SCREEN_WIDTH / 2 + 100 &&
                    mouseY > SCREEN_HEIGHT / 2 - 50 && mouseY < SCREEN_HEIGHT / 2)
                {
                    //doi mau chu
                    rendertext2("PLAY" , SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50);
                    gBackgroundTexture.free();
                    if(!gBackgroundTexture.loadFromFile(gRenderer,"abcd.jpg"))
                    {
                        return ;
                    }
                    SDL_RenderPresent(gRenderer);
                    //tao do tre
                    SDL_Delay(500);
                    isclick = true;
                    resetGame();
                }
                if( mouseY > SCREEN_HEIGHT / 2 + 50 && mouseY < SCREEN_HEIGHT / 2 + 100)
                {
                    //doi mau chu
                    //rendertext2("QUIT" , SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 50);
                    isclick = true;
                    // Thoát chương trình
                    quit = false ;
                }
        }
    }
    }
}

void hieuungno(bool &quit,double &speed)
{
    rendertext("Score : "+std::to_string((SDL_GetTicks()-dem)/100),SCREEN_WIDTH / 2 - 100,SCREEN_HEIGHT / 2 - 150);
    dem =SDL_GetTicks();
    int tmp = bestScore();
    khoitaoBestScore( tmp ,(SDL_GetTicks()-dem)/100);
    rendertext("BEST SCORE : "+std::to_string(bestScore()), SCREEN_WIDTH / 2 + 275 , SCREEN_HEIGHT / 2 - 250);
    rendertext("Play Again" , SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50);
    rendertext("Quit" , SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 50);

    SDL_RenderPresent(gRenderer);
    bool isclick = false ;
    while(!isclick)
    {
        SDL_Event e ;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                quit = true ;
                isclick = true ;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX > SCREEN_WIDTH / 2 - 100 && mouseX < SCREEN_WIDTH / 2 + 100 &&
                    mouseY > SCREEN_HEIGHT / 2 - 50 && mouseY < SCREEN_HEIGHT / 2)
                {
                    //doi mau chu
                    rendertext2("Play Again" , SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50);
                    SDL_RenderPresent(gRenderer);
                    //tao do tre
                    SDL_Delay(500);

                    isclick = true;
                    resetGame();
                }
                if( mouseY > SCREEN_HEIGHT / 2 + 50 && mouseY < SCREEN_HEIGHT / 2 + 100)
                {
                    //doi mau chu
                    isclick = true;
                    quit = true;
                    // Thoát chương trình
                }
            }
        }
    }
}

double  randomimage(int a,int b)
{
    return rand()%(b-imagewith)+a;
}
double randomDouble(double min1, double max1){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min1, max1);

    return dis(gen);
}
//ham kiem tra va cham
bool checkCollision(SDL_Rect a, SDL_Rect b)
{
    // rect của a
    int leftA = a.x;
    int rightA = a.x + a.w;
    int topA = a.y;
    int bottomA = a.y + a.h;

    //rect cua b
    int leftB = b.x;
    int rightB = b.x + b.w;
    int topB = b.y;
    int bottomB = b.y + b.h;

    //co  va cham neu :
    if (bottomA <= topB) return false;
    if (topA >= bottomB) return false;
    if (rightA <= leftB) return false;
    if (leftA >= rightB) return false;

    // day la khi khong va cham
    return true;
}

int main( int argc, char* args[] )
{

	if( !init() )
	{
		return 0;
	}
	else
	{
		if( !loadMedia() )
		{
			return 0;
		}
		else
		{
		    bool kt = true ;
		    Menu(kt);
		    if(kt)
            {
            //tao gia tri cho x va y cua vat
            khoitao();
			// flag
			bool quit = false;
			//Event
			SDL_Event e;
			//nhac
            Mix_PlayMusic(sound,-1);
            //tao vi tri cho cho vat dau tien .
            for(int i=0;i<n;i++)
            {
                barrierPositionsx[i]=randomimage(0,SCREEN_WIDTH);
            }
            //khoi tao trai tim
		    for(int i=0;i<YourHeath;i++)
            {
                if( !heathy[i].loadFromFile(gRenderer ,"traitim.png"))
                {
                 quit = true;
                }
            }
            //tao vong lap vo han
            while( !quit )
			{
			   // bat su kien:
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					else if(e.type==SDL_KEYDOWN)
                    {
                        switch(e.key.keysym.sym)
                        {
                        case SDLK_UP : case SDLK_w :
                            vatrong -= MOVE_SPEED;
                            if(vatrong < 0 ) vatrong = 0;
                            break;

                        case SDLK_DOWN : case SDLK_s :
                             vatrong += MOVE_SPEED;
                            if(vatrong + chieurong >= SCREEN_HEIGHT) vatrong = SCREEN_HEIGHT-chieurong;
                             break;

                        case SDLK_RIGHT : case SDLK_d :
                            vatdai += MOVE_SPEED;
                            if(vatdai + chieudai > SCREEN_WIDTH) vatdai = SCREEN_WIDTH-chieudai;
                            break;

                        case SDLK_LEFT : case SDLK_a :
                            vatdai -= MOVE_SPEED;
                            if(vatdai < 0) vatdai = 0;
                            break;
                        default :
                            break;

                         }
                     }
				  }
				// tao lai mau tren cua so
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//background
				gBackgroundTexture.render(gRenderer, 0, 0 );
				//
				SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

				//vi tri cua main:
				gFooTexture.render(gRenderer, vatdai, vatrong );
				//Update :
                for(int i=0;i  <  YourHeath;  i++ )
                 {
                    heathy[i].render(gRenderer,i*chieurongheathy,0);
                 }
                rect1={vatdai,vatrong,chieudai,chieurong};
                //ham tao do roi cho vat .
				for(int i=0;i<n;i++)
                {
                  barrierPositionsy[i]+=  randomDouble(speed , 1.02*speed);
                  if(barrierPositionsy[i]>SCREEN_HEIGHT-chieurongimage)
                  {
                      barrierPositionsy[i] = randomimage(0,75);
                      barrierPositionsx[i] = randomimage(14,SCREEN_WIDTH-chieurongimage);

                      if(n < sovatcantoida2)
                      {
                          n++ ;
                      }
                      else
                      {
                          n = sovatcantoida2;
                          speed += 0.0008 ;
                         if(speed > max_speed)
                          {
                              speed = max_speed ;
                          }
                      }
                      SDL_RenderPresent(gRenderer);
                  }
                  //tao rect cho vat
                  rect2 = {barrierPositionsx[i],barrierPositionsy[i],imagewith,chieurongimage};
                  //kiem tra va cham va thoi gian truoc khi va cham tiep theo...
                  if( (SDL_GetTicks() - lastCollisionTime > COOLDOWN_TIME ) && checkCollision(rect1,rect2))
                  {
                    // thay doi thoi gian
                     lastCollisionTime =SDL_GetTicks();
                     if(YourHeath > 0)
                      {
                        heathy[YourHeath-1].free();
                        YourHeath--;

                      }
                     else
                      {
                         hieuungno(quit,speed);
                      }
                  }
                   else if(lastCollisionTime != 0 &&  SDL_GetTicks()-lastCollisionTime <= COOLDOWN_TIME )
                    {
                      //thoi gian :
                      Uint32 elapsedTime = SDL_GetTicks()-lastCollisionTime ;
                      //giam mau cua vat khi va cham .
                      gFooTexture.giammau((Uint8)((float)elapsedTime/COOLDOWN_TIME*255));
                      //tao hieu ung bien mat trai tim
                      if(!heathy2.loadFromFile(gRenderer,"traitim2.png"))
                         {
                           return 0;
                         }
                       //load hinh anh trai tim trang
                       heathy2.render(gRenderer,YourHeath*chieurongheathy,0);
                       heathy2.free();
                    }
                 barrier[i].render(gRenderer,barrierPositionsx[i],barrierPositionsy[i]);
              }
                SDL_RenderPresent(gRenderer);
			}
         }
      }
	}
	close();
	return 0;
}
