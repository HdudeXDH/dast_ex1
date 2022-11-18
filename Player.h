#ifndef DAST_EX1_PLAYER_H
#define DAST_EX1_PLAYER_H
class Player {
private:
	int id;
	Team* team;
	int games_played;
	int cards;
	bool is_goal_keeper;
	int goals;
	int teams_matches_pre_arrival_count;

public:
	Player()= 0;
	Player(int id);
	~player();
	bool operator> (const Player& other) const;

	/**
	 * getters and setters - add needed
	 */
}


#endif //DAST_EX1_PLAYER_H
