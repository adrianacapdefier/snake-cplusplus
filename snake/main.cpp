#include "game.h"

int main(int argc, const char * argv[]) { //argv=lista de linie de comandă transmise programului la lansare
    Game gameScene;
    
    gameScene.init(); //initializeaza scena jocului
    gameScene.run(); //pentru aincepe jocul si a-l mentine in executie pana cand jucatorul decide sa il opreasca sau pana cand jocul se termina.
    
    return 0;
}
