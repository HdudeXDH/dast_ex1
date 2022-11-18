#ifndef DAST_EX1_TEAM_H
#define DAST_EX1_TEAM_H
#include "AvlTree.h"

class Team {
private:
	int id;
	int points;
	AvlTree* players;
	Player* top_scorrer;
	int players_count;
	bool has_goal_keeper;
	int power;
	int games_played;

public:
	Team() = 0;
	Team(int id);
	~Team();
	/**
	 * those methods are for the Team only, and will be executed from the add_player and remove_player methods
	 * **/
	add_player_to_team(const Player& player);
	remove_player_from_team()

	/**
	 * getters and setters : according to need
	 */

};

#endif //DAST_EX1_TEAM_H
