#pragma once
// base class for drawables forces implementation of method draw() 
// We will have a vector of drawable objects in the main game loop

class drawable {
public:
	drawable();
	void draw(void* buffer);
	int x, y;
};

class board_t : drawable { // central grid with squares filled in
public:
	board_t();
};

class piece_t : drawable { // individual pieces
public:
	piece_t();
};

class queue_t : drawable { // queue is just line of pieces
public:
	queue_t();
};


class button_t : drawable {
public:
	button_t();
};