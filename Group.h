#ifndef DS_EX1_GROUP
#define DS_EX1_GROUP

#include "Player.h"
#include "AVLTree.h"
#include "Key.h"

class Group {

private:
	int groupID;
	AVLTree<Key,Player*>* players_tree;

public:

    //consructor
	Group(int id);
    //destructor
	~Group();
    //consructor
	Group(const Group& other_group) = default;
    //consructor
	Group& operator=(const Group& other_group) = default;

	/**
	 * Get a pointer to the players tree
	 * @return players_tree
	 */
	AVLTree<Key,Player*>* getPlayersTree();

	/**
	 * Set a new players tree
	 * @param tree - pointer to new tree
	 */
	void setPlayersTree(AVLTree<Key,Player*>* tree);

	/**
	 * Get the group id
	 * @return groupID
	 */
	int getGroupID();

	/**
	 * Get number of players in the group
	 * @return number of players in the group
	 */
	int getNumberOfPlayers();

	/**
	 * Add player to the group and adding the player to players tree
	 * @param player -new player
	 */
	void addPlayer(Player* player);

	/**
	 * Remove player to the group and removing the player from players tree
	 * @param player the removed player
	 */
	void removePlayer(Player* player);
};

#endif
