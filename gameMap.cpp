/*
 *GameMap class - creates the game format and handle the game logic.
 */
//Mohamed Abdi
//CSS 342
//Cygwin
//10 hours

#include "room.h"
#include "gameMap.h"
#include <cstdlib>

using namespace std;

////////////////////////////
//GameMap class
///////////////////////////

//constructor
GameMap:: GameMap(const int size, const int numBats, const int numPits, const int numShots)
{
	this->gameOver = "";
	this->size = size;
	this->numBats = numBats;
	this->numPits = numPits;
	this->numShots = numShots;
	this->map = NULL;
}

//destructor
GameMap::~GameMap()
{
}

//clears the map.
void GameMap:: clearMap()
{
	for(int i=0; i<this->size; i++)
	{
		delete [] map[i];
	}
	delete [] map;
	this->map = NULL;
}

//restarts the map
void GameMap:: restartMap()
{
	map = new Room*[this->size]; //creating array.
	for(int i=0; i<this->size; i++) 
		map[i] = new Room[this->size];
	settingTraps();
	map[size-1][size-1].clearStatic();
}


//return the game map size.
int GameMap:: getSize() const
{
	return size;
}

//returns the number of bats.
int GameMap:: getNumBats() const
{
	return numBats;
}

//returns player's x cooridinate
int GameMap:: getPlayerX() const
{
	return playerX;
}

//returns player's y cooridinate.
int GameMap:: getPlayerY() const
{
	return playerY;
}

//returns a string with the status of the game.
string GameMap:: getGameStatus() const
{
	return gameOver;
}

//sets the players cooridnate at a random location that does not have a bat, wumpus, or pit.
void GameMap:: setPlayerStart()
{
	this->playerX = rand() % size;
	this->playerY = rand() % size;
	while(map[playerY][playerX].getRoomInfo() == "B" || map[playerY][playerX].getRoomInfo() == "P" 
			|| map[playerY][playerX].getRoomInfo() == "W")
	{
		playerX = rand() % size;
		playerY = rand() % size;
	}
	map[playerY][playerX].setRoomType("*");
}

//prints out the game map with player, playerfootsteps, bat(s), Pit(s), and wampus location.
void GameMap:: printMapAnswers() const
{
	cout << endl;
	cout << "Cheat map: " << endl;
	cout << "Keys: * - player, (1-64) - room numbers, B - bats, P - pits, W - wumpus" << endl;
	cout << "BW - bat and wumpus, PW - pit and wumpus, BP - bat & pit"<< endl;
	cout << endl;
	for(int i=0; i<size; i++)
	{
		for(int j= 0; j<size; j++)
		{
			cout << "|" << map[j][i].getRoomInfo();
			if(map[j][i].getRoomInfo().length() == 1) cout << " ";
			if(j==size-1) cout << "|";
		}
		cout<<endl;
	}
}

//set the wumpus in the game.
bool GameMap:: setWumpus(const int x, const int y)
{
	if(map[y][x].getRoomInfo() != "*")
	{	
		if(map[y][x].getRoomInfo() == "B")
		{
			map[y][x].setRoomType("BW");
		}else if(map[y][x].getRoomInfo() == "P")
		{
			map[y][x].setRoomType("PW");
		}else map[y][x].setRoomType("W");
		this->wumpusX = x;
		this->wumpusY = y;
		return true;
	}
	return false;
}

//Sets up and positions the bat(s), pit(s), and wampus.
void GameMap:: settingTraps()
{
	int batX, batY;
	//setting up bats.
	for(int i=0; i<numBats;) 
	{
		batX = rand() % size;
		batY = rand() % size;
		if(map[batX][batY].getRoomInfo() != "B")
		{
			map[batX][batY].setRoomType("B");
			i++;
		}
	}
	int pitX, pitY; //pit x & y cooridnate
	//setting up pits.
	for(int i=0; i<numPits;) 
	{
		pitX = rand() % size;
		pitY = rand() % size;
		if(map[pitX][pitY].getRoomInfo() != "P")
		{
			if(map[pitX][pitY].getRoomInfo() == "B"){
				map[pitX][pitY].setRoomType("BP");
			}else {
				map[pitX][pitY].setRoomType("P");
			}
			i++;
		}
	}
	int wumX = rand() % size; //wumpus x-corridnate
	int wumY = rand() % size; //wumpus y-corridnate
	while(map[wumY][wumX].getRoomInfo() == "*")
	{
		wumX = rand() % size; //wumpus x-corridnate
		wumY = rand() % size; //wumpus y-corridnate
	}
	setWumpus(wumX, wumY);
}

//prints out the messages about the info of the rooms near by the player
void GameMap:: detectMessages(const int x,  const int y)
{
	if(map[y][x].getRoomInfo() == "BW"){
		cout << "\tYou hear a bat in the distance." << endl;
		cout << "\tYou smell something very awful near by." << endl;
	}else if(map[y][x].getRoomInfo() == "BP"){
		cout << "\tYou hear a bat in the distance." << endl;
		cout << "\tYou feel a draft." << endl;
	}else if(map[y][x].getRoomInfo() == "PW") {
		cout << "\tYou feel a draft." << endl;
		cout << "\tYou smell something very awful near by." << endl;
	}else if(map[y][x].getRoomInfo() == "W") {
		cout << "\tYou smell something very awful near by." << endl;
	}else if(map[y][x].getRoomInfo() == "B") {
		cout << "\tYou hear a bat in the distance." << endl;
	}else if(map[y][x].getRoomInfo() == "P"){
		cout << "\tYou feel a draft." << endl;
	}
}

//This method detects the rooms near by players and prints out whats the player is near by.
void GameMap:: detectRooms()
{
	cout << "----------------------------------------------------------" << endl;
	string whatsInNextRoom = "n"; //n stands for nothing.
	//if player is in the corners of the map and near 2 rooms.
	if((playerX == 0 && playerY == 0)) { 
		detectMessages(playerX+1, playerY); //down
		detectMessages(playerX, playerY+1); //right
	}else if((playerX == 0 && playerY == size-1)) { 
		detectMessages(playerX+1, playerY); //down
		detectMessages(playerX, playerY-1); //left
	}else if((playerX == size-1 && playerY == 0)) {
	       detectMessages(playerX-1, playerY); //up
	       detectMessages(playerX, playerY+1); //right	
	}else if((playerX == size-1 && playerY == size-1)) { 
		detectMessages(playerX-1, playerY); //up.
		detectMessages(playerX, playerY+1); //left.
	}
	//if player is on the sides of the map and near 3 rooms.
	else if(playerX == size-1 && playerY > 0) { //bottum side of map.
		detectMessages(playerX, playerY-1); //left.
		detectMessages(playerX-1, playerY); //up
		detectMessages(playerX, playerY+1); //right
	}else if(playerX >0 && playerY == size-1) { //right side of map.
		detectMessages(playerX, playerY-1); //left.
		detectMessages(playerX+1, playerY); //down
		detectMessages(playerX-1, playerY); //up
	}else  if(playerX == 0 && playerY > 0) { //top side of map
		detectMessages(playerX, playerY-1); //left
		detectMessages(playerX, playerY+1); //right
		detectMessages(playerX+1, playerY); //down	
	}else  if(playerX > 0 && playerY == 0) { //left side of map.
		detectMessages(playerX, playerY+1); //right
		detectMessages(playerX+1, playerY); //down	
		detectMessages(playerX-1, playerY); //up.
	}
	//if player is near 4 rooms
	else{
		detectMessages(playerX-1, playerY); //up
		detectMessages(playerX, playerY+1); //right
		detectMessages(playerX+1, playerY); //down	
		detectMessages(playerX, playerY-1); //left.
	}
	cout << "----------------------------------------------------------" << endl;
}

//the bat moves the player at a random location then the bat goes to a random location also.
void GameMap:: batMovePlayer()
{
	cout << "\tsomething is in the room.....its a bat!" << endl;
	//sets previous room to footsteps.
	map[playerY][playerX].setRoomType(".");
	//moves player
	cout << "\tThe Bat has pick you up." << endl;
	this->playerX = rand() % size;
	this->playerY = rand() % size;
	if(map[playerY][playerX].getRoomInfo() == "P") //if player ends up in the pit
	{
		cout << "\tThe bat dropped you into the pit of death." << endl;
		gameOver = "game over!";
	}else if(map[playerY][playerX].getRoomInfo() == "W") //if player end up a room with wumpus.
	{
		cout<< "\tThe bat has dropped you in a strange room.." << endl;
		cout<< "\tYou hear a loud noise... it's the Wumpus!" << endl;
		gameOver = "game over!";
	}else
	{
		if(map[playerY][playerX].getRoomInfo() == ".") cout << "\tYou see footprints in the dust." << endl;
		else cout << "\tIt dropped you in a new room." << endl;
		//so player doesn't land on another bat and gets replaced
		while(map[playerY][playerX].getRoomInfo() == "B") 
		{
			playerX = rand() % size;
			playerY = rand() % size;
		}
		map[playerY][playerX].setRoomType("*");
		//moves the bat at a random location.
		int batX = rand() % size;
		int batY = rand() % size;
		while(map[batY][batX].getRoomInfo() == "B"||map[batY][batX].getRoomInfo() == "*"||map[batY][batX].getRoomInfo() == "BP"
				||map[batY][batX].getRoomInfo() == "BW"||map[batY][batX].getRoomInfo() == "PW")
		{
			batX = rand() % size;
			batY = rand() % size;
		}
		if(map[batY][batX].getRoomInfo() == "W") map[batY][batX].setRoomType("BW");
		else if(map[batY][batX].getRoomInfo() == "P") map[batY][batX].setRoomType("BW");
		else map[batY][batX].setRoomType("B");
	}
}
//returns either 0 or 1 on a 50% chance.
int GameMap:: pickSituation()
{
	int num = rand() % 100 + 1;//1 to 100
	if(num > 50) return 1;
	return 0;
}

//moves the player and replaces the room it moved from with footsteps.
//also the method has some condition such as out of bound, moving to a bat/pit/wumpus.
void GameMap:: move(const int x, const int y)
{
	int num = pickSituation(); //used for only rooms BW, PW, BP.
	if(map[y][x].getRoomInfo() == "B") //if has a bat
	{
		map[y][x].setRoomType("."); //sets the room to footsteps.
		batMovePlayer();
	}else if(map[y][x].getRoomInfo() == "P") //if has a pit
	{
		cout << "\tyou have walked into the pit of death!" << endl;
		gameOver = "game over!";
	}else if(map[y][x].getRoomInfo() == "W") //if has a wumpus
	{
		cout << "\tyou have walked into a strange room..." << endl;
		cout << "\tYou heard a loud noise... it's the Wumpus!" << endl;
		gameOver = "game over!";
	}else if(map[y][x].getRoomInfo() == "BW") //bat and wumpus
	{
		if(num == 1) batMovePlayer();
		else {
			cout << "\tyou have walked into a strange room..." << endl;
			cout << "\tYou heard a loud noise... it's the Wumpus!" << endl;
			gameOver = "game over!";	
		}

	}else if(map[y][x].getRoomInfo() == "PW") //pit and wumpus
	{
		if(num == 1) cout << "\tyou have walked into the pit of death!" << endl;
		else {
			cout << "\tyou have walked into a strange room..." << endl;
			cout << "\tyou heard a loud noise... it's the Wumpus!" << endl;
		}
		gameOver = "game over!";
	}else if(map[y][x].getRoomInfo() == "BP") //bat and pit
	{
		if(num == 1) batMovePlayer();
		else {
			cout << "\tyou have walked into the pit of death!" << endl;
			gameOver = "game over!";	
		}

	}else if(map[y][x].getRoomInfo() == ".") //if a previous room
	{
		map[playerY][playerX].setRoomType("."); //sets previous room to footsteps.
		cout << "\tyou see footprints in the dust." << endl;
		this->playerX = x;
		this->playerY = y;
	       	map[y][x].setRoomType("*");
	}else {
		map[playerY][playerX].setRoomType(".");//sets previous room to footsteps.
		cout << "\tyou walked into a new room." << endl;
		this->playerX = x;
		this->playerY = y;
		map[y][x].setRoomType("*");
	}
}

//moves the player but there's a limited place the player can go to.
void GameMap:: movePlayer(const char key) 
{
	cout << "what happened? " << endl;
	cout << "----------------------------------------------------------" << endl;
	switch(key)
	{
		case 'j': //left
			if(playerY-1 < 0) cout << "\tPlayer pathway to west is blocked." << endl;
			else move(playerX, playerY-1);
			break;
		case 'k': //down
			if(playerX+1 >= size) cout << "\tPlayer pathway to south is blocked." << endl;
			else move(playerX+1, playerY);
			break;
		case 'i': //up
			if(playerX-1 < 0) cout << "\tPlayer pathway to north is blocked." << endl;
			else move(playerX-1, playerY);
			break;
		case 'l': //right
			if(playerY+1 >= size) cout << "\tPlayer pathway to east is blocked." << endl;
			else move(playerX, playerY+1);
			break;
	}
	cout << "----------------------------------------------------------" << endl;
}
//Wumpus will move depending by the amount of rooms near it. It will have a 40% chance for 2 rooms,
//60% chance for 3 rooms, and 80% chance for 4 rooms to move.
void GameMap:: moveWumpus() 
{
	int orginalWumpX = wumpusX;
	int orginalWumpY = wumpusY;
	bool hasMoved = true;
	int num = rand() % 100+1;
	//if wumpus at corners of the map.
	if((wumpusX == 0 && wumpusY == 0)) { //has 40% chance of moving
		if(num <= 20) { //20% to move down.
			hasMoved = setWumpus(wumpusX+1, wumpusY);
		}else if(num > 20 && num <=41) { //20% to move right.
			hasMoved =setWumpus(wumpusX, wumpusY+1);
		}else hasMoved = false;
	}else if((wumpusX == 0 && wumpusY == size-1)) { //has 40% chance of moving
		if(num <= 20) { //20% to move down.
			hasMoved = setWumpus(wumpusX+1, wumpusY);	
		}else if(num > 20 && num <=41) { //20% to move left.
			hasMoved = setWumpus(wumpusX, wumpusY-1);
		}else hasMoved = false;
	}else if((wumpusX == size-1 && wumpusY == 0)) { //has 40% chance of moving
		if(num <= 20) { //20% to move up.
			hasMoved = setWumpus(wumpusX-1, wumpusY);	
		}else if(num > 20 && num <=41) { //20% to move right.
			hasMoved = setWumpus(wumpusX, wumpusY+1);
		}else hasMoved = false;	
	}else if((wumpusX == size-1 && wumpusY == size-1)) { //has 40% chance of moving
		if(num <= 20) { //20% to move up.
			hasMoved = setWumpus(wumpusX-1, wumpusY);	
		}else if(num > 20 && num <=41) { //20% to move left.
			hasMoved = setWumpus(wumpusX, wumpusY-1);
		}else hasMoved = false;
	}
	//if wumpus is on the sides of maps (not the corners).
	else if(wumpusX == size-1 && wumpusY > 0) { //bottom side. 60% chance of moving
		if(num <= 20) { //20% to move left.
			hasMoved = setWumpus(wumpusX, wumpusY-1);
		}else if(num > 20 && num <=41) { //20% to move right.
			hasMoved = setWumpus(wumpusX, wumpusY+1);
		}else if(num > 41 && num <= 62) { //20% to move up.
			hasMoved = setWumpus(wumpusX-1, wumpusY);
		}else hasMoved = false;
	}else if(wumpusX > 0 && wumpusY == size-1) { //right side. 60% chance of moving
		if(num <= 20) { //20% to move left.
			hasMoved = setWumpus(wumpusX, wumpusY-1);
		}else if(num > 20 && num <=41) { //20% to move down.
			setWumpus(wumpusX+1, wumpusY);
		}else if(num > 41 && num <= 62) { //20% to move up.
			hasMoved = setWumpus(wumpusX-1, wumpusY);
		}else hasMoved = false;
	}else if(wumpusX == 0 && wumpusY > 0) { //top side. 60% chance of moving
		if(num <= 20) { //20% to move down.
			hasMoved = setWumpus(wumpusX+1, wumpusY);	
		}else if(num > 20 && num <=41) { //20% to move right.
			hasMoved = setWumpus(wumpusX, wumpusY+1);
		}else if(num > 41 && num <= 62) { //20% to move left.
			hasMoved = setWumpus(wumpusX-1, wumpusY);
		}else hasMoved = false;
	}else if(wumpusX > 0 && wumpusY == 0) { //left side. 60% chance of moving
		if(num <= 20) { //20% to move right.
			hasMoved = setWumpus(wumpusX, wumpusY+1);
		}else if(num > 20 && num <=41) { //20% to move down.
			hasMoved = setWumpus(wumpusX+1, wumpusY);
		}else if(num > 41 && num <= 62) { //20% to move up.
			hasMoved =setWumpus(wumpusX-1, wumpusY);
		}else hasMoved = false;
	}
	//if wumpus is near 4 rooms on the map then has a 80% chance to move.
	else if(num <= 20) setWumpus(wumpusX-1, wumpusY); //20 % chance to moves up
	else if(num > 20 && num <= 41) setWumpus(wumpusX+1, wumpusY); //20% chance to moves down
	else if(num > 41 && num <= 62) setWumpus(wumpusX, wumpusY-1); //20% chance to moves left
	else if(num > 62 && num <= 83) setWumpus(wumpusX, wumpusY+1); //20% chance to moves right
	else hasMoved = false; //if it has not moved at all it does not change nothing.
	//changes the rooms that the wumpus might've been in.
	if(hasMoved) {
		if(map[orginalWumpY][orginalWumpX].getRoomInfo() == "BW") map[orginalWumpY][orginalWumpX].setRoomType("B");
		else if (map[orginalWumpY][orginalWumpX].getRoomInfo() == "PW") map[orginalWumpY][orginalWumpX].setRoomType("P");
		else {
			int roomID = map[orginalWumpY][orginalWumpX].getRoomID();
			map[orginalWumpY][orginalWumpX].setRoomType(to_string(roomID));
		}
	}
}

//if have the right cooridantes where the wumpus is at player win. if not then wumpus moves.
void GameMap:: shoot(const int x, const int y)
{
	if(map[y][x].getRoomInfo() == "W" || map[y][x].getRoomInfo() == "BW" || map[y][x].getRoomInfo() == "PW")
	{
		gameOver = "You've defeated the wumpus! good job!";
	}else {
		numShots--;
		moveWumpus();
	}
}

//Gets the key from the parameter and uses it to choose where shoot the arrow.
void GameMap:: shootTheWumpus(const char key) 
{
	switch(key)
	{
		case 'J': //left
			if(playerY-1 < 0) numShots--;
			else shoot(playerX, playerY-1);
			break;
		case 'K': //down
			if(playerX+1 >= 0) numShots--;
			else shoot(playerX, playerY-1);
			break;
		case 'I': //up
			if(playerX-1 < 0) numShots--;
			else shoot(playerX-1, playerY);
			break;
		case 'L': //right
			if(playerY+1 >= size) numShots--;
			else shoot(playerX, playerY+1);
			break;
	}
	if(numShots == 0) gameOver = "game over!";
	if(gameOver[0] != 'Y') {
		cout << "Arrows remaining: " << endl;
		cout << "----------------------------------------------------------" << endl;
		cout << "\tyou have " << numShots << " remaining." << endl;
		cout << "----------------------------------------------------------" << endl;
	}
}
