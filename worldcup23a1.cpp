#include "worldcup23a1.h"

world_cup_t::world_cup_t()
{
	// TODO: Your code goes here
}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
}


StatusType world_cup_t::add_team(int teamId, int points)
{
	if (teamId <= 0 || points < 0) {
		return StatusType::INVALID_INPUT;
	}
	// todo Noam- check the problem with the search method
	Node<Team_id, Team> *search_result = teams.search(teamId, true);
	if(search_result.key == teamId) {
		return StatusType::FAILURE;
	}
	try {
		// after discussion - use regular ptrs here
		Team* new_team = new Team(teamId, points);
		teams.add(teamId, *new_team);
	}
	catch (std::bad_alloc& err){
		return StatusType::ALLOCATION_ERROR;
	}
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
	if (teamId <= 0) {
		return StatusType::INVALID_INPUT;
	}
	Node<Team_id, Team>* search_result = AVLTree<Team_id, Team>::search(teamId);
	// todo check what is returned if key doesnt exist
	if (search_result == nullptr) {
		// team doens't exists
		return StatusType::FAILURE;
	}
	Team* team_to_remove = search_result->value;
	if (!((team_to_remove-players).is_empty())) {
		// team has players
		return StatusType::FAILURE;
	}
	try {
		teams.remove_by_key(teamId)
		delete team_to_remove;
	}
	// todo check what is the spesific type of the deletion exeption
	catch (std::exception& err){
		return StatusType::ERROR_ALLOCATION;
	}
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
	if (playerId <= 0 || teamId <= 0 || gamesPlayed <= 0 || goals <=0 || cards <= 0 ) {
		retunr StatusType::INVALID_INPUT;
	}
	Node<Team_id, Team> *team_search_result = teams.search(teamId);
	Node<Player_id, Player> *player_search_result = players_by_id.search(playerId);
	if(team_search_result == nullptr || player_search_result != nullptr ) {
		return StatusType::FAILURE;
	} try {
		// after discussion - use regular ptrs here
		Player* new_player = new Player(playerId,team_search_result, gamesPlayed, goals, cards, goalKeeper);
		players_by_id.add(playerId, new_player);
		players_by_level.add(new_player->level, new_player);
	}
	catch (std::bad_alloc& err){
		return StatusType::ALLOCATION_ERROR;
	}
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
	if (playerId <= 0) {
		return StatusType::INVALID_INPUT
	}
	Node<Player_id, Player> *player_node = players_by_id.search(playerId);
	if (player_node == nullptr) {
		return StatusType::FAILURE
	}
	Player search_result = player_node->value;
	PlayerLevel level = search_result->level;
	Node<PlayerLevel, Player> *player_node = players_by_level.search(level);
	assert()
	return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
	// TODO: Your code goes here
	return 22;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
	// TODO: Your code goes here
	return 2008;
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
	// TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
	// TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
	// TODO: Your code goes here
	return 1006;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
	// TODO: Your code goes here
	return 2;
}

