#include "mbed.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>




UnbufferedSerial pc(USBTX, USBRX, 9600);
AnalogIn ain(A0);
PwmOut ledR(LED1);
Timer t;
double calcularAceleracionGravitacional(const vector<double>& tiempo, const vector<double>& posicion) {
    int n = tiempo.size();

    // Calcular sumatorias necesarias para la fórmula de la regresión lineal
    double sumTiempo = 0.0, sumPosicion = 0.0, sumTiempoPosicion = 0.0, sumTiempoCuadrado = 0.0;

    for (int i = 0; i < n; ++i) {
        sumTiempo += tiempo[i];
        sumPosicion += posicion[i];
        sumTiempoPosicion += tiempo[i] * posicion[i];
        sumTiempoCuadrado += tiempo[i] * tiempo[i];
    }

    // Calcular la pendiente (m) y la intersección en el eje y (b)
    double m = (n * sumTiempoPosicion - sumTiempo * sumPosicion) / (n * sumTiempoCuadrado - sumTiempo * sumTiempo);
    double b = (sumPosicion - m * sumTiempo) / n;

    // Calcular la aceleración gravitacional (g)
    double g = 2 * m;

    return g;
}

int main() {

  ledR = 1;
  float previousReading = 0.0;
  vector<double> tiempo = {};
  vector<double> posicion = {0,2,  4,  6,  8,  10, 12, 14,
                             16, 18};

  while (true) {

    t.start();

    if (ain <= 0.08) {
      cout << ain << endl;
      t.stop();
      cout << "Tiempo transcurrido: " << t.elapsed_time().count()
           << " milisegundos" << endl;

      // Agregar el tiempo transcurrido al vector tiempo
      tiempo.push_back(t.elapsed_time().count());

      // Verificar si el vector tiempo contiene 14 valores
      if (tiempo.size() == 5) {
        // Invocar la función aceleracionGrav
        double aceleracionGrav = calcularAceleracionGravitacional(tiempo, posicion);

        // Imprimir el resultado
        cout << "Aceleración gravitacional: " << aceleracionGrav << " m/s^2"
             << endl;

        // Limpiar el vector tiempo para futuras mediciones
         //tiempo.clear();
      }
    }

    // Añade una condición de salida para salir del bucle cuando sea necesario.
    if (tiempo.size() == 5) {
      break;
    }

    // ThisThread::sleep_for(150ms);
  }
}