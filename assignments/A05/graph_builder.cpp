/************************************************
 * Name: Ravishka Rathnasuriya
 * Date: 10/28/2019
 * Professor : Dr. Terry Griffin
 * Assignment : Graph assignment part 1
 * 
 * Description: 
 * This assignment is the first part of the graphing assignment.
 * Here, we create the priority of each cities based on a 
 * city and store it in the heap.The priority is the distance
 * of the cities to a certain city. Lesser the distance, higher 
 * priority. Then it will extract the top number of cities for that city.
 * This code will print the top connected cities of first 10 cities
 * and the last 10 cities. The number of top cities is entered by the
 * user. We need to use the Heap.hpp, JsonFacae.hpp, Geo.hpp files.
 * cities.json file contains 1000 cities with a rank, population,
 * latitude, and longitude, state and growth rate. The structure City
 * is used to create an instance that would help to read the cities and 
 * store in. To compute the distance we used Harversine distance method
 * in Geo.hpp by creating two cordinates. 
 *  Heap class contains insert, extract, bubbleup/down, heapify methods.
 * The algorithm is explained in the below.  
 * 
 * ************************************************/



//#include directories and files.
#include <iostream>
#include <fstream>
#include <string.h>
#include "Heap.hpp"
#include <vector>
#include "JsonFacade.hpp"
#include "json.hpp"
#include "Geo.hpp"

using namespace std;
//used for json
using json = nlohmann::json;


//structure City 
//contains population, Name, longitude, latitude, rank
//state, priority
struct City
{
    int Population;
    string Name;
    double longitude;
    double latitude;
    int rank;
    string state;
    double Priority;

//constructor of the City
    City()
    {
        Population = 0;
        Name = "";
        longitude = 0.0;
        latitude = 0.0;
        rank = 0;
        state = " ";
        Priority = 0.0;
    }

    //used for json file creating an instance obj
    City(json obj)
    {
        Name = obj["city"];
        Population = obj["population"];
        longitude = obj["longitude"];
        latitude = obj["latitude"];
        rank = obj["rank"];
        state = obj["state"];
        Priority = 0.0;
    }
};


//this is the main file. 
int main()
{
    ofstream outfile;  //opens and output file 
    outfile.open("Output.txt");
    //instance for json file
    json obj;
    //create an instance of Cities
    City **Cities;
    //another instance of city
    City *temp;
    //to read the json file
    string filename = "cities.json";
    JsonFacade J(filename);

    //make an heap instance of City for 1001 elements
    Heap<City> H(1001, false);

//get the size of the json file
    int size = J.getSize();
    Cities = new City *[size];
    // loads an array of cities with the json data
    for (int i = 0; i < size; i++)
    {
        obj = J.getNext();
        Cities[i] = new City(obj);
    }


    outfile << "Ravishka Rathnasuriya" << endl << endl; 
    //variables distance to compute distance, number,
    //numOfCities to get how many cities needed to print
    double distance;
    int number = 0;
    int numOfCities = 5;
    //user enters number of cities. 
    cin >> numOfCities;

//the main loop that iterates for 1000 cities
    for (int i = 0; i < 1000; i++)
    {
        //get the latitude and longitude of that city and make a coordinate
        Coordinate A(Cities[i]->latitude, Cities[i]->longitude);

        //only need top 10 and bottom 10 cities 
        if (i < 10 || i > size - 11)
        {
            outfile << i +1 << ": " << Cities[i]->Name << endl;
        }

        //nested for loop that will  iterate 1000 times for cities
        for (int j = 0; j < 1000; j++)
        {
            //get the latitude and longitude of that city and make a coordinate
            Coordinate B(Cities[j]->latitude, Cities[j]->longitude);
            //pass two coordinates to harversine distance method
            distance = HaversineDistance(A, B);
            //store the priority of the cities based on i
            Cities[j]->Priority = distance;
            // insert it to the heap
            H.Insert(Cities[j]);
        }

        //while loop that iterates 1000 times
        while (number < 1000)
        {
            //temp will extract the heap
            temp = H.Extract();
            //only need top 10 and bottom 10 cities
            if (i < 10 || i > size - 11)
            {
                //prints the number of closest cities based on how many
                //user needs
                if (number <=numOfCities)
                {
                    //does not print the same city
                    if (temp->Name != Cities[i]->Name)
                        outfile << "\t" <<number << ")  " << temp->Name << " " << temp->Priority << endl;
                }
            }

            number++;
            //delete the heap or make it to null
            temp = NULL;
        }
        
       
            
        number = 0;
    }
    outfile.close();
    return 0;
}
