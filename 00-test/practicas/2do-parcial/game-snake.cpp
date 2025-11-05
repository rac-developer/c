#include <iostream>
#include <windows.h> // Para gotoxy, Sleep, Beep, etc.
#include <conio.h>   // Para _kbhit, _getch
#include <ctime>     // Para rand, srand

using namespace std;

// --- Constantes del Juego ---
const int ANCHO_PANTALLA = 60;
const int ALTO_PANTALLA = 20;

// --- Variables Globales del Juego ---
bool gameOver;
int snakeX, snakeY; // Posición de la cabeza
int foodX, foodY;   // Posición de la comida
int score;

// Arreglos para la cola (cuerpo)
// 100 es un tamaño máximo, la serpiente no llegará a tanto
int colaX[100], colaY[100];
int longitudCola; // Cuántos segmentos tiene actualmente

// Variable para la dirección
// Usamos un 'enum' para que el código sea más legible
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

// --- Funciones Ayudantes (las mismas del juego anterior) ---

// Mueve el cursor de la consola a la posición X, Y
void gotoxy(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
}

// Oculta el cursor parpadeante
void ocultarCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &info);
}

// --- Funciones del Juego ---

void GenerarComida() {
    // Genera comida en una posición aleatoria DENTRO del marco
    // ANCHO_PANTALLA - 2 (porque el marco está en 0 y ANCHO-1)
    foodX = (rand() % (ANCHO_PANTALLA - 2)) + 1;
    foodY = (rand() % (ALTO_PANTALLA - 2)) + 1;
    
    // Opcional: Revisar si la comida apareció sobre la serpiente
    // (Por ahora lo dejamos simple)
}

void DibujarMarco() {
    system("cls"); // Limpia la pantalla al inicio
    for (int i = 0; i < ANCHO_PANTALLA; i++) {
        gotoxy(i, 0);
        cout << "#"; // Pared superior
        gotoxy(i, ALTO_PANTALLA - 1);
        cout << "#"; // Pared inferior
    }
    for (int i = 0; i < ALTO_PANTALLA; i++) {
        gotoxy(0, i);
        cout << "#"; // Pared izquierda
        gotoxy(ANCHO_PANTALLA - 1, i);
        cout << "#"; // Pared derecha
    }
}

void Setup() {
    srand(time(NULL));
    ocultarCursor();
    
    gameOver = false;
    dir = STOP; // La serpiente empieza quieta
    
    // Posición inicial de la serpiente (en el centro)
    snakeX = ANCHO_PANTALLA / 2;
    snakeY = ALTO_PANTALLA / 2;
    
    GenerarComida(); // Pone la primera comida
    
    score = 0;
    longitudCola = 0; // Empieza sin cola
    
    DibujarMarco();
}

void Input() {
    if (_kbhit()) { // Si se presionó una tecla
        char tecla = _getch();
        
        // Cambiamos la dirección
        // (Evitamos que se mueva en reversa)
        switch (tecla) {
            case 'a':
            case 'A':
                if (dir != RIGHT) dir = LEFT;
                break;
            case 'd':
            case 'D':
                if (dir != LEFT) dir = RIGHT;
                break;
            case 'w':
            case 'W':
                if (dir != DOWN) dir = UP;
                break;
            case 's':
            case 'S':
                if (dir != UP) dir = DOWN;
                break;
            case 'x': // Tecla para salir
            case 'X':
                gameOver = true;
                break;
        }
    }
}

void Logic() {
    // --- 1. Lógica para mover la cola ---
    // Guardamos la posición de la cabeza ANTES de moverla
    int prevX = colaX[0];
    int prevY = colaY[0];
    int prev2X, prev2Y;

    // El primer segmento de la cola (cola[0]) se mueve a donde estaba la cabeza (snakeX, snakeY)
    colaX[0] = snakeX;
    colaY[0] = snakeY;

    // Bucle para que cada segmento siga al anterior
    // Empezamos en 1 (el segundo segmento)
    for (int i = 1; i < longitudCola; i++) {
        prev2X = colaX[i];
        prev2Y = colaY[i];
        colaX[i] = prevX;
        colaY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // --- 2. Mover la cabeza según la dirección ---
    switch (dir) {
        case LEFT:
            snakeX--;
            break;
        case RIGHT:
            snakeX++;
            break;
        case UP:
            snakeY--;
            break;
        case DOWN:
            snakeY++;
            break;
        case STOP:
            break; // No se mueve
    }

    // --- 3. Revisar Colisiones ---
    
    // Colisión con las paredes
    if (snakeX <= 0 || snakeX >= ANCHO_PANTALLA - 1 || snakeY <= 0 || snakeY >= ALTO_PANTALLA - 1) {
        gameOver = true;
        Beep(200, 300); // Sonido de choque
    }

    // Colisión con su propio cuerpo
    for (int i = 0; i < longitudCola; i++) {
        if (colaX[i] == snakeX && colaY[i] == snakeY) {
            gameOver = true;
            Beep(200, 300);
        }
    }

    // --- 4. Colisión con la comida ---
    if (snakeX == foodX && snakeY == foodY) {
        score += 10;
        longitudCola++; // ¡Crece!
        GenerarComida(); // Pone comida nueva
        Beep(700, 100); // Sonido de comer
    }
}

void Draw() {
    // --- 1. Dibujar Cabeza ---
    gotoxy(snakeX, snakeY);
    cout << "O"; // La cabeza

    // --- 2. Dibujar Cuerpo ---
    for (int i = 0; i < longitudCola; i++) {
        gotoxy(colaX[i], colaY[i]);
        cout << "o"; // El cuerpo
    }

    // --- 3. Dibujar Comida ---
    gotoxy(foodX, foodY);
    cout << "*"; // La comida

    // --- 4. Borrar la última pieza de la cola ---
    // Obtenemos la posición de la *última* pieza ANTES de moverla
    // (Esta es la magia para que no parpadee)
    int ultimoX = colaX[longitudCola - 1];
    int ultimoY = colaY[longitudCola - 1];
    
    // Si la longitud es > 0 Y la última pieza no es donde está la cabeza ahora
    // (Esto evita borrar la cabeza si la cola es muy corta)
    if (longitudCola > 0 && (ultimoX != snakeX || ultimoY != snakeY)) {
        gotoxy(ultimoX, ultimoY);
        cout << " "; // Borramos el último segmento
    }
    
    // --- 5. Dibujar Puntaje ---
    gotoxy(ANCHO_PANTALLA + 2, 2); // Afuera del marco
    cout << "Puntaje: " << score;
}

// --- Función Principal ---
int main() {
    Setup(); // Prepara el juego

    // --- EL BUCLE DE JUEGO (GAME LOOP) ---
    while (!gameOver) {
        // No borramos la pantalla (system("cls"))
        // Solo dibujamos lo que se mueve
        
        Draw();  // Dibuja el estado actual
        Input(); // Revisa si el jugador cambió de dirección
        Logic(); // Mueve la serpiente y revisa colisiones
        
        // Controlar la velocidad del juego
        if (dir == STOP) {
            Sleep(500); // Si está quieto, espera más
        } else {
            Sleep(100); // 100ms por "frame"
        }
    }

    // --- Fin del Juego ---
    system("cls");
    gotoxy(ANCHO_PANTALLA / 2 - 5, ALTO_PANTALLA / 2);
    cout << "GAME OVER";
    gotoxy(ANCHO_PANTALLA / 2 - 8, ALTO_PANTALLA / 2 + 1);
    cout << "Puntaje final: " << score;
    
    gotoxy(0, ALTO_PANTALLA); // Mueve el cursor al final
    
    _getch(); // Espera a que presiones una tecla para salir
    return 0;
}
