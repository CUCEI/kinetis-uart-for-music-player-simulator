#include "main.h"


void delay(int a){
	int i;
	for(i=0;i<a;i++);
	
}

 

int main(void){
	
	    SIM_SCGC5  = 0x00000800;
		PORTC_PCR0 = 0x00000100;
		PORTC_PCR1 = 0x00000100;
		PORTC_PCR2 = 0x00000100;
		PORTC_PCR3 = 0x00000100;
		PORTC_PCR4 = 0x00000100;
		PORTC_PCR5 = 0x00000100;
		PORTC_PCR6 = 0x00000100;
		PORTC_PCR7 = 0x00000100;
		PORTC_PCR8 = 0x00000100;
		PORTC_PCR9 = 0x00000100;
		GPIOC_PDDR = 0xffffffff;
	
  // 0 para que micro no mande odd parity
	
	unsigned char comando_1;
	int paridad = 0;
	char ban_paso1 = 0;
	unsigned char mascara_cmd;
	unsigned char comando_2;
	unsigned char checksum;
	unsigned char comando_3;
   	unsigned char accion;
   	unsigned char velocidad;
	unsigned int delay_deb1 = 1500000;      // ojo ajustar
	unsigned int delay_deb2 = 6000000;
   	unsigned char bajos=0;
   	unsigned char medios=0;
   	unsigned char altos=0;
   	
   	enum velocidades {
   		
   		nada,
   		ms_100,
   		ms_200,
   		ms_500,
   		ms_1000
   	};
   	
   	
	enum acciones {
		
		nadas,
		play,
		pause,
		stop,
		fw,
		rw,
		skip,
		prev,
		bajos_mas,
		bajos_menos,
		medios_mas,
		medios_menos,
		altos_mas,
		altos_menos,
		album
		
	};
	
	
	put("\r\nCONTROLES DE REPRODUCTOR ON\r\n");

    if (paridad == 1)
    UART0_C1 = UART0_C1 | 0x03;  // modo paridad odd

    
    
    while(TRUE)
	{
	
    	
    	accion    = nada;
    	velocidad = nada;
    	
    	
    	while (ban_paso1 == 0) {
    	  comando_1 = in_char();
		if(comando_1 == 196 || comando_1 == 230 || comando_1 == 38  )
			ban_paso1=1;   
		else
		put("\r\nMENSAJE NO VALIDO\r\n");	
                            	}
    	ban_paso1=0;
    	
    	put("\r\nVALIDO\r\n");
    	put("\r\n esperando 2 byte\r\n");
    	
    	comando_2 = in_char();
    	
    	put("\r\ningrese checksum\r\n");
    	
    	comando_3 = in_char();
    	
    	checksum = comando_1 ^ comando_2 ;
    	
    	out_char(checksum);
    	put("\r\n\r\n");
    	out_char(checksum-128);
    	
    	if( (checksum & 0x7f) == (comando_3 & 0x7f) ){
    	
    	switch(comando_1){
    	
    	case (196):  put("\r\nahorita no joven, solo hay 1 album\r\n"); break;
    	
    	case (230):    put("\r\nentramos a comando de ecualizadores\r"); 
    	               mascara_cmd = comando_2 & 0x07 ;
    	
    	                  switch(mascara_cmd){
    	                  
    	                  case(0): accion = altos_menos; put("\r\nagudos_menos\r\n");  break;
    	                  case(1): accion = medios_menos; put("\r\nmedios_menos\r\n"); break;	  
    	                  case(3): accion = bajos_menos; put("\r\nbajos_menos\r\n");  break; 
    	                  case(4): accion = altos_mas;   put("\r\nagudos_mas\r\n");  break;
    	                  case(5): accion = medios_mas;  put("\r\nmedios_mas\r\n");  break;
    	                  case(7): accion = bajos_mas;   put("\r\nbajos_mas\r\n");  break;
    	                  default: accion = nada; break;
    	                                     }
    	
    	
    	                    break;
    	
    	
    	
    	
    	
    	
    	case (38):  put("\r\nentramos a comando de botones\r");
    	          mascara_cmd = comando_2 & 0x07 ;
    	         
    	           switch(mascara_cmd){
    	           
    	           case(0):  accion = play;             switch( comando_2 & 0x60){
    	                                                case(0):   velocidad = ms_500; put("\r\nPLAY con 500ms\r\n"); break;
    	                                                case (32): velocidad = ms_200; put("\r\nPLAY con 200ms\r\n"); break;
    	                                                case (64): velocidad = ms_100; put("\r\nPLAY con 100ms\r\n"); break;
    	                                                case (96): velocidad = ms_1000; put("\r\nPLAY con 1seg\r\n"); break;
    	                                                default: break;
    	                                                                     }  break;
    	          
    	           case(1): accion = pause;put("\r\nPAUSE\r\n"); break;	   
    	           
    	           case(2): accion = stop; put("\r\nSTOP\r\n"); break;
    	           
    	           case(3): accion = fw;               switch( comando_2 & 0x18){
                                                        case(0):   velocidad = ms_500;   put("\r\nFW con 500ms\r\n"); break;
                                                        case (8): velocidad = ms_200;    put("\r\nFW con 200ms\r\n"); break;
                                                        case (16): velocidad = ms_100;   put("\r\nFW con 100ms\r\n"); break;
                                                         case (24): velocidad = ms_1000; put("\r\nFW con 1seg\r\n"); break;
                                                         default: break;
                                                                        }  break;
    	        	 
    	        	   
    	           
    	           case(4): accion = rw;                   switch( comando_2 & 0x18){
                                                       case(0):   velocidad = ms_500; put("\r\nRW con 500ms\r\n"); break;
                                                       case (8): velocidad = ms_200;  put("\r\nRW con 200ms\r\n"); break;
                                                       case (16): velocidad = ms_100; put("\r\nRW con 100ms\r\n"); break;
                                                       case (24): velocidad = ms_1000;put("\r\nRW con 1seg\r\n"); break;
                                                       default: break;
                                                                      }  break;
    	           case(5): accion = skip; put("\r\nSKIP\r\n"); break;
    	           case(6): accion = prev; put("\r\nPREVIEW\r\n"); break; 
    	           default: accion = nada; put("\r\nNADA DE NADA\r\n"); break; 
    	           
    	                               }
    		
                   break;
    	
    	
    default:  accion = nada;  break;
    	           
    	
    	
    	
    	
    	}}
    	else
    		put("\r\nChecksum invalido\r\n");
    	
    	switch(velocidad){
    	           
    	    	case(ms_1000): GPIOC_PDOR |= 16; delay(delay_deb1); GPIOC_PDOR = 0; break;
    	    	case(ms_500):  GPIOC_PDOR |= 16; delay(delay_deb2); GPIOC_PDOR = 0; break;
    	    	case(ms_200):  GPIOC_PDOR |= 32; delay(delay_deb1); GPIOC_PDOR = 0; break;
    	    	case(ms_100):  GPIOC_PDOR |= 32; delay(delay_deb2); GPIOC_PDOR = 0; break;
    	    	default: break;
    	    	}
    	
    	
    	switch(accion){
    	
    	
    	case(play):	   GPIOC_PDOR |= 1;  delay(delay_deb1); GPIOC_PDOR = 0; break;
    	case(pause):   GPIOC_PDOR |= 1;  delay(delay_deb2); GPIOC_PDOR = 0; break;
    	case(stop):    GPIOC_PDOR |= 2;  delay(delay_deb1); GPIOC_PDOR = 0; break;
    	case(fw):      GPIOC_PDOR |= 4;  delay(delay_deb1); GPIOC_PDOR = 0; break;
    	case(rw):      GPIOC_PDOR |= 8;  delay(delay_deb1); GPIOC_PDOR = 0; break;
    	case(skip):    GPIOC_PDOR |= 4;  delay(delay_deb2); GPIOC_PDOR = 0; break;
    	case(prev):    GPIOC_PDOR |= 8;  delay(delay_deb2); GPIOC_PDOR = 0; break;
    	
    	case(bajos_menos):  GPIOC_PDOR |= 64;  delay(delay_deb1); GPIOC_PDOR = 0; break;
    	case(bajos_mas):    GPIOC_PDOR |= 64;  delay(delay_deb2); GPIOC_PDOR = 0; break;
    	case(medios_menos): GPIOC_PDOR |= 64;  delay(delay_deb1); GPIOC_PDOR = 0; break;
    	case(medios_mas):   GPIOC_PDOR |= 64;  delay(delay_deb2); GPIOC_PDOR = 0; break;
    	case(altos_menos):  GPIOC_PDOR |= 64;  delay(delay_deb1); GPIOC_PDOR = 0; break;
    	case(altos_mas):    GPIOC_PDOR |= 64;  delay(delay_deb2); GPIOC_PDOR = 0; break;
    	default: break;
    	              }
    	
    	
	}

	
	return 0;
}
