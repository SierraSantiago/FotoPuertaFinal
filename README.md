Santiago Sierra, Pablo Garcia

## Descripción
Este programa utiliza una plataforma mbed para medir la aceleración gravitacional mediante un sensor de posición analógico. La medición se realiza a través de una regresión lineal sobre datos de tiempo y posición.

## Componentes
- **Placa mbed**: Se utiliza para la programación y control del sistema.
- **Sensor de posición analógico (A0)**: Mide la posición del objeto en estudio.
- **LED1**: Indicador visual para señalar el inicio del proceso.
- **Puerto serie USB (pc)**: Se utiliza para imprimir resultados y mensajes de depuración.


Esta parte del código define una función llamada calcularAceleracionGravitacional que toma dos vectores de tipo double como argumentos: tiempo y posicion. La función tiene como objetivo calcular la aceleración gravitacional a partir de estos datos mediante una regresión lineal.
```double calcularAceleracionGravitacional(const vector<double>& tiempo, const vector<double>& posicion) {
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
```
estas líneas establecen la configuración inicial del LED (ledR), crean vectores vacíos para almacenar los tiempos (tiempo) y asignan un conjunto de valores de posición predefinidos (posicion). Estos valores de posición y tiempos se utilizarán para calcular la aceleración gravitacional mediante una regresión lineal más adelante en el programa.
```
  ledR = 1;
  vector<double> tiempo = {};
  vector<double> posicion = {0,2,  4,  6,  8,  10, 12, 14,
                             16, 18};
```
Este fragmento de código representa un bucle que realiza mediciones de posición y tiempo de un objeto en intervalos regulares. Aquí hay un resumen comprensible:
Se verifica si el valor leído del sensor analógico (ain) indica un cambio significativo en la posición del objeto (si es menor o igual a 0.08).
Si hay un cambio en la posición, se registra el tiempo transcurrido desde el inicio del temporizador en un vector llamado tiempo.
Cuando se registran 5 cambios en la posición, se invoca una función que utiliza los datos de tiempo y posición para calcular la aceleración gravitacional.
Se imprimen en la consola el valor leído del sensor, el tiempo transcurrido y la aceleración gravitacional calculada.

```
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
```
