#include <gb/gb.h>
#include <gb/console.h>
#include <stdio.h>
#include <string.h>

#define Y_LOW 0
#define Y_HIGH 144
#define X_LOW 0
#define X_HIGH 160

#define BIRD_Y_LOW Y_LOW + 16
#define BIRD_Y_HIGH Y_HIGH - 0
#define BIRD_X_LOW X_LOW + 8
#define BIRD_X_HIGH X_HIGH - 8


void flap(long * flip);
void out();
int bounds(int x,char s, int i, int j);
void multi(int times,int * x,int * y);
void down(int*x,int*y);
void up(int*x,int*y);
void right(int*x,int*y);
void left(int*x,int*y);
void a(int x, int y);
void a_rel();



unsigned char bird[] =
{
  0x00,0x00,0x03,0x03,0x07,0x04,0x0F,0x08,
  0x1F,0x10,0x1E,0x10,0x1E,0x10,0x1B,0x14,
  0x23,0x3E,0x32,0x3F,0x52,0x7F,0x8A,0xFF,
  0x9F,0xFF,0xA1,0xE1,0x43,0x43,0x00,0x00,
  0x00,0x00,0x80,0x80,0xE0,0x60,0xF0,0x10,
  0x7C,0x0C,0xF2,0xC2,0xD2,0xC2,0x3A,0x0A,
  0xF6,0x06,0xFA,0x0A,0x14,0xF4,0x20,0xE0,
  0xC0,0xC0,0x00,0x00,0xC0,0xC0,0x00,0x00,
  0x00,0x00,0x03,0x03,0x07,0x04,0x0F,0x08,
  0x1F,0x10,0x1E,0x10,0x2E,0x38,0x27,0x3C,
  0x23,0x3E,0x20,0x3F,0x40,0x7F,0x80,0xFF,
  0x9F,0xFF,0xA1,0xE1,0x43,0x43,0x00,0x00,
  0x00,0x00,0x80,0x80,0xE0,0x60,0xF0,0x10,
  0x7C,0x0C,0xF2,0xC2,0xD2,0xC2,0x3A,0x0A,
  0xF6,0x06,0xFA,0x0A,0x14,0xF4,0x20,0xE0,
  0xC0,0xC0,0x00,0x00,0xC0,0xC0,0x00,0x00,
  0x00,0x00,0x03,0x03,0x07,0x04,0x0F,0x08,
  0x1F,0x10,0x1E,0x10,0x2E,0x38,0x27,0x3C,
  0x23,0x3E,0x20,0x3F,0x40,0x7F,0x80,0xFF,
  0x9F,0xFF,0xA1,0xE1,0x43,0x43,0x00,0x00,
  0x00,0x00,0x80,0x80,0xE0,0x60,0xF0,0x10,
  0x7E,0x0E,0xF1,0xC1,0xD5,0xC5,0x3A,0x0A,
  0xF8,0x08,0xF4,0x04,0x1A,0xFA,0x26,0xE6,
  0xC0,0xC0,0x00,0x00,0xC0,0xC0,0x00,0x00,
  0x00,0x00,0x43,0x43,0xA1,0xE1,0x9F,0xFF,
  0x80,0xFF,0x40,0x7F,0x20,0x3F,0x21,0x3E,
  0x22,0x3E,0x2D,0x31,0x1D,0x11,0x1E,0x12,
  0x0F,0x08,0x07,0x04,0x03,0x03,0x00,0x00,
  0x00,0x00,0xC0,0xC0,0x00,0x00,0xC0,0xC0,
  0x20,0xE0,0x14,0xF4,0xFA,0x0A,0xF6,0x06,
  0xFA,0x8A,0x72,0x02,0x72,0x02,0xFC,0x8C,
  0xF0,0x10,0xE0,0x60,0x80,0x80,0x00,0x00
};

unsigned char bullet[] =
{
  0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,
  0x32,0x32,0x4D,0x43,0x79,0x47,0x32,0x3E,
  0x0C,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
UBYTE flip;
int seedshot; 
int maxSeeds = 3;
int seeds;
unsigned int seedx, seedy, seedx2, seedy2, seedx3, seedy3;

void tim();



void main()
{
    //flip1 = 0;
    //long flip = 0;
    int x = 55;
    int y = 75;

    int time = 2;
	//memcpy(&seeds, 0, 1);
	//memcpy(&seedshot, 0, 1);
	//memcpy(&seedx, 171, 1);
	//memcpy(&seedx2, 171, 1);
	//memcpy(&seedx3, 171, 1);
	//printf("%d , %d , %d",seedshot,seeds,seedx);
	//int i;
	//int add(int, int);
	SPRITES_8x16;
    set_sprite_data(0, 16, bird);
	set_sprite_data(16, 2, bullet);
    set_sprite_tile(0,0);
    move_sprite(0,x,y);
    set_sprite_tile(1,2);
    move_sprite(1, x + 8, y);
    SHOW_SPRITES;
	
	

	//TMA_REG = 0x00U;

	
	disable_interrupts();
	add_TIM(tim);
	enable_interrupts();
	set_interrupts(VBL_IFLAG);

	 //WORD i;
	 TMA_REG = 0x11U;
     TAC_REG = 0x04U;
	 set_interrupts(VBL_IFLAG | TIM_IFLAG);
     //i = add(3, 3);
	// printf("%d\n",i);
	 //puts("\n");
while(1){
	//printf("%d\n",seeds);
	//gameloop:
    if(joypad() & J_RIGHT)
    {
        //flap(&flip);
        multi(time,&x,&y);
        right(&x,&y);
    }

    if(joypad() & J_LEFT)
    {
        //flap(&flip);
        multi(time,&x,&y);
        left(&x,&y);
    }
    if(joypad() & J_UP)
    {
        // flap(&flip);
        multi(time,&x,&y);
        up(&x,&y);
    }
    if(joypad() & J_DOWN)
    {
        // flap(&flip);
        multi(time,&x,&y);
        down(&x,&y);
    }
    if(joypad() & J_A)
    {
        // flap(&flip);
        multi(time,&x,&y);
        a(x,y);
    }else{a_rel();}
	//SHOW_SPRITES;
    // flap(&flip);
    //return flip;
    //flip++;
    //flip = flap(flip);
}
}

void tim(){
	if(flip == 8){
        set_sprite_tile(0,4);
        flip = 0;
		
    }
    else if(flip == 4){
		flip++;
        set_sprite_tile(0,0);
    }
	else{flip++;}
	if(seedx <= 170 && seedx != 0){
		//seedshot = 0;
		seedx += 10;
		move_sprite(3,seedx,seedy);
		if(seedx >= 170){seedx=0;}
		//if(seedx == 0){seeds--;}
	}
	if(seedx2 <= 170 && seedx2 != 0){
		//seedshot = 0;
		seedx2 += 10;
		move_sprite(4,seedx2,seedy2);
		if(seedx2 >= 170){seedx2=0;}
	}
	if(seedx3 <= 170 && seedx3 != 0){
		//seedshot = 0;
		seedx3 += 10;
		move_sprite(5,seedx3,seedy3);
		if(seedx3 >= 170){seedx3=0;}
	}
	if(seedshot > 0){seedshot--;}
	if(seedshot < 0){seedshot = 0;}
	//seeds = (seedx != 0) + (seedx2 != 0) + (seedx3 != 0);
}

void out() //horrid beeping noise
{
    NR52_REG = 0x80;
    NR51_REG = 0x11;
    NR50_REG = 0x33;
    NR10_REG = 0x1E;
    NR11_REG = 0x10;
    NR12_REG = 0xF3;
    NR13_REG = 0x00;
    NR14_REG = 0x87;
}
int bounds(int x,char s, int i, int j){

    if(s == '-'){
        if(x == i){
            out();
            return i;
        }
        return x - 1;
    }
    else if(s == '+'){
        if(x == j){
            out();
            return j;
        }
        return x + 1;
    }
    
}

void multi(int times,int * x,int * y){
    times--;
    if(times == 0){
        return;
    }
    if(joypad() & J_UP){
            multi(times,x,y);
			//up(x,y);
            *y = bounds(*y,'-',BIRD_Y_LOW,BIRD_Y_HIGH);
    }
    if(joypad() & J_DOWN){
            multi(times,x,y);
            *y = bounds(*y,'+',BIRD_Y_LOW,BIRD_Y_HIGH);
            //return y;
    }
    if(joypad() & J_RIGHT){
            multi(times,x,y);
            *x = bounds(*x,'+',BIRD_X_LOW,BIRD_X_HIGH);
            //return x;
    }
    if(joypad() & J_LEFT){
            multi(times,x,y);
            *x = bounds(*x,'-',BIRD_X_LOW,BIRD_X_HIGH);
            //return x;
    }
    if(joypad() & J_A){
           multi(times,x,y);
		   a(*x,*y);
}else{a_rel();}
    if(joypad() & J_B){
            multi(times,x,y);
            //TODO
    }
    if(joypad() & J_START){
            multi(times,x,y);
            //TODO
    }
    if(joypad() & J_SELECT){
            multi(times,x,y);
            //TODO
    }
}
void flap(long * flip){
    *flip = *flip + 1;
    if(*flip == 1000){
        set_sprite_tile(0,4);
        *flip = 0;
    }
    else if(*flip == 500){
        set_sprite_tile(0,0);
    }
}
void down(int*x,int*y){
	delay(20);
    *y = bounds(*y,'+',BIRD_Y_LOW,BIRD_Y_HIGH);
    move_sprite(0,*x,*y);
    move_sprite(1, *x + 8, *y);
}
void up(int*x,int*y){
	delay(20);
    *y = bounds(*y,'-',BIRD_Y_LOW,BIRD_Y_HIGH);
    move_sprite(0,*x,*y);
    move_sprite(1, *x + 8, *y);

}
void right(int*x,int*y){
    delay(20);
    *x = bounds(*x,'+',BIRD_X_LOW,BIRD_X_HIGH);
    move_sprite(0,*x,*y);
    move_sprite(1, *x + 8, *y);
    //delay(20);
}

void left(int *x,int *y){
	delay(20);
    *x = bounds(*x,'-',BIRD_X_LOW,BIRD_X_HIGH);
    move_sprite(0,*x,*y);
    move_sprite(1, *x + 8, *y);
    //delay(20);
}
void a(int x,int y){
    set_sprite_tile(1,10);
	if(seedshot == 0){
		if(seedx == 0){
			out();
			seedx = x + 12;
			seedy = y + 2;
			// seeds++;
			set_sprite_tile(3,17);
			move_sprite(3,seedx,seedy);
			seedshot = 6;
		}	
		else if(seedx2 == 0){
			// seeds++;
			out();
			seedx2 = x + 12;
			seedy2 = y + 2;
			seeds++;
			set_sprite_tile(4,17);
			move_sprite(4,seedx2,seedy2);
			seedshot = 6;
		}
		else if(seedx3 == 0){
			// seeds++;
			out();
			seedx3 = x + 12;
			seedy3 = y +2;
			set_sprite_tile(5,17);
			move_sprite(5,seedx3,seedy3);
			seedshot = 6;
		}	
	}
		//printf("%d, %d, %d, %d, %d\n", seedx, seedx2, seedx3, seeds, seedshot);
}
void a_rel(){
	set_sprite_tile(1,2);

}
