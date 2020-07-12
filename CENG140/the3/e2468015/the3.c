#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <float.h>




int precedence(char x){			/*precedence function*/
    switch(x){
        case '+':
        case '-':return 1;
        case '*':
        case '/':return 2;
        case '^':return 3;
        case '~':
        case 's':               /*bigger then / and * */
        case 'c':
        case 'q':
        case 'l':return 4;
        default:break;
    }
    return 0;
}

/*
sin->s
sqrt->q
cos->c
ln->l
any number->z
*/
void postfix(char *formula,double *numbers){                /*function that changes infix operation to a postfix operation*/
    char temp[405],stack[405];
    int i=0,i_f=0,i_s=0,i_num=0;
    strcpy(temp,formula);
    
    while(temp[i]!=0){
        switch(temp[i]){
            case '~':      /*all done*/     /*unary minas*/
            case 's':                       /*sin*/ 
            case 'c':                       /*cos*/ 
            case 'l':                       /*ln*/ 
            case 'q':                       /*sqrt*/ 
            case '+':                       
            case '-':                       /*çıkarma*/ 
            case '*':                       
            case '/':                       
            if(i_s){
                i_s--;
                while(1){           
                    if(precedence(temp[i])>precedence(stack[i_s])){
                        i_s++;
                        break;
                    }
                    formula[i_f]=stack[i_s];
                    i_f++;
                    if(!i_s)break;
                    if(stack[i_s-1]=='(')break;
                    i_s--;
                }
            }
            stack[i_s]=temp[i];
            i_s++;
            break;
            
            case '^':                       /*done*/
            if(i_s){
                i_s--;
                while(1){           
                    if(precedence(temp[i])>=precedence(stack[i_s])){
                        i_s++;
                        break;
                    }
                    formula[i_f]=stack[i_s];
                    i_f++;
                    if(!i_s)break;
                    if(stack[i_s-1]=='(')break;
                    i_s--;
                }
            }
            stack[i_s]=temp[i];
            i_s++;
            break;



            case '(':                       /*done*/
            stack[i_s]='(';
            i_s++;
            break;
            case ')':                       /*done*/
            i_s--;
            while(stack[i_s]!='('){
                formula[i_f]=stack[i_s];
                i_s--;
                i_f++;
            }
            break;
            default:
            if(temp[i]>='A'&&temp[i]<='Z'){             /*letter*/ /*done*/
                formula[i_f]=temp[i];
                i_f++;
            }                        
            else{                                       /*number*/ /*done*/
                formula[i_f]='z';
                i_f++;
                numbers[i_num]=atof(&temp[i]);
                i_num++;
                while((temp[i]<='9'&&temp[i]>='0')||temp[i]=='.'){
                    i++;
                }
                i--;
                
            }   
            break;
            
        }
        i++;
    }

    while(i_s--){
        formula[i_f]=stack[i_s];
        i_f++;
    }



    formula[i_f]=0;
}

int how_many_letters_in(char *formula,double **probabilities,int n){		/* function that counts how many different variables there are in the given formula*/
    int letters[26],i,sum=0;
    char *p=formula;
    for(i=0;i<26;i++)letters[i]=0;
    for(;*p;p++){
        if(*p>='A'&&*p<='Z'){
            if(!letters[*p-'A']){
                letters[*p-'A']=1;
                probabilities[*p-'A']=malloc(n*sizeof(double));
            }
        }
    }
    for(i=0;i<26;i++)sum+=letters[i];

    return sum;
}

void randomize(double *variable,char *letter,double **probabilities,int n,double (*lower_upper)[2]){	/*funtion that creates random numbers between given scopes using given probabilities*/
    int i,current;
    double num,lower,sum,interval_length;
    for(;*letter;letter++){
        sum=0;
        current=*letter-'A';
        num=((double)rand())/(double)RAND_MAX;
        for(i=0;i<n;i++){
            sum+=probabilities[current][i];
            if(sum>num){                    /* (i+1)inci intervalda bulunuyor */
                num=((double)rand())/(double)RAND_MAX;
                lower=lower_upper[current][0];
                interval_length=(lower_upper[current][1]-lower)/n;

                variable[current]=lower+interval_length*(i+num);
                break;
            }
        }
    }

}

double calculate(char *formula,double *variable,double *numbers){	/*calculation function*/
    double stack[200];
    int i_s=0,i_num=0;
    for(;*formula;formula++){
        switch(*formula){
            case '~':stack[i_s-1]=-stack[i_s-1];break;                                          /*unary minas*/
            case 's':stack[i_s-1]=sin(stack[i_s-1]);break;                                      /*sin*/ 
            case 'c':stack[i_s-1]=cos(stack[i_s-1]);break;                                      /*cos*/ 
            case 'l':stack[i_s-1]=log(stack[i_s-1]);break;                                      /*ln*/ 
            case 'q':stack[i_s-1]=sqrt(stack[i_s-1]);break;                                     /*sqrt*/ 

            case '+':stack[i_s-2]=stack[i_s-2]+stack[i_s-1];i_s--;break;                            
            case '-':stack[i_s-2]=stack[i_s-2]-stack[i_s-1];i_s--;break;                        /*çıkarma*/ 
            case '*':stack[i_s-2]=stack[i_s-2]*stack[i_s-1];i_s--;break;                       
            case '/':stack[i_s-2]=stack[i_s-2]/stack[i_s-1];i_s--;break;
            case '^':stack[i_s-2]=pow(stack[i_s-2],stack[i_s-1]);i_s--;break;

            case 'z':       /*done*/                                                            /*number*/
            stack[i_s]=numbers[i_num];
            i_s++;
            i_num++;
            break;
            default:        /*done*/                                                            /*variable*/
            stack[i_s]=variable[*formula-'A'];
            i_s++;
            break;    
        }
    }
    return stack[0];

}


int main()
{
    char formula[405],c=0,letter[27],*c_pointer;
    double *probabilities[26],lower_upper[26][2],variable[26],lower,upper,*result,interval_length,*control,*freed,numbers[110];
    int i=0,n,number_of_letters,j,i_c=0;
    long int experiments,*interval_results;
    srand(time(NULL));
    
    while(c!='\n'){
        c=getchar();
        while(c==' ')c=getchar();
        switch(c){
            case 's':
            c=getchar();
            if(c=='i'){             /*sin*/
                getchar();
                c='s';
            }
            else{                   /*sqrt*/
            getchar();
            getchar();
            }
            break;
            case 'c':
            getchar();
            getchar();
            break;
            case 'l':
            getchar();
            break;
            default:break;
        }
        if(c=='\n')break;
        formula[i]=c;
        i++;
    }
    formula[i]=0;
    postfix(formula,numbers);   
    scanf("%d %ld",&n,&experiments);
    number_of_letters=how_many_letters_in(formula,probabilities,n);
    for(i=0;i<number_of_letters;i++){
        c=getchar();
        while(c<'A'||c>'Z')c=getchar();
        letter[i_c]=c;
        i_c++;
        scanf("%lf %lf",&lower_upper[c-'A'][0],&lower_upper[c-'A'][1]);
        for(j=0;j<n;j++){
            scanf("%lf",&probabilities[c-'A'][j]);
        }
    }
    letter[i_c]=0;


freed=malloc(5000*sizeof(double));
result=malloc(experiments*sizeof(double));
    if(result!=NULL){					
        free(freed);
        lower=DBL_MAX;
        upper=DBL_MAX*-1;
        for(i=0;i<experiments;i++){                                       /*experiments*/
            randomize(variable,letter,probabilities,n,lower_upper);
            result[i]=calculate(formula,variable,numbers);
            if(lower>result[i])lower=result[i];
            if(upper<result[i])upper=result[i];
        }


        interval_results=calloc(n,sizeof(long int));
        control=malloc(n*sizeof(double));
        interval_length=(upper-lower)/n;
        control[0]=lower+interval_length;
        for(i=1;i<n;i++){
            control[i]=control[i-1]+interval_length;
        }



        for(i=0;i<experiments;i++){
            for(j=0;j<n;j++){
                if(control[j]>result[i]){
                interval_results[j]++;
                break;
                }
                if(j==n-1){
                    if(control[j]==result[i])
                    interval_results[j]++;
                    break;
                }
            }
        }
        free(result);
    }
    else{
        double duble;
        long int randy;
        free(freed);
        randy=rand();
        srand(randy);

        lower=DBL_MAX;
        upper=DBL_MAX*-1;
        for(i=0;i<experiments;i++){                                       /*experiments*/
            randomize(variable,letter,probabilities,n,lower_upper);
            duble=calculate(formula,variable,numbers);
            if(lower>duble)lower=duble;
            if(upper<duble)upper=duble;
        }

        interval_results=calloc(n,sizeof(long int));
        control=malloc(n*sizeof(double));
        interval_length=(upper-lower)/n;
        control[0]=lower+interval_length;
        for(i=1;i<n;i++){
            control[i]=control[i-1]+interval_length;
        }

        srand(randy);
        for(i=0;i<experiments;i++){
            for(j=0;j<n;j++){
                randomize(variable,letter,probabilities,n,lower_upper);
                duble=calculate(formula,variable,numbers);
                if(control[j]>duble){
                interval_results[j]++;
                break;
                }
                if(j==n-1){
                    if(control[j]<=duble)
                    interval_results[j]++;
                    break;
                }
            }
        }
    }




    for(c_pointer=letter;*c_pointer;c_pointer++){
        free(probabilities[*c_pointer-'A']);
    }
    free(control);
    printf("%.3f %.3f ",lower,upper);
    for(i=0;i<n;i++){
        printf("%.3f ",(double)interval_results[i]/experiments);
    }
    printf("\n");
    free(interval_results);

    


    
    
    return 0;
}
