#variables usadas en el programa
option := -1;
creditos := 500;

do
    print('
    .____                              _________               .__               
    |    |    ____ ___  _______   ____ \_   ___ \_____    _____|__| ____   ____  
    |    |  _/ __ \\  \/  /  _ \ /    \/    \  \/\__  \  /  ___/  |/    \ /  _ \ 
    |    |__\  ___/ >    <  <_> )   |  \     \____/ __ \_\___ \|  |   |  (  <_> )
    |_______ \___  >__/\_ \____/|___|  /\______  (____  /____  >__|___|  /\____/ 
            \/   \/      \/          \/        \/     \/     \/        \/        
    ');

    print('[0] Salir del programa');
    print('[1] Adivina el número secreto');
    print('[2] Ruleta de la suerte');
    print('[3] Mentiroso Mentiroso...');
    read(option);

    switch(option)
        case 1:
            clear_screen;
            place(0,0);
            print('Bienvenido a Adivina el numero!');
            print('En este juego vas a tener que adivinar un número entre un rango del 1 al 1000');
            print('Dependiendo de que tan lejos estes den número puedes perder más o menos creditos, asi que ten cuidado');
            read(n);
            
        case 2:
            clear_screen;
            place(0,0);
            print('Bienvenido a la ruleta de la suerte');

        case 3:
            clear_screen;
            place(0,0);
            print('Bienvenido al juego del mentiroso');

        default:
            print('Opción inválida');
    end_switch;

while(option <> 0)