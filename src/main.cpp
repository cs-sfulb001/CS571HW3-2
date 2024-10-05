#include<thread>
#include <sys/types.h>
#include "Tools/UIHelper.h"
#include <ctime>
#include <chrono>

void Process(int process, bool (&flags)[2], int &turn){
    int min=0;
    int max=100;
    int otherP;
    if(process==1){
        otherP=0;
    }
    else{
        otherP=1;
    }
    for(int i=0;i<3;i++){
        std::string output;
        while(min+rand()%max!=50);//Chance to move to Critical section
        //Request to go to Critical section
        turn=otherP;
        flags[process]=true;
        output="Thread "+std::to_string(process)+" has requested the resource";
        std::cout<<output<<std::endl;
        while(flags[otherP]&&turn==otherP);
        //Enter Critical section
        output="Thread "+std::to_string(process)+" has the resource";
        std::cout<<output<<std::endl;
        while(min+rand()%max!=50);//Chance to leave the critical section
        output="Thread "+std::to_string(process)+" has released the resource";
        std::cout<<output<<std::endl;
        flags[process]=false;
    }
}

main(){
    bool flags[2]={0,0};
    int turn;
    std::thread thread1(Process, 0, std::ref(flags), std::ref(turn));
    std::thread thread2(Process, 1, std::ref(flags), std::ref(turn));
    std::cout<<"Threads started?"<<std::endl;
    while(thread1.joinable()||thread2.joinable()){
        if(!flags[turn])
            turn = rand()%1;
    }
}

