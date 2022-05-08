# Laboratorio GPIO

Para este laboratorio debes completar una librería que permite el uso de pines GPIO. Nota: La libería no contempla la habilitación de reloj, que debe hacerse antes de usarla.

El conjunto de pruebas pin_gpio contiene pruebas para la librería a desarrollar, que fueron creadas al preparar la implementación de referencia. En lib/pin_gpio encontrarás el encabezado para lenguaje C y el listado de ensamblador.

El proyecto consiste en una aplicación de parpadeo de led que hace uso de la librería que debes completar. Si completas la librería y cargas el firmware verás que parpadea el led incluido en el bluepill. El código de la aplicación se encuentra en lib/parpadeo.

# Librería pin_gpio

Esta librería está diseñada con estilo orientado a objetos. Define el tipo de dato Pin y la enumeración ConfigPin con constantes para configuración de pin. Las funciones que debes implementar son las siguientes:

```c
void Pin_init(Pin *self, GPIO_TypeDef *puerto, int numPin);
```
Inicializa una estructura Pin. El primer argumento es un puntero a la estructura a inicializar, el segundo un puntero al puerto GPIO y el tercero el número del pin a controlar. Pin_init debe cargar en los respectivos campos de la estructura el puntero y número de pin suministrados. *Esta función está ya implementada*.

```c
void Pin_configura(Pin *self,ConfigPin modo);
```
Configura el pin según el modo indicado. El parámetro modo contiene un entero de 5 bits. Los 4 bits menos significativos contienen la configuración del pin a usar en el registro de control y el quinto bit sirve para distinguir las configuraciones de entrada pull-up y pull-down (que son idénticas en cuanto al valor del registro de configuración). Su valor es 1 para la configuración de entrada con pull-up y 0 para la de entrada con pull-down. *Debes implementar esta función*. Recuerda deshabilitar las interrupciones antes de realizar la lectura/modificación/escritura del registro de configuración (esto no es evaluado por las pruebas).

```c
void Pin_escribe(Pin *self, bool valor);
```
Cambia el estado del pin según el registro de salida. El valor true (1) corresponde a estado alto y false (0) al estado bajo. El cambio no debe realizarse directamente sino mediante los registros BSRR y BRR. *Debes implementar esta función*.

```c
bool Pin_lee(Pin *self);
```
Lee el estado del pin en el registro de entrada. El valor true (1) indica que el nivel lógico en el pin es alto y false (0) que el nivel es bajo. *Debes implementar esta función*

```c
bool Pin_leeSalida(Pin *self);
```
Lee el valor del registro de salida asociado al pin. El valor true (1) corresponde a un nivel alto y false (0) a un nivel bajo. Este valor es el valor de entrada del buffer de salida si el puerto está configurado como salida. *Debes implementar esta función* 