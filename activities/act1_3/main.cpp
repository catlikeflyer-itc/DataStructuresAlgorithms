#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>

#include "search.hpp"
#include "data.hpp"

// misc splitting function, same as in Data class
std::vector<std::string> splitString(std::string s, std::string del = " "){
    std::vector<std::string> d;    

    int start = 0; // starts at looking for words at char 0
    int end = s.find(del); // ends looking when it encounters char "-"

    while (end != -1) { // loop to repeat the search, adding the resulting string into the return vector
        d.push_back(s.substr(start, end - start));
        start = end + del.size(); // moves the start of the search to after the found "-" char
        end = s.find(del, start);
    }

    d.push_back(s.substr(start, end - start));
    return d;
}

//question-solution functions
void stage_1(std::vector<Data*> &data_vector){ // cleaner implementation of first question's solution
    std::cout << "Registros totales: " << data_vector.size() << std::endl;
}

void stage_2(std::vector<Data*> &data_vector){ // cleaner implementation of second question's solution
    std::vector<std::string> first_date = data_vector[0]->getFecha();
    int first_day = stoi(first_date[0]);

    std::vector<std::string> dates, chosen_date;
    int count = 0, chosen_index;

    for(int i = 1; i < data_vector.size() - 1; i++){ // loop to count second-day entries
        dates.clear();
        dates = data_vector[i]->getFecha();

        if(stoi(dates[0]) == first_day + 1){ // checks if it is the second day
            count ++;
            chosen_index = i;
        }
        else if(stoi(dates[0]) == first_day + 2){
            break;
        }
    }

    chosen_date = data_vector[chosen_index]->getFecha();

    std::cout << "Registros del segundo dia: " << count << "\t\tFecha: " << chosen_date[0] << "-" << chosen_date[1] << "-" << chosen_date[2] << std::endl;
}

void stage_3(std::vector<Data*> data_vector){ // cleaner implementation of third question's solution 

}

void stage_4(std::vector<Data*> data_vector){ // cleaner implementation of fourth question's solution
    
}

void stage_5(std::vector<Data*> data_vector){ // cleaner implementation of fifth question's solution
    
}

void stage_6(std::vector<Data*> &data_vector){ // cleaner implementation of sixth question's solution
    std::vector<std::string> mails;
    std::string mail_i;
    
    for(int i = 0; i < data_vector.size(); i++){ // loop to check all destination names
        mail_i = data_vector[i]->getNombreD();
        mails.push_back(mail_i);
    }
    
    // removes all repeated elements from the vector<string>
    std::vector<std::string>::iterator it;
    it = std::unique(mails.begin(), mails.end());
    mails.resize(std::distance(mails.begin(),it));

    bool proton_f = true, aol_f = true, outlook_f = true, gmail_f = true;
    
    // prints all mail services from the vector<string>
    std::cout << "Servicios de mail: ";
    for(int i = 0; i < mails.size(); i++){
        if (mails[i] == "protonmail.com" && proton_f == true){
            proton_f = false;
            std::cout << "\n\tprotonmail.com";
        }
        if (mails[i] == "aol.com" && aol_f == true){
            aol_f = false;
            std::cout << "\n\taol.com";
        }
        if (mails[i] == "live.com" && outlook_f == true){
            outlook_f = false;
            std::cout << "\n\tlive.com";
        }
        if (mails[i] == "gmail.com" && gmail_f == true){
            gmail_f = false;
            std::cout << "\n\tgmail.com";
        }        
    }
    std::cout << std::endl;    
}

void stage_7(std::vector<Data*> &data_vector){ // cleaner implementation of seventh question's solution
    std::vector<int> ports;
    
    for(int i = 0; i < data_vector.size(); i++){ // loop to check all destination ports, being added into a vector<int> if they are lower than 1000
        if(data_vector[i]->getPuertoD() != "-"){
            if(stoi(data_vector[i]->getPuertoD()) < 1000 && stoi(data_vector[i]->getPuertoD()) > 0){
                ports.push_back(stoi(data_vector[i]->getPuertoD()));
            }
        }
    }
    
    sort(ports.begin(),ports.end());
    ports.erase(unique(ports.begin(),ports.end()),ports.end());

    std::cout << "Puertos destino:\n";
    for(int i = 0; i < ports.size(); i++){
        std::cout << "\t" << ports[i] << std::endl;
    }
    
    // tried the code below to do the above thing, didn't work. Unless I figure out how to solve it, we delete it and use the above 
    /* // removes all repeated elements from the vector<int>
    std::vector<int>::iterator it;
    it = std::unique(ports.begin(), ports.end());
    ports.resize(std::distance(ports.begin(),it));
    
    // prints all ports lower than 1000 from the vector<int>
    std::cout << "Puertos destino: ";
    for(int i = 0; i < ports.size(); i++){
        std::cout << ports[i] << "\t";
    }
    std::cout << std::endl; */
}

int main(int argc, const char * argv[]){
    std::vector<Data*> data_vector;
    std::fstream file;

    file.open("equipo5.csv", std::ios::in);
    
    std::vector<std::string> row;
    std::string line, word, temp;  

    while (getline(file, line)) {        
        row.clear(); // cleans the vector<string> for each new row
  
        std::stringstream s(line); // used for breaking words
  
        while(getline(s, word, ',')) { // read a row's columns and store them in 'word'  
            row.push_back(word); // add each 'word' into a vector
        }
        
        // turns all .csv rows into Data objects and adds them into a vector<Data>
        data_vector.push_back(new Data(row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7]));
    }

    // ¿Cuántos registros tiene tu archivo?
    stage_1(data_vector);

    // ¿Cuántos récords hay del segundo día registrado? ¿Qué día es este? 
    stage_2(data_vector);

    // ¿Alguna de las computadoras pertenece a Jeffrey, Betty, Katherine, Scott, Benjamin, Samuel o Raymond? ¿A quiénes?
    stage_3(data_vector);

    // ¿Cuál es la dirección de la red interna de la compañía? 
    stage_4(data_vector);

    // ¿Alguna computadora se llama server.reto.com? 
    stage_5(data_vector);

    // ¿Qué servicio de correo electrónico utilizan (algunas ideas: Gmail, Hotmail, Outlook, Protonmail)? 
    stage_6(data_vector);

    // Considerando solamente los puertos destino ¿Qué puertos abajo del 1000 se están usando?
    stage_7(data_vector);    

    return 0;
}