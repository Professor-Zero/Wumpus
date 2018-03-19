/*
 *Room class - defines a room and the room can contain different things in it.
 * A room can contain a player, player's footsteps, death pit, bat, and wumpus.
 */

//Mohamed Abdi
//CSS 342
//Cygwin
//10 hours

#ifndef ROOM_H
#define ROOM_H

#include <stdlib.h>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Room 
{
	private:
		static int totalRooms;
		string roomType;
		int id;
		string emptyRoom = " ";
		bool roomTypeCorrect(const string roomType);
	public:
		const string player = "*";
		const string footsteps = ".";
		const string deathPit = "P";
		const string bat = "B"; 
		const string wumpus = "W";
		const string batAWumpus = "BW";
		const string batAPit = "BP";
		const string pitAWumpus = "PW";

		//constructor & destructor.
		Room();
		Room(const string roomType);
		virtual ~Room();
		
		//setter
		void setRoomType(const string roomType);
		
		//getter.
		string getRoomInfo() const;
		int getRoomID() const;

		//clear static method
		void clearStatic();


};
#endif
