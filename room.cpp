//Mohamed Abdi
//CSS 342
//Cygwin
//10 hours

#include "room.h"
#include <stdlib.h>
#include <stdexcept>

using namespace std;
////////////////////////
//Room Class
////////////////////////

//static variable.
int Room:: totalRooms = 0;

//constructor
Room:: Room()
{
	totalRooms++;
	this->roomType = emptyRoom; //set roomType to empty.
	id = totalRooms;
	roomType = to_string(totalRooms);

}

//constructor with parameter which is the roomType.
Room::Room(const string roomType)
{
	setRoomType(roomType);
}

//destuctor
Room:: ~Room()
{
}

//Sets the room type.
void Room:: setRoomType(const string roomType) 
{
	if(roomTypeCorrect(roomType))
	{
		this->roomType = roomType;

	}else throw logic_error("wrong room type!");
}

//returns the room type info.
string Room:: getRoomInfo() const
{
	return roomType;
}

int Room:: getRoomID() const
{
	return id;
}

//return the true or false depending if the room type is correct.
bool Room:: roomTypeCorrect(const string roomType)
{
	if(roomType == this->emptyRoom) return true;
	else if(roomType == this->player) return true;
	else if(roomType == footsteps) return true;
	else if(roomType == deathPit) return true;
	else if(roomType == bat) return true;
	else if(roomType == wumpus) return true;
	else if(roomType == batAWumpus) return true;
	else if(roomType == pitAWumpus) return true;
	else if(roomType == batAPit) return true;
	else if(roomType == to_string(id)) return true;
	return false;
}

//this clears static value to it stops adding on room numbers
void Room:: clearStatic()
{
	this->totalRooms = 0;
}

