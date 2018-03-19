/*
 *GameMap class - creates the game format, with any amount of bats/pits, and player location.
 */
//Mohamed Abdi
//CSS 342
//Cygwin
//10 hours

#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <stdlib.h>
#include "room.h"
#include <iostream>
#include <string>

using namespace std;

class GameMap{
	private:
		Room ** map;
		
		int size;
		int numBats;
		int numPits;
		int numShots;
		int playerX, playerY, wumpusX, wumpusY;
		string gameOver;

		//setting up traps method.
		void settingTraps();

		//move method follows up with method movePlayer().
		void move(const int, const int);

		//bat moves player method.
		void batMovePlayer();

		//set wumpus method
		bool setWumpus(const int, const int);

		//wumpus moves method.
		void moveWumpus();
		
		//method used to for rooms BW, PW, & BP.
		int pickSituation();

		//detectMessages method follows up with method detectRooms().
		void detectMessages(const int x, const int y); 

		//shoot method follows up with method shootTheWumpus().
		void shoot(const int x, const int y);
	public:	
		//constructor and destuctor
		GameMap(int size, int numBats, int numPits, int numShots);
		virtual ~GameMap();

		//getters
		int getSize() const;
		int getNumBats() const;
		int getNumPits() const;
		int getPlayerX() const;
		int getPlayerY() const;
		string getGameStatus() const;

		//setter
		void setPlayerStart();

		//print
		void printMapAnswers() const;

		//moving methods
		void movePlayer(const char);

		//detect rooms near by player method.
		void detectRooms();

		//restarts the map
		void restartMap();

		//clears the map
		void clearMap();
		
		//shoot method.
		void shootTheWumpus(const char);

};
#endif
