#ifndef DAST_EX1_PLAYER_H
#define DAST_EX1_PLAYER_H
#include "Team.h"

class PlayerLevel {
public:
	int goals;
	int cards;
	int id;

	// big 3
	PlayerLevel(int goals, int cards, int id):goals(goals), cards(cards), id(id){}
	~PlayerLevel() = default;
	PlayerLevel(const PlayerLevel&) = delete;

	//compare method overload
	bool operator>(PlayerLevel* level1, PlayerLevel* level2);
};


class Player {
private:
    int id;
    Team* team;
	PlayerLevel* level;
	int cards;
	int games_played;
    bool is_goal_keeper;
    int goals;
    int teams_matches_pre_arrival_count;
    Node<int, Player>* next_up;
    Node<int, Player>* next_down;

public:
    Player()= delete;
	Player(int playerId, Team* team, int gamesPlayed, int goals, int cards, bool goalKeeper);
    ~Player()= default;
    bool operator> (const Player& other) const;


    /**
     * getters and setters - add needed
     */
}


#endif //DAST_EX1_PLAYER_H