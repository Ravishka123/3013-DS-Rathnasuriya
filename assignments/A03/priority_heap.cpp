/*
Name - Ravishka Rathnasuriya
Date- october 4th, 2019
Professor - Dr. Terry Griffin
Assignment - No. 3 Heaps and Priority Queues using json files.

Description
Using a binary heap as the data structure. 
Read a data file and print out the order in which they would be processed.
The order is based on the priority value.
The larger the number | the higher the priority.
Here we use a json file to read in our array of data of different animals.
Several classes are implemented here. 
Class coordinate will compute the distance between longitude and latitude.
We have a structure for Animals which will implement the data of each animals
Also class Animal helper will compute the priority and make instances of 
each animals using getters that will make the necessary computations.
Class heap will perform the max heap and priority queues.
Overall, we splitt each animals in to buckets based on their bucket 
number and perform a max heap.  Then we extract the top 5 animals of each
bucket based on their bucket number. 

*/



//https://stackoverflow.com/questions/55116344/how-to-setup-vs-code-for-c-14-c-17
//https://github.com/nlohmann/json

#include "json_helper.cpp"
#include <fstream>
#include <iostream>

#define _USE_MATH_DEFINES

#include <math.h>

using namespace std;

const static double EarthRadiusKm = 6372.8;

inline double DegreeToRadian(double angle) {
    return M_PI * angle / 180.0;
}



/*Class Coordinate
This will get the latitude and longitude of each animals and make coordinates
to perform the HarversineDistance.*/
class Coordinate {
public:
//parametrized constructor
    Coordinate(double latitude, double longitude) : myLatitude(latitude), myLongitude(longitude) {}

    double Latitude() const {
        return myLatitude;
    }

    double Longitude() const {
        return myLongitude;
    }
//private data
private:
    double myLatitude;
    double myLongitude;

};

/*
HarvesineDistance function.
Need 2 coordinate points one would be the longitude and latitude
And the other would be the standard distances
Then the function would compute the distance in between for each animal
based on their positions.*/

double HaversineDistance(const Coordinate &p1, const Coordinate &p2) {
    double latRad1 = DegreeToRadian(p1.Latitude());
    double latRad2 = DegreeToRadian(p2.Latitude());
    double lonRad1 = DegreeToRadian(p1.Longitude());
    double lonRad2 = DegreeToRadian(p2.Longitude());

    double diffLa = latRad2 - latRad1;
    double doffLo = lonRad2 - lonRad1;

    double computation = asin(sqrt(sin(diffLa / 2) * sin(diffLa / 2) + cos(latRad1) * cos(latRad2) * sin(doffLo / 2) * sin(doffLo / 2)));
    return 2 * EarthRadiusKm * computation;
}

/*
Structure of Animals
The details in the json file is used to construct the structure.
Each animal has a name, date, latiture, longitude, validated, version and a priority.
We implement Animal using the structure.
Having a default, parametrized constructors. */

struct Animal{
    string animal_name;
    long date;
    double latitude;
    double longitude;
    float adjustor;
    bool validated;
    string version;
    float priority;

    Animal() {
        animal_name = "";
        date = 0;
        latitude = 0.0;
        longitude = 0.0;
        adjustor = 0.0;
        validated = 0;
        version = "";
        priority = 0.0;
    }

//Parametrized constructor that assign to the animal
    Animal(string name, long _date, double lat, double lon, float pri, bool val, string ver) {
        animal_name = name;
        date = _date;
        latitude = lat;
        longitude = lon;
        adjustor = pri;
        validated = val;
        version = ver;
        priority = 0.0;
    }

//constructor for animals that would get the necessary details of the animal that was assigned to
//each animal.
    Animal(json j) {
        animal_name = j["animal_name"];
        date = j["date"];
        latitude = j["latitude"];
        longitude = j["longitude"];
        adjustor = j["adjuster"];
        validated = j["validated"];
        version = j["version"];
        priority = 0.0;
    }
};


/*
Class AnimalHelper
This will make an instance of Animal.
constructor which reads in the json file,
 Print Function,getsize, get length, calculate distance,
 get adjustor, check validated, get date,
 compute priority, return an animal are the functions that included in the class.
 These functions would compute the necessary computaions needed for the heap.
*/
class AnimalHelper {
private:
    Animal **Animals;  //Animal pointer to a pointer
    JsonHelper *J;   //pointer to jasonHelper
    json obj;  //instance of json
    int size;  //number of animals
  



public:
//reads the json file and create objects that store in as an animal.
    AnimalHelper(string filename) {
        J = new JsonHelper(filename);
        size = J->getSize();   //get the size of the file
        Animals = new Animal *[size];    //make a new animal
        for (int i = 0; i < size; i++) {
            obj = J->getNext();    //goes to the next 
            Animals[i] = new Animal(obj);  //store the object 
        }
    }

/* Print Animal Function
This will Print the details of each animal like
name of the animal, latitude, longitude, date, adjustor, validation,
and version. */

    void PrintAnimals() {
        
        for (int i = 0; i < 10; i++) {
            //cout << Animals[i]->animal_name << " " << Animals[i]->priority << endl;          
             cout << Animals[i]->animal_name << " " 
            << Animals[i]->latitude << " " 
            << Animals[i]->longitude << " " 
            << Animals[i]->date << " " 
            << Animals[i]->adjustor<< " " 
            << Animals[i]->validated << " " 
            << Animals[i]->version << endl;
                
        }
    }


/* getsize function
This will return the number of animals in the json file
*/
    double getSize(){
        return J->getSize();;
    }

    
    /*
    The get length function will return the number of characters of 
    an animal name 
    */
    double getLength(int i){
           
               return  Animals[i]->animal_name.length();            
    
    }



/*
Calculate distance function
Need to create two cordinates
One cordinate will take the latitude and longitude of the animal
The other coodrdinate will take two numbers which are from the standard position

And pass those coordinates to the HarvesineDistance function 
which compute the dostance of the animal and return it back.*/
    double CalcuteDistance(int i){
        
        Coordinate Point1(Animals[i]->latitude,Animals[i]->longitude);
        Coordinate Point2(33.9137, -98.4934);
        return HaversineDistance(Point1, Point2);
        
 }

/*
Get Adjustor function that would return the adjustor of the animal*/
        double getAdjustor(int i){
           return  Animals[i]->adjustor ;

        }


/* 
Get date function
Return the date of the animal from the standardized date */
        int getDate(int i){
            return Animals[i]->date;
        
        }

/* 
Compute priority function.
L = length of the animal_name
D = distance (latitude,longitude) is from (33.9137,-98.4934)
A = adjustor
V = validated

Priority = (6372.8 - D) * A / L
This would compute the priority of each animal */
        void computePriority(int i){
           
            Animals[i]->priority = (6372.8-CalcuteDistance(i)) *getAdjustor(i)/ getLength(i);
            //if validation is true invert the validation.
            if(Animals[i]->validated == true)
            Animals[i]->priority = Animals[i]->priority * -1; 
        }

     
/*
Animal out function 
This will return and animal with all the data whenever the out is called.*/
        Animal* out(int x){

            Animal* temp;
            temp = Animals[x];
            return temp;

        }

};


/**
 * Class Heap:
 * 
 * Public Methods:
 *    Heap(int)
 *    void Insert(int)
 *    int Remove()
 *    void PrintHeap()
 *    int Size()
 *    bool Empty()
 *    void Heapify(int*,int)
 */
class heap{

    private:
    Animal **H;   // pointer to dynamically allocated memory for Animals
    int next;    // Next available location
    int maxsize;  // Max size since were using array
    int heapsize;  // Actual number of items in the array.



/*Function IncreaseKey:Bubbles element up from given index.
 Params: [int] index  - index of item to be increased
*/
    void bubbleup(int i){
        int p = parent(i);
        while(p>0 && H[i]->priority > H[p]->priority){
            swap (i,p);
            i=p;
            p=parent(i);
        }
    }

    /** Function DecreaseKey: Bubbles element down from given index
     * Params: [int] index - index of item to be decreased
    */
    void bubbledown(int i ){
        int c = PickChild(i);
        while(c>0){
            if(H[i]->priority < H[c]->priority){
                swap(i,c);
                i=c;
                c=PickChild(i);
            }else{
                c= -1;
            }
        }
    }
    

    /**Function Swap:  Swaps two Animals in an array
     * Params:
      [int] index1 - index of item to swap with
      [int] index2 - same
     */
    void swap(int p, int i){
        Animal *temp = H[p];
        H[p]=H[i];
        H[i]=temp;
    }


/* Function Parent: Returns parent index of a given index
     Params: [int]index - index to calculate parent from
 */
    int parent(int i){
        return int(i/2);
    }


/** Function LeftChild:  Returns left index of a given index
    Params:  [int] index - index to calculate child from
    Returns [int] index - left child index
 */
    int LeftChild(int i){
        return i*2;
    }


/**Function RightChild: Returns right index of a given index
    Params: [int] index - index to calculate child from
    Returns [int] index - right child index
*/
    int RightChild(int i){
        return i*2 +1;
    }


/**Function PickChild: Return index of child to swap with or -1 to not swap.
    Params:[int] index - index of parent element
    Returns[int] index - index to swap with or -1 to not swap
 */
    int PickChild(int i) {
        if (RightChild(i) >= next) {    //No right child
            if (LeftChild(i) >= next) { //No left child
                return -1;
            } else { //you have a left no right
                return LeftChild(i);
            }
        } else {
            //right child exists
            if (H[RightChild(i)]->priority > H[LeftChild(i)]->priority) {
                return RightChild(i);
            } else {
                return LeftChild(i);
            }
        }
    }


    /*  Function Heap:  Constructor that allocates memory for array and
     *  inits vars.
     * Params: void
     * Returns void
     */
    public:
    heap(int size){
        H = new Animal*[size];
        next =1;
        maxsize = size;
        heapsize = 0;
    }


 /**Function Insert: Insert value into heap.
     * Params: [int] x - value to be inserted
 */
    void Insert(Animal *x){
        H[next] = x;
        bubbleup(next);
        next++;
        heapsize ++;
    }


/** Function Extract: Removes top element from heap (whether min or max).
    Params: void, outfile to pass to print out function
     * Returns [int] top_value - top value in the heap (min or max)
*/
    Animal extract(ofstream &outfile){
        if(empty()){
            cout << " "<< endl;
            exit(0);
        }
        Animal *retval = H[1];
        H[1] = H[--next];
        heapsize --;

        if(heapsize >1){
            bubbledown(1);
        }
        PrintHeap(retval,outfile);
        return *retval;
    }


 /**Function PrintHeap: Prints the values currently in the heap array
     based on array location, not heap order
     Params: void
     Returns void
 */
    void PrintHeap(Animal* A, ofstream &outfile){
        
            outfile << A->animal_name << " " <<A->priority << endl;
        
    }


/*size function  Returns the number of items in the heap 
*/
    int size(){
        return next -1;
    }


/*to check if the array is empty. Returns boolean true of array is empty*/
    bool empty(){
        return next == 1;
    }

/*Function for heapify 
Creates a heap out of a given array of animals in no specific order
*/
    void heapify(heap *A, int size){
        int i = size/2;

        for(int j = i; j>=1; j--){
            bubbledown(j);
        }
    }
};


        
  
    

//main file.

int main(int argc, char **argv) {
    
//create the output file to print the results.
    ofstream outfile;
    outfile.open("A3Output.txt");
    outfile<< "Ravishka Rathnasuriya " <<endl;
    int number_of_buckets  ;  //number of buckets needed
    cin >> number_of_buckets;
    
//create an instance of Abimal
    AnimalHelper AH("animals.json");

//call the get functions to compute the priority
    for(int i =0; i< AH.getSize(); i++){
    AH.getLength(i);   //get the name length
    AH.CalcuteDistance(i);    //compute the distance
    AH.getAdjustor(i);   //get the adjustor value
   // AH.checkValidated(i);  //check if validated
    AH. computePriority(i);   //compute the priority
    AH.getDate(i);  //get the date of the animal
   
    }


//create the bucket heaps that would dynamically allocate memory
    heap **Buckets = new heap*[number_of_buckets];
    for(int i =0; i< number_of_buckets;i++){  //iterate for no of buckets
        Buckets[i] = new heap(AH.getSize());
    }

//this loop will insert each animal to the respective bucket they belong to
    for (int x = 0; x < AH.getSize(); x++)
    {
        Animal *temp = AH.out(x); //create an animal temp

        //compute the bucket number
        int Buck = abs(AH.getDate(x))%number_of_buckets; 

        Buckets[Buck]->Insert(temp);  //insert the animal
    }

//this loop will print the heaps that we needed in buckets
     for (int i = 0; i < number_of_buckets; i++) {
		outfile << endl << "Heap " << i << endl
			<< "========================" << endl;
		for (int j = 1; j <= 5; j++) {
			Buckets[i]->extract(outfile);  //will extract the top animal from the bucket
		}
	}
    outfile.close();         //close the output file
    return 0;
}