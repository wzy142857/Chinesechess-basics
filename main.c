#include<stdio.h>
#include<stdbool.h>
#include<string.h>
char map[2][16][2];
bool lmap(char *a,char *data){
    if(a==NULL||data==NULL){
        printf("exists error in lmap(NULL) s.t. lmap:NULL->false");
        return false;
    }
    FILE *fp=NULL;
    size_t n=0;
    if(strcmp(a,"init")==0){
        fp=fopen(data,"rb");
    }else if(strcmp(a,"save")==0){
        fp=fopen(data,"wb");
    }
    if(fp==NULL){
        printf("exists error in lmap(%s,%s) s.t. open_data is false",a,data);
        perror("");
        return false;
    }
    if(strcmp(a,"init")==0){
        n = fread(map,sizeof(char),sizeof(map),fp);
    }else if(strcmp(a,"save")==0){
        n = fwrite(map,sizeof(char),sizeof(map),fp);
    }
    fclose(fp);
    if(n != sizeof(map)){
        printf("exists error in lmap(%s,%s) s.t. n!=%zu",a,data,sizeof(map));
        return false;
    }
    return true;
}
char find_ij[2];
bool find(char a,char b){
    for(char i=0;i<2;i++) for(char j=0;j<16;j++) if((map[i][j][0]==a)&&(map[i][j][1]==b)){
        find_ij[0]=i;
        find_ij[1]=j;
        return true;
    }
    return false;
}
void printmap(){
    for(char i=0;i<10;i++){
        for(char j=0;j<9;j++) if(find(i,j)){
            if(find_ij[0]==0){
                printf("\x1b[1;37;42m%c\x1b[0m",find_ij[1]+97);
            }else{
                printf("\x1b[1;37;41m%c\x1b[0m",find_ij[1]+97);
            }
        }else{
            printf("0");
        }
        printf("\n");
    }
}
bool che(char *x){
    for(char i=0;i<2;i++) if(x[2+i]==map[x[0]][x[1]-97][i]){
        char max=9-i;
        char min=0;
        for(char j=0;j<2;j++) for(char k=0;k<16;k++){
            if(map[j][k][i]!=x[2+i]){
                continue;
            }
            if(map[j][k][1-i]>map[x[0]][x[1]-97][1-i]){
                if(map[j][k][1-i]<max){
                    max=map[j][k][1-i];
                }
            }else if((k!=x[1]-97)&&(map[j][k][1-1]>min)){
                min=map[j][k][1-i];
            }
        }
        if(x[3-i]<=max&&x[3-i]>=min){
            return true;
        }
    }
    return false;
}
bool ma(char *x){
    char px[4][2]={{0,1},{1,0},{-1,0},{0,-1}};
    char dx[4][2][2]={{{1,2},{-1,2}},{{2,1},{2,-1}},{{-2,1},{-2,-1}},{{1,-2},{-1,-2}}};
    for(char i=0;i<4;i++) if(!find(map[x[0]][x[1]-97][0]+px[i][0],map[x[0]][x[1]-97][1]+px[i][1])) for(char j=0;j<2;j++) if((x[2]==map[x[0]][x[1]-97][0]+dx[i][j][0])&&(x[3]==map[x[0]][x[1]-97][1]+dx[i][j][1])){
        return true;
    }
    return false;
}
bool xiang(char *x){
    if(((x[0]==1)&&(x[2]<5))||((x[0]==0)&&(x[2]>4))){
        return false;
    }
    char dx[4][2]={{-1,-1},{1,1},{-1,1},{1,-1}};
    for(char i=0;i<4;i++) if((x[2]==map[x[0]][x[1]-97][0]+2*dx[i][0])&&(x[3]==map[x[0]][x[1]-97][1]+2*dx[i][1])&&(!find(map[x[0]][x[1]-97][0]+dx[i][0],map[x[0]][x[1]-97][0]+dx[i][1]))){
        return true;
    }
    return false;
}
bool shi(char *x){
    if((((x[0]==1)&&(x[2]<7))||((x[0]==0)&&(x[2]>3)))||((x[3]<3)||(x[3]>5))){
        return false;
    }
    char dx[4][2]={{-1,-1},{1,1},{-1,1},{1,-1}};
    for(char i=0;i<4;i++) if((x[2]==map[x[0]][x[1]-97][0]+dx[i][0])&&(x[3]==map[x[0]][x[1]-97][1]+dx[i][1])){
        return true;
    }
    return false;
}
bool jiang(char *x){
    if((((x[0]==1)&&(x[2]<7))||((x[0]==0)&&(x[2]>3)))||((x[3]<3)||(x[3]>5))){
        return false;
    }
    char dx[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
    for(char i=0;i<4;i++) if((x[2]==map[x[0]][x[1]-97][0]+dx[i][0])&&(x[3]==map[x[0]][x[1]-97][1]+dx[i][1])){
        return true;
    }
    return false;
}
bool pao(char *x){
    if(che(x)&&!find(x[2],x[3])){
        return true;
    }else for(char i=0;i<2;i++) if(x[2+i]==map[x[0]][x[1]-97][i]) for(char n=0,b=(x[3-i]>map[x[0]][x[1]-97][1-i] ? 1 : -1),j=map[x[0]][x[1]-97][1-i];b*j<=b*x[3-i];j+=b) if(find(x[2+i]*(1-i)+j*i,j*(1-i)+x[2+i]*i)) if((n++||true)&&j==x[3-i]&&n==3){
        return true;
    }
    return false;
}
bool bing(char *x){
    for(char i=0;i<2;i++) if((x[0]==i)&&((i==0 ? x[2]<5 : x[2]>4)&&(map[x[0]][x[1]-97][1]!=x[3])||(i==0 ? map[x[0]][x[1]-97][0]>x[2] : map[x[0]][x[1]-97][0] < x[2]))){
        return false;
    }
    if(che(x)) for(char b,i=0;i<2;i++) if((((b=x[2+i]-map[x[0]][x[1]-97][i])>0) ? b : -b)==1){
        return true;
    }
    return false;
}
bool gamecore(char *x){
    switch(x[1]-97){
        case 0:
        case 8:
            return che(x);
            break;
        case 1:
        case 7:
            return ma(x);
            break;
        case 2:
        case 6:
            return xiang(x);
            break;
        case 3:
        case 5:
            return shi(x);
            break;
        case 4:
            return jiang(x);
            break;
        case 9:
        case 10:
            return pao(x);
            break;
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            return bing(x);
            break;
        default:
            return false;
    }
}
int main(){
    char sx[4];
    lmap("init","init.data");
    while(1){
        printmap();
        scanf("%hhd,%c,%hhd,%hhd",sx,sx+1,sx+2,sx+3);
        if(!gamecore(sx)){
            continue;
        }
        if(find(sx[2],sx[3])) if(find_ij[0]==sx[0]){
            continue;
        }else{
            map[find_ij[0]][find_ij[1]][0]=-1;
            map[find_ij[0]][find_ij[1]][1]=-1;
        }
        map[sx[0]][sx[1]-97][0]=sx[2];
        map[sx[0]][sx[1]-97][1]=sx[3];
    }
    return 0;
}
