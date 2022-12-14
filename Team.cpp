#include "Team.h"


Team::Team(int id, int points): id(id), points(points), top_scorrer(nullptr), players_count(EMPTY_NUM),
								goal_keepers_count(EMPTY_NUM), power(EMPTY_NUM), games_played(EMPTY_NUM) {
    {players = AVLTree<PlayerLevel, Player*>();
        players_by_id = AVLTree<int, Player*>();
            };
}

void Team::add_player_to_team(Player* player) {
	assert(player != nullptr);
	players.add(player->level, player);
    players_by_id.add(player->id, player);
	players_count = players_count + 1;
	if (player->is_goal_keeper) {
		this->goal_keepers_count = ((this->goal_keepers_count) + 1);
	}
	int add_to_power = (player->goals - player->cards);
	this->power = this->power + add_to_power;
	if (top_scorrer == nullptr) {
		top_scorrer = player;
	}
    if ( top_scorrer->level < player->level){
        top_scorrer = player;
    }
}

void Team::remove_player_from_team(Player* player) {
	assert(player != nullptr);
	players.remove_by_key(player->level);
    player->next_up= nullptr;
    this->players_by_id.remove_by_key(player->id);
	players_count = players_count - 1;
	if (player->is_goal_keeper) {
		this->goal_keepers_count = ((this->goal_keepers_count) - 1);
	}
	int deduct_from_power = (player->goals - player->cards);
	this->power = this->power - deduct_from_power;
	if(player == top_scorrer) {
		std::shared_ptr<Node<PlayerLevel,Player*>> new_top_scorrer = players.max_node();
        if (new_top_scorrer== nullptr){
            top_scorrer=nullptr;
            return;
        }
		top_scorrer = new_top_scorrer->value;
	}
}

bool Team::is_legitimate_for_match() {
	if (players_count >= MINIMUM_TEAM_SIZE_FOR_MATCH && (goal_keepers_count > EMPTY_NUM) ){
		return true;
	}
	return false;
}

int Team::get_overall_score() {
	return power+points;
}

void Team::bump_games_played() {
	this->games_played = this->games_played + 1;
}

void Team::validate_sizes() {
	std::cout<<this->players_count<<", "<<this->players.size<<", "<<this->players_by_id.size<<std::endl;
}

int Player::get_total_games_played() {
    return (team->games_played + games_played - teams_matches_pre_arrival_count);
}


Player::Player(int playerId, Team* team, int gamesPlayed, int goals, int cards, bool goalKeeper):
        id(playerId), team(team), games_played(gamesPlayed), goals(goals), cards(cards), is_goal_keeper(goalKeeper),
        level(PlayerLevel(goals, cards, playerId)), next_up(nullptr), next_down(
        nullptr) {
    teams_matches_pre_arrival_count=team->games_played;
}
