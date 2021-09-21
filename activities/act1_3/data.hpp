#ifndef data_hpp
#define data_hpp
#include <iostream>
#include <vector>

class Data{
    protected:
        std::vector<std::string> fecha;
        std::string hora;
        std::string ip_o;
        std::string puerto_o;
        std::string nombre_o;
        std::string ip_d;
        std::string puerto_d;
        std::string nombre_d;

    private:
        std::vector<std::string> splitter(std::string); // splits the date string by looking for "-"

    public:
        Data(){ // default constructor
            fecha = {""};
            hora = "";
            ip_o = "";
            puerto_o = "";
            nombre_o = "";
            ip_d = "";
            puerto_d = "";
            nombre_d = "";
        }

        Data(std::string _fecha, std::string _hora, 
        std::string _ip_o, std::string _puerto_o, std::string _nombre_o, 
        std::string _ip_d, std::string _puerto_d, std::string _nombre_d){ // overloaded constructor
            
            fecha = splitter(_fecha);
            hora = _hora;
            ip_o = _ip_o;
            puerto_o = _puerto_o;
            nombre_o = _nombre_o;
            ip_d = _ip_d;
            puerto_d = _puerto_d;
            nombre_d = _nombre_d;
        }

        ~Data(){}; // destructor

        int operator<(Data const &d); // overloaded operator <

        // setters / getters
        void setFecha(std::string);
        std::vector<std::string> getFecha();

        void setHora(std::string);
        std::string getHora();

        void setIPO(std::string);
        std::string getIPO();

        void setPuertoO(std::string);
        std::string getPuertoO();

        void setNombreO(std::string);
        std::string getNombreO();

        void setIPD(std::string);
        std::string getIPD();

        void setPuertoD(std::string);
        std::string getPuertoD();

        void setNombreD(std::string);
        std::string getNombreD();
};

#endif