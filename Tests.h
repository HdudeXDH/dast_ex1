#ifndef DAST_EX1_TESTS_H
#define DAST_EX1_TESTS_H
#include "worldcup23a1.h"
#include "Player.h"
#define N 10

bool player_test() {
	world_cup_t *cup = new world_cup_t();
	cup->add_team(1);
	cup->add_team(2)
	int teamId, gamesPlayed, goals, cards;
	bool is_goal_keeper;
	for (int i=1; i <= N; i++) {
		// just some pseodo random staff
		teamId = i%2 + 1;
		gamesPlayed = i * 2;
		goals = i%3 + 1;
		cup->add_player(i, teamId, gamesPlayed, goals, cards, is_goal_keeper);
	}
};


bool avl_to_array_test() {

}

#endif //DAST_EX1_TESTS_H
