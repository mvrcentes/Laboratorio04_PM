//Programación de Microprocesadores
//Laboratorio 4 Parte 1 secuencial
//Marco Ramirez 21032

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <iostream>
#include <iterator>
#include <vector>


//Variables 
double totalSold, varCost, monthUtility;
#define TOTAL_PRODUCTS 8
void* thread_result_Sold;
void* thread_result_VarCost; 
void* thread_result_MonthUtility;

class Producto{  
  private:
    std::string nombre;
    double unitPrice, unitCost, unitSold;
    
  public:
    Producto() {}

    Producto(std::string nombre, double unitPrice, double unitCost, double unitSold){
      this->nombre = nombre;
      this->unitPrice = unitPrice;
      this->unitCost = unitCost;
      this->unitSold = unitSold;
    }

    //getters and setters
    std::string getNombre(){
      return nombre;
    }
    void setNombre(std::string nombre){
      this->nombre = nombre;
    }
    double getUnitPrice(){
      return unitPrice;
    }
    void setUnitPrice(double unitPrice){
      this->unitPrice = unitPrice;
    }
    double getUnitCost(){
      return unitCost;
    }
    void setUnitCost(double unitCost){
      this->unitCost = unitCost;
    }
    double getUnitSold(){
      return unitSold;
    }
    void setUnitSold(double unitSold){
      this->unitSold = unitSold;
    }
    
    
    double getProductSales(){
        return unitPrice * unitSold;
    }
    //Ventas  por  producto  –  (Unidades  vendidas  *  Costo  fijo  por unidad)
    double getUtility(){
        return getProductSales() - (unitSold * unitCost);;
    }
};

struct Parameters{
  int id, month;
  double totalSold, varCost, monthUtility;
  std::vector<std::vector<Producto> > products;
};

void *soldReport(void *arg){
    Parameters *ps; 
    ps = (Parameters *)arg;

    // std::cout << ps->products.at(ps->month).at(ps->id).getNombre() << ":\tQ" << (ps->products.at(ps->month).at(ps->id).getProductSales()) << std::endl;
    
    double* res = (double*)malloc(sizeof(double));
    *res = ps->totalSold += ps->products.at(ps->month).at(ps->id).getProductSales();
    return res;

    pthread_exit(NULL);
};

void *varCostReport(void *arg){
    Parameters *ps; 
    ps = (Parameters *)arg;

    double* res = (double*)malloc(sizeof(double));
    *res = ps->varCost += ps->products.at(ps->month).at(ps->id).getUnitCost();
    return res;
    pthread_exit(NULL);
};

void *varUtilityReport(void *arg){
    Parameters *ps; 
    ps = (Parameters *)arg;

    // std::cout << ps->products.at(ps->month).at(ps->id).getNombre() << ":\tQ" <<(ps->products.at(ps->month).at(ps->id).getUtility()) << std::endl;
    
    double* res = (double*)malloc(sizeof(double));
    *res = ps->monthUtility += ps->products.at(ps->month).at(ps->id).getUtility();
    return res;
    
    pthread_exit(NULL);
};



int main(){
    pthread_t tid;
    Parameters p;
    fflush(stdin);
    
    int mes;
    double tSold;
    double tVarCost;
    double tUtilityMonth; 
    bool salir = false;
    std::vector<Producto> productsJulio;
    std::vector<Producto> productsAgosto;


    productsJulio.insert(productsJulio.end(), Producto("Porcion pastel de chocolate", 60, 20, 300));
    productsJulio.insert(productsJulio.end(), Producto("White mocha", 32, 19.20, 400));
    productsJulio.insert(productsJulio.end(), Producto("Cafe americano 8onz", 22, 13.20, 1590));
    productsJulio.insert(productsJulio.end(), Producto("Latte 8onz", 24, 17.20, 200));
    productsJulio.insert(productsJulio.end(), Producto("Toffee Coffe", 28, 20.10, 390));
    productsJulio.insert(productsJulio.end(), Producto("Cappuccino 8onz", 24, 17.20, 1455));
    productsJulio.insert(productsJulio.end(), Producto("Smore late", 32, 23, 800));
    productsJulio.insert(productsJulio.end(), Producto("Cafe tostado molido", 60, 20, 60));
                                            
    productsAgosto.insert(productsAgosto.end(), Producto("Porcion de pastel", 60, 20, 250));
    productsAgosto.insert(productsAgosto.end(), Producto("White mocha", 32, 19.20, 380));
    productsAgosto.insert(productsAgosto.end(), Producto("Cafe americano 8onz", 22, 13.20, 800));
    productsAgosto.insert(productsAgosto.end(), Producto("Latte 8onz", 24, 17.20, 250));
    productsAgosto.insert(productsAgosto.end(), Producto("Toffee Coffe", 28, 20.10, 600));
    productsAgosto.insert(productsAgosto.end(), Producto("Cappuccino 8onz", 24, 17.20, 1200));
    productsAgosto.insert(productsAgosto.end(), Producto("Smore late", 32, 23, 1540));
    productsAgosto.insert(productsAgosto.end(), Producto("Cafe tostado molido", 60, 20, 15));

    p.products.push_back(productsJulio);
    p.products.push_back(productsAgosto);
    
    while (!salir){
        std::cout << "Ingrese el mes: \n[1]\tJulio\n[2]\tAgosto\n[3]\tSalir\n";
        std::cin >> mes;
        std::string sMonth; 
        int varCostmonth;

        if (mes == 1){
            sMonth = "Julio";
            p.month = 0;
            varCostmonth = 45640;
        }else if (mes == 2){
            sMonth = "Agosto";
            p.month = 1;
            varCostmonth = 40590;
        }

        if (mes == 1 || mes == 2){
            printf ("\n ---------------------------------------------\n");
            std::cout << "\nReporte del mes de " << sMonth << "\n" << std::endl;

            printf ("Ventas por producto \n\n");
            for (double i=0; i < TOTAL_PRODUCTS; i++){
                p.id = i;
                pthread_create(&tid, NULL, soldReport, ( void *)&p);
                pthread_join(tid, &thread_result_Sold);

            }

            printf ("\n --------------------------------------------- \n");
            printf ("Utilidad por producto \n\n");
            for (double k=0; k < TOTAL_PRODUCTS; k++){
                p.id = k;
                pthread_create(&tid, NULL, varCostReport, ( void *)&p);
                pthread_join(tid, &thread_result_VarCost);
                pthread_create(&tid, NULL, varUtilityReport, ( void *)&p);
                pthread_join(tid, &thread_result_MonthUtility);
            }

            printf ("\n --------------------------------------------- \n");

            tSold = *(double*) thread_result_Sold;
            tVarCost = *(double*) thread_result_VarCost;
            tUtilityMonth= *(double*) thread_result_MonthUtility;

            free(thread_result_Sold);
            std::cout << "Total de venta: \t" << tSold << std::endl;
            std::cout << "Total de costos variables: \t" <<  varCostmonth  << std::endl;
            std::cout << "Total de utilidad: \t" << tUtilityMonth - varCostmonth << std::endl;
            printf ("\n --------------------------------------------- \n\n\n\n");

            p.totalSold = 0;
            p.varCost = 0;
            p.monthUtility = 0;
        } else if (mes == 3){
            salir = true;
        } else {
            std::cout << "Ingrese un mes valido\n";
        }
    }
    pthread_exit(NULL); 
}


