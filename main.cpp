#include "SFML/Graphics.hpp"
#include "iostream"

using namespace std;
using namespace sf;

int main() {
	RenderWindow ventana(VideoMode(800, 600), "Drag");
	Event evento;
	Texture punto_rojo;
	Texture tx_cursor;

	Sprite punto1, punto2, punto3, punto4, cursor, punto_seleccionado;
	Sprite arreglo_puntos[4];
	arreglo_puntos[0] = punto1;
	arreglo_puntos[1] = punto2;
	arreglo_puntos[2] = punto3;
	arreglo_puntos[3] = punto4;

	punto_rojo.loadFromFile("rcircle.png");
	tx_cursor.loadFromFile("crosshair.png");
	cursor.setTexture(tx_cursor);
	int seleccionado = 5;

	for (int i = 0; i < 4; i++) {
		arreglo_puntos[i].setTexture(punto_rojo);
	}

	arreglo_puntos[0].setPosition(0, 0);
	arreglo_puntos[1].setPosition(680, 0);
	arreglo_puntos[2].setPosition(0, 480);
	arreglo_puntos[3].setPosition(680, 480);

	ventana.setMouseCursorVisible(false);
	Vector2f pos_mouse(ventana.getSize().x / 2, ventana.getSize().y / 2);
	cursor.setPosition(pos_mouse.x, pos_mouse.y);
	cursor.setOrigin(64.0, 64.0);

	Vector2f posicion_click;

	while (ventana.isOpen()) {
		while (ventana.pollEvent(evento)) {
			arreglo_puntos[seleccionado].setPosition(evento.mouseMove.x, evento.mouseMove.y);
			if (evento.type == Event::Closed) {
				ventana.close();
			}
			if (evento.type == Event::MouseMoved) {//le da al sprite del cursor la misma posición que el cursor del mouse    
				cursor.setPosition(evento.mouseMove.x, evento.mouseMove.y);
			}

			if (evento.type == Event::MouseButtonPressed) {
				if (evento.key.code == Mouse::Left) {
					posicion_click.x = (float)cursor.getPosition().x;//al presionar la tecla izquierda del mouse guarda la posicion en que se presió
					posicion_click.y = (float)cursor.getPosition().y;//para compararla con las posiciones del los puntos
					for (int i = 0; i < 4; i++) {//dntro de este for compara las posiciones de los puntos con las coordenadas del click
						if (posicion_click.x >= arreglo_puntos[i].getPosition().x and posicion_click.y >= arreglo_puntos[i].getPosition().y) {
							if (posicion_click.x <= arreglo_puntos[i].getPosition().x + 128 and posicion_click.y <= arreglo_puntos[i].getPosition().y + 128) {
								seleccionado = i;//indica que elemento del arreglo de puntos esta seleccionado
							}
						}
					}
				}
			}
			if (evento.type == Event::MouseButtonReleased) {
				if (evento.key.code == Mouse::Left) {//al soltar la tecla del mouse, los puntos recuperan su posicion original
					arreglo_puntos[0].setPosition(0, 0);
					arreglo_puntos[1].setPosition(680, 0);
					arreglo_puntos[2].setPosition(0, 480);
					arreglo_puntos[3].setPosition(680, 480);
					seleccionado = 4;
				}
			}

		}

		ventana.clear(Color::Black);
		for (int i = 0; i < 4; i++) {
			ventana.draw(arreglo_puntos[i]);
		}
		ventana.draw(cursor);
		ventana.display();

	}

	return 0;
}
