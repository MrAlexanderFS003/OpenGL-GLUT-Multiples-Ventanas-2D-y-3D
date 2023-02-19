class Camara {
	//static float lx , lz ;
	float lx = 0.0f, lz = -1.0f;
	float salto = 0.0f;
	float angulo = 0.0f, radio = 0.1f,posX = 0.0f, posY = 0.0f;
	//XZ posicion de la camara
	static float fraccion;
	static float x, y, z;
	static int w, s;
public:
	Camara() {}
	void Vista();
	void CamaraPosicion();

	void setSalto(float value) { salto = value; }

	float getLx() { return lx; }
	float getLz() { return lz; }

	void setLx(float value) { lx = value; }
	void setLz(float value) { lz = value; }

	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }

	void setX(float value) { x = value; }
	void setY(float value) { y = value; }
	void setZ(float value) { z = value; }

	float getFraccion() { return fraccion; }
	void setFraccion(float value) { fraccion = value; }

	int getKeyW() { return w; }
	int getKeyS() { return s; }
	void setKeyW(int val) { w = val; }
	void setKeyS(int val) { s = val; }

	void setAngulo(float value) { angulo = value; }
	float getAngulo() { return angulo; }
};
