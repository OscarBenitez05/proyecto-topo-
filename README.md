# TOPO MANIA PRO

## Descripción del Proyecto

Topo Mania PRO es un videojuego desarrollado en C++ utilizando la librería SFML. El objetivo del juego es golpear los topos que aparecen en diferentes agujeros antes de que desaparezcan. Conforme aumenta la puntuación, la dificultad se incrementa haciendo que los topos aparezcan más rápido.

El proyecto fue desarrollado para la materia de programacion .

---

## Objetivo del Juego

Conseguir la mayor cantidad de puntos posible golpeando los topos antes de que el tiempo termine o se pierdan todas las vidas.

---

## Controles

* ENTER: Iniciar partida.
* Tecla 1: Golpear agujero 1.
* Tecla 2: Golpear agujero 2.
* Tecla 3: Golpear agujero 3.
* Tecla 4: Golpear agujero 4.
* ESC: Salir del juego.

---

## Mecánicas del Juego

### Topo Normal

* Aparece con frecuencia.
* Otorga 10 puntos al golpearlo.

### Topo con Casco

* Requiere dos golpes para eliminarlo.
* Otorga 25 puntos.

### Bomba

* Resta 20 puntos.
* Quita una vida al jugador.

### Sistema de Vidas

* El jugador comienza con 5 vidas.
* Si un topo normal desaparece sin ser golpeado, se pierde una vida.

### Sistema de Tiempo

* Cada partida dura 60 segundos.
* Al terminar el tiempo, el juego finaliza.

---

## Características

* Pantalla de inicio personalizada.
* Fondo de juego personalizado.
* Sistema de puntuación.
* Sistema de vidas.
* Temporizador.
* Incremento progresivo de dificultad.
* Pantalla de Game Over.
* Uso de imágenes externas.
* Uso de fuentes externas.

---

## Estructura del Proyecto

```text
assets/
├── Fonts/
│   └── arial.ttf
├── Imagenes/
│   ├── menu.png
│   └── juego.jpg

bin/
├── juego.exe

screenshots/
├── inicio.png
├── juego.png
└── finjuego.png

src/
├── Main.cpp
```

---

## Tecnologías Utilizadas

* Lenguaje: C++
* Librería gráfica: SFML 3.0
* IDE: Visual Studio Code
* Sistema Operativo: Windows

---

## Capturas de Pantalla

Las capturas del proyecto se encuentran dentro de la carpeta:

```text
screenshots/
```

---

## Video Demonstrativo

El video de demostración se encuentra dentro de la carpeta:

```text
video/demo.mp4
```

---

## Créditos

Desarrollado por:

Oscar Fabian Benitez Carrillo

Materia:

Proyecto 252

Año:

2026
