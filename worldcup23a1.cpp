#include "worldcup23a1.h"

world_cup_t::world_cup_t(): top_scorrer(nullptr), players_count(EMPTY_NUM)
{
	players_by_id = AVLTree<int, Player>();//AVLTree<Player_id, Player*>();
	players_by_level = AVLTree<PlayerLevel, Player*>();
	teams = AVLTree<int , Team>();//AVLTree<Team_id , Team*>();
	legitimate_teams = AVLTree<int, Team*>();
}

world_cup_t::~world_cup_t()
{
	delete players_by_level;
	delete players_by_id;
	delete legitimate_teams;
	delete teams;
	// TODO: Your code goes here
}


StatusType world_cup_t::add_team(int teamId, int points)
{
	if (teamId <= 0 || points < 0) {
		return StatusType::INVALID_INPUT;
	}
	Node<Team_id, Team> *search_result = teams.search(teamId, true);
	if(search_result != nullptr) {
		return StatusType::FAILURE;
	}
	try {
//		Team* new_team = new
		teams.add(teamId, Team(teamId, points));
	}
	catch (AVLTree<Team_id, Team>::NodeAlreadyExists& err) {
		return StatusType::FAILURE;
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
	Node<int, Team>* search_result = teams.search(teamId); //Node<Team_id, Team>* //AVLTree<Team_id, Team>::search(teamId);
	// todo check what is returned if key doesnt exist
	if (search_result == nullptr) {
		// team doens't exists
		return StatusType::FAILURE;
	}
	Team* team_to_remove = search_result->value;
	if (!((team_to_remove->players).is_empty())) {
		// team has players
		return StatusType::FAILURE;
	}
	try {
		teams.remove_by_key(teamId);
		delete team_to_remove;
	}
	// todo check what is the spesific type of the deletion exeption
	catch (std::exception& err){
		return StatusType::ALLOCATION_ERROR; //ERROR_ALLOCATION;
	}
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
	if (playerId <= 0 || teamId <= 0 || gamesPlayed <= 0 || goals <=0 || cards <= 0 ) {
		return StatusType::INVALID_INPUT;
	}
	Node<Team_id, Team> *team_search_result = teams.search(teamId);
    Node<int, Player> *player_search_result = players_by_id.search(playerId); //Node<Player_id, Player>
	if(team_search_result == nullptr || player_search_result != nullptr ) {
		return StatusType::FAILURE;
	}
	Team *team_to_add_player = team_search_result->value;
	try {
		// after discussion - use regular ptrs here
//		Player* new_player = new Player(playerId,team_search_result, gamesPlayed, goals, cards, goalKeeper);
        Node<int, Player> *new_player = players_by_id.add(playerId, Player(playerId,&team_search_result->value, gamesPlayed, goals, cards, goalKeeper));
		players_by_level.add(*new_player->value.level, &new_player->value);
		bool was_team_legitimate_before_adding = team_to_add_player->is_legitimate_for_match();
		team_to_add_player->add_player_to_team(&new_player->value);
		if (team_to_add_player->is_legitimate_for_match() && !was_team_legitimate_before_adding) {
			legitimate_teams.add(teamId, team_to_add_player);
		}
		players_count = players_count + 1;
		top_scorrer = players_by_level.max_node()->value;
	}
	catch (std::bad_alloc& err){
		return StatusType::ALLOCATION_ERROR;
	}
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
	if (playerId <= 0) {
		return StatusType::INVALID_INPUT;
	}
	Node<Player_id, Player> *player_node_in_id_tree = players_by_id.search(playerId);
	if (player_node_in_id_tree == nullptr) {
		return StatusType::FAILURE;
	}
	Player *player_to_remove = &player_node_in_id_tree->value;
	Team *players_team = player_to_remove->team;
	PlayerLevel  level = *player_to_remove->level;
	Node<PlayerLevel, Player*> *player_node_in_level_tree = players_by_level.search(level);
	try {
		// remove player from all AVL trees
		bool was_team_legitimate_before_removing = players_team->is_legitimate_for_match();
		players_by_id.remove_Node(player_node_in_id_tree);
		players_by_level.remove_Node(player_node_in_level_tree);
		players_team->remove_player_from_team(player_to_remove);
		players_count = players_count - 1;
		if (was_team_legitimate_before_removing && !players_team->is_legitimate_for_match()) {
			legitimate_teams.remove_by_key(players_team->id);
		}
		//delete player
		delete player_to_remove;
		top_scorrer = players_by_level.max_node()->value;
	} catch (std::exception& err) {
		return StatusType::ALLOCATION_ERROR;
	}
	return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
	if (playerId <= 0 || gamesPlayed <= 0 || scoredGoals <= 0 || cardsReceived <=0) {
		retunr StatusType::INVALID_INPUT;
	}
	Node<Player_id, Player> *player_node_in_id_tree = players_by_id.search(playerId);
	Player player = player_node_in_id_tree->value;
	Team team = player.team;
	if (player_node_in_id_tree == nullptr) {
		return StatusType::FAILURE;
	}
	try {
		players_by_level.remove_by_key(player.level);
	} catch (std::exception& err) {
		return StatusType::ALLOCATION_ERROR;
	}
	// remove (in order to add)
	team.remove_player_from_team(player);
	player.games_played = (player.games_played + gamesPlayed);
	player.goals = (player.goals + scoredGoals);
	player.cards = (player.cards + cardsReceived);
	player.updateLevel();
	try {
		players_by_level.add(player.level, player);
		team.add_player_to_team(player)
	} catch (std::exception& err) {
		return StatusType::ALLOCATION_ERROR;
	}
	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
	if (teamId1 == teamId2 || teamId1 <= 0 || teamId2 <= 0) {
		return StatusType::INVALID_INPUT;
	}
	Team* team1 = teams.search(teamId1);
	Team* team2 = teams.search(teamId2);
	if (team1 == nullptr || team2 == nullptr || !(team1->is_legitimate_for_match()) || !(team2->is_legitimate_for_match())) {
		return StatusType::FAILURE;
	}
	int team1_overall_score = team1->get_overall_score();
	int team2_overall_score = team2->get_overall_score();
	if (team1_overall_score == team2_overall_score) {
		team1->points = team1->points + 1;
		team2->points = team2->points + 1;
	} else if (team1_overall_score > team2_overall_score) {
		team1->points = team1->points + 3;
	} else {
		team2->points = team2->points + 3;
	}
	team1->bump_games_played();
	team2->bump_games_played();
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
	if (playerId <= 0) {
		return output_t<int>(StatusType::INVALID_INPUT)
	}
	Player* player = players_by_id.search(playerId);
	if (player == nullptr) {
		return output_t<int>(StatusType::FAILURE);
	}
	int num_of_games = player->get_total_games_played();
	// todo check syntax correctness
	return output_t<int>(num_of_games);
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	if (teamId <= 0) {
		return output_t<int>(StatusType::INVALID_INPUT)
	}
	Team* team = teams.search(teamId);
	if (team == nullptr) {
		return output_t<int>(StatusType::FAILURE);
	}
	return output_t<int>(team->points);
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
	// TODO fuck my life
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
	if (teamId == 0) {
		return output_t<int>(StatusType::INVALID_INPUT);
	}
	if (teamId > 0 ) {
		Team* team = teams.search(teamId);
		if (team == nullptr) {
			return output_t<int>(StatusType::FAILURE);
		}
		return team->top_scorrer->id;
	} else {
		return top_scorrer->id;
	}
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
	if (teamId == 0) {
		return output_t<int>(StatusType::INVALID_INPUT);
	}
	if (teamId > 0 ) {
		Team* team = teams.search(teamId);
		if (team == nullptr) {
			return output_t<int>(StatusType::FAILURE);
		}
		return output_t<int>(team->players_count);
	} else {
		return output_t<int>(players_count);
	}
	// TODO: Your code goes here ?????
//    static int i = 0;
//    return (i++==0) ? 11 : 2;
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
	if (teamId == 0 || output == nullptr) {
		return StatusType::INVALID_INPUT;
	}
	if (teamId > 0 ) {
		Team* team = teams.search(teamId);
		if (team == nullptr) {
			return StatusType::FAILURE;
		}
		team->players
	}
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
	// TODO: Your code goes here
	return 1006;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{

}

