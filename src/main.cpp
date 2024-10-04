#include<pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include "Tools/UIHelper.h"
#include <ctime>

main(){
    pid_t p1=fork();
    pid_t p2=0;
    int turn;
    bool flag[2]={0,0};
    if(pipe(flag)==-1||pipe(turn)==-1){
        std::cout<<"Pipe Failed"<<std::endl;
        return;
    }
    if(p1!=0){
        p2=fork();
    }
    if(p1==0){
        Process(1, flag, turn);
    }
    else if(p2==0){

    }
}

void Process(int process, bool& flag, int& turn){
    int min=0;
    int max=100;
    int otherP;
    if(process==1){
        otherP=0;
    }
    else{
        otherP++
    }
    for(int i=0;i<3;i++){
        while(min+rand()%max!=50);//Chance to move to Critical section
        //Request to go to Critical section
        turn=otherP;
        flag[process]=true;
        time_t timestamp;
        time(&timestamp);
        std::cout<<"Time: "<<timestamp<<" Thead "<<process<<" has requested the resource"<<std::endl;
        while(flag[otherP]&&turn==otherP);
        //Enter Critical section
        time(&timestamp);
        std::cout<<"Time: "<<timestamp<<" Thead "<<process<<" has the resource"<<std::endl;
        while(min+rand()%max!=50);//Chance to leave the critical section
        time(&timestamp);
        std::cout<<"Time: "<<timestamp<<" Thead "<<process<<" has released the resource"<<std::endl;
        flag[process]=false;
    }
}
void Process2(){

}