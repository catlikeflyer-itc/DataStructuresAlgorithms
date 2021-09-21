#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "data.hpp"

//question-solution functions
void stage_1(std::vector<Data> data_vector){ // cleaner implementation of first question's solution
    std::cout << "Registros totales: " << data_vector.size() << std::endl;
}

void stage_2(std::vector<Data> data_vector){ // cleaner implementation of second question's solution
    std::vector<std::string> first_date = data_vector[0].getFecha();
    int first_day = stoi(first_date[0]);

    std::vector<std::string> dates, chosen_date;
    int count = 0, chosen_index;

    for(int i = 1; i < data_vector.size() - 1; i++){ // loop to count second-day entries
        dates.clear();
        dates = data_vector[i].getFecha();

        if(stoi(dates[0]) == first_day + 1){ // checks if it is the second day
            count ++;
            chosen_index = i;
        }
        else if(stoi(dates[0]) == first_day + 2){
            break;
        }
    }

    chosen_date = data_vector[chosen_index].getFecha();

    std::cout << "Registros del segundo dia: " << count << "\tFecha: " << chosen_date[0] << "-" << chosen_date[1] << "-" << chosen_date[2] << std::endl;
}

void stage_3(std::vector<Data> data_vector){ // cleaner implementation of third question's solution

}

void stage_4(std::vector<Data> data_vector){ // cleaner implementation of fourth question's solution
    
}

void stage_5(std::vector<Data> data_vector){ // cleaner implementation of fifth question's solution
    
}

void stage_6(std::vector<Data> data_vector){ // cleaner implementation of sixth question's solution
    
}

void stage_7(std::vector<Data> data_vector){ // cleaner implementation of seventh question's solution
    
}

int main(int argc, const char * argv[]){
    std::vector<Data> data_vector;
    std::fstream fin;
  
    // open the .csv
    fin.open("equipo5.csv");
  
    // read the data from the rows as vector<string>
    std::vector<std::string> row;
    std::string line, word, temp;
  
    while (fin >> temp) {
        
        row.clear(); // cleans the vector<string> for each new row
  
        getline(fin, line); // read an entire row and store it in a string variable 'line'
  
        std::stringstream s(line); // used for breaking words
  
        while(getline(s, word, ',')) { // read a row's columns and store them in 'word'
  
            row.push_back(word); // add each 'word' into a vector
        }
        
        // turns all .csv rows into DAta objects and adds them into a vector<Data>
        data_vector.push_back(Data(row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7]));
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