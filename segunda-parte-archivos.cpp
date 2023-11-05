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
  string nombre;
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

struct tBanca
{
  int votoBanca;
};
typedef tBanca tMatrizBanca[12][5];
int vectorNumBancaOb[5];

// prototipos
void guardarListasEnArchivo();
void pedirLista(tRLista &rLista, bool &fin);
void ingresarVoto(tRVoto &rVoto, bool &fin);

void guardarVotosEnArchivo(std::vector<tRVoto> &vVotos, int maxVotos);
void pedirVoto(tRVoto &rVoto);
void ordenarPorNumeroLista(std::vector<tRVoto> &vVotos, int cantVotos);

void imprimirVotos(std::vector<tRVoto> &vVotos, int cantVotos);
void leerArchivo(const char *nombreArchivo);

// Punto 2
void guardarListasEnArchivo()
{
  tRLista rLista;
  bool fin;

  FILE *fLista;
  fLista = fopen("listas.dat", "wb");

  for (int i = 0; i < numListas; ++i)
  {

    fin = false;

    pedirLista(rLista, fin);

    while (!fin)
    {
      fwrite(&rLista, sizeof(rLista), 1, fLista);
      pedirLista(rLista, fin);
    }
  }

  fclose(fLista);
}

void pedirLista(tRLista &rLista, bool &fin)
{

  printf("\nInresar datos de una Lista\n");
  printf("Numero de Lista (0=fin)=");
  cin >> rLista.numero;
  cin.ignore();

  if (rLista.numero != 0)
  {
    fin = false;
    printf("\nNombre de Lista=");
    cin.ignore();
    getline(cin, rLista.nombre);

    for (int i = 0; i < candidatosPorLista; ++i)
    {
      printf("\nNombre del candidato %d =", i + 1);
      getline(cin, rLista.candidatos[i].nombre);
    }
  }
  else
    fin = true;
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
  cout << "Ingrese el número de lista votado (entre 1 y 7, 0 en blanco, otros nulos): ";
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

void leerArchivo(const char *nombreArchivo)
{
  FILE *archivo = fopen(nombreArchivo, "rb");

  if (archivo == NULL)
  {
    std::cout << "Error al abrir el archivo." << std::endl;
    return;
  }

  tRVoto votoLeido;
  while (fread(&votoLeido, sizeof(votoLeido), 1, archivo) == 1)
  {

    std::cout << "Número de Lista: " << votoLeido.numeroLista << std::endl;
    std::cout << "Género: " << votoLeido.genero << std::endl;
    std::cout << "Edad: " << votoLeido.edad << std::endl;
    std::cout << std::endl;
  }

  fclose(archivo);
}

int main()
{
  int cantVotos;

  cout << "Ingrese la cantidad de votos emitidos: ";
  cin >> cantVotos;

  std::vector<tRVoto> vVotos(cantVotos);

  guardarListasEnArchivo();
  guardarVotosEnArchivo(vVotos, cantVotos);
  leerArchivo("votos.dat");

  return 0;
}