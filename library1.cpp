
#include "library1.h"
#include "PlayersManager.h"

void *Init(){
    try{
        PlayersManager* PlayersManager_ptr=new PlayersManager();

        return (void*)PlayersManager_ptr;

    }
    catch(std::bad_alloc& exception ){
        return nullptr;

    }

}

StatusType AddGroup(void *DS, int GroupID){
    if((DS== nullptr) || (GroupID<=0)){
        return INVALID_INPUT;
    }

    PlayersManager* PlayersManager_ptr=((PlayersManager*)DS);
    return PlayersManager_ptr->AddGroup(GroupID);

}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int Level){
    if((DS== nullptr) || (PlayerID<=0) || (GroupID<=0) || (Level<0)){
        return INVALID_INPUT;
    }

    PlayersManager* PlayersManager_ptr=((PlayersManager*)DS);
    return PlayersManager_ptr->AddPlayer(PlayerID,GroupID,Level);


}

StatusType RemovePlayer(void *DS, int PlayerID){
    if((DS== nullptr) || (PlayerID<=0)){
        return INVALID_INPUT;
    }

    PlayersManager* PlayersManager_ptr=((PlayersManager*)DS);
    return PlayersManager_ptr->RemovePlayer(PlayerID);
}

StatusType ReplaceGroup(void *DS, int GroupID, int ReplacementID){
    if((DS== nullptr) || (GroupID<=0) || (ReplacementID<=0) || (ReplacementID==GroupID)){
        return INVALID_INPUT;
    }

    PlayersManager* PlayersManager_ptr=((PlayersManager*)DS);
    return PlayersManager_ptr->ReplaceGroup(GroupID,ReplacementID);
}

StatusType IncreaseLevel(void *DS, int PlayerID, int LevelIncrease){
    if((DS== nullptr) || (PlayerID<=0) || (LevelIncrease<=0)){
        return INVALID_INPUT;
    }

    PlayersManager* PlayersManager_ptr=((PlayersManager*)DS);
    return PlayersManager_ptr->IncreaseLevel(PlayerID,LevelIncrease);
}

StatusType GetHighestLevel(void *DS, int GroupID, int *PlayerID){
    if((DS== nullptr) || (PlayerID== nullptr) || (GroupID== 0)){
        return INVALID_INPUT;
    }

    PlayersManager* PlayersManager_ptr=((PlayersManager*)DS);
    return PlayersManager_ptr->GetHighestLevel(GroupID,PlayerID);
}

StatusType GetAllPlayersByLevel(void *DS, int GroupID, int **Players, int *numOfPlayers){
    if((DS== nullptr) || (GroupID==0) || (Players==nullptr) || (numOfPlayers==nullptr)){
        return INVALID_INPUT;
    }

    PlayersManager* PlayersManager_ptr=((PlayersManager*)DS);
    return PlayersManager_ptr->GetAllPlayersByLevel(GroupID,Players,numOfPlayers);
}

StatusType GetGroupsHighestLevel(void *DS, int numOfGroups, int **Players){
    if((DS== nullptr) || (Players==nullptr) || (numOfGroups<1)){
        return INVALID_INPUT;
    }

    PlayersManager* PlayersManager_ptr=((PlayersManager*)DS);
    return PlayersManager_ptr->GetGroupsHighestLevel(numOfGroups,Players);
}

void Quit(void** DS){
    if(DS== nullptr){
        return;
    }

    if((*DS)== nullptr){
        return;
    }

    delete ((PlayersManager*)(*DS));

    *DS= nullptr;

}





