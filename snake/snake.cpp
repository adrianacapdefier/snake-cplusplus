#include "snake.h"

void Snake::initBody() { //constructorul clasei care inițializează corpul șarpelui prin apelul funcției private initBody(), prin adăugarea a șase poziții în listă
	Position position;
    direction = Direction::RIGHT;
	position.currentPosition.x = SCENE_X_START + 100; //atunci cand incepe jocul, pozitia curenta a sarpelui se muta pe axa X (10) cu 100 de pixeli  
	position.currentPosition.y = SCENE_Y_START + 50;
	body.insert(body.begin(), position);
	position.currentPosition.x = SCENE_X_START + 80;
	position.currentPosition.y = SCENE_Y_START + 50;
	body.push_back(position);
	position.currentPosition.x = SCENE_X_START + 60;
	position.currentPosition.y = SCENE_Y_START + 50;
	body.push_back(position);
	position.currentPosition.x = SCENE_X_START + 40;
	position.currentPosition.y = SCENE_Y_START + 50;
	body.push_back(position);
	position.currentPosition.x = SCENE_X_START + 20;
	position.currentPosition.y = SCENE_Y_START + 50;
	body.push_back(position);
	position.currentPosition.x = SCENE_X_START;
	position.currentPosition.y = SCENE_Y_START + 50;
	body.push_back(position);
}

void Snake::move() { //mută șarpele în direcția specificată de variabila direction, folosind funcțiile private goUp(), goDown(), goRight() sau goLeft()
	switch (direction) {
	case UP: {
        goUp();
		break;
	}
	case DOWN: {
        goDown();
		break;
	}
	case RIGHT: {
        goRight();
		break;
	}
	case LEFT: {
        goLeft();
		break;
	}
	default: {
		break;
	}
	}

	auto start = std::next(body.begin(), 1);
	for (std::list<Position>::iterator it = start; it != body.end(); it++) {
		it->lastPosition = it->currentPosition;
		it->currentPosition = std::prev(it)->lastPosition;
		/*mutarea fiecărui segment al șarpelui în poziția segmentului următor în urma mutării capului șarpelui
		Pentru fiecare poziție, se actualizează ultima poziție cu valoarea curentă și se actualizează poziția curentă cu poziția ultimului element*/
	}
}

void Snake::goUp() {
    auto head = body.begin();
    int yPos;
    
    head->lastPosition = head->currentPosition;
    if (head->currentPosition.y - GRID_TILE_SIZE < SCENE_Y_START) { 
        yPos = SCENE_Y_END;
    }
    else {
        yPos = head->currentPosition.y - GRID_TILE_SIZE;
    }
    head->currentPosition.y = yPos;
}
/*schimbă poziția capului șarpelui (reprezentat prin primul element al listei body) în sus, cu o distanță egală cu dimensiunea unei celule de pe grila de joc, GRID_TILE_SIZE. Înainte de a muta capul, poziția sa curentă este salvată în lastPosition, 
apoi se verifică dacă noul yPos calculat (coordonata y a noii poziții a capului) ar ieși din zona de joc în partea de sus. Dacă da, se setează yPos la coordonata y a ultimei celule din partea de jos a zonei de joc, SCENE_Y_END. 
În caz contrar, yPos este setat la valoarea curentă a coordonatei y a capului, scazuta cu GRID_TILE_SIZE. La final, noua poziție a capului este setată pe axa y la valoarea lui yPos.*/

void Snake::goRight() {
    auto head = body.begin();
    int xPos;
    
    head->lastPosition = head->currentPosition;
    if (head->currentPosition.x + GRID_TILE_SIZE > SCENE_X_END) { 
        xPos = SCENE_X_START;
    }
    else {
        xPos = head->currentPosition.x + GRID_TILE_SIZE;
    }
    head->currentPosition.x = xPos;
}

void Snake::goDown() {
    auto head = body.begin();
    int yPos;

    head->lastPosition = head->currentPosition;
    if (head->currentPosition.y + GRID_TILE_SIZE > SCENE_Y_END) {
        yPos = SCENE_Y_START;
    }
    else {
        yPos = head->currentPosition.y + GRID_TILE_SIZE;
    }
    head->currentPosition.y = yPos;
}

void Snake::goLeft() {
    auto head = body.begin();
    int xPos;

    head->lastPosition = head->currentPosition;
    if (head->currentPosition.x - GRID_TILE_SIZE < SCENE_X_START) {
        xPos = SCENE_X_END;
    }
    else {
        xPos = head->currentPosition.x - GRID_TILE_SIZE;
    }
    head->currentPosition.x = xPos;
}

//mută capul șarpelui în direcția specificată, modificând prima poziție din listă, și actualizează pozițiile celorlalte noduri din corpul șarpelui

std::list<Position> Snake::getBody() const { //returnează o copie a listei de poziții care reprezintă corpul șarpelui
	return body;
}

Direction Snake::getDirection() const { //returnează direcția curentă a șarpelui
	return direction;
}
void Snake::setDirection(Direction direction) { //setează direcția curentă a șarpelui
	this->direction = direction;
}

void Snake::insertNode() { //adaugă un nod la sfârșitul corpului șarpelui

	Position node;

	switch (direction) {
	case UP: {
		node.currentPosition.x = body.back().currentPosition.x;
		node.currentPosition.y = body.back().currentPosition.x - GRID_TILE_SIZE;
		break;
	}
	case DOWN: {
		node.currentPosition.x = body.back().currentPosition.x;
		node.currentPosition.y = body.back().currentPosition.x + GRID_TILE_SIZE;
		break;
	}
	case RIGHT: {
		node.currentPosition.y = body.back().currentPosition.x;
		node.currentPosition.x = body.back().currentPosition.x + GRID_TILE_SIZE;
		break;
	}
	case LEFT: {
		node.currentPosition.y = body.back().currentPosition.x;
		node.currentPosition.x = body.back().currentPosition.x - GRID_TILE_SIZE;
		break;
	}

	default: {
		break;
	}
	}

	body.push_back(node);
}
