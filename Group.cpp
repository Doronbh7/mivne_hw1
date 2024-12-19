#include "Group.h"

Group::Group(int id) {
	groupID = id;
	players_tree = new AVLTree<Key, Player*>();
}
Group::~Group() {
	delete players_tree;
}
AVLTree<Key,Player*>* Group::getPlayersTree() {
	return players_tree;
}
void Group::setPlayersTree(AVLTree<Key,Player*>* tree) {
	players_tree = tree;
}
int Group::getGroupID() {
	return groupID;
}
void Group::addPlayer(Player* player) {
	Key tmp_key(player->getPlayerID(), player->getLevel());
	players_tree->insertNode(tmp_key, player);
	player->setGroup(groupID);
	return;
}
void Group::removePlayer(Player* player) {
	Key temp_key(player->getPlayerID(), player->getLevel());
	players_tree->deleteNodeByKey(temp_key);
	return;
}
int Group::getNumberOfPlayers() {
	return players_tree->getSize();
}