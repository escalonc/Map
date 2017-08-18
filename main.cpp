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

  City(string name)
  {
    this->name = name;
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
  //cout<<city->name<<endl;
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
    for(int i=0;i<current_city->relationships.size();i++)
    {
      if (current_city->name == city_name) {
        return current_city;
      }

      return SearchCity(current_city->relationships[i]->to, city_name);
    }

    return NULL;
  }

  City* SearchCity(string city_name)
  {
    return SearchCity(start_city, city_name);
  }

};

void CreateCity(Map map){

  while (true) {
    string new_city_name, existing_city_name;
    City* existing_city;
    int km;

    if (map.start_city == NULL) {
      cout << "La lista se encuentra vacía, ingrese el nombre para la ciudad principal:" << endl;
      cin >> new_city_name;
      map.AddCity(new_city_name);
      cout << endl;
      cout << "¡La ciudad principal fue creada!" << endl;
    }
    else
    {
      cout << "Ingrese el nombre de la ciudad:" << endl;
      cin >> new_city_name;
      cout << endl;
      cout << "Ingrese la ciudad adyacente para formar la relación:" << endl;
      cin >> existing_city_name;
      cout << endl;
      cout << "Ingrese la distancia entre las ciudades:" << endl;
      cin >> km;

    }
  }


}

int main()
{
  while (true) {
    int option;
    char answer;
    Map map;

    cout << "*****************************************" << endl;
    cout << "* 1) Agregar cuidad                     *" << endl;
    cout << "* 2) Calcular distancia entre ciuidades *" << endl;
    cout << "*****************************************" << endl;
    cout << endl;

    cout << "Ingrese una opción:" << endl;
    cin >> option;

    switch (option) {
      case 1:
        CreateCity(map);
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
