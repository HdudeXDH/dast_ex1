#include "Team.h"

//Team::Team(int id, int points, Player* top_scorrer = nullptr, int power = ZERO, int games_played = ZERO, bool has_goal_keeper = false):
//	 id(id), points(points), top_scorrer(top_scorrer), power(power), games_played(games_played), has_goal_keeper(has_goal_keeper) {};

Team::Team(int id, int points): id(id), points(points), top_scorrer(nullptr), players_count(EMPTY_NUM),
								goal_keepers_count(EMPTY_NUM), power(EMPTY_NUM), games_played(EMPTY_NUM) {
		players = new AVLTree<PlayerLevel, PlayerLevel>();
}

void Team::add_player_to_team(Player* player) {
	assert(player != nullptr);
	players.add(player->level, player);
	players_count = players_count + 1
	if (player->is_goal_keeper) {
		this->goal_keepers_count = ((this->goal_keepers_count) + 1);
	}
	int add_to_power = (player->goals - player->cards);
	this->power = this->power + add_to_power;
	if (top_scorrer == null || top_scorrer->level < player->level) {
		top_scorrer = player;
	}
}

void Team::remove_player_from_team(Player* player) {
	assert(player != nullptr);
	players.remove_by_key(player->level);
	players_count = players_count - 1
	if (player->is_goal_keeper) {
		this->goal_keepers_count = ((this->goal_keepers_count) - 1);
	}
	int deduct_from_power = (player->goals - player->cards);
	this->power = this->power - deduct_from_power;
	if(player == top_scorrer) {
		Node<PlayerLevel, Player> *new_top_scorrer = AVLTree<PlayerLevel, Player>::max_node(players);
		top_scorrer = new_top_scorrer->value;
	}
}

bool Team::is_legitimate_for_match() {
	if (this->players.size >= MINIMUM_TEAM_SIZE_FOR_MATCH(this->goal_keepers_count > EMPTY_NUM)
}

int Team::get_overall_score() {
	return power+points;
}

void Team::bump_games_played() {
	this->games_played = this->games_played + 1;
}
//void Team::update_team_stats(int playerId, int gamesPlayed, int scoredGoals, int cardsReceived) {
//
//	Node<PlayerLevel, Player> *new_top_scorrer = players.max_node();
//	top_scorrer = new_top_scorrer->value;
//}