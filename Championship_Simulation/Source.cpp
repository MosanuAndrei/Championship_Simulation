#include<iostream>
#include<cstdlib>
#include<fstream>

using namespace std;

struct Match {
	int host_goals;
	int guest_goals;
};

struct Team {
	string name;
	int points;
	Team* next;
};

void add_team(Team* &head,string name,int points) {
	//This function inserts a new 'Team' in the linked list by creating a structure called new_team, adding values to
	//the respective variables and linking it to the last element in the list using a loop

	Team* new_team = new Team;
	new_team->name = name;
	new_team->points = points;
	new_team->next = nullptr;

	if (head == NULL) {
		head = new_team;
	}
	else {
		Team* current_team = head;
		while (current_team->next != nullptr) {
			current_team = current_team->next;
		}
		current_team->next = new_team;
	}
}

void show_teams(Team* head) {
	while (head != nullptr) {
		cout << head->name << " with " << head->points << " points" << endl;
		head = head->next;
	}
}

void disqualify_teams(Team* &head, int points) {
	//This function has the role to delete all the elements from the linked list that are smaller than a specific number

	while (head->points < points) {
		Team* victim = head;
		head = head->next;
		delete victim;
	}

	Team* elem = head,*prev = nullptr;
	while ( elem->next != nullptr) {
		if (elem->points >= points) {
			prev = elem;
			elem = elem->next;
		}
		else if (elem->points < points) {
			if (elem->next == nullptr) {
				prev->next = nullptr;
			}
			else {
				Team* victim = elem;
				prev->next = prev->next->next;
				elem = elem->next;
				delete victim;
			}
		}
	}
}

int get_minimum_points(int n,int points[]) {
	//This function uses the 'points' array in order to get the average score in the championship and
	//than giving it to 'disqualify_teams' function

	int min_val;
	int sum=0;
	for (int i = 0; i < n; i++) {
			sum += points[i];
	}
	min_val = sum / n;
	
	return min_val;
}

void bubblesort(string team_names[], int points[], int n) {
	int aux;
	string aux2;
	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (points[j] < points[j+1]) {
				aux = points[j];
				points[j] = points[j + 1];
				points[j + 1] = aux;
				aux2 = team_names[j];
				team_names[j] = team_names[j + 1];
				team_names[j + 1] = aux2;
			}
		}
	}
}

void simulate_matches(Match match[][20],int* points,int n, string team_names[]) {
	//This function has the role of simulating matches between the teams, each team will
	//battle 2 times with the other teams, one time being the host and the other being the guest
	//the scores are random and since a team cannot fight herself the primary diagonale of the 2d array will be represented by -1
	//the function also assigns points for the teams based on their performance: +3 if they win, +1 for both if they draw
	//and +0 when they lose after witch the 2d array is displayed in the console

	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i != j) {
				match[i][j].host_goals = rand() % 8;
				match[i][j].guest_goals = rand() % 8;
			}
			else {
				match[i][j].host_goals = -1;
				match[i][j].guest_goals = -1;
			}
		}
	}

	for (i = 0; i < n; i++) {
		points[i] = 0;
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (match[i][j].host_goals < match[i][j].guest_goals)
			{
				points[j] += 3;
			}
			else if (match[i][j].host_goals > match[i][j].guest_goals)
			{
				points[i] += 3;
			}
			else if (match[i][j].host_goals == -1 && match[i][j].guest_goals == -1) {
				points[i] += 0;
				points[j] += 0;
			}
			else {
				points[i]++;
				points[j]++;
			}
		}
	}
	for (i = 0; i < n; i++)
	{
		cout << team_names[i] << " |";
		for (j = 0; j < n; j++) {
			cout<< match[i][j].host_goals << " - ";
			cout << match[i][j].guest_goals;
			cout << " |";
		}
		cout << endl;
	}
	cout<<endl<<"In this Championship the teams get 3 points for a win, 1 point each for a draw and 0 points for a loss!" << endl<<endl;
	cout << "The results are:" << endl<<endl;
}

int main() {
	Match match[20][20];
	Match(*pm)[20] = match;
	int i, n, points[20], * pp = &points[0];
	string team_names[16];

	cout << "=======================================================================" << endl;
	cout << "             Welcome to our Soccer Championship Simulation"<<endl<<endl;

	cout << "How many teams would you like to compete in this Championship?"<<endl;
	cin >> n;
	while (n < 2 || n>16) {
		if (n < 2) {
			cout << "You need at least 2 teams dummy!" << endl;
		}
		if (n > 16) {
			cout << "We are sorry but our Championship can only host 16 teams!" << endl;
		}
		cout<<endl << "Please try again"<<endl;
		cin >> n;
	}
	cout << "Excellent choice!"<<endl<<endl;
	cout << "Now we need you to nominate witch teams are going to participate in this Championship" << endl;
	for (i = 0; i < n; i++) {
		cout << "Team " << i + 1 << " : ";
		cin >> team_names[i];
	}

	cout << endl << endl << "And here are the matches!" << endl;
	simulate_matches(pm, pp, n, team_names);

	Team* head_team = nullptr;
	for (i = 0; i < n; i++) {
		add_team(head_team, team_names[i], points[i]);
	}

	show_teams(head_team);
	cout << endl;
	int min_points = get_minimum_points(n,points);
	cout << endl<<min_points << endl;
	cout << "The following teams have scored higher than the average and are eligible for the prize pool:"<<endl;
	disqualify_teams(head_team, min_points);
	show_teams(head_team);

	cout<<endl<<"The Championship leaderboard stands as follows:" << endl;
	bubblesort(team_names, points, n);
	for (int i = 0; i < n; i++) {
		cout << i + 1 << ". " << team_names[i]<< endl;
	}

	cout << endl << "Thank you for participating in our simulation, have a nice day!" << endl;
	cout << "=======================================================================" << endl;

	return 0;
}