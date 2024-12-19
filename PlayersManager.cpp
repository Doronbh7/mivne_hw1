#include "PlayersManager.h"
#include "helper_functions.h"
#include <cstdlib>

PlayersManager::PlayersManager() {
    this->groupsTree=new AVLTree<int, Group*>;
    this->populatedGroupsTree=new AVLTree<int, Group*>;
    this->playersTree=new AVLTree<int, Player*>;
    this->playersBylevelTree=new AVLTree<Key, Player*>;

}

PlayersManager::~PlayersManager() {
    groupsTree->deleteAllDataInTree();
    delete groupsTree;
    delete populatedGroupsTree;
    playersTree->deleteAllDataInTree();
    delete playersTree;
    delete playersBylevelTree;
}

StatusType PlayersManager::AddGroup(int GroupID) {
    try{
        if((groupsTree->isExist(GroupID))==true){
            return FAILURE;
        }
        Group* data = new Group(GroupID);
        groupsTree->insertNode(GroupID, data);
    }catch(std::bad_alloc& exception){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType PlayersManager::AddPlayer(int PlayerID, int GroupID, int Level) {
    try{
        if(groupsTree->isExist(GroupID) != true || playersTree->isExist(PlayerID) == true) {
            return FAILURE;
        }
        AVLNode<int,Group*>* group_node = groupsTree->getNodeByKey(GroupID);
        Group* group_data = group_node->getData();
        
        Player* new_player = new Player(PlayerID, Level, GroupID);
        Key player_key(PlayerID, Level);
        group_data->addPlayer(new_player);

        if (group_data->getNumberOfPlayers() == 1) {
            populatedGroupsTree->insertNode(GroupID, group_data);
        }
        playersTree->insertNode(PlayerID, new_player);
        playersBylevelTree->insertNode(player_key, new_player);
        return SUCCESS;
    }catch(std::bad_alloc& exception){
        return ALLOCATION_ERROR;
    }
}

StatusType PlayersManager::RemovePlayer(int PlayerID) {
    if(playersTree->isExist(PlayerID) != true ){
        return FAILURE;
    }
    AVLNode<int, Player*>* player_node = playersTree->getNodeByKey(PlayerID);
    Player* player_data = player_node->getData();
    int player_group_id = player_data->getGroup();
    AVLNode<int, Group*>* group_node = populatedGroupsTree->getNodeByKey(player_group_id);
    Group* player_group_data = group_node->getData();
    Key player_key(PlayerID, player_data->getLevel());


    player_group_data->removePlayer(player_data);
    playersTree->deleteNodeByKey(PlayerID);
    playersBylevelTree->deleteNodeByKey(player_key);
    delete player_data;

    if (player_group_data->getNumberOfPlayers() == 0) {
        populatedGroupsTree->deleteNodeByKey(player_group_data->getGroupID());
    }
    return SUCCESS;
}

StatusType PlayersManager::ReplaceGroup(int GroupID, int ReplacementID) {
    try{
        if(groupsTree->isExist(GroupID) != true || groupsTree->isExist(ReplacementID) != true){
            return FAILURE;
        }
        AVLNode<int, Group*>* curr_group_node = groupsTree->getNodeByKey(GroupID);
        AVLNode<int, Group*>* replacement_group_node = groupsTree->getNodeByKey(ReplacementID);
        Group* group_a = curr_group_node->getData();
        Group* group_b = replacement_group_node->getData();

     
        int group_a_size = group_a->getNumberOfPlayers();
        int group_b_size = group_b->getNumberOfPlayers();
        int array_size = group_a_size + group_b_size;

        Player** group_a_players_array = new Player*[group_a_size];
        Player** group_b_players_array = new Player*[group_b_size];
        Player** combined_players_array = new Player*[array_size];
        Key* keys_array = new Key[array_size];

        (group_a->getPlayersTree())->GetKSmallestInOrderArray(group_a_players_array, group_a_size);
        (group_b->getPlayersTree())->GetKSmallestInOrderArray(group_b_players_array, group_b_size);

        for (int i = 0; i < group_a_size; i++) {
            group_a_players_array[i]->setGroup(ReplacementID);
        }
        mergePlayerArrays(group_a_players_array, group_a_size, group_b_players_array, group_b_size, combined_players_array);

        for (int i = 0; i < array_size; i++) {
           Key tmp_key(combined_players_array[i]->getPlayerID(), combined_players_array[i]->getLevel());
           keys_array[i] = tmp_key;
        }
        delete (group_b->getPlayersTree());

        AVLTree<Key, Player*>* merged_groups_tree = new AVLTree<Key, Player*>;

        merged_groups_tree->sortedArrayToAVL(combined_players_array, keys_array, array_size);
        group_b->setPlayersTree(merged_groups_tree);

        groupsTree->deleteNodeByKey(GroupID);
        if (populatedGroupsTree->isExist(GroupID)) {
            populatedGroupsTree->deleteNodeByKey(GroupID);
        }
        if (group_a_size != 0 && group_b_size == 0) {
            populatedGroupsTree->insertNode(ReplacementID, group_b);
        }
        delete group_a;
        delete[] group_a_players_array;
        delete[] group_b_players_array;
        delete[] keys_array;
        delete[] combined_players_array;

        return SUCCESS;
    }catch(std::bad_alloc& exception){
        return ALLOCATION_ERROR;
    }

}

StatusType PlayersManager::IncreaseLevel(int PlayerID, int LevelIncrease) {
    try{
        if(playersTree->isExist(PlayerID) != true ){
            return FAILURE;
        }
        AVLNode<int, Player*>* player_node = playersTree->getNodeByKey(PlayerID);
        Player* player_data = player_node->getData();
        int player_group_id = player_data->getGroup();
        AVLNode<int, Group*>* group_node = populatedGroupsTree->getNodeByKey(player_group_id);
        Group* player_group_data = group_node->getData();
        int old_level=player_data->getLevel();
        int new_level=old_level+LevelIncrease;
        player_group_data->removePlayer(player_data);
        Key temp_key(PlayerID,old_level);
        playersBylevelTree->deleteNodeByKey(temp_key);

        player_data->setLevel(new_level);

        player_group_data->addPlayer(player_data);
        Key temp1_key(PlayerID,new_level);
        playersBylevelTree->insertNode(temp1_key, player_data);


        return SUCCESS;
    }catch(std::bad_alloc& exception){
        return ALLOCATION_ERROR;
    }

}

StatusType PlayersManager::GetHighestLevel(int GroupID, int *PlayerID) {
    try{
        if(GroupID>0){
            if((groupsTree->isExist(GroupID) != true)){
                return FAILURE;
            }
        }
        if(GroupID<0){
            if((this->playersBylevelTree->getSize())==0){
                *PlayerID=-1;
            }
            else{
                *PlayerID=this->playersBylevelTree->getBiggestData()->getPlayerID();

            }

        }

        if(GroupID>0){
            AVLNode<int, Group*>* group_node = groupsTree->getNodeByKey(GroupID);
            Group* group_data = group_node->getData();
            AVLTree<Key,Player*>* group_players_tree=group_data->getPlayersTree();

            if((group_players_tree->getSize())==0){
                *PlayerID=-1;
            }
            else{
                *PlayerID=group_players_tree->getBiggestData()->getPlayerID();

            }

        }


        return SUCCESS;
    }catch(std::bad_alloc& exception){
        return ALLOCATION_ERROR;
    }

}

StatusType PlayersManager::GetAllPlayersByLevel(int GroupID, int **Players,
                                                int *numOfPlayers) {
    try{
        if(GroupID>0){
            if((groupsTree->isExist(GroupID) != true)){
                return FAILURE;
            }
        }

        if(GroupID<0){
            *numOfPlayers=this->playersBylevelTree->getSize();
            int array_size = *numOfPlayers;
            if(array_size == 0){
                *Players = NULL;
            }
            else{
                int* players_id = (int*)malloc(sizeof(int) * array_size);
                if (!players_id) {
                    return ALLOCATION_ERROR;
                }
                Player** players_data_array = new Player*[array_size];
                playersBylevelTree->GetKLargestReversedInOrderArray(players_data_array, array_size);
                for(int i=0;i<array_size;i++){
                    players_id[i]= (players_data_array[i]->getPlayerID());
                }
                delete[] players_data_array;
                *Players = players_id;
            }

        }

        if(GroupID>0){
            AVLNode<int, Group*>* group_node = groupsTree->getNodeByKey(GroupID);
            Group* group_data = group_node->getData();
            AVLTree<Key,Player*>* group_players_tree = group_data->getPlayersTree();

            *numOfPlayers = group_players_tree->getSize();
            int array_size = *numOfPlayers;
            if(array_size == 0){
                *Players = NULL;
            } else{
                int* players_id = (int*)malloc(sizeof(int) * array_size);
                if (!players_id) {
                    return ALLOCATION_ERROR;
                } 
                Player** players_data_array = new Player*[array_size];
                group_players_tree->GetKLargestReversedInOrderArray(players_data_array, array_size);
                for(int i=0;i<array_size;i++){
                    players_id[i] = players_data_array[i]->getPlayerID();
                }
                delete[] players_data_array;
                *Players = players_id;
            }
        }
        return SUCCESS;
    }catch(std::bad_alloc& exception){
        return ALLOCATION_ERROR;
    }
}

StatusType PlayersManager::GetGroupsHighestLevel(int numOfGroups,
                                                 int **Players) {
    try{
        if(numOfGroups>(populatedGroupsTree->getSize())){
            return FAILURE;
        }

        int* players_id = (int*)malloc(sizeof(int) * numOfGroups);
        if (!players_id) {
            return ALLOCATION_ERROR;
        } 
        Group** group_data_array = new Group*[numOfGroups];
        populatedGroupsTree->GetKSmallestInOrderArray(group_data_array, numOfGroups);
        for(int i = 0; i< numOfGroups; i++){
            Group* group_data = group_data_array[i];
            Player* highest_player = (group_data->getPlayersTree())->getBiggestData();
            players_id[i] = highest_player->getPlayerID();
        }
        delete[] group_data_array;
        *Players= players_id;

        return SUCCESS;
    }catch(std::bad_alloc& exception){
        return ALLOCATION_ERROR;
    }

}