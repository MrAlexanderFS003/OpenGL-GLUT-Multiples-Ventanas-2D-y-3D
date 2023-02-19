class Puntero {
	float posX = 20, posY = 20, velocidad = 0.01f;
	int r = 255, g = 0, b = 0;
public:
	Puntero() {}
	void Cabeza();
	void Seleccion();
	void Borrar();
	void Actualiza();

	//Setters y Getters
	void setPosX(float valor) { posX = valor; }
	void setPosY(float valor) { posY = valor; }

	float getPosX() { return posX; }
	float getPosY() { return posY; }

	void setRGB(int CodeR, int CodeG, int CodeB) { r = CodeR; g = CodeG; b = CodeB; }
	
};
