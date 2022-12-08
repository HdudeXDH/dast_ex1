// 
// 234218 Data Structures 1.
// Semester: 2023A (winter).
// Wet Exercise #1.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef WORLDCUP23A1_H_
#define WORLDCUP23A1_H_
#define POINTS_TO_ADD 3

#include "wet1util.h"
//#include "AVLTree.h"
#include "Player.h"
#include "Team.h"
#include "LinkedList.h"

typedef int Team_id;
typedef int Player_id;
class world_cup_t {
private:
	// members
	AVLTree<Player_id, Player> players_by_id;
	AVLTree<PlayerLevel, Player*> players_by_level;
	AVLTree<Team_id ,Team> teams;
	AVLTree<Team_id ,Team*> legitimate_teams;
	Player* top_scorrer;
	int players_count;

	// methods
	LinkedList<int, int>* export_lagitimate_teams_to_list(int minTeamId, int maxTeamId);
    void renew_player_nextup_nextdown(Node<PlayerLevel, Player*> * player_node);
	void recursive_export_to_list(int minTeamId, int maxTeamId, Node<int, Team*>* start, LinkedList<int, int>* list);
	void Recursive_export_legitimate_teams_to_list(Node<int, Team*>* root, LinkedList<int, int>* list, int minId, int maxId);
	void printScoreboard();
	
public:
	// <DO-NOT-MODIFY> {
	
	world_cup_t();
	virtual ~world_cup_t();
	
	StatusType add_team(int teamId, int points);
	
	StatusType remove_team(int teamId);
	
	StatusType add_player(int playerId, int teamId, int gamesPlayed,
	                      int goals, int cards, bool goalKeeper);
	
	StatusType remove_player(int playerId);
	
	StatusType update_player_stats(int playerId, int gamesPlayed,
	                                int scoredGoals, int cardsReceived);
	
	StatusType play_match(int teamId1, int teamId2);
	
	output_t<int> get_num_played_games(int playerId);
	
	output_t<int> get_team_points(int teamId);
	
	StatusType unite_teams(int teamId1, int teamId2, int newTeamId);
	
	output_t<int> get_top_scorer(int teamId);
	
	output_t<int> get_all_players_count(int teamId);
	
	StatusType get_all_players(int teamId, int *const output);
	
	output_t<int> get_closest_player(int playerId, int teamId);
	
	output_t<int> knockout_winner(int minTeamId, int maxTeamId);
	
	// } </DO-NOT-MODIFY>
};

#endif // WORLDCUP23A1_H_
