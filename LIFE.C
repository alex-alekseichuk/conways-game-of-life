#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<bios.h>
#include<mem.h>
#include<dos.h>

struct Textel {char c;char a;};
struct Textel far *Screen=(struct Textel far *)0xb8000000L;


int k;
char x,y,xmax=39,ymax=24;
char a[40][25];
char off[8][2]={{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0}};

char aa(char x,char y);
void aaa(char x,char y,char t);
void dolife(void);

void main(void){
unsigned char i,j;
textcolor(WHITE);textbackground(BLUE);
clrscr();
puts("   -------------    LIFE   ------------\r\n");
puts("   Space  - On/Off");
puts("   Enter  - Step");
puts("   F3     - Random Fill");
puts("   F2     - Clear");
puts("   F5     - Run");
puts("   F6     - Stop");
puts("   Arrows - Move");
puts("   Esc    - Exit\r\n");
puts("Pres Any Key ...");
getch();
clrscr();setmem(&a,1000,0);
x=xmax/2;y=ymax/2;gotoxy(2*x+1,y+1);
for(;;){k=bioskey(0);
switch (k) {
  case 15616 : /*  F3 - Random Fill */
      for(i=2;i<38;i++) for(j=2;j<23;j++)
	{gotoxy(i*2+1,j+1);
	 if((a[i][j]=(char)random(2))) printf("°°"); else printf("  ");
	}gotoxy(x*2+1,y+1);break;
  case 15360 : /*  F2 - Clear  */
      clrscr();x=xmax/2;y=ymax/2;gotoxy(2*x+1,y+1);setmem(&a,1000,0);break;
  case 283   : /*   Exit  */
      textcolor(7);textbackground(0);clrscr();exit(0);
  case 19712 : /*  Right  */
      if(x==xmax) x=0; else x++;gotoxy(2*x+1,y+1);break;
  case 19200 : /*  Left   */
      if(!x) x=xmax; else x--;gotoxy(2*x+1,y+1);break;
  case 18432 : /*  Up     */
      if(!y) y=ymax; else y--;gotoxy(2*x+1,y+1);break;
  case 20480 : /*  Down   */
      if(y==ymax) y=0; else y++;gotoxy(2*x+1,y+1);break;
  case 14624 : /*  Space  */
      if(a[x][y]) {a[x][y]=0;printf("  ");gotoxy(x*2+1,y+1);}
      else {a[x][y]=1;printf("°°");gotoxy(x*2+1,y+1);}break;
  case 7181 : /*  Enter - Step  */
     dolife();gotoxy(x*2+1,y+1);break;
  case 16128 : /*  F5 - Run  */
     do{dolife();

	delay(300);  /*  <<---------  This is very Interesting place */

       }while(!kbhit());gotoxy(x*2+1,y+1);
}}}


char aa(char x,char y)
{if(x<0||x>xmax||y<0||y>ymax) return(0); else return(a[x][y]);}

void aaa(char x,char y,char t)
{if(!(x<0||x>xmax||y<0||y>ymax)) a[x][y]=t; return;}


void dolife(void)
     { char x,y,h,g;
      for(x=0;x<xmax;x++)
	for(y=0;y<ymax;y++)
	  if(a[x][y]) {char co=0,co2;
	     for(h=0;h<8;h++) { co2=aa(x+off[h][0],y+off[h][1]);
	       if(co2==1||co2==2) co++;
	       else {char co3=0,co4;
		     for(g=0;g<8;g++)
			if((co4=aa(x+off[h][0]+off[g][0],
				 y+off[h][1]+off[g][1]))==1||co4==2) co3++;
		     if(co3==3) aaa(x+off[h][0],y+off[h][1],3);}}
	     if(co<2||co>3) a[x][y]=2;}
      for(x=0;x<xmax;x++)
	for(y=0;y<ymax;y++)
	   switch (a[x][y]) {
	       case 2 : a[x][y]=0;gotoxy(x*2+1,y+1);printf("  ");break;
	       case 3 : a[x][y]=1;gotoxy(x*2+1,y+1);printf("°°");
	   }
     return;}


/*    Something  very  interesting :

	     ##         ######### - N
   ###        ##
	     #       ##
##		      ##
##	##	     ##
       #  #
	##
*/