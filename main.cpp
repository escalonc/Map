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

int main()
{
  cout << "*****************************************" << endl;
  cout << "* 1) Agregar cuidad                     *" << endl;
  cout << "* 2) Calcular distancia entre ciuidades *" << endl;
  cout << "*****************************************" << endl;
  cout << endl;
  cout << "Ingrese una opción:" << endl;

  City* sps = new City("SPS");
  City* tegus = new City("Tegus");
  City* tela = new City("Tela");
  City* ceiba = new City("Ceiba");
  City* tocoa = new City("Tocoa");
  City* otro = new City("Otro pueblo");

  Relationship* sps_to_tegus = new Relationship(sps, tegus, 50);
  Relationship* sps_to_tela = new Relationship(sps, tela, 20);
  Relationship* tela_to_ceiba = new Relationship(tela, ceiba, 10);
  Relationship* ceiba_to_tocoa = new Relationship(ceiba, tocoa, 60);
  Relationship* ceiba_to_otro = new Relationship(ceiba, otro, 70);

  sps->relationships.push_back(sps_to_tegus);
  sps->relationships.push_back(sps_to_tela);
  tela->relationships.push_back(tela_to_ceiba);
  ceiba->relationships.push_back(ceiba_to_tocoa);
  ceiba->relationships.push_back(ceiba_to_otro);

  return 0;
}
