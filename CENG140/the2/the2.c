#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void swap(char **str1,char **str2){
    char *temp=*str1;
    *str1=*str2;
    *str2=temp;
    return;
}

int odd(int i){return i%2;}

void stringcopy(char *p1,char *p2){     
    while(*p2){
        *p1=*p2;
        p2++;
        p1++;
    }
    *p1=*p2;
    return;
}

void stringmove(char *p1,char *p2){     
    char *p3=malloc((strlen(p2)+1)*sizeof(char));
    stringcopy(p3,p2);
    stringcopy(p1,p3);
    free(p3);
    return;
}

void formula_count(char *it,int *left_or_right){
    int i=1;
    if(*it=='#')
        i=0;
    else{
	    while(*it!='#'){
	        if(*it==',')
	            i++;
	        it++;
	    }
    }
    left_or_right[0]=i;
    i=1;
    it++;
    if(*it==0)
        i=0;
    else{
	    while(*it!=0){
	        if(*it==',')
	            i++;
	        it++;
	    }
    }
    left_or_right[1]=i;
    return;
}

void open_space0(char *p,char ***arr){
    int i=0,j=1;
    while(*p!='#'){
        if(*p==','){
            *(*arr+i)=malloc(j*sizeof(char));
            i++;
            j=1;
        }
        else j++;
        p++;
    }
    *(*arr+i)=malloc(j*sizeof(char));
    
    arr++,i=0,j=1,p++;
    while(*p!=0){
        if(*p==','){
            *(*arr+i)=malloc(j*sizeof(char));
            i++;
            j=1;
        }
        else j++;
        p++;
    }
    *(*arr+i)=malloc(j*sizeof(char));

    return;
}

void use_space0(char *p,char ***arr){
    int i=0,j=0;
    while(*p!='#'){
        if(*p==','){
            *(*(*arr+i)+j)=0;
            i++;
            j=0;
        }
        else{
            *(*(*arr+i)+j)=*p;
            j++;
        }
        p++;
    }
    p++,arr++,i=0,j=0;
    while(*p!=0){
        if(*p==','){
            *(*(*arr+i)+j)=0;
            i++;
            j=0;
        }
        else{
            *(*(*arr+i)+j)=*p;
            j++;
        }
        p++;
    }
    
    return;
}

int R5(char *str){
    int parantez=0;
    char *p=str;
    if(*str!='(')
        return 0;
    while(*p){
        switch(*p){
            case '(':parantez++;break;
            case ')':parantez--;break;
            case '>':
            if(parantez==1){
               *p='|';
               str=realloc(str,(strlen(str)+1)*sizeof(char));
               stringmove(str+2,str+1);
               *(str+1)='-';
               return 1;
            }
            break;
            default:break;
        }
        p++;
    }    
    return 0;
}

int R2(char *str,int i,char ***arr,int *left_or_right){
    char x,*p=str,*p0;
    int parantez=0;
    if(*str!='(')
        return 0;
    switch(i){
        case 0:x='&';break;
        case 1:x='|';break;
        default:break;
    }
    while(*p){
        switch(*p){
            case '(':parantez++;break;
            case ')':parantez--;break;
            case '&':
            case '|':
            case '>':
            if(*p!=x){
                break;
            }
            if(parantez==1){
                arr[i]=realloc(arr[i],(left_or_right[i]+1)*sizeof(char*));
                *p=0;
                p0=p+1;
                p0[strlen(p0)-1]=0;
                arr[i][left_or_right[i]]=malloc((strlen(p0)+1)*sizeof(char));
                stringmove(arr[i][left_or_right[i]],p0);
                stringmove(str,str+1);
                str=realloc(str,(strlen(str)+1)*sizeof(char));
                left_or_right[i]++;
                return 1;
            }
            break;
            default:break;
        }
        p++;
    }
    return 0;
}



int R67(char ***arr,int *left_or_right){
    int i,j;
    for(i=0;i<left_or_right[0];i++){
        for(j=0;j<left_or_right[1];j++){
            if(!strcmp(arr[0][i],arr[1][j])){
                return 1;
            }
        }
    }
    return 0;
}

int R1(char ***arr,int *left_or_right){
    int i,j,res=0;
    for(i=0;i<2;i++){
        for(j=0;j<left_or_right[i];j++){
            if(arr[i][j][0]=='-'){
                int minus_count=0;
                char *p=arr[i][j];
                res=1;
                while(*p=='-'){
                    minus_count++;
                    p++;
                }
                stringcopy(arr[i][j],p);
                arr[i][j]=realloc(arr[i][j],sizeof(char)*(strlen(arr[i][j])+1));
                
                if(odd(minus_count)){
                    arr[!i]=realloc(arr[!i],sizeof(char*)*(left_or_right[!i]+1));
                    swap(&arr[i][j],&arr[!i][left_or_right[!i]]);
                    swap(&arr[i][j],&arr[i][left_or_right[i]-1]);
                    arr[i]=realloc(arr[i],sizeof(char*)*(left_or_right[i]-1));
                    left_or_right[!i]++;
                    left_or_right[i]--;
                    j--;
                }
            }
        }
    }
    return res;
}





int R_func(char ***arr,int which,int *left_or_right){
    int i,j,res=0;
    for(i=0;i<2;i++){
        for(j=0;j<left_or_right[i];j++)
            switch(which){
                case 5:
                res=R5(arr[i][j])||res;
                break;
                case 2:
                res=R2(arr[i][j],i,arr,left_or_right)||res;
                break;
                default:
                printf("not written yet\n");
                return 0;
            }
            
    }
    return res;
}

int all_letter(char ***arr,int *left_or_right){
    int i,j;
    for(i=0;i<2;i++){
        for(j=0;j<left_or_right[i];j++){
            if(arr[i][j][1]!=0){
                return 0;
            }
        }
    }
    return 1;
}
void arraycopy(char ***arr,int *left_or_right,char ***arr2,int *left_or_right2){
    int i,j;
    left_or_right2[0]=left_or_right[0];
    left_or_right2[1]=left_or_right[1];
    for(i=0;i<2;i++){
        arr2[i]=malloc(left_or_right2[i]*sizeof(char*));
    }
    for(i=0;i<2;i++){
        for(j=0;j<left_or_right2[i];j++){
         arr2[i][j]=malloc((1+strlen(arr[i][j]))*sizeof(char));
         stringcopy(arr2[i][j],arr[i][j]);
        }
    }
    return;
}

void free_array(char ***arr,int *left_or_right){
    int i,j;
    for(i=0;i<2;i++){
        for(j=0;j<left_or_right[i];j++){
            free(arr[i][j]);
        }
    }
    free(arr[0]);
    free(arr[1]);
    return;
}

char *check(char *str,int i){
    int parantez=0;
    char x,*p=str;
    if(str[0]!='(')
        return NULL;
    switch(i){
        case 0:x='|';break;
        case 1:x='&';break;
        default:break;
    }
    while(*p){
        switch(*p){
            case '(':parantez++;break;
            case ')':parantez--;break;
            case '&':
            case '|':
            case '>':
            if(*p!=x){
                break;
            }
            if(parantez==1){
                return p;
            }
            break;
            default:break;
        }
        p++;
    }
    return NULL;
}

int recursive_solution(char ***arr,int *left_or_right){
    int j,i=1,res,*left_or_right2,flag=0;
    char ***arr2,*temp,*p;
    while(i){
        i=R1(arr,left_or_right);
        i=R_func(arr,5,left_or_right)||i;
        i=R_func(arr,2,left_or_right)||i;
    }
    
    if(all_letter(arr,left_or_right)){
        return R67(arr,left_or_right);
    }
    else{
        left_or_right2=malloc(2*sizeof(int));
        arr2=malloc(2*sizeof(char**));
        arraycopy(arr,left_or_right,arr2,left_or_right2);
        for(i=0;i<2;i++){
            for(j=0;j<left_or_right2[i];j++){
                p=check(arr2[i][j],i);
                if(p){
                    temp=malloc(sizeof(char)*strlen(p+1));
                    p[strlen(p)-1]=0;
                    stringcopy(temp,p+1);
                    *p=0;
                    stringmove(arr2[i][j],arr2[i][j]+1);
                    arr2[i][j]=realloc(arr2[i][j],sizeof(char)*(1+strlen(arr[i][j])));
                    
                    flag=1;
                    break;
                }
            }
            if(flag)
                break;
        }
        res=recursive_solution(arr2,left_or_right2);
        free_array(arr2,left_or_right2);
        arraycopy(arr,left_or_right,arr2,left_or_right2);
        swap(&arr2[i][j],&temp);
        free(temp);
        res=res&&recursive_solution(arr2,left_or_right2);
        free_array(arr2,left_or_right2);
        free(arr2);
        free(left_or_right2);
    }
    return res;
}



int main(void)
{
    int result,*left_or_right=malloc(2*sizeof(int));  
    char *p=malloc(201*sizeof(char)),***arr=malloc(2*sizeof(char**)),resultchar;
    gets(p);
    formula_count(p,left_or_right);
    *arr=malloc(left_or_right[0]*sizeof(char*));
    *(arr+1)=malloc(left_or_right[1]*sizeof(char*));
    open_space0(p,arr);
    use_space0(p,arr);
    free(p);
    result=recursive_solution(arr,left_or_right);
    switch(result){
        case 0:resultchar='F';break;
        case 1:resultchar='T';break;
        default:break;
    }
    
    printf("%c",resultchar);
    free_array(arr,left_or_right);
    free(arr);
    free(left_or_right);

    return 0;
}