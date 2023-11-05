#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

string t_columna[] = {"Lista", "Voto", "% Valido", "Banca 1", "Banca 2", "Banca 3", "Banca 4", "Banca 5", "Ganan"};

struct tVotante
{
  int cantHombre, cantMujer, cantNoBinario, cant16_18, cant18_30, cant30_50, cantmas50;
};
typedef tVotante tVectorVotante[12];

struct tLista
{
  string nombreLista, nombreListaOrdenado, nombreAbreviado, nombreAbreviadoOrdenado;
  bool valido;
};
typedef tLista tVectorLista[12];
int vectorVotos[12];

struct tBanca
{
  int votoBanca;
};
typedef tBanca tMatrizBanca[12][5];
int vectorNumBancaOb[5];

// prototipo
int cantListas();
void cargarListas(tVectorLista &vLis, int &cantLis);
void cargarVotos(tVectorLista &vLis, int &cantLis, tVectorVotante &vVotante);
void verificarVotoValido(tVectorLista &vLis, int &cantLis);
int votoTotal(int vVotos[], tVectorLista &vLis, int &cantLis);
float votoPorcentual(int vLista, int vTotal);
void cargarVotoPorcentual(int vVotos[], tVectorLista &vLis, int &cantLis, int &vTotal);
void ordenarMayorMenorVoto(int vVotos[], int &cantLis, tVectorLista &vLis, int &vTotal);
void cargarVotoPorBanca(tMatrizBanca &mBanca, int vVotos[], tVectorLista &vLis, int &cantLis, int &columna, int &vTotal);
int cantListaMas3Por(int vVotos[], tVectorLista &vLis, int &cantLis, int &vTotal);
void cargarObtieneBanca(tMatrizBanca &mBanca, int &cantLis, int &columna, int vVotos[], tVectorLista &vLis, int &vTotal, int &cantMas3Por);
void mostrarTabla(tMatrizBanca &mBanca, tVectorLista &vLis, int vVotos[], int &cantLis, int &columna, int &vTotal);

int main()
{

  tVectorLista vLista;
  tVectorVotante vVotante;
  tMatrizBanca mBanca;

  int bFila = sizeof(mBanca) / sizeof(mBanca[0]);
  int bColumna = sizeof(mBanca[0]) / sizeof(mBanca[0][0]);

  int cantLis = cantListas() + 2;

  cargarListas(vLista, cantLis);
  cargarVotos(vLista, cantLis, vVotante);

  verificarVotoValido(vLista, cantLis);

  int vTotal = votoTotal(vectorVotos, vLista, cantLis);

  ordenarMayorMenorVoto(vectorVotos, cantLis, vLista, vTotal);

  cargarVotoPorcentual(vectorVotos, vLista, cantLis, vTotal);

  int cantMas3Por = cantListaMas3Por(vectorVotos, vLista, cantLis, vTotal);

  cargarVotoPorBanca(mBanca, vectorVotos, vLista, cantLis, bColumna, vTotal);

  cargarObtieneBanca(mBanca, cantLis, bColumna, vectorVotos, vLista, vTotal, cantMas3Por);

  mostrarTabla(mBanca, vLista, vectorVotos, cantLis, bColumna, vTotal);

  system("pause");
  return 0;
}

int cantListas()
{
  int cantLista;
  cout << "Cuantas listas se presentan: ";
  cin >> cantLista;
  return cantLista;
}
void cargarListas(tVectorLista &vLis, int &cantLis)
{
  cout << endl;
  for (int i = 0; i < cantLis; i++)
  {
    string nombreLista;
    if (i < cantLis - 2)
    {
      cout << "Ingrese abreviatura de la lista: ";
      (i == 0) && cin.ignore();
      getline(cin, nombreLista);
      vLis[i].nombreLista = nombreLista;
    }
    else if (i == cantLis - 2)
      vLis[i].nombreLista = "Votos en blanco";
    else if (i == cantLis - 1)
      vLis[i].nombreLista = "Votos nulos";
  }

  cout << endl;
  cout << "Listas" << endl;
  for (int i = 0; i < cantLis; i++)
  {
    cout << vLis[i].nombreLista << endl;
  }
}
void cargarVotos(tVectorLista &vLis, int &cantLis, tVectorVotante &vVotante)
{
  cout << endl;
  for (int i = 0; i < cantLis; i++)
  {
    int cantVoto;
    cout << "Lista: " << vLis[i].nombreLista << endl;
    cout << "Ingrese cantidad de votos obtenidos: ";
    cin >> cantVoto;
    vectorVotos[i] = cantVoto;

    cout << "Votos: " << cantVoto << endl;

    int vEdad[cantVoto];
    int vGenero[cantVoto];

    for (int j = 0; j < cantVoto; j++)
    {
      cout << endl;
      cout << "Seleccione su genero" << endl;
      cout << "1: Hombre \t 2: Mujer \t 3 al 9: No binario" << endl;
      int sexo;
      cin >> sexo;
      vGenero[j] = sexo;

      cout << "(16 - 70) Ingrese su edad: ";
      int edad;
      cin >> edad;
      vEdad[j] = edad;
    }

    for (int i = 0; i < cantLis; i++)
    {

      int cantH = 0, cantM = 0, cantNB = 0, cant16_18 = 0, cant18_30 = 0, cant30_50 = 0, cantmas50 = 0;

      for (int j = 0; j < cantVoto; j++)
      {
        if (vGenero[j] == 1)
          cantH++;
        if (vGenero[j] == 2)
          cantM++;
        if (vGenero[j] > 2 && vGenero[j] < 10)
          cantNB++;
        if (vEdad[j] > 15 && vEdad[j] < 19)
          cant16_18++;
        if (vEdad[j] > 18 && vEdad[j] < 31)
          cant18_30++;
        if (vEdad[j] > 30 && vEdad[j] < 51)
          cant30_50++;
        if (vEdad[j] > 50)
          cantmas50++;
      }

      vVotante[i].cantHombre = cantH;
      vVotante[i].cantMujer = cantM;
      vVotante[i].cantNoBinario = cantNB;
      vVotante[i].cant16_18 = cant16_18;
      vVotante[i].cant18_30 = cant18_30;
      vVotante[i].cant30_50 = cant30_50;
      vVotante[i].cantmas50 = cantmas50;
    }

    cout << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "Lista\t"
         << "Votos\t"
         << "Num H\t"
         << "Num M\t"
         << "Num B\t"
         << "16-18\t"
         << "19-30\t"
         << "31-50\t"
         << "> 50" << endl;
    cout << ((vLis[i].nombreLista == "Votos en blanco")
                 ? "VB"
             : (vLis[i].nombreLista == "Votos nulos")
                 ? "VN"
                 : vLis[i].nombreLista)
         << "\t" << cantVoto << "\t" << vVotante[i].cantHombre << "\t" << vVotante[i].cantMujer << "\t" << vVotante[i].cantNoBinario << "\t" << vVotante[i].cant16_18 << "\t" << vVotante[i].cant18_30 << "\t" << vVotante[i].cant30_50 << "\t" << vVotante[i].cantmas50 << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << endl;
  }
}
void verificarVotoValido(tVectorLista &vLis, int &cantLis)
{
  for (int i = 0; i < cantLis; i++)
  {
    bool vValido = (vLis[i].nombreLista == "Votos en blanco" || vLis[i].nombreLista == "Votos nulos");
    vLis[i].valido = !vValido;
  }
}
int votoTotal(int vVotos[], tVectorLista &vLis, int &cantLis)
{
  int vTotal = 0;
  for (int i = 0; i < cantLis; i++)
  {
    vLis[i].valido && (vTotal += vVotos[i]);
  }
  return vTotal;
}
float votoPorcentual(int vLista, int vTotal)
{
  float x = vLista, y = vTotal;
  float votoPorcentual = (x / y) * 100;
  return votoPorcentual;
}
void cargarVotoPorcentual(int vVotos[], tVectorLista &vLis, int &cantLis, int &vTotal)
{
  for (int i = 0; i < cantLis; i++)
  {
    float vPorcentual = votoPorcentual(vVotos[i], vTotal);
    if (vLis[i].valido)
    {
      cout << "Lista: " << vLis[i].nombreLista << endl;
      cout << "% Votos validos: " << ((vPorcentual > 10) ? setprecision(4) : setprecision(3)) << vPorcentual << endl;
      cout << endl;
    }
    else
    {
      cout << "Lista: " << vLis[i].nombreLista << endl;
      cout << "% Votos validos: " << 0 << endl;
      cout << endl;
    }
  }
  cout << "---------------------------------------------------------------------------------" << endl;
  cout << endl;
}

void ordenarMayorMenorVoto(int vVotos[], int &cantLis, tVectorLista &vLis, int &vTotal)
{
  for (int i = 0; i < cantLis - 1; i++)
  {
    for (int j = 0; j < cantLis - 1; j++)
    {
      if (vVotos[j] < vVotos[j + 1] && vLis[j].valido && vLis[j + 1].valido)
      {
        int menor = vVotos[j];
        vVotos[j] = vVotos[j + 1];
        vVotos[j + 1] = menor;

        string nombreMenor = vLis[j].nombreLista;
        vLis[j].nombreLista = vLis[j + 1].nombreLista;
        vLis[j + 1].nombreLista = nombreMenor;
      }
    }
  }
}
void cargarVotoPorBanca(tMatrizBanca &mBanca, int vVotos[], tVectorLista &vLis, int &cantLis, int &columna, int &vTotal)
{
  for (int i = 0; i < cantLis; i++)
  {
    cout << "Lista: " << vLis[i].nombreLista << endl;
    float vPorcentual = votoPorcentual(vVotos[i], vTotal);
    for (int j = 0; j < columna; j++)
    {
      if (vLis[i].valido && (vPorcentual > 3))
      {
        mBanca[i][j].votoBanca = vVotos[i] / (!j ? 1 : (j + 1));
        cout << "Banca " << (!j ? 1 : (j + 1)) << ": " << vVotos[i] / (!j ? 1 : (j + 1)) << endl;
      }
      else
      {
        mBanca[i][j].votoBanca = 0;
        cout << 0 << endl;
      }
    }
  }
}

void cargarObtieneBanca(tMatrizBanca &mBanca, int &cantLis, int &columna, int vVotos[], tVectorLista &vLis, int &vTotal, int &cantMas3Por)
{
  int vectorVotosBanca[5];
  int vVotosBanca[cantMas3Por * 5];
  int cantVotosBanca = sizeof(vVotosBanca) / sizeof(vVotosBanca[0]);

  for (int i = 0; i < cantLis; i++)
  {
    for (int j = 0; j < columna; j++)
    {
      float vPorcentual = votoPorcentual(vVotos[i], vTotal);
      switch (i)
      {
      case (0):
        if ((vPorcentual > 3) && vLis[i].valido)
          vVotosBanca[j] = mBanca[i][j].votoBanca;
        break;
      case (1):
        if ((vPorcentual > 3) && vLis[i].valido)
        {
          int k = 5 + j;
          vVotosBanca[k] = mBanca[i][j].votoBanca;
        }
        break;
      case (2):
        if ((vPorcentual > 3) && vLis[i].valido)
        {
          int k = 10 + j;
          vVotosBanca[k] = mBanca[i][j].votoBanca;
        }
        break;
      case (3):
        if ((vPorcentual > 3) && vLis[i].valido)
        {
          int k = 15 + j;
          vVotosBanca[k] = mBanca[i][j].votoBanca;
        }
        break;
      case (4):
        if ((vPorcentual > 3) && vLis[i].valido)
        {
          int k = 20 + j;
          vVotosBanca[k] = mBanca[i][j].votoBanca;
        }
        break;
      case (5):
        if ((vPorcentual > 3) && vLis[i].valido)
        {
          int k = 25 + j;
          vVotosBanca[k] = mBanca[i][j].votoBanca;
        }
        break;
      case (6):
        if ((vPorcentual > 3) && vLis[i].valido)
        {
          int k = 30 + j;
          vVotosBanca[k] = mBanca[i][j].votoBanca;
        }
        break;
      case (7):
        if ((vPorcentual > 3) && vLis[i].valido)
        {
          int k = 35 + j;
          vVotosBanca[k] = mBanca[i][j].votoBanca;
        }
        break;
      case (8):
        if ((vPorcentual > 3) && vLis[i].valido)
        {
          int k = 40 + j;
          vVotosBanca[k] = mBanca[i][j].votoBanca;
        }
        break;
      case (9):
        if ((vPorcentual > 3) && vLis[i].valido)
        {
          int k = 45 + j;
          vVotosBanca[k] = mBanca[i][j].votoBanca;
        }
        break;
      case (10):
        if ((vPorcentual > 3) && vLis[i].valido)
        {
          int k = 50 + j;
          vVotosBanca[k] = mBanca[i][j].votoBanca;
        }
        break;
      case (11):
        if ((vPorcentual > 3) && vLis[i].valido)
        {
          int k = 55 + j;
          vVotosBanca[k] = mBanca[i][j].votoBanca;
        }
        break;

      default:
        break;
      }
    }
  }

  for (int i = 0; i < cantVotosBanca - 1; i++)
  {
    for (int j = 0; j < cantVotosBanca - 1; j++)
    {
      if (vVotosBanca[j] < vVotosBanca[j + 1])
      {
        int menor = vVotosBanca[j];
        vVotosBanca[j] = vVotosBanca[j + 1];
        vVotosBanca[j + 1] = menor;
      }
    }
  }

  for (int i = 0; i < 5; i++)
    vectorVotosBanca[i] = vVotosBanca[i];

  for (int i = 0; i < 5 - 1; i++)
  {
    for (int j = 0; j < 5 - 1; j++)
    {
      if (vectorVotosBanca[j] == vectorVotosBanca[j + 1])
      {
        vectorVotosBanca[j + 1] = -1;
      }
    }
  }

  cout << endl;

  for (int i = 0; i < cantLis; i++)
  {
    int bancaObtenida = 0;
    for (int j = 0; j < columna; j++)
    {
      for (int k = 0; k < columna; k++)
        (vectorVotosBanca[j] == mBanca[i][k].votoBanca) && bancaObtenida++;

      float vPorcentual = votoPorcentual(vVotos[i], vTotal);
      if ((j == (columna - 1)) && vLis[i].valido && (bancaObtenida > 0))
      {
        cout << "La lista " << vLis[i].nombreLista << " obtiene " << bancaObtenida << " banca " << endl;
        vectorNumBancaOb[i] = bancaObtenida;
      }
      else if ((j == (columna - 1)) && (vPorcentual > 3) && vLis[i].valido && (bancaObtenida == 0))
      {
        cout << "La lista " << vLis[i].nombreLista << " obtuvo mas del 3% pero no obtuvo banca" << endl;
        vectorNumBancaOb[i] = 0;
      }
      else if ((j == (columna - 1)) && (vPorcentual < 3) && vLis[i].valido)
      {
        cout << "La lista " << vLis[i].nombreLista << " obtuvo menos del 3%" << endl;
        vectorNumBancaOb[i] = 0;
      }
      else
        vectorNumBancaOb[i] = 0;
    }
  }
}

int cantListaMas3Por(int vVotos[], tVectorLista &vLis, int &cantLis, int &vTotal)
{
  int cantMas3Por = 0;
  for (int i = 0; i < cantLis; i++)
  {
    float vPorcentual = votoPorcentual(vVotos[i], vTotal);
    if (vLis[i].valido && vPorcentual > 3)
      cantMas3Por++;
  }
  return cantMas3Por;
}

void mostrarTabla(tMatrizBanca &mBanca, tVectorLista &vLis, int vVotos[], int &cantLis, int &columna, int &vTotal)
{
  cout << "---------------------------------------------------------------------------------" << endl;
  for (int i = 0; i < 9; i++)
    cout << t_columna[i] << "\t";
  cout << endl;
  for (int i = 0; i < cantLis; i++)
  {
    float vPorcentual;
    if (vLis[i].valido)
      vPorcentual = votoPorcentual(vVotos[i], vTotal);
    else
      vPorcentual = 0;

    cout << ((vLis[i].nombreLista == "Votos en blanco")
                 ? "VB"
             : (vLis[i].nombreLista == "Votos nulos")
                 ? "VN"
                 : vLis[i].nombreLista)
         << "\t" << vVotos[i] << "\t" << ((vPorcentual > 10) ? setprecision(4) : setprecision(3)) << vPorcentual << "\t\t" << mBanca[i][0].votoBanca << "\t" << mBanca[i][1].votoBanca << "\t" << mBanca[i][2].votoBanca << "\t" << mBanca[i][3].votoBanca << "\t" << mBanca[i][4].votoBanca << "\t" << vectorNumBancaOb[i] << endl;
  }
  cout << "---------------------------------------------------------------------------------" << endl;
}
