#variables usadas en el programa
option := -1;
creditos := 500;
tickets := 0;

do
    print('
    .____                              _________               .__               
    |    |    ____ ___  _______   ____ \_   ___ \_____    _____|__| ____   ____  
    |    |  _/ __ \\  \/  /  _ \ /    \/    \  \/\__  \  /  ___/  |/    \ /  _ \ 
    |    |__\  ___/ >    <  <_> )   |  \     \____/ __ \_\___ \|  |   |  (  <_> )
    |_______ \___  >__/\_ \____/|___|  /\______  (____  /____  >__|___|  /\____/ 
            \/   \/      \/          \/        \/     \/     \/        \/        
    ');

    print('Cualquier opción no considerada te hará salir del programa');
    print('[1] Adivina el número secreto');
    print('[2] Ruleta de la suerte (Para esta necesitas tickets que se consiguen ganando)');
    print('[3] Mentiroso Mentiroso...');
    print('');
    print('Creditos actuales: ');
    print(creditos);
    print('');
    print('Tickets actuales: ');
    print(tickets);
    print('');
    print('Elija su opción');
    read(option);

    if(creditos < 0) then
        print('Esta pobre, gameOver');
        option := -1;
    end_if

    switch(option)
        case 1:
            clear_screen;
            place(0,0);
            print('Bienvenido a Adivina el numero!');
            print('En este juego vas a tener que adivinar un número entre un rango del 1 al 1000');
            print('');
            print('Se te quitaran creditos por cada error que cometas, asi que ten cuidado. Si ganas en menos de 10 intentos ganaras tickets equivalentes a 10-LosIntentosQueHagas');
            print('');

            #Declaración de variables
            numAle := 0;
            numAle := rand(1, 1000);
            numAdivinar := numAle // 1;
            intentos := 0;

            #Elija Su número!!!!
            print('Elija el número');
            read(n);

            #Sentencias de control del juego
            while(n < 0 or n>1000) do
                print('No se puede poner un número negativo o superior a 1000, prueba de nuevo');
                read(n);
            end_while

            while(n <> numAdivinar) do
                intentos++;
                if(n > numAdivinar) then
                    print('Estas por encima de número, -10 creditos');
                    creditos -:= 10;
                    read(n);
                    while(n < 0 or n>1000) do
                        print('No se puede poner un número negativo o superior a 1000, prueba de nuevo');
                        read(n);
                    end_while
                else if (n < numAdivinar) then
                        print('Estas por debajo del numero -10 creditos');
                        creditos -:= 10;
                        read(n);
                        while(n < 0 or n>1000) do
                            print('No se puede poner un número negativo o superior a 1000, prueba de nuevo');
                            read(n);
                        end_while
                    end_if
                end_if
            end_while

            #Final del juego
            if(n = numAdivinar) then
                print('Felicidades has adivinado el número, has ganado 100 creditos');
                creditos +:= 100;
                if(intentos <= 10) then
                    print('Tambien has logrado conseguir tickets');
                    tickets +:= 10 - (intentos - 1);
                end_if
            end_if

        case 2:
            clear_screen;
            place(0,0);
            print('Bienvenido a la ruleta de la suerte');
            print('');
            print('Este es un juego de puro azar y riesgo, hecho para los más ludopatas, puedes ganar o perder varios cretidos asi que ten cuidado');
            print('Premios y perdidas: ');
            print('1) 2000 Creditos!! o perder todos tus creditos, un gameOver (%2)');
            print('2) Ganar o perder 1000 Creditos (%6)');
            print('3) Ganar o perder 500 Creditos (%12)');
            print('4) Ganar o perder 100 Creditos (20%)');
            print('5) Ganar o perder 10 Creditos (60%)');
            print('');
            print('Confirmas de que te la quieres jugar? S/N');
            read_string(conf);

            #Control de la confirmación
            while(conf <> 'S' and conf <> 'N' and conf <> 's' and conf <> 'n') do
                conf := '';
                print('Opción no valida, debes respondes S/N');
                read_string(conf);
            end_while

            #Variable booleana para el bucle while
            if(conf = 'S' or conf = 's') then
                cont := true;
            else
                cont := false;
            end_if

            #Control del número de tickets
            if(tickets <= 0 and cont <> false) then
                print('Número de tickets insuficiente para la ruleta');
                cont := false;
            else
                tickets--;
            end_if

            #Variable del aleatorio
            numAle := rand(0, 100);

            while(cont) do
                if(numAle >= 0 and numAle <= 2) then
                    balanza := rand(0,100);
                    if(balanza >= 0 and balanza <= 30) then
                        print('Has ganado 2000 creditos!!');
                        creditos +:= 2000;
                    else
                        print('Has perdido todo... (T-T)');
                        creditos -:= creditos;
                    end_if
                end_if

                if(numAle > 2 and numAle <= 8) then
                    balanza := rand(0,100);
                    if(balanza >= 0 and balanza <= 30) then
                        print('Has ganado 1000 creditos (O-O)');
                        creditos +:= 1000;
                    else
                        print('Has perdido 1000 creditos');
                        creditos -:= 1000;
                    end_if
                end_if

                if(numAle > 8 and numAle <= 20) then
                    balanza := rand(0,100);
                    if(balanza >= 0 and balanza <= 30) then
                        print('Has ganado 500 creditos');
                        creditos +:= 500;
                    else
                        print('Has perdido 500 creditos');
                        creditos -:= 500;
                    end_if
                end_if

                if(numAle > 20 and numAle <= 40) then
                    balanza := rand(0,100);
                    if(balanza >= 0 and balanza <= 30) then
                        print('Has ganado 100 creditos');
                        creditos +:= 100;
                    else
                        print('Has perdido 100 creditos');
                        creditos -:= 100;
                    end_if
                end_if

                if(numAle > 40 and numAle <= 100) then
                    balanza := rand(0,100);
                    if(balanza >= 0 and balanza <= 40) then
                        print('Has ganado 10 creditos');
                        creditos +:= 10;
                    else
                        print('Has perdido 10 creditos');
                        creditos -:= 10;
                    end_if
                end_if

                #Seguimos con la ruleta?
                print('Quieres continuar? S/N');
                read_string(conf);
                while(conf <> 'S' and conf <> 'N' and conf <> 's' and conf <> 'n') do
                    conf := '';
                    print('Opción no valida, debes respondes S/N');
                    read_string(conf);
                end_while

                if(conf = 'S' or conf = 's') then
                    numAle := rand(0, 100);
                else
                    cont := false;
                end_if

                #Control del número de tickets interno
                if(tickets <= 0 and cont <> false) then
                    print('Número de tickets insuficiente para la ruleta');
                    cont := false;
                else
                    tickets--;
                end_if

            end_while


        case 3:
            clear_screen;
            place(0,0);
            print('Bienvenido al juego del mentiroso');
            print('');
            print('En este juego vas a participar contra la maquina, esta te va a tirar un dado, y te dira lo que ha salido, pero deberas de elegir si creerle o no');
            print('Si aciertas, tanto al creerle como al no creerle, ganarás 150 creditos sino perderas la misma cantidad. Si aciertas ganarás un ticket');
            juega := true;
            
            while(juega) do
                clear_screen;
                place(0,0);
                tiraD := rand(1, 7) // 1;
                while(tiraD = 7) do
                    tiraD := rand(1, 7) // 1;
                end_while

                probMentir := rand(1, 100);

                if(probMentir > 50) then
                    tiraDM := rand(1, 7) // 1;
                    while(tiraD = tiraDM or tiraDM = 7) do
                        tiraDM := rand(1, 7) // 1;
                    end_while
                    print('El número que ha salido en el dado es:');
                    print(tiraDM);
                    verdad := false;
                else
                    print('El número que ha salido en el dado es:');
                    print(tiraD);
                    verdad := true;
                end_if

                print('Será verdad, o es mentira? Escribe S para decir que le crees, o escribe N para decir que es mentira');
                read_string(VM);

                while(VM <> 'S' and VM <> 'N' and VM <> 's' and VM <> 'n') do
                    conf := '';
                    print('Opción no valida, debes respondes S/N');
                    read_string(VM);
                end_while

                if(VM = 'S' or VM = 's') then
                    if(verdad) then
                        print('Felicidades, has ganado, era verdad');
                        tickets++;
                        creditos +:= 150;
                    else
                        print('Era mentira y te lo has creido, que mal');
                        creditos -:= 150;
                    end_if
                else
                    if(verdad = false) then
                        print('Felicidades, has ganado, era mentira');
                        tickets++;
                        creditos +:= 150;
                    else
                        print('Era verdad no confiaste, que mal');
                        creditos -:= 150;
                    end_if
                end_if

                print('Quieres continuar jugando?');
                read_string(text);

                while(text <> 'S' and text <> 'N' and text <> 's' and text <> 'n') do
                    conf := '';
                    print('Opción no valida, debes respondes S/N');
                    read_string(VM);
                end_while

                if(text = 'S' or text = 's') then
                    juega := true;
                else
                    juega := false;
                end_if
                
            end_while

        default:
            clear_screen;
            place(0,0);
            print('Saliendo del programa....');
    end_switch;

while(option <> 0)