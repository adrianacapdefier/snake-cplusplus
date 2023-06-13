#include "game.h"
#include <random>

void Game::init() {
    //Create window
    window = SDL_CreateWindow( "Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN ); //se creeaza fereastra jocului primind ca paramtri: Sarpele, fereastra,lungimea si latimea
    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    pen.setRenderer(renderer); //pen-ul deseneaza cu ajutorul renderer-ului, facand referinta la acesta
    initScene();
    isQuit = false; // se verifica daca s-a apasat butonul "QUIT"; 
    sm = GameSM::STARTED; //in caz contrar jocul incepe
}

void Game::initScene() { //se initializeaza scena 
    SDL_SetRenderDrawColor( renderer, SCENE_BACKGROUND_COLOR.r, SCENE_BACKGROUND_COLOR.g, SCENE_BACKGROUND_COLOR.b, SCENE_BACKGROUND_COLOR.a ); //se alege culoarea
    SDL_RenderClear(renderer); //"sterge fereastra cu culoarea respectiva(negru)
    
    if(snake != nullptr) {
        delete snake;
    }
    if(food != nullptr) {
        delete food;
        food = nullptr;
    }
    snake = new Snake();
    score = 0;
   /*elimină vechiul șarpe și fructul
   creează un nou obiect de tip șarpe și resetează scorul
   se face pentru a reporni jocul și a asigura că toate obiectele sunt la starea lor inițială*/
}


void Game::getUserInput(SDL_Event* e, bool* quit) {
    switch( e->type ){
        case SDL_KEYDOWN: {
            
            switch(e->key.keysym.sym) {
                    
                case SDL_KeyCode::SDLK_DOWN: {
                    if(snake->getDirection() != Direction::UP) {
                        snake->setDirection(Direction::DOWN);
                    }
                    break;
                }
                    
                case SDL_KeyCode::SDLK_UP: {
                    if(snake->getDirection() != Direction::DOWN) {
                        snake->setDirection(Direction::UP);
                    }
                    break;
                }
                    
                case SDL_KeyCode::SDLK_RIGHT: {
                    if(snake->getDirection() != Direction::LEFT) {
                        snake->setDirection(Direction::RIGHT);
                    }
                    break;
                }
                    
                case SDL_KeyCode::SDLK_LEFT: {
                    if(snake->getDirection() != Direction::RIGHT) {
                        snake->setDirection(Direction::LEFT);
                    }
                    break;
                }
                    
                case SDL_KeyCode::SDLK_SPACE: {
                    if(sm != GameSM::RUNNING) {
                        initScene();
                        sm = GameSM::RUNNING;
                    }
                    break;
                }
                    
                default: {
                    break;
                }
            }
            break;
        }
        case SDL_QUIT: {
            *quit = true;
            break;
        }
        default:
            break;
    }
}
/*switch-ul verifica ce tasta a fost apasata:
cu ajutorul sagetilor, schimbam directia
space arata starile jocului: Started, Running, Stopped*/

void Game::run() {
    SDL_Event e; //Event reprezinta o tasta apasata
    int b = 0;
    int turns = SPEED_TURNS; 
    /*turns reprezinta un contor care se decrementeaza, pornind de la 5. 
    In momentul in care e 0, se executa
    Se foloseste pentru a incetini viteza*/
    
    while( isQuit == false ){ //se verifica daca s-a apasat butonul Quit
        while( SDL_PollEvent( &e ) ){
            getUserInput(&e, &isQuit);
        }
        auto a = SDL_GetTicks(); //GetTicks intoarce nr de milisecunde (1000 de milisecunde/60 fps-uri)
        auto delta = a - b;
        if (delta > FPS_CAP)
        {
            if(turns == 0) {
                switch(sm) {
                    case GameSM::STARTED: {
                        break;
                    }
                    case GameSM::RUNNING: {
                        if(checkStopCondition()) { // conditia de STOP e verifica: daca pozitia segmentului capului cu oricare alt segment din corp e aceeasi;adica se schimba State Machine
                            sm = GameSM::STOPPED;
                        }
                        else {
                            // in caz contrar:
                            checkFood(); //se verifica manacarea
                            moveSnake(); // sarpele se misca
                            generateRandomFood(); //se genereaza frunctul
                        }
                        break;
                    }
                    case GameSM::STOPPED: {
                        break;
                    }
                        
                    default:
                        break;
                }
                turns = SPEED_TURNS;
                redraw(); //redeseneaza, adica o ia de la capat;
            }
            turns--;
            b = a;
        }
    }
    //Destroy window
    SDL_DestroyWindow( window ); 
    
    //Quit SDL subsystems
    SDL_Quit(); //deinitializeaza
}

void Game::generateRandomFood() {
    if (food == nullptr) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> foodTypeDistr(0, 2); 
    // se genereaza un fruct între 0 și 2, inclusiv, pentru a alege aleatoriu tipul alimentului ce urmează a fi generat (0 pentru mere, 1 pentru portocale, 2 pentru struguri) 
        std::uniform_int_distribution<> foodPositionDistrX(60, 1200); //se genereaza pozitia fructului intre 60 si 1200 pixeli; atat sarpele, cat si fructul se afla intr-un hitbox (chenar de coliziune)
        std::uniform_int_distribution<> foodPositionDistrY(200, 650);
        auto type = foodTypeDistr(gen);
        auto xPos = foodPositionDistrX(gen);
        auto yPos = foodPositionDistrY(gen);
        bool collision = false;
        auto body = snake->getBody();
        
        auto head = body.front();
        auto tail = body.back();
        
        if ((tail.currentPosition.x - FRUIT_HITBOX >= xPos  && head.currentPosition.x + FRUIT_HITBOX <= xPos) &&
            (tail.currentPosition.y - FRUIT_HITBOX >= yPos && head.currentPosition.y + FRUIT_HITBOX <= yPos)) {
            collision = true;
        }
        /*se verifica daca hitbox-ul sarpelui a fost plasat peste hitbox-ul fructului
        in caz afirmativ, are loc o coliziune si nu se mai genereaza fructul*/
        
        if(collision == false) { //0, 1 ,2-generare aleatorie
            switch (type) {
                case 0: {
                    food = new Apple();
                    break;
                }
                case 1: {
                    food = new Orange();
                    break;
                }
                case 2: {
                    food = new Grapes();
                    break;
                }
                default: {
                    break;
                }
            }
            Point2D position = { xPos, yPos };
            food->setPosition(position); //se seteaza pozitia
        }
    }
}

bool Game::checkStopCondition() {
    auto body = snake->getBody();
    auto head = body.begin();
    
    for (auto it = std::next(body.begin()); it != body.end(); it++) {
        if (it->currentPosition.x == head->currentPosition.x &&
            it->currentPosition.y == head->currentPosition.y) {
            return true;
        }
    }
    //conditia de STOP e verifica: daca pozitia segmentului capului cu oricare alt segment din corp e aceeasi;adica se schimba State Machine
    return false;
}


void Game::moveSnake() {
    snake->move();
}

void Game::checkFood() {
    if (food != nullptr) {
        Position head = snake->getBody().front();
        Point2D foodPos = food->getPosition();
        int xFoodRangeStart = foodPos.x - FRUIT_HITBOX;
        int xFoodRangeEnd = foodPos.x + FRUIT_SIZE + FRUIT_HITBOX;
        int yFoodRangeStart = foodPos.y - FRUIT_HITBOX;
        int yFoodRangeEnd = foodPos.y + FRUIT_SIZE + FRUIT_HITBOX;
        
        if ((head.currentPosition.x >= xFoodRangeStart && head.currentPosition.x <= xFoodRangeEnd) &&
            (head.currentPosition.y >= yFoodRangeStart && head.currentPosition.y <= yFoodRangeEnd)) {
            score += food->score();
            delete food;
            food = nullptr;
            snake->insertNode();
        }
    } 
    /* se verifica daca hitbox-ul sarpelui "a intrat in hitbox-ul fructului (daca l-a mancat)
    in caz afrimativ, se incrementeaza scorul
    se dealoca fructul
    si se adauga un segment la coada sarpelui; fiecare segment din sarpe are referinta la cap*/
}

void Game::redraw() { //se redeseneaza scena initiala
    SDL_SetRenderDrawColor( renderer, SCENE_BACKGROUND_COLOR.r, SCENE_BACKGROUND_COLOR.g, SCENE_BACKGROUND_COLOR.b, SCENE_BACKGROUND_COLOR.a );
    SDL_RenderClear(renderer);
    
    switch(sm) {
        case GameSM::STARTED: {
            pen.drawStartView(); // in cazul in care jocul a inceput, se deseneaza scena initiala
            break;
        }
        case GameSM::RUNNING: { //in desfasurarea jocului
            pen.drawSnake(snake->getBody()); //se deseneaza corpul sarpelui
            pen.drawText("Score: " + std::to_string(score), SCORE_TEXT_COLOR, {16, 16}, {64, TEXT_FONT_NORMAL}); //se afiseaza scorul, cu culoarea, fontul, date cu ajutorul renderer-ului
            if(food != nullptr) { // se verifică dacă fructul a fost alocat în memorie, înainte de a încerca să o acceseze sau să o șteargă. În cazul în care aceasta este nullptr, se evită orice acțiune cu această variabilă pentru a preveni erori de execuție.
                pen.drawFruit(food->type(), food->getPosition());
            }
            break;
        }
        case GameSM::STOPPED: { // in cazul in care jocul s-a terminat
            pen.drawText("Your score is: " + std::to_string(score), SCORE_TEXT_COLOR, {570, WINDOW_HEIGHT/ 2}, {120, TEXT_FONT_NORMAL}); //se afiseaza scorul
            pen.drawText("Press SPACE to play again", START_TEXT_COLOR, {550, WINDOW_HEIGHT/ 2 + 30}, {164, TEXT_FONT_NORMAL}); //si textul aferent opririi jocului:"Press SPACE to play again"
            break;
        }
    }
    SDL_RenderPresent(renderer);
}
