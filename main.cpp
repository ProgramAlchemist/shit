#include <iostream>
#include <fstream>

using namespace std;
ofstream outFile;
struct STACK{
    int  *elems;	//申请内存用于存放栈的元素
    int   max;	//栈能存放的最大元素个数
    int   pos;	//栈实际已有元素个数，栈空时pos=0;
};
STACK* slist[100];
int slistn =0;
void initSTACK(STACK *const p, int m);	//初始化p指向的栈：最多m个元素
void initSTACK(STACK *const p, const STACK&s); //用栈s初始化p指向的栈
int  size (const STACK *const p);		//返回p指向的栈的最大元素个数max
int  howMany (const STACK *const p);	//返回p指向的栈的实际元素个数pos
int  getelem (const STACK *const p, int x);	//取下标x处的栈元素
STACK *const push(STACK *const p, int e); 	//将e入栈，并返回p
STACK *const pop(STACK *const p, int &e); 	//出栈到e，并返回p
STACK *const assign(STACK*const p, STACK&s); //赋s给p指的栈,并返回p
void print(const STACK*const p);			//打印p指向的栈
void destroySTACK(STACK*const p);		    //销毁p指向的栈
int printOUT(STACK*p);

int main(int argc, char const *argv[]) {
    outFile.open("U201614876_1.txt");
    int n;
    string strlist[100];
    for (int i = 0; i < argc; i++) {
        strlist[i] = argv[i];
    }
    if(strlist[1]=="-S"){
        outFile<<"S"<<" ";
        cout<<"S"<<" ";
        n = atoi(strlist[2].c_str());
        STACK *p = new STACK;
        outFile<<n<<" ";
        cout<<n<<" ";
        slist[0] = p;
        slistn = 1;

        initSTACK(p,n);
        int flag = 0;
        int argg;
        for (int i = 3; i < argc; i++) {
            if(flag==-1) {
                outFile<<"E ";
                cout<<"E ";
                break; }
            if(strlist[i]=="-I"){
                if(p->pos>0)printOUT(p);
                outFile<<"I"<<" ";
                cout<<"I"<<" ";
                flag = 1;
            }else if(strlist[i]=="-O"){
                if(p->pos>0)printOUT(p);
                outFile<<"O"<<" ";
                cout<<"O"<<" ";
                flag = 2;
            }else if(strlist[i]=="-G"){
                if(p->pos>0)printOUT(p);
                outFile<<"G"<<" ";
                cout<<"G"<<" ";
                flag = 3;
            }else if(strlist[i]=="-A"){
                if(p->pos>0)printOUT(p);
                outFile<<"A"<<" ";
                cout<<"A"<<" ";
                flag = 4;
            }else if(strlist[i]=="-C"){
                if(p->pos>0)printOUT(p);
                outFile<<"C"<<" ";
                cout<<"C"<<" ";
                flag = 4;
            }else if(strlist[i]=="-N"){
                if(p->pos>0)printOUT(p);
                outFile<<"N"<<" ";
                cout<<"N"<<" ";
                flag = 5;
            }
            else{
                argg = atoi(strlist[i].c_str());
                switch (flag) {
                    case 1:{
                        if(push(p,argg)==NULL){
                            flag=-1;
                        }
                        break;
                    }
                    case 2:{
                        int x = argg;
                        int tmp;
                        for(int j =0;j<x;j++){
                            if(pop(p,tmp)==NULL)flag=-1;
                        }
                        break;
                    }
                    case 3:{
                        int tmp;
                        tmp = getelem(p,argg+1);
                        outFile<<tmp<<" ";
                        cout<<tmp<<" ";
                        break;
                    }
                    case 4:{
                        STACK*t = new STACK;
                        assign(t,*p);
                        p =t;
                        slist[slistn] = t;
                        slistn++;
                        break;
                    }
                    case 5:{
                        outFile<<p->pos<<" ";
                        cout<<p->pos<<" ";
                        break;
                    }
                }
            }
        }if(p->pos>0&&(flag==1||flag==2))printOUT(p);
    }else {
        std::cout << "ERROR" << '\n';
    }

    outFile.close();
    return 0;
}

void initSTACK(STACK *const p, int m)	//初始化p指向的栈：最多m个元素
{
    if (m>0) {
        p->elems = (int *) malloc(sizeof(int) * m);
        p->max = m;
        p->pos = 0;
    }
    else {
        printf("wrong m\n");
        return;
    }
}
void initSTACK(STACK *const p, const STACK&s) //用栈s初始化p指向的栈
{

    int pos = s.pos;
    initSTACK(p,s.max);
    for (int i=0; i < pos;i++){
        p->elems[i] = s.elems[i];
    }
    p->max = s.max;
    p->pos = pos;
}
int  size (const STACK *const p)		//返回p指向的栈的最大元素个数max
{
    if(p->max!=NULL) return p->max;
}
int  howMany (const STACK *const p)		//返回p指向的栈的实际元素个数pos
{
    if(p->pos!=NULL) return p->pos;
}
int  getelem (const STACK *const p, int x)	//取下标x处的栈元素
{
    if (0<x<=p->max){
        return p->elems[x-1];
    }
    else {
        printf("Wrong!\n");
        return false;
    }
}
STACK *const push(STACK *const p, int e) 	//将e入栈，并返回p
{
    if (p->pos<p->max) {
        p->elems[p->pos] =e;
        p->pos++;
        return p;
    } else{
        return NULL;
    }
}
STACK *const pop(STACK *const p, int &e) 	//出栈到e，并返回p
{
    if (p->pos>0){
        e = p->elems[p->pos-1];
        p->pos=p->pos-1;
        return p;
    }
    else {
        return NULL;
    }
}
STACK *const assign(STACK*const p, STACK&s) //赋s给p指的栈,并返回p
{
    int pos = s.pos;
    initSTACK(p,s.max);
    for (int i=0; i < pos;i++){
        p->elems[i] = s.elems[i];
    }
    p->max = s.max;
    p->pos = pos;
    return p;
}
void print(const STACK*const p)			//打印p指向的栈
{
    printf("\n");
    if (p->max>0){
        for (int i=0;i < p->max;i++){
            printf("%d ",p->elems[i]);
        }

    }
    else{
        printf("False");
        return;
    }
}
int printOUT(STACK*p){

    if (p->max>0){
        for (int i=0;i < p->pos;i++){
            outFile<<p->elems[i]<<" ";
            cout<<p->elems[i]<<" ";
        }
        return 1;

    }
    else{
//        printf("False");
        return -1;
    }

}

void destroySTACK(STACK*const p)		    //销毁p指向的栈
{
    free(p->elems);
    p->max = 0;
    p->pos = 0;
    free(p);
}