/*#include  "loop.h"*/
#include  <stdio.h>
int row=0,name[256],first[256],last[256],inc[256],current[256];
char nnumber[256];
void loop_execute(void);
void loopster(int row1,int count);
 
int loop_variable_value(char x){
    return current[name[x]];
   
    
    
}
void loop_continue(char x){
    int i,j,flag=1;


    for(i=name[x];i>=0;i--){
        if(inc[i]>0){
            if(last[i]>=current[i]+inc[i]){
                current[i]+=inc[i];
                break;
            }
            else{
                if(i)
                current[i]=first[i];
                else{
                    for(j=0;j<row;j++)
                    current[j]=last[j];
                    flag=0;
                }
            }
        }
        else{
            if(last[i]<=current[i]+inc[i]){
                current[i]+=inc[i];
                break;
            }
            else{
                if(i)
                current[i]=first[i];
                else{
                    for(j=0;j<row;j++)
                    current[j]=last[j];
                    flag=0;
            }
        }
    }
}

    if(flag){
    for(i=name[x]+1;i<=row-1;i++){
        current[i]=first[i];
    }
   
    current[row-1]-=inc[row-1];
    }
   
}
 
 
 
 
 
 

int main()
{
    char x='\n';
    while(x!=EOF){
        scanf("%c %d %d %d",&nnumber[row],&first[row],&last[row],&inc[row]);
        x=getchar();
        name[nnumber[row]]=row;
        row++;
    }
   if(first[row-1]==0&&last[row-1]==0&&inc[row-1]==0)
   row--;
	
   
    loopster(row,0);
    
    
    
    
    return 0;
}



 
void loopster(int row1,int count){
    if(inc[count]>0){
        if(row1==1){
            for(current[count]=first[count];current[count]<=last[count];current[count]+=inc[count]){
                loop_execute();
        }
        }
        else{
            for(current[count]=first[count];current[count]<=last[count];current[count]+=inc[count]){
                loopster(row1-1,count+1);
            }
        }
    }
    else{
        if(row1==1){
            for(current[count]=first[count];current[count]>=last[count];current[count]+=inc[count]){
                loop_execute();
        }
        }
        else{
            for(current[count]=first[count];current[count]>=last[count];current[count]+=inc[count]){
                loopster(row1-1,count+1);
            }
        }
    }
}





/*void loop_execute(void)
{
printf("X:%d r:%d Y:%d\n",
loop_variable_value('X'),
loop_variable_value('r'),
loop_variable_value('Y'));
if ((loop_variable_value('X')+loop_variable_value('r')+loop_variable_value('Y')) % 5 == 0)
{ printf("JUST MAGIC OF FIVE HAPPENED!...Continuing with next ’r’ value.\n");
loop_continue('r'); }
}*/


void loop_execute(void)
{
printf("a:%d X:%d r:%d Y:%d z:%d\n",loop_variable_value('a'),
loop_variable_value('X'),
loop_variable_value('r'),
loop_variable_value('Y'),loop_variable_value('z'));
if ((loop_variable_value('X')+loop_variable_value('r')+loop_variable_value('Y')+loop_variable_value('z')+loop_variable_value('a')) % 5 == 0)
{ printf("JUST MAGIC OF FIVE HAPPENED!...Continuing with next ’r’ value.\n");
loop_continue('r'); }
}




/*
a 0 3 1
X 10 18 3
r -3 2 1
Y -1 -3 1
z 1 8 5
*/


