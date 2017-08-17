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

int calculate_distance(City* city, string destino)
{
  for(int i=0;i<city->relationships.size();i++)
  {
    if(city->relationships[i]->to->name == destino)
      return city->relationships[i]->kilometers_distance;

    int last_distance = calculate_distance(city->relationships[i]->to, destino);
    if(last_distance != 999999)
      return city->relationships[i]->kilometers_distance + last_distance;
  }

  return 999999;
}

int calculate_distance(Relationship* relationship) {
  return calculate_distance(relationship->to, 0) + relationship->kilometers_distance;
}

int main()
{
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

  std::cout << calculate_distance(sps, "Ceiba") << '\n';

  return 0;
}
