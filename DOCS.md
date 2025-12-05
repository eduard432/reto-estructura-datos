📘 Documentación de Comandos – Juego DnD (CLI)

Esta documentación describe todos los comandos disponibles dentro del sistema de línea de comandos (CLI) del juego tipo DnD desarrollado en C++. Los comandos permiten gestionar el héroe, navegar por la mazmorra, combatir monstruos y administrar el tablero.

🧭 Comandos Generales
/help

Muestra la lista completa de comandos disponibles y su descripción básica.

/register

Permite seleccionar y registrar un tipo de héroe para iniciar el juego.

/play

Inicia la exploración de la casilla actual.
Si hay un monstruo y no ha sido derrotado, comenzará un encuentro.

/combat

Continúa o inicia el combate contra el monstruo de la casilla actual.

/me

Muestra toda la información del héroe actual: vida, ataque, defensa, etc.

/monster

Muestra información del monstruo en la casilla actual (si existe).

/list
/ls

Muestra las casillas adyacentes a la actual, con sus nombres e IDs.

/move
/cs

Permite moverse a otra casilla adyacente.
Solo es posible si la casilla actual ya ha sido "superada".

Flujo:

Se muestran las casillas adyacentes.

El usuario escribe el nombre de la casilla destino.

El sistema intenta realizar el movimiento.

/status

Muestra el estado general del tablero:

Casilla actual

Si hay combate

Si la casilla está tranquila o pendiente de jugar

/clear
/cls

Limpia la terminal.

/exit

Sale del juego.

🛠️ Comandos de Administrador (sudo)

Para usar estos comandos:
sudo <comando> <opciones...>

📦 sudo add
sudo add square

Agrega una nueva casilla al tablero.

Solicita:

Nombre de la casilla

Probabilidad de aparición de monstruo

(La opción para agregar monstruos está marcada como TODO.)

📥 sudo load

Carga información desde archivos CSV.

sudo load monsters

Carga monstruos desde un CSV.

sudo load squares

Carga casillas desde un CSV.

sudo load connections

Carga las conexiones entre casillas desde un CSV.

sudo load attacks monsters

Carga los ataques de los monstruos desde un CSV.

📋 sudo list / sudo ls
sudo list squares -a

Muestra todas las casillas existentes.

sudo list monsters -a

Muestra todos los monstruos disponibles.

🔗 sudo connect

Conecta dos casillas existentes mediante sus IDs.

Solicita:

ID de la primera casilla

ID de la segunda casilla

🗺️ sudo cheatcode

Muestra la ruta más fácil hacia el tesoro según el algoritmo implementado.

✔️ Resumen Rápido
Comando	Descripción
/help	Muestra todos los comandos
/register	Registrar héroe
/play	Jugar casilla actual
/combat	Continuar combate
/me	Mostrar héroe
/monster	Mostrar monstruo actual
/list / /ls	Mostrar casillas adyacentes
/move	Mover de casilla
/status	Estado general
/clear	Limpiar terminal
/exit	Salir
sudo add square	Agregar casilla
sudo load ...	Cargar CSVs
sudo connect	Conectar casillas
sudo cheatcode	Camino al tesoro