#include <iostream>
#include <vector>

using namespace std;

class Relationship;
class City;

class City
{
public:
  vector<Relationship*> relationships;

  string name;

  City(string city_name)
  {
    name = city_name;
  }
};

class Relationship {
private:

public:
  City* from;
  City* to;
  int kilometers_distance = 0;

  Relationship (City* from_city, City* to_city, int km)
  {
    from = from_city;
    to = to_city;
    kilometers_distance = km;
  }

  //virtual ~Relationship ();
};

void backtracking(City* city)
{
  cout<<city->name<<endl;
  for(int i=0;i<city->relationships.size();i++)
    backtracking(city->relationships[i]->to);
}

int CalculateDistance(City* city, string destination)
{
  for(int i=0;i<city->relationships.size();i++)
  {
    if(city->relationships[i]->to->name == destination)
      return city->relationships[i]->kilometers_distance;

    int last_distance = CalculateDistance(city->relationships[i]->to, destination);
    if(last_distance != 999999)
      return city->relationships[i]->kilometers_distance + last_distance;
  }

  return 999999;
}

class Map {
private:

public:
  City* start_city;
  Map ()
  {
    start_city = NULL;
  }

  void AddCity(string city_name) {
    City* new_city = new City(city_name);

    if (start_city == NULL) {
      start_city = new_city;
    }
  }

  void RelateCities(City* from_city, City* to_city, int km) {
    Relationship* relation = new Relationship(from_city, to_city, km);
    from_city->relationships.push_back(relation);
  }

  City* SearchCity(City* current_city, string city_name)
  {
    if (current_city->name == city_name) {
      return current_city;
    }

    for(int i=0;i<current_city->relationships.size();i++)
    {
      return SearchCity(current_city->relationships[i]->to, city_name);
    }

    return NULL;
  }

  City* SearchCity(string city_name)
  {
    return SearchCity(start_city, city_name);
  }

};

void CreateCity(Map &map){

  while (true) {
    string new_city_name, existing_city_name;
    City* existing_city = NULL;
    int km;
    char restart;

    if (map.start_city == NULL) {
      cout << "La lista se encuentra vacía, ingrese el nombre para la ciudad principal:" << endl;
      cin >> new_city_name;
      map.AddCity(new_city_name);
      cout << endl;

      cout << "¡La ciudad principal fue agregada!" << endl;
    }
    else
    {
      cout << "Ingrese el nombre de la ciudad:" << endl;
      cin >> new_city_name;
      cout << endl;

      do {
        cout << "Ingrese la ciudad adyacente para formar la relación:" << endl;
        cin >> existing_city_name;
        cout << endl;

        existing_city = map.SearchCity(existing_city_name);

        if (existing_city == NULL) {
          cout << "No se encontró la ciudad, por favor ingresela nuevamente:" << '\n';
          //std::cout << map.start_city->name << '\n';
        }

      } while(existing_city == NULL);

      cout << "Ingrese la distancia entre las ciudades:" << endl;
      cin >> km;

      map.RelateCities(existing_city, new City(new_city_name), km);
      cout << "¡Nueva ciudad agregada!" << endl;
    }

    cout << "¿Desea agregar una nueva ciudad?, ingrese 's' o 'n' como su respuesta:" << endl;
    cin >> restart;

    if (restart != 's') {
      break;
    }
  }
}

void CalculateDistanceOption(Map &map) {
  string origin_city_name, destination_city_name;

  City* origin_city = NULL;
  City* destination_city = NULL;
  int km_distance = 0;

  // do {
  //   cout << "Ingrese la ciudad de origen:" << endl;
  //   cin >> origin_city_name;
  //   cout << endl;
  //
  //   origin_city = map.SearchCity(origin_city_name);
  //
  //   if (origin_city == NULL) {
  //     cout << "No se encontró la ciudad de origen, por favor ingresela nuevamente:" << endl;
  //   }
  //
  // } while(origin_city == NULL);

  // do {
  //   cout << "Ingrese la ciudad de destino:" << endl;
  //   cin >> destination_city_name;
  //   cout << endl;
  //
  //   destination_city = map.SearchCity(destination_city_name);
  //
  //   if (destination_city == NULL) {
  //     cout << "No se encontró la ciudad de destino, por favor ingresela nuevamente:" << endl;
  //   }
  //
  // } while(destination_city == NULL);

  cout << "Ingrese la ciudad de destino:" << endl;
  cin >> destination_city_name;
  cout << endl;

  destination_city = map.SearchCity(destination_city_name);

  km_distance = CalculateDistance(map.start_city, destination_city_name);
  cout << endl << endl;
  cout << "La distancia entre " << map.start_city->name << " y " << destination_city_name << endl;
  cout << "es de " << km_distance << " kilometros" << endl;

}

int main()
{
  Map map;

  while (true) {
    int option;
    char answer;

    cout << "*****************************************" << endl;
    cout << "* 1) Agregar cuidad                     *" << endl;
    cout << "* 2) Calcular distancia entre ciuidades *" << endl;
    cout << "* 3) Listar ciudades                    *" << endl;
    cout << "*****************************************" << endl;
    cout << endl;

    cout << "Ingrese una opción:" << endl;
    cin >> option;
    cout << endl;

    switch (option) {
      case 1:
        CreateCity(map);
        break;
      case 2:
        CalculateDistanceOption(map);
        break;
      case 3:
        backtracking(map.start_city);
        break;
    }

    cout << endl;
    cout << "¿Desea volver al munu principal?, ingrese 's' o 'n' como su respuesta:" << endl;
    cin >> answer;

    if (answer != 's') {
      break;
    }

    cout << endl << endl;
  }
  return 0;
}
