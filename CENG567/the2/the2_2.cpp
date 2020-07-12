#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct ersel{
    ersel *left,*right;
    int number;
    string character;
    string bit;
};

bool erselcompare0(ersel a,ersel b){
    return a.number<b.number;
}

bool erselcomparec(ersel a,ersel b){
    if(a.character[0]!=b.character[0])
    return a.character[0]<b.character[0];
    else
        return a.character[1]<b.character[1];
}
    


int main()
{
    int number[676];
    for(int *i=number;i<number+676;i++)                             
        *i=0;
    int bits=0,letter_count=0;
	string s;
	cin>>s;
	char *limit=&s[s.length()];
	for(register char *i=&s[0];i<limit;i+=2){                            
		number[(*i-'A')*26+*(i+1)-'A']++;
	}

    cout<<"Frequencies:"<<endl;
	for(int *i=number;i<number+676;i++)                             
        	if(*i){
			letter_count++;
			printf("%c%c: %d\n",'A'+(i-number)/26,'A'+((i-number)%26),*i);
			}
    cout<<endl;
    
    
    
    
    ersel array[letter_count*2-1];
    register ersel *e=array;
    for(int *i=number;i<number+676;i++){                    
        	if(*i){
                (*e).right=NULL;
                (*e).left=NULL;
                (*e).number=*i;
                (*e).character='A'+(i-number)/26;
                (*e).character+='A'+((i-number)%26);
                e++;
            }
    }
    
    sort(array,array+letter_count,erselcompare0);                  
    
    ersel *min1=array,*min2=array+1,*current=array+letter_count,*notleaf=array+letter_count,*isleaf=array+2;            
    for(int i=0;i<letter_count-1;i++){                              
        (*current).number=(*min1).number+(*min2).number;
        (*current).left=min1;
        (*current).right=min2;
        (*min1).bit="1";
        (*min2).bit="0";     
        current++;
        
        if(isleaf>=array+letter_count){
            min1=notleaf;
            notleaf++;
        }
        else{
            if((*isleaf).number<(*notleaf).number){
                min1=isleaf;
                isleaf++;
            }
            else{
                min1=notleaf;
                notleaf++;
            }
        }
        
        if(isleaf>=array+letter_count){
            min2=notleaf;
            notleaf++;
        }
        else if(notleaf>=current){
            min2=isleaf;
            isleaf++;
        }
        else{
            if((*isleaf).number<(*notleaf).number){
                min2=isleaf;
                isleaf++;
            }
            else{
                min2=notleaf;
                notleaf++;
            }
        }
        
    }
    

    
    for(e=array+letter_count*2-2;e>array-1;e--){
        if((*e).left){
            (*(*e).left).bit=(*e).bit+(*(*e).left).bit;
        }
        if((*e).right){
            (*(*e).right).bit=(*e).bit+(*(*e).right).bit;
        }
        
    }

    sort(array,array+letter_count,erselcomparec);
    cout<<"Codes:"<<endl;
    for(e=array;e<array+letter_count;e++){
        bits+=(*e).number*(*e).bit.length();
        cout<<(*e).character<<": "<<(*e).bit<<endl;
    }
    cout<<endl<<"Total Size:"<<endl<<bits<<" bits";
}