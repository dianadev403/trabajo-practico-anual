#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

#define numListas 7
#define candidatosPorLista 10

string t_columna[] = {"Lista", "Voto", "% Valido", "Banca 1", "Banca 2", "Banca 3", "Banca 4", "Banca 5", "Ganan"};

struct tRCandidato
{
  string nombre;
};
typedef tRCandidato tVecCandidatos[candidatosPorLista];

struct tRLista
{
  int numero;
  string nombreLista;
  tVecCandidatos candidatos;
};
typedef tRLista tVecListas[numListas];

struct tRVoto
{
  int numeroLista;
  string genero;
  int edad, cantHombre, cantMujer, cantOtro, cant16_18, cant18_30, cant30_50, cantmas50;
  bool valido;
};
typedef tRVoto tVecVotos;

struct tBanca
{
  int votoBanca;
};
typedef tBanca tMatrizBanca[12][5];
int vectorNumBancaOb[5];

// prototipos
void guardarListasEnArchivo();
void pedirLista(tRLista &rLista);

void guardarVotosEnArchivo(std::vector<tRVoto> &vVotos, int maxVotos);
void pedirVoto(tRVoto &rVoto);
void ordenarPorNumeroLista(std::vector<tRVoto> &vVotos, int cantVotos);

void imprimirVotos(std::vector<tRVoto> &vVotos, int cantVotos);
int cantRegistrosVotos(FILE *archivo, tRVoto rVoto);
int cantRegistrosListas(FILE *archivo, tRLista rLista);
void cargarVectoresDesdeArchivo(FILE *archivo, tVecListas vListas, tVecVotos vVotos[]);

// Punto 2
void guardarListasEnArchivo()
{
  tRLista rLista;

  FILE *fLista;
  fLista = fopen("listas.dat", "wb");

  for (int i = 0; i < numListas; ++i)
  {
    pedirLista(rLista);
    fwrite(&rLista, sizeof(rLista), 1, fLista);
  }

  fclose(fLista);
}

void pedirLista(tRLista &rLista)
{
  cout << "Ingresar Numero de Lista: ";
  cin >> rLista.numero;
  cin.ignore();

  cout << "Ingresar Nombre de Lista: ";
  getline(cin, rLista.nombreLista);

  for (int j = 0; j < candidatosPorLista; ++j)
  {
    cout << "Ingresar Nombre del candidato " << j + 1 << ": ";
    getline(cin, rLista.candidatos[j].nombre);
  }
}

// Punto 3
void guardarVotosEnArchivo(std::vector<tRVoto> &vVotos, int cantVotos)
{
  tRVoto rVoto;

  FILE *fVoto;
  fVoto = fopen("votos.dat", "wb");

  for (int i = 0; i < cantVotos; ++i)
  {
    pedirVoto(rVoto);

    vVotos[i].edad = rVoto.edad;
    vVotos[i].genero = rVoto.genero;
    vVotos[i].numeroLista = rVoto.numeroLista;
  }

  ordenarPorNumeroLista(vVotos, cantVotos);

  for (int i = 0; i < cantVotos; ++i)
  {
    fwrite(&vVotos[i], sizeof(vVotos[i]), 1, fVoto);
  }

  fclose(fVoto);
}

// Ordenamos por numero de lista usando burbujeo
void ordenarPorNumeroLista(std::vector<tRVoto> &vVotos, int cantVotos)
{
  tRVoto aux;

  for (int i = 0; i < cantVotos - 1; ++i)
  {
    for (int j = 0; j < cantVotos - i - 1; ++j)
    {
      if (vVotos[j].numeroLista > vVotos[j + 1].numeroLista)
      {
        aux = vVotos[j];
        vVotos[j] = vVotos[j + 1];
        vVotos[j + 1] = aux;
      }
    }
  }
}

void pedirVoto(tRVoto &rVoto)
{
  cout << "Ingrese el numero de lista votado (entre 1 y 7, 0 en blanco, otros nulos): ";
  cin >> rVoto.numeroLista;

  // if (rVoto.numeroLista < 0 || rVoto.numeroLista > 7)
  // {
  //   rVoto.esValido = false;
  // }
  // else
  // {
  //   rVoto.esValido = true;
  // }

  cout << "Ingrese el género del votante (Femenino, Masculino, Otro): ";
  cin >> rVoto.genero;

  cout << "Ingrese la edad del votante en años: ";
  cin >> rVoto.edad;
}


int cantRegistrosVotos(FILE *archivo, tRVoto rVoto)
{
  
  int cantRegistros = 0;
  fseek(archivo, 0, SEEK_END); // nos posicionamos al final del archivo
  cantRegistros = ftell(archivo) / sizeof(rVoto);
  return cantRegistros;
}


int cantRegistrosListas(FILE *archivo, tRLista rLista)
{
  
  int cantRegistros = 0;
  fseek(archivo, 0, SEEK_END); // nos posicionamos al final del archivo
  cantRegistros = ftell(archivo) / sizeof(rLista); 
  return cantRegistros;
}

void cargarVectoresDesdeArchivo(FILE *archivo, tVecListas vListas, tVecVotos vVotos[])
{
  tRLista rLista;
  tRVoto rVoto;

  int i = 0;
  int j = 0;

  while (fread(&rLista, sizeof(rLista), 1, archivo) != 0)
  {
    vListas[i] = rLista;
    i++;
  }

  while (fread(&rVoto, sizeof(rVoto), 1, archivo) != 0)
  {
    vVotos[j] = rVoto;
    j++;
  }
}

int main()
{
  int cantVotos;

  cout << "Ingrese la cantidad de votos emitidos: ";
  cin >> cantVotos;

  tVecListas vListas;
  tMatrizBanca mBanca;


  std::vector<tRVoto> vecVotos(cantVotos); 

  guardarListasEnArchivo();
  guardarVotosEnArchivo(vecVotos, cantVotos);

  int bFila = sizeof(mBanca) / sizeof(mBanca[0]);
  int bColumna = sizeof(mBanca[0]) / sizeof(mBanca[0][0]);

  int tamVotos;
  tRVoto rVoto;
  FILE *fVotos = fopen("votos.dat", "rb");

  int tamLista;
  tRLista rLista;
  FILE *fListas = fopen("listas.dat", "rb");

  tamVotos = cantRegistrosVotos(fVotos, rVoto);
  tamLista = cantRegistrosListas(fListas, rLista);

  tVecVotos vVotos[tamVotos];
  tVecListas vListas[tamLista];

  cargarVectoresDesdeArchivo(fListas, vListas, vVotos);

  return 0;
}