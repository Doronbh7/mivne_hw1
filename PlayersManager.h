#ifndef LIBRARY1_CPP_PLAYERSMANAGER_H
#define LIBRARY1_CPP_PLAYERSMANAGER_H

#include <memory>

#include "Group.h"
#include "Player.h"
#include "library1.h"
#include "Key.h"
#include "AVLTree.h"

class PlayersManager {

    AVLTree<int, Group*>* groupsTree;
    AVLTree<int, Group*>* populatedGroupsTree;
    AVLTree<int, Player*>* playersTree;
    AVLTree<Key, Player*>* playersBylevelTree;

public:
    PlayersManager();
    ~PlayersManager();

    /**
     * Add  a Group to the system
     * @param GroupID
     * @return
     */
    StatusType AddGroup(int GroupID);

    /**
     * Add  a Player to the system
     * @param PlayerID
     * @param GroupID
     * @param Level
     * @return
     */
    StatusType AddPlayer(int PlayerID, int GroupID, int Level);

    /**
     * Remove a Player from the system
     * @param PlayerID
     * @return
     */
    StatusType RemovePlayer(int PlayerID);

    /**
     * Move the players from GroupID to ReplacementID and delete the group GroupID
     * @param GroupID
     * @param ReplacementID
     * @return
     */
    StatusType ReplaceGroup(int GroupID, int ReplacementID);

    /**
     * Increase PlayerID level (LevelIncrease)
     * @param PlayerID
     * @param LevelIncrease
     * @return
     */
    StatusType IncreaseLevel(int PlayerID, int LevelIncrease);

    /**
     * Get the player with the highest level in the group and put ID in the pointer PlayerID.
     * If GroupID<0 get the player with the highest level in the system and put ID in the pointer PlayerID.
     * @param GroupID
     * @param PlayerID
     * @return
     */
    StatusType GetHighestLevel(int GroupID, int* PlayerID);

    /**
     * Get players of the group sorted from the highest to lowest level and put the players id in array Players pointing to and the number of players in numOfPlayers pointer.
     * If GroupID<0  get players of the system sorted from the highest to lowest level and put the players id in array Players pointing to and the number of players in numOfPlayers pointer.
     * @param GroupID
     * @param Players
     * @param numOfPlayers
     * @return
     */
    StatusType GetAllPlayersByLevel(int GroupID, int** Players, int* numOfPlayers);

    /**
     *Get the highest level player of the lowest numOfGroups id in the populated groups and put the id in the array Players pointing to.
     * @param numOfGroups
     * @param Players
     * @return
     */
    StatusType GetGroupsHighestLevel(int numOfGroups, int** Players);
};

#endif //LIBRARY1_CPP_PLAYERSMANAGER_H
