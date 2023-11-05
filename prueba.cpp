#include <fstream>
#include <iostream>
#include <vector>

struct tRCandidato
{
  int numero;
  string nombre;
};
typedef tRCandidato tVecCandidatos[10];

struct tRLista
{
  int numero;
  string nombre;
  tVecCandidatos candidatos;
};

struct tRVoto
{
  int numero;
  string genero;
  int edad;
};
typedef std::vector<tRVoto> tVecVotos;

// prototipos
void guardarListaEnArchivo();
void pedirLista(tRLista &rLista, bool &fin);
void pedirVoto(tRVoto &rVoto, bool &fin);
void guardarVotosPorListaEnArchivo(tVecVotos &vVotos);
void ordenarPorNumeroLista(tVecVotos &vVotos);

void guardarVotosPorListaEnArchivo(tVecVotos &vVotos, int cantVotos)
{
  tRVoto rVoto;
  bool fin;

  FILE *fVoto;
  fVoto = fopen("votos.dat", "wb");

  if (!fVoto)
  {
    std::cerr << "Error al abrir el archivo de votos" << std::endl;
    return;
  }

  fVoto.fwrite(rVoto, sizeof(cantVotos), 1, fVoto);

  for (int i = 0; i < cantVotos; i++)
  {
    fVoto.fwrite(reinterpret_cast<const char *>(&vVotos[i]), sizeof(tRVoto));
  }

  fVoto.fclose();
}

void pedirVoto(tRVoto &rVoto, bool &fin)
{
  std::cout << "Ingrese el número de lista (0 para finalizar): ";
  std::cin >> rVoto.numero;

  if (rVoto.numero == 0)
  {
    fin = true;
    return;
  }

  std::cout << "Ingrese el género (M/F): ";
  std::cin >> rVoto.genero;

  std::cout << "Ingrese la edad: ";
  std::cin >> rVoto.edad;
}