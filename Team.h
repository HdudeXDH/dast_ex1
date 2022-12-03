#ifndef DAST_EX1_TEAM_H
#define DAST_EX1_TEAM_H
#include "AVLTree.h"
#include "Player.h"
#define EMPTY_NUM 0
#define ZERO 0

class Player;
class Team {
private:

public:
	// todo - to be private
	int id;
	int points;
	AVLTree<Player, Player>* players;
	Player* top_scorrer;
	int players_count;
	bool has_goal_keeper;
	int power;
	int games_played;

	// public methods
    Team() = delete;
    Team(int id, int points, AVLTree<Player, Player>* players = nullptr, Player* top_scorrer = nullptr,
		 int players_count = EMPTY_NUM, int power = ZERO, int games_played = ZERO, bool has_goal_keeper = false);

    ~Team() = default;
    /**
     * those methods are for the Team only, and will be executed from the add_player and remove_player methods
     * **/
    Node<int, Player&>* add_player_to_team(Player& player);
    Node<int, Player&>* remove_player_from_team(Player& player);

    /**
     * getters and setters : according to need
     */

};

#endif //DAST_EX1_TEAM_H