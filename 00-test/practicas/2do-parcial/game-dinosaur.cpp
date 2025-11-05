#include <iostream>
#include <windows.h> // Para Sleep, Beep, y mover el cursor
#include <conio.h>   // Para _kbhit y _getch (entrada sin pausa)
#include <ctime>     // Para números aleatorios (rand)

using namespace std;

// --- Constantes del Juego (Variables que no cambian) ---
// El 'ancho' y 'alto' de nuestra área de juego en la consola
const int ANCHO_PANTALLA = 50;
const int ALTO_PANTALLA = 20;
// La posición Y (vertical) donde estará el suelo
const int POS_SUELO = 18;


// --- Funciones Ayudantes (Herramientas) ---

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

// --- Variables Globales del Juego ---
// (Las ponemos aquí para que todas las funciones puedan usarlas)

bool gameOver = false;
int puntaje = 0;

// Posición del Dinosaurio
int dinoX = 5;
int dinoY = POS_SUELO;

// Variables para el salto
bool estaSaltando = false;
int velocidadSalto = 0; // Qué tan rápido sube o baja
const int FUERZA_SALTO = -4; // Impulso inicial (negativo porque 'Y' 0 es arriba)
const int GRAVEDAD = 1;      // Cuánto "tira" hacia abajo en cada frame

// Posición del Obstáculo (Cactus)
int cactusX = ANCHO_PANTALLA - 10; // Empieza a la derecha
int cactusY = POS_SUELO;


// --- Funciones de Dibujo ---

void dibujarSuelo() {
    for (int i = 0; i < ANCHO_PANTALLA - 1; ++i) {
        gotoxy(i, POS_SUELO + 1); // Dibuja una línea de '_'
        cout << "_";
    }
}

// Dibuja el dinosaurio en su posición actual
void dibujarDino() {
    gotoxy(dinoX, dinoY);
    cout << "R"; // 'R' se parece un poco a un T-Rex :)
}

// Dibuja el cactus en su posición actual
void dibujarCactus() {
    gotoxy(cactusX, cactusY);
    cout << "T"; // 'T' parece un cactus
}

// Borra el dinosaurio de su posición ANTERIOR
void borrarDino() {
    gotoxy(dinoX, dinoY);
    cout << " ";
}

// Borra el cactus de su posición ANTERIOR
void borrarCactus() {
    gotoxy(cactusX, cactusY);
    cout << " ";
}


// --- Funciones de Lógica del Juego ---

void procesarInput() {
    // _kbhit() (de conio.h) revisa si se presionó una tecla
    // ¡Pero no detiene el programa!
    if (_kbhit()) {
        char tecla = _getch(); // Obtenemos la tecla
        
        // Si fue 'espacio' Y no está saltando
        if (tecla == ' ' && !estaSaltando) {
            estaSaltando = true;
            velocidadSalto = FUERZA_SALTO; // Le da el impulso inicial
            Beep(600, 100); // Sonido de salto (¡tu petición!)
        }
    }
}

void actualizarLogica() {
    // 1. Mover el Cactus
    cactusX = cactusX - 1; // Mueve 1 espacio a la izquierda

    // Si el cactus salió de la pantalla
    if (cactusX < 0) {
        cactusX = ANCHO_PANTALLA - 10; // Lo reinicia a la derecha
        puntaje++; // ¡Ganas un punto!
        
        // (Opcional: hacer que vaya más rápido cada 5 puntos)
        // if (puntaje % 5 == 0) velocidadJuego -= 5;
    }

    // 2. Física del Salto
    if (estaSaltando) {
        dinoY = dinoY + velocidadSalto; // Mueve el dino verticalmente
        velocidadSalto = velocidadSalto + GRAVEDAD; // La gravedad lo frena y luego lo baja

        // Si el dino aterriza en el suelo
        if (dinoY >= POS_SUELO) {
            dinoY = POS_SUELO; // Lo "clava" al suelo
            estaSaltando = false;
        }
    }

    // 3. Revisar Colisión (Choque)
    if (dinoX == cactusX && dinoY == cactusY) {
        gameOver = true;
        Beep(200, 500); // Sonido de Game Over (más grave)
    }
}

void dibujarFrame() {
    // Dibuja los elementos en sus NUEVAS posiciones
    dibujarDino();
    dibujarCactus();

    // Dibuja el puntaje
    gotoxy(ANCHO_PANTALLA - 20, 2); // Arriba a la derecha
    cout << "Puntaje: " << puntaje;
}

// --- Función Principal ---

int main() {
    srand(time(NULL)); // Inicializar generador aleatorio (para futuros obstáculos)
    ocultarCursor();   // Esconde el cursor parpadeante
    
    // Pantalla de inicio
    gotoxy(25, 8);
    cout << "¡JUEGO DEL DINOSAURIO EN C++!";
    gotoxy(28, 10);
    cout << "Presiona ESPACIO para saltar";
    gotoxy(25, 12);
    cout << "Presiona cualquier tecla para empezar...";
    
    dibujarSuelo();
    _getch(); // Espera a que el jugador esté listo

    // Limpia la pantalla de inicio
    system("cls");
    dibujarSuelo(); // Vuelve a dibujar el suelo
    
    int velocidadJuego = 50; // Milisegundos de espera por frame (más bajo = más rápido)

    // --- EL BUCLE DE JUEGO (GAME LOOP) ---
    while (!gameOver) {
        
        // 1. Borrar (las posiciones viejas)
        // (Importante: borramos ANTES de actualizar la lógica)
        borrarDino();
        borrarCactus();

        // 2. Revisar Entradas (Input)
        procesarInput();

        // 3. Actualizar Lógica (Física, Movimiento, Colisiones)
        actualizarLogica();
        
        // 4. Dibujar (las nuevas posiciones)
        dibujarFrame();

        // 5. Esperar (Controlar la velocidad)
        Sleep(velocidadJuego);
    }

    // --- Fin del Juego ---
    system("cls"); // Limpia la pantalla
    gotoxy(35, 10);
    cout << "GAME OVER";
    gotoxy(30, 12);
    cout << "Puntaje final: " << puntaje;
    
    _getch(); // Espera una tecla antes de cerrar
    
    return 0;
}
