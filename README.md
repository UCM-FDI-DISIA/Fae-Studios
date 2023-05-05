# **Ott: an Elemental Journey - Game Design Document**
- [**Ott: an Elemental Journey - Game Design Document**](#ott-an-elemental-journey---game-design-document)
  - [**1 - Ficha técnica**](#1---ficha-técnica)
  - [**2 - Descripción**](#2---descripción)
  - [**3 - Jugabilidad**](#3---jugabilidad)
    - [**3.1 - Elementos**](#31---elementos)
    - [**3.2 - Mecánicas de Ott**](#32---mecánicas-de-ott)
    - [**3.3 - Ataque**](#33---ataque)
    - [**3.4 - Defensa**](#34---defensa)
    - [**3.5 - Sistema de vida**](#35---sistema-de-vida)
    - [**3.6 - Mapa**](#36---mapa)
    - [**3.7 - Mecánicas de escenario**](#37---mecánicas-de-escenario)
    - [**3.8 - Cámara**](#38---cámara)
  - [**4 - Diseño de nivel**](#4---diseño-de-nivel)
    - [Bosque](#bosque)
  - [**5 - HUD**](#5---hud)
  - [**6 - Visual**](#6---visual)
  - [**7 - Menús y flujo de juego**](#7---menús-y-flujo-de-juego)
  - [**8 - Contenido**](#8---contenido)
    - [**Personajes y enemigos**](#personajes-y-enemigos)
  - [**9 - Referencias**](#9---referencias)


## **1 - Ficha técnica**
- **Título**: *Ott: an Elemental Journey*
- **Género**: Metroidvania
- **Target**: Jugadores no noveles exploradores
- **Rating**: PEGI 7
- **Plataforma**: PC (Windows/Mac)
- **Modos de juego**: 
  - Un jugador: Campaña.
  
## **2 - Descripción**
Ott, el protagonista, tiene por destino salvar al mundo de la oscuridad que lo asola. Viajará por tres regiones diferenciadas por las fuerzas de la naturaleza que ejercen sus dominios sobre ellas: El Reino de la Tierra, del Agua y del Fuego. En estos lugares, Ott se encontrará con habitantes corruptos por la oscuridad que tratarán de evitar que cumpla su sino. Durante sus viajes conseguirá dominar los diferentes elementos para derrocar al mal de su tierra natal. Estos elementos le proporcionarán nuevas habilidades con las que explorar zonas antes cerradas para elle, permitiéndole volver atrás en sus pasos y descubrir pequeños secretos que estas tierras ocultan.

## **3 - Jugabilidad**
### **3.1 - Elementos**
<img src="./gdd-assets/elementos.png">

El elemento básico que incluye el personaje es luz, a lo largo del juego podrás conseguir el resto de elementos, cada uno en su reino correspondiente, exceptuando la oscuridad, que es la representación del enemigo y superior en fuerza al resto de elementos (no ante luz) tal y como se muestra en el diagrama.

### **3.2 - Mecánicas de Ott**
<img src="./gdd-assets/controles.png">
<table>
    <tr>
        <th>Input</th>
        <th>Acción</th>
    </tr>
    <tr>
        <td>Flechas laterales (teclado) <br> Mover joystick izquierdo (mando)</td>
        <td><b>Desplazamiento izquierda o derecha</b>. Velocidad constante.
        También se permite movimiento durante el salto a una velocidad reducida.
        </td>
    </tr>
    <tr>
        <td>Barra espaciadora (teclado) <br> X (PS) <br> A (XBOX)</td>
        <td><b>Salto</b>: impulso vertical a velocidad constante. No podrá volver a saltar hasta apoyarse en una superficie sólida. Al estar sumergido en agua Ott saltará ligeramente menos.
        </td>
    </tr>
    <tr>
        <td>Flecha superior (teclado) <br> Mover joystick verrticalmente (mando)</td>
        <td><b>Ascender</b>: Si Ott está en una enrredadera, ascenderá verticalmente.
        </td>
    </tr>
    <tr>
        <td>Flecha inferior (teclado) <br> Mover joystick verrticalmente (mando)</td>
        <td><b>Descenso</b>: Si Ott está en una enrredadera, descenderá verticalmente. De no ser el caso, si está en una sala que es muy grande, Ott puede mirar hacia abajo, lo que moverá la cámara en sentido vertical descendente revelando lo que hay debajo del jugador.
        </td>
    </tr>
     <tr>
        <td>Teclas numéricas (1-4) <br> R1, R2, L1, L2 (PS) <br> RB, RT, LB, LT (XBOX)</td>
        <td><b>Cambio de elemento</b>. No se podrá cambiar de elemento instantáneamente después de haber cambiado al actual (habrá un pequeño <i>cooldown</i> marcado por una animación). 
        </td>
    </tr>
    <tr>
        <td>Tecla "E" (teclado) <br> Cuadrado (PS) <br> X (XBOX)</td>
        <td><b>Ataque elemental</b>:
            <ul>
              <li>Habrá un ligero <i>cooldown</i> entre ataques marcado por una animación. </li>
                <li>No hay límite de ataques.</li>
                <li>Puedes realizar un ataque y moverte a la vez.</li>
                <li> La efectividad del ataque contra los enemigos depende del elemento de Ott.</li>
            </ul>
        </td>
    </tr>
    <tr>
        <td><b>MANTENER</b> <br>Tecla "E" (teclado) <br> Cuadrado (PS) <br> X (XBOX)</td>
        <td><b>Ataque cargado</b>: Ott podrá realizarlo si el indicador de “<i>Ataque Cargado</i>” está completamente lleno (matando enemigos). Podrá seguir moviéndose durante el ataque, y al terminar, perderá todas las cargas</td>
    </tr>
    <tr>
        <td>Tecla "R" (teclado) <br> Círculo (PS) <br> B (XBOX)</td>
        <td><b>Defensa</b>: Ott dispone de un escudo para defenderse. Podrá tenerlo activo, y moverse todo el tiempo que quiera. (ver <a href="#34---defensa"><b><i>Defensa</i></b></a>).</td>
    </tr>
    <tr>
        <td>Tecla "F" (teclado)<br> Triángulo (PS) <br> Y (XBOX)</td>
        <td><b>Interactuar con objetos</b>: ver <a href="#37---mecánicas-de-escenario"><b><i>Mecánicas de escenario</i></b></a>
        </td>
    </tr>
    <tr>
        <td>Tabulador (teclado) <br> Botón Share (PS) <br> Botón Vista (XBOX)</td>
        <td><b>Mapa</b>: se podrá consultar la ubicación actual y salas descubiertas (ver <a href="#36---mapa"><b><i>Mapa</i></b></a> más adelante).
        </td>
    </tr>
</table>

### **3.3 - Ataque**
<table>
    <tr>
        <th>Elemento</th>
        <th>Ataque normal</th>
        <th>Ataque cargado</th>
        <th>Habilidad</th>
    </tr>
    <tr>
        <td>Luz</td>
        <td>Ataque básico <br> <img src="./gdd-assets/ott-ataque.gif" width=25% height=25%></td>
        <td>Igual que el básico pero con doble de daño y un mayor rango</td>
        <td><b>Teletransporte</b> entre determinados focos de luz del mundo</td>
    </tr>
        <tr>
        <td>Tierra</td>
        <td><b>Látigo</b> de medio alcance hacia una dirección.  <br> <img src="./gdd-assets/earth_Attack.png"> <br></td>
        <td>Látigo que se tira en ambos lados, creando daño en el área delimitada por su alcance.</td>
        <td><b>Enredadera</b>: puede escalarse y crece verticalmente cuando interactúa con las zonas de hierba.</td>
    </tr>
    <tr>
        <td>Agua</td>
        <td><b>Chorro de agua</b> (de más rango que el básico, pero con menor daño) <br> <img src="./gdd-assets/water_Attack.png"> <br> El rectángulo representa el ataque. El jugador lanza un ataque que se detiene al golpear a un enemigo.</td>
        <td>La versión cargada permanece activa durante un tiempo, dañando a todos los enemigos que entran en contacto por ticks, Ott puede moverse y el ataque le sigue.</td>
        <td><b>Buceo</b>: sustituye al movimiento básico de Ott al estar bajo el agua. Con el resto de elementos, Ott subirá hacia la superficie al estar sumergido.</td>
    </tr>
    <tr>
        <td>Fuego</td>
        <td><b>Bola de fuego</b>: con un alto rango que se dispara en la dirección que mira el jugador. <br> <img src="./gdd-assets/fire_Attack.png"> <br> </td>
        <td><b>Bolas de fuego</b>: igual que la bola de fuego normal, pero se lanzan tres seguidas.</td>
        <td><b>Quemar</b> objetos como raíces</td>
    </tr>
</table>

### **3.4 - Defensa**
Ott es capaz de usar un escudo que le permitirá mitigar completamente el daño que vaya a recibir. Cuando tiene el escudo en alto su velocidad de movimiento se ve bastante reducida. Este método de defensa tiene 3 formas de actuar según el elemento que haya atacado a Ott respecto al elemento escogido actualmente:

- **Elemento débil**: Si Ott ha bloqueado un ataque de esta forma, no recibirá daño.
- **Elemento neutro**: Se le pondrá una vida **débil**
- **Elemento fuerte**: Ott queda *stunneado* durante pocos segundos por lo que no podrá realizar ningún tipo de acción hasta que termine el efecto.
<img src="./gdd-assets/lightShield.png">
### **3.5 - Sistema de vida**
Se empezará con 5 puntos de vida que puede perder cuando recibe un ataque de un enemigo, si entra en contacto con algún enemigo o con algún elemento del dañino entorno (pinchos, zarzas, cristales…).   
El sistema de vida también se ve afectada por el sistema de elementos. Según el tipo de daño elemental que reciba Ott, se recibe una cantidad de daño variable:
- **Elemento débil**: Ott recibe "media vida" de daño, de manera que si no recibe ningún daño en un corto margen de tiempo, recuperará esa vida. De lo contrario, si recibe otro daño debil, perderá la vida por completo, pero si recibe daño neutro o fuerte, además de perder las vidas correspondientes, su vida media pasará a la última vida entera que tenga.
- **Elemento neutro**: Perderá una vida.
- **Elemento fuerte**: Ott recibe un impacto crítico por lo que pierde 2 vidas.

Si en algún momento el valor de vida llega a 0, Ott morirá y volverá a aparecer en el último **Punto de Teletransporte** que atravesará, haciendo que los enemigos que haya vencido durante su última vida reaparezcan.  
El máximo de puntos de vida puede ser ampliado mediante fragmentos de vida, que podrán obtenerse mediante:
  - Exploración, encontrando reliquias ocultas por el mundo.

Al obtener 2 de estos, la vida máxima de Ott aumenta en 1 permanentemente. Cunado el jugador coge uno de estos, se le indicará por pantalla el número de ellos que tiene.
(Véase [***HUD***](#5---hud) para la representación de este sistema).

### **3.6 - Mapa**
A medida que Ott atraviesa las diferentes salas que conforman el mundo, el pequeño las irá dibujando de una forma esquemática en un mapa, los Santuarios que hayan sido descubiertos aparecen marcados en el mapa. Este mapa será accesible en cualquier momento por el jugador.

El mapa también es capaz de registrar constantemente la posición de Ott durante su recorrido. Véase [***HUD***](#5---hud) para la representación del mapa.

### **3.7 - Mecánicas de escenario**
<table>
    <tr>
        <td><b>Zona de hierba</b></td>
        <td>Habilitan la creación de <b>enredaderas</b> sobre ellas usando el poder elemental de tierra/planta</td>
    </tr>
    <tr>
        <td><b>Enredaderas</b></td>
        <td>Hojas dispuestas verticalmente; permiten a Ott <b>subir por ellas</b>.</td>
    </tr>
    <tr>
        <td><b>Raíces/Hielo</b></td>
        <td><b>Bloquean</b> el camino. Pueden <b>romperse</b> usando el poder elemental del <b>fuego</b></td>
    </tr>
    <tr>
        <td><b>Zonas profundas de agua</b></td>
        <td>Habrá que pasar por ellas <b>buceando</b> con el poder del agua. Al usarlo, el personaje es capaz de llegar hasta el fondo del agua, pudiendo caminar por él. Su salto y movimiento se verán ligeramente ralentizados. Al cambiar de elemento bajo el agua, el personaje ascenderá lentamente.</td>
    </tr>
    <tr>
        <td><b>Lámparas de teletransporte</b></td>
        <td>Siempre son 2 lámparas que están relacionadas: Funcionan de forma similar a las <b>Tuberías</b> de <i>Mario Bros</i>, donde puedes interactuar con cualquiera de los dos extremos y este moverá a tu personaje al otro extremo.</td>
    </tr>
    <tr>
        <td><b>Santuarios</b></td>
        <td><b>Referencia</b> rápida: Bancos de <i>Hollow Knight</i>; Hogueras de <i>Dark Souls</i> y similares.<br>
        Actúan como <b>zonas de descanso</b> y <b>puntos de guardado</b> para el jugador. Serán su punto de <b>reaparición</b> al morir y al volver a cargar una partida. Al interactuar con ellos <b>recuperas</b> completamente tus <b>puntos de vida</b>, haciendo que los <b>enemigos</b> a tu alrededor <b>reaparezcan</b> si habían sido derrotados y guardando la partida.</td>
    </tr>
</table>

### **3.8 - Cámara**
La cámara sigue al jugador, manteniéndolo en el centro en todo momento excepto al llegar al borde de una sala, momento en que los bordes de la sala coincidirían con el borde de la cámara, causando que el jugador deje de estar en el centro. Cuando se pase de una sala a otra la cámara hace un efecto de fundido en negro, antes de pasar a la siguiente  sala.


## **4 - Diseño de nivel**
El diseño gira entorno al plataformeo y al movimiento del personaje por las ‘salas’, que contienen múltiples plataformas de diferentes tipos, aparte de caminos en un primer lugar bloqueados o inaccesibles debido a la falta de habilidades del personaje que controlamos; y también destaca la presencia múltiples en enemigos.  
Todos los reinos cuentan con los siguientes puntos en común:
  - **Tres tipos de enemigos** que no se comparten entre los reinos.
  - Un **elemento** guardado por enemigos de oscuridad.
  - Un **Boss final** que nos dará un fragmento de vida.
  - Uno o varios **fragmentos de vida oculto** en alguna sala
  - Una **reliquia** única.
  - Salas sin peligros donde se cuenta el lore a través de escritos en las paredes.
  
De esta forma es posible aumentar la vida máxima en 1 en cada uno de los reinos (para un total de **8 vidas**) siempre y cuando se exploren casi en su totalidad. 

### Bosque
Se trata de la **primera zona del juego**. Trata de introducir las mecánicas de movimiento y tiene **enemigos** muy **sencillos**, que intentan introducir las mecánicas de ataque y defensa de forma liviana.
El juego comienza con el jugador observando la gigantesca puerta del **Boss Final**, a quien se tendrá que enfrentar para rematar su aventura. Esta puerta muestra **4 luces**, todas **apagadas**, excepto 1, que se encenderá en cuanto el jugador pueda tomar control de Ott. Estas luces representan los diferentes elementos, y la que se enciende al comenzar la aventura representa la luz.

<img src="./gdd-assets/boceto-mapa.png">

**Figura 1**: *Primer boceto del mapa con la región de tierra entera y el comienzo de la región de agua.*

### Zona acuática
La segunda zona del juego estará sumergida en su mayor parte. Para poder desplazarse Ott tendrá que cambiar entre el poncho de agua y el resto de elementos para poder descender y ascender a voluntad por el nivel. Este nivel está muy centrado al rededor de esta mecánica de movimiento, presentando así salas a modo de laberinto y algún que otro puzzle.

### Volcán
La última zona del juego, ambientada un desolado y peligroso ambiente volcánico. En este segmento del juego desta una distribución menos lineal de las salas, brindando más libertad al jugador. El parkour juega un rol importante en el nivel, la lava sustituye a los pinchos del principio, y las plataformas son más pequeñas. Además algunas raíces bloquean el paso del jugador que tendrá que buscar una manera de destruirlas para abrirse paso.

## **5 - HUD**
La interfaz ocupará el menor espacio posible en pantalla, ya que la información acerca del estado del jugador se presentará de forma diegética (integrada en el mundo).  
**Vida**: tendrá una representación ‘doble’:
  - Mediante una *barra de vida* que toma valores discretos.
  - Oscureciendo la pantalla ligeramente cuando quede poca vida.

Justo al lado de la barra de vida aparecerá un medidor circular dividido en ocho fragmentos que indicará el número de cargas obtenidas para el **ataque cargado**.

 <img src="./gdd-assets/hud-vida-cargada.png">

 **Figura 1**: *boceto de HUD con la mayoria de vida.*

<img src="./gdd-assets/hud-poca-vida.png">

**Figura 2**: *Boceto de cómo se vería el oscurecimiento de pantalla si Ott tuviera un valor muy bajo de vida.*

## **6 - Visual**
La estética del juego será Pixel Art 2D. El juego está ambientado en un mundo fantástico basado en tres elementos. La parte visual tendrá una estética suave, atrayente y colorida, que contraste la temática más bélica/dramática.  
En el reino del agua predominarán los elementos marinos, representados mediante una paleta de azules y verdes azulados. En el reino del fuego, colores intensos rojos que dibujarán las llamas y otros elementos como la lava. En el reino de tierra, veremos colores y elementos propios de la naturaleza (verdes, amarillos, etc..).  
El personaje principal, **Ott**, en su estado inicial/base será un ser de luz con vestimenta amarilla. Irá incorporando nuevos elementos y con estos cambiará su *skin*.  
El **boss final** es un ser de oscuridad, antagonista a Ott, por lo que se conformará por una paleta oscura de negros y violetas.    
Los personajes de cada elemento portarán los colores de su reino, excepto aquellos infectados por la oscuridad, nuestros **enemigos**, que incorporarán partes del cuerpo **afectadas con los colores del antagonista**.

**Las paletas de cada zona serán las siguientes:**

<img src="./gdd-assets/paletas.PNG">

## **7 - Menús y flujo de juego**
El juego contará con un menú principal donde poder crear una **partida nueva**, **cargar partida**, **acceder a ajustes** o **salir** de la aplicación. 
Al acceder al submenú de ajustes se podrán encontrar mayoritariamente ajustes de sonido.

<img src="./gdd-assets/menus.png">

Una vez se haya accedido a una partida, el juego podrá **pausarse** pulsando la tecla ESC (teclado) || Botón Options (PS) || Botón Start (XBOX). Esto hará que toda la ejecución del juego, excepto la música, se detenga. En este menú podremos entrar a **ajustes**, **salir al menú** o **salir al escritorio**.

<img src="./gdd-assets/flujos-menu.png">


## **8 - Contenido**
### **Personajes y enemigos**
Cada zona del juego (Bosque, Lago - Fondo del lago, Volcán y Oscuridad) tendrán 3 tipos de enemigos (débil, medio y fuerte) descrito más adelante. De esta forma, el enemigo débil del bosque no será el mismo que el del Volcán, por ejemplo.
<table>
    <tr>
        <td><b>Bug</b></td>
        <td>
            <ul>
                <li>Patrón de movimiento "<b>centinela</b>": al ver al jugador le perseguirá hasta poder ejecutar su ataque.</li>
            </ul>
        </td>
    </tr>
    <tr>
        <td><b>Seta lanzaesporas</b></td>
        <td>
            <ul>
                <li><b>Estático</b>.</li>
                <li><b>Lanza esporas</b> hacia el jugador cada X segundos.</li>
            </ul>
        </td>
    </tr>
    <tr>
        <td><b>Slime de Roca</b></td>
        <td>
            <ul>
                <li>Ataca <b>acercándose</b> al <b>jugador</b> y <b>cayendo</b> hacia él. En ese momento se queda vulnerable al no poder moverse. Al morir, se <b>divide en 2</b>.</li>
            </ul>
        </td>
    </tr>
</table>

### **Jefes**
Cada zona del juego dispondrá de 1 jefe propio, con sus mecánicas únicas y donde se tendrá que hacer uso de las habilidades aprendidas en ese reino y los anteriores para poder derrotarlo.
<table>
    <tr>
        <td><b>Gusano de tierra</b></td>
        <td>
            <ul>
                <li>En la sala del jefe habrá varias enrredaderas que podrá crear el jugador para poder moverse verticalmente y subir a las plataformas presentes.</li>
              <li> El boss empezará ejecutando dos rondas de ataques horizontales a dos alturas distintas. Haciendo uso del movimiento vertical el jugador tendrá que evitar dichos ataques </li>
              <li> Finalmente, el boss aparecerá encima del jugador, y descenderá hacia él para atacar, haciendo daño por contacto </li>
              <li> En una de las plataformas de la sala, aparecerá aleatoriamente unos pinchos, si el jugador se coloca debajo de dicha plataforma, el jefe descenderá más despacio permitiendo alargando la fase de daño </li>
            </ul>
        </td>
    </tr>
    <tr>
        <td><b>Monstruo Marino</b></td>
        <td>
            <ul>
                <li>Cuando el jugador llegue a su sala, el mostruo empezará a perseguirle</li>
                <li>Si consigue atrapar a Ott, este morirá al instante, por lo tanto, su única opción es escapar</li>
              <li>Durante su escapada, será necesario usar los distintos efectos para sortear varios obstáculos que intentarán frenar al jugador, el jefe sin embargo destruirá los obstáculos al tocarlos</li>
              <li>Ott vencerá al jefe llegando hasta el final del recorrido</li>
            </ul>
        </td>
    </tr>
    <tr>
        <td><b>Esqueleto</b></td>
        <td>
            <ul>
                <li>El jefe aparecerá cuando Ott entre en su arena de combate</li>
              <li>El jefe es inmune a todos los ataques que recibe</li>
              <li>Sus ataques son muy variados, si Ott está a su altura, le perseguirá para golpearle con su maza, sino, le lanzará proyectiles y ocasionalmente, creará un pilar de fuego mortal bajo los pies del jugador.</li>
              <li>Si Ott rompe la raíz que cuelga del tanque de agua sobre el jefe, este quedará vulnerable y aturdido por unos segundos.</li>
            </ul>
        </td>
    </tr>
    <tr>
        <td><b>Urk, jefe oscuro</b></td>
        <td>
            <ul>
                <li>Este jefe a utiliza varios ataques de todos los elementos.</li>
                <li>El ataque de oscuridad, crea un agujero negro que atrae a Ott hacia él a menos que lleve el elemento de luz, igualmente, crea puños que se moverán horizontalmente o verticalmente.</li>
              <li>El ataque de fuego, crea paredes que se desplazan horizontalmente, y dañarán a Ott si entra en contacto con ellas. La única manera de evitarlas es con el elemento de Agua, buceando en unos surco que hay a la altura del suelo.</li>
              <li>El ataque de agua crea 2 burbujas que dispararán a Ott. Estas burbujas permanecen activas durante bastante tiempo, y la única forma de destruirlas antes es creando unas enrredaderas que las exploten./li>
              <li>El jefe puede hacer uso de su habilidad de planta, gracias al cual empezará a curarse. Si Ott utiliza sus ataques de fuego para cortar las raíces que le curan, empezará la fase de daño.</li>
              <li>La fase de daño será de tiempo limitado. Durante el tiempo que esté activa, Ott puede dañar al jefe golpeándole en la cara.</li>
            </ul>
        </td>
    </tr>
</table>

Los tres tipos de enemigos estarán presentes en todos los reinos, pudiendo ser de todos los elementos disponibles, excepto oscuridad. De manera que para poder enfrentarse a ellos facilmente, se tendrá que hacer un buen uso de la jerarquía de elementos. (véase [***Elementos***](#31---elementos)).

## **9 - Recursos utilizados**
#### Recursos propios
- Shuriken de agua (Basado en https://www.nicepng.com/ourpic/u2y3q8t4t4e6y3e6_water-shuriken-water-pixel-art/)
- Ataque de fuego de Ott
- SpriteSheet Ott escalando (Basado en SpriteSheet de Ott)
- Elementos

#### Créditos
- Música del boss final --> Riding Dragons - https://www.boris-sandor.com/


## **10 - Referencias**
 - **Historia**: *The Legend of Zelda: Breath of the Wild*, *Hollow Knight*
 - **Género**: *CastleVania*, *Hollow Knight*