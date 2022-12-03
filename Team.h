#ifndef DAST_EX1_TEAM_H
#define DAST_EX1_TEAM_H
#include "AVLTree.h"
#include "Player.h"
#define EMPTY_NUM 0
#define ZERO 0
#define MINIMUM_TEAM_SIZE_FOR_MATCH 11

class Player;
class Team {
private:

public:
	// members
	int id;
	int points;
	AVLTree<PlayerLevel, Player*> players;
	Player* top_scorrer;
	int players_count;
	int goal_keepers_count;
	// power == sum (goals - cards)
	int power;
	int games_played;

	// big 3
    Team() = delete;
	Team(int id, int points);
	~Team() = default;

	// other methods
    void add_player_to_team(Player* player);
	void remove_player_from_team(Player* player);
	void update_team_stats(int playerId, int gamesPlayed, int scoredGoals, int cardsReceived);
	bool is_legitimate_for_match();
	int get_overall_score();
	void bump_games_played();


//    Team(int id, int points, Player* top_scorrer = nullptr, int power = ZERO, int games_played = ZERO, bool has_goal_keeper = false);

};

#endif //DAST_EX1_TEAM_H