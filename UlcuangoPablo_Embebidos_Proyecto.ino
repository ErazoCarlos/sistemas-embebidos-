/*
 * UNIVERSIDAD TÉCNICA DEL NORTE
 * FICA-CITEL
 * SISTEMAS EMBEBIDOS
 * NOMBRE: Ulcuango Pablo
 * FECHA: 15-12-2020
 * PROYECTO FINAL PRIMER BIMESTRE 
 */
#define tam_entrada 88
double signal_entrada[tam_entrada] = {
-1.6000000e+001,
-2.5000000e+001,
-3.4000000e+001,
-4.6000000e+001,
-6.8000000e+001,
-9.7000000e+001,
-1.4000000e+002,
-1.7100000e+002,
-1.8400000e+002,
-1.4100000e+002,
-8.0000000e+001,
-6.0000000e+000,
4.9000000e+001,
7.2000000e+001,
7.1000000e+001,
4.8000000e+001,
2.5000000e+001,
1.3000000e+001,
6.0000000e+000,
-3.0000000e+000,
-1.1000000e+001,
-1.6000000e+001,
-1.7000000e+001,
-1.5000000e+001,
-1.4000000e+001,
-1.6000000e+001,
-1.6000000e+001,
-1.8000000e+001,
-1.9000000e+001,
-1.9000000e+001,
-1.8000000e+001,
-1.9000000e+001,
-1.9000000e+001,
-2.2000000e+001,
-2.0000000e+001,
-2.0000000e+001,
-2.3000000e+001,
-2.3000000e+001,
-2.0000000e+001,
-2.3000000e+001,
-2.2000000e+001,
-2.4000000e+001,
-2.3000000e+001,
-2.2000000e+001,
-2.5000000e+001,
-2.5000000e+001,
-2.8000000e+001,
-2.7000000e+001,
-2.7000000e+001,
-3.1000000e+001,
-2.8000000e+001,
-3.1000000e+001,
-3.2000000e+001,
-3.2000000e+001,
-3.5000000e+001,
-3.6000000e+001,
-3.7000000e+001,
-3.6000000e+001,
-3.9000000e+001,
-3.7000000e+001,
-4.3000000e+001,
-4.2000000e+001,
-4.5000000e+001,
-4.4000000e+001,
-4.4000000e+001,
-4.4000000e+001,
-4.8000000e+001,
-4.7000000e+001,
-4.9000000e+001,
-4.8000000e+001,
-5.1000000e+001,
-4.8000000e+001,
-4.8000000e+001,
-4.7000000e+001,
-4.4000000e+001,
-4.2000000e+001,
-4.2000000e+001,
-4.0000000e+001,
-4.1000000e+001,
-3.7000000e+001,
-3.3000000e+001,
-3.3000000e+001,
-2.8000000e+001,
-2.4000000e+001,
-2.3000000e+001,
-1.8000000e+001,
-1.7000000e+001,
-1.2000000e+001,
};

#define tam_impulso 29
double  impulso[tam_impulso] = {
  -0.0018225230f, -0.0015879294f, +0.0000000000f, +0.0036977508f, +0.0080754303f, +0.0085302217f, -0.0000000000f, -0.0173976984f,
  -0.0341458607f, -0.0333591565f, +0.0000000000f, +0.0676308395f, +0.1522061835f, +0.2229246956f, +0.2504960933f, +0.2229246956f,
  +0.1522061835f, +0.0676308395f, +0.0000000000f, -0.0333591565f, -0.0341458607f, -0.0173976984f, -0.0000000000f, +0.0085302217f,
  +0.0080754303f, +0.0036977508f, +0.0000000000f, -0.0015879294f, -0.0018225230f
};

//--------------------variables para suavizado de la señal----------------------------------------------------------
# define alpha 0.25 // no tiene q ser <1
//alpha=1/2n+1;
float suavizado = 0.0; //salida para el suavizado
float signalActual = 0; //varaible para guardar temporalmente los datos de la señal de entrada
int cont=0;

//-------------------variable para S/N------------------------------------------------------------------------------
float SNR = 0; //relacion S/N
float P_signal=0;
float P_ruido=0;

//-------------------variable para filto----------------------------------------------------------------------------
double filtro[tam_entrada + tam_impulso];


void setup() {
  Serial.begin(9600);
//--------------------------------convolucion------------------------------------------------------------------------
  for (int i = 0; i < (tam_entrada + tam_impulso); i++) {
    filtro[i] = 0;
  }
  for (int j = 0; j < tam_entrada; j++) {
    for (int k = 0; k < tam_impulso; k++) {
      filtro[j + k] = filtro[j + k] + signal_entrada[j] * impulso[k];
    }
  }
}
void loop() {
//---------------------------------FILTRO MEDIO (PROMEDIO)--------------------------------------------------------------------------------
  signalActual = signal_entrada[cont];
  
  suavizado = (alpha * signalActual) + ((1 - alpha) * suavizado);

//----------------------------------SNR--------------------------------------------------------------------------------------------------
  P_signal=pow(0.707 * (signalActual), 2);
  P_ruido=pow(0.707 * (signalActual - suavizado), 2);
  
  SNR = 10 * log10(P_signal / P_ruido);

//---------------------------------GRAFICAR----------------------------------------------------------------------------------------------
  Serial.print(signalActual);
  Serial.print(',');
  Serial.print(suavizado + 500);
  Serial.print(',');
  Serial.print(filtro[cont] + 1000);
  Serial.print(',');
  Serial.println(SNR+1500);

  cont++;
//-------------------------------Reestablecer el contador---------------------------------------------------------------------------------
  if (cont >= tam_entrada - 1) {
    cont = 0;
  }

  delay(100);
}
